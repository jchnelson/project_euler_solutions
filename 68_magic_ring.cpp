#include <cstddef>
#include <iostream>
#include <chrono>
#include <vector>
#include <set>

using std::cout;
using std::size_t;
using std::vector;

static size_t origsize = 0;
static size_t currsize = 0;
static size_t reqvec = 0;

static size_t max = 0;

size_t power(size_t n, size_t exp)
{
    size_t ret = 1;
    for (size_t i = 0; i != exp; ++i)
    {
        ret *= n;
    }
    return ret;
}


inline void add_digits(size_t& solut, size_t& digits, size_t bob)
{
    if (bob > 999)
        --digits;
    solut += bob * power(10, digits);
    digits -= 3;
}

void make_solut(const vector<unsigned char>& core,
    const vector<unsigned char>& outside)
{

    if (core[1] + core[0] + outside[0] != core[2] + core[1] + outside[1] ||
        core[2] + core[1] + outside[1] != core[3] + core[2] + outside[2] ||
        core[3] + core[2] + outside[2] != core[4] + core[3] + outside[3] ||
        core[4] + core[3] + outside[3] != core[0] + core[4] + outside[4] )

        return;

    size_t solut = 0;
    vector<size_t> soluts;
    soluts.reserve(5);

    solut += core[1];
    solut += core[0] * 10;
    solut += outside[0] * 100;
    soluts.push_back(solut);

    solut = 0;
    solut += core[2];
    solut += core[1] * 10;
    solut += outside[1] * 100;
    soluts.push_back(solut);

    solut = 0;
    solut += core[3];
    solut += core[2] * 10;
    solut += outside[2] * 100;
    soluts.push_back(solut);

    solut = 0;
    solut += core[4];
    solut += core[3] * 10;
    solut += outside[3] * 100;
    soluts.push_back(solut);

    solut = 0;
    solut += core[0];
    solut += core[4] * 10;
    solut += outside[4] * 100;
    soluts.push_back(solut);

    size_t min = 111111111111111;
    size_t min_index = 0;
    for (size_t i = 0; i != soluts.size(); ++i)
    {
        if (soluts[i] < min)
        {
            min = soluts[i];
            min_index = i;
        }
    }

    size_t digits = 13;

    solut = 0;
    for (size_t i = min_index; i != min_index + soluts.size(); ++i)
    {
        add_digits(solut, digits, soluts[i % 5]);
    }
    if (solut > max)
    {
        cout << solut << '\n';
        max = solut;
    }
}

void make_permut(const vector<unsigned char>& core, 
                 std::set<unsigned char>& avail)
{
    vector<unsigned char> outside(5);
    outside[0] = 6; // gotta be six for max solution
    for (unsigned char b = 1; b != 11; ++b)
    {
        if (avail.count(b) == 0)
            continue;
        outside[1] = b;
        avail.erase(b);

        for (unsigned char c = 1; c != 11; ++c)
        {

            if (avail.count(c) == 0)
                continue;
            outside[2] = c;
            avail.erase(c);

            for (unsigned char d = 1; d != 11; ++d)
            {

                if (avail.count(d) == 0)
                    continue;
                outside[3] = d;
                avail.erase(d);

                for (unsigned char e = 1; e != 11; ++e)
                {

                    if (avail.count(e) == 0)
                        continue;
                    outside[4] = e;
                    avail.erase(e);
                    make_solut(core,outside);
                    avail.insert(e);

                }
                avail.insert(d);
            }
            avail.insert(c);
        }
        avail.insert(b);
    }
    //avail.insert(a);
}




size_t fivegon()
{
    vector<unsigned char> core(5);

    std::set<unsigned char> avail = {1, 2, 3, 4, 5, 7, 8, 9};
    for (unsigned char a = 1; a != 10; ++a)
    {

        if (avail.count(a) == 0)
            continue;
        core[0] = a;
        avail.erase(a);
        for (unsigned char b = 1; b != 10; ++b)
        {

            if (avail.count(b) == 0)
                continue;
            core[1] = b;
            avail.erase(b);

            for (unsigned char c = 1; c != 10; ++c)
            {

                if (avail.count(c) == 0)
                    continue;
                core[2] = c;
                avail.erase(c);

                for (unsigned char d = 1; d != 10; ++d)
                { 

                    if (avail.count(d) == 0)
                        continue;
                    core[3] = d;
                    avail.erase(d);

                    for (unsigned char e = 1; e != 10; ++e)
                    {

                        if (avail.count(e) == 0)
                            continue;
                        core[4] = e;
                        avail.erase(e);
                        avail.insert(10); 

                        make_permut(core, avail);

                        avail.insert(e);
                        avail.erase(10);
                    }
                    avail.insert(d);
                }
                avail.insert(c);
            }
            avail.insert(b);
        }
        avail.insert(a);
    }
    return max;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = fivegon();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}