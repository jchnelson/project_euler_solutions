#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;
using std::string;
using std::vector;

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

size_t prime_permutations()
{
    string retstr;
    size_t count = 0;
    size_t j = 3330;
    for (size_t i = 2; i != 5000; ++i) // no term more than 9999
    {
        if (i + j + j > 10000 || !is_prime(i) || i == 1487)
            continue;
        if (!is_permut(i+j, i) || !is_permut(i+j+j, i))
            continue;
        if (is_prime(i + j) && is_prime(i + j + j))
        {
            retstr = std::to_string(i) + std::to_string(i + j) + 
                std::to_string(i + j + j);
            break;
        }
        if (!retstr.empty())
            break;
    }
    return std::stoull(retstr);
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = prime_permutations();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << std::boolalpha << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}