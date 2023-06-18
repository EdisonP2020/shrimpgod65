#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./bettereva.hpp"

Move Bettereva::get_move(State *state, int depth){
    state->get_legal_actions();
    auto actions = state->legal_actions;
    Move bestmove;
    int eval=(state->player)?INT_MAX:INT_MIN;
    for(auto it :actions){
        State *root = state->next_state(it);
        if(state->player){
            int val = minimax(root, depth+1, INT_MIN, INT_MAX, true, state->player);
            if(val < eval){
                eval = val;
                bestmove = it;
            }
        }
        else{
            int val = minimax(root, depth+1, INT_MIN, INT_MAX, false, state->player);
            if(val > eval){
                eval = val;
                bestmove = it;
            }
        }
        delete root;
        
    }
    return bestmove;
}

int Bettereva::minimax(State* state, int depth, int alpha, int beta, bool maximumplayer, int me){
    if(depth>=6){
        return state->evaluate();
    }
    int best=(maximumplayer)?INT_MIN:INT_MAX;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(maximumplayer){
        for (auto it : actions){
            State *nextstate = state->next_state(it);
            int val = minimax(nextstate, depth+1, alpha, beta, false, me);
            delete nextstate;
            best = (best>val)?best:val;
            alpha = (alpha>best)?alpha:best;
            if(beta<=alpha){
                break;
            }
        }
    }
    else{
        for (auto it : actions){
            State *nextstate = state->next_state(it);
            int val = minimax(nextstate, depth+1, alpha, beta, true, me);
            delete nextstate;
            best = (best<val)?best:val;
            beta = (beta<best)?beta:best;
            if(beta<=alpha){
                break;
            }
        }
    }
    return best;
}