#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
using namespace std;
class MAP{						//main class
	protected:
	char map_shape[30][100];          //attribute     
	public:
		MAP()					//default constructor
		{
		}
		draw_map()			//functin to assign values to the map[grid]
		{
			char map[28][91]={
        	"#######################################################################################",
        	"#. . . . . . . . . . . . . . . . . . . . . . . . . . ####  . . . . . . . . . . . . .  #",//40
        	"#. . . . . . . . . . . . . . . . . .  ################ . . . . . . . . . . . . . . .  #",
        	"#. . . . . . . . . . . . . . . .  #####  . . . . . . . . . . . . . . . . . . . . . .  #",
			"#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .  #",
			"########################################################################## . . . . .  #",
        	" . . . . . . . E . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . .  #",
        	" . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . .  #",
        	" . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . .  #",
        	"#################. . . . . . . . . . ######. . . ####### . . . ####### . . . . . . .  #",
        	" . . . # . . . . . . . . . . . . . . #   . . . . # . . . . . . . . . # . . . . . . .  #",
        	" . . . # . . . . . . . . . . . . . . #   ####### # . . . . . . . . . # . . . . . . .  #",
        	" . . . # . . . . . . . ##.## . . . . #   # . . # # . . . . . . . . . # . . ### .## .  #",
        	" . . . . . . . . . . . # . # . . . . #   # . . # # . . . . . . # . . . . . # . . # .  #",
        	" . . . . . . . . . . . # . # . . . . . . . . . . # . . . . . . # . . . . . # . . # .  #",
        	" . . . .######## . . . # . # . . . # . . . . . . # . . . . . . ####### . . # . . # .  #",
        	" . . . . . . . # . . . # . # . . . # . . . . . . # . . . . . . . . . . . . # . . # .  #",
        	" . . . . . . . # . . . # . # . . . ############### . . . . . . . . . . ##### . . . .  #",
        	"###### . . . . # . . . # . # . . . . . . . . . . . . . . . . . . . . . # . . . . . .  #",
        	" . . # . . . . # . . . # . # . . . . . . . . . . . . . . . . . . . . . # . . # . # .  #",
        	" . . # . . . . # . . . ##.## . . . ######. . ####### . . . . . . . . . # . . # . # .  #",
        	" . . # . . . . # . . . . . . . . . # . . . . . . . # . . . . . . . . . # . . # . # .  #",
        	" . . # . . . . . . . . . . . . . . # . . . . . . . # . . . . . . . . . # . . # . # .  #",
        	" . . # . . . . . . . . . . . . . . ################# . . . . . . . . . # . . ##.## .  #",
        	" . . # . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . # . . . . . .  #",
        	" . . ################################################################### . . . . . .  #",
        	" . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . H  #",
        	"#######################################################################################"};
        	for(int i=0;i<29;i++)
        	{
        		for(int j=0;j<91;j++)
        		{
        			map_shape[i][j]=map[i][j];
				}
			}
		}
		gotoxy(int a,int b)		//function to control cursor movement
		{
			COORD c;
			c.X=b;
			c.Y=a;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
		}
		virtual	display()		//A virual function to pint the map[grid]
		{
			for(int i=0;i<28;i++)
			{
				for(int j=0;j<87;j++)
				{
					cout<<map_shape[i][j];	
				}
				cout<<endl;	
			}
		}
		int game_over()				//function controlling the game over fuctionality
		{
			int k=0;				//0=game over
			for(int i=0;i<28;i++)
			{
				for(int j=0;j<87;j++)
				{
					if(map_shape[i][j]=='.')    
					{
						k++;				// >0 =Game on
						break;	
					}	
				}
				if(k>0)				//checking the condition
				{
					break;
				}	
			}
			return k; 
		}
};
template <class t1,class t2>		//a template class 
class score{
	t1 Score;						//t1=int
	t2 name[10];					//t2=char
	const t2 type[7];		
	public:
		score():type{"MEDIUM"}		//initializiing constant attribute with level name
		{
			Score=0;			//initializing attribute
		}
		NAME(t2 a[10])			//function to vale to the name attribute
		{
			strcpy(name,a);
		}
		calculate_score()			//function to increment score
		{
			Score++;
		}
		t1 get_score()				//function to get the points/score
		{
			return Score;
		}
		write()					//function to write data on thr file
		{
			ofstream o;
			o.open("HIGH_SCORE.txt",ios::app);
			if(o.is_open())
			{
				o.write((char*)this,sizeof(*this));	
			}
			else
			{
				cout<<"FILE NOT OPENED"<<endl;
			}	
		}
		t1 total()				//function to calculate total records
		{
			ifstream i;
			t1 num=0;					
			i.open("HIGH_SCORE.txt",ios::in);		
			while(!i.eof())
			{
				if(i.read((char*)this,sizeof(*this)))	
				{
					num++;						
				}
				else
				{
					break;
				}
			}
			return num;			//returning number of records
		}
		sort_record(t1 num)			//num=total number of records
		{
			t1 k,j,m=0;				//k=outer loop,j=inner loop
			ifstream i;
			ofstream o;
			t1 lar=0,same[num];						//storing already stored sorted data
			o.open("HIGH_SCORE1.txt",ios::app); 	//opening temporary file to write sorted data
			for(k=0;k<num;k++)							
			{
				i.open("HIGH_SCORE.txt",ios::in);
				while(!i.eof())
				{
					if(i.read((char*)this,sizeof(*this)))
					{
						if(Score>lar)
						{
							for(j=0;j<num;j++)
							{
								if(Score!=same[j])			//comparing so that data doesn't get repeated 
								{
								}
								else
								{
									break;
								}
							}
							if(j==num)				//only true when data is not repeated
							{
								lar=Score;	
							}
						}
					}
				}
				same[m]=lar;				
				m++;
				i.close();
				i.open("HIGH_SCORE.txt",ios::in);			//opening file to read and then write sorted record in temporary file
				while(!i.eof())
				{
					if(i.read((char*)this,sizeof(*this)))
					{
						if(Score==lar)
						{
							o.write((char*)this,sizeof(*this));
							break;	
						}
					}
				}
				i.close();
				lar=0;	
			}
		}
		copy()					//copying data from One file
		{
			ifstream i;
			ofstream o;
			i.open("HIGH_SCORE1.txt",ios::in);			//temporay file
			o.open("HIGH_SCORE.txt",ios::trunc);		//opening file to erase data 
			o.close();										//closing file after erasing data
			o.open("HIGH_SCORE.txt",ios::app);			//opening file to write new data
			while(!i.eof())
			{
				if(i.read((char*)this,sizeof(*this)))		
				{
					o.write((char*)this,sizeof(*this));
				}
				else
				{
					break;
				}
			}
			i.close();
			o.close();
			o.open("HIGH_SCORE1.txt",ios::trunc);		//erasing data from temporary file
			o.close();
		}
		view_all()								//reading and displaying content of the file
		{
			ifstream i;
			i.open("HIGH_SCORE.txt",ios::in);
			while(!i.eof())
			{
				if(i.read((char*)this,sizeof(*this)))
				{
					display3();					//calling display3() function
				}
				else
				{
					break;
				}
			}	
		}
		display3()				//function to display content on screen
		{
			cout<<"NAME: "<<name<<"\tSCORE: "<<get_score()<<"\tLEVEL: "<<type<<endl;
		}
};
class enemy:public MAP{				//class inheriting properties from main class
	protected:
		int position_x1,position_y1;			//coordinates of enemy
	public:
		enemy()					//default constructor to assign coordinates of enemy
		{
			position_x1=6;
			position_y1=15;
		}				
};

class hero:public score<int,char>,public enemy{			//heo inheriting properties from score and enemy class
	protected:
	int position_x,position_y,count;			//attributes to store coordinates of hero,    count=used to over the game
	char ch;				 					//ch=used for element like "."
	public:
		hero()								//default constructor to assign values
		{
			position_x=26;					
			position_y=83;
			count =0;			
			ch=' ';	
		}
		move()					//function used to move both enemy and hero
		{	
			gotoxy(position_x,position_y);		//moving cursor to hero location
			ch=getch();							//asking user to choose direction
			if(ch==75)							//moving left
			{
				if((map_shape[position_x][position_y-2]=='.') || ((map_shape[position_x][position_y-2]==' ')) ) 
				{
					map_shape[position_x][position_y]=' ';
					cout<<map_shape[position_x][position_y];
					position_y-=2;
					map_shape[position_x][position_y]='H';
					gotoxy(position_x,position_y);
					cout<<map_shape[position_x][position_y];
				}
				else if((map_shape[position_x][position_y-2]=='#'))
				{
					gotoxy(position_x,position_y);
				}
				if((map_shape[position_x][position_y-2]=='.'))
				{
					calculate_score();
				}
			}
			else if(ch==80)			//moving down
			{
				if((map_shape[position_x+1][position_y]=='.') || (map_shape[position_x+1][position_y]==' ') )
				{
					map_shape[position_x][position_y]=' ';
					cout<<map_shape[position_x][position_y];
					position_x+=1;
					map_shape[position_x][position_y]='H';
					gotoxy(position_x,position_y);
					cout<<map_shape[position_x][position_y];
				}
				else if((map_shape[position_x+1][position_y]=='#'))
				{
					gotoxy(position_x,position_y);
				}
				if(map_shape[position_x+1][position_y]=='.')
				{
					calculate_score();
				}
			}
			else if(ch==77)     //moving right
			{
				if((map_shape[position_x][position_y+2]=='.') || (map_shape[position_x][position_y+2]==' ') )
				{
					map_shape[position_x][position_y]=' ';
					cout<<map_shape[position_x][position_y];
					position_y+=2;
					map_shape[position_x][position_y]='H';
					gotoxy(position_x,position_y);
					cout<<map_shape[position_x][position_y];
				}
				else if((map_shape[position_x][position_y+2]=='#') )
				{				
					gotoxy(position_x,position_y);
				}
				if(map_shape[position_x][position_y+2]=='.')
				{
					calculate_score();
				}
			}
			else if(ch==72)		//moving up
			{
				if((map_shape[position_x-1][position_y]=='.') || (map_shape[position_x-1][position_y]==' ') )
				{
					map_shape[position_x][position_y]=' ';
					cout<<map_shape[position_x][position_y];
					position_x-=1;
					map_shape[position_x][position_y]='H';
					gotoxy(position_x,position_y);
					cout<<map_shape[position_x][position_y];
				}
				else if((map_shape[position_x-1][position_y]=='#'))
				{
					gotoxy(position_x,position_y);
				}
				if(map_shape[position_x-1][position_y]=='.')
				{
					calculate_score();
				}
			}
			gotoxy(position_x1,position_y1); //moving cursor to enemy position(moving it in opposite direction of hero)
			if(ch==72)						//moving down
			{
				if((map_shape[position_x1+1][position_y1]=='.') || (map_shape[position_x1+1][position_y1]==' ') )
				{
					map_shape[position_x1][position_y1]=map_shape[position_x1+1][position_y1];
					cout<<map_shape[position_x1][position_y1];
					position_x1+=1;
					map_shape[position_x1][position_y1]='E';
					gotoxy(position_x1,position_y1);
					cout<<map_shape[position_x1][position_y1];
				}
				else if((map_shape[position_x1+1][position_y1]=='#'))
				{
					gotoxy(position_x1,position_y1);
				}
				else if(map_shape[position_x1+1][position_y1]=='H')		//function to over the game
				{
					count=10;		//10=enemy caught the hero
				}
			}
			else if(ch==80)		//moving up
			{
				if((map_shape[position_x1-1][position_y1]=='.') || (map_shape[position_x1-1][position_y1]==' ') )
				{
					map_shape[position_x1][position_y1]=map_shape[position_x1-1][position_y1];
					cout<<map_shape[position_x1][position_y1];
					position_x1-=1;
					map_shape[position_x1][position_y1]='E';
					gotoxy(position_x1,position_y1);
					cout<<map_shape[position_x1][position_y1];
				}
				else if((map_shape[position_x1-1][position_y1]=='#'))
				{
					gotoxy(position_x1,position_y1);
				}
				else if(map_shape[position_x1-1][position_y1]=='H')		//function to over the game
				{
					count=10;						//10=enemy caught the hero
				}
			}
			else if(ch==77)			//moving left
			{
				if((map_shape[position_x1][position_y1-2]=='.') || ((map_shape[position_x1][position_y1-2]==' ')) ) 
				{
					map_shape[position_x1][position_y1]=map_shape[position_x1][position_y1-2];
					cout<<map_shape[position_x1][position_y1];
					position_y1-=2;
					map_shape[position_x1][position_y1]='E';
					gotoxy(position_x1,position_y1);
					cout<<map_shape[position_x1][position_y1];
				}
				else if((map_shape[position_x1][position_y1-2]=='#'))
				{
					gotoxy(position_x1,position_y1);
				}
				else if(map_shape[position_x1][position_y1-2]=='H')		//function to over the game
				{
					count=10;					//10=enemy caught the hero
				}
			}
			else if(ch==75)		//moving left
			{
				if((map_shape[position_x1][position_y1+2]=='.') || (map_shape[position_x1][position_y1+2]==' ') )
				{
					map_shape[position_x1][position_y1]=map_shape[position_x1][position_y1+2];
					cout<<map_shape[position_x1][position_y1];
					position_y1+=2;
					map_shape[position_x1][position_y1]='E';
					gotoxy(position_x1,position_y1);
					cout<<map_shape[position_x1][position_y1];
				}
				else if((map_shape[position_x1][position_y1+2]=='#'))
				{				
					gotoxy(position_x1,position_y1);
				}
				else if(map_shape[position_x1][position_y1+2]=='H')		//function to over the game
				{
					count=10;			//10=enemy caught the hero
				}
			}
			view_score();      //calling function to display function in game play
		}
		friend int get_count(hero h);
		view_score()
		{
			gotoxy(28,0);			//moving cursor to a new location to display score
			cout<<"CURRENT SCORE:"<<get_score();	
		}
		
		
};
int get_count(hero h)		//function to get the count value to over the game
{
	return h.count;			
}

