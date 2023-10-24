#include <iostream>
#include <conio.h>
#include <graphics.h>
#include <math.h>

using namespace std;

#define pi 3.141592
int color = 7;

void pifagor(int n, int x0, int y0, int a, double fi, double alpha){
    int x1,x2,x3,x4,y1,y2,y3,y4;
    double b = a*cos(alpha);
    double c = a*sin(alpha);
    if(n != 0){
        n--;

        x1 = (int) (x0 + a*cos(fi));
        x2 = (int) (x1 - a*sin(fi));
        x3 = (int) (x0 - a*sin(fi));
        x4 = (int) (x3 + b*cos(fi + alpha));

        y1 = (int) (y0 - a*sin(fi));
        y2 = (int) (y1 - a*cos(fi));
        y3 = (int) (y0 - a*cos(fi));
        y4 = (int) (y3 - b*sin(fi + alpha));

        setcolor(color);

        line(x0,y0,x1,y1);
        line(x0,y0,x3,y3);
        line(x1,y1,x2,y2);
        line(x2,y2,x3,y3);
        line(x3,y3,x4,y4);
        line(x2,y2,x4,y4);

        color++;
        color %= 16;
        if(color == 0){
            color++;
        }
        pifagor(n, x3, y3, (int)b, fi + alpha, alpha);
        pifagor(n, x4, y4, (int)c, (-pi/2+fi+alpha, alpha));
    }
    return;

}

int main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver,&gmode,"");
    pifagor(12,280,getmaxy()-15,120,-pi/25.0,pi/4.7);
    getch();
    closegraph();
    return 0;
}
