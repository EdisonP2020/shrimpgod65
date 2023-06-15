#pragma once
#include "../state/state.hpp"

class Minimax{
public:
  static Move get_move(State *state, int depth, int alpha, int beta);
};