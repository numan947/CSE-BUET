#include "stdafx.h"
# include "iGraphics.h"
#include "GLUT.H"
#include <cstdio>
#include <set>
#include <utility>
#include <algorithm>
#include <vector>
/*
	function iDraw() is called again and again by the system.
*/
char eenemy[6][12]={"ast1.bmp","ast2.bmp","ast3.bmp","ast4.bmp","ast5.bmp","ast6.bmp"};
int bstart=0;

int x_s = 1024, y_s = 512;
int credit=0;

struct enemy{
	int lx;
	int ly;
	int color;
	int k;
	int forward;

};
//double mainx,mainy,mainl,mainb;
//char ienemy[6][]={"ast1.bmp",};
bool intersect(int lx,int ly ,int mainx,int mainy,int size){
	if((lx>=mainx && lx<=mainx+size) && (ly>=mainy && ly<=mainy+size)){
		return true;
	}
	else
		return false;
    
}
long long int etime=0;
int r=0;
int curr=0;
int level=1;
long long int bcount1=0,bcount2=0,bcount3=0,bcount4=0;
int score=0;
//set <int> findex;
//set <int> eindex;
//set <int>::iterator ifi,ie;
long long int f=400;
double mainx=700.0,mainy=200.0,mainl=64,mainb=64;
struct enemy en[10000];
bool Boss=false;
long long int bhealth=100,health=50;
bool healthc=true;
int bcount=0;
int st=265;
struct laser{
	int lx;
	int ly;
	int rx;
	int ry;
}fir[10000];
int dream=100;
bool restart=true;
int xb1=25,yb1=512-174,xb2=45,yb2=512-174;

//int lev[100]={0};
int curf=0;
int fire=0;
bool bhealthc=true;
bool eintersect(int mx,int my,int ex,int ey,int ml,int el){
	if((my+ml>ey && my+ml<ey+el && mx>ex && mx<ex+el) || (mx>=ex && mx<=ex+el && my>=ey && my<=ey+el) ||(mx+ml>=ex && mx+ml<=ex+el && my>=ey && my <=ey+el) &&(mx+ml>=ex && mx+ml<=ex+el && my+ml>=ey && my+ml<=ey+el)){
		return true;
	}
	return false;

}
int inst=0;
int counf=0;int counf1=0;

struct enemy boss;
struct laser fboss[10000];
int pause=0;
void iDraw()
{	if(pause){
		iText(470,250,"PAUSE",GLUT_BITMAP_HELVETICA_18);
	return;}
	iClear();
	

	
	if(restart){
		bhealthc=true;
		curf=0;
		counf=0;
		level = 1;
		counf1=0;
		fire=0;
		r=0;
		curr=0;
		etime=0;
		score=0;
		bcount1=0,bcount2=0,bcount3=0,bcount4=0;
		f=400;
		bhealth=100,health=50;
		healthc=true;
		bcount=0;
		st=265;
		restart=false;
		mainx=(rand()*rand())%700+300;
		mainy=300;
		Boss=false;
}
	//iSetcolor(,0,0);
	iShowBMP(0,0,"back22.bmp");
	if(bstart==0 && credit==0 && inst==0){
	iShowBMP(0,0,"start.BMP");
	iSetcolor(255,0,0);
	iLine(xb1,yb1,xb2,yb2);

		return;
	}
	else if(credit){
		iShowBMP(0,0,"crdts.bmp");
		return;
	}
	else if(inst){
		iShowBMP(0,0,"INS.bmp");
		return;
	}
	//iFilledRectangle(0,0,1024,512);

	if(bcount1==0){
		boss.lx=(rand()*rand()+rand())%20-20;
		boss.ly=(rand()*rand()+rand())%100 +40;
		boss.forward=0;
		boss.k=128;
	}

	iSetcolor(255,0,0);
	iShowBMP(mainx,mainy,"SPACE.bmp");

	//iFilledRectangle(mainx,mainy,mainl,mainb);
	if(!Boss && healthc)
	{etime++;
	counf1+=2;
	if(counf1==100){
		counf=0;
		counf1=0;
	}
	if(etime==f){
		r++;
		f+=(100-level*6);
		
		
	}
	if(fire>curf /*&& findex.empty()*/){
		//curf=curf%100;
		fir[curf%10000].lx=mainx;
		fir[curf%10000].ly=mainy+mainb/2;
		fir[curf%10000].rx=mainx+25;
		fir[curf%10000].ry=fir[curf%10000].ly;
		curf=fire;
		//curf=curf%100;
	}

	if(r>curr /*&& (eindex.empty()*/){

		en[curr%10000].ly=(rand()+rand()*rand())%400 +20;
		en[curr%10000].lx=0;
		en[curr%10000].k=64;
		en[curr%10000].color=rand()*rand()+r;
		curr=r;
		//curr=curr%100;
		
		en[curr%10000].forward=0;
		
	
	}

		for(int i=0;i<curr && i<10000;++i){
			iSetcolor(255,0,0);
			iShowBMP(en[i].lx,en[i].ly,eenemy[en[i].color%5]);
			
			//iFilledRectangle((en[i].forward++%1==0)?en[i].lx+=level:en[i].lx,en[i].ly,en[i].k,en[i].k);
			en[i].forward=(en[i].forward++%1==0)?en[i].lx+=level:en[i].lx;
			
			
			if(eintersect(mainx,mainy,en[i].lx,en[i].ly,mainl,en[i].k) || eintersect(en[i].lx,en[i].ly,mainx,mainy,en[i].k,mainl)){
				en[i].lx=3000;
				en[i].ly=23332;
				//score++;
				health-=5;
				if(health==0)
					healthc=false;
			};
			
		}
		for(int i=0;i<curf && i<10000;++i)
		{	
			iSetcolor(0,0,255);
			
			iLine(fir[i].lx-=4,fir[i].ly,fir[i].rx-=4,fir[i].ry);
			for(int j=0;j<curr && j<10000;++j)
				if(intersect(fir[i].lx,fir[i].ly,en[j].lx,en[j].ly,en[j].k)){
				score++;
				//findex.insert(i);
				//eindex.insert(j);
				en[j].ly=(rand()+rand()*rand())%250 +2300;
		en[j].lx=1200;
		en[j].k=64;
		en[j].color=(rand()%60) + 50;
		//curr=r;
		en[j].forward=0;
		fir[i].lx=-300;
		fir[i].ly=mainy+mainb/2;
		fir[i].rx=-310;
		fir[i].ry=fir[i].ly;
		
				}
				
		}	
	iSetcolor(255,0,0);
	char s[100];
	sprintf(s,"%d",score);
	iText(900,470,"SCORE",GLUT_BITMAP_HELVETICA_18);
	iText(970,470,s,GLUT_BITMAP_HELVETICA_18);
	iText(10,470,"HEALTH",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(255,0,0);
	iFilledRectangle(100,470,health,18);
	iText(480,470,"LEVEL:",GLUT_BITMAP_HELVETICA_18);
	sprintf(s,"%d",level==1?level:level/2);
	iText(550,470,s,GLUT_BITMAP_HELVETICA_18);
	if(score>30)
		Boss=true;
	else if(score>25)
		level=10;
	else if(score>18)
		level=4*2;
	else if(score>12)
		level=3*2;
	else if(score>5)
		level=2*2;
	
	}
	else if(!healthc){
		iSetcolor(0,0,0);
		//iFilledRectangle(0,0,1024,512);
		if(bhealthc)
			iShowBMP(0,0,"endlost.bmp");
		else
			iShowBMP(0,0,"endwin.bmp");
		iSetcolor(255,255,255);
		iText(450,300,"GAME OVER",GLUT_BITMAP_HELVETICA_18);
		iSetcolor(255, 255, 255);
		iText(450,260,"RESTART",GLUT_BITMAP_HELVETICA_12);
		iLine(440,st,430,st);
		iText(450,220,"EXIT",GLUT_BITMAP_HELVETICA_12);
		char s[100];
		sprintf(s,"%d",score);
		iSetcolor(255, 255, 0);
		iText(450,340,"YOUR SCORE IS:",GLUT_BITMAP_HELVETICA_18);
		iText(630,340,s,GLUT_BITMAP_HELVETICA_18);

		
	}
	else{
		char s[100];
	sprintf(s,"%d",score);
	iText(900,470,"SCORE",GLUT_BITMAP_HELVETICA_18);
	iText(970,470,s,GLUT_BITMAP_HELVETICA_18);
	iText(10,470,"HEALTH",GLUT_BITMAP_HELVETICA_18);
	iText(10,430,"BOSS HEALTH",GLUT_BITMAP_HELVETICA_18);
	iSetcolor(255,0,0);
	iFilledRectangle(100,470,health,18);
	iFilledRectangle(160,430,bhealth,18);
		if(bcount==0){
		curf=0;
		curr=0;
		fire=0;
		r=0;
	}
		counf1+=2;
	if(counf1==100){
		counf=0;
		counf1=0;
	}
		if(bcount<int(1e3-300)){
			iText(400,150,"BOSS IS COMING",GLUT_BITMAP_HELVETICA_18);
			bcount++;
		}
		else{
			iSetcolor(255,0,0);
			iShowBMP(boss.lx,boss.ly,"BOSS.bmp");
			//iFilledRectangle(boss.lx,boss.ly,boss.k,boss.k);
			if(bcount1++%4==0 && boss.lx<=30){
				boss.lx+=2;

				
				}
			else{
				if(bcount2++%6==0){
					if(boss.ly<=280 && bcount3==0)
						boss.ly+=14;
					else{bcount3=1;
						boss.ly-=14;
						if(boss.ly<10)
							bcount3=0;
					}
					
					}
				if(bcount4++%(dream)==0){
					dream=(rand()*rand())%30+30;
					r++;}
				if(r>curr){
					fboss[curr%10000].lx=boss.lx+128;
					fboss[curr%10000].ly=boss.ly+64;
					fboss[curr%10000].rx=boss.lx+148;
					fboss[curr%10000].ry=fboss[curr%10000].ly;
					curr=r;

				}
				for(int i=0;i<curr && i<10000;++i){
					iSetcolor(0,0,255);
					iLine(fboss[i].lx+=5,fboss[i].ly,fboss[i].rx+=5,fboss[i].ry);
					if(intersect(fboss[i].lx,fboss[i].ly,mainx,mainy,mainb)){
						health-=5;
						if(health==0)
							healthc=false;
						fboss[i].lx=3000;
						fboss[i].ly=mainy+mainb/2;
						fboss[i].rx=3100;
						fboss[i].ry=fboss[i].ly;
					
					}

				}
				if(fire>curf){
					fir[curf%10000].lx=mainx;
					fir[curf%10000].ly=mainy+mainb/2;
					fir[curf%10000].rx=mainx+10;
					fir[curf%10000].ry=fir[curf%10000].ly;
					curf=fire;
					
				}
				for(int i=0;i<curf && i<10000;++i)
		{	
			iSetcolor(0,0,255);
			
			iLine(fir[i].lx-=6,fir[i].ly,fir[i].rx-=6,fir[i].ry);
			
				if(intersect(fir[i].lx,fir[i].ly,boss.lx,boss.ly,boss.k)){
				score++;
				bhealth-=4;
				if(bhealth==0){
					bhealthc=false;
					healthc=false;
					score+=4*health;
				}

				
		
		fir[i].lx=-300;
		fir[i].ly=mainy+mainb/2;
		fir[i].rx=-310;
		fir[i].ry=fir[i].ly;
		
				}
				
		}
	}
			

		
		if(eintersect(mainx,mainy,boss.lx,boss.ly,64,128) || eintersect(boss.lx,boss.ly,mainx,mainy,128,64)){
			healthc=false;
			}
		}
		
	}

	


}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
	//iShowBMP(100, 100, "girl.bmp");

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{	if(bstart==0){
	if(key=='w'){
		if(yb1==204){
			
		}
		else if(yb1==250){
			yb1=294,yb2=yb1;
		}
		else if(yb1==294){
			yb1=512-174,yb2=yb1;
		}
		else if(yb1==15){
			yb1=250,yb2=250;
			xb1=36-20,xb2=36;
		}
	}
		if(key=='s'){
			if(yb1==512-174)
				yb1=294,yb2=294;
			else if(yb1==294)
				yb1=250,yb2=yb1;
			else if(yb1==250)
				//yb1=204,yb2=yb1;
			//else if(yb1==204)
				yb1=15,yb2=15;
			if(yb1==15){
				xb1=903-20,xb2=903;
			}
		}
		if(key=='f' && credit==0 && inst==0){
			if(yb1==512-174){
				bstart=1;
			}
			else if(yb1==250){
				credit=1;
			}
			else if(yb1==294){
				inst=1;
			}
			else if(yb1==15){
				exit(0);
			}
		}
		else if(credit && key=='f'){
			credit=0;
			
		
		}
		else if(inst && key=='f'){
			inst=0;
		}


		return;

	
	

}
	
	if(key=='m' && !healthc){
		if(st==225)
			exit(0);
		else{
			restart=true;

		}
	}
	
	if(key == 'q')
	{
		exit(0);
	}
	if(key=='p'){
		pause=pause?0:1;
		
	}
	if(key=='w' && healthc){
		if(mainy+mainb<450)
		mainy+=3*3;
		else
			mainy=450-mainb;
	
	}
	else if(key=='w'){
		if(st==225)
			st=265;
	}
	if(key=='s' && healthc){
		if(mainy>0)
			mainy-=3*3;
		else 
			mainy=0;
	}
	else if(key=='s'){
		if(st==265)
			st=225;
	}
	if(key=='a'){
		if(mainx>0)
			mainx-=3*3;
		else
			mainx=0;
	}
	if(key=='d'){
		if(mainx+mainl<1000)
			mainx+=3*3;
		else
			mainx=1000-mainl;
	}
	if(key=='f'){
		if(counf<=1){
			fire++;
			counf++;
		}
		
	
	}

}
	


	
	//place your codes for other keys here


int main()
{	
	//place your own initialization codes here.
	iInitialize(x_s,y_s, "Noman");
	return 0;
}
