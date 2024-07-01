#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/*********************************************************************************************************
This is to certify that this project is our own work, based on my personal efforts in studying and applying the
concepts learned. We have constructed the functions and their respective algorithms and corresponding code by
ourselves. The program was run, tested, and debugged by my own efforts. We further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
Cedric Francis Young, DLSU ID# 12372439  & <insert name>
*********************************************************************************************************/

/*
		STRUCT USAGE GUIDE -Cedric
	
	Cin STRUCT - Cinema
	
	PASS INFO OF ENTIRE CINEMA NO. - cinema[cinema no.]
	
	PASS INFO OF CINEMA'S SHOWTIME & SEATS - cinema[cinema no.].show[showtime no.]
	
	PASS INFO OF AVAILABILITY OF SEAT - cinema[cinema no.].show[showtime no.].seat[ROW][COLUMN]
	
	PASS INFO OF TITLE - cinema[cinema no.].title
	
	PASS INFO OF DESCRIPTION - cinema[cinema no.].desc
	
	PASS INFO OF RUNTIME - cinema[cinema no.].runtime
	
	
	
	CLOCK STRUCT
	time.hour
	time.min
	time.night
	
*/

//half = am or pm
typedef struct
{
	int hour;
	int min;
	char half[2];
}clock;


/*
	showtime start
	showtime end
	seat info; 1 if taken, 0 if empty
	no. of seats taken
*/
typedef struct
{
	clock showstart;
	clock showend;
	int seats[5][10];
	int takenS;
}st;

/*
	movie title
	movie description
	runtime
	showtimes
*/

typedef struct
{
	char title[50];
	char desc[100];
	int runtime;
	st show[6];
	
}cin;

//	 line prints out a line
void 
line(int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("-");
	
	printf("\n");
	

}

/*	funcAddtime returns the time in struct format with minutes added
	@param time - struct carrying time details
	@param addmin - minutes to be added to time
	
	contributed - C.Y.
*/
void 
funcAddtime(clock *time, int addmin)
{
	
	while(time->min>=60)
	{
		if(time->hour==12)
		{
			time->hour=1;
			if(time->half[0]=='a')
				strcpy(time->half,"pm");
			if(time->half[0]=='p')
				strcpy(time->half,"am");
		}
		else if(time->hour<12)
		{
			time->hour++;
		}
		time->min-=60;
	}
}

/*	funcDispClock prints out the time in clock format
	@param time - struct storing time info
	
	contributed - C.Y.
*/
void 
funcDispClock(clock time)
{
	printf("%d:",time.hour);
	
	if(time.min<10)
		printf("0%d",time.min);
	else
		printf("%d",time.min);
	
	time.half[2]='\0';
	printf("%s",time.half);
}

/*	funcInitSeats sets all seats to empty (0)
	@param a - specific showtime of a movie
	
	contributed - C.Y.
*/
void 
funcInitSeats(st *a)
{
	int i,j;
	
	a->	takenS=0;
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			a->seats[i][j]=0;
		}
	}
}

/*	funcDispSeats displays all seats with their number and letter, and shows taken seats as X

	contributed - C.Y.
*/
void 
funcDispSeats(st a)
{
	int i,j;
	
	for(i=0;i<5;i++)
	{
		line(52);
		for(j=0;j<10;j++)
		{
			if(a.seats[i][j]==0)
			{
				printf("| %c%d ",'A'+i,j+1);
			}
			else if(a.seats[i][j]==1)
			{
				printf("| X  ");
			}
		}
		printf("|\n");
	}
	line(52);
}

/*	funcLoading loads the data from a text file
	@param cinema - struct array to store info
	@param Fname - string input for file name to open
	
	@return 1 if file is found, return 0 if not found
	contributed - C.Y.
*/
int 
funcLoading(cin cinema[], char strFname[50])
{
	FILE * fp;
	int i,j,k,dn,rt,resp;
	char hour[2];
	char min[2];
	char strTime[7];
	
	
	//appends .txt if file name doesnt end with .txt
	if(strcmp(strFname+strlen(strFname)-4,".txt")!=0)
		strcat(strFname,".txt");
	
	fp=fopen(strFname,"r");
	
	if(fp==NULL)
	{
		line(35);
		printf(" File %s was not found\n", strFname);
		line(35);
		resp=0;	
	}
	else
	{
		line(35);
		printf("File %s found\n", strFname);
		line(35);
		fseek(fp,0,SEEK_SET);
		resp=1;
		while(!feof(fp))
		{

			fscanf(fp,"%d",&i);
			fscanf(fp,"\r%[^\n]s",cinema[i-1].title);
			fscanf(fp,"\r%[^\n]s",cinema[i-1].desc);
			fscanf(fp,"%d",&rt);
			cinema[i-1].runtime=rt;
			
			//scans showtimes
			for(j=0;j<6;j++)
			{
				fscanf(fp,"\r%[^\n]s",strTime);
				
				//searches for index of am/pm
				for(k=0;k<7;k++)
				{
		
					if(strTime[k]=='a'||strTime[k]=='p')
						dn=k;
				}
				
				//saves am/pm to struct info
				cinema[i-1].show[j].showstart.half[0]=strTime[dn];
				cinema[i-1].show[j].showstart.half[1]=strTime[dn+1];
				cinema[i-1].show[j].showstart.half[2]='\0';
				
				strTime[dn]='\0';
				//saves minutes to struct info
				strcpy(min,strTime+dn-2);
				cinema[i-1].show[j].showstart.min = atoi(min);
				
				strTime[dn-3]='\0';
				//saves hours to struct info
				strcpy(hour,strTime);
				cinema[i-1].show[j].showstart.hour = atoi(hour);

			}
		}
	}
	
	fclose(fp);
	return resp;
}

/*	funcLoadOption gets string input for filename to load
	@param cinema - struct array to store info
	
	@returns 1 if file is found, 0 if not found
	contributed - C.Y.
*/
int 
funcLoadOption(cin cinema[])
{

	char strFname[50];
	
	line(40);
	printf("Enter File Name: ");
	scanf("\r%[^\n]s",strFname);
	line(40);
	
	return funcLoading(cinema,strFname);
	
}

/*	funcMenu is a menu system to choose what task to perform
	@param cinema - struct array to store info
*/
void 
funcMenu(cin cinema[])
{
	int nLoop=1,nSelect;
	while(nLoop==1)
	{
		line(30);
		printf("    %s","Cinema Seating System\n");
		line(30);
		printf(" [1] Load Schedule\n [2] View Schedule\n [3] Seat Select\n [4] Search Movie\n [5] Exit\n");
		line(30);
		scanf("%d",&nSelect);
		switch(nSelect)
		{
			case 1:
				funcLoadOption(cinema);
				break;
			case 2:
				//function
				break;
			case 3:
				//function
				break;
			case 4:
				//function
				break;
			case 5:
				nLoop=0;
				break;
			default:
				break;
			
		}
	}
}


int 
main()
{
	//cinema number
	cin cinema[6];
	int i,j,pl=0;
	
	//preloading
	pl=funcLoading(cinema,"MovieSched.txt");
	
	line(30);
	if(pl==1)
		printf("    Preloading Successful\n");
	else
		printf("	Preloading Failed\n");
	line(30);
	printf("\n");
	
	while(pl==0)
		pl=funcLoadOption(cinema);

		
	
	//initializes all seats as empty
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
			funcInitSeats(&cinema[i].show[j]);
	}
	
	
	
	funcMenu(cinema);
	
	return 0;
}