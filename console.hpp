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
void moveCursor(int x,int y);
void fill(int x1,int y1,int x2,int y2,char c);
void text(int x,int y,const char*s);

void clear(){
  system("cls");
}
bool keyDown(int k){
  return GetAsyncKeyState(k)&0x8000?1:0;
}
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
COORD getConsoleSize(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns, rows;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
  columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
  rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  COORD a;
  a.X=columns;
  a.Y=rows;
  return a;
}