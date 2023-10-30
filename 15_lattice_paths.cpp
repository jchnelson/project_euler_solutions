#include <cstddef>
#include <set>
#include <vector>
#include <iostream>
#include <functional>
#include <chrono>

using std::size_t;
using std::cout;

using pathset = std::set<std::vector<std::pair<int, int>>>;
using path = std::vector<std::pair<int, int>>;
using pos = std::pair<int,int>;

static bool breaker = false;

bool all_paths_y(pathset& paths, path p, int ix, int iy, int dimension);

bool all_paths_x(pathset& paths, path p, int ix, int iy, int dimension)
{

    for (int x = ix; x <= dimension; ++x)
    {
        for (int y = iy; y <= dimension; ++y)
        {
            if ((x == p.back().first && y == p.back().second + 1)
                || x == p.back().first + 1 && y == p.back().second)
            {
                p.push_back({ x,y });
                //all_paths_x(paths, p, ix, iy, dimension);
                all_paths_y(paths, p, ix, iy, dimension);
            }
        }
    }
    auto ret = paths.insert(p);
    return ret.second;
    
}

bool all_paths_y(pathset& paths, path p, int ix, int iy,  int dimension)
{

    for (int y = iy; y <= dimension; ++y)
    {
        for (int x = ix; x <= dimension; ++x)
        {
            if ((x == p.back().first && y == p.back().second + 1)
                || x == p.back().first + 1 && y == p.back().second)
            {
                p.push_back({ x,y });
                all_paths_x(paths, p, ix, iy, dimension);
                //all_paths_y(paths, p, ix, iy, dimension);

            }
        }
    }
    auto ret = paths.insert(p);
    return ret.second;

}



size_t lattice_paths(int dimension)
{
    std::set<std::vector<std::pair<int,int>>> paths;
    // for a 20x20, there are 21 positions by 21 positions for the cursor to be at
    // only to the right and down
    // feels like a job for recursion

    // make a move, check all possible moves
    // 0,0 0,1 0,2, 1,2, 2,2
    // final position is dimension, dimension


    path p{ {0,0} };
    for (int x = 0; x <= dimension; ++x)
    {
        for (int y = 0; y <= dimension; ++y)
        {
            if ((x == p.back().first && y == p.back().second + 1)
                || (x == p.back().first + 1 && y == p.back().second))
            {
                p.push_back({x,y});
                all_paths_x(paths, p, x, y, dimension);
                all_paths_y(paths, p, x, y, dimension);
                p.pop_back();
            }
            //if ((y == p.back().first && x == p.back().second + 1)
            //    || (y == p.back().first + 1 && x == p.back().second))
            //{
            //    p.push_back({ y, x });
            //    if (p.back().first == dimension && p.back().second == dimension)
            //    {
            //        paths.insert(p);
            //        break;
            //    }
            //    all_paths_x(paths, p, dimension);
            //    all_paths_y(paths, p, dimension);
            //    p.pop_back();
            //}
        }
    }

  /*  for (const auto& one : paths)
    { 
        for (const auto& p : one)
        {
            cout << '(' << p.first << ',' << p.second << ')' << " ";
        }
        cout << '\n';
    }*/

    return paths.size();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    cout << lattice_paths(6) << '\n';
    auto finish = std::chrono::high_resolution_clock::now();
    cout << "Function took " << 
        std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);
}