#include <cmath>
#include <vector>

#include "moves.hh"
/*Adds every move possible for a knight based on his position the increments
  {6,10,15,17} positive or negative */
namespace board
{
    std::vector<unsigned long long>
    &first_column(unsigned long long i, std::vector<unsigned long long> &bob)
    {
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long count = 0;
        // h1 case
        if (i == 0)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
        }
        // h2 case
        else if (i == 8)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
        }
        // h7 case
        else if (i == 48)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
        }
        // h8 case
        else if (i == 56)
        {
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
        }
        // h* cases
        else
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
        }
        bob[i] = count;
        return bob;
    }
    std::vector<unsigned long long>
    &second_column(unsigned long long i, std::vector<unsigned long long> &bob)
    {
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long count = 0;
        // g1 case
        if (i == 1)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
        }
        // g2 case
        else if (i == 9)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
        }
        // g7 case
        else if (i == 49)
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // g8 case
        else if (i == 57)
        {
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // g* case
        else
        {
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        bob[i] = count;
        return bob;
    }
    std::vector<unsigned long long>
    &seventh_column(unsigned long long i, std::vector<unsigned long long> &bob)
    {
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long count = 0;
        // b1 case
        if (i == 6)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
        }
        // b2 case
        else if (i == 14)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
        }
        // b7 case
        else if (i == 54)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // b8 case
        else if (i == 62)
        {
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // b* cases
        else
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        bob[i] = count;
        return bob;
    }

    std::vector<unsigned long long>
    &eightth_column(unsigned long long i, std::vector<unsigned long long> &bob)
    {
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long count = 0;
        // a1 case
        if (i == 7)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
        }
        // a2 case
        else if (i == 15)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
        }
        // a7 case
        else if (i == 55)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // a8 case
        else if (i == 63)
        {
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // a* case
        else
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        bob[i] = count;
        return bob;
    }

    std::vector<unsigned long long>
    &other_column(unsigned long long i, std::vector<unsigned long long> &bob)
    {
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long count = 0;
        // *1 case
        if (i < 8)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
        }
        // *2 case
        else if (i < 16)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
        }
        // *7 case
        else if (i > 47 && i < 56)
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 10;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // *8 case
        else if (i > 55)
        {
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
        }
        // ** case
        else
        {
            tmp = i + 6;
            count |= un << tmp;
            tmp = i + 10;
            count |= un << tmp;
            tmp = i + 15;
            count |= un << tmp;
            tmp = i + 17;
            count |= un << tmp;
            tmp = i - 6;
            count |= un << tmp;
            tmp = i - 10;
            count |= un << tmp;
            tmp = i - 17;
            count |= un << tmp;
            tmp = i - 15;
            count |= un << tmp;
        }
        bob[i] = count;
        return bob;
    }
    std::vector<unsigned long long> Move::knight_moves()
    {
        std::vector<unsigned long long> bob(64, 0);
        for (unsigned long long i = 0; i < 64; i++)
        {
            // H COLUMN
            if (i % 8 == 0)
            {
                bob = first_column(i, bob);
            }
            // G COLUMN
            else if (i % 8 == 1)
            {
                bob = second_column(i, bob);
            }
            // B COLUMN
            else if (i % 8 == 6)
            {
                bob = seventh_column(i, bob);
            }
            // A COLUMN
            else if (i % 8 == 7)
            {
                bob = eightth_column(i, bob);
            }
            // C,D,E,F COLUMNS
            else
            {
                bob = other_column(i, bob);
            }
        }
        return bob;
    }
} // namespace board
