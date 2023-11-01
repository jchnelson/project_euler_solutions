#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <set>
#include <utility>

using std::cout;
using std::size_t;

std::pair<size_t, size_t> min_sum_diff()
{
    // both are pentagonal, sum and difference is pentagonal
    std::set<size_t> pentos;
    size_t i = 1;
    size_t step = 4;
    for (size_t x = 0; x != 2500; ++x)
    {
        pentos.insert(i);
        i += step;
        step += 3;
    }
    size_t curr1 = 0;
    size_t curr2 = 0;
    size_t min_diff = std::string::npos;
    size_t counter = 0;
    for (const auto p1 : pentos)
    {
        for (const auto p2 : pentos)
        {           
            if (p2 > p1 
                && pentos.count(p1 + p2) != 0 
                && pentos.count(p2 - p1) != 0 
                && (p2 - p1) < min_diff) 
            {
                curr1 = p1;
                curr2 = p2;
                min_diff = p2-p1;
            }
        }
    }
    return {curr1, curr2};
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = min_sum_diff();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob.first << " and " << bob.second << " -- in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

    cout << "D: " << bob.second - bob.first;

}