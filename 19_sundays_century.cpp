#include <string>
#include <map>
#include <iostream>

using std::cout;

int sundays_in(int start, int end)
{
    std::map<int, int> months = {
        {0, 3}, {2,3}, {3, 2}, {4, 3}, {5, 2},
        {6, 3}, {7, 3}, {8, 2}, {9, 3}, {10, 2}, {11, 3}
    };
    // 1 Jan 1900 monday.
    end += 1; // include end year;

    int year = start; // 1901
    int month = 0; // january
    int day = 2; // tuesday
    int sunday_firsts = 0;
    while (year != end)
    {
        bool is_leap = year % 4 == 0 
            ? (year % 100 == 0 ? (year % 400 == 0 ? true : false) : true) : false;
        while (month != 12)
        {
            if (month != 1)
            {
                day = (day + months.at(month)) % 7;
            }
            else if (is_leap)
            {
                day = ((day + 1) % 7);
            }
            if (day == 0)
                ++sunday_firsts;
            ++month;
        }
        month = 0;
        ++year;
    }
    return sunday_firsts;
}




int main()
{
    cout << sundays_in(1901, 2000);
}