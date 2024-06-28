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
const int N=20;
deque<pii> sp;
const short dx[6]={0,0,1,0,-1},dy[6]={0,-1,0,1,0};
short dir=1,fdx,fdy;
bool m[N][N];
long double ind=1.0,last_time;

void add(short x,short y){
  sp.push_front(mp(x,y));
  m[x][y]=1;
}
void createFood(){
  fdx=rand()%15+1;
  fdy=rand()%15+1;
  while(m[fdx+1][fdy+3]){
    fdx=rand()%15+1;
    fdy=rand()%15+1;
  }
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
  int tp=1,cdir=1;
  while(1){
    // Updating Directions
    if(keyDown(38)&&dir!=3)cdir=1;
    if(keyDown(39)&&dir!=4)cdir=2;
    if(keyDown(40)&&dir!=1)cdir=3;
    if(keyDown(37)&&dir!=2)cdir=4; 
    if(keyDown(16))ind=0.3;
    else ind=1; 

    // Snake only moves once per second
    if((double)clock()/CLOCKS_PER_SEC-ind<(double)last_time)continue;
    last_time=(double)clock()/CLOCKS_PER_SEC;

    dir=cdir;
    // Updating the snake's position
    text(sp.front().f,sp.front().s,"#");
    int x=sp.front().f+dx[dir];
    int y=sp.front().s+dy[dir];
    if(m[x][y]){
      tp=2;
      break;
    }
    add(x,y);
    text(x,y,"%");
    if(x<2||x>16||y<4||y>18)break;

    // Eat Food
    if(x==fdx+1&&y==fdy+3){
      createFood();
      continue;
    }
    text(sp.back().f,sp.back().s,".");
    m[sp.back().f][sp.back().s]=0;
    sp.pop_back();
    drawFood();
  }

  // Game Over
  if(tp==1)text(2,2,"You hit the wall!");
  else text(2,2,"You hit yourself!");
  moveCursor(1,20);
  system("PAUSE");
  return 0;
}