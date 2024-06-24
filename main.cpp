#include<windows.h>
#include<stdio.h>
#include<algorithm>
#include<deque>
#include<ctime>

// Functions for drawing on the console
using namespace std;
void mov(int x,int y){
  HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X=x,pos.Y=y;
  SetConsoleCursorPosition(hOut,pos);
}
void clear(){
  system("cls");
}
bool getkey(int key){
  return GetAsyncKeyState(key)&0x8000?1:0;
}
void fill(int x1,int y1,int x2,int y2,char c){
  for(int i=x1;i<=x2;i++)
    for(int j=y1;j<=y2;j++)
      mov(i,j),printf("%c",c);
}
void line(int x1,int y1,int x2,int y2,char c){
  double slope=(y1*1.0-y2)/(x1*1.0-x2);
  double b=int(y1-slope*x1+0.1);
  if(abs(x1-x2)>abs(y1-y2)){
    if(x1>x2)swap(x1,x2),swap(y1,y2);
    for(int i=x1;i<=x2;i++)
      mov(i,slope*i+b),printf("%c",c);
  }
  else{
    if(y1>y2)swap(x1,x2),swap(y1,y2);
    for(int i=y1;i<=y2;i++)
      mov((i-b)/slope,i),printf("%c",c);
  }
}
POINT cursorPos(){
  POINT p;
  GetCursorPos(&p);
  return p;
}

// Variables for the game
#define pii pair<int,int>
#define mp make_pair
#define f first
#define s second
deque<pii> sp;
short dir=1;
int dx[6]={0,0,1,0,-1};
int dy[6]={0,-1,0,1,0};
int last_time,fdx,fdy;

int main(){
  // Setup
  srand((unsigned)time(NULL));
  clear();
  mov(2,2);
  puts("Snake Game");
  fill(2,4,16,18,'.');

  // Game
  sp.push_front(mp(9,11));
  sp.push_front(mp(9,10));
  mov(9,11);
  puts("%");
  mov(9,10);
  puts("#");
  fdx=rand()%15+1,fdy=rand()%15+1;
  mov(fdx+1,fdy+3);puts("@");
  while(1){
    // Updating Directions
    if(getkey(38))dir=1;
    if(getkey(39))dir=2;
    if(getkey(40))dir=3;
    if(getkey(37))dir=4; 

    // Snake only moves once per second
    if(clock()/CLOCKS_PER_SEC<last_time+1)continue;
    last_time=clock()/CLOCKS_PER_SEC;

    // Updating the snake's position
    mov(sp.front().f,sp.front().s);
    puts("#");
    int x=sp.front().f+dx[dir];
    int y=sp.front().s+dy[dir];
    sp.push_front(mp(x,y));
    mov(x,y);
    puts("%");

    // Game Over
    if(x<2||x>16)break;
    if(y<4||y>18)break;

    // Eat Food
    if(x==fdx+1&&y==fdy+3){
      fdx=rand()%15+1,fdy=rand()%15+1;
    }
    else{
      mov(sp.back().f,sp.back().s);
      puts(".");
      sp.pop_back();
    }
    mov(fdx+1,fdy+3);puts("@");

    // 
    Sleep(10);
  }

  // Game Over
  mov(2,2);
  puts("Game Over!");
  mov(1,20);
  system("PAUSE");
  return 0;
}