#include<iostream>
#include<conio.h>
#include<windows.h>
#include<strings.h>
#include<fstream>
#include<math.h>
#define KEY_UP 72                 //Defining the ASCII of Up Arrow Key to Move Hero Character
#define KEY_DOWN 80					//Defining the ASCII of Down Arrow Key to Move Hero Character
#define KEY_LEFT 75						//Defining the ASCII of left Arrow Key to Move Hero Character
#define KEY_RIGHT 77 						//Defining the ASCII of right Arrow Key to Move Hero Character
using namespace std;
class Map
{
    public:
    char map[19][106];
    Map()
    {
    	char map_temp[19][106]=
{"########################################################################################################",
"||###################################################  ################################################||",
"|| ................................................  |...............................................  ||",
"|| ..  #########################################....  #########################################......  ||",
"|| ..  |.....................................  |.............................................  |.....  ||",
"|| ..  |...........................  |........  ######################...  #####..  ###..  ####|.....  ||",
"|| ...  ########...  #########.....  |.....................  |...............  |..  |........  |.....  ||",
"|| ...............  |.......  |....  |.......................................  |..  |................  ||",
"|| ...............  |.......  |.....  #######................................  |..  |................  ||",
"|| ...............  |....  ###..........................  #######......  |...  |..  |................  ||",
"|| ...............  |...  |....................................  |......  ##########...  ########....  ||",
"|| ..  |..........  |...  |...............  |..................  |.............................  |...  ||",
"|| ..  |####..  ####.....  ########...  ##################.....  |.............................  |...  ||",
"|| ..  |...............................................  |.....................................  |...  ||",
"|| ..  |...............................................  |.....................................  |...  ||",
"|| ...  ############################################....  #######################################....  ||",
"|| ..................................................................................................  ||",
"||#####################################################################################################||",
"#########################################################################################################"};

		for(int i=0;i<19;i++)
        {
        	for(int j=0;j<106;j++)
        	{
        		map[i][j]=map_temp[i][j];	
			}
		}
	}	                
	void Draw_Map()             //function To Print The Map
    {
    	system("cls");
        for(int i=0;i<19;i++)
        {
            cout<<map[i]<<endl;
        }
    }         
};
class Character
{
	
    protected:
    void gotoxy(short X,short Y)  // Function to Move to the Desired Position on Console 
    {
        COORD Position;   // Coordinates For The Position 
        Position.X=X;    //Structure Containing two short variable for postion setting
        Position.Y=Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Position); //Function for Setting desired Position on console             
    }
    public:
    virtual void Draw_Character()=0;
    virtual void move_Character(short x,short y)=0;
};
class Enemy:public Character
{
	Map m;
    char enemy;   //Enemy Character  
    short Ey[1]; //  Y-Co-ordinate of Enemy's Position
    short Ex[1]; //  X-Co-ordinate of Enemy's Position
    float Min[4];  //Sorted Array Of Distances
    float Distance[4];   //  Distance From All the Four Sides Of The Enemy To The Hero 

    public:
    Enemy()
    {
        Ex[0]=3;
        Ey[0]=2;
        enemy='E';                											
    }
    void Set_Data(short X,short Y)
    {
    	Ex[0]=X;
    	Ey[0]=Y;
	}
	short get_Eposx() const
	{
		return Ex[0];
	}
	short get_Eposy() const
	{
		return Ey[0];
	}
    void Draw_Character()         //Drawing Enenmy Character
    {
        gotoxy(Ex[0],Ey[0]);
        cout<<enemy;
    }
    void Cal_Distance(short  hx,short  hy)    //fuction to Calculate Shortest Distance between Hero and Enemy
    {
    	short x=hx;
    	short y=hy;
    	Distance[0]= sqrt((pow(x-Ex[0],2))+(pow(y-(Ey[0]-1),2)));    //Distance Formulae used For Calculating Distance                                   
		Distance[1]= sqrt((pow(x-Ex[0],2))+(pow(y-(Ey[0]+1),2)));    //         D=(sqrt((pow(x2-x1,2)+pow(y2-y1,2)) 
		Distance[2]= sqrt((pow(x-(Ex[0]-1),2))+(pow(y-Ey[0],2)));
		Distance[3]= sqrt((pow(x-(Ex[0]+1),2))+(pow(y-Ey[0],2)));		
		for(int i=0;i<4;i++)
		{
			Min[i]=Distance[i];
		}
		for(int i=0;i<4;i++)
		{
			for(int j=i;j<4;j++)
			{
				if(Min[i]>Min[j])
				{
					float temp=Min[i];         
					Min[i]=Min[j];                        // Sorting the Array to Find Minimum Distance
					Min[j]=temp;	
				}	
			}	
		} 	
	}
    void move_Character(short x,short y)    // Function to move the Enemy Towards The Hero By the Shortest Path Calculated
    {
    	Cal_Distance(x,y);
    	for(int i=0;i<4;i++)
    	{

    	if(Min[i]==Distance[0])
    	{
    		if(m.map[Ey[0]-1][Ex[0]]==' '||m.map[Ey[0]-1][Ex[0]]=='.')  // check to restrict the enemy within Walls of Map
    		{
    			if(m.map[Ey[0]][Ex[0]]=='.')
    			{
    				gotoxy(Ex[0],Ey[0]);
    				cout<<'.';
    				Ey[0]--;                                //changing position w.r.t Y Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;
				}
				else
				{
					gotoxy(Ex[0],Ey[0]);
    				cout<<'.';
    				Ey[0]--;                          //changing position w.r.t Y Co-ordinate      
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;
				}
				break;
			}
		}
		if(Min[i]==Distance[1])
    	{
    		if(m.map[Ey[0]+1][Ex[0]]==' '||m.map[Ey[0]+1][Ex[0]]=='.') // check to restrict the enemy within Walls of Map
    		{
    			if(m.map[Ey[0]][Ex[0]]=='.')
    			{
    				gotoxy(Ex[0],Ey[0]);
    				cout<<'.';
    				Ey[0]++;                        //changing position w.r.t Y Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;
				}
				else
				{
					gotoxy(Ex[0],Ey[0]);
    				cout<<'.';                    //changing position w.r.t Y Co-ordinate
    				Ey[0]++;
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;

				}
				break;
			}
		}
		if(Min[i]==Distance[2])
    	{
    		if(m.map[Ey[0]][Ex[0]-1]==' '||m.map[Ey[0]][Ex[0]-1]=='.') // check to restrict the enemy within Walls of Map
    		{
    			if(m.map[Ey[0]][Ex[0]]=='.')
    			{
    				gotoxy(Ex[0],Ey[0]);
    				cout<<'.';
    				Ex[0]--;                     //changing position w.r.t X Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;		
				}
				else
				{
					gotoxy(Ex[0],Ey[0]);
    				cout<<'.';
    				Ex[0]--;              //changing position w.r.t X Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;	
				}
				break;
    		}
    		
		}
		if(Min[i]==Distance[3])
    	{
    		if(m.map[Ey[0]][Ex[0]+1]==' '||m.map[Ey[0]][Ex[0]+1]=='.') // check to restrict the enemy within Walls of Map
    		{
    			if(m.map[Ey[0]][Ex[0]]=='.')
    			{
					gotoxy(Ex[0],Ey[0]);
					cout<<'.';
    				Ex[0]++;                            //changing position w.r.t X Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;
    				
				}
				else
				{
					gotoxy(Ex[0],Ey[0]);
					cout<<'.';
    				Ex[0]++;						//changing position w.r.t X Co-ordinate
    				gotoxy(Ex[0],Ey[0]);
    				cout<<enemy;
				}
				break;
			}
    	}
    }
	}	
};
class Hero:public Character
{
	Enemy E;
	Map m;
    char hero;   // Character Of Hero to choosen
    short hy;    //  X-Co-ordinate of Hero's Position
    short hx;	//  Y-Co-ordinate of Hero's Position
    int pts;   //  Points/Score
    public:
    Hero()
    {
    	hero='C';    //default Hero Character
    	pts=0;
        hx=100;
        hy=16;
    }
    void Set_Data(short hx,short hy,char hero)
    {
    	this->hx=hx;
    	this->hy=hy;
    	this->hero=hero;
    	pts=0;
	}
	short get_posx() const
	{
		return hx;
	}
	short get_posy() const
	{
		return hy;
	}
	int get_pts() const
	{
		return pts;
	}
    void Select_Character()                  // Choice Given To User To Select Hero Of Its Own Choice from A-Z
	{
    	char c;
    	cout<<"Select Your Own Hero Character"<<endl;
    	for(c='A';c>='A'&&c<='Z';c++)
    	{
    		cout<<c<<" ";
    		if(c=='H'||c=='P'||c=='X')
    		{
    			cout<<endl;
			}
		}
		cout<<endl;
		cout<<"Your Choice: "<<endl;
		cout<<"Hero: ";
		cin>>c;
		hero=c;	
	}                                                                
    void Draw_Character()              //Drawing the Character ON Map                                   
    {
        gotoxy(hx,hy);
        cout<<hero;
    }
    bool Check_EndGame()             //Checking Collission Between Enemy and Hero
    {
    	bool End=false;
    	short x=E.get_Eposx();
    	short y=E.get_Eposy();
    	if(hx==x&&hy==y)
    	{
    		End=true;
    		return End;
		}
		return End;
	}
    void move_Character(short x,short y)           //Moving the Hero Charcter
    {
    	char ch;
    	while(!Check_EndGame())           // Ending The Game When Collission between Enenmy and Hero
		{
			
    		switch(ch=getch())
    		{
    			case KEY_UP:
    				{
    					if(m.map[hy-1][hx]==' '||m.map[hy-1][hx]=='.')  // check to restrict the Hero to move within Walls of Map
    					{
    						if((m.map[hy-1][hx]=='.'))
    						{
    							pts++;             //Increasing Score when finds Food('.')
							}
    						gotoxy(hx,hy);
							m.map[hy][hx]=' ';	
							cout<<' ';
							hy--;           //changing position w.r.t Y Co-ordinate 
							gotoxy(hx,hy);
							cout<<hero;	
						}
						break;	
					}
				case KEY_DOWN:
					{
						if(m.map[hy+1][hx]==' '||m.map[hy+1][hx]=='.')
						{
							if((m.map[hy+1][hx]=='.'))
    						{
    							pts++;                //Increasing Score when finds Food('.')
							}
							gotoxy(hx,hy);
							m.map[hy][hx]=' ';
							cout<<' ';
							hy++;     			//changing position w.r.t Y Co-ordinate 
							gotoxy(hx,hy);
							cout<<hero;	
						}
						break;	
					}
				case KEY_LEFT:
					{
						if(m.map[hy][hx-1]==' '||m.map[hy][hx-1]=='.')
						{
							if((m.map[hy][hx-1]=='.'))
    						{
    							pts++;                           //Increasing Score when finds Food('.')
							}
							gotoxy(hx,hy);
							m.map[hy][hx]=' ';
							cout<<' ';
							hx--;                        //changing position w.r.t X Co-ordinate 
							gotoxy(hx,hy);
							cout<<hero;
						}
						break;			
					}
				case KEY_RIGHT:
					{
						if(m.map[hy][hx+1]==' '||m.map[hy][hx+1]=='.')
						{
							if((m.map[hy][hx+1]=='.'))
							{
								pts++;                    //Increasing Score when finds Food('.')
							}
							gotoxy(hx,hy);
							m.map[hy][hx]=' ';
							cout<<' ';
							hx++;                           //changing position w.r.t Y Co-ordinate 
							gotoxy(hx,hy);
							cout<<hero;	
						}
						break;		
					}		
			}
			E.move_Character(hx,hy);        //Calling the Function For Movement of ENEMY
		}
	}
	void Show_points()                       //  Diplaying Final Points After Game Is Over   
	{
		system("cls");
		cout<<"Game Over"<<endl;
		cout<<"Your Points: "<<pts<<endl;
	}
};
class User
{
	char Name[20];                
	int Score;
	const char difficulty[5];     
	public:
	User():difficulty{"HARD"}       // Setting the Difficulty Type
	{
		
	}
	User(char name[],int Score):difficulty{"HARD"}      // Setting the Difficulty Type and Obtainig User Name And Score
	{
		strcpy(Name,name);
		this->Score=Score;
	}
	void Set_Data(char name[],int Score)
	{
		strcpy(Name,name);
		this->Score=Score;
	}
	string get_Name() const
	{
		return Name;
	}
	int get_Score() const
	{
		return Score;
	}
	int WFiling()                    //Writing User Data In File
	{
		fstream File;
		File.open("User.txt",ios::in|ios::out|ios::app);
		if(!File.is_open())
		{
			cout<<"Unable To Open File";
			exit(0);
		}
		else
		{
			File.write((char *)this,sizeof(*this));
			File.close();
			total_Records();
		}
	}
	int total_Records()           // Calculating Total nmber Of Records
	{
		int i=0;
		ifstream File;
		File.open("User.txt",ios::in);
		if(!File.is_open())
		{
			cout<<"File Can Not Be Opened";
			exit(0);
		}
		File.read((char *)this,sizeof(*this));
		while(!File.eof())
		{
			i++;
			File.read((char *)this,sizeof(*this));
		}
		File.close();
		Sort_Records(i);
	}
	void Sort_Records(int Num)            // Sorting Total Number Of Records In the File In Descending Order
	{
		int Max[Num];
		ifstream File;
		ofstream f;
		File.open("User.txt",ios::in);
		if(!File.is_open())
		{
			cout<<"File Can Not Be Opened";
			exit(0);
		}
		for(int i=0;i<Num;i++)
		{
			File.read((char *)this,sizeof(*this));
			Max[i]=this->Score;
		}
		File.close();
		for(int i=0;i<Num;i++)
		{
			for(int j=i;j<Num;j++)
			{	
				if(Max[i]<Max[j])
				{
					int temp=Max[i];
					Max[i]=Max[j];
					Max[j]=temp;
				}
			}
		}
		f.open("temp.txt",ios::out|ios::app);
		for(int i=0;i<Num;i++)
		{
			File.open("User.txt",ios::in);
			File.read((char *)this,sizeof(*this));
			while(!File.eof())
			{
				if(Max[i]==this->Score)
				{
					f.write((char *)this,sizeof(*this));      //Copying Data from One File To The Other For Sorting Purpose
 				}
				File.read((char *)this,sizeof(*this));
			}
			File.close();
		}
		File.close();
		f.close();
		remove("User.txt");
		rename("temp.txt","User.txt");
	}
	int Show_LeaderBoard()                // Dispalying Data In File In Descending Order
	{
		ifstream File;
		ofstream temp;
		temp.open("User.txt",ios::out|ios::app);
		File.open("User.txt",ios::in);
		if(!File.is_open())
		{
			cout<<"Unable To Open File";
			exit(0);
		}
		else
		{
			try
			{
				
				File.read((char *)this,sizeof(*this));
				if(File.eof())
				{
					File.close();
					throw(1);
				}
				system("cls");
				cout<<"\t\t\t\tLeader Board"<<endl<<endl;
				while(!File.eof())
				{
					cout<<"Name: "<<this->Name<<"\t\t";
					cout<<"Difficulty: "<<this->difficulty<<"\t\t";
					cout<<"Score: "<<this->Score<<endl<<endl;
					File.read((char *)this,sizeof(*this));
				}
				File.close();	
			}
			catch(int a)
			{
				system("cls");
				cout<<"No Any Records Present In The File";
			}
		}
	}		
};
