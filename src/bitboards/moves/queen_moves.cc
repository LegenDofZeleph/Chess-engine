#include <cmath>
#include <vector>

#include "moves.hh"
namespace board
{
    std::vector<unsigned long long> Move::queen_moves()
    {
        std::vector<unsigned long long> res(64, 0);
        std::vector<unsigned long long> rookTab = Move::rook_moves();
        std::vector<unsigned long long> bishopTab = Move::bishop_moves();
        for (unsigned long long i = 0; i < 64; i++)
        {
            res[i] = rookTab[i] + bishopTab[i];
        }
        return res;
    }
} // namespace board
