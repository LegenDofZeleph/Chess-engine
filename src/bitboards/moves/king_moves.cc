#include <cmath>
#include <vector>

#include "moves.hh"
namespace board
{
    unsigned long long Move::white_king_castling()
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        res |= un << 1;
        return res;
    }

    unsigned long long Move::black_king_castling()
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        res |= un << 57;
        return res;
    }

    unsigned long long Move::white_queen_castling()
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        res |= un << 5;
        return res;
    }

    unsigned long long Move::black_queen_castling()
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        res |= un << 61;
        return res;
    }

    std::vector<unsigned long long> Move::king_moves()
    {
        std::vector<unsigned long long> res(64, 0);
        unsigned long long tmp;
        unsigned long long un = 1;
        for (unsigned long long i = 0; i < 64; i++)
        {
            unsigned long long tab = 0;
            // if not in the last line we can move backward
            if (i >= 8)
            {
                tmp = i - 8;
                tab |= un << tmp;
                // if not in the right colon we can move on backward right
                // diagonal
                if (i % 8 != 0)
                {
                    tmp = i - 9;
                    tab |= un << tmp;
                }
                // if not in the left colon we can move on backward left
                // diagonal
                if (i % 8 != 7)
                {
                    tmp = i - 7;
                    tab |= un << tmp;
                }
            }
            // if not on the upper line we can move ahead
            if (i <= 55)
            {
                tmp = i + 8;
                tab |= un << tmp;
                // if not in the right colon we can move on upward right
                // diagonal
                if (i % 8 != 0)
                {
                    tmp = i + 7;
                    tab |= un << tmp;
                }
                // if not in the left colon we can move on upward left diagonal
                if (i % 8 != 7)
                {
                    tmp = i + 9;
                    tab |= un << tmp;
                }
            }
            // if not on the right colon we can move on the right
            if (i % 8 != 0)
            {
                tmp = i - 1;
                tab |= un << tmp;
            }
            // if not on the left colon we can move on the left
            if (i % 8 != 7)
            {
                tmp = i + 1;
                tab |= un << tmp;
            }
            res[i] = tab;
        }
        return res;
    }
} // namespace board
