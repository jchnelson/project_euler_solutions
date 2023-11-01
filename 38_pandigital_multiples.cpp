#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>

using std::cout;
using std::size_t;
using std::string;

std::pair<size_t, string> pandigital_multiples(size_t limit)
{
    size_t base = 0;
    std::string prods;
    for (size_t n = 2; n != limit; ++n)
    {
        prods = "";
        for (size_t i = 1;; ++i)
        {
            prods += std::to_string(n * i);
            if (prods.size() > 8)
                break;
        }
        if (prods.size() > 9)
            continue;

        bool pandig = true;
        for (int i = 1; i != 10; ++i)
        {
            auto pos = prods.find('0' + i);
            if (pos == std::string::npos || prods.find('0' + i, pos + 1)
                != std::string::npos)
            { 
                pandig = false;
                break;
            }
        }
        if (pandig)
        { 
            base = n;
        }
        
    }
    return {base, prods};

}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::pair<size_t, string> bob = pandigital_multiples(10000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob.first << " with product " << bob.second << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}