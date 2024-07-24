#pragma once

#include <cmath>
#include <string>
#include <vector>

#include "../bitboard.hh"
namespace board
{
    class Move
    {
    public:
        std::vector<unsigned long long> bishop_moves();
        static std::vector<unsigned long long> black_pawn_moves();

        static std::vector<unsigned long long> white_pawn_moves();

        std::vector<unsigned long long> queen_moves();

        std::vector<unsigned long long> rook_moves();

        static std::vector<unsigned long long> king_moves();

        static std::vector<unsigned long long> knight_moves();

        std::vector<struct pieces_moves>
        white_possible_moves(std::vector<unsigned long long> &bitBoard);

        std::vector<struct pieces_moves>
        black_possible_moves(std::vector<unsigned long long> &bitBoard);

        unsigned long long black_rooks_attacks
        (std::vector<unsigned long long> &bitBoard);

        unsigned long long white_rooks_attacks
        (std::vector<unsigned long long> &bitBoard);

        unsigned long long white_pawns_attacks
        (std::vector<unsigned long long> &bitBoard);

        unsigned long long black_pawns_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long white_bishops_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long black_bishops_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long white_queen_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long black_queen_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long white_king_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long black_king_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long white_knights_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        unsigned long long black_knights_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        std::vector<unsigned long long> &black_attacks
        (std::vector<unsigned long long> &bitBoard);
        
        std::vector<unsigned long long> &white_attacks
        (std::vector<unsigned long long> &bitBoard);

        bool black_king_is_safe(std::vector<unsigned long long> &bitBoard,
                                unsigned long long i,
                                unsigned long long newPos);
        bool white_king_is_safe(std::vector<unsigned long long> &bitBoard,
                                unsigned long long i,
                                unsigned long long newPos);

        unsigned long long white_king_castling();

        unsigned long long black_king_castling();

        unsigned long long white_queen_castling();

        unsigned long long black_queen_castling();

        unsigned long long get_number_of_moves(std::string &file_path);

        unsigned long long get_white_size_rec(
            std::vector<unsigned long long> &bitBoard,
            std::vector<struct board::pieces_moves> &moves, int depth);

        unsigned long long get_black_size_rec(
            std::vector<unsigned long long> &bitBoard,
            std::vector<struct board::pieces_moves> &moves, int depth);
        //std::vector<unsigned long long>
        //&do_move(std::vector<unsigned long long> &bitBoard,
             /*   struct pieces_moves &p);
        std::vector<unsigned long long>
    &undo_move(std::vector<unsigned long long> &bitBoard,
    struct pieces_moves &p);*/
    };
    struct pieces_moves
    {
        unsigned long long initial = 0;
        unsigned long long moved = 0;
        //report[0] = white king castling
        //report[1] = white queen castling
        //report[2] = en passant blanc
        //report[3] = mouvement qui met roi noir en echec
        //report[4] = black king castling
        //report[5] = black queen catling
        //report[6] = en passant noir
        //report[7] = mouvement qui met roi blanc en echec
        //report[8] = prise d'une piece
        //report[9] = white pawn moves
        //report[10] = white rook moves
        //report[11] = white knight moves
        //report[32] = white bishop moves
        //report[12] = white queen moves
        //report[13] = white king moves
        //report[14] = black pawn moves
        //report[15] = black rook moves
        //report[16] = black knight moves
        //report[17] = black bishop moves
        //report[18] = black queen moves
        //report[19] = black king moves
        //report[20] = white pawn is taken
        //report[21] = white rook is taken
        //report[22] = white knight is taken
        //report[23] = white bishop is taken
        //report[24] = white queen is taken
        //report[25] = white king is taken
        //report[26] = black pawn is taken
        //report[27] = black rook is taken
        //report[28] = black knight is taken
        //report[29] = black bishop is taken
        //report[30] = black queen is taken
        //report[31] = black king is taken
        //report[33] = is promotion to rook
        //report[34] = is promotion to knight
        //report[35] = is promotion to bishop
        //report[36] = is promotion to queen
        // bool pion blanc just +2 in pos [37]
        // bool pion blanc just +2 in pos [38]
        // bool pion blanc just +2 in pos [39]
        // bool pion blanc just +2 in pos [40]
        // bool pion blanc just +2 in pos [41]
        // bool pion blanc just +2 in pos [42]
        // bool pion blanc just +2 in pos [43]
        // bool pion blanc just +2 in pos [44]
        // bool pion noir just +2 in pos [45]
        // bool pion noir just +2 in pos [46]
        // bool pion noir just +2 in pos [47]
        // bool pion noir just +2 in pos [48]
        // bool pion noir just +2 in pos [49]
        // bool pion noir just +2 in pos [50]
        // bool pion noir just +2 in pos [51]
        // bool pion noir just +2 in pos [52]
        unsigned long long report_type = 0;
    };
} // namespace board
