#include <cmath>
#include <vector>

#include "moves.hh"
namespace board
{
    std::vector<unsigned long long> Move::rook_moves()
    {
        std::vector<unsigned long long> res(64, 0);
        for (unsigned long long i = 0; i < 64; i++)
        {
            unsigned long long tab = 0;
            unsigned long long j = i % 8 + 56;
            unsigned long long un = 1;
            bool stop = false;
            while (!stop)
            {
                if (j > i % 8)
                {
                    tab |= un << j;
                    j -= 8;
                }
                else if (j == i % 8)
                {
                    tab |= un << j;
                    stop = true;
                }
                if (i == 42)
                    std::cout << "tab after colon completed : " << tab << '\n';
            }
            tab &= ~(un << i);
            // possible moves of rook backward
            // possible moves of rook on the right
            if (i % 8 != 0)
            {
                for (unsigned long long j = i - 1; j % 8 != 7; j--)
                {
                    tab |= un << j;
                }
            }
            // possible moves of rook on the left
            if (i % 8 != 7)
            {
                for (unsigned long long j = i + 1; j % 8 != 0; j++)
                {
                    tab |= un << j;
                }
            }
            res[i] = tab;
        }
        return res;
    }
} // namespace board
