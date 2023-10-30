#pragma warning(disable : 26451) // it's a char minus a char?!?
#include <cstddef>
#include <iostream>
#include <set>
#include <cmath>
#include <string>

// list all multiples of three or 5 under 1000 and return their sum

using std::size_t;
using std::cout;

template <typename...other>
int sum_multiples(unsigned top, other...rest)
{
    std:: set<int> mults;
    int bob[] = { rest... };
    int numbob = sizeof...(other);
    for (int i = 0; i != numbob; ++i)
        for (int j = 1; j != top; ++j)
            if (j % bob[i] == 0)
                mults.insert(j);
    int ret = 0;
    for (const int& mult : mults)
        ret += mult;
    return ret;
}

int even_fibs(int limit)
{
    std::set<int> fibs;
    int last = 0;
    int a = 0;
    int b = 1;
    int sum = 0;
    while (last < limit)
    {
        last = a + b;
        a = b;
        b = last;
        if (last % 2 == 0)
            sum += last;
    }
    return sum;
}

bool prime(size_t i)
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

size_t largest_prime_factor(size_t beeg)
{
    if (prime(beeg)) // check if original is prime first
        return 1;
    std::set<size_t> factors;
    size_t max = beeg;
    bool newmax = false;
    for (size_t i = 2; i <= max; ++i)
    {

        bool is_prime = true;
        for (size_t j = 2; j <= max/2; ++j)
        {
            if (i % j == 0)
            { 
                while (max % j == 0 && max != j)
                { 
                    max /= j;
                    newmax = true;
                }
                if (newmax)
                {
                    if (prime(max))
                        return max;
                    else
                        newmax = false;
                }
                if (i != j)
                    is_prime = false;
                break;
            }
        }
        if (is_prime)
        { 
            if (beeg % i == 0)
                factors.insert(i);

        }
    }
    return *(--factors.end());

}

int largest_palindrome(int digits = 3)
{
    // find number between 10,000 and 998,001
    // that is a palindrome.  

    int minimum = std::stoi(std::string("1") + std::string((digits - 1),'0'));
    minimum *= minimum;
    int maximum = std::stoi(std::string(digits, '9'));
    maximum *= maximum;

    for (int i = maximum; i != minimum; --i)
    {
        std::string i_string = std::to_string(i);
        bool is_palindrome = true;
        if (i_string.size() % 2 == 0)
        {
            for (int j = 0; j != i_string.size() / 2; ++j)
            { 
                if (i_string[j] != i_string[(i_string.size()-1) - j])
                    is_palindrome = false;
            }
        }
        else
        {
            for (int j = 0; j != std::ceil(i_string.size() / 2); ++j)
            {
                if (i_string[j] != i_string[(i_string.size() - 1) - j])
                    is_palindrome = false;
            }
        }
        if (is_palindrome)
            return i;
    }
    return -1; // some number should have qualified before this
    
}

size_t smallest_all_divisible(size_t a, size_t b)
{
    if (a == b)
        return a;
    size_t min = a < b ? a : b;
    size_t max = a < b ? b : a;
    size_t ret = max;
    while (1)
    {
        bool is_divisible = true;
        for (size_t i = min; i <= max; ++i)
        {
            if (ret % i != 0)
            {
                is_divisible = false;
                break;
            }
        }
        if (is_divisible)
            return ret;
        else
        { 
            ++ret;
        }        
    }
    return 0;
}

size_t square_sum_diff(int min, int max)
{
    // subtract the sum of squares from the square of the sums

    size_t square_sum = 0;
    size_t normal_sum = 0;
    for (int i = min; i <= max; ++i)
    { 
        square_sum += (i*i);
        normal_sum += i;
    }
    normal_sum *= normal_sum;

    return normal_sum - square_sum;
}

size_t find_nth_prime(int x)
{
    int i = 0;
    size_t ret = 1; 
    while (i != x)
    {
        ++ret;
        if (prime(ret))
        {
            ++i;
        }
    }
    return ret;
}

size_t largest_thirteen(std::string beeg)
{
    // find the adjacent thirteen digits with the largest product
    size_t product = 0;
    size_t ret_index = 0;
    for (size_t index = 0; index != beeg.size() - 12; ++index)
    {
        size_t round = size_t((beeg[index] - '0')) * (beeg[index + 1] - '0') * 
            (beeg[index + 2] - '0') * (beeg[index + 3] - '0') * 
            (beeg[index + 4] - '0') * (beeg[index + 5] - '0') *
            (beeg[index + 6] - '0') * (beeg[index + 7] - '0') *
            (beeg[index + 8] - '0') * (beeg[index + 9] - '0') *
            (beeg[index + 10] - '0') * (beeg[index + 11] - '0') *
            (beeg[index + 12] - '0');
        if (round > product)
        {
            product = round;
            ret_index = index;
        }
    }

    cout << product << '\n';
    cout << beeg.substr(ret_index, 13) << '\n';
    return ret_index;
}

int main()
{
    //cout << sum_multiples(100, 6, 5) << '\n';

    //cout << even_fibs(4000000) << '\n';

    cout << largest_prime_factor(32124687463) << '\n';

    //cout << largest_palindrome(4);

    //cout << smallest_all_divisible(1,23);

    //cout << square_sum_diff(1,10);

    cout << find_nth_prime(200000);

    std::string thousand = 
        "73167176531330624919225119674426574742355349194934"
        "96983520312774506326239578318016984801869478851843"
        "85861560789112949495459501737958331952853208805511"
        "12540698747158523863050715693290963295227443043557"
        "66896648950445244523161731856403098711121722383113"
        "62229893423380308135336276614282806444486645238749"
        "30358907296290491560440772390713810515859307960866"
        "70172427121883998797908792274921901699720888093776"
        "65727333001053367881220235421809751254540594752243"
        "52584907711670556013604839586446706324415722155397"
        "53697817977846174064955149290862569321978468622482"
        "83972241375657056057490261407972968652414535100474"
        "82166370484403199890008895243450658541227588666881"
        "16427171479924442928230863465674813919123162824586"
        "17866458359124566529476545682848912883142607690042"
        "24219022671055626321111109370544217506941658960408"
        "07198403850962455444362981230987879927244284909188"
        "84580156166097919133875499200524063689912560717606"
        "05886116467109405077541002256983155200055935729725"
        "71636269561882670428252483600823257530420752963450";

    //cout << largest_thirteen(thousand);
}