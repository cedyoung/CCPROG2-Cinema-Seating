#include <stdio.h>
#include <string.h>



/*********************************************************************************************************
This is to certify that this project is our own work, based on my personal efforts in studying and applying the
concepts learned. We have constructed the functions and their respective algorithms and corresponding code by
ourselves. The program was run, tested, and debugged by my own efforts. We further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
Cedric Francis Young, DLSU ID# 12372439  & <insert name>
*********************************************************************************************************/

/*
		STRUCT USAGE GUIDE
	
	SYSTEM STRUCT - Cinema
	
	PASS INFO OF ENTIRE CINEMA NO. - cinema[cinema no.]
	
	PASS INFO OF CINEMA'S SHOWTIME & SEATS - cinema[cinema no.].show[showtime no.]
	
	PASS INFO OF AVAILABILITY OF SEAT - cinema[cinema no.].show[showtime no.].seat[ROW][COLUMN]
	
	
	
	CLOCK STRUCT
	time.hour
	time.min
	time.night
	
*/

//night = 1 if PM, night = 0 if AM
typedef struct
{
	int hour;
	int min;
	int night;
}clock;


/*
	showtime start
	showtime end
	available seats
*/
typedef struct
{
	clock showstart;
	clock showend;
	int seats[5][10];
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
	
}system;

//	 line prints out a line
void line(int length)
{
	int i;
	for(i=0;i<length;i++)
		printf("-");
	
	printf("\n");
	

}

/*	 funcAddtime returns the time in struct format with minutes added
	@param time - struct carrying time details
	@param addmin - minutes to be added to time
*/
void funcAddtime(clock *time, int addmin)
{
	
	while(time->min>=60)
	{
		if(time->hour==12)
		{
			time->hour=1;
			if(time->night==0)
				time->night=1;
			if(time->night==1)
				time->night=0;
		}
		else if(time->hour<12)
		{
			time->hour++;
		}
		time->min-=60;
	}
}

/*	funcDispClock prints out the time in clock format
	@param time - struct containing time details
*/
void funcDispClock(clock time)
{
	printf("%d:",time.hour);
	
	if(time.min<10)
		printf("0%d",time.min);
	else
		printf("%d",time.min);
		
	if(time.night==0)
		printf(" am");
	else
		printf(" pm");
}

/*	funcInitSeats sets all seats to empty (0)
	@param a - specific showtime of a movie
*/
void funcInitSeats(st *a)
{
	int i,j;
	
	for(i=0;i<5;i++)
	{
		for(j=0;j<10;j++)
		{
			a->seats[i][j]=0;
		}
	}
}

/*	funcDispSeats
*/
void funcDispSeats(st a)
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


void funcMenu(system cinema[])
{
	int nLoop=1,nSelect;
	while(nLoop==1)
	{
		printf("    %s","Cinema Seating System\n");
		line(30);
		printf(" [1] Load Schedule\n [2] View Schedule\n [3] Seat Select\n [4] Search Movie\n [5] Exit\n");
		line(30);
		scanf("%d",&nSelect);
		switch(nSelect)
		{
			case 1:
				//function
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


int main()
{
	//cinema number
	system cinema[6];
	int i,j;

	//initializes all seats as empty
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
		funcInitSeats(&cinema[i].show[j]);
	}
	
	
	funcMenu(cinema);
	        
}