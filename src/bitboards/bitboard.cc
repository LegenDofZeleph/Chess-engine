#include "bitboard.hh"

#include <stdlib.h>
namespace board
{
    void BitB::print_BitBoard(unsigned long long to_print)
    {
        for (unsigned long long i = 64; i > 0; i--)
        {
            unsigned long long tmp = pow(2, i - 1);
            if (to_print >= tmp)
            {
                std::cout << "\033[1;31mX\033[0m";
                //std::cout << 'X';
                to_print -= tmp;
            }
            else
                std::cout << "O";
            if ((i - 1) % 8 != 0)
            {
                std::cout << "   ";
            }
            else
            {
                std::cout << std::endl << std::endl;
            }
        }
    }

    std::vector<unsigned long long> BitB::init_bitboard()
    {
        std::vector<unsigned long long> bob(16, 0);
        // white stuff
        // white_pawn
        bob[0] = 65280;
        // white_rook
        bob[1] = 129;
        // white_knight
        bob[2] = 66;
        // white_bishop
        bob[3] = 36;
        // white_queen
        bob[4] = 16;
        // white_king
        bob[5] = 8;
        // white_board
        bob[6] = 65535;

        // black stuff
        // black_pawn
        bob[7] = 71776119061217280;
        // black_rook
        bob[8] = 9295429630892703744U;
        // black_knight
        bob[9] = 4755801206503243776U;
        // black_bishop
        bob[10] = 2594073385365405696U;
        // black_queen
        bob[11] = 1152921504606846976U;
        // black_king
        bob[12] = 576460752303423488U;
        // black_board
        bob[13] = 18446462598732840960U;

        // white attacks
        bob[14] = 16711680;
        // black attacks
        bob[15] = 280375465082880;

        // bool can_white_queen_castle = true [0];
        // can_black_queen_castle = true [1];
        // can_white_king_castle = true [2];
        // can_black_king_castle = true [3];
        // bool just_canceled_white_queen_castle [4]
        // bool just_canceled_black_queen_castle [5]
        // bool just_canceled_white_king_castle [6]
        // bool just_canceled_black_king_castle [7]
        // bool pion blanc just +2 in pos [24]
        // bool pion blanc just +2 in pos [25]
        // bool pion blanc just +2 in pos [26]
        // bool pion blanc just +2 in pos [27]
        // bool pion blanc just +2 in pos [28]
        // bool pion blanc just +2 in pos [29]
        // bool pion blanc just +2 in pos [30]
        // bool pion blanc just +2 in pos [31]
        // bool pion noir just +2 in pos [32]
        // bool pion noir just +2 in pos [33]
        // bool pion noir just +2 in pos [34]
        // bool pion noir just +2 in pos [35]
        // bool pion noir just +2 in pos [36]
        // bool pion noir just +2 in pos [37]
        // bool pion noir just +2 in pos [38]
        // bool pion noir just +2 in pos [39]
        bob[16] = 15;

        return bob;
    }
} // namespace board
