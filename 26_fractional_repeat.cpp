#include <iostream>
#include <chrono>
#include <cstddef>
#include <string>
#include <utility>

using std::size_t;
using std::cout;
using std::string;

bool check_pair_recur(const string& frac, const size_t& first, const size_t& second,
    const size_t& currnum, char currchar, 
    size_t& pattern_size, size_t& denominator)
{
    if (first != string::npos && second != string::npos &&
        first != second && ((first + (second - first)) <= frac.size()))
    {
        size_t count = second - first;
        if (frac.substr(first, count) == frac.substr(second, count) &&
            frac.substr(second, count) == frac.substr(second + count, count))
        {
            if (count > pattern_size)
            {
                pattern_size = count;
                denominator = currnum;
            }
            return true;
        }
        else
        {
            size_t next = frac.find(currchar, second + 1);
             if ( next != string::npos && check_pair_recur(frac, first, next, currnum, 
                currchar, pattern_size, denominator))
                 return true;
        }
    }
    return false;
}

bool check_pair(const string& frac, const size_t& first, const size_t& second,
    const size_t& currnum, size_t& pattern_size, size_t& denominator)
{

    size_t count = second - first;
    if (frac.substr(first, count) == frac.substr(second, count) &&
        frac.substr(second, count) == frac.substr(second + count, count))
    {
        if (count > pattern_size)
        {
            pattern_size = count;
            denominator = currnum;
        }
        return true;
    }
    return false;
}

std::pair<size_t, size_t> fractional_repeat(int limit)
{
    // find the largest repeating pattern in the
    //  decimal part of a fraction with 1 on top
    size_t pattern_size = 0;
    size_t denominator = 0;
    for (int i = 2; i != limit; ++i)
    {
        cout << i << '\n';
        std::string frac;
        int n = 10;
        while (n - i < 0)
            n *= 10;
        bool repeat_found = false;
        while (1)
        { 
            if (n % i == 0)
            {
                n /= i;
                frac.push_back(n + '0');
                break;
            }
            else 
            {
                int fracnum = 0;
                while (n - i > -1)
                {
                    n -= i;
                    ++fracnum;
                }
                frac.push_back(fracnum + '0');
                n *= 10;
            }
            for (char j = '0'; j != '0' + 10; ++j)
            {
                size_t first = frac.find(j);
                size_t second = frac.find(j, first +1);
                size_t third = frac.find(j, second + 1);
                size_t fourth = frac.find(j, third + 1);
                size_t fifth = frac.find(j, fourth + 1);
                size_t sixth = frac.find(j, fifth + 1);
                size_t seventh = frac.find(j, sixth + 1);

                // two instances of character found, and we have the same
                // amount of characters after each available to test
                if (first != string::npos && second != string::npos &&
                    third != string::npos && fourth != string::npos &&
                    ((fourth + (fourth - first)) <= frac.size()) )
                {
                    if (check_pair(frac, first, second, i, pattern_size,denominator))
                    {
                        repeat_found = true;
                        break;
                    }
                    else if
                        (check_pair(frac, first, third, i, pattern_size, denominator))
                    {
                        repeat_found = true;
                        break;
                    }
                    else if
                        (check_pair(frac, first, fourth, i, pattern_size, denominator))
                    {
                        repeat_found = true;
                        break;
                    }
                    else if 
                        (check_pair(frac, second, third, i, pattern_size, denominator))
                    {
                        repeat_found = true;
                        break;
                    }
                    else if
                        (check_pair(frac, second, fourth, i, pattern_size, denominator))
                    {
                        repeat_found = true;
                        break;
                    }
                
                    if (fifth != string::npos  &&
                        ((fifth + (fifth - first)) <= frac.size()))
                    {
                        if (check_pair(frac, first, 
                                fifth, i, pattern_size, denominator))
                        {
                            repeat_found = true;
                            break;
                        }
                        else if
                            (check_pair(frac, second, 
                                fifth, i, pattern_size, denominator))
                        {
                            repeat_found = true;
                            break;
                        }
                        else if
                            (check_pair(frac, third, 
                                fifth, i, pattern_size, denominator))
                        {
                            repeat_found = true;
                            break;
                        }

                        if (sixth != string::npos &&
                            ((sixth + (sixth - first)) <= frac.size()))
                        {
                            if (check_pair(frac, first,
                                sixth, i, pattern_size, denominator))
                            {
                                repeat_found = true;
                                break;
                            }
                            else if
                                (check_pair(frac, second,
                                    sixth, i, pattern_size, denominator))
                            {
                                repeat_found = true;
                                break;
                            }
                            else if
                                (check_pair(frac, third,
                                    sixth, i, pattern_size, denominator))
                            {
                                repeat_found = true;
                                break;
                            }
                            if (seventh != string::npos &&
                                ((seventh + (seventh - first)) <= frac.size()))
                            {
                                if (check_pair(frac, first,
                                    seventh, i, pattern_size, denominator))
                                {
                                    repeat_found = true;
                                    break;
                                }
                                else if
                                    (check_pair(frac, second,
                                        seventh, i, pattern_size, denominator))
                                {
                                    repeat_found = true;
                                    break;
                                }
                                else if
                                    (check_pair(frac, third,
                                        seventh, i, pattern_size, denominator))
                                {
                                    repeat_found = true;
                                    break;
                                }
                                else if
                                    (check_pair(frac, fourth,
                                        seventh, i, pattern_size, denominator))
                                {
                                    repeat_found = true;
                                    break;
                                }
                                if (frac.size() > 175)
                                {
                                    size_t eighth = frac.find(j, seventh + 1);
                                    size_t ninth = frac.find(j, eighth + 1);
                                    size_t tenth = frac.find(j, ninth + 1);
                                    size_t eleventh = frac.find(j, tenth + 1);
                                    size_t twelfth = frac.find(j, eleventh + 1);
                                    size_t thirteenth = frac.find(j, twelfth + 1);
                                    size_t fourteenth = frac.find(j, thirteenth + 1);
                                    if (eighth != string::npos && ninth != string::npos
                                        && tenth != string::npos &&
                                        ((tenth + (tenth - first)) <= frac.size()))
                                    { 
                                        if (check_pair(frac, first,
                                            eighth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                        else if
                                            (check_pair(frac, first,
                                                ninth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                        else if
                                            (check_pair(frac, first,
                                                tenth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                    }
                                    if (eleventh != string::npos && 
                                        twelfth != string::npos &&
                                        ((twelfth + (twelfth - first)) <= frac.size()))
                                    { 
                                        if
                                            (check_pair(frac, first,
                                                eleventh, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                        else if
                                            (check_pair(frac, first,
                                                twelfth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                    }
                                    if (thirteenth != string::npos && 
                                        fourteenth != string::npos &&
                                        ((fourteenth + (fourteenth - first)) 
                                            <= frac.size()))
                                    { 
                                        if
                                            (check_pair(frac, first,
                                                thirteenth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                        else if
                                            (check_pair(frac, first,
                                                fourteenth, i, pattern_size, denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                        if (frac.size() > 400 && 
                                            first != string::npos && 
                                            fourteenth != string::npos && 
                                            check_pair_recur(frac, first, 
                                                fourteenth, i, j, pattern_size, 
                                                denominator))
                                        {
                                            repeat_found = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (repeat_found)
                break;
        }

    }
    return { denominator, pattern_size };
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = fractional_repeat(1000);

    size_t denominator = bob.first;
    size_t pattern_size = bob.second;

    auto finish = std::chrono::high_resolution_clock::now();

    cout << denominator << " with pattern of " << pattern_size << " digits in " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

    // 506 seconds ... tried without the messy section, but I get 
    // a stack overflow when only using the recursive function.  There must be 
    // a better way to do this, but I'm leaving it like this for now.  
}
