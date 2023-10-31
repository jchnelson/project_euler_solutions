#include <set>
#include <iostream>
#include <cstddef>
#include <cmath>
#include <chrono>
#include <string>

using std::size_t;
using std::set;
using std::cout;

size_t digit_powers(size_t power)
{

    std::string digittest(power, '9');
    size_t sumtest = 0;
    while (1)
    { 
        digittest.push_back('9');
        for (const auto& digit : digittest)
        {
            sumtest += size_t(pow((digit - '0'), power));
        }
        if (sumtest < std::stoull(digittest))
            break;
    }

    set<size_t> specials;

    for (size_t i = 0; i != std::stoull(digittest); ++i)
    { 
        std::string digits = std::to_string(i);
        size_t sum = 0;
        for (const auto& digit : digits)
        {
            sum += size_t(pow((digit - '0'), power));
        }
        if (sum == i && i != 1)
            specials.insert(size_t(i));
    }
    size_t sum = 0;
    for (const auto& special : specials)
    {
        sum += special;
    }
    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = digit_powers(5);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}