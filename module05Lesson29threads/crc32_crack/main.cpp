#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char>& data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}

/**
 * @brief Ищет значение, которое обеспечит равенство CRC32 оригинальной строки
 * и строки с INJECTION + 4 байта
 * @param originalCrc32 оригинального вектора
 * @param injectionCrc32 CRC32 INJECTION
 * @param start начало диапазона поиска
 * @param end конец диапазона поиска
 * @return найденное значение или 0 при неудаче
 */
std::optional<uint32_t> hack(uint32_t originalCrc32, uint32_t injectionCrc32,
                             uint32_t start, uint32_t end) {
  for (uint32_t i = start; i < end; ++i) {
    // вычислить crc32 исходного файла + строка injection + 4 новых байта
    uint32_t resultCrc32 =
        crc32(reinterpret_cast<const char*>(&i), 4, ~injectionCrc32);

    if (resultCrc32 == originalCrc32) {
      std::cout << "\nSuccess.\n";
      // вернуть найденное значение
      return i;
    }

    // Отображаем прогресс
    if (i % 10000 == 0) {
      std::cout << "progress of batch " << start << '-' << end << ':'
                << static_cast<double>(i - start) /
                       static_cast<double>(end - start)
                << std::endl;
    }
  }
  return std::nullopt;  // не найдено
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Call with two args: " << argv[0]
              << " <input file> <output file>\n";
    return 1;
  }

  try {
    // определить количество потоков
    uint32_t numberOfThreads = std::thread::hardware_concurrency();
    if (numberOfThreads == 0) {
      numberOfThreads = 2;
    }

    // определить размер поддиапазонов для подбора
    const uint32_t maxVal = std::numeric_limits<uint32_t>::max();
    uint32_t batchSize = maxVal / numberOfThreads;

    const std::string INJECTION = "He-he-he";
    const std::vector<char> data = readFromFile(argv[1]);

    // вычислить crc32 исходного файла
    const uint32_t originalCrc32 = crc32(data.data(), data.size());
    // вычислить crc32 исходного файла + строка injection
    const uint32_t injectionCrc32 =
        crc32(INJECTION.data(), INJECTION.size(), ~originalCrc32);

    // объявить и зарезервировать объект для запуска потоков
    std::vector<std::thread> threads;
    threads.reserve(numberOfThreads);

    // объявить массив результатов потоков
    std::vector<std::optional<uint32_t>> results(numberOfThreads);

    // менять поддиапазон
    for (uint32_t idx = 0; idx < numberOfThreads; ++idx) {
      uint32_t start = idx * batchSize;
      uint32_t end = (idx == numberOfThreads - 1) ? maxVal : start + batchSize;

      // и стартовать потоки
      threads.emplace_back([&resultOfThread = results[idx], start, end,
                            originalCrc32, injectionCrc32]() {
        try {
          resultOfThread = hack(originalCrc32, injectionCrc32, start, end);
        } catch (const std::exception& e) {
          std::cerr << "Thread error: " << e.what() << std::endl;
          resultOfThread = 0;
        }
      });
    }

    // собрать потоки
    for (auto& tObject : threads) {
      if (tObject.joinable())
        tObject.join();

      else
        // прочие ошибки
        return 2;
    }

    // обработать массив результатов работы потоков
    for (const auto& result : results) {
      if (result != std::nullopt) {
        // собрать результирующий вектор из оригинального + INJECTION +
        // найденное значение для 4-х байт
        std::vector<char> forgedResult(data.size() + INJECTION.size() + 4);
        auto it = std::copy(data.begin(), data.end(), forgedResult.begin());
        std::copy(INJECTION.begin(), INJECTION.end(), it);
        // Заменяем последние четыре байта на подобранное значение
        replaceLastFourBytes(forgedResult, result.value());

        writeToFile(argv[2], forgedResult);
        std::cout << "\nWritten to file: " << argv[2] << "\n";
        // успех
        return 0;
      }
    }

    std::cerr << "Can't hack\n";
    // ничего не нашли подбором
    return 3;
  } catch (const std::exception& ex) {
    std::cerr << ex.what() << '\n';
    // прочие ошибки
    return 2;
  }
}
