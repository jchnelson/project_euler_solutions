#include <chrono>
#include <iostream>
#include <cstddef>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using std::cout;
using std::sqrt;
using std::abs;
using std::size_t;
using std::string;
using std::vector;

bool is_prime(long long i)
{
    if (i == 0 || i == 1 || i == -1)
        return false;

    long long max = long long(sqrt(abs(i)));
    for (long long j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            return false;
        }
    }
    return true;
}

size_t consec_prime_sum(size_t limit)
{
    int sum = 0;
    int consec = 0;
    int curr_consec = 0;
    int sum_of_most = 0;
    for (int i = 2;; ++i)
    {

        if (is_prime(i))
        { 
            sum += i;
            ++curr_consec;
        }
        if (sum >= limit)
        {
            sum -= i;
            --curr_consec;
            break;
        }
        if (is_prime(sum) && curr_consec > consec)
        { 
            consec = curr_consec;
            sum_of_most = sum;
        }
    }
    for (int i = 2; sum > 0; ++i)
    {
        if (is_prime(i))
        { 
            sum -= i;
            --curr_consec;
        }
        if (is_prime(sum) && curr_consec > consec)
        { 
            consec = curr_consec;
            sum_of_most = sum;
        }
    }
    return sum_of_most;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = consec_prime_sum(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << std::boolalpha << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}