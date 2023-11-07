#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::deque;
using std::sqrt;
using std::abs;

bool is_square(unsigned n)
{
    if (n == 0 || n == 1)
        return true;
    unsigned x = 0;
    for (unsigned i = 1; n > x; ++i)
    {
        x = i * i;
        if (n == x)
            return true;
    }
    return false;
}


struct triple {

    unsigned one = 0;
    unsigned two = 0;
    unsigned three = 0;
};

bool operator==(const triple& t1, const triple& t2)
{
    return t1.one == t2.one && t1.two == t2.two && t1.three == t2.three;
}


unsigned odd_period_square_roots(unsigned limit)
{
    unsigned odds = 0;
    std::vector<triple> triplets;
    triplets.reserve(30);
    for (unsigned i = 2; i != limit; ++i)
    {
        if (is_square(i))
            continue;

        unsigned m = 0;
        unsigned d = 1;
        unsigned a0 = unsigned(sqrt(i));
        unsigned a = a0;
        unsigned nm = 0;
        unsigned nd = 0;
        unsigned na = 0;
        while (1)
        {

            nm = d * a - m;
            nd = unsigned(double(i - (nm * nm)) / d);
            na = (a0 + nm) / nd; // floor after division

            m = nm;
            d = nd; 
            a = na;

            if (find(triplets.cbegin(), triplets.cend(), 
                triple{nm,nd,na}) != triplets.cend())
                break;
            else
                triplets.push_back({nm,nd,na});
        }
        if (triplets.size() % 2 != 0)
            ++odds;
        triplets.clear();

    }
    return odds;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    unsigned bob = odd_period_square_roots(10000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}