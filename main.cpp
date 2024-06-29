#include"console.hpp"

// Defs
using namespace std;
const int N=505;
const char brightnessTable[15]={' ','.',',',':',';','>','?','[','8','$','@','#'};
char a[N*N];
int wndW,wndH,_wndW,_wndH,csrX,csrY;
HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);

// Functions
void getConsoleInfo(){
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  int columns,rows;
  GetConsoleScreenBufferInfo(hOut, &csbi);
  wndW=csbi.srWindow.Right-csbi.srWindow.Left+1;
  wndH=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
}
// void getCursorPos(){
//   if(!wndW || !wndH) return;
//   POINT p;
//   GetCursorPos(&p);
//   ScreenToClient(GetForegroundWindow(), &p);

//   CONSOLE_SCREEN_BUFFER_INFO csbi;
//   GetConsoleScreenBufferInfo(hOut, &csbi);
//   int fontWidth = csbi.dwSize.X / wndW;
//   int fontHeight = csbi.dwSize.Y / wndH;

//   csrX = p.x / fontWidth;
//   csrY = p.y / fontHeight;
// }
void set(int x,int y,char c){
  if(x<1||y<1||x>wndW||y>wndH)return;
  a[(y-1)*wndW+x]=c;
}
void setBrightness(int x,int y,short b){
  if(b<0||b>13)return;
  set(x,y,brightnessTable[b]);
}
void setString(int x,int y,const char*s){
  for(int i=1;s[i];i++)
    set(x+i-1,y,s[i]);
}
void setBlank(){
  memset(a,0,sizeof(a));
  for(int i=1;i<=wndW*wndH;i++)
    a[i]=' ';
}
void show(){
  moveCursor(0,0);
  printf("%s",a+1);
}

// Draw


// Events
void onResize(){
  clear();
}

signed main(){
  while(true){
    getConsoleInfo();
    if(_wndW!=wndW||_wndH!=wndH)onResize();
    _wndW=wndW;_wndH=wndH;
    setBlank();
    
    setBrightness(csrX,csrY,10);

    show();
  }
  return 0;
}