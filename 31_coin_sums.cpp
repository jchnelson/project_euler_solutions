#include <set>
#include <iostream>
#include <cstddef>
#include <cmath>
#include <chrono>
#include <string>
#include <array>

using std::size_t;
using std::set;
using std::cout;

int reset_avail(const int& oner_, const int& fiftyp_, const int& twentyp_,
                const int& tenp_, const int& fivep_)
{
    return 200 - (oner_ * 100) - (fiftyp_ * 50) - (twentyp_ * 20) - (tenp_ * 10) - 
        (fivep_ * 5);
}
size_t coin_sums(int pounds)
{
    std::set<std::array<int, 8>> changes{
        {200, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 100, 0, 0, 0, 0, 0, 0},
        {0, 0, 40, 0, 0, 0, 0, 0},
        {0, 0, 0, 20, 0, 0, 0, 0},
        {0, 0, 0, 0, 10, 0, 0, 0},
        {0, 0, 0, 0, 0, 4, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 1}
    };

    int avail = pounds * 100;

    int oner_ = 0;
    int fiftyp_ = 0;
    int twentyp_ = 0;
    int tenp_ = 0;
    int fivep_ = 0;
    int twop_ = 0;
        
    for (int oner = 1; oner != -1; --oner)
    {
        avail += (oner_ * 100);
        oner_ = 0;
        if (avail - (oner * 100) > -1)
        {
            avail -= (oner * 100);
            oner_ = oner;
        }

        for (int fiftyp = 0; fiftyp != 6; ++fiftyp)
        {
            avail += (fiftyp_ * 50);
            fiftyp_ = 0;
            if (fiftyp * 50 > avail)
                break;
            if (avail - (fiftyp * 50) > -1)
            {
                avail -= (fiftyp * 50);
                fiftyp_ = fiftyp;
            }
                
            for (int twentyp = 0; twentyp != 12; ++twentyp)
            {
                avail += (twentyp_ * 20);
                twentyp_ = 0;
                if (twentyp * 20 > avail)
                    break;
                if (avail - (twentyp * 20) > -1)
                { 
                    avail -= (twentyp * 20);
                    twentyp_ = twentyp;
                }

                for (int tenp = 0; tenp != 22; ++tenp)
                {
                    avail += (tenp_ * 10);
                    tenp_ = 0;
                    if (tenp * 10 > avail)
                        break;
                    if (avail - (tenp * 10) > -1)
                    {
                        avail -= (tenp * 10);
                        tenp_ = tenp;
                    }
                    for (int fivep = 0; fivep != 42; ++fivep)
                    {
                        avail += (fivep_ * 5);
                        fivep_ = 0;
                        if (fivep * 5 > avail)
                            break;
                        if (avail - (fivep * 5) > -1)
                        { 
                            avail -= (fivep * 5);
                            fivep_ = fivep;
                        }
                        for (int twop = 0; twop != 102; ++twop)
                        {
                            twop_ = 0;
                            if (avail - (twop * 2) > -1)
                            { 
                                avail -= (twop * 2);
                                twop_ = twop;
                            }
                            changes.insert({
                                avail,twop_,fivep_,tenp_,
                                twentyp_,fiftyp_,oner_,0 });
                            avail = reset_avail(oner_, fiftyp_, twentyp_,
                                tenp_, fivep_);     
                            if (twop * 2 > avail)
                                break;
                        }
                    }
                }
            }
        }
    }
    return changes.size();
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = coin_sums();

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}