#include <vector>
#include <cstddef>
#include <cmath>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <set>

using std::size_t;
using std::sqrt;
using std::abs;
using std::cout;

static std::set<size_t> trios;
static std::set<size_t> quadros;
static std::set<size_t> pentos;
static std::set<size_t> hexos;
static std::set<size_t> heptos;
static std::set<size_t> octos;

static size_t target;
static size_t first_i;

std::set<size_t> make_triangle()
{
    std::set<size_t> ret;
    size_t step = 2;
    for (size_t i = 1; i < 10000;)
    {
        if (i > 1000)
            ret.insert(i);
        i += step;
        step += 1;
    }
    return ret;
}

std::set<size_t> make_square()
{
    std::set<size_t> ret;
    for (size_t i = 1; i < 10000; ++i)
    {
        size_t square_i = i * i;
        if (square_i > 10000)
            break;
        if (square_i > 1000)
            ret.insert(square_i);
    }
    return ret;
}

std::set<size_t> make_pent()
{
    std::set<size_t> ret;
    size_t step = 4;
    for (size_t i = 1; i < 10000;)
    {
        if (i > 1000)
            ret.insert(i);
        i += step;
        step += 3;
    }
    return ret;
}

std::set<size_t> make_hex()
{
    std::set<size_t> ret;
    size_t step = 5;
    for (size_t i = 1; i < 10000;)
    {
        if (i > 1000)
            ret.insert(i);
        i += step;
        step += 4;
    }
    return ret;
}

std::set<size_t> make_hept()
{
    std::set<size_t> ret;
    size_t step = 6;
    for (size_t i = 1; i < 10000;)
    {
        if (i > 1000)
            ret.insert(i);
        i += step;
        step += 5;
    }
    return ret;
}

std::set<size_t> make_oct()
{
    std::set<size_t> ret;
    size_t step = 7;
    for (size_t i = 1; i < 10000;)
    {
        if (i > 1000)
            ret.insert(i);
        i += step;
        step += 6;
    }
    return ret;
}

size_t get_retsum(std::vector<size_t> cyclos)
{
    size_t retsum = 0;
    for (const auto& cyclo : cyclos)
    {
        retsum += cyclo;
    }  
    return retsum;
}

size_t find_next(std::vector<size_t> cyclos, size_t i, bool hastrio,
    bool hasquadro, bool haspento, bool hashexo, bool hashepto, bool hasocto)
{

    size_t next = i % 100;
    next *= 100;
    next += 10;
    size_t retsum = 0;

    for (size_t j = next; j != next + 100; ++j)
    {
        if (cyclos.size() == target - 1 &&
            ((j % 100) != ((first_i / 100) % 100)))
            continue;

        cyclos.push_back(j);
        bool is_target_size = cyclos.size() == target;
        if (!hastrio && trios.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j, true, hasquadro,
                haspento, hashexo, hashepto, hasocto);
            if (retsum)
                return retsum;
        }
        if (!hasquadro && quadros.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j, hastrio, true,
                haspento, hashexo, hashepto, hasocto);
            if (retsum)
                return retsum;
        }
        if (!haspento && pentos.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j,  hastrio, hasquadro,
                true, hashexo, hashepto, hasocto);
            if (retsum)
                return retsum;

        }
        if (target > 3 && !hashexo && hexos.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j, hastrio, hasquadro,
                haspento, true, hashepto, hasocto);
            if (retsum)
                return retsum;
        }
        if (target > 4 && !hashepto && heptos.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j, hastrio, hasquadro,
                haspento, hashexo, true, hasocto);
            if (retsum)
                return retsum;
        }
        if (target > 5 && !hasocto && octos.count(j) != 0)
        {
            if (is_target_size)
                return get_retsum(cyclos);
            retsum = find_next(cyclos, j, hastrio, hasquadro,
                haspento, hashexo, hashepto, true);
            if (retsum)
                return retsum;
        }
        cyclos.pop_back();
    }
    return retsum;
}

size_t cyclical_figurate(size_t target_n)
{
    target = target_n;
    trios = make_triangle();
    quadros = make_square();
    pentos = make_pent();
    hexos = make_hex();
    heptos = make_hept();
    octos = make_oct();

    std::vector<size_t> cyclos;
    cyclos.reserve(6);
    size_t retsum = 0;

    for (size_t i = 1010; i != 10000; ++i)
    {
        first_i = i;

        if (i % 100 < 10 || find(cyclos.cbegin(), cyclos.cend(), i) != cyclos.cend())
            continue;

        cyclos.push_back(i);
        if (trios.count(i) != 0)
        {
            retsum = find_next(cyclos, i, true, false, false,
                false, false, false);
            if (retsum)
                return retsum;
        }
        if (quadros.count(i) != 0)
        {
            retsum = find_next(cyclos, i, false, true, false,
                false, false, false);
            if (retsum)
                return retsum;     
        }
        if (pentos.count(i) != 0)
        {
            retsum = find_next(cyclos, i, false, false, true,
                false, false, false);
            if (retsum)
                return retsum;
        }
        if (target > 3 && hexos.count(i) != 0)
        {
            retsum = find_next(cyclos, i, false, false, false,
                true, false, false);
            if (retsum)
                return retsum;
        }
        if (target > 4 && heptos.count(i) != 0)
        {
            retsum = find_next(cyclos, i, false, false, false,
                false, true, false);
            if (retsum)
                return retsum;
        }
        if (target > 5 && octos.count(i) != 0 )
        {
            retsum = find_next(cyclos, i, false, false, false,
                false, false, true);
            if (retsum)
                return retsum;
        }
        cyclos.pop_back();

    }
    return retsum;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = cyclical_figurate(6);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}