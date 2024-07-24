#include "pgn.hh"

#include <fstream>
#include <iostream>
#include <vector>
namespace board
{
    size_t file_to_bit(board::File f)
    {
        size_t res = 0;
        // letter parse
        if (f == board::File::H)
            res += 0;
        else if (f == board::File::G)
            res += 1;
        else if (f == board::File::F)
            res += 2;
        else if (f == board::File::E)
            res += 3;
        else if (f == board::File::D)
            res += 4;
        else if (f == board::File::C)
            res += 5;
        else if (f == board::File::B)
            res += 6;
        else if (f == board::File::A)
            res += 7;
        return res;
    }

    size_t play_to_bit(std::string &s, size_t a, size_t b)
    {
        size_t res = 0;
        // letter parse
        if (s[a] == 'h')
            res += 0;
        else if (s[a] == 'g')
            res += 1;
        else if (s[a] == 'f')
            res += 2;
        else if (s[a] == 'e')
            res += 3;
        else if (s[a] == 'd')
            res += 4;
        else if (s[a] == 'c')
            res += 5;
        else if (s[a] == 'b')
            res += 6;
        else if (s[a] == 'a')
            res += 7;
        // number parse
        if (s[b] == '1')
            res += 0;
        else if (s[b] == '2')
            res += 8;
        else if (s[b] == '3')
            res += 16;
        else if (s[b] == '4')
            res += 24;
        else if (s[b] == '5')
            res += 32;
        else if (s[b] == '6')
            res += 40;
        else if (s[b] == '7')
            res += 48;
        else if (s[b] == '8')
            res += 56;

        return res;
    }

    size_t rank_to_bit(board::Rank r)
    {
        // number parse
        size_t res = 0;
        if (r == board::Rank::ONE)
            res += 0;
        else if (r == board::Rank::TWO)
            res += 8;
        else if (r == board::Rank::THREE)
            res += 16;
        else if (r == board::Rank::FOUR)
            res += 24;
        else if (r == board::Rank::FIVE)
            res += 32;
        else if (r == board::Rank::SIX)
            res += 40;
        else if (r == board::Rank::SEVEN)
            res += 48;
        else if (r == board::Rank::EIGHT)
            res += 56;

        return res;
    }

    int piecetype_manager(std::string &line, int i)
    {
        if (line[i] == 'R')
            return 1;
        else if (line[i] == 'N')
            return 2;
        else if (line[i] == 'B')
            return 3;
        else if (line[i] == 'Q')
            return 4;
        else if (line[i] == 'K')
            return 5;
        return 0;
    }
    size_t get_piece_type(PieceType piece, bool color)
    {
        if (color)
        {
            if (piece == PieceType::PAWN)
                return 9;
            else if (piece == PieceType::ROOK)
                return 10;
            else if (piece == PieceType::BISHOP)
                return 32;
            else if (piece == PieceType::KNIGHT)
                return 11;
            else if (piece == PieceType::QUEEN)
                return 12;
            else
                return 13;
        }
        else
        {
            if (piece == PieceType::PAWN)
                return 14;
            else if (piece == PieceType::ROOK)
                return 15;
            else if (piece == PieceType::BISHOP)
                return 17;
            else if (piece == PieceType::KNIGHT)
                return 16;
            else if (piece == PieceType::QUEEN)
                return 18;
            else
                return 19;
        }
    }

    size_t get_taken_piece(std::vector<unsigned long long> &bitboard,
                           bool color, unsigned long long pos)
    {
        int i = 0;
        if (color)
        {
            for (; i < 6; i++)
            {
                if (bitboard[i + 7] & pos)
                    return i + 26;
            }
        }
        else
        {
            for (; i < 6; i++)
            {
                if (bitboard[i] & pos)
                    return i + 20;
            }
        }
        return i;
    }
    PieceType pos_to_type_(int pos)
    {
        if (pos == 0)
        {
            return board::PieceType::PAWN;
        }
        else if (pos == 1)
        {
            return board::PieceType::ROOK;
        }
        else if (pos == 2)
        {
            return board::PieceType::KNIGHT;
        }
        else if (pos == 3)
        {
            return board::PieceType::BISHOP;
        }
        else if (pos == 4)
        {
            return board::PieceType::QUEEN;
        }
        else
        {
            return board::PieceType::KING;
        }
    }

    PieceType pos_to_type(int pos, std::vector<unsigned long long> &bitBoard)
    {
        unsigned long long un = 1;
        PieceType res = board::PieceType::PAWN;
        if (bitBoard[6] & un << pos)
        {
            for (int i = 0; i < 6; i++)
            {
                if (bitBoard[i] & un << pos)
                {
                    res = pos_to_type_(i);
                    break;
                }
            }
        }
        else if (bitBoard[13] & un << pos)
        {
            for (int i = 7; i < 13; i++)
            {
                if (bitBoard[i] & un << pos)
                {
                    res = pos_to_type_(i - 7);
                    break;
                }
            }
        }
        return res;
    }

    pieces_moves move_from_pgn(board::PgnMove &move,
                               std::vector<unsigned long long> &bitboard)
    {
        unsigned long long un = 1;
        pieces_moves m;
        size_t res = 0;
        bool color = true;
        board::Position start = move.start_get();
        board::Position end = move.end_get();
        res += rank_to_bit(start.rank_get());
        res += file_to_bit(start.file_get());
        size_t init = res;
        m.initial = un << res;
        res = rank_to_bit(end.rank_get());
        res += file_to_bit(end.file_get());
        m.moved = un << res;
        if (m.initial & bitboard[13])
            color = false;
        if (move.report_get() != ReportType::NONE)
        {
            if (color)
                m.report_type |= un << 3;
            else
                m.report_type |= un << 7;
        }
        PieceType piece = move.piece_get();
        size_t t = get_piece_type(piece, color);
        m.report_type |= un << t;
        if (t == 9 && init == res - 16)
            m.report_type |= un << (res + 13);
        if (t == 14 && init == res + 16)
            m.report_type |= un << (res + 13);
        // white king castle
        if (t == 13 && init == 3 && res == 1)
            m.report_type |= un;
        // white queen castle
        else if (t == 13 && init == 3 && res == 5)
            m.report_type |= un << 1;
        // black king castle
        else if (t == 19 && init == 59 && res == 57)
            m.report_type |= un << 4;
        // black queen castle
        else if (t == 19 && init == 59 && res == 61)
            m.report_type |= un << 5;
        std::optional<PieceType> prom = move.promotion_get();
        if (prom.has_value())
        {
            if (prom.value() == PieceType::ROOK)
                res = 33;
            else if (prom.value() == PieceType::KNIGHT)
                res = 34;
            else if (prom.value() == PieceType::BISHOP)
                res = 35;
            else if (prom.value() == PieceType::QUEEN)
                res = 36;
            m.report_type |= un << res;
        }
        // is taken part
        /*size_t taken = get_taken_piece(bitboard, color, m.moved);
        if (taken != 0)
        {
            m.report_type |= un << taken;
            }*/
        // else
        if (move.capture_get())
        {
            size_t taken = get_taken_piece(bitboard, color, m.moved);
            if (taken < 20)
            {
                // en passant
                if (color)
                {
                    m.report_type |= un << 26;
                    m.report_type |= un << 2;
                    m.report_type &= ~(un << 8);
                }
                else
                {
                    m.report_type |= un << 20;
                    m.report_type |= un << 6;
                    m.report_type &= ~(un << 8);
                }
            }
            else
            {
                m.report_type |= un << 8;
                m.report_type |= un << taken;
            }
        }
        return m;
    }

    void listeners(std::string &s, listener::Listener *list)
    {
        board::Move board;
        std::vector<unsigned long long> bitBoard = BitB::init_bitboard();
        auto pgn_moves = pgn_parser::parse_pgn(s);
        list->on_game_started();
        bool stop = false;
        unsigned long long un = 1;
        size_t size = pgn_moves.size();
        for (size_t i = 0; i < size; i++)
        {
            struct pieces_moves move = move_from_pgn(pgn_moves[i], bitBoard);
            std::vector<pieces_moves> possible_moves;
            board::Color side;
            if (i % 2 == 0)
            {
                possible_moves = board.white_possible_moves(bitBoard);
                side = board::Color::WHITE;
            }
            else
            {
                possible_moves = board.black_possible_moves(bitBoard);
                side = board::Color::BLACK;
            }
            bool found = false;
            struct pieces_moves p;
            for (auto k : possible_moves)
            {
                if (k.initial == move.initial && k.moved == move.moved
                    && k.report_type == move.report_type)
                {
                    found = true;
                    p = k;
                    break;
                }
            }
            if (found)
            {
                // if the moves is a castling
                if (p.report_type & un || p.report_type & un << 1
                    || p.report_type & un << 4 || p.report_type & un << 5)
                {
                    list->on_piece_moved(board::PieceType::KING,
                                         pgn_moves[i].start_get(),
                                         pgn_moves[i].end_get());
                    if (i % 2 == 0)
                        side = board::Color::WHITE;
                    else
                        side = board::Color::BLACK;
                    if (p.report_type & un || p.report_type & un << 4)
                    {
                        list->on_kingside_castling(side);
                    }
                    else
                    {
                        list->on_queenside_castling(side);
                    }
                }
                else
                {
                    list->on_piece_moved(pgn_moves[i].piece_get(),
                                         pgn_moves[i].start_get(),
                                         pgn_moves[i].end_get());
                    // if there is a capture
                    if (pgn_moves[i].capture_get())
                    {
                        // if en passant
                        if (p.report_type & un << 2 || p.report_type & un << 6)
                        {
                            int rank = (int)log2(move.moved) / 8;
                            int file = (int)log2(move.moved) % 8;
                            Position pos = Position(static_cast<File>(file),
                                                    static_cast<Rank>(rank));
                            list->on_piece_taken(board::PieceType::PAWN, pos);
                        }
                        else
                        {
                            auto pieceType =
                                pos_to_type(log2(p.moved), bitBoard);
                            list->on_piece_taken(pieceType,
                                                 pgn_moves[i].end_get());
                        }
                    }
                    // if promotion
                    if (pgn_moves[i].promotion_get().has_value())
                    {
                        board::PieceType pieceType =
                            pgn_moves[i].promotion_get().value();
                        list->on_piece_promoted(pieceType,
                                                pgn_moves[i].end_get());
                    }
                }
                bitBoard = do_move(bitBoard, move);
                size_t is_king_chessed = 0;
                if (i % 2 == 0)
                {
                    possible_moves = board.black_possible_moves(bitBoard);
                    side = board::Color::BLACK;
                    is_king_chessed = 3;
                }
                else
                {
                    possible_moves = board.white_possible_moves(bitBoard);
                    side = board::Color::WHITE;
                    is_king_chessed = 7;
                }
                if ((possible_moves.empty()
                     && move.report_type & un << is_king_chessed)
                    || pgn_moves[i].report_get() == ReportType::CHECKMATE)
                {
                    list->on_player_mat(side);
                    stop = true;
                    break;
                }
                else if ((!possible_moves.empty()
                          && move.report_type & un << is_king_chessed)
                         || pgn_moves[i].report_get() == ReportType::CHECK)
                {
                    list->on_player_check(side);
                }
                if (possible_moves.empty()
                    && !(move.report_type & un << is_king_chessed))
                {
                    list->on_player_pat(side);
                    list->on_draw();
                    stop = true;
                    break;
                }
            }
            else
            {
                list->on_player_disqualified(side);
                stop = true;
                break;
            }
        }
        if (stop)
        {
            list->on_game_finished();
        }
    }
} // namespace board
