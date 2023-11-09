#include <iostream>
#include <vector>
#include <deque>
#include <cstddef>
#include <utility>
#include <fstream>
#include <stdexcept>
#include <chrono>

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


vector<vector<unsigned>> text_file_chars()
{
    std::basic_ifstream<unsigned char> bob("triangle.txt");
    vector<vector<unsigned>> text;
    text.reserve(100);
    unsigned char the_chars[3];
    bool end_of_file = false;
    while (bob)
    {
        vector<unsigned> line;
        line.reserve(100);
        while (bob.get(the_chars, 3))
        {
            size_t count = bob.gcount();
            unsigned test = 0;
            test += ((the_chars[0] - '0') * 10) + (the_chars[1] - '0');

            line.push_back(test);

            long next = char(bob.get()); // get space or newline, if space do nothing
            if (next == '\n')
                break;
        }
        text.push_back(line);
    }
    if (text.back().empty())
        text.pop_back();
    return text;
}


std::pair<unsigned, deque<std::pair<unsigned, unsigned>>>
triangle_path_sum(vector<vector<unsigned>> triangle)
{
    unsigned sz = unsigned(triangle.size());
    path_index points(sz);

    for (int i = 0; i != triangle.size(); ++i)
    {
        points[i].resize(triangle[i].size(), { {0, {{0,0}}}, {0, {{0,0}}} });
    }

    std::deque<std::pair<unsigned, unsigned>> next;
    for (int y = 0; y != sz; ++y)
    {
        points[sz - 1][y] = { {triangle[sz - 1][y], {{sz - 1, y}}},
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
                        pathpoint.second.push_front({ x - 1, y - 1 });
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
    auto start = std::chrono::high_resolution_clock::now();
    vector<vector<unsigned>> triangle = text_file_chars();

    auto bob = triangle_path_sum(triangle);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob.first << '\n';
    for (const auto& par : bob.second)
        cout << '(' << par.first << ", " << par.second << ')' << '\n';

    cout << "operation took " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}