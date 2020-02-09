#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

class Shogi {
public:
  using Piece = std::int_fast8_t;
  using Board = std::array<Piece, 9>;
  using Bitboard = std::int_fast16_t;
  using Moves = std::vector<std::array<int, 5>>;

  Shogi();

  Moves get_black_legal_moves();

  Board board;
  int num_files;
  int num_ranks;
  int num_squares;

  std::array<Bitboard, 12> piece_bitboards;

  Bitboard black_occupied_bitboard;
  Bitboard white_occupied_bitboard;
  Bitboard occupied_bitboard;

  std::array<Bitboard, 6> piece_attacks_bitboards;
};
