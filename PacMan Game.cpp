#include <iostream>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include "MEDIUM.h"
#include "Hard.h"
#include"EASY.h"
using namespace std;
class menu{
	protected:
		int k;
		string level;
	public:
		menu()
		{
			system("cls");
			system("COLOR 0A");
			k=3;
			char game[12][86]={"######         ##           ######  ##           ##          ##          ##         #",
						   "#     #       #  #         #        # #         # #         #  #         # #        #",
						   "#     #      #    #       #         #  #       #  #        #    #        #  #       #",
						   "#     #     #      #     #          #   #     #   #       #      #       #   #      #",
						   "#     #    #        #    #          #    #   #    #      #        #      #    #     #",
						   "#######   ############   #          #     # #     #     ############     #     #    #",
						   "#        #            #  #          #      #      #    #            #    #      #   #",
    					   "#       #              #  #         #             #   #              #   #       #  #",
						   "#      #                #  #        #             #  #                #  #        # #",
    					   "#     #                  #  ######  #             # #                  # #         ##"};
			for(int i=0;i<12;i++)
			{
				gotoxy(k,20);
				k++;
				for(int j=0;j<86;j++)
				{
					cout<<game[i][j];	
				}
				cout<<endl;
			}
			k+=2;
			gotoxy(k,25);
			if(level!="EXIT")
			{
				menu1();	
			}
			
			
		}
		void gotoxy(int a,int b)
		{
			COORD c;
			c.X=b;
			c.Y=a;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
		}
		void menu2()
		{
			string diff[3]={"EASY","MEDIUM","HARD"};
			for(int i=0;i<2;i++)
			{	
				gotoxy(k,25);
				cout<<"SELECT Difficulty Level";
				k++;
				gotoxy(k,25);
				cout<<"1)EASY                   ";
				k++;
				gotoxy(k,25);
				cout<<"2)MEDIUM                ";
				k++;
				gotoxy(k,25);
				cout<<"2)HARD                  ";
				k++;
				gotoxy(k,25);
				cout<<"ENTER CHOICE: ";
				fflush(stdin);
				cin>>level;
				try
				{
					if(level==diff[0])
					{
						system("cls");
						system("COLOR 0B");
						EASY();
					}
					else if(level==diff[1])
					{
						system("cls");
						system("COLOR 0C");
						MEDIUM();
					}
					else if(level==diff[2])
					{
						system("cls");
						system("COLOR 0D");
						HARD();
					}
					else
					{
						throw(1);
					}
					if(cin.fail())
					{
						throw(1);
					}
					i=2;
				}
				catch(int a)
				{
					
					gotoxy(k,25);
					cout<<"                                                         ";
					gotoxy(k,25);
					cout<<"Invalid Difficulty Kindly Enter Full Name Of Difficlty In Capital letters";
					getch();
					gotoxy(k,25);
					cout<<"                                                                                 ";
					k=k-4;
					i=0;
				}
			}
			
		}
		void menu1()
		{
			char ch;
			cout<<"USE ARROW KEYS TO MOVE AND S TO SELECT OPTION";
			k++;
			gotoxy(k,25);
			cout<<"1)PLAY GAME";
			k++;
			gotoxy(k,25);
			cout<<"2)HOW TO PLAY";
			k++;
			gotoxy(k,25);
			cout<<"3)VIEW_SCORES";
			k++;
			gotoxy(k,25);
			cout<<"4)EXIT              ";
			for(; ;)
			{
				ch=getch();
				if(ch==72 && k==18)
				{
				}
				else if(ch==80 && k==21)
				{
				}
				else if(ch==72)
				{
					k--;
					gotoxy(k,25);
				}
				else if(ch==80)
				{
					k++;
					gotoxy(k,25);
				}
				else if(ch==115)
				{
					break;
				}
			}
			if(k==18)
			{
				gotoxy(k,25);
				menu2();
			}
			else if(k==19)
			{
				k-=1;
				gotoxy(k,25);
				cout<<"CONTROLS:                          ";
				k++;//19
				gotoxy(k,25);
				cout<<"> = MOVE RIGHT";
				k++;//20
				gotoxy(k,25);
				cout<<"< = MOVE LEFT";
				k++;//21
				gotoxy(k,25);
				cout<<"^ = MOVE UP";
				k++;//22
				gotoxy(k,25);
				cout<<"? = MOVE DOWN";
				getch();
				k=22;
				gotoxy(k,25);                                             
				cout<<"                               ";
				k=17;
				gotoxy(k,25);
				menu1();	
		}
		else if(k==20)
		{
			k-=2;
			for(int i=0;i<2;i++)
			{
				gotoxy(k,25);
				cout<<"Enter The Name Of Dificulty You Want To See the Leader Board"<<endl;
				k++;
				gotoxy(k,25);
				cout<<"1)EASY                   ";
				k++;
				gotoxy(k,25);
				cout<<"2)MEDIUM                ";
				k++;
				gotoxy(k,25);
				cout<<"2)HARD                  ";
				k++;
				gotoxy(k,25);
				cout<<"ENTER CHOICE: ";
				cin>>level;
				try
				{
					if(level=="EASY"||level=="MEDIUM"||level=="HARD")
					{
						if(level=="EASY")
						{
							leaderboard l;
							system("cls");
							l.show_score();
							getch();
						}
					else if(level=="MEDIUM")
					{
						class hero h;
						system("cls");
						cout<<"\t\t\tLearder Board "<<endl<<endl;
						h.view_all();
						getch();
						system("cls");
					}
					else if(level=="HARD")
					{
						User U;
						system("cls");
						U.Show_LeaderBoard();
						getch();
						system("cls");
					}		
				}
				else
				{
					throw(1);
				}
				if(cin.fail())
				{
					throw(1);
				}
				i=2;
				}
				catch(int a)
				{
					gotoxy(k,25);
					cout<<"                                                         ";
					gotoxy(k,25);
					cout<<"Invalid Difficulty Kindly Enter Full Name Of Difficlty In Capital letters";
					getch();
					gotoxy(k,25);
					cout<<"                                                                                 ";
					k=k-4;
					i=0;
				}
			}
			menu();
			}
		else 
		{
			level="EXIT";
		}
	}
/*	string get_level()
	{
		return level;
	}*/
int MEDIUM()
	{	
		class hero h1;
		int a,b,c,d;
		char name[10];
		cout<<"ENTER YOUR NAME"<<endl;
		cin>>name;
		system("cls");
		h1.NAME(name);
		h1.draw_map();
		h1.display();
		int j;
		for( ; ; )
		{
			h1.move();
			a=get_count(h1);
			if((a==10))
			{
				system("cls");
				cout<<"GAME OVER"<<endl;
				cout<<"YOUR SCORE: "<<h1.get_score();
				
				break;
			}
			a=h1.game_over();
			if(a==0)
			{
				system("cls");
				cout<<"YOU WON"<<endl;
				cout<<"YOUR SCORE: "<<h1.get_score();
				
				break;
			}
		}
		h1.write();
		j=h1.total();
		h1.sort_record(j);
		h1.copy();
		getch();
		system("cls");
		menu();	
 	    return 0;	
	}
void HARD()
	{
		system("cls");
		char Name[20];			
		short x=0,y=0;
		User U1;
    	Map Hard;
    	Hero H;
    	Enemy E;
    	cout<<"Enter Your Name: ";
    	fflush(stdin);
    	gets(Name);
    	fflush(stdin);
    	Hard.Draw_Map();
    	H.Select_Character();
    	H.Draw_Character();
    	E.Draw_Character();
		H.move_Character(x,y);
		x=H.get_pts();
		U1.Set_Data(Name,x);
		U1.WFiling();
		H.Show_points();	
    	getch();
    	getch();
    	system("cls");
		menu(); 
	}
void EASY()
	{
		hidecursor();
	srand(time(NULL));
	string name, ch;
	cout << "Enter your username : ";
	fflush(stdin);
	getline(cin, name);
	for(int i = 0; i < name.size(); i++)
		if(name[i] == ' ') name[i] = '_';
	system("cls");
	easy_difficulty m;
	leaderboard l(name);
	m.draw_map();
	int n = m.get_enemycount();
	vector<enemy_easy> e(n);
	pacman p;
	int win = 0;
	auto start = chrono::high_resolution_clock::now();
	while(true)
	{
		p.move();
		checkWin(&win, p, n, e);
		if (win == 1 || win == -1)
		{
			break;
		}
		else
		{
			updateEnemy(n, e, p);
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end - start;
	l.write(p, diff.count());
	showcursor();
	system("cls");
	getch();
	printMessage(win, diff.count());
	p.show_points();
	cout << "Enter any key to exit: ";
	keybd_event(VK_ESCAPE, 0, 0, 0);
	cin >> ch;
	menu();		
	}

};
int main()
{
	class menu m1;
	
	
	return 0;	
}

