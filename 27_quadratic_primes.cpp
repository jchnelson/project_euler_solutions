#include <cmath>
#include <iostream>
#include <chrono>

using std::cout;


bool is_prime(long long i)
{
    if (i == 0 || i == 1)
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

// find the numbers a and b such that n squared + an + b generates the 
// maximum number of consecutive primes beginning from n = 0.

// for max, a < absolute value of max, b <= absolute

long long* quad_primes(long long ab_max)
{
    long long a_min = -(ab_max-1);
    long long b_min = -ab_max;
    long long b_max = ab_max + 1;
    long long most_conseq = 0;
    long long a_val = 0;
    long long b_val = 0;
    for (long long a = a_min; a != ab_max; ++a)
    {
        for (long long b = b_min; b != b_max; ++b)
        {
            if (!is_prime(b) || !is_prime(1 + a + b))
                continue;
            long long curr_conseq = 0;
            for (long long n = 0; n != 1000; ++n)
            {
                if (is_prime((n * n) + (a * n) + b))
                {
                    ++curr_conseq;
                }
                else
                {
                    if (curr_conseq > most_conseq)
                    {
                        most_conseq = curr_conseq;
                        a_val = a;
                        b_val = b;
                    }
                    break;
                }
            }
        }
    }
    return new long long[3]{a_val, b_val, most_conseq};
}



int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto bob = quad_primes(1000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << "a: " << bob[0] << " b: " << bob[1] << " with\n"
        << bob[2] << " consecutive primes in " <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

    cout << "Product: " << bob[0] * bob[1];

}