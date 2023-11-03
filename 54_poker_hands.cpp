#include <cstddef>
#include <iostream>
#include <chrono>
#include <utility>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <stdexcept>

using std::cout;
using std::size_t;
using std::vector;

using hand = vector<std::pair<unsigned char, unsigned char>>;

static vector<unsigned char> cards{
    '2', '3', '4', '5', '6', '7', '8', '9', 
    'T' ,'J', 'Q', 'K', 'A'};

static vector<unsigned char> suits{
    'C', 'H', 'S', 'D'};

static std::map<unsigned char, size_t> cardval {
    {0, 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, 
    {'8', 7}, {'9', 8}, {'T', 9}, {'J', 10}, {'Q', 11}, {'K', 12}, {'A', 13}
};

// hand score will be 90000 for royal, 80000 for straight flush etc,
// highest scoring card, then highest non-scoring card,
// so a three-of-a-kind of queens with a king high would be 31011

size_t high_non(const hand& player)
{
    size_t retcard = 0;
    for (const auto& pcard : player)
    {
        size_t pcardval = cardval.at(pcard.first);
        if (pcardval > retcard)
            retcard = pcardval;
    }
    return retcard;
}

size_t flush(const hand& player)
{
    bool has_flush = false;

    bool all_same = true;
    for (const auto& suit : suits)
    { 
        all_same = true;
        for (const auto& pcard : player)
        {
            if (pcard.second != suit)
            { 
                all_same = false;
                break;
            }
        }
        if (all_same)
        {
            has_flush = true;
            break;
        }
    }
    if (!has_flush)
        return 0;
    else
        return high_non(player);
}

size_t straight(const hand& player)
{
    size_t lowest = 1000;
    unsigned char lowchar = 255;
    std::set<unsigned char> cardset;
    for (const auto& pcard : player)
    {
        cardset.insert(pcard.first);
        size_t pval = cardval.at(pcard.first);
        if (pval < lowest)
        {
            lowest = pval;
            lowchar = pcard.first;
        }
    }
    auto lowit = find(cards.begin(), cards.end(), lowchar);
    if (cards.cend() - 5 < lowit)
        return 0;
    size_t rounds = 0;
    unsigned char lastcard = 0;
    for (std::vector<unsigned char>::iterator it = lowit; it != lowit + 5; ++it)
    { 
        if (cardset.count(*it) == 0)
            return 0;
        if (++rounds == 5)
        {
            lastcard = *it;
        }    
    }
    return cardval.at(lastcard);
}

size_t single_hand(hand& player)
{
    size_t has_flush = flush(player);
    size_t has_straight = straight(player);
    if (has_flush && has_straight)
    {
        if (has_straight == 13) // highest value in straight was an ace
            return 90000;
        else
        {
            return 80000 + (has_straight * 100);
        }
    }
    else
    {
        size_t highest_count = 0;
        unsigned char groupcard = 0;
        unsigned char first_pair = 0;
        bool has_pair = false;
        for (const auto& card : cards)
        {
            size_t currcount = 0;
            for (const auto& pcard : player)
            {
                if (pcard.first == card)
                    if (++currcount > 1 && !has_pair)
                    {
                        first_pair = card;
                        has_pair = true;
                    }
            }
            if (currcount > highest_count || (currcount == 2 && highest_count == 2))
            {
                highest_count = currcount;
                groupcard = card;
                if (currcount > 3)
                {
                    for (auto& pcard : player)
                    {
                        if (pcard.first != groupcard)
                        {
                            return 70000 + (cardval.at(groupcard) * 100) +
                                cardval.at(pcard.first);
                        }
                    }
                }
                else if (currcount > 2 && has_pair && card != first_pair)
                {
                    return 60000 + (cardval.at(card) * 100); // no non-scoring card
                }
            }
        }
        if (has_flush)
        {
            return 50000 + (has_flush * 100); // no non-scoring card
        }
        else if (has_straight)
        {
            return 40000 + (has_straight * 100); // no non-scoring card
        }
        else
        {
            if (highest_count > 2)
            {
                for (auto& pcard : player)
                {
                    if (pcard.first == groupcard)
                    {
                        pcard.first = 0;
                    }
                }
                return 30000 + (cardval.at(groupcard) * 100) + high_non(player);
            }
            if (has_pair && first_pair != groupcard)
            {
                for (auto& pcard : player)
                {
                    if (pcard.first != groupcard && pcard.first != first_pair)
                    {
                        size_t groupval = cardval.at(groupcard);
                        size_t pairval = cardval.at(first_pair);
                        size_t bigval = groupval > pairval ? groupval : pairval;
                        return 20000 + (bigval * 100) + cardval.at(pcard.first);
                    }
                }
            }
            else if (has_pair && first_pair == groupcard)
            {
                for (auto& pcard : player)
                {
                    if (pcard.first == groupcard)
                    {
                        pcard.first = 0;
                    }
                }
                return 10000 + (cardval.at(groupcard) * 100) + high_non(player);
            }
            else
            {
                return high_non(player);
            }
        }
    }
    throw std::runtime_error("Hand-scoring logic failure");
    return 0; // this shouldn't be possible
}


bool round_winner(unsigned char* round)
{
    hand p1;
    hand p2;
    p1.reserve(5);
    p2.reserve(5);
    for (size_t i = 0; i != 5; ++i)
    { 
        p1.push_back({round[(i*3)], round[i*3+1]});
        p2.push_back({round[(i+5)*3], round[((i+5)*3)+1]});
    }
    return single_hand(p1) > single_hand(p2);
}

size_t poker_hands()
{
    std::basic_ifstream<unsigned char> infile("poker.txt");
    unsigned char hand[30];
    size_t player1 = 0;
    while (infile.getline(hand, 50, '\n'))
    {
        if(round_winner(hand))
            ++player1;
    }
    return player1;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = poker_hands(); // 4160357289

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n'
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

}