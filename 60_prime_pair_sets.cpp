#include <vector>
#include <cstddef>
#include <cmath>
#include <chrono>
#include <iostream>
#include <set>

using std::size_t;
using std::sqrt;
using std::abs;
using std::cout;

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

size_t power(size_t n, size_t exp)
{
    size_t ret = 1;
    for (size_t i = 0; i != exp; ++i)
    {
        ret *= n;
    }
    return ret;
}

std::vector<unsigned char> get_rdigits(size_t n)
{
    std::vector<unsigned char> digits;
    digits.reserve(16);

    digits.push_back(n % 10);
    size_t working = n;
    while (working > 9)
    {
        working /= 10;
        digits.push_back(working % 10);
    }
    return digits;
}

bool prime_append(size_t a, size_t b)
{
    auto adig = get_rdigits(a);
    auto bdig = get_rdigits(b);
    size_t asz = adig.size();
    size_t bsz = bdig.size();

    // append left
    size_t working = a;
    for (size_t k = 0; k != bsz; ++k)
        working += (bdig[k] * power(10, asz + k));
    if (!is_prime(working))
        return false;

    // append right
    working = b;
    for (size_t k = 0; k != asz; ++k)
        working += (adig[k] * power(10, bsz + k));
    if (!is_prime(working))
        return false;

    return true;
}

size_t prime_pair_sets(size_t family)
{
    std::set<size_t> buddies;
    while (1)
        for (size_t i = 3; i != 10000; ++i)
        {
            if (!is_prime(i) || buddies.count(i) != 0)
                continue;
            for (size_t j = 5; j != 10000; ++j)
            {
                if (i == j || !is_prime(j) || buddies.count(j) != 0 )
                    continue;

                bool is_buddy = true;
                for (const auto& buddy : buddies)
                {
                    if (buddy == i || buddy == j)
                        continue;
                    if (buddies.count(i) == 0 && !prime_append(buddy, i))
                    { 

                        is_buddy = false;
                        break;
                    }
                    if (!prime_append(buddy, j))
                    {
                        is_buddy = false;
                        break;
                    }
                }
                if (!is_buddy || !prime_append(i,j))
                    continue;


                buddies.insert(i);
                buddies.insert(j);

                if (buddies.size() >= family)
                {
                    size_t retsum = 0;
                    for (const auto& buddy : buddies)
                    {
                        cout << buddy << '\n';
                        retsum += buddy;
                    }
                    return retsum;
                }
            }
            buddies.clear();
        }
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = prime_pair_sets(5);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}