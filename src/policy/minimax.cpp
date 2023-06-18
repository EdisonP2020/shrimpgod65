#include <cstdlib>
#include <climits>
#include "../state/state.hpp"
#include "./minimax.hpp"

Move Minimax::get_move(State *state, int depth){
    state->get_legal_actions();
    auto actions = state->legal_actions;
    Move bestmove;
    int eval=(state->player)?INT_MAX:INT_MIN;
    for(auto it :actions){
        State *root = state->next_state(it);
        if(state->player){
            //if(root->game_state==WIN) continue;
            int val = minimax(root, depth+1, true, state->player);
            if(val < eval){
                eval = val;
                bestmove = it;
            }
        }
        else{
            //if(root->game_state==WIN) continue;
            int val = minimax(root, depth+1, false, state->player);
            if(val > eval){
                eval = val;
                bestmove = it;
            }
        }
        delete root;     
    }
    return bestmove;
}

int Minimax::minimax(State* state, int depth, bool maximumplayer, int me){
    if(depth>=5){
        return state->evaluate();
    }
    else if(state->game_state==WIN){
        if(state->player){
            return INT_MIN;
        }
        else{
            return INT_MAX;
        }
    }
    int best=(maximumplayer)?INT_MIN:INT_MAX;
    state->get_legal_actions();
    auto actions = state->legal_actions;
    if(maximumplayer){
        for (auto it : actions){
            State *nextstate = state->next_state(it);
            int val = minimax(nextstate, depth+1, false, me);
            delete nextstate;
            best = (best>val)?best:val;
        }
    }
    else{
        for (auto it : actions){
            State *nextstate = state->next_state(it);
            int val = minimax(nextstate, depth+1, true, me);
            delete nextstate;
            best = (best<val)?best:val;
        }
    }
    return best;
}