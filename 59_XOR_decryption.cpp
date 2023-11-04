#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <fstream>

using std::cout;
using std::size_t;
using std::string;
using std::vector;

vector<unsigned char> text_file_chars()
{
    std::basic_ifstream<unsigned char> bob("cipher.txt");
    vector<unsigned char> text;
    text.reserve(100000);
    unsigned char the_chars[3];
    while (bob.get(the_chars, 3, ','))
    {
        size_t count = bob.gcount();
        if (bob.get() != ',')
            bob.unget();
        unsigned char test = 0;
        if (count == 3)
        { 
            test += ((the_chars[0] - '0') * 100) + ((the_chars[1] - '0') * 10) +
            (the_chars[2] - '0');
        }
        if (count == 2)
        { 
            test += ((the_chars[0] - '0') * 10) +(the_chars[1] - '0');
        }
        if (count == 1)
            test += (the_chars[0] - '0');

        text.push_back(test);
        
        
    }
    return text;
}

size_t decryption_xor()
{
    vector<unsigned char> text = text_file_chars();

    vector<unsigned char> tester = text;


    unsigned char key[3];
    size_t index = 0;
    bool breaker = false;
    for (unsigned char a = 0; a != 26; ++a)
    {
        for (unsigned char b = 0; b != 26; ++b)
        {
            for (unsigned char c = 0; c != 26; ++c)
            {
                key[0] = a + 'a';
                key[1] = b + 'a';
                key[2] = c + 'a';
                for (auto charit = tester.begin(); charit != tester.end(); ++charit)
                {
                    *charit ^= key[index];
                    if (++index == 3)
                    {
                        index = 0;
                    }
                }
                size_t hits = 0;
                for (size_t i = 0; i != tester.size()-3; ++i)
                {
                    if ((tester[i] == 't' || tester[i] == 'T') && tester[i + 1] == 'h'
                        && tester[i + 2] == 'e')
                    { 
                        ++hits;
                    }
                    if ((tester[i] == 'i' && tester[i + 1] == 's'))
                    {
                        ++hits;
                    }
                    if ((tester[i] == 'a' && tester[i + 1] == 'r' && 
                        tester[i + 2] == 'e'))
                    {
                        ++hits;
                    }
                    if (hits > 50)
                    {
                        cout << key[0] << key[1] << key[2] << "\n\n\n";
                        breaker = true;
                        break;
                    }
                }
                if (breaker)
                    break;
                tester = text;
            }
            if (breaker)
                break;
        }
        if (breaker)
            break;
    }
    size_t retsum = 0;
    for (const auto& ch : tester)
    {
        cout << ch;
        retsum += ch;
    }
    cout << "\n\n";
    return retsum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = decryption_xor();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}