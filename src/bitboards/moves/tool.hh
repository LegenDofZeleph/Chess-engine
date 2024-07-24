#pragma once
#include <vector>

#include "moves.hh"
namespace board
{
    std::vector<unsigned long long>
    &do_move(std::vector<unsigned long long> &bitBoard, struct pieces_moves &p);

    std::vector<unsigned long long>
    &undo_move(std::vector<unsigned long long> &bitBoard,
               struct pieces_moves &p);

    std::vector<unsigned long long>
    &add_piece(std::vector<unsigned long long> &bitBoard, size_t i, size_t t);

    std::vector<unsigned long long>
    &del_piece(std::vector<unsigned long long> &bitBoard, size_t i, size_t t);

    unsigned long long
    get_num_of_moves_w(std::vector<unsigned long long> &bitBoard,
                       std::vector<struct board::pieces_moves> &moves,
                       int depth);

    unsigned long long
    get_num_of_moves_b(std::vector<unsigned long long> &bitBoard,
                       std::vector<struct board::pieces_moves> &p, int depth);
} // namespace board
