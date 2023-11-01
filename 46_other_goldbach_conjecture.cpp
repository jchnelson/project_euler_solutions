#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <set>
#include <cmath>
#include <utility>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;

bool is_prime(long long i)
{
    if (i == 0 || i == 1)
        return false;

    long long max = long long(sqrt(abs(i)));
    for (long long j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            return false;
        }
    }
    return true;
}

size_t other_goldbach()
{
    for (size_t i = 9; i != 10000000; ++i)
    {
        if (i % 2 == 0 || is_prime(i) || is_prime(i-2))
            continue;
        bool continuer = false;
        for (size_t j = 0; j != 1000000; ++j)
        {
            if (i < (2 * j*j))
                break;

            if (is_prime(i-(2 * j * j)))
            {
                continuer = true;
                break;
            }
        }
        if (continuer)
            continue;
        return i;
    }
    return 0;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = other_goldbach();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}