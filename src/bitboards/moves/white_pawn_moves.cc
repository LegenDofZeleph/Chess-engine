#include <cmath>
#include <vector>

#include "moves.hh"
namespace board
{
    std::vector<unsigned long long> Move::white_pawn_moves()
    {
        std::vector<unsigned long long> bob(64, 0);
        unsigned long long tmp;
        unsigned long long un = 1;
        for (unsigned long long i = 0; i < 64; i++)
        {
            unsigned long long count = 0;
            if (i <= 15)
            {
                tmp = i + 8;
                count |= un << tmp;
                tmp = i + 16;
                count |= un << tmp;
            }
            else if (i > 7 && i < 56)
            {
                tmp = i + 8;
                count |= un << tmp;
            }
            bob[i] = count;
        }
        return bob;
    }
} // namespace board
