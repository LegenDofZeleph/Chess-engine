#pragma once
#include "../listener.hh"
#include "../pgn-move.hh"
#include "../pgn-parser.hh"
#include "../report-type.hh"
#include "bitboard.hh"
#include "moves/moves.hh"
#include "moves/tool.hh"

namespace board
{
    size_t file_to_bit(board::File f);

    size_t play_to_bit(std::string &s, size_t a, size_t b);

    size_t rank_to_bit(board::Rank r);
    pieces_moves move_from_pgn(board::PgnMove &move,
                               std::vector<unsigned long long> &bitboard);
    void listeners(std::string &s, listener::Listener *list);
} // namespace board
