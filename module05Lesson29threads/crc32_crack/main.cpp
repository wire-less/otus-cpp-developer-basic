#include <algorithm>
#include <iostream>
#include <limits>
#include <thread>
#include <vector>

#include "CRC32.hpp"
#include "IO.hpp"

/// @brief Переписывает последние 4 байта значением value
/*
void replaceLastFourBytes(std::vector<char>& data, uint32_t value) {
  std::copy_n(reinterpret_cast<const char*>(&value), 4, data.end() - 4);
}
*/

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
std::vector<char> hack(const std::vector<char> original,
                       const std::string injection, const uint32_t start,
                       const uint32_t end) {
  const uint32_t originalCrc32 = crc32(original.data(), original.size());
  const uint32_t injectionCrc32 =
      crc32(injection.data(), injection.size(), originalCrc32);

  std::vector<char> result(original.size() + injection.size() + 4);
  auto it = std::copy(original.begin(), original.end(), result.begin());
  std::copy(injection.begin(), injection.end(), it);

  /*
   * Внимание: код ниже крайне не оптимален.
   * В качестве доп. задания устраните избыточные вычисления
   */

  for (uint32_t i = start; i < end; ++i) {
    // Заменяем последние четыре байта на значение i
    // replaceLastFourBytes(result, uint32_t(i));
    std::copy_n(reinterpret_cast<const char*>(&i), 4, result.end() - 4);

    // Вычисляем CRC32 текущего вектора result
    uint32_t resultCrc32 =
        crc32(reinterpret_cast<const char*>(&i), 4, injectionCrc32);

    if (resultCrc32 == originalCrc32) {
      std::cout << "\nSuccess.\n";
      return result;  // вернуть найденный локальный результат в массив векторов
    }
    // Отображаем прогресс
    if (i % 1000 == 0) {
      std::cout << "progress of batch " << start << '-' << end << ':'
                << static_cast<double>(start) / static_cast<double>(end)
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

    // определить количество поддиапазонов для подбора
    const uint32_t maxVal = std::numeric_limits<uint32_t>::max();
    uint32_t batchSize = maxVal / numberOfThreads;

    const std::vector<char> data = readFromFile(argv[1]);

    std::vector<std::thread> threads;
    threads.reserve(numberOfThreads);

    // объявить массив результатов потоков
    std::vector<std::vector<char>> results(numberOfThreads);

    // менять поддиапазон
    for (uint32_t idx = 0; idx < numberOfThreads; ++idx) {
      uint32_t start = idx * batchSize;
      uint32_t end = (idx == numberOfThreads - 1) ? maxVal : start + batchSize;

      // и стартовать потоки
      threads.emplace_back([&results, data, start, end, idx]() {
        try {
          results[idx] = hack(data, "He-he-he", start, end);
        } catch (const std::exception& e) {
          std::cerr << "Thread error: " << e.what() << std::endl;
          results[idx] = {};
        }
      });
    }

    // собрать потоки
    for (auto& tObject : threads) {
      tObject.join();
    }

    // const std::vector<char> badData = hack(data, "He-he-he");
    // writeToFile(argv[2], badData);

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
  } catch (std::exception& ex) {
    std::cerr << ex.what() << '\n';
    // прочие ошибки
    return 2;
  }

  // успех
  return 0;
}
