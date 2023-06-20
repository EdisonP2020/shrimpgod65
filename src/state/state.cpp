#include <iostream>
#include <sstream>
#include <cstdint>

#include "./state.hpp"
#include "../config.hpp"

static double pawn_posw[2][6][5]={{
    {80, 80, 80, 80, 80},
    {5, 5, 5, 5, 5},
    {0.5, 1, 2.5, 1, 0.5},
    {0, 0, 2, 0, 0},
    {0.5, -1, -2, -1, 0.5},
    {0, 0, 0, 0, 0}
  }, {
    {0, 0, 0, 0, 0},
    {0.5, -1, -2, -1, 0.5},
    {0, 0, 2, 0, 0},
    {0.5, 1, 2.5, 1, 0.5},
    {5, 5, 5, 5, 5},
    {80, 80, 80, 80, 80}
  }
};
static double rook_posw[2][6][5]={{
    {0, 0, 0, 0, 0},
    {0.5, 1, 1, 1, 0.5},
    {-0.5, 0, 0, 0, -0.5},
    {-0.5, 0, 0, 0, -0.5},
    {-0.5, 0, 0, 0, -0.5},
    {0, 0, 0.5, 0, 0}
  }, {
    {0, 0, 0.5, 0, 0},
    {-0.5, 0, 0, 0, -0.5},
    {-0.5, 0, 0, 0, -0.5},
    {-0.5, 0, 0, 0, -0.5},
    {0.5, 1, 1, 1, 0.5},
    {0, 0, 0, 0, 0}
  }
};
static double knight_posw[2][6][5]={{
    {-5, -4, -3, -4, -5},
    {-4, -2, 0, -2, -4},
    {-3, 1.5, 2, 1.5, -3},
    {-3, 1.5, 2, 1.5, -3},
    {-4, 0, 0.5, 0, -4},
    {-5, -4, -3, -4, -5}
  }, {
    {-5, -4, -3, -4, -5},
    {-4, 0, 0.5, 0, -4},
    {-3, 1.5, 2, 1.5, -3},
    {-3, 1.5, 2, 1.5, -3},
    {-4, -2, 0, -2, -4},
    {-5, -4, -3, -4, -5}
  }
};
static double bishop_posw[2][6][5]={{
    {-2, -1, -1, -1, -2},
    {-1, 0, 0, 0, -1},
    {-1, 0.5, 1, 0.5, -1},
    {-1, 0, 1, 0, -1},
    {-1, 0.5, 0, 0.5, -1},
    {-2, -1, -1, -1, -2}
  }, {
    {-2, -1, -1, -1, -2},
    {-1, 0.5, 0, 0.5, -1},
    {-1, 0, 1, 0, -1},
    {-1, 0.5, 1, 0.5, -1},
    {-1, 0, 0, 0, -1},
    {-2, -1, -1, -1, -2}
  }
};
static double queen_posw[2][6][5]={{
    {-2, -1, -0.5, -1, -2},
    {-1, 0, 0, 0, -1},
    {-0.5, 0.5, 0.5, 0.5, -0.5},
    {0, 0.5, 0.5, 0.5, -0.5},
    {-1, 0.5, 0, 0, -1},
    {-2, -1, -0.5, -1, -2}
  }, {
    {-2, -1, -0.5, -1, -2},
    {-1, 0, 0, 0.5, -1},
    {-0.5, 0.5, 0.5, 0.5, 0},
    {-0.5, 0.5, 0.5, 0.5, -0.5},
    {-1, 0, 0, 0, -1},
    {-2, -1, -0.5, -1, -2}
  }
};
static double king_posw[2][6][5]={{
    {-3, -4, -5, -4, -3},
    {-3, -4, -5, -4, -3},
    {-3, -4, -5, -4, -3},
    {-2, -3, -4, -3, -2},
    {2, 0, 0, 0, 2},
    {2, 3, 0, 3, 2}
  }, {
    {2, 3, 0, 3, 2},
    {2, 0, 0, 0, 2},
    {-2, -3, -4, -3, -2},
    {-3, -4, -5, -4, -3},
    {-3, -4, -5, -4, -3},
    {-3, -4, -5, -4, -3}
  }
};
int State::checkrookmove(int i, int j){
  int up=-2;
  int right=-2;
  int left=-2;
  int down=-2;
  for(int x = j+1; x < 5; x++){
    if(!board.board[0][i][x]&&!board.board[1][i][x]){
      right++;
    }
    else{
      right++;
      break;
    }
  }
  for(int x=j-1;x>=0;x--){
    if(!board.board[0][i][x]&&!board.board[1][i][x]){
      left++;
    }
    else{
      left++;
      break;
    }
  }
  for(int y = j+1; y < 6; y++){
    if(!board.board[0][y][j]&&!board.board[1][i][j]){
      down++;
    }
    else{
      down++;
      break;
    }
  }
  for(int y=j-1;y>=0;y--){
    if(!board.board[0][y][j]&&!board.board[1][i][j]){
      up++;
    }
    else{
      up++;
      break;
    }
  }
  return (up+down+right+left);
}

int State::checkbismove(int i, int j){
  int upright=-2;
  int downright=-2;
  int upleft=-2;
  int downleft=-2;
  for(int x=1;i+x<6&&j+x<5;x++){
    if(!board.board[0][i+x][j+x]&&!board.board[1][i+x][j+x]){
      downright++;
    }
    else{
      downright++;
      break;
    }
  }
  for(int x=1;i-x>=0&&j-x>=0;x++){
    if(!board.board[0][i-x][j-x]&&!board.board[1][i-x][j-x]){
      upleft++;
    }
    else{
      upleft++;
      break;
    }
  }
  for(int x=1;i+x<6&&j-x>=0;x++){
    if(!board.board[0][i+x][j-x]&&!board.board[1][i+x][j-x]){
      downleft++;
    }
    else{
      downleft++;
      break;
    }
  }
  for(int x=1;i-x>=0&&j+x<5;x++){
    if(!board.board[0][i-x][j+x]&&!board.board[1][i-x][j+x]){
      upright++;
    }
    else{
      upright++;
      break;
    }
  }
  return (downleft+downright+upright+upleft);
}
/**
 * @brief evaluate the state
 * 
 * @return int 
 */
int State::evaluate(){
  // [TODO] design your own evaluation function
  int val[2];
  for(int n=0;n<2;n++){
    val[n]=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        switch(board.board[n][i][j]){
          case 1:
            val[n]+=10;
            //std::cout<<"pawn\n";
            break;
          case 2:
            val[n]+=50;
            //std::cout<<"rook\n";
            break;
          case 3:
            val[n]+=30;
            //std::cout<<"knight\n";
            break;
          case 4:
            val[n]+=30;
            //std::cout<<"bishop\n";
            break;
          case 5:
            val[n]+=90;
            //std::cout<<"queen\n";
            break;
          case 6:
            val[n]+=900;
            //std::cout<<"king\n";
            break;
          default:
            break;
        }
      }
    }
  }
  return val[0]-val[1];
}
int State::betterevaluate(){
  // [TODO] design your own evaluation function
  int val[2];

  for(int n=0;n<2;n++){
    val[n]=0;
    for(int i=0;i<6;i++){
      for(int j=0;j<5;j++){
        int pieceval=0;
        switch(board.board[n][i][j]){
          case 1:
            pieceval+=(20+2*pawn_posw[n][i][j]);
            break;
          case 2:
            pieceval+=(100+2*rook_posw[n][i][j]/*+0.3*checkrookmove(i, j)*/);
            break;
          case 3:
            pieceval+=(60+2*knight_posw[n][i][j]);
            break;
          case 4:
            pieceval+=(60+2*bishop_posw[n][i][j]/*+0.3*checkbismove(i, j)*/);
            break;
          case 5:
            pieceval+=(180+2*queen_posw[n][i][j]/*+checkbismove(i, j)+0.3*checkrookmove(i, j)*/);
            break;
          case 6:
            pieceval+=(1800+2*king_posw[n][i][j]);
            break;
          default:
            break;
        }
        val[n]+=pieceval;
      }
    }
  }
  //std::cout<<val[0]<<" "<<val[1]<<"\n";
  return val[0]-val[1];
}

/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  //std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}