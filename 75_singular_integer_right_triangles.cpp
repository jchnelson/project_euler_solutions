#include <chrono>
#include <iostream>
#include <set>
#include <map>
#include <array>
#include <cstddef>
#include <utility>
#include <vector>

using std::cout;
using std::size_t;
using std::string;

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{};
    size_t max = size_t(sqrt(i));
    for (size_t j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    return divisors;
}

bool check_divisors(size_t i, size_t n, std::set<size_t> n_divisors)
{
    if (i % n == 0)
        return false;
    size_t max = size_t(sqrt(i));
    for (size_t j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            if (n_divisors.count(j) != 0 || n_divisors.count(i / j) != 0)
                return false;
        }
    }
    return true;
}

size_t singular_integer_right_triangles(size_t limit)
{
    ++limit;

    size_t count = 0;
    size_t m_max = size_t(sqrt(limit));  // a guess
    std::map<size_t, std::set<std::array<size_t,3>>> triples;

    for (size_t m = 1; m != m_max; ++m)
    {
        
        if (++count == 50)
        {
            cout << m << '\n';
            count = 0;
        }
        
        bool m_even = m % 2 == 0;
        std::set<size_t> m_divisors = divisors(m);
        for (size_t n = 1; m > n; ++n)
        {
            bool n_even = n % 2 == 0;
            if (m_even && n_even || !m_even && !n_even || 
                !check_divisors(n, m, m_divisors))
                continue; // only one must be even, and they must be coprime

            size_t a = (m * m) - (n * n);
            size_t b = 2 * m * n;
            size_t c = (m * m) + (n * n);


            size_t perim = a + b + c;
            if (!(perim > limit))
                triples[perim].insert({a,b,c});
                
            for (size_t k = 2; (perim * k) < limit; ++k)
            {
                triples[perim *k].insert({a*k, b*k, c*k});
            }        
        }
    }
    size_t ret = 0;
    for (const auto& ind : triples)
    {
        if (ind.second.size() == 1)
            ++ret;
    }
    return ret;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = singular_integer_right_triangles(1500000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}