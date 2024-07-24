#include <cmath>

#include "moves.hh"

namespace board
{
    extern const std::vector<unsigned long long> Knight_moves =
        Move::knight_moves();
    extern const std::vector<unsigned long long> King_moves =
        Move::king_moves();

    unsigned long long
    Move::white_pawns_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long whitePawnsPos = bitBoard[0];
        for (unsigned long long i = 0; i <= 55; i++)
        {
            if (whitePawnsPos & (un << i))
            {
                // if not in the right colon we can move on upward right
                // diagonal
                unsigned long long x = whiteBoard;
                x &= (un << (i + 7));
                if (i % 8 != 0 && !(x & (un << (i + 7))))
                {
                    tmp = i + 7;
                    res |= un << tmp;
                }
                unsigned long long y = whiteBoard;
                y &= (un << (i + 9));
                // if not in the left colon we can move on upward left diagonal
                if (i % 8 != 7 && !(y & (un << (i + 9))))
                {
                    tmp = i + 9;
                    res |= un << tmp;
                }
            }
        }
        return res;
    }

    unsigned long long
    Move::black_pawns_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long tmp;
        unsigned long long un = 1;
        unsigned long long blackBoard = bitBoard[13];
        unsigned long long blackPawnsPos = bitBoard[7];
        for (unsigned long long i = 63; i >= 8; i--)
        {
            if (blackPawnsPos & (un << i))
            {
                // if not in the right colon we can move on backward right
                // diagonal
                unsigned long long x = blackBoard;
                x &= (un << (i - 9));
                if (i % 8 != 0 && !(x & (un << (i - 9))))
                {
                    tmp = i - 9;
                    res |= un << tmp;
                }
                // if not in the left colon we can move on backward left
                // diagonal
                unsigned long long y = blackBoard;
                y &= (un << (i - 7));
                if (i % 8 != 7 && !(y & (un << (i - 7))))
                {
                    tmp = i - 7;
                    res |= un << tmp;
                }
            }
        }
        return res;
    }

    unsigned long long
    _white_rooks_attacks(std::vector<unsigned long long> &bitBoard,
                         unsigned long long pos)
    {
        unsigned long long tab = 0;
        unsigned long long un = 1;
        unsigned long long rooksPos = pos;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long blackBoard = bitBoard[13];
        int i;
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                int j = i;
                bool stop = true;
                if (i < 56)
                {
                    j = i + 8;
                    stop = false;
                }
                while (!stop)
                {
                    if (whiteBoard & (un << j))
                    {
                        stop = true;
                    }
                    else if (blackBoard & (un << j))
                    {
                        tab |= un << j;
                        stop = true;
                    }
                    else if (j < i % 8 + 56)
                    {
                        tab |= un << j;
                        j += 8;
                    }
                    else if (j == i % 8 + 56)
                    {
                        tab |= un << j;
                        stop = true;
                    }
                }
            }
        }
        for (i = 63; i >= 0; i--)
        {
            int j = i;
            if (rooksPos & (un << j))
            {
                bool stop = true;
                if (i > 7)
                {
                    j = i - 8;
                    stop = false;
                }
                while (!stop)
                {
                    if (whiteBoard & (un << j))
                    {
                        stop = true;
                    }
                    else if (blackBoard & (un << j))
                    {
                        tab |= un << j;
                        stop = true;
                    }
                    else if (j > i % 8)
                    {
                        tab |= un << j;
                        j -= 8;
                    }
                    else if (j == i % 8)
                    {
                        tab |= un << j;
                        stop = true;
                    }
                }
            }
        }
        tab &= ~(un << i);
        // possible moves of rook bacward
        // possible moves of rook on the right
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                if (i % 8 != 0)
                {
                    for (unsigned long long j = i - 1; j % 8 != 7; j--)
                    {
                        if (whiteBoard & (un << j))
                            break;
                        tab |= un << j;
                        if (blackBoard & (un << j))
                            break;
                    }
                }
            }
        }
        // possible moves of rook on the left
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                if (i % 8 != 7)
                {
                    for (unsigned long long j = i + 1; j % 8 != 0; j++)
                    {
                        if (whiteBoard & (un << j))
                            break;
                        tab |= un << j;
                        if (blackBoard & (un << j))
                            break;
                    }
                }
            }
        }
        return tab;
    }

    unsigned long long
    Move::white_rooks_attacks(std::vector<unsigned long long> &bitBoard)
    {
        return _white_rooks_attacks(bitBoard, bitBoard[1]);
    }

    unsigned long long
    _black_rooks_attacks(std::vector<unsigned long long> &bitBoard,
                         unsigned long long pos)
    {
        unsigned long long tab = 0;
        unsigned long long un = 1;
        unsigned long long rooksPos = pos;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long blackBoard = bitBoard[13];
        int i;
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                int j;
                bool stop = true;
                if (i < 56)
                {
                    j = i + 8;
                    stop = false;
                }
                while (!stop)
                {
                    if (blackBoard & (un << j))
                    {
                        stop = true;
                    }
                    else if (whiteBoard & (un << j))
                    {
                        tab |= un << j;
                        stop = true;
                    }
                    else if (j < i % 8 + 56)
                    {
                        tab |= un << j;
                        j += 8;
                    }
                    else if (j == i % 8 + 56)
                    {
                        tab |= un << j;
                        stop = true;
                    }
                }
            }
        }
        for (i = 63; i >= 0; i--)
        {
            int j = i;
            if (rooksPos & (un << j))
            {
                bool stop = true;
                if (i > 7)
                {
                    j = i - 8;
                    stop = false;
                }
                while (!stop)
                {
                    if (blackBoard & (un << j))
                    {
                        stop = true;
                    }
                    else if (whiteBoard & (un << j))
                    {
                        tab |= un << j;
                        stop = true;
                    }
                    else if (j > i % 8)
                    {
                        tab |= un << j;
                        j -= 8;
                    }
                    else if (j == i % 8)
                    {
                        tab |= un << j;
                        stop = true;
                    }
                }
            }
        }
        tab &= ~(un << i);
        // possible moves of rook bacward
        // possible moves of rook on the right
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                if (i % 8 != 0)
                {
                    for (unsigned long long j = i - 1; j % 8 != 7; j--)
                    {
                        if (blackBoard & (un << j))
                            break;
                        tab |= un << j;
                        if (whiteBoard & (un << j))
                            break;
                    }
                }
            }
        }
        // possible moves of rook on the left
        for (i = 0; i < 64; i++)
        {
            if (rooksPos & (un << i))
            {
                if (i % 8 != 7)
                {
                    for (unsigned long long j = i + 1; j % 8 != 0; j++)
                    {
                        if (blackBoard & (un << j))
                            break;
                        tab |= un << j;
                        if (whiteBoard & (un << j))
                            break;
                    }
                }
            }
        }
        return tab;
    }

    unsigned long long
    Move::black_rooks_attacks(std::vector<unsigned long long> &bitBoard)
    {
        return _black_rooks_attacks(bitBoard, bitBoard[8]);
    }

    unsigned long long
    _white_bishops_attacks(std::vector<unsigned long long> &bitBoard,
                           unsigned long long pos)
    {
        unsigned long long un = 1;
        unsigned long long tab = 0;
        unsigned long long bishopsPos = pos;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long blackBoard = bitBoard[13];
        for (unsigned long long i = 0; i < 64; i++)
        {
            if (bishopsPos & (un << i))
            {
                // backward right diagonal
                if (i > 8 && i % 8 != 0)
                {
                    bool stop = false;
                    unsigned long long j = i - 9;
                    while (!stop)
                    {
                        if (whiteBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (blackBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j >= 9 && j % 8 != 0)
                                j -= 9;
                            else
                                stop = true;
                        }
                    }
                }
                // backward left diagonal
                if (i > 7 && i % 8 != 7)
                {
                    unsigned long long j = i - 7;
                    bool stop = false;
                    while (!stop)
                    {
                        if (whiteBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (blackBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j > 7 && j % 8 != 7)
                                j -= 7;
                            else
                                stop = true;
                        }
                    }
                }
                // forward right diagonal
                if (i < 56 && i % 8 != 0)
                {
                    unsigned long long j = i + 7;
                    bool stop = false;
                    while (!stop)
                    {
                        if (whiteBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (blackBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j < 56 && j % 8 != 0)
                                j += 7;
                            else
                                stop = true;
                        }
                    }
                }
                // forward left diagonal
                if (i < 56 && i % 8 != 7)
                {
                    unsigned long long j = i + 9;
                    bool stop = false;
                    while (!stop)
                    {
                        if (whiteBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (blackBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j < 55 && j % 8 != 7)
                                j += 9;
                            else
                                stop = true;
                        }
                    }
                }
            }
        }
        return tab;
    }

    unsigned long long
    Move::white_bishops_attacks(std::vector<unsigned long long> &bitBoard)
    {
        return _white_bishops_attacks(bitBoard, bitBoard[3]);
    }

    unsigned long long
    _black_bishops_attacks(std::vector<unsigned long long> &bitBoard,
                           unsigned long long pos)
    {
        unsigned long long un = 1;
        unsigned long long tab = 0;
        unsigned long long bishopsPos = pos;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long blackBoard = bitBoard[13];
        for (unsigned long long i = 0; i < 64; i++)
        {
            if (bishopsPos & (un << i))
            {
                // backward right diagonal
                if (i > 8 && i % 8 != 0)
                {
                    bool stop = false;
                    unsigned long long j = i - 9;
                    while (!stop)
                    {
                        if (blackBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (whiteBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j >= 9 && j % 8 != 0)
                                j -= 9;
                            else
                                stop = true;
                        }
                    }
                }
                // backward left diagonal
                if (i > 7 && i % 8 != 7)
                {
                    unsigned long long j = i - 7;
                    bool stop = false;
                    while (!stop)
                    {
                        if (blackBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (whiteBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j > 7 && j % 8 != 7)
                                j -= 7;
                            else
                                stop = true;
                        }
                    }
                }
                // forward right diagonal
                if (i < 56 && i % 8 != 0)
                {
                    unsigned long long j = i + 7;
                    bool stop = false;
                    while (!stop)
                    {
                        if (blackBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (whiteBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j < 56 && j % 8 != 0)
                                j += 7;
                            else
                                stop = true;
                        }
                    }
                }
                // forward left diagonal
                if (i < 56 && i % 8 != 7)
                {
                    unsigned long long j = i + 9;
                    bool stop = false;
                    while (!stop)
                    {
                        if (blackBoard & (un << j))
                        {
                            stop = true;
                        }
                        else if (whiteBoard & (un << j))
                        {
                            tab |= un << j;
                            stop = true;
                        }
                        else
                        {
                            tab |= un << j;
                            if (j < 55 && j % 8 != 7)
                                j += 9;
                            else
                                stop = true;
                        }
                    }
                }
            }
        }
        return tab;
    }

    unsigned long long
    Move::black_bishops_attacks(std::vector<unsigned long long> &bitBoard)
    {
        return _black_bishops_attacks(bitBoard, bitBoard[10]);
    }

    unsigned long long
    Move::white_queen_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        res |= _white_rooks_attacks(bitBoard, bitBoard[4]);
        res |= _white_bishops_attacks(bitBoard, bitBoard[4]);
        return res;
    }

    unsigned long long
    Move::black_queen_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        res |= _black_rooks_attacks(bitBoard, bitBoard[11]);
        res |= _black_bishops_attacks(bitBoard, bitBoard[11]);
        return res;
    }

    unsigned long long
    Move::white_king_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long kingPos = bitBoard[5];
        unsigned long long un = 1;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long i = 0;
        for (; i < 64; i++)
        {
            if (kingPos & (un << i))
            {
                res |= King_moves[i];
                break;
            }
        }
        res &= ~(whiteBoard);
        return res;
    }

    unsigned long long
    Move::black_king_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long kingPos = bitBoard[12];
        unsigned long long un = 1;
        unsigned long long blackBoard = bitBoard[13];
        unsigned long long i = 0;
        for (; i < 64; i++)
        {
            if (kingPos & (un << i))
            {
                res |= King_moves[i];
                break;
            }
        }
        res &= ~(blackBoard);
        return res;
    }

    unsigned long long
    Move::white_knights_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long knightPos = bitBoard[2];
        unsigned long long un = 1;
        unsigned long long whiteBoard = bitBoard[6];
        unsigned long long i = 0;
        for (; i < 64; i++)
        {
            if (knightPos & (un << i))
            {
                res |= Knight_moves[i];
            }
        }
        res &= ~(whiteBoard);
        return res;
    }

    unsigned long long
    Move::black_knights_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        unsigned long long knightPos = bitBoard[9];
        unsigned long long un = 1;
        unsigned long long blackBoard = bitBoard[13];
        unsigned long long i = 0;
        for (; i < 64; i++)
        {
            if (knightPos & (un << i))
            {
                res |= Knight_moves[i];
            }
        }
        res &= ~(blackBoard);
        return res;
    }
    std::vector<unsigned long long>
    &Move::white_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        res |= Move::white_pawns_attacks(bitBoard);
        res |= Move::white_rooks_attacks(bitBoard);
        res |= Move::white_knights_attacks(bitBoard);
        res |= Move::white_bishops_attacks(bitBoard);
        res |= Move::white_queen_attacks(bitBoard);
        res |= Move::white_king_attacks(bitBoard);
        bitBoard[14] = res;
        return bitBoard;
    }

    std::vector<unsigned long long>
    &Move::black_attacks(std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long res = 0;
        res |= Move::black_pawns_attacks(bitBoard);
        res |= Move::black_rooks_attacks(bitBoard);
        res |= Move::black_knights_attacks(bitBoard);
        res |= Move::black_bishops_attacks(bitBoard);
        res |= Move::black_queen_attacks(bitBoard);
        res |= Move::black_king_attacks(bitBoard);
        bitBoard[15] = res;
        return bitBoard;
    }
} // namespace board
