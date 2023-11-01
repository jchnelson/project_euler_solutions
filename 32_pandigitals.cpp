#include <chrono>
#include <iostream>
#include <set>
#include <cstddef>
#include <string>
#include <cmath>


using std::sqrt;
using std::cout;

// find the sum of all numbers whose product and multiplicands together
// use all digits 1-9 once

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{ 1,i };
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

size_t pandigital_sum()
{
    std::set<size_t> pandigitals;
    for (size_t i = 2000; i != 10000; ++i)
    {
        auto divs = divisors(i);
        for (const auto& div1 : divs)
        {
            for (const auto& div2 : divs)
            {
                if (div1 * div2 == i)
                {
                    std::string tester = std::to_string(div1) + std::to_string(div2)
                        + std::to_string(i);
                    bool pandig = true;
                    for (int i = 1; i != 10; ++i)
                    {
                        auto pos = tester.find('0'+i);
                        if (pos == std::string::npos || tester.find('0'+i, pos + 1) 
                            != std::string::npos)
                            pandig = false;
                    }
                    if (pandig)
                        pandigitals.insert(i);
                }
            }
        }
    }
    size_t sum = 0;
    for (const auto& pan : pandigitals)
    {
        sum += pan;
    }
    return sum;

}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = pandigital_sum();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}