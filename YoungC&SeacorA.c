#include <stdio.h>
#include <string.h>



/*********************************************************************************************************
This is to certify that this project is our own work, based on my personal efforts in studying and applying the
concepts learned. We have constructed the functions and their respective algorithms and corresponding code by
ourselves. The program was run, tested, and debugged by my own efforts. We further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
Cedric Francis Young, DLSU ID# 12372439  & <insert name>
*********************************************************************************************************/

typedef struct
{
	int time;
	int seats[50];
}show;

/*
	cinema number
	movie title
	movie description
	runtime
	seats
*/
typedef struct
{
	int cinema;
	char title[50];
	char desc[100];
	int runtime;
	show shtime[6];
	
	
}system;

void funcSystem(system mov[])
{
	int nLoop=1,nSelect;
	while(nLoop==1)
	{
		printf("%7s","Cinema Seating System\n");
		printf("-----------------------------\n");
		printf(" [1] Load Schedule\n [2] View Schedule\n [3] Seat Select\n [4] Search Movie\n");
		printf("-----------------------------\n");
		scanf("%d",&nSelect);
	}
}


int main()
{
	system mov[500];
	mov[0].cinema=1;
	funcSystem(mov);
	printf("%d",mov[1].cinema);

 	return 0;
}
