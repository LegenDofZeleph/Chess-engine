#include <cmath>
#include <fstream>
#include <iostream>

#include "all.hh"
#include "tool.hh"
#include "moves.hh"
#include "../bitboard.hh"
#include "../pgn.hh"

namespace board
{
    std::vector<unsigned long long> get_bitBoard(std::string line, int i)
    {
        std::vector<unsigned long long> bitBoard(17, 0);
        board::Move board;
        unsigned long long j = 0;
        unsigned long long un = 1;
        while (i >= 0)
        {
            if (line[i] == 'P')
                bitBoard[0] |= un << j;
            else if (line[i] == 'R')
                bitBoard[1] |= un << j;
            else if (line[i] == 'N')
                bitBoard[2] |= un << j;
            else if (line[i] == 'B')
                bitBoard[3] |= un << j;
            else if (line[i] == 'Q')
                bitBoard[4] |= un << j;
            else if (line[i] == 'K')
                bitBoard[5] |= un << j;
            else if (line[i] == 'p')
                bitBoard[7] |= un << j;
            else if (line[i] == 'r')
                bitBoard[8] |= un << j;
            else if (line[i] == 'n')
                bitBoard[9] |= un << j;
            else if (line[i] == 'b')
                bitBoard[10] |= un << j;
            else if (line[i] == 'q')
                bitBoard[11] |= un << j;
            else if (line[i] == 'k')
                bitBoard[12] |= un << j;
            else if (line[i] == '/')
            {
                j--;
            }
            else if (line[i] >= '0' && line[i] <= '9')
                j += line[i] - '0' - 1;
            i--;
            j++;
        }
        for (size_t x = 0; x < 6; x++)
        {
            bitBoard[6] |= bitBoard[x];
        }
        for (size_t x = 7; x < 13; x++)
        {
            bitBoard[13] |= bitBoard[x];
        }
        bitBoard = board.white_attacks(bitBoard);
        bitBoard = board.black_attacks(bitBoard);
        return bitBoard;
    }

    unsigned long long
    get_num_of_moves_w(std::vector<unsigned long long> &bitBoard,
                       std::vector<struct board::pieces_moves> &moves,
                       int depth)
    {
        board::Move board;
        if (depth == 0)
            return 1;
        else if (depth == 1)
        {
            return moves.size();
        }
        else
        {
            int count = 0;
            for (size_t i = 0; i < moves.size(); ++i)
            {
                struct board::pieces_moves p = moves[i];
                bitBoard = do_move(bitBoard, p);
                unsigned long long castlingBooleans = bitBoard[16];
                std::vector<struct board::pieces_moves> m2 =
                    board.black_possible_moves(bitBoard);
                if (bitBoard[12] != 0 && bitBoard[5] != 0 && m2.size() != 0)
                    count += get_num_of_moves_b(bitBoard, m2, depth - 1);
                bitBoard[16] = castlingBooleans;
                bitBoard = undo_move(bitBoard, moves[i]);
            }
            return count;
        }
    }
    unsigned long long
    get_num_of_moves_b(std::vector<unsigned long long> &bitBoard,
                       std::vector<struct board::pieces_moves> &moves,
                       int depth)
    {
        board::Move board;
        if (depth == 0)
            return 1;
        else if (depth == 1)
        {
            return moves.size();
        }
        else
        {
            int count = 0;
            for (size_t i = 0; i < moves.size(); ++i)
            {
                bitBoard = do_move(bitBoard, moves[i]);
                unsigned long long castlingBooleans = bitBoard[16];
                std::vector<struct board::pieces_moves> m2;
                m2 = board.white_possible_moves(bitBoard);
                if (bitBoard[5] != 0 && bitBoard[12] != 0 && m2.size() != 0)
                    count += get_num_of_moves_w(bitBoard, m2, depth - 1);
                bitBoard[16] = castlingBooleans;
                bitBoard = undo_move(bitBoard, moves[i]);
            }
            return count;
        }
    }

    std::vector<unsigned long long>
    &are_castles_possible(std::vector<unsigned long long> &bitBoard,
                         std::string &line, int i, int size)
    {
        bool white_queen = false;
        bool white_king = false;
        bool black_queen = false;
        bool black_king = false;
        unsigned long long un = 1;
        int j = i;
        while (i < size)
        {
            if (line[i] == 'Q')
            {
                white_queen = true;
                bitBoard[16] |= un;
            }
            if (line[i] == 'K')
            {
                white_king = true;
                bitBoard[16] |= (un << 2);
            }
            if (line[i] == 'q')
            {
                black_queen = true;
                bitBoard[16] |= (un << 1);
            }
            if (line[i] == 'k')
            {
                black_king = true;
                bitBoard[16] |= (un << 3);
            }
            if (line[i] == ' ')
                break;
            i++;
        }
        if (white_queen || white_king || black_queen || black_king)
            j = i + 1;
        size_t tmp = play_to_bit(line, j, j + 1);
        if (line[j + 1] == '3')
            bitBoard[16] |= un << (tmp + 8);
        if (line[j + 1] == '6')
            bitBoard[16] |= un << (tmp - 8);
        if (!white_queen)
        {
            bitBoard[16] &= ~un;
        }
        if (!black_queen)
        {
            bitBoard[16] &= ~(un << 1);
        }
        if (!white_king)
        {
            bitBoard[16] &= ~(un << 2);
        }
        if (!black_king)
        {
            bitBoard[16] &= ~(un << 3);
        }
        return bitBoard;
    }

    unsigned long long
    Move::get_black_size_rec(std::vector<unsigned long long> &bitBoard,
                             std::vector<struct board::pieces_moves> &moves,
                             int depth)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        if (depth == 1)
        {
            res += moves.size();
        }
        else
        {
            unsigned long long size = moves.size();
            for (unsigned long long i = 0; i < size; i++)
            {
                std::vector<unsigned long long> bitBoard2;
                for (size_t j = 0; j < bitBoard.size(); j++)
                {
                    bitBoard2.push_back(bitBoard[j]);
                }
                for (size_t k = 14; k < 20; k++)
                {
                    if (moves[i].report_type & un << k)
                    {
                        bitBoard2[k - 7] &= ~(moves[i].initial);
                        bitBoard2[k - 7] |= moves[i].moved;
                    }
                }
                bitBoard2[13] &= ~(moves[i].initial);
                bitBoard2[13] |= moves[i].moved;
                std::vector<struct board::pieces_moves> new_moves =
                    board.white_possible_moves(bitBoard2);
                res +=
                    board.get_white_size_rec(bitBoard2, new_moves, depth - 1);
            }
        }
        return res;
    }

    unsigned long long
    Move::get_white_size_rec(std::vector<unsigned long long> &bitBoard,
                             std::vector<struct board::pieces_moves> &moves,
                             int depth)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        if (depth == 1)
        {
            res += moves.size();
        }
        else
        {
            unsigned long long size = moves.size();
            for (unsigned long long i = 0; i < size; i++)
            {
                std::vector<unsigned long long> bitBoard2;
                for (size_t j = 0; j < bitBoard.size(); j++)
                {
                    bitBoard2.push_back(bitBoard[j]);
                }
                for (size_t k = 9; k < 14; k++)
                {
                    if (moves[i].report_type & (un << k))
                    {
                        bitBoard2[k - 9] &= ~(moves[i].initial);
                        bitBoard2[k - 9] |= moves[i].moved;
                    }
                    break;
                }
                bitBoard2[6] &= ~(moves[i].initial);
                bitBoard2[6] |= moves[i].moved;
                std::vector<struct board::pieces_moves> new_moves =
                    board.black_possible_moves(bitBoard2);
                res +=
                    board.get_black_size_rec(bitBoard2, new_moves, depth - 1);
            }
        }
        return res;
    }

    unsigned long long Move::get_number_of_moves(std::string &file_path)
    {
        std::ifstream file;
        board::Move board;
        std::string line;
        unsigned long long res = 0;
        file.open(file_path);
        if (!file.is_open())
        {
            std::cerr << "error while openning perft file\n";
            exit(2);
        }
        std::getline(file, line);
        int i = 0;
        bool stop = false;
        std::vector<struct board::pieces_moves> moves;
        int size = line.size();
        while (!stop && i < size)
        {
            if (line[i] == ' ')
                stop = true;
            i++;
        }
        size_t color = line[i];
        std::vector<unsigned long long> bitBoard = get_bitBoard(line, i - 2);
        bitBoard = are_castles_possible(bitBoard, line, i + 2, size);
        int x = size - 1;
        while (line[x] != ' ')
            x--;
        x++;
        int depth = (line[x] - '0');
        for (x++; x < size; x++)
            depth *= 10 + (line[x] - '0');
        if (color == 'w')
        {
            unsigned long long tmp = bitBoard[16];
            moves = board.white_possible_moves(bitBoard);
            bitBoard[16] = tmp;
            res = get_num_of_moves_w(bitBoard, moves, depth);
        }
        else if (color == 'b')
        {
            moves = board.black_possible_moves(bitBoard);
            res = get_num_of_moves_b(bitBoard, moves, depth);
        }
        file.close();
        return res;
    }
} // namespace board
