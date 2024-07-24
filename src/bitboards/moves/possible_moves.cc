#include <cmath>
#include <vector>

#include "moves.hh"
#include "tool.hh"
#include "../bitboard.hh"
#include <cmath>

namespace board
{
    extern const std::vector<unsigned long long> White_pawn_moves =
        Move::white_pawn_moves();
    extern const std::vector<unsigned long long> Black_pawn_moves =
        Move::black_pawn_moves();

    unsigned long long
    black_king_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        unsigned long long black_king_attacks =
            board.black_king_attacks(bitBoard);
        for (unsigned long i = 0; i < 64; i++)
        {
            if (black_king_attacks & (un << i))
            {
                res |= (un << i);
            }
        }
        if (bitBoard[16] & un << 3)
        {
            bool castle_possible = true;
            for (unsigned long i = 58; i > 56; i--)
            {
                if (bitBoard[13] & un << i || bitBoard[6] & un << i)
                    castle_possible = false;
            }
            if (castle_possible)
            {
                if (!(bitBoard[14] & un << 57) && !(bitBoard[14] & un << 58)
                    && !(bitBoard[14] & un << 59))
                    res |= board.black_king_castling();
            }
        }
        if (bitBoard[16] & un << 1)
        {
            bool castle_possible = true;
            for (unsigned long i = 60; i < 63; i++)
            {
                if (bitBoard[13] & un << i || bitBoard[6] & un << i)
                    castle_possible = false;
            }
            if (castle_possible)
                if (!(bitBoard[14] & un << 60) && !(bitBoard[14] & un << 61)
                    && !(bitBoard[14] & un << 59))
                    res |= board.black_queen_castling();
        }
        return res;
    }

    unsigned long long
    white_king_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        unsigned long long white_king_attacks =
            board.white_king_attacks(bitBoard);
        for (unsigned long i = 0; i < 64; i++)
        {
            if (white_king_attacks & (un << i))
            {
                res |= (un << i);
            }
        }
        if (bitBoard[16] & un << 2)
        {
            bool castle_possible = true;
            for (unsigned long i = 2; i >= 1; i--)
            {
                if (bitBoard[6] & un << i || bitBoard[13] & un << i)
                    castle_possible = false;
            }
            if (castle_possible)
                if (!(bitBoard[15] & un << 1) && !(bitBoard[15] & un << 2)
                    && !(bitBoard[15] & un << 3))
                    res |= board.white_king_castling();
        }
        if (bitBoard[16] & un)
        {
            bool castle_possible = true;
            for (unsigned long i = 4; i <= 6; i++)
            {
                if (bitBoard[6] & un << i || bitBoard[13] & un << i)
                    castle_possible = false;
            }
            if (castle_possible)
                if (!(bitBoard[15] & un << 4) && !(bitBoard[15] & un << 5)
                    && !(bitBoard[15] & un << 3))
                    res |= board.white_queen_castling();
        }
        return res;
    }

    unsigned long long
    white_pawns_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        unsigned long long whitePawns = bitBoard[0];
        unsigned long long blackBoard = bitBoard[13];
        unsigned long long potential_attacks =
                     board.white_pawns_attacks(bitBoard);
        unsigned long long pawn_moves = 0;
        for (size_t i = 0; i < 64; i++)
        {
            if (potential_attacks & un << i && blackBoard & un << i)
            {
                    res |= un << i;
            }
            if (whitePawns & (un << i) && !(bitBoard[13] & un << (i + 8))
                && !(bitBoard[6] & un << (i + 8)))
            {
                pawn_moves |= White_pawn_moves[i];
            }
            if (whitePawns & un << i)
            {
                if (i >= 33 && i <= 39 && bitBoard[16] & un << (i - 1)
                    && !(bitBoard[13] & un << (i + 7))
                    && !(bitBoard[6] & un << (i + 7)))
                {
                    res |= un << (i + 7);
                }
                if (i >= 32 && i <= 38 && bitBoard[16] & un << (i + 1)
                    && !(bitBoard[13] & un << (i + 9))
                    && !(bitBoard[6] & un << (i + 9)))
                {
                    res |= un << (i + 9);
                }
            }
        }
        pawn_moves &= ~(bitBoard[13]);
        pawn_moves &= ~(bitBoard[6]);
        res |= pawn_moves;
        return res;
    }

    unsigned long long
    black_pawns_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long un = 1;
        board::Move board;
        unsigned long long blackPawns = bitBoard[7];
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long potential_attacks =
            board.black_pawns_attacks(bitBoard);
        unsigned long long pawn_moves = 0;
        for (size_t i = 0; i < 64; i++)
        {
            if (potential_attacks & un << i && whiteBoard & un << i)
            {
                    res |= un << i;
            }
            if (blackPawns & (un << i) && !(bitBoard[6] & un << (i - 8))
                && !(bitBoard[13] & un << (i - 8)))
            {
                pawn_moves |= Black_pawn_moves[i];
            }
            // en passant
            if (blackPawns & un << i)
            {
                if (i >= 24 && i <= 30 && bitBoard[16] & un << (i - 1)
                    && !(bitBoard[13] & un << (i - 9))
                    && !(bitBoard[6] & un << (i - 9)))
                {
                    res |= un << (i - 9);
                }
                if (i >= 25 && i <= 31 && bitBoard[16] & un << (i + 1)
                    && !(bitBoard[13] & un << (i - 7))
                    && !(bitBoard[6] & un << (i - 7)))
                {
                    res |= un << (i - 7);
                }
            }
        }
        pawn_moves &= ~(bitBoard[6]);
        pawn_moves &= ~(bitBoard[13]);
        res |= pawn_moves;
        return res;
    }

    struct pieces_moves &store_black_piece_attacked(
        std::vector<unsigned long long> &bitBoard,
        struct pieces_moves &m)
    {
        unsigned long long un = 1;
        unsigned long long taken = m.moved;
        if (m.report_type & un << 2)
            taken = taken >> 8;
        for (size_t i = 7; i < 13; i++)
        {
            if (taken & bitBoard[i])
            {
                m.report_type |= un << (i + 19);
                break;
            }
        }
        return m;
    }

    struct pieces_moves &store_white_piece_attacked(
        std::vector<unsigned long long> &bitBoard,
        struct pieces_moves &m)
    {
        size_t count = 9;
        unsigned long long un = 1;
        unsigned long long taken = m.moved;
        if (m.report_type & un << 6)
            taken = taken << 8;
        for (size_t i = 0; i < 6; i++)
        {
            if (i == 4)
                count += 20;
            if (i == 5)
                count -= 21;
            if (taken & bitBoard[i])
            {
                m.report_type |= un << (i + 20);
                break;
            }
        }
        return m;
    }

    std::vector<struct pieces_moves>
    &white_pawns_mask(std::vector<unsigned long long> &bitBoard,
                     unsigned long long i,
                      std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        unsigned long long tmp = 0;
        unsigned long long whitePawns = bitBoard[0];
        bitBoard[0] = un << i;
        tmp |= white_pawns_possible_moves(bitBoard);
        bitBoard[0] = whitePawns;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (!(m.moved & un << (i + 8)) && !(m.moved & un << (i + 16)))
                {
                    // en passant
                    if (!(m.moved & bitBoard[13]))
                        m.report_type |= un << 2;
                    // attack
                    else
                        m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                else
                {
                    if (m.moved & un << (i + 16))
                        m.report_type |= un << (j + 13);
                }
                m.report_type |= un << 9;
                unsigned long long tmp = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    m.report_type |= un << 3;
                bool stop = false;
                if (bitBoard[15] & bitBoard[5])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp;
                if (!stop)
                {
                    if (log2(m.moved) >= 56 && log2(m.moved) <= 63)
                    {
                        for (int x = 0; x < 3; x++)
                        {
                            struct pieces_moves promot = m;
                            promot.report_type |= un << (33 + x);
                            res.push_back(promot);
                        }
                        m.report_type |= un << 36;
                    }
                    res.push_back(m);
                }
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &black_pawns_mask(std::vector<unsigned long long> &bitBoard,
                     unsigned long long i,
                      std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        unsigned long long tmp = 0;
        unsigned long long blackPawns = bitBoard[7];
        bitBoard[7] = un << i;
        tmp |= black_pawns_possible_moves(bitBoard);
        bitBoard[7] = blackPawns;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                if (!(m.moved & un << (i - 8)) && !(m.moved & un << (i - 16)))
                {
                    // en passant
                    if (!(m.moved & bitBoard[6]))
                        m.report_type |= un << 6;
                    // attack
                    else
                        m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                else
                {
                    if (m.moved & un << (i - 16))
                        m.report_type |= un << (j + 13);
                }
                m.report_type |= un << 14;
                unsigned long long tmp = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    m.report_type |= un << 7;
                bool stop = false;
                if (bitBoard[12] & bitBoard[14])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp;
                if (!stop)
                {
                    if (log2(m.moved) >= 0 && log2(m.moved) <= 7)
                    {
                        for (int x = 0; x < 3; x++)
                        {
                            struct pieces_moves promot = m;
                            promot.report_type |= un << (33 + x);
                            res.push_back(promot);
                        }
                        m.report_type |= un << 36;
                    }
                    res.push_back(m);
                }
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &white_rooks_mask(std::vector<unsigned long long> &bitBoard,
                     unsigned long long i,
                      std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long rooks = bitBoard[1];
        bitBoard[1] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.white_rooks_attacks(bitBoard);
        bitBoard[1] = rooks;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[13])
                {
                    m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 10;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    m.report_type |= un << 3;
                bool stop = false;
                if (bitBoard[5] & bitBoard[15])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &black_rooks_mask(std::vector<unsigned long long> &bitBoard,
                     unsigned long long i,
                      std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long rooks = bitBoard[8];
        bitBoard[8] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.black_rooks_attacks(bitBoard);
        bitBoard[8] = rooks;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[6])
                {
                    m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 15;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    m.report_type |= un << 7;
                bool stop = false;
                if (bitBoard[12] & bitBoard[14])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &white_knights_mask(std::vector<unsigned long long> &bitBoard,
                       unsigned long long i,
                       std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long knights = bitBoard[2];
        bitBoard[2] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.white_knights_attacks(bitBoard);
        bitBoard[2] = knights;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[13])
                {
                    m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 11;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    m.report_type |= un << 3;
                bool stop = false;
                if (bitBoard[5] & bitBoard[15])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &black_knights_mask(std::vector<unsigned long long> &bitBoard,
                       unsigned long long i,
                       std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long knights = bitBoard[9];
        bitBoard[9] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.black_knights_attacks(bitBoard);
        bitBoard[9] = knights;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[6])
                {
                    m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 16;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    m.report_type |= un << 7;
                bool stop = false;
                if (bitBoard[12] & bitBoard[14])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &white_bishops_mask(std::vector<unsigned long long> &bitBoard,
                       unsigned long long i,
                       std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long bishops = bitBoard[3];
        bitBoard[3] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.white_bishops_attacks(bitBoard);
        bitBoard[3] = bishops;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[13])
                {
                    m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 32;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    m.report_type |= un << 3;
                bool stop = false;
                if (bitBoard[5] & bitBoard[15])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    &black_bishops_mask(std::vector<unsigned long long> &bitBoard,
                       unsigned long long i,
                       std::vector<struct pieces_moves> &res)
    {
        unsigned long long un = 1;
        board::Move board;
        unsigned long long bishops = bitBoard[10];
        bitBoard[10] = un << i;
        unsigned long long tmp = 0;
        tmp |= board.black_bishops_attacks(bitBoard);
        bitBoard[10] = bishops;
        for (unsigned long long j = 0; tmp != 0 && j < 64; j++)
        {
            if (tmp & (un << j))
            {
                struct pieces_moves m;
                m.initial = un << i;
                m.moved = un << j;
                m.report_type = 0;
                if (m.moved & bitBoard[6])
                {
                    m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 17;
                unsigned long long tmp2 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    m.report_type |= un << 7;
                bool stop = false;
                if (bitBoard[12] & bitBoard[14])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp2;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << j);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    Move::white_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        std::vector<struct pieces_moves> res;
        unsigned long long un = 1;
        unsigned long long whitePawns = bitBoard[0];
        unsigned long long whiteRooks = bitBoard[1];
        unsigned long long whiteKnights = bitBoard[2];
        unsigned long long whiteBishops = bitBoard[3];
        unsigned long long tmp2 = 0;
        tmp2 = white_king_possible_moves(bitBoard);
        unsigned long long tmp = 0;
        tmp = Move::white_queen_attacks(bitBoard);
        // white pawn moves
        for (unsigned long long i = 0; i < 64; i++)
        {
            if (whitePawns & (un << i))
            {
                res = white_pawns_mask(bitBoard, i, res);
            }
        // white rooks moves
            else if (whiteRooks & (un << i))
            {
                res = white_rooks_mask(bitBoard, i, res);
            }
        // white knight moves
            else if (whiteKnights & (un << i))
            {
                res = white_knights_mask(bitBoard, i, res);
            }
        // white bishops moves
            else if (whiteBishops & (un << i))
            {
                res = white_bishops_mask(bitBoard, i, res);
            }
        // white queen moves
            if (tmp != 0 && tmp & un << i)
            {
                struct pieces_moves m;
                m.initial = bitBoard[4];
                m.moved = un << i;
                m.report_type = 0;
                //if queen takes a piece
                if (m.moved & bitBoard[13])
                {
                    m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 12;
                unsigned long long tmp3 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    m.report_type |= un << 3;
                bool stop = false;
                if (bitBoard[5] & bitBoard[15])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp3;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << i);
            }
        // white king moves
            if (tmp2 != 0 && tmp2 & un << i)
            {
                bool impossible = false;
                struct pieces_moves m;
                m.initial = bitBoard[5];
                m.moved = un << i;
                m.report_type = 0;
                if (m.initial & un << 3)
                {
                    // if king castling
                    if (m.moved == un << 1)
                        m.report_type |= un;
                    // if queen castling
                    if (m.moved == un << 5)
                        m.report_type |= un << 1;
                }
                if (m.moved & bitBoard[13])
                {
                    m.report_type |= un << 8;
                    m = store_black_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 13;
                unsigned long long tmp3 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    impossible = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16]= tmp3;
                if (!impossible)
                    res.push_back(m);
                tmp2 &= ~(un << i);
            }
        }
        return res;
    }

    std::vector<struct pieces_moves>
    Move::black_possible_moves(std::vector<unsigned long long> &bitBoard)
    {
        std::vector<struct pieces_moves> res;
        unsigned long long un = 1;
        unsigned long long blackPawns = bitBoard[7];
        unsigned long long blackRooks = bitBoard[8];
        unsigned long long blackKnights = bitBoard[9];
        unsigned long long blackBishops = bitBoard[10];
        unsigned long long tmp2 = 0;
        tmp2 = black_king_possible_moves(bitBoard);
        unsigned long long tmp = 0;
        tmp = Move::black_queen_attacks(bitBoard);
        // black pawns moves
        for (unsigned long long i = 0; i < 64; i++)
        {
            if (blackPawns & (un << i))
            {
                res = black_pawns_mask(bitBoard, i, res);
            }
            // black rooks moves
            else if (blackRooks & (un << i))
            {
                res = black_rooks_mask(bitBoard, i, res);
            }
            // black knights moves
            else if (blackKnights & (un << i))
            {
                res = black_knights_mask(bitBoard, i, res);
            }
            // black bishops moves
            else if (blackBishops & (un << i))
            {
                res = black_bishops_mask(bitBoard, i, res);
            }
            // black queen moves
            if (tmp != 0 && tmp & un << i)
            {
                struct pieces_moves m;
                m.initial = bitBoard[11];
                m.moved = un << i;
                m.report_type = 0;
                //if queen takes a piece
                if (m.moved & bitBoard[6])
                {
                    m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 18;
                unsigned long long tmp3 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[15] & bitBoard[5])
                    m.report_type |= un << 7;
                bool stop = false;
                if (bitBoard[12] & bitBoard[14])
                    stop = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp3;
                if (!stop)
                    res.push_back(m);
                tmp &= ~(un << i);
            }
            // black king moves
            if (tmp2 != 0 && tmp2 & un << i)
            {
                bool impossible = false;
                struct pieces_moves m;
                m.initial = bitBoard[12];
                m.moved = un << i;
                m.report_type = 0;
                if (m.initial & un << 59)
                {
                    // if king castling
                    if (m.moved == un << 57)
                        m.report_type |= un << 4;
                    // if queen castling
                    if (m.moved == un << 61)
                        m.report_type |= un << 5;
                }
                if (m.moved & bitBoard[6])
                {
                    m.report_type |= un << 8;
                    m = store_white_piece_attacked(bitBoard, m);
                }
                m.report_type |= un << 19;
                unsigned long long tmp3 = bitBoard[16];
                bitBoard = do_move(bitBoard, m);
                if (bitBoard[14] & bitBoard[12])
                    impossible = true;
                bitBoard = undo_move(bitBoard, m);
                bitBoard[16] = tmp3;
                if (!impossible)
                    res.push_back(m);
                tmp2 &= ~(un << i);
            }
        }
        return res;
    }
} // namespace board
