#include <cstddef>
#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <set>

using std::cout;
using std::size_t;
using std::vector;

size_t power(size_t n, size_t exp)
{
    size_t ret = 1;
    for (size_t i = 0; i != exp; ++i)
    {
        ret *= n;
    }
    return ret;
}

bool palindrome(size_t cand)
{
    std::vector<unsigned char> digits;
    digits.reserve(16);

    digits.push_back(cand % 10);
    size_t working = cand;
    while (working > 9)
    {
        working /= 10;
        digits.push_back(working % 10);
    }
    size_t sz = digits.size();
    if (sz % 2 == 0)
    {
        for (size_t j = 0; j != sz / 2; ++j)
        {
            if (digits[j] != digits[(sz - 1) - j])
            {
                return false;
            }
        }
    }
    else
    {
        for (size_t j = 0; j != std::ceil(sz / 2); ++j)
        {
            if (digits[j] != digits[(sz - 1) - j])
            {
                return false;
            }
        }
    }
    return true;
}

size_t reverse_digits(size_t n)
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
    size_t sz = digits.size();
    size_t ret = 0;
    for (size_t i = 0; i != sz; ++i)
    {
        ret += digits[sz-1-i] * power(10,i);
    }
    return ret;

}

size_t count_lychrel_numbers(size_t limit)
{
    limit += 1;
    size_t lychrels = 0;
    for (size_t i = 0; i != limit; ++i)
    {
        size_t result = i;
        bool is_lychrel = true;
        for (size_t j = 1; j != 51; ++j)
        {
            result += reverse_digits(result);
            if (palindrome(result))
            {
                is_lychrel = false;
                break;
            }
        }
        if (is_lychrel)
            ++lychrels;
    }
    return lychrels;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = count_lychrel_numbers(10000); // 4160357289

    auto finish = std::chrono::high_resolution_clock::now();

    cout << std::boolalpha << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}