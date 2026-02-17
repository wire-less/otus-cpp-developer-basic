#include <algorithm>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
void replaceLastFourBytes(std::vector<char>& data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}

/**
 * @brief Формирует новый вектор с тем же CRC32, добавляя в конец оригинального
 * строку injection и дополнительные 4 байта
 * @details При формировании нового вектора последние 4 байта не несут полезной
 * нагрузки и подбираются таким образом, чтобы CRC32 нового и оригинального
 * вектора совпадали
 * @param original оригинальный вектор
 * @param injection произвольная строка, которая будет добавлена после данных
 * оригинального вектора
 * @return новый вектор
 */
std::vector<char> hack(const std::vector<char>& original,
                       const std::string& injection, uint32_t originalCrc32,
                       uint32_t injectionCrc32, uint32_t start, uint32_t end) {
  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  for (uint32_t i = start; i < end; ++i) {
        // вычислить crc32 исходного файла + строка injection + 4 новых байта
    uint32_t resultCrc32 =
        crc32(reinterpret_cast<const char*>(&i), 4, ~injectionCrc32);

    if (resultCrc32 == originalCrc32) {
      // Заменяем последние четыре байта на значение i
      replaceLastFourBytes(result, i);
      std::cout << "\nSuccess.\n";
      // вернуть найденный локальный результат как элемент массива векторов
      return result;
    }

    // Отображаем прогресс
    if (i % 10000 == 0) {
      std::cout << "progress of batch " << start << '-' << end << ':'
                << static_cast<double>(i - start) /
                       static_cast<double>(end - start)
                << std::endl;
    }
  }
  // throw std::logic_error("Can't hack");
  return {};  // вернуть пустой вектор при неудаче подбора
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
    std::vector<std::vector<char>> results(numberOfThreads);

    // менять поддиапазон
    for (uint32_t idx = 0; idx < numberOfThreads; ++idx) {
      uint32_t start = idx * batchSize;
      uint32_t end = (idx == numberOfThreads - 1) ? maxVal : start + batchSize;

      // и стартовать потоки
      threads.emplace_back([&resultOfThread = results[idx], &data, start, end,
                            INJECTION, originalCrc32, injectionCrc32]() {
        try {
          resultOfThread =
              hack(data, INJECTION, originalCrc32, injectionCrc32, start, end);
        } catch (const std::exception& e) {
          std::cerr << "Thread error: " << e.what() << std::endl;
          resultOfThread.clear();
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
      if (!result.empty()) {
        writeToFile(argv[2], result);
        std::cout << "\nWritten to file: " << argv[2] << "\n";
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

  // успех
  return 0;
}
