#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <vector>

using std::cout;
using std::size_t;
using std::string;

void make_permut(const string& word, const string& avail,
    std::vector<string>& permutations)
{
    string currword = word;
    for (const auto& ch : avail)
    {
        currword.push_back(ch);
        if (currword.size() == 10)
        {
            if (std::stoi(currword.substr(7, 3)) % 17 == 0 &&
                std::stoi(currword.substr(6, 3)) % 13 == 0 &&
                std::stoi(currword.substr(5, 3)) % 11 == 0 &&
                std::stoi(currword.substr(4, 3)) % 7 == 0 &&
                std::stoi(currword.substr(3, 3)) % 5 == 0 &&
                std::stoi(currword.substr(2, 3)) % 3 == 0 &&
                std::stoi(currword.substr(1, 3)) % 2 == 0
                )
                    permutations.push_back(currword);
        }
        else
        {
            string curravail = avail;
            auto pos = curravail.find(ch);
            curravail.erase(pos, 1);
            make_permut(currword, curravail, permutations);

        }
        currword.pop_back();
    }
}

std::vector<string> lexico_permut(const string& orig)
{

    std::vector<string> permutations;
    permutations.reserve(100);

    for (char i = 1; i != 10; ++i)
    {
        string avail = orig;
        string word;
        word.push_back('0' + i);
        size_t pos = avail.find('0' + i);
        avail.erase(pos, 1);
        make_permut(word, avail, permutations);
        word.pop_back();
    }
    return permutations;
}

size_t substring_divisibility()
{
    auto bob = lexico_permut("0123456789");
    size_t retsum = 0;
    for (const auto& s : bob)
    {
        retsum += std::stoull(s);
    }
    return retsum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = substring_divisibility(); // 4160357289

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}