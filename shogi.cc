#include "shogi.h"

Shogi::Shogi() {
  /*
    6 3 0
    7 4 1
    8 5 2
  */
  /*
    0b0000 = empty
    0b0001 = black pawn
    0b0010 = black silver
    0b0011 = black gold
    0b0100 = black king
    0b0101 = black promoted pawn
    0b0110 = black promoted silver
    0b1111 = white pawn
    0b1110 = white silver
    0b1101 = white gold
    0b1100 = white king
    0b1011 = white promoted pawn
    0b1010 = white promoted silver
  */
  // clang-format off
  board = {
      0b1100, 0b0000, 0b0000,
      0b0000, 0b0000, 0b0000,
      0b0000, 0b0000, 0b0100,
  };
  // clang-format on
  num_files = 3;
  num_ranks = 3;
  num_squares = num_files * num_ranks;

  piece_bitboards = {
      0b000'000'000, // black pawn
      0b000'000'000, // black silver
      0b000'000'000, // black gold
      0b100'000'000, // black king
      0b000'000'000, // black promoted pawn
      0b000'000'000, // black promoted silver
      0b000'000'000, // white pawn
      0b000'000'000, // white silver
      0b000'000'000, // white gold
      0b000'000'001, // white king
      0b000'000'000, // white promoted pawn
      0b000'000'000, // white promoted silver
  };

  black_occupied_bitboard = 0b100'000'000;
  white_occupied_bitboard = 0b000'000'001;
  occupied_bitboard = black_occupied_bitboard | white_occupied_bitboard;

  piece_attacks_bitboards = {
      0b000'000'000, // black pawn
      0b000'000'000, // black silver
      0b000'000'000, // black gold
      0b010'110'000, // black king
      0b000'000'000, // black promoted pawn
      0b000'000'000, // black promoted silver
  };
}

inline int ctz(unsigned int mask) { return mask ? __builtin_ctz(mask) : 16; }

inline int find_lsb(unsigned int mask, int offset) {
  return ctz(mask & ~((1 << offset) - 1));
}

Shogi::Moves Shogi::get_black_legal_moves() {
  Moves moves;

  for (int i = 0; (i = find_lsb(black_occupied_bitboard, i)) < num_squares;
       i++) {
    Piece from_piece = board[i];

    Bitboard from_piece_attacks_bitboard =
        piece_attacks_bitboards[from_piece - 1];
    from_piece_attacks_bitboard &= ~black_occupied_bitboard;

    for (int j = 0;
         (j = find_lsb(from_piece_attacks_bitboard, j)) < num_squares; j++) {
      int from_file = i / num_ranks + 1;
      int from_rank = i % num_ranks + 1;
      int to_file = j / num_ranks + 1;
      int to_rank = j % num_ranks + 1;
      moves.push_back({from_file, from_rank, to_file, to_rank, from_piece});
    }
  }

  return moves;
}
