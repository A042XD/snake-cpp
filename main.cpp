/*
  Snake Game
  
  Ends when the snake head hits the borders.

  Controll
    Arrow Keys (Up, Down, Left, Right) - Change Direction
    Shift (Left or Right) - Accelerate

 */

#include<windows.h>
#include<stdio.h>
#include<algorithm>
#include<deque>
#include<ctime>

using namespace std;

// Functions for drawing on the console
#define pii pair<int,int>
#define mp make_pair
#define f first
#define s second
void clear();
bool keyDown(int k);
void moveCursor(int x,int y);
void fill(int x1,int y1,int x2,int y2,char c);

// Variables & Functions for the game
deque<pii> sp;
const short dx[6]={0,0,1,0,-1},dy[6]={0,-1,0,1,0};
short dir=1,fdx,fdy;
long double ind=1.0,last_time;

void add(short x,short y){
  sp.push_front(mp(x,y));
}
void createFood(){
  fdx=rand()%15+1,fdy=rand()%15+1;
}
void drawFood(){
  moveCursor(fdx+1,fdy+3);puts("@");
}


int main(){
  srand((unsigned)time(NULL));
  clear();

  // Setup
  moveCursor(2,2);
  puts("Snake Game");
  fill(2,4,16,18,'.');
  add(9,11);
  moveCursor(9,11);
  puts("%");
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
    moveCursor(sp.front().f,sp.front().s);
    puts("#");
    int x=sp.front().f+dx[dir];
    int y=sp.front().s+dy[dir];
    sp.push_front(mp(x,y));
    moveCursor(x,y);
    puts("%");

    // Game Over
    if(x<2||x>16)break;
    if(y<4||y>18)break;

    // Eat Food
    if(x==fdx+1&&y==fdy+3){
      fdx=rand()%15+1,fdy=rand()%15+1;
    }
    else{
      moveCursor(sp.back().f,sp.back().s);
      puts(".");
      sp.pop_back();
    }
    drawFood();
  }

  // Game Over
  moveCursor(2,2);
  puts("Game Over!");
  moveCursor(1,20);
  system("PAUSE");
  return 0;
}

void moveCursor(int x,int y){
  HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X=x,pos.Y=y;
  SetConsoleCursorPosition(hOut,pos);
}
void clear(){
  system("cls");
}
bool keyDown(int k){
  return GetAsyncKeyState(k)&0x8000?1:0;
}
void fill(int x1,int y1,int x2,int y2,char c){
  for(int i=x1;i<=x2;i++)
    for(int j=y1;j<=y2;j++)
      moveCursor(i,j),printf("%c",c);
}