/*
  Snake Game
  
  Ends when the snake head hits the borders.

  Controll
    Arrow Keys (Up, Down, Left, Right) - Change Direction
    Shift (Left or Right) - Accelerate

 */

#include"console.hpp"

using namespace std;

// Variables & Functions for the game
deque<pii> sp;
const short dx[6]={0,0,1,0,-1},dy[6]={0,-1,0,1,0};
short dir=1,fdx,fdy;
long double ind=1.0,last_time;

void add(short x,short y){
  sp.push_front(mp(x,y));
}
void createFood(){
  fdx=rand()%15+1;
  fdy=rand()%15+1;
}
void drawFood(){
  text(fdx+1,fdy+3,"@");
}


int main(){
  srand((unsigned)time(NULL));
  clear();

  // Setup
  text(2,2,"Snake Game");
  fill(2,4,16,18,'.');
  add(9,11);
  text(9,11,"%");
  createFood();
  drawFood();
  
  // Game
  while(1){
    // Updating Directions
    if(keyDown(38))dir=1;
    if(keyDown(39))dir=2;
    if(keyDown(40))dir=3;
    if(keyDown(37))dir=4; 
    if(keyDown(16))ind=0.3;
    else ind=1; 

    // Snake only moves once per second
    if((double)clock()/CLOCKS_PER_SEC-ind<(double)last_time)continue;
    last_time=(double)clock()/CLOCKS_PER_SEC;

    // Updating the snake's position
    text(sp.front().f,sp.front().s,"#");
    int x=sp.front().f+dx[dir];
    int y=sp.front().s+dy[dir];
    sp.push_front(mp(x,y));
    text(x,y,"%");

    // Game Over
    if(x<2||x>16||y<4||y>18)break;

    // Eat Food
    if(x==fdx+1&&y==fdy+3){
      createFood();
      continue;
    }
    text(sp.back().f,sp.back().s,".");
    sp.pop_back();
    drawFood();
  }

  // Game Over
  text(2,2,"Game Over ");
  moveCursor(1,20);
  system("PAUSE");
  return 0;
}