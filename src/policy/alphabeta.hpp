#pragma once
#include "../state/state.hpp"

class Alphabeta{
public:
  static Move get_move(State *state, int depth);
  static int minimax(State *state, int depth, int alpha, int beta, bool maximumplayer, int me);
};