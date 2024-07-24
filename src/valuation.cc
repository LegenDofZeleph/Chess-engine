#include "valuation.hh"

int piece_count(std::vector<unsigned long long> bitBoard, size_t piece_place)
{
    int count = 0;
    unsigned long long un = 1;
    unsigned long long piece_count = bitBoard[piece_place];
    for (unsigned long long i = 64; i > 0; --i)
    {
        unsigned long long tmp = un << (i - 1);
        if (piece_count >= tmp)
        {
            count += 1;
            piece_count -= tmp;
        }
    }
    return count;
}

int white_count(std::vector<unsigned long long> bitBoard)
{
    int count = 0; // king value;
    for (size_t i = 0; i <= 4; i++)
    {
        int tmp = piece_count(bitBoard, i);
        if (i == 0)
            count += (tmp * 100);
        else if (i == 1)
            count += (tmp * 510);
        else if (i == 2)
            count += (tmp * 320);
        else if (i == 3)
        {
            count += (tmp * 330);
            /*if (tmp == 2)
                count += 15;*/ //bonus: paire de fou
        }
        else
            count += (tmp * 881);
    }
    std::cout << count;
    return count;
}

int black_count(std::vector<unsigned long long> bitBoard)
{
    int count = 0; // king value;
    for (size_t i = 7; i <= 11; i++)
    {
        int tmp = piece_count(bitBoard, i);
        if (i == 7)
            count += (tmp * 100);
        else if (i == 8)
            count += (tmp * 510);
        else if (i == 9)
            count += (tmp * 320);
        else if (i == 10)
        {
            count += (tmp * 330);
            /*if (tmp == 2)
                count += 15;*/ //bonus: paire de fou
        }
        else
            count += (tmp * 881);
    }
    std::cout << count;
    return count;
}
//todo add point when king is safe (castle management)
int score(std::vector<unsigned long long> bitBoard)
{
    int white = white_count(bitBoard);
    int black = black_count(bitBoard);
    return (white - black); // >0 blanc mène
}

/*int main()
{
    std::vector<unsigned long long> bob(16, 0);
    // white stuff
    // white_pawn
    bob[0] = 0;
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
    bob[7] = 0;
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
    bob[16] = 15;
    int a = white_count(bob);
    return a;
}*/
