#include <chrono>
#include <iostream>
#include <set>
#include <cstddef>
#include <string>
#include <utility>

using std::cout;
using std::size_t;
using std::string;

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{ i };
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

std::pair<size_t, size_t> reduce_fraction(std::pair<size_t, size_t> frac)
{
    size_t top = frac.first;
    size_t bot = frac.second;
    if (bot == 0)
        return {top, bot};

    while (1)
    { 
        auto topdivs = divisors(top);
        auto botdivs = divisors(bot);
        bool found_div = false;
        for (const auto& div : botdivs)
        {
            if (topdivs.count(div) != 0)
            {
                top /= div;
                bot /= div;
                found_div = true;
                break;
            }
        }
        if (!found_div)
            break;
    }   
    return {top,bot};
}


std::pair<size_t, size_t> digit_cancel_frac()
{
    // 49/98 = 4/8 but not because the nines cancel, however find four of this type
    // two digits in numerator and denominator, less than one. 

    std::set<std::pair<size_t, size_t>> cancel_fracs;

    for (size_t n = 10; n != 100; ++n)
    {
        for (size_t d = 10; d != 100; ++d)
        {
            bool is_cancelfrac = false;
            string numer = std::to_string(n);
            string denom = std::to_string(d);
            for (size_t i = 0; i != 10; ++i)
            {
                char curr = '0' + i;
                if (numer.find(curr) != string::npos &&
                    denom.find(curr) != string::npos)
                {
                    if (numer[0] == curr && denom[1] == curr  && denom[0] != '0')
                    {
                        if ((double(n) / d) == double(numer[1] - '0') / (denom[0] - '0'))
                        {
                            is_cancelfrac = true;
                        }
                    }
                    else if (numer[1] == curr && denom[0] == curr && denom[1] != '0')
                    {
                        if ((double(n) / d) == double(numer[0] - '0') / (denom[1] - '0'))
                        {
                            is_cancelfrac = true;
                            cancel_fracs.insert({n, d});
                            cout << n << '/' << d << '\n';
                        }
                    }
                }
                if (is_cancelfrac)
                    break;
            }
        }
    }
    size_t top = 1;
    size_t bot = 1;
    for (const auto& cfrac : cancel_fracs)
    {
        top *= cfrac.first;
        bot *= cfrac.second;
    }
    return {top,bot};

}



int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = digit_cancel_frac();
    bob = reduce_fraction(bob);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob.first << "/" << bob.second << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}