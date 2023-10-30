#include <cstddef>
#include <cmath>
#include <iostream>
#include <set>
#include <chrono>

using std::size_t;
using std::cout;

bool n_divisors(size_t i, size_t n)
{
    std::set<size_t> divisors{1,i};
    size_t divs = 2;
    for (size_t j = 2; j <= sqrt(i); ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
            if (divisors.size() > n)
                return true;
        }
    }
    return false;
}

size_t triangle_first_n_divisors(size_t divisors)
{
    // 1 (1), 1+2(3), 1+2+3(6) etc is the series of "triangle numbers"  
    // what is the value of the first one to have 500 divisors?
    size_t tri = 1;
    for (size_t i = 2; i != 100000000 ; ++i)
    {
        tri += i;
        if (n_divisors(tri, divisors))
            break;

    }
    return tri;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    cout << triangle_first_n_divisors(500) << '\n';
    auto finish = std::chrono::high_resolution_clock::now();
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish-start)
        << " milliseconds";
}