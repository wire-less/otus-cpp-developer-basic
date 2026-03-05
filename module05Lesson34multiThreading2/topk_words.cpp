// Read files and prints top k word by frequency

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <future>
#include <mutex>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

void count_words(std::istream &stream, Counter &, std::mutex &mtx);

void print_topk(std::ostream &stream, const Counter &, const size_t k);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Приготовиться к распараллеливанию задачи на потоки
    std::vector<std::future<void>> workers;
    std::mutex mtx;

    Counter freq_dict;
    // Создать вектор для открываемых файлов
    std::vector<std::ifstream> file_streams;
    file_streams.reserve(argc - 1);

    for (int i = 1; i < argc; ++i)
    {
        file_streams.emplace_back(argv[i]);

        if (!file_streams.back().is_open())
        {
            std::cerr << "Failed to open file " << argv[i] << '\n';
            return EXIT_FAILURE;
        }

        // Запустить обработку каждого файла в отдельном потоке с общим mutex и единым словарем
        workers.emplace_back(std::async(std::launch::async, count_words, std::ref(file_streams.back()), std::ref(freq_dict), std::ref(mtx)));
    }

    // Подождать завершения всех потоков выполнения программы
    for (auto &worker : workers)
    {
        worker.get();
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " \u03bcs\n";
}

std::string tolower(const std::string &str)
{
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch)
                   { return std::tolower(ch); });
    return lower_str;
};

void count_words(std::istream &stream, Counter &counter, std::mutex &mtx)
{
    std::for_each(std::istream_iterator<std::string>(stream),
                  std::istream_iterator<std::string>(),
                  [&counter, &mtx](const std::string &s)
                  { std::lock_guard<std::mutex> lock(mtx); ++counter[tolower(s)]; });
}

void print_topk(std::ostream &stream, const Counter &counter, const size_t k)
{
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it)
    {
        words.push_back(it);
    }

    // вычислить итератор верхней границы диапазона элементов к сортировке
    auto middle_iter = std::begin(words) + std::min(k, words.size());

    std::partial_sort(
        std::begin(words), middle_iter, std::end(words),
        [](const auto &lhs, const auto &rhs)
        { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), middle_iter,
        [&stream](const Counter::const_iterator &pair)
        {
            stream << std::setw(4) << pair->second << " " << pair->first
                   << '\n';
        });
}