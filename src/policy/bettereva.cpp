#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./bettereva.hpp"

Move Bettereva::get_move(State *state, int depth){
    if(!state->legal_actions.size())
    state->get_legal_actions();
    auto actions = state->legal_actions;
    Move bestmove;
    int eval=(depth%2)?INT_MAX:INT_MIN;
    for(auto it :actions){
        State *root = state->next_state(it);
        int val = minimax(root, 0, INT_MIN, INT_MAX);
        if(val>eval){
            eval=val;
            bestmove=it;
        }
        delete root;
    }
    return bestmove;
}

int Bettereva::minimax(State* state, int depth, int alpha, int beta){
    if(depth>=5||state->game_state==WIN){
        return state->betterevaluate();
    }
    int best=(depth%2)?INT_MAX:INT_MIN;
    auto actions = state->legal_actions;
    if(depth%2==0){
        for (auto it : actions){
            State *nextstate = state->next_state(it);
            int val = minimax(nextstate, depth+1, alpha, beta);
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
            int val = minimax(nextstate, depth+1, alpha, beta);
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