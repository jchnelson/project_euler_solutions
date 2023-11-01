#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <fstream>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;
using std::string;

bool is_triangle(size_t n)
{
    size_t i = 1;
    size_t step = 2;
    bool ret = false;
    while (1)
    {
        if (i > n)
            return false;
        else if (i == n)
            return true;
        else
        {
            i += step;
            step += 1;
        }
    } 
}

size_t coded_triangle_numbers()
{
    std::ifstream bob("words.txt");
    char nextword[100]{};
    char garbage[10]{};
    std::vector<std::string> words;
    words.reserve(2000);
    while (bob.getline(garbage, 10, '"')) // this get gets the garbage
    {
        bob.getline(nextword, 100, '"');
        words.push_back(nextword);
    }
    size_t triwords = 0;
    for (const auto& word : words)
    {

        size_t wordval = 0;
        for (size_t i = 0; i != word.size(); ++i)
        {
            wordval += word[i] + 1  - 'A';
        }
        if (is_triangle(wordval))
            ++triwords;
    }
    return triwords;

}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = coded_triangle_numbers();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}