#include <cstddef>
#include <iostream>
#include <chrono>
#include <vector>

using std::cout;
using std::size_t;
using std::vector;

double factorial(double n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    double ret = n;
    for (double i = n - 1; i != 1; --i)
    {
        ret *= i;
    }
    return ret;
}

double choose(double n, double r)
{
    return (factorial(n) / (factorial(r) * (factorial(n-r))));
}

size_t varied_choose(size_t limit)
{
    size_t biggies = 0;
    limit += 1;
    for (double n = 23; n != limit; ++n)
    {
        for (double r = 1; r != limit; ++r)
        {
            if (r > n)
                continue;
            if (choose(n,r) > 1000000)
                ++biggies;
        }
    }
    return biggies;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = varied_choose(100);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}