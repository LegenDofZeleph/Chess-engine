#include "tool.hh"
#include "../bitboard.hh"
namespace board
{
    std::vector<unsigned long long>
    &add_piece(std::vector<unsigned long long> &bitBoard, size_t i, size_t t)
    {
        unsigned long long un = 1;
        if (t <= 5)
        {
            bitBoard[t] |= un << i;
            bitBoard[6] |= un << i;
        }
        else if (t > 6 && t <= 12)
        {
            bitBoard[t] |= un << i;
            bitBoard[13] |= un << i;
        }
        return bitBoard;
    }

    std::vector<unsigned long long>
    &del_piece(std::vector<unsigned long long> &bitBoard, size_t i, size_t t)
    {
        unsigned long long un = 1;
        if (t <= 5)
        {
            bitBoard[t] &= ~(un << i);
            bitBoard[6] &= ~(un << i);
        }
        else if (t > 6 && t <= 12)
        {
            bitBoard[t] &= ~(un << i);
            bitBoard[13] &= ~(un << i);
        }
        return bitBoard;
    }

    std::vector<unsigned long long>
    &do_move(std::vector<unsigned long long> &bitBoard,
                   struct pieces_moves &p)
    {
        board::Move board;
        bool color = true; // white
        unsigned long long un = 1;
        size_t k = 0;
        size_t promotion = 0;
        while ((un << k) != p.initial)
        {
            k++;
        }
        if ((un << k) & bitBoard[13])
            color = false;
        size_t m = 0;
        while ((un << m) != p.moved)
        {
            m++;
        }
        for (size_t x = 4; x <= 7; x++)
            bitBoard[16] &= ~(un << x);
        //promotions
        for (int k = 33; k <= 36; k++)
        {
            if (p.report_type & un << k)
                promotion = k - 32;
        }
        if (color)
        {
            if (p.report_type & un << 8 || p.report_type & un << 2)
            {
                size_t piece_taken = 7;
                while (!(p.report_type & un << (piece_taken + 19)))
                {
                    piece_taken++;
                }
                // if en passant blanc
                size_t taken_en_passant = m;
                if (p.report_type & un << 2)
                {
                    taken_en_passant = taken_en_passant - 8;
                }
                bitBoard = del_piece(bitBoard, taken_en_passant, piece_taken);
            }
            size_t piece_taking = 0;
            size_t count = 9;
            if (promotion == 0)
            {
                while (!(p.report_type & un << (piece_taking + count)))
                {
                    piece_taking++;
                    if (piece_taking == 3)
                        count += 20;
                    if (piece_taking == 4)
                        count -= 21;
                }
            }
            // setting of white queen castling
            if (bitBoard[16] & un)
            {
                if (piece_taking == 5 && m == 5)
                {
                    bitBoard = add_piece(bitBoard, 4, 1);
                    bitBoard = del_piece(bitBoard, 7, 1);
                    bitBoard[16] &= ~(un);
                    bitBoard[16] |= (un << 4);
                }
                else if (piece_taking == 5 ||
                    (piece_taking == 1 && p.initial & un << 7))
                {
                    bitBoard[16] &= ~(un);
                    bitBoard[16] |= (un << 4);
                }
            }
            // setting of white king castling
            if (bitBoard[16] & un << 2)
            {
                if (piece_taking == 5 && m == 1)
                {
                    bitBoard = add_piece(bitBoard, 2, 1);
                    bitBoard = del_piece(bitBoard, 0, 1);
                    bitBoard[16] &= ~(un << 2);
                    bitBoard[16] |= (un << 6);
                }
                else if (piece_taking == 5 ||
                    (piece_taking == 1 && p.initial & un))
                {
                    bitBoard[16] &= ~(un << 2);
                    bitBoard[16] |= (un << 6);
                }
            }
            size_t piece_to_add = piece_taking;
            if (promotion != 0)
                piece_to_add = promotion;
            bitBoard = add_piece(bitBoard, m, piece_to_add);
            bitBoard = del_piece(bitBoard, k, piece_taking);
        }
        else
        {
            if (p.report_type & un << 8 || p.report_type & un << 6)
            {
                size_t piece_taken = 0;
                while (!(p.report_type & un << (piece_taken + 20)))
                {
                    piece_taken++;
                }
                // if en passant noir
                size_t taken_en_passant = m;
                if (p.report_type & un << 6)
                    taken_en_passant = taken_en_passant + 8;
                bitBoard = del_piece(bitBoard, taken_en_passant, piece_taken);
            }
            size_t piece_taking = 7;
            if (promotion == 0)
            {
                while (!(p.report_type & un << (piece_taking + 7)))
                {
                    piece_taking++;
                }
            }
            //settings of black queen castling
            if (bitBoard[16] & un << 1)
            {
                if (piece_taking == 12 && m == 61)
                {
                    bitBoard = add_piece(bitBoard, 60, 8);
                    bitBoard = del_piece(bitBoard, 63, 8);
                    bitBoard[16] &= ~(un << 1);
                    bitBoard[16] |= (un << 5);
                }
                else if (piece_taking == 12 ||
                    (piece_taking == 8 && p.initial & un << 63))
                {
                    bitBoard[16] &= ~(un << 1);
                    bitBoard[16] |= (un << 5);
                }
            }
            //settings of black king castling
            if (bitBoard[16] & un << 3)
            {
                if (piece_taking == 12 && m == 57)
                {
                    bitBoard = add_piece(bitBoard, 58, 8);
                    bitBoard = del_piece(bitBoard, 56, 8);
                    bitBoard[16] &= ~(un << 3);
                    bitBoard[16] |= (un << 7);
                }
                else if (piece_taking == 12 ||
                    (piece_taking == 8 && p.initial & un << 56))
                {
                    bitBoard[16] &= ~(un << 3);
                    bitBoard[16] |= (un << 7);
                }
            }
            size_t piece_to_add = piece_taking;
            if (promotion != 0)
                piece_to_add = promotion + 7;
            bitBoard = add_piece(bitBoard, m, piece_to_add);
            bitBoard = del_piece(bitBoard, k, piece_taking);
        }
        // si un pion a avance de 2 alors set up le en passant
        for (size_t z = 37; z <= 52; z++)
        {
            bitBoard[16] &= ~(un << (z - 13));
        }
        for (size_t y = 37; y <= 52; y++)
        {
            if (p.report_type & un << y)
                bitBoard[16] |= un << (y - 13);
        }
        bitBoard = board.white_attacks(bitBoard);
        bitBoard = board.black_attacks(bitBoard);
        return bitBoard;
    }

    std::vector<unsigned long long>
    &undo_move(std::vector<unsigned long long> &bitBoard,
               struct pieces_moves &p)
    {
        board::Move board;
        bool color = true; // white
        unsigned long long un = 1;
        size_t m = 0;
        size_t promotion = 0;
        while ((un << m) != p.moved)
        {
            m++;
        }
        if ((un << m) & bitBoard[13])
            color = false;
        size_t k = 0;
        while ((un << k) != p.initial)
        {
            k++;
        }
        for (size_t x = 24; x <= 39; x++)
        {
            if (bitBoard[16] & un << x)
            {
                bitBoard[16] &= ~(un << x);
            }
        }
        //promotions
        for (int k = 33; k <= 36; k++)
        {
            if (p.report_type & un << k)
                promotion = k - 32;
        }
        if (color)
        {
            size_t piece_taking = 0;
            size_t count = 9;
            if (promotion == 0)
            {
                while (!(p.report_type & un << (piece_taking + count)))
                {
                    piece_taking++;
                    if (piece_taking == 3)
                        count += 20;
                    if (piece_taking == 4)
                        count -= 21;
                }
            }
            size_t piece_to_del = piece_taking;
            if (promotion != 0)
            {
                piece_to_del = promotion;
            }
            bitBoard = del_piece(bitBoard, m, piece_to_del);
            // setting of white queen castling
            if (bitBoard[16] & un << 4)
            {
                if (piece_taking == 5 && m == 5)
                {
                    bitBoard = add_piece(bitBoard, 7, 1);
                    bitBoard = del_piece(bitBoard, 4, 1);
                    bitBoard[16] |= (un);
                    bitBoard[16] &= ~(un << 4);
                }
                else
                {
                    bitBoard[16] |= (un);
                    bitBoard[16] &= ~(un << 4);
                }
            }
            //settings of white king castling
            if (bitBoard[16] & un << 6)
            {
                if (piece_taking == 5 && m == 1)
                {
                    bitBoard = add_piece(bitBoard, 0, 1);
                    bitBoard = del_piece(bitBoard, 2, 1);
                    bitBoard[16] |= (un << 2);
                    bitBoard[16] &= ~(un << 6);
                }
                else
                {
                    bitBoard[16] |= (un << 2);
                    bitBoard[16] &= ~(un << 6);
                }
            }
            if (p.report_type & un << 8 || p.report_type & un << 2)
            {
                size_t piece_taken = 7;
                while (!(p.report_type & un << (piece_taken + 19)))
                {
                    piece_taken++;
                }
                // if en passant blanc
                unsigned long long taken_en_passant = m;
                if (p.report_type & un << 2)
                    taken_en_passant = taken_en_passant - 8;
                bitBoard = add_piece(bitBoard, taken_en_passant, piece_taken);
            }
            size_t piece_to_add = piece_taking;
            if (promotion != 0)
                piece_to_add = 0;
            bitBoard = add_piece(bitBoard, k, piece_to_add);
        }
        else
        {
            size_t piece_taking = 7;
            if (promotion == 0)
            {
                while (!(p.report_type & un << (piece_taking + 7)))
                {
                    piece_taking++;
                }
            }
            size_t piece_to_del = piece_taking;
            if (promotion != 0)
            {
                piece_to_del = promotion + 7;
            }
            bitBoard = del_piece(bitBoard, m, piece_to_del);
            // setting of black queen castling
            if (bitBoard[16] & un << 5)
            {
                if (piece_taking == 12 && m == 61)
                {
                    bitBoard = add_piece(bitBoard, 63, 8);
                    bitBoard = del_piece(bitBoard, 60, 8);
                    bitBoard[16] |= (un << 1);
                    bitBoard[16] &= ~(un << 5);
                }
                else
                {
                    bitBoard[16] |= (un << 1);
                    bitBoard[16] &= ~(un << 5);
                }
            }
            //settings of black king castling
            if (bitBoard[16] & un << 7)
            {
                if (piece_taking == 12 && m == 57)
                {
                    bitBoard = add_piece(bitBoard, 56, 8);
                    bitBoard = del_piece(bitBoard, 58, 8);
                    bitBoard[16] |= (un << 3);
                    bitBoard[16] &= ~(un << 7);
                }
                else
                {
                    bitBoard[16] |= (un << 3);
                    bitBoard[16] &= ~(un << 7);
                }
            }
            if (p.report_type & un << 8 || p.report_type & un << 6)
            {
                size_t piece_taken = 0;
                while (!(p.report_type & un << (piece_taken + 20)))
                {
                    piece_taken++;
                }
                // if en passant blanc
                unsigned long long taken_en_passant = m;
                if (p.report_type & un << 6)
                    taken_en_passant = taken_en_passant + 8;
                bitBoard = add_piece(bitBoard, taken_en_passant, piece_taken);
            }
            size_t piece_to_add = piece_taking;
            if (promotion != 0)
                piece_to_add = 7;
            bitBoard = add_piece(bitBoard, k, piece_to_add);
        }
        bitBoard = board.white_attacks(bitBoard);
        bitBoard = board.black_attacks(bitBoard);
        return bitBoard;
    }
} // namespace board
