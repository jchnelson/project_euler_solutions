#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>

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

void rotate_str_in_place(string& s)
{
    char c = s.back();
    s.pop_back();
    s.insert(0,1,c);
}

size_t circular_primes(size_t limit)
{
    size_t retnum = 0;
    for (size_t i = 0; i != limit; ++i)
    {
        if (is_prime(i))
        { 
            bool is_circular = true;
            string istr = std::to_string(i);
            for (size_t j = 0; j != istr.size()-1; ++j)
            {
                rotate_str_in_place(istr);
                if (!is_prime(std::stoull(istr)))
                    is_circular = false;
            }
            if (is_circular)
                ++retnum;
        }
    }
    return retnum;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = circular_primes(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}