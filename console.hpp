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

void clear();
bool keyDown(int k);
void moveCursor(short x,short y);
void fill(int x1,int y1,int x2,int y2,char c);
void text(int x,int y,const char*s);

void clear(){
  system("cls");
}
bool keyDown(int k){
  return GetAsyncKeyState(k)&0x8000?1:0;
}
void moveCursor(short x,short y){
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