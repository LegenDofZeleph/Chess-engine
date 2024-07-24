#include "all.hh"
int main()
{
    std::cout << "PInitial\n";
    board::Move board;
    board::BitB bob;
    std::vector<unsigned long long> test = bob.init_bitboard();
    // test[2] = 134217728;
    // std::vector<unsigned long long> test =
         // board.white_pawns_possible_moves();
    /*unsigned long long res = board.white_pawns_possible_moves(test);
    bob.print_BitBoard(res);
    std::cout << "\n attacks\n";*/
    //unsigned long long res1 = board.white_pawns_attacks(test);
    //bob.print_BitBoard(16777216);
    /*for (int x = 0; x < test.size(); x++)
        test[x] = 0;
    test[9] = 549755813888;
    test[13] = 549755813888;
    std::vector<struct pieces_moves> pi = board.black_possible_moves(test);
    for (int i = 0; i < pi.size(); i++)
    {
        std::cout << "PInitial\n";
        bob.print_BitBoard(pi.initial);
        std::cout << "PMOved\n";
        bob.print_BitBoard(pi.moved);
    }*/
    /*std::cout << "Initial\n";
     */
    /*std::cout << "attaques blanches \n";
    bob.print_BitBoard(16777216);
    std::cout << "roi noir \n";
    bob.print_BitBoard(246315239096896U);
    
    std::cout << "----------------------------------------------------\n";
    std::cout << "INITIAL\n";
    bob.print_BitBoard(131072);
    std::cout << "BOARD BLANC\n";
    bob.print_BitBoard(825741019136U);
    std::cout << "BOARD NOIR\n";
    bob.print_BitBoard(9024795752660992);
    std::cout << "report_type\n";
    bob.print_BitBoard(1065024);
    std::cout << "BOARD BLANC avant modif\n";
    bob.print_BitBoard(825741019136U);
    std::cout << "initial\n";
    bob.print_BitBoard(67108864);*/
    //std::cout << "moved\n";
    //bob.print_BitBoard(9925597129240281088U);
    std::cout << "attaques noires\n";
    bob.print_BitBoard(65418);
    std::cout << "roi blanc\n";
    bob.print_BitBoard(9943385031575601152U);
    std::cout << "roi blanc\n";
    bob.print_BitBoard(15);
/*
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(562949953421312U);
    std::cout << "Moved\n";
    bob.print_BitBoard(1099511627776U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4503599627370496U);
    std::cout << "Moved\n";
    bob.print_BitBoard(68719476736U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4503599627370496U);
    std::cout << "Moved\n";
    bob.print_BitBoard(17592186044416U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9007199254740992U);
    std::cout << "Moved\n";
    bob.print_BitBoard(137438953472U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9007199254740992U);
    std::cout << "Moved\n";
    bob.print_BitBoard(35184372088832U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(72057594037927936U);
    std::cout << "Moved\n";
    bob.print_BitBoard(144115188075855872U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(72057594037927936U);
    std::cout << "Moved\n";
    bob.print_BitBoard(288230376151711744U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9223372036854775808U);
    std::cout << "Moved\n";
    bob.print_BitBoard(36028797018963968U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9223372036854775808U);
    std::cout << "Moved\n";
    bob.print_BitBoard(1152921504606846976U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9223372036854775808U);
    std::cout << "Moved\n";
    bob.print_BitBoard(2305843009213693952U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(9223372036854775808U);
    std::cout << "Moved\n";
    bob.print_BitBoard(4611686018427387904U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(549755813888U);
    std::cout << "Moved\n";
    bob.print_BitBoard(4194304U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(549755813888U);
    std::cout << "Moved\n";
    bob.print_BitBoard(536870912U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(549755813888U);
    std::cout << "Moved\n";
    bob.print_BitBoard(35184372088832U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4398046511104U);
    std::cout << "Moved\n";
    bob.print_BitBoard(33554432U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4398046511104U);
    std::cout << "Moved\n";
    bob.print_BitBoard(134217728U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4398046511104U);
    std::cout << "Moved\n";
    bob.print_BitBoard(4294967296U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4398046511104U);
    std::cout << "Moved\n";
    bob.print_BitBoard(68719476736U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(4398046511104U);
    std::cout << "Moved\n";
    bob.print_BitBoard(144115188075855872U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(2199023255552U);
    std::cout << "Moved\n";
    bob.print_BitBoard(134217728);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(2199023255552U);
    std::cout << "Moved\n";
    bob.print_BitBoard(4294967296U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(2199023255552U);
    std::cout << "Moved\n";
    bob.print_BitBoard(17179869184U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(2);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(1024);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(524288);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(268435456U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(137438953472U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(70368744177664U);
    std::cout << "Moved\n";
    bob.print_BitBoard(36028797018963968U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(32768U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(262144U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(524288U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(1048576U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(2097152U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(4194304);*/
    /*std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(1073741824U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(8388608);
    std::cout << "Moved\n";
    bob.print_BitBoard(2147483648U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(576460752303423488U);
    std::cout << "Moved\n";
    bob.print_BitBoard(144115188075855872U);
    std::cout << "----------------------------------------------------\n";
    std::cout << "Initial\n";
    bob.print_BitBoard(576460752303423488U);
    std::cout << "Moved\n";
    bob.print_BitBoard(1152921504606846976U);
    std::cout << "----------------------------------------------------\n";
    */
    /*std::cout << "Initial\n";
    bob.print_BitBoard(576460752303423488U);
    std::cout << "Moved\n";
    bob.print_BitBoard(2305843009213693952U);*/
    /*std::vector<unsigned long long> res2 = board.white_pawn_moves();
    for (unsigned long long  i = 8; i < 16; i++)
    {
         bob.print_BitBoard(res2[i]);
         std::cout << '\n';
         }*/
    /*unsigned long long res = board.white_rooks_attacks(test);
      bob.print_BitBoard(res);*/
    // std::cout << '\n';

    /*test[0] = 0;
    test[1] = 2048;
    test[2] = 0;
    test[3] = 1024;
    test[4] = 4096;
    test[5] = 16;
    test[6] = 7184;
    test[7] = 0;
    test[8] = 1;
    test[9] = 0;
    test[10] = 0;
    test[11] = 0;
    test[13] = 1;
    test = board.black_attacks(test);*/

    // bob.print_BitBoard(white_king_possible_moves(test, false, false));

    /*std::vector<struct board::pieces_moves> res =
        board.white_possible_moves(test);
    for (unsigned long long i = 0; i < res.size(); i++)
    {
        bob.print_BitBoard(res[i].initial);
        std::cout << '\n';
        bob.print_BitBoard(res[i].moved);
        std::cout << '\n';
        std::cout << "---------------------------------------------------------"
                     "------------------------\n";
        std::cout << '\n';
        }*/
    //bob.print_BitBoard(129);
    return 0;
}
