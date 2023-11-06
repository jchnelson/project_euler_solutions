#include <vector>
#include <cstddef>
#include <cmath>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>

using std::string;
using std::size_t;
using std::sqrt;
using std::abs;
using std::cout;

static size_t origsize = 0;
static size_t reqvec = 0;
static std::set<size_t> cubes;

bool is_permut(long long cand, long long orig)
{
    std::vector<unsigned char> vorig;
    std::vector<unsigned char> vcand;
    vorig.reserve(20);
    vcand.reserve(20);
    size_t working = orig;
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

bool is_cube(long long cand)
{
    size_t test = 0;
    for (size_t i = 2; ; ++i)
    {      
        if ((test = i * i * i ) == cand)
            return true;
        if (test > cand)
            return false;
    }
}

size_t next_cube()
{
    static size_t i = 350;
    size_t ret = i * i * i;
    ++i;
    return ret;
}

std::vector<unsigned char> get_rdigits(size_t n)
{
    std::vector<unsigned char> digits;
    digits.reserve(16);

    digits.push_back(n % 10);
    size_t working = n;
    while (working > 9)
    {
        working /= 10;
        digits.push_back(working % 10);
    }
    return digits;
}

size_t number_digits(size_t i)
{
    size_t ret = 0;
    while (i > 0)
    {
        i /= 10;
        ++ret;
    }
    return ret;
}


size_t cubic_permutations(size_t amount)
{
    reqvec = amount;
    size_t ret = 0;
    for (size_t i = 0; i != 10000; ++i)
    {
        cubes.insert(next_cube());
    }
    size_t dig1 = 0;
    size_t dig2 = 0;
    for (const auto& cube1 : cubes)
    {
        dig1 = number_digits(cube1);
        size_t permutations = 0;
        for (const auto& cube2 : cubes)
        {

            if ((dig2 = number_digits(cube2)) < dig1)
                continue;
            if (dig2 > dig1)
                break;
            if (is_permut(cube2, cube1))
            {
                if (++permutations == amount)
                    return cube1;
            }
        }
    }
    return ret;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = cubic_permutations(5);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}