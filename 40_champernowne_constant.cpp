#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>

using std::cout;
using std::size_t;
using std::string;

size_t champernowne(size_t limit)
{
    size_t place = 0;
    size_t last_place = 0;
    std::vector<size_t> tenners;
    tenners.reserve(10);
    size_t threshold = 1;
    limit += 1;
    for (size_t i = 1; i != limit; ++i)
    {
        size_t n = i;
        while (n > 0)
        {
            place += 1;
            n /= 10;
        }
        if (place >= threshold)
        {
            size_t index = i < 10 ? 0 : threshold - last_place - 1;
            threshold *= 10;
            string istr= std::to_string(i);
            // example, n was 998, i is 3 digits, we would need digit 2 of i
            tenners.push_back(istr[index] - '0');
        }
        last_place = place;
    }
    size_t retprod = 1;
    for (const auto& tenner : tenners)
    {
        retprod *= tenner;
    }
    return retprod;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = champernowne(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}