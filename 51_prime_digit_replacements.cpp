#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using std::cout;
using std::sqrt;
using std::abs;
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

size_t prime_digit_replacement(size_t limit, size_t family)
{
    vector<unsigned char> rdigits; // digits in reverse order
    vector<size_t> retprimes;
    retprimes.reserve(family);
    rdigits.reserve(8);
    size_t count = 1;
    for (size_t n = 10000; n != limit; ++n)
    {
        if (n % 2 == 0 || n % 5 == 0 || n % 3 == 0)  // quick filter for obvious
            continue;                                // non-primes by last digit
           
        size_t working = n; 
        while (working > 0)
        {
            rdigits.push_back(working % 10);
            working /= 10;
        }
        size_t sz = rdigits.size();
        auto it = rdigits.rbegin();
        size_t primes = 0;
        for (size_t k = 0; k != sz -3; ++k)
        { 
            for (size_t i = 1; i != sz - 2; ++i)
            {
                for (size_t j = 2; j != sz - 1; ++j)
                {
                    if (k >= i || i >= j)
                        continue;
                    primes = 0;
                    retprimes.clear();
                    for (size_t x = 0; x != 10; ++x)
                    {
                        // make candidate number
                        size_t cand = ((x * size_t(pow(10, sz - 1 - k))) + 
                            (x * size_t(pow(10, sz - 1 - i))) +
                            (x * size_t(pow(10, sz - 1 - j))));
                        for (int pos = sz - 1; pos >= 0; --pos)
                        {
                            if (pos != i && pos != j && pos != k)
                            {
                                cand += it[pos] * size_t(pow(10, sz - 1 - pos));
                            }
                        }
                        if (cand < n)
                            continue;
                        // if x = 3 and we don't have primes, we can't make it to 8
                        if (x > (10-family) && ((10 - x) + primes) < (family))
                            break;
                        if (is_prime(cand))
                        {
                            retprimes.push_back(cand);
                            if (++primes == family)
                            {
                                sort(retprimes.begin(), retprimes.end());
                                return retprimes.front();
                            }
                        }
                    }
                }
            }
        }
        rdigits.clear();
    }
    return 0;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = prime_digit_replacement(2000000, 8);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}