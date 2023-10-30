#include <vector>
#include <string>
#include <cstddef>
#include <iostream>
#include <chrono>

using std::cout;
using std::size_t;
using std::string;

// one millionth lexicographic (in numeric/alphab order) permutation of 0123456789

void make_permut(const string& word, const string& avail, 
                 std::vector<string>& permutations, const size_t& reqsize)
{
    string currword = word;
    for (const auto& ch : avail)
    {
        if (permutations.size() == reqsize)
            return;
        currword.push_back(ch);
        if (currword.size() == 10)
        { 
            permutations.push_back(currword);

        }
        else
        { 
            string curravail = avail;
            auto pos = curravail.find(ch);
            curravail.erase(pos, 1);
            make_permut(currword, curravail, permutations, reqsize);

        }
        currword.pop_back();
    }
}

string lexico_permut(const string& orig, const size_t& reqsize)
{

    std::vector<string> permutations;
    permutations.reserve(reqsize + 1);
    
    for (char i = 0; i != 10; ++i)
    {
        string avail = orig;
        string word;
        word.push_back('0' + i);
        size_t pos = avail.find('0' + i);
        avail.erase(pos, 1);
        make_permut(word, avail, permutations, reqsize);
        if (permutations.size() == reqsize)
            return permutations.back();
        else
            word.pop_back();
    }
    cout << "bob";
    return "something went wrong";
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto bob = lexico_permut("0123456789", 1000000);
    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);
}
