#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./minimax.hpp"

Move Minimax::get_move(State *state, int depth, int alpha, int beta){
    if(!state->legal_actions.size())
    state->get_legal_actions();
    Move bestmove;
    int best=(depth%2)?INT_MAX:INT_MIN;
    auto actions = state->legal_actions;
    if(depth%2==0){
        for (auto it = actions.begin();it!=actions.end();it++){
            State *nextstate = state->next_state(*it);
            Move curmove = get_move(nextstate, depth+1, alpha, beta);
            int val = nextstate->evaluate();
            delete nextstate;
            if(val>best){
                best = val;
                bestmove = curmove;
            }
            alpha = (alpha>best)?alpha:best;
            if(beta<=alpha){
                break;
            }
        }
    }
    else{
        for (auto it = actions.begin();it!=actions.end();it++){
            State *nextstate = state->next_state(*it);
            Move curmove = get_move(nextstate, depth+1, alpha, beta);
            int val = nextstate->evaluate();
            delete nextstate;
            if(val<best){
                best = val;
                bestmove = curmove;
            }
            beta = (beta<best)?beta:best;
            if(beta<=alpha){
                break;
            }
        }
    }
    return bestmove;
}