#pragma once

#include <cmath>
#include <iostream>
#include <vector>

#include "../color.hh"
#include "../piece-type.hh"
#include "../position.hh"
#include "../report-type.hh"

namespace board
{
    // typedef unsigned long long BitBoard;
    class BitB
    {
    public:
        // init
        void print_BitBoard(unsigned long long to_print);
        static std::vector<unsigned long long> init_bitboard();
        /*for the init_bitboard function, it returns a std::vector of unsigned
         * long long with default values for the setup of the initial board
         *with [0] being the white_pawn_bitboard, [1] the white_rook_board
         , [2] the white knight board, [3] the white bishop board,
         [4] the white queen board, [5] the white king board,
         [6] the white board in general
         [7] the black pawn , and on and on till 13 being the black_board*/
    };
} // namespace board
