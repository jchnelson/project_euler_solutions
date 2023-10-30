#include <iostream>
#include <cmath>
#include <array>

using std::cout;


int special_pythag()
{
    // only one a2 + b2 = c2 where a + b + c = 1000
    // find a * b * c

    int a, b, c;
    bool breaker = false;
    for (c = 1000; c != 0; --c)
    {
        for (a = 1; a != 1000; ++a)
        {
            for (b = 1; b != 1000; ++b)
            {
                if ((((a * a) + (b * b)) == (c * c)) && ((a + b + c) == 1000) )
                { 
                    breaker = true;
                    break;
                }
            }
            if (breaker)
                break;
        }
        if (breaker)
            break;
    }
    cout << a << ' ' << b << ' ' << c << '\n';
    return a * b * c;
}

bool is_prime(size_t i)
{
    int max = int(sqrt(i));
    for (size_t j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            return false;
        }
    }
    return true;
}

size_t sum_of_primes(size_t max)
{
    size_t ret = 0;
    for (int i = 2; i != max; ++i)
    { 
        if (is_prime(i))
        {
            ret += i;
        }
    }
    return ret;
}

size_t grid_product(std::array<std::array<int, 20>, 20> grid)
{
    // find the largest four adjacent numbers' product
    size_t retprod = 0;
    int index[2]{};
    std::string dir;
    for (size_t j = 0; j != 20; ++j)
    {
        for (size_t i = 0; i != 17; ++i)
        {
            size_t product = size_t(grid[j][i]) * grid[j][i+1] * 
                grid[j][i+2] * grid[j][i+3];
            if (product > retprod)
            {
                retprod = product;
                index[0] = j;
                index[1] = i;
                dir = "to the right";
            }
        }
    }
    for (size_t j = 0; j != 17; ++j)
    {
        for (size_t i = 0; i != 20; ++i)
        {
            size_t product = size_t(grid[j][i]) * grid[j+1][i] *
                grid[j+2][i] * grid[j+3][i];
            if (product > retprod)
            {
                retprod = product;
                index[0] = j;
                index[1] = i;
                dir = "down";
            }
        }
    }

    // ugh it's minesweeper again

    for (size_t j = 0; j != 20; ++j)
    {
        for (size_t i = 0; i != 20; ++i)
        {
            if (i + 3 > 19 || j + 3 > 19) 
                continue;
            size_t product = size_t(grid[j][i]) * grid[j + 1][i + 1] *
                grid[j + 2][i + 2] * grid[j + 3][i + 3];
            if (product > retprod)
            {
                retprod = product;
                index[0] = j;
                index[1] = i;
                dir = "diagonally down and to the right";
            }
        }
    }

    for (int j = 0; j != 20; ++j)
    {
        for (int i = 0; i != 20; ++i)
        {
            if (i - 3 < 0 || j + 3 > 19)
                continue;
            size_t product = size_t(grid[j][i]) * grid[j + 1][i - 1] *
                grid[j + 2][i - 2] * grid[j + 3][i - 3];
            if (product > retprod)
            {
                retprod = product;
                index[0] = j;
                index[1] = i;
                dir = "diagonally down and to the left";
            }
        }
    }
    cout << index[0] << "," << index[1] << ' ' << dir << '\n';
    return retprod;
}

int main()
{
    // cout << special_pythag();

    std::array<std::array<int, 20>, 20> grid{{
        { 8, 2,22,97,38,15, 0,40, 0,75, 4, 5, 7,78,52,12,50,77,91, 8},
        {49,49,99,40,17,81,18,57,60,87,17,40,98,43,69,48, 4,56,62, 0},
        {81,49,31,73,55,79,14,29,93,71,40,67,53,88,30, 3,49,13,36,65}, 
        {52,70,95,23, 4,60,11,42,69,24,68,56, 1,32,56,71,37, 2,36,91},
        {22,31,16,71,51,67,63,89,41,92,36,54,22,40,40,28,66,33,13,80},
        {24,47,32,60,99, 3,45, 2,44,75,33,53,78,36,84,20,35,17,12,50},
        {32,98,81,28,64,23,67,10,26,38,40,67,59,54,70,66,18,38,64,70},
        {67,26,20,68, 2,62,12,20,95,63,94,39,63, 8,40,91,66,49,94,21},
        {24,55,58, 5,66,73,99,26,97,17,78,78,96,83,14,88,34,89,63,72},
        {21,36,23, 9,75, 0,76,44,20,45,35,14, 0,61,33,97,34,31,33,95},
        {78,17,53,28,22,75,31,67,15,94, 3,80, 4,62,16,14, 9,53,56,92},
        {16,39, 5,42,96,35,31,47,55,58,88,24, 0,17,54,24,36,29,85,57},
        {86,56, 0,48,35,71,89, 7, 5,44,44,37,44,60,21,58,51,54,17,58},
        {19,80,81,68, 5,94,47,69,28,73,92,13,86,52,17,77, 4,89,55,40},
        {04,52, 8,83,97,35,99,16, 7,97,57,32,16,26,26,79,33,27,98,66},
        {88,36,68,87,57,62,20,72, 3,46,33,67,46,55,12,32,63,93,53,69},
        {04,42,16,73,38,25,39,11,24,94,72,18, 8,46,29,32,40,62,76,36},
        {20,69,36,41,72,30,23,88,34,62,99,69,82,67,59,85,74, 4,36,16},
        {20,73,35,29,78,31,90, 1,74,31,49,71,48,86,81,16,23,57, 5,54},
        {01,70,54,71,83,51,54,69,16,92,33,48,61,43,52, 1,89,19,67,48}
        }};

    // cout << sum_of_primes(2000000);

    cout << grid_product(grid);
}