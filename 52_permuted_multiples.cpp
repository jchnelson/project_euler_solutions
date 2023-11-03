#include <chrono>
#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>

using std::cout;
using std::size_t;
using std::vector;

bool is_permut(long long cand, long long orig)
{
    size_t working = orig;
    vector<unsigned char> vorig;
    vector<unsigned char> vcand;
    vorig.reserve(20);
    vcand.reserve(20);
    while (working > 0)
    {
        vorig.push_back(working % 10);
        working /= 10;
    }
    working = cand;
    while (working > 0)
    {
        vcand.push_back(working % 10);
        working /= 10;
    }
    sort(vorig.begin(), vorig.end());
    sort(vcand.begin(), vcand.end());
    return vorig == vcand;
}

size_t permuted_multiples(size_t multiplier)
{
    for (size_t i = 100; i != 2000000; ++i)
    {
        bool all_permut = true;
        for (size_t j = multiplier; j != 1; --j)
        {
            if (!is_permut(i * j, i))
            {
                all_permut = false;
                break;
            }
        }
        if (all_permut)
            return i;
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = permuted_multiples(6);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}