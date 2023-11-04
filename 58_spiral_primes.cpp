#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::size_t;
using std::string;
using std::vector;

bool is_prime(long long i)
{
    if (i == 0 || i == 1 || i == -1)
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

size_t spiral_primes(double percentage)
{
    size_t n = 1;
    size_t diagonal_count = 1; // counting center
    size_t prime_count = 0;
    for (size_t i = 3; i < 100000; ++i, ++i)
    {
        size_t move = i - 1;
        for (int j = 0; j != 4; ++j)
        {
            n += move;
            ++diagonal_count;
            if (is_prime(n))
                ++prime_count;
        }
        if (double(prime_count) / diagonal_count < percentage)
            return i;
    }
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = spiral_primes(0.10);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}