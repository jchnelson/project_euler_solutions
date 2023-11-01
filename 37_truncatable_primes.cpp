#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;
using std::string;

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

size_t truncatable_primes()
{
    size_t retsum = 0;
    for (size_t i = 23; i != 739398; ++i)
    {
        bool is_trunc = false;
        if (is_prime(i))
        { 
            is_trunc = true;
            string istr = std::to_string(i);
            size_t sz = istr.size();
            for (size_t j = 1; j != sz; ++j)
            {
                if (!is_prime(std::stoull(istr.substr(j))))
                {
                    is_trunc = false;
                    break;
                }
                if (!is_prime(std::stoull(istr.substr(0, sz - j))))
                {
                    is_trunc = false;
                    break;
                }
            }
        }
        if (is_trunc)
            retsum += i;
    }
    return retsum;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = truncatable_primes();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}