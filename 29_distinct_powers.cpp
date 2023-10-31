#include <set>
#include <iostream>
#include <cstddef>
#include <cmath>
#include <chrono>

using std::size_t;
using std::set;
using std::cout;

size_t distinct_powers(size_t min, size_t max)
{
    max += 1;
    set<double> powers;
    for (int i = min; i != max; ++i)
        for (int j = min; j != max; ++j)
        {
            powers.insert(pow(i,j));
        }
    return powers.size();
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = distinct_powers(2, 100);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' 
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}