#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::sqrt;

using digits = std::pair<vector<size_t>, vector<size_t>>;

static size_t base_n = 0;
static bool same_size = true;
static bool first_big = false;
static size_t expander = 0;
static size_t starter = 0;
static bool first_bigvalue = true;

size_t power(size_t n, size_t exp)
{
    size_t ret = 1;
    for (size_t i = 0; i != exp; ++i)
    {
        ret *= n;
    }
    return ret;
}

std::pair<size_t, size_t> imed_sum_single(digits& biggies, size_t j, size_t origcarry)
{
    size_t sum = origcarry;
    size_t carry = 0;
    for (size_t i = 0; i != base_n; ++i)
    {
        sum += biggies.second[j];
    }
    size_t num_digits = 0;
    if (sum > 1000000000000000)
    {
        size_t working = sum;
        working /= 1000000000000000;
        ++num_digits;
        carry = working % 10;

        while (working >= 10)
        {
            working /= 10;
            carry += (working % 10) * power(10, num_digits);
            ++num_digits;
        }
    }
    else if (sum == 1000000000000000)
    {
        carry = 1;
        sum = 0;
    }
    sum %= 1000000000000000;
    return { sum, carry };
}

std::pair<size_t, size_t> imed_sum_dual(digits& biggies, size_t j, size_t origcarry)
{
    size_t sum = origcarry;
    size_t carry = 0;
    sum += biggies.first[j] + biggies.second[j];
    size_t num_digits = 0;
    if (sum >= 1000000000000000)
    {
        size_t working = sum;
        working /= 1000000000000000;
        carry = working % 10;
        ++num_digits;
        while (working >= 10)
        {
            working /= 10;
            carry += (working % 10) * power(10, num_digits);
            ++num_digits;
        }
    }
    sum %= 1000000000000000;
    return { sum, carry };
}

void dual(digits& biggies)
{
    vector<size_t> bigworking;
    bigworking.reserve(biggies.second.size() + 2);
    size_t carry = 0;
    same_size = biggies.second.size() == biggies.first.size();
    first_big = biggies.second.size() < biggies.first.size();
    size_t sz = first_big ? biggies.first.size() : biggies.second.size();
    size_t sizegap = same_size ? 0 : first_big ? biggies.first.size() -
        biggies.second.size() : biggies.second.size() - biggies.first.size();
    if (same_size)
    {
        for (int i = 0; i != sz; ++i)
        {
            std::pair<size_t, size_t> inter = imed_sum_dual(biggies, i, carry);
            bigworking.push_back(inter.first);
            carry = inter.second;
        }
        if (carry != 0)
        {
            bigworking.push_back(carry);
        }
    }
    else
    {
        for (int i = 0; i != sz - sizegap; ++i)
        {
            std::pair<size_t, size_t>
                inter = imed_sum_dual(biggies, i, carry);

            bigworking.push_back(inter.first);
            carry = inter.second;
        }
        
        if (first_big)
        {
            for (auto it = biggies.first.end() - sizegap; it != biggies.first.end(); ++it)
                bigworking.push_back(*it);
        }
        else
        {
            for (auto it = biggies.second.end() - sizegap; it != biggies.second.end(); ++it)
                bigworking.push_back(*it);
        }
        *(bigworking.end() - sizegap) += carry;
    }
    biggies.first = bigworking;
}

void single(digits& biggies)
{
    vector<size_t> bigworking;
    bigworking.reserve(biggies.second.size() + 2);
    size_t carry = 0;
    size_t sz = biggies.second.size();
    for (int i = 0; i != sz; ++i)
    {
        std::pair<size_t, size_t> inter = imed_sum_single(biggies, i, carry);
        bigworking.push_back(inter.first);
        carry = inter.second;
    }
    if (carry != 0)
    {
        bigworking.push_back(carry);
    }
    biggies.second = bigworking;
}

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

bool is_square(size_t n)
{
    if (n == 0 || n == 1)
        return true;
    size_t x = 0;
    for (size_t i = 1; n > x; ++i)
    {
        x = i * i;
        if (n == x)
            return true;
    }
    return false;
}

size_t next_expansion(bool reset = false)
{
    static size_t m = 0;
    static size_t d = 1;
    size_t a0 = size_t(sqrt(expander));
    static size_t a = a0;
    static size_t nm = 0;
    static size_t nd = 0;
    static size_t na = 0;
    if (reset)
    {
        m = 0;
        d = 1;
        a = a0;
        nm = 0;
        nd = 0;
        na = 0;
        return a0;
    }

    nm = d * a - m;
    nd = size_t(double(expander - (nm * nm)) / d);
    na = (a0 + nm) / nd; // floor after division

    m = nm;
    d = nd;
    a = na;

    return a;
}

vector<size_t> next_convergent(size_t i = expander)
{
    bool firstround = expander != i;
    expander = i;
    digits working;

    working.first.reserve(20);
    working.second.reserve(20);
    
    static vector<size_t> prevtop;
    static vector<size_t> prevbot;
    static vector<size_t> currtop;
    static vector<size_t> currbot;
    static vector<size_t> temptop;
    static vector<size_t> tempbot;

    prevtop.reserve(20);
    prevbot.reserve(20);
    currtop.reserve(20);
    currbot.reserve(20);
    temptop.reserve(20);
    tempbot.reserve(20);
    size_t biground = 0;

    if (firstround)
    {
        starter = next_expansion(true);
        prevtop.clear();
        prevbot.clear();
        currtop.clear();
        currbot.clear();
        temptop.clear();
        tempbot.clear();
        prevtop.push_back(starter);
        prevbot.push_back(1);
        biground = next_expansion();
        if (biground == 1)
        {
            currtop.push_back(starter+1);
            currbot.push_back(1);
        }
        else
        {
            currtop.push_back(starter * biground + 1);
            currbot.push_back(biground);
        }
        return currtop;
    }
    biground = next_expansion();
    temptop = currtop;
    tempbot = currbot;

    if (biground != 1)
    {
        base_n = biground;
        working.second = temptop;
        single(working);
        working.first = prevtop;
        dual(working);
        currtop = working.first;

        working.second = tempbot;
        single(working);
        working.first = prevbot;
        dual(working);
        currbot = working.first;
    }
    else
    {
        working.first = currtop;
        working.second = prevtop;
        dual(working);
        currtop = working.first;

        working.first = currbot;
        working.second = prevbot;
        dual(working);
        currbot = working.second;
    }
    prevtop = temptop;
    prevbot = tempbot;
    
    return currtop;
}

size_t count_digits(size_t n)
{
    size_t digits = 0;
    size_t working = n;
    while (working > 0)
    {
        ++digits;
        working /= 10;
    }
    return digits;
}

vector<size_t> big_exp(size_t base, size_t exp)
{
    if (exp == 0)
    {
        return {1};
    }
    if (exp == 1)
    {
        return {base};
    }
    base_n = base;
    
    digits biggies;
    biggies.first.reserve(exp + base);
    biggies.second.reserve(exp + base);
    biggies.second.push_back(base_n);
    for (size_t j = 1; j != exp; ++j)
    {
        single(biggies);
    }
    return biggies.second;
}

std::pair<size_t, bool> imed_diff_dual(digits& biggies, size_t j)
{
    size_t diff = 0;
    bool borrow = false;
    size_t n_digits_first = count_digits(biggies.first[j]);
    size_t n_digits_second = count_digits(biggies.second[j]);

    if ((n_digits_first == n_digits_second && biggies.first[j] < biggies.second[j]
        && biggies.first[j] / power(10, n_digits_first - 1) % 10 <=
        biggies.second[j] / power(10, n_digits_first - 1) % 10) ||
        n_digits_first < n_digits_second)
    {
        biggies.first[j] += power(10, 15);
        borrow = true;
    }
    diff = biggies.first[j] - biggies.second[j];

    return { diff, borrow };
}

int compare_blocks(digits& biggies)
{
    size_t sz = biggies.first.size();
    for (int i = int(sz - 1); i > -1; --i)
    {
        if (biggies.first[i] > biggies.second[i])
            return 1;
        else if (biggies.first[i] < biggies.second[i])
            return -1;
    }
    return 0;
}

bool dual_diff(digits& biggiesorig)
{
    digits biggies;
    vector<size_t> bigworking;
    size_t first_sz = biggiesorig.first.size();
    size_t second_sz = biggiesorig.second.size();
    same_size = second_sz == first_sz;
    first_big = second_sz < first_sz;
    int value_compare = -2;
    if (same_size)
        value_compare = compare_blocks(biggiesorig);

    if (value_compare == 0)
    {
        biggiesorig.first = { 0 };
        return false;
    }
    first_bigvalue = !same_size ? first_big ? true : false :
        value_compare > 0 ? true : false;
    bool negate_final = first_bigvalue ? false : true;
    size_t sz = first_big ? first_sz : second_sz;
    bigworking.reserve(sz + 2);
    size_t sizegap = same_size ? 0 : first_big ? first_sz -
        second_sz : second_sz - first_sz;
    if (first_bigvalue)
    {
        biggies.first = biggiesorig.first;
        biggies.second = biggiesorig.second;
    }
    else
    {
        biggies.first = biggiesorig.second;
        biggies.second = biggiesorig.first;
    }

    if (same_size)
    {

        for (int i = 0; i != sz; ++i)
        {
            std::pair<size_t, bool> inter = imed_diff_dual(biggies, i);
            bigworking.push_back(inter.first);
            if (inter.second)
            {
                // a borrow shouldn't happen on the last round
                if (i == sz - 1)
                    throw std::runtime_error("This shouldn't be possible");
                biggies.first[i + 1] -= 1;
            }
        }
    }
    else
    {
        for (int i = 0; i != sz - sizegap; ++i)
        {
            std::pair<size_t, size_t>
                inter = imed_diff_dual(biggies, i);

            bigworking.push_back(inter.first);
            if (inter.second)
            {
                biggies.first[i + 1] -= 1;
            }
        }
        for (size_t i = sz - sizegap; i != sz; ++i)
        {
            bigworking.push_back(biggies.first[i]);
        }
    }
    while (bigworking.back() == 0)
        bigworking.pop_back();

    biggiesorig.first = bigworking;

    return negate_final;
}

vector<size_t> big_square(vector<size_t> xvec)
{
    size_t sz = xvec.size();

    digits working;
    working.first.reserve(sz + 2);
    working.second.reserve(sz + 2);

    base_n = 2;
    working.second = xvec;
    working.first = xvec;

    digits pretend;
    pretend.first.reserve(sz + 2);
    pretend.second.reserve(sz + 2);

    pretend.first = xvec;
    pretend.second = { 1 };

    vector<vector<size_t>> multiples;
    multiples.reserve(200);
    multiples.push_back(xvec);

    vector<vector<size_t>> pmultiples;
    pmultiples.reserve(200);
    pmultiples.push_back({ 1 });
    while (1)
    {
        single(working);
        single(pretend);
        if (pretend.second.size() < pretend.first.size() || (pretend.second.size() ==
            pretend.first.size() && pretend.second.back() < pretend.first.back()))
        {
            multiples.push_back(working.second);
            pmultiples.push_back(pretend.second);
        }
        else break;
    }
    vector<size_t> two_powers;
    while (!multiples.empty())
    {
        working.second = multiples.back();
        pretend.second = pmultiples.back();
        while (pretend.first.size() > pretend.second.size() || (pretend.first.size() ==
            pretend.second.size() && pretend.first.back() > pretend.second.back()))
        {
            dual(working);
            dual_diff(pretend);
            two_powers.push_back(multiples.size() - 1);
        }
        multiples.pop_back();
        pmultiples.pop_back();
    }
    return working.first;
}

std::pair<vector<size_t>, size_t> big_division(digits& biggiesorig)
{
    size_t first_sz = biggiesorig.first.size();
    size_t second_sz = biggiesorig.second.size();
    same_size = second_sz == first_sz;
    first_big = second_sz < first_sz;
    first_bigvalue = same_size ? biggiesorig.first.back() >
        biggiesorig.second.back() : first_big ? true : false;
    size_t sz = first_big ? first_sz : second_sz;
    size_t sizegap = same_size ? 0 : first_big ? first_sz -
        second_sz : second_sz - first_sz;
    size_t n_digits_first = count_digits(biggiesorig.first.back());
    size_t n_digits_second = count_digits(biggiesorig.second.back());

    digits biggies;
    biggies.first.reserve(sz + 2);
    biggies.second.reserve(sz + 2);

    if (first_bigvalue)
    {
        biggies.first = biggiesorig.first;
        biggies.second = biggiesorig.second;
    }
    else
    {
        biggies.first = biggiesorig.second;
        biggies.second = biggiesorig.first;
    }


    digits working;
    working.first.reserve(sz + 2);
    working.second.reserve(sz + 2);

    base_n = 2;
    working.second = biggies.second;
    working.first = biggies.first;

    vector<vector<size_t>> multiples;
    multiples.reserve(200);
    multiples.push_back(biggies.second);
    while (1)
    {
        single(working);
        if (working.second.size() < working.first.size() || (working.second.size() ==
            working.first.size() && working.second.back() < working.first.back()))
        {
            multiples.push_back(working.second);
        }
        else break;
    }
    vector<size_t> two_powers;
    while (!multiples.empty())
    {
        working.second = multiples.back();
        while (working.first.size() > working.second.size() || (working.first.size() ==
            working.second.size() && working.first.back() > working.second.back())
            || working.second.size() == 1 && working.first.size() == 1 &&
            working.first.back() == working.second.back())
        {
            dual_diff(working);
            two_powers.push_back(multiples.size() - 1);
        }
        multiples.pop_back();
    }
    vector<size_t> result;
    size_t remainder = working.first[0];
    working.first = big_exp(2, two_powers.back());
    two_powers.pop_back();
    for (const auto& power : two_powers)
    {
        working.second = big_exp(2, power);
        dual(working);
    }
    return {working.first, remainder};

}

size_t diophantine_max(size_t limit)
{
    limit += 1; // include in upper bound
    digits max_compare;
    max_compare.first = {0};
    size_t d_for_max_x = 0;
    bool has_solution = false;
    double y = 1.0;
    size_t count = 0;
    digits working;
    for (size_t d = 1; d != limit; ++d)
    {
        if (is_square(d))
            continue;

        auto xvec = next_convergent(d);

        size_t x = xvec.front();

        double yy = ((double(-1) + (starter * starter)) / d);
        double ymodf = std::modf(std::sqrt(yy), &y);
        double result = yy <= 0 || ymodf != 0 ? 0 : ((starter * starter) - (d * yy));
        if (result == 1)
        {
            continue;
        }

        yy = ((double(-1) + (x * x)) / d);
        ymodf = std::modf(std::sqrt(yy), &y);
        result = yy <= 0 || ymodf != 0 ? 0 : ((x * x) - (d * yy));
        if (result == 1)
        {
            continue;
        }

        has_solution = false;
        vector<size_t> xfull;
        while (1)
        {
            xfull = next_convergent();

            vector<size_t> xsquared = big_square(xfull);

            vector<size_t> yyvec = xsquared;
            yyvec[0] -= 1;

            digits working;
            working.first = yyvec;
            working.second = {d};
            auto result = big_division(working);
            if (result.second != 0)
                continue;
            yyvec = result.first;

            working.first.clear();
            working.second = yyvec;
            working.first = yyvec;

            for (size_t i = 0; i != d-1; ++i)
            {
                dual(working);
            }
            working.second = working.first;
            working.first = xsquared;
            auto bob = dual_diff(working);
            if (bob)
                continue;
            if (working.first.size() == 1 && working.first[0] == 1)
            {
                has_solution = true;
                break;
            }
        }

        if (xfull.size() > max_compare.first.size())
        {
            max_compare.first = xfull;
            d_for_max_x = d;
        }
        else if (xfull.size() == max_compare.first.size())
        {
            max_compare.second = xfull;
            if (compare_blocks(max_compare) < 0)
            { 
                max_compare.first = max_compare.second;
                d_for_max_x = d;
            }
        }
    }
    return d_for_max_x;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = diophantine_max(1000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}