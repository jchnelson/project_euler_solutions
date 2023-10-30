#include <cstddef>
#include <iostream>
#include <chrono>

using std::size_t;
using std::cout;

using htp = std::chrono::high_resolution_clock::time_point;


size_t* longest_collatz(size_t max_start)
{
    // if even n becomes n/2, if odd, n becomes 3n + 1

    // I saw that someone else was using a dictionary to track partial
    // results, so I tried to implement it but it made it INCREDIBLY slow

    size_t longest = 0;
    size_t n = 0;
    for (size_t i = 2; i <= max_start; ++i)
    {
        size_t x = i;
        size_t length = 0;
        while (1)
        { 
            if (x % 2 == 0)
                x /= 2;
            else
                x = (3 * x) + 1;
            ++length;
            if (x == 1)
            {
                if ( length > longest)
                { 
                    longest = length;
                    n = i;    
                }
                break;
            }
        }
    }
    return new size_t[2] {n, longest};
}


int main()
{
    htp start = std::chrono::high_resolution_clock::now();
    size_t* bob = longest_collatz(10000);
    htp finish = std::chrono::high_resolution_clock::now();
    cout << bob[0] << " and length was " << bob[1] << ". Processing took "
        << std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
}