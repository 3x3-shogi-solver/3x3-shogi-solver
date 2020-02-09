#include "shogi.h"
#include <iostream>

int main() {
  Shogi shogi;
  Shogi::Moves moves = shogi.get_black_legal_moves();

  for (auto move : moves) {
    for (auto x : move) {
      std::cout << x;
    }

    std::cout << std::endl;
  }
}
