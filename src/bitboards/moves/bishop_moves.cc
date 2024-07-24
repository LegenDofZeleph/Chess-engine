#include <cmath>
#include <iostream>
#include <vector>

#include "moves.hh"
namespace board
{
    std::vector<unsigned long long> Move::bishop_moves()
    {
        std::vector<unsigned long long> res(64, 0);
        unsigned long long un = 1;
        for (unsigned long long i = 0; i < 64; i++)
        {
            unsigned long long tab = 0;
            // backward right diagonal
            if (i > 8 && i % 8 != 0)
            {
                bool stop = false;
                unsigned long long j = i - 9;
                while (!stop)
                {
                    tab |= un << j;
                    if (j >= 9 && j % 8 != 0)
                        j -= 9;
                    else
                        stop = true;
                }
            }
            // backward left diagonal
            if (i > 7 && i % 8 != 7)
            {
                unsigned long long j = i - 7;
                bool stop = false;
                while (!stop)
                {
                    tab |= un << j;
                    if (j > 7 && j % 8 != 7)
                        j -= 7;
                    else
                        stop = true;
                }
            }
            // forward right diagonal
            if (i < 56 && i % 8 != 0)
            {
                unsigned long long j = i + 7;
                bool stop = false;
                while (!stop)
                {
                    tab |= un << j;
                    if (j < 56 && j % 8 != 0)
                        j += 7;
                    else
                        stop = true;
                }
            }
            // forward left diagonal
            if (i < 56 && i % 8 != 7)
            {
                unsigned long long j = i + 9;
                bool stop = false;
                while (!stop)
                {
                    tab |= un << j;
                    if (j < 55 && j % 8 != 7)
                        j += 9;
                    else
                        stop = true;
                }
            }
            res[i] = tab;
        }
        return res;
    }
} // namespace board
