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
#include<map>

#define pii pair<int,int>
#define mp std::make_pair
#define f first
#define s second
#define keyDown(k) (GetAsyncKeyState(k)&0x8000?1:0)

using namespace std;

// Variables & Functions for the game
const int N=20;
deque<pii> sp;
const short dx[6]={0,0,1,0,-1},dy[6]={0,-1,0,1,0};
short dir=1,fdx,fdy,length=1;
bool m[N][N];
double ind=1.0,last_time;

void moveCursor(int x,int y){
  HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X=x,pos.Y=y;
  SetConsoleCursorPosition(hOut,pos);
}
void fill(int x1,int y1,int x2,int y2,char c){
  for(int i=x1;i<=x2;i++)
    for(int j=y1;j<=y2;j++)
      moveCursor(i,j),printf("%c",c);
}
void text(int x,int y,const char*s){
  moveCursor(x,y);
  printf("%s",s);
}
void add(short x,short y){
  sp.push_front(mp(x,y));
  m[x][y]=1;
}
void rndFood(){
  fdx=rand()%15+1;
  fdy=rand()%15+1;
}
void createFood(){
  rndFood();
  while(m[fdx+1][fdy+3])rndFood();
}

signed main(){

  // Setup
  srand((unsigned)time(NULL));
  system("cls");
  text(2,2,"Snake Game");
  fill(2,4,16,18,'.');
  add(9,11);
  text(9,11,"%");
  text(20,4,"Length: 1");
  text(20,5,"Position: (8,8)");
  text(20,6,"Accelerate (Shift Key): 0");
  text(20,7,"Direction (Arrow Keys): 1");
  createFood();
  text(fdx+1,fdy+3,"@");
  
  // Game
  int tp=1,cdir=1,tmps=0,tmpd=1;
  while(1){
    // Updating Directions
    if(keyDown(38)&&dir!=3)cdir=1;
    if(keyDown(39)&&dir!=4)cdir=2;
    if(keyDown(40)&&dir!=1)cdir=3;
    if(keyDown(37)&&dir!=2)cdir=4; 
    if(keyDown(16))ind=0.3;
    else ind=1; 
    if(tmpd!=cdir)moveCursor(44,7),printf("%d ",tmpd);
    if(tmps!=(int)ind)moveCursor(44,6),printf("%d ",tmps);
    tmpd=cdir;
    tmps=ind;

    // Snake only moves once per second
    if((double)clock()/CLOCKS_PER_SEC-ind<(double)last_time)continue;
    last_time=(double)clock()/CLOCKS_PER_SEC;

    // Updating the snake's position
    dir=cdir;
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
    moveCursor(30,5);
    printf(" (%d,%d)  ",x-1,y-3);

    // Eat Food
    if(x==fdx+1&&y==fdy+3){
      text(20,4,"length: ");
      printf("%d",++length);
      createFood();
      text(fdx+1,fdy+3,"@");
      continue;
    }
    text(sp.back().f,sp.back().s,".");
    m[sp.back().f][sp.back().s]=0;
    sp.pop_back();
  }

  // Game Over
  if(tp==1)text(2,2,"You hit the wall!");
  else text(2,2,"You hit yourself!");
  moveCursor(1,20);
  Sleep(2000);
  system("PAUSE");
  return 0;
}