#include "graphics.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <windows.h>

class tocka{ //оператор функции для присваивания внутри
	public:
		double x,y,z;
		tocka(){x=0;y=0;z=0;};
	tocka(double a,double b,double c){x=a;y=b;z=c;};
	
};
class vertex{//используем метод vertex, чтобы задать координаты вершин для точек куба
	public:
		tocka mir;//мировые координаты
		tocka vid;
		vertex(){};//видимые(экранные) координаты
		vertex1(tocka p){mir=p;
		};
		~vertex(){};// вычисление видовых координат
		void SetViewCoord(tocka sphercoord){//используя мировые координаты и точку наблюдения
				double Ro=sphercoord.x,teta=sphercoord.y,fi=sphercoord.z;
		vid.x=-mir.x*sin(teta)+mir.y*cos(teta); //начало расчета
		vid.y=-mir.x*cos(fi)*cos(teta)-mir.y*cos(fi)*sin(teta)+mir.z*sin(fi); 
		vid.z=-mir.x*sin(fi)*cos(teta)-mir.y*sin(fi)*sin(teta)-mir.z*cos(fi)+Ro; 	
		};
};
class edge { 
		private:
	vertex sv, fv;//создание конструктор, с помощью которого будем создавать точки и отрисовывать ребра
	public:
		edge(){};//рисование ребра
		edge1 (vertex sver, vertex fver){
		sv=sver;fv=fver;
		}
		~edge(){};
			void DRAWedge(double d){ 	
			d=d/2;//используются видовые координаты
			double x1 = (int)((d*sv.vid.x)/sv.vid.z);
			double y1 = (int)((d*sv.vid.y)/sv.vid.z);
			double x2 = (int)((d*fv.vid.x)/fv.vid.z);
			double y2 = (int)((d*fv.vid.y)/fv.vid.z);
				line(x1+(getmaxx()/2),y1+(getmaxy()/2),x2+(getmaxx()/2),y2+(getmaxy()/2));
  }	
};
struct eh{
	public: 
	int a,b;
};
class DRAW { // создаем класс для работы с edge и vertex
	private:
	vertex *verts; edge *edges; eh *eh1;
	tocka vidpoint;
	bool flg = false;
	public:
		int n,m;
	friend	class edge; 
	friend	class vertex;
	
	void draw(){//функция отрисовки куба
		for(int i=0;i<m;i++)  
		edges[i].DRAWedge(vidpoint.x);
	};
	void load(){
	int c,a,b;
	if(!flg){
		FILE *file;//берем информацию о кубе из документа 
		file = fopen("kub.txt", "r"); 
  	if (file!=NULL) {
		fscanf(file,"%d",&n);//fscanf функция которая позволяет считывать поток данных и записывать его в переменные
    	fscanf(file,"%d",&m);
    	verts=new vertex[n];
    	edges=new edge[m];
    for(int i=0;i<n;i++){
    	fscanf(file,"%d",&a);
    	fscanf(file,"%d",&b);
    	fscanf(file,"%d",&c);
    	tocka p=tocka(a*100,b*100,c*100);
		verts[i].vertex1(p);
		verts[i].SetViewCoord(vidpoint);
		}
		eh1=new eh[m];
	for(int i=0;i<m;i++){
		fscanf(file,"%d",&a);
    	fscanf(file,"%d",&b);
    	eh1[i].a=a;
    	eh1[i].b=b;
    	edges[i].edge1(verts[eh1[i].a],verts[eh1[i].b]);
		}
	flg=1;
	}}
for(int i=0;i<n;i++)verts[i].SetViewCoord(vidpoint);
	for(int i=0;i<m;i++)
    edges[i].edge1(verts[eh1[i].a],verts[eh1[i].b]);
	};
	void Setvidimtck(double rota,double alp,double fi){
	vidpoint.x=rota;
	vidpoint.y=alp;
	vidpoint.z=fi;
	};
	void drawsurface(){
	};
	void delObject(){};
};
int main(){ 
double rota=200,alp=0,fi=0;
int tmp;
int gddriver = DETECT, gmode, errorcode;
	initgraph(&gddriver, &gmode, (char*)"");
	setfillstyle(LINE_FILL,BLACK) ; 
	DRAW cub;
	cub.Setvidimtck(rota,alp,fi);
	cub.load();	
	cub.draw();    
while(true)   {
		cleardevice();
		setcolor(2);
		if(tmp=='a') 
		alp += ((M_PI/9));
		if(tmp=='d') 
		alp -= ((M_PI/9));
		if(tmp=='w') 
		fi += ((M_PI/9));
		if(tmp=='s') 
		fi -= ((M_PI/9));
		if(tmp=='e') 
		rota +=6;
		if(tmp=='q') 
		rota -=6;
		if(tmp==27)
		break;	
		cub.Setvidimtck(rota,alp,fi); 
		cub.load();	
		cub.draw();
		tmp = getch();
	}
	getch();
	closegraph () ;
	return 0;
}
