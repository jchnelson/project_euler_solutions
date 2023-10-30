#include <iostream>
#include <vector>
#include <deque>
#include <cstddef>
#include <utility>

using std::size_t;
using std::cout;
using std::vector;
using std::deque;
using std::string;

 using path_index = 
     vector<  // x coord
      vector< // y coord
       std::pair< // l path, r path
        std::pair<unsigned, deque<std::pair<unsigned, unsigned>>>, // l sum and path
    std::pair<unsigned, deque<std::pair<unsigned, unsigned>>>  // r sum and path
     >>>;

std::pair<unsigned, deque<std::pair<unsigned, unsigned>>>
triangle_path_sum(vector<vector<unsigned>> triangle)
{
    unsigned sz = triangle.size();
    path_index points(sz);

    for (int i = 0; i != triangle.size(); ++i)
    {
        points[i].resize(triangle[i].size(),  { {0, {{0,0}}}, {0, {{0,0}}} }  );
    }

    std::deque<std::pair<unsigned, unsigned>> next;
    for (int y = 0; y != sz; ++y)
    { 
        points[sz-1][y] = { {triangle[sz - 1][y], {{sz - 1, y}}}, 
                            {0, {{0, 0}}} };     
    }
    for (int currrow = (sz - 1); currrow != 0; --currrow)
    {
        unsigned max_y = sz - (sz - (currrow + 1));
        for (int currcol = 0; currcol != max_y; ++currcol)
        {
            next.push_back({ currrow, currcol });
        }
        while (!next.empty())
        {
            auto current = next.front();
            next.pop_front();

            unsigned x = current.first;
            unsigned y = current.second;

            // the largest sum and its path from this point so far
            auto max_path = points[x][y].first.first > points[x][y].second.first ?
                points[x][y].first : points[x][y].second;

            unsigned sum = 0;
            if (x > 0) // we can still go up
            {
                if (y > 0) // go left since we're not on the left edge. we are the
                    // point to the RIGHT for this point we're moving to
                {
                    auto& pathpoint = points[x - 1][y - 1].second; // second is right
                    unsigned newsum = triangle[x - 1][y - 1] + max_path.first;
                    if (newsum > pathpoint.first)
                    {
                        pathpoint = max_path;
                        pathpoint.first = newsum;
                        pathpoint.second.push_front({x-1, y-1});
                    }
                }
                if (y < (max_y - 1)) // go right since we're not on the right edge.
                    // we are the point to the LEFT for this point
                {
                    auto& pathpoint = points[x - 1][y].first; // first is left
                    unsigned newsum = triangle[x - 1][y] + max_path.first;
                    if (newsum > pathpoint.first)
                    {
                        pathpoint = max_path;
                        pathpoint.first = newsum;
                        pathpoint.second.push_front({ x - 1, y });
                    }
                }
            }
        }
    }
    auto final_max_path = points[0][0].first.first > points[0][0].second.first ?
        points[0][0].first : points[0][0].second;
    return final_max_path;
}

int main()
{
    vector<vector<unsigned>> triangle{
                                    {75},
                                  {95, 64},
                                {17, 47, 82},
                              {18, 35, 87, 10},
                            {20,  4, 82, 47, 65},
                          {19,  1, 23, 75,  3, 34},
                        {88,  2, 77, 73,  7, 63, 67},
                      {99, 65,  4, 28,  6, 16, 70, 92},
                    {41, 41, 26, 56, 83, 40, 80, 70, 33},
                  {41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
                {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
              {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
            {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
          {63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
        {04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23}
    };
    auto bob = triangle_path_sum(triangle);
    cout << bob.first << '\n';
    for (const auto& par : bob.second)
        cout << '(' << par.first << ", " << par.second << ')' << '\n';
}
