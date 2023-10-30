#include <cmath>
#include <cstddef>
#include <set>
#include <iostream>
#include <chrono>

using std::cout;

size_t sum_divisors(size_t i)
{
    std::set<size_t> divisors{1};
    size_t divs = 2;
    for (size_t j = 2; j <= sqrt(i); ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    size_t sum = 0;
    for (const size_t& divisor : divisors)
    {
        sum += divisor;
    }
    return sum;
}

bool amicable(size_t a, size_t b)
{
    return a != b && sum_divisors(a) == b && sum_divisors(b) == a;
}




int main()
{
    cout << sum_divisors(220) << '\n';

    cout << std::boolalpha << amicable(220, 220) << '\n';

    // both methods take about the same amount of time

    auto start = std::chrono::high_resolution_clock::now();
    size_t sum = 0;
    for (size_t i = 0; i != 10000; ++i)
    {
        auto ami = sum_divisors(i);
        if (amicable(i, ami) && (ami < 10000))
        {
            sum += i;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    cout << sum << " in " 
         << std::chrono::duration_cast<std::chrono::microseconds>(finish - start) 
         << '\n';

    start = std::chrono::high_resolution_clock::now();
    std::set<size_t> amis;
    size_t sum2 = 0;
    for (size_t i = 0; i != 10000; ++i)
    {
        auto ami = sum_divisors(i);
        if ((amis.count(i) == 0 || amis.count(ami) == 0) && 
            amicable(i, ami) && (ami < 10000))
        {
            sum2 += i + ami;
            amis.insert(i);
            amis.insert(ami);
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    cout << sum2 << " in "
         << std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
         << '\n';

}