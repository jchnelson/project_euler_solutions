#include <chrono>
#include <iostream>
#include <set>
#include <cstddef>
#include <string>
#include <utility>

using std::cout;
using std::size_t;
using std::string;

size_t factorial(size_t n)
{
    if (n < 2)
        return 1;
    size_t ret = n;
    for (size_t i = n - 1; i != 1; --i)
    {
        ret *= i;
    }
    return ret;
}

bool equals_fac_digits(size_t i)
{
    string istr = std::to_string(i);
    size_t sum = 0;
    for (const auto& ch : istr)
    {
        sum += factorial(ch - '0');
    }
    if (sum == i)
        return true;
    else
        return false;
}

size_t all_fac_digits()
{
    size_t retsum = 0;
    for (size_t i = 10; i != 2600000; ++i)
    {
        if (equals_fac_digits(i))
            retsum += i;
    }
    return retsum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    cout << factorial(9);

    auto bob = all_fac_digits();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob <<  " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}