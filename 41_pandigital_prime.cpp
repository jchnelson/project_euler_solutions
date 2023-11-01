#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>

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

bool pandigital(size_t n)
{
    std::string nstr = std::to_string(n);
    bool pandig = true;
    size_t sz = nstr.size() + 1;
    for (int i = 1; i != sz; ++i)
    {
        auto pos = nstr.find('0' + i);
        if (pos == std::string::npos || nstr.find('0' + i, pos + 1)
            != std::string::npos)
        {
            pandig = false;
            break;
        }
    }
    return pandig;
}

size_t largest_pandigital_prime(size_t largest_digit)
{
    size_t max = std::stoull(std::string(largest_digit, '9'));
    largest_digit += 1;
    std::string minstr;
    for (char i = 1; i != largest_digit; ++i)
    {
        minstr.push_back('0' + i);
    }
    size_t min = std::stoull(minstr)-1;
    for (size_t i = max; i != min; --i)
    {
        if (i % 2 == 0 || i % 3 == 0) continue;
        if (pandigital(i) && is_prime(i))
        {
            return i; // first found will be largest
        }
    }
    return 0; // none found

}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = largest_pandigital_prime(7);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
        
}