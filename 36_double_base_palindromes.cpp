#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <bitset>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;
using std::string;

std::vector<size_t> palindromes(size_t limit)
{
    // find number between 10,000 and 998,001
    // that is a palindrome. 
    std::vector<size_t> ret; 


    for (int i = 0; i != limit; ++i)
    {
        std::string i_string = std::to_string(i);
        bool is_palindrome = true;
        if (i_string.size() % 2 == 0)
        {
            for (int j = 0; j != i_string.size() / 2; ++j)
            {
                if (i_string[j] != i_string[(i_string.size() - 1) - j])
                { 
                    is_palindrome = false;
                    break;
                }
            }
        }
        else
        {
            for (int j = 0; j != std::ceil(i_string.size() / 2); ++j)
            {
                if (i_string[j] != i_string[(i_string.size() - 1) - j])
                {
                    is_palindrome = false;
                    break;
                }
            }
        }
        if (is_palindrome)
            ret.push_back(i);
    }
    return ret; // some number should have qualified before this

}

size_t double_base_palindromes(size_t limit)
{
    auto pallies = palindromes(limit);
    size_t sum = 0;
    for (const auto& pally : pallies)
    {
        if (pally == 0)
        {
            continue;
        }
        std::bitset<64> pallybits{pally};
        string bitstring = pallybits.to_string();
        bitstring = bitstring.substr(bitstring.find('1'));
        bool is_palindrome = true;
        size_t sz = bitstring.size();
        if (sz % 2 == 0)
        {
            for (int j = 0; j != sz / 2; ++j)
            {
                if (bitstring[j] != bitstring[(sz - 1) - j])
                {
                    is_palindrome = false;
                    break;
                }
            }
        }
        else
        {
            for (int j = 0; j != std::ceil(sz / 2); ++j)
            {
                if (bitstring[j] != bitstring[(sz - 1) - j])
                {
                    is_palindrome = false;
                    break;
                }
            }
        }
        if (is_palindrome)
            sum += pally;
        
    }
    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = double_base_palindromes(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}