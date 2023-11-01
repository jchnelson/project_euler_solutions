#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <set>
#include <utility>

using std::cout;
using std::size_t;

bool is_triangle(size_t n)
{
    size_t i = 40755;
    size_t step = 286;
    bool ret = false;
    while (1)
    {
        if (i > n)
            return false;
        else if (i == n)
            return true;
        else
        {
            i += step;
            step += 1;
        }
    }
}

bool is_hex(size_t n)
{
    size_t i = 40755;
    size_t step = 573;
    bool ret = false;
    while (1)
    {
        if (i > n)
            return false;
        else if (i == n)
            return true;
        else
        {
            i += step;
            step += 4;
        }
    }
}

size_t tri_penta_hex()
{
    std::set<size_t> pentos;
    size_t i = 40755;
    size_t step = 496;
    for (size_t x = 0; x != 32000; ++x)
    {
        pentos.insert(i);
        i += step;
        step += 3;
    }
    std::set<size_t> tripentos;
    for (const auto& pento : pentos)
    {
        if (is_triangle(pento))
            tripentos.insert(pento);
    }
    for (const auto& tripento : tripentos)
    {
        if (is_hex(tripento) && tripento > 40755)
            return tripento;
    }

    return 0;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = tri_penta_hex();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}