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

size_t integer_right_triangles(size_t limit)
{

    double one = 1;
    size_t solut = 0;
    size_t perim = 0;
    limit += 1;
    for (double n = 5; n != limit; ++n)
    { 
        size_t currsolut = 0;
        size_t currperim = 0;
        double amax = n/1.5;
        double bmin = n/3;
        for (double a = 1; a < amax ; ++a)
        {
            for (double b = bmin; b < n; ++b)
            {

                double c = sqrt((a * a) + (b * b));
                
                if (std::modf(c, &one) != 0 || a + b + c != n)
                { 
                    continue;
                }
                else
                {
                    currperim = a + b + c;
                    ++currsolut;
                }
            }
        }
        if (currsolut > solut)
        {
            solut = currsolut;
            perim = n;
        }
    }
    return perim;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = integer_right_triangles(1000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}