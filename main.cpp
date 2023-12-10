#include <stdio.h>      /* printf, scanf, puts, NULL ,fflush*/
#include <iostream>
#include <string> 
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>
using namespace std;
#ifdef _WIN32
    #include <windows.h>

    void Sleep(unsigned milliseconds)
    {
        sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void Sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif

void system_pause();
void system_cls();
void Print_Out();
void Print_Out_Test(int _x,int _y,int _d);
bool Direct(int _x,int _y,int _d);

int Fx=1,Fy=30;
float x=1,y=1,Vx=0.1,Vy=0.1;
float V=0.141,th=0;
bool wall[32][32]={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1},
		{1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
		{1,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
		{1,0,1,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1},
		{1,1,1,1,1,0,1,1,0,1,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1},
		{1,0,0,1,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,0,1,0,1},
		{1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,0,1,1,0,0,0,1},
		{1,0,0,1,0,0,1,0,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,1},
		{1,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,1,0,1,1,1,1,1,0,1,0,0,1,0,0,1,0,1,0,1,1,1},
		{1,0,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,1},
		{1,1,1,0,1,0,0,0,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,1,1,0,1},
		{1,0,0,0,1,0,1,1,1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,0,0,1,0,0,1},
		{1,0,1,1,1,0,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,1,1,0,1,1},
		{1,0,0,0,0,0,1,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,1,1,0,0,0,1},
		{1,0,1,1,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1},
		{1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
		{1,0,1,0,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,1,0,1,0,1,1,1,0,1,0,0,0,1},
		{1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,1,1,0,1,1,1,1,0,0,0,1,1,1,0,1,1,1},
		{1,0,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,0,0,1,1,1,0,1},
		{1,0,1,1,1,1,1,0,1,0,1,0,0,1,0,1,0,1,1,0,0,0,1,1,0,1,0,0,0,1,0,1},
		{1,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1},
		{1,0,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,0,1},
		{1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,1,0,0,0,1,1,1,1,1,1,1,0,1,0,1,0,1},
		{1,0,1,1,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1,0,1},
		{1,0,0,0,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,0,1},
		{1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1},
		{1,0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,0,0,0,1,1,1,1,1,0,1,1,1},
		{1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
		};
int counter =0;

int main()
{
	while(1)
	{
		cout << "Please type in start point:\n";
		cin >> x >> y;
		if (x >=32) {cout << "x is too big!\n"; Sleep(2000); system_cls();continue;}
		else if (y>=32) {cout << "y is too big!\n"; Sleep(2000); system_cls();continue;}
		else if (x<0) {cout << "x is too small!\n"; Sleep(2000); system_cls();continue;}
		else if (y<0) {cout << "y is too small!\n"; Sleep(2000); system_cls();continue;}
		else if (wall[(int)y][(int)x]) {cout << "The position is in the walll!\n"; Sleep(2000); system_cls();continue;}
		else {break; cout << "\n\n";}
	}
	while(1)
	{
		cout << "Please type in final point:\n";
		cin >> Fx >> Fy;
		if (Fx >=32) {cout << "x is too big!\n"; Sleep(2000); system_cls();continue;}
		else if (Fy>=32) {cout << "y is too big!\n"; Sleep(2000); system_cls();continue;}
		else if (Fx<0) {cout << "x is too small!\n"; Sleep(2000); system_cls();continue;}
		else if (Fy<0) {cout << "y is too small!\n"; Sleep(2000); system_cls();continue;}
		else if (wall[(int)Fy][(int)Fx]) {cout << "The position is in the walll!\n"; Sleep(2000); system_cls();continue;}
		else break;
	}
	system_cls();
	for(int i=5;i>0;i--)
	{
		cout << "Start point is (" << x << "," << y << ")\n";
		cout << "Final point is (" << Fx << "," << Fy << ")\n";
		cout << "Maze start in " << i << " second\n";
		Sleep(1000);
		system_cls();
	}
		
		//cout << "please type in final point:\n";
		//cin >> Fx >> Fy;
	
	system_pause();

	while(1)
	{
		if((int)x!=Fx||(int)y!=Fy)
		{

			if (Direct((int)x,(int)y+1,1)==1) {y+=Vy;}
			if (Direct((int)x+1,(int)y,2)==1) {x+=Vx;}
			if (Direct((int)x,(int)y-1,3)==1) {y-=Vy;}
			if (Direct((int)x-1,(int)y,4)==1) {x-=Vx;}
			/*
			if(wall[int(y+Vy)][int(x+Vx)])
			{
				if(wall[int(y)][int(x+Vx)])
					Vx*=-1;
				else if (wall[int(y+Vy)][int(x)])
					Vy*=-1;
				else if((wall[int(y+Vy)][int(x+Vx)]))
				{
					Vx*=-1;Vy*=-1;
				}
			}
			x+=Vx;
			y+=Vy;*/
		}

		
		//Lay out

		counter++;
		if(counter>=7)
		{
			Print_Out();
			Sleep(100);
			system_cls();
			counter=0;
		}
	}
	system_pause();
	return 0;
}
void Print_Out()
{
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			if (i==(int)y&&j==(int)x)
			{
				cout << "鼠";
				continue;
			}
			else if(i==Fy&&j==Fx)
			{
				cout << " ♪";
				continue;
			}
			if(wall[i][j])
			{
				bool up=0,down=0,right=0,left=0;
				if(i-1>=0)
				{
					if(wall[i-1][j])
					up=true;
				}
				if(i+1<=31)
				{
					if(wall[i+1][j])
					down=true;
				}
				if(j-1>=0)
				{
					if(wall[i][j-1])
					left=true;
				}
				if(j+1<=31)
				{
					if(wall[i][j+1])
					right=true;
				}
				if(up&&down&&right&&left)
				{cout <<"─┼";}
				else if(up&&down&&right)
				{cout << " ├";}
				else if(up&&down&&left)
				{cout << "─┤";}
				else if(right&&left&&down)
				{cout << "─┬";}
				else if(up&&right&&left)
				{cout << "─┴";}
				else if(up&&right)
				{cout << " └";}
				else if(up&&left)
				{cout << "─┘";}
				else if(down&&right)
				{cout << " ┌";}
				else if(down&&left)
				{cout << "─┐";}

				else if(up||down)
				{cout << " │";}
				else if(right||left)
				{cout << "──";}
				else
				{cout <<" ※";}
			}
			else	//don't has wall
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << "(";
	cout << setw(5) << x;
	cout << ",";
	cout << setw(5) << y;
	cout << ") "<<endl;

	if (Direct((int)x,(int)y+1,1)==1) {cout << " ↓";}
	if (Direct((int)x+1,(int)y,2)==1) {cout << " →";}
	if (Direct((int)x,(int)y-1,3)==1) {cout << " ↑";}
	if (Direct((int)x-1,(int)y,4)==1) {cout << " ←";}
	cout << endl;

}
int testx=0;
bool Direct(int _x,int _y,int _d)
{
	//Print_Out_Test(_x,_y,_d);
	//Sleep(1);
	//system_cls();
	if(_x <0 || x>31 || _y <0 || y>31)	//
		return 0;
	else
	{
		if(wall[_y][_x])	//
			return 0;
		else
		{
			if (_x==1&&_y==30)
			{
				//cout << "(" << _x << "," << _y << ")";
				//system_pause();
				return 1;
			}
			else
			{
				int dd=0;
				if(_d!=1)
					if(_y-1>=0)
						if(!wall[_y-1][_x])
							dd+=Direct(_x,_y-1,3);
				if(_d!=2)
				{
					if(_x-1>=0)
						if(!wall[_y][_x-1])
							dd+=Direct(_x-1,_y,4);	
				}
				if(_d!=3)
				{
					if(_y+1<32)
						if(!wall[_y+1][_x])
							dd+=Direct(_x,_y+1,1);
				}
				if(_d!=4)
				{
					if(_x+1<32)
						if(!wall[_y][_x+1])
							dd+=Direct(_x+1,_y,2);	
				}
				return dd;
			}
		}
	}
}

void Print_Out_Test(int _x,int _y,int _d)
{
	for(int i=0;i<32;i++)
	{
		for(int j=0;j<32;j++)
		{
			if (i==_y&&j==_x)
			{
				switch (_d)
				{
					case 1:cout << " ↑";break;
					case 2:cout << " →";break;
					case 3:cout << " ↓";break;
					case 4:cout << " ←";break;
				}
				continue;
			}
			else if(i==Fy&&j==Fx)
			{
				cout << " ♪";
				continue;
			}
			if(wall[i][j])
			{
				bool up=0,down=0,right=0,left=0;
				if(i-1>=0)
				{
					if(wall[i-1][j])
					up=true;
				}
				if(i+1<=31)
				{
					if(wall[i+1][j])
					down=true;
				}
				if(j-1>=0)
				{
					if(wall[i][j-1])
					left=true;
				}
				if(j+1<=31)
				{
					if(wall[i][j+1])
					right=true;
				}
				if(up&&down&&right&&left)
				{cout <<"─┼";}
				else if(up&&down&&right)
				{cout << " ├";}
				else if(up&&down&&left)
				{cout << "─┤";}
				else if(right&&left&&down)
				{cout << "─┬";}
				else if(up&&right&&left)
				{cout << "─┴";}
				else if(up&&right)
				{cout << " └";}
				else if(up&&left)
				{cout << "─┘";}
				else if(down&&right)
				{cout << " ┌";}
				else if(down&&left)
				{cout << "─┐";}

				else if(up||down)
				{cout << " │";}
				else if(right||left)
				{cout << "──";}
				else
				{cout <<" ※";}
			}
			else	//don't has wall
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	cout << "(";
	cout << setw(5) << _x;
	cout << ",";
	cout << setw(5) << _y;
	cout << ")"<<endl;
	//system_pause();
	//system_pause();
}

void system_pause()
{
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');	
    	 printf("Press Enter key to continue..."); fgetc(stdin);
}
void system_cls()
{
	printf("\033[H\033[J");	//clear
	//printf("\e[2J\e[H");	//move but no clear
	//printf("\033[2J");	//hide old message but didn't claer
}