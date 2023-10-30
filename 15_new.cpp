#pragma warning(disable : 4267)
#pragma warning(disable : 26451)
#include <vector>
#include <deque>
#include <iostream>
#include <cstddef>
#include <functional>
using std::cout;
using std::size_t;
using std::vector;

// this solution is entirely stolen from some guy on github


size_t lattice_paths(size_t dimension)
{
    size_t width = dimension;
    size_t height = dimension;
    vector<vector<size_t>> bob(dimension+1);
    for (auto& inner : bob)
        inner.resize(dimension+1, 0);
    std::deque<std::pair<int, int>> next;
    bob[width][height] = 1;
    next.push_back({width-1, height});
    next.push_back({width, height-1});

    while (!next.empty())
    {
        const auto& current = next.front();
        next.pop_front();

        size_t x = current.first;
        size_t y = current.second;

        if (bob[x][y] != 0)
            continue;

        size_t paths = 0;
        if (x < width)
            paths += bob[x+1][y];
        if (y < height)
            paths += bob[x][y+1];

        bob[x][y] = paths;

        if (x > 0)
            next.push_back({x-1, y});
        if (y > 0)
            next.push_back({x, y-1});
    }
    return bob[0][0];

}

int main()
{
    cout << lattice_paths(20);
}