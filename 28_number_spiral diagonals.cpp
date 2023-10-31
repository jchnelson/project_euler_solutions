#include <iostream>
#include <cstddef>
#include <chrono>

using std::cout;
using std::size_t;


size_t number_spiral(size_t dimension)
{
    size_t sum = 1;
    size_t n = 1;
    dimension += 1;
    for (size_t i = 3; i < dimension; ++i, ++i)
    {
        size_t move = i-1;
        for (int j = 0; j != 4; ++j)
        { 
            n += move;
            sum += n;
        }    
    }
    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = number_spiral(1001);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n';

}