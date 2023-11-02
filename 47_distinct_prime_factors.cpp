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

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{};
    size_t divs = 2;
    for (size_t j = 2; j <= sqrt(i); ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    return divisors;
}

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

size_t distinct_prime_factors(size_t reps)
{
    size_t consec = 0;
    std::vector<size_t> conseks(reps);
    bool breaker = false;
    for (size_t i = 4; i != 1000000; ++i)
    {
        if (is_prime(i))
        {
            consec = 0;
            continue;
        }
        auto divs = divisors(i);
        size_t primes = 0;
        for (const auto& div : divs)
        {
            if (is_prime(div))
            { 
                if (++primes == reps)
                {
                    conseks[consec] = i;
                    if (++consec == reps)
                        breaker = true;
                    break;
                }
            }
        }
        if (breaker)
            break;
        else if (primes != reps)
            consec = 0;
    }
    return conseks.front();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = distinct_prime_factors(4);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}

