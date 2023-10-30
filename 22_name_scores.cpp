#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstddef>
#include <algorithm>

using std::size_t;
using std::cout;

int main()
{
    std::ifstream bob("names.txt");
    char nextname[100]{};
    char garbage[10]{};
    std::vector<std::string> names;
    names.reserve(5200);
    while (bob.getline(garbage, 10, '"')) // this get gets the garbage
    {
        bob.getline(nextname, 100, '"');
        names.push_back(nextname);
    }
    cout << names.size() << '\n';
    std::sort(names.begin(), names.end());

    size_t sum = 0;
    for (size_t i = 0; i != names.size(); ++i)
    {
        size_t namesum = 0;
        for (size_t j = 0; j != names[i].size(); ++j)
        {
            namesum += names[i][j] - 'A' + 1;
        }
        sum += namesum * (i + 1);
    }
    cout << sum;
}