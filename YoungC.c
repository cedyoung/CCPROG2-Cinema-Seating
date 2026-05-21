#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


/*********************************************************************************************************
This is to certify that this prokect is our own work, based on my personal efforts in studying and applying the
concepts learned. We have constructed the functions and their respective algorithms and corresponding code by
ourselves. The program was run, tested, and debugged by my own efforts. We further certify that I have not copied
in part or whole or otherwise plagiarized the work of other students and/or persons.
Cedric Francis Young, DLSU ID# 12372439
*********************************************************************************************************/

/*
		STRUCT USAGE GUIDE
	
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

//half = am or pm, nu for null
typedef struct
{
	int hour;
	int min;
	char half[3];
}clocky;


/*
	showtime start
	showtime end
	seat info; 1 if taken, 0 if empty
	no. of seats taken
*/
typedef struct
{
	clocky showstart;
	clocky showend;
	int seats[5][10];
	int takenS;
}st;


/*
	movie title
	movie description
	runtime
	showtimes
	number of showtimes
*/
typedef struct
{
	char title[100];
	char desc[200];
	int runtime;
	st show[6];
	int nShows;
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

/*	funcInitTime initiates time struct data as 0:00nu
	@param time - struct carrying time details
*/
void
funcInitTime(clocky *time)
{
	time->hour=0;
	time->min=0;
	strcpy(time->half,"nu");
}


/*	funcAddtime returns the time in struct format with minutes added
	@param time - struct carrying time details
	@param addmin - minutes to be added to time
*/
void 
funcAddtime(clocky *time, 
			int addmin)
{
	time->min+=addmin;
	while(time->min>=60)
	{
	
		if(time->hour<12)
		{
			
			if(time->hour==11)
			{
				if(time->half[0]=='a')
					time->half[0]='p';
				else if(time->half[0]=='p')
					time->half[0]='a';
			}
			time->hour++;
		}
		else if(time->hour==12)
		{
			time->hour=1;
		}
		time->min-=60;
	}
}

/*	funcDispClock prints out the time in clock format
	@param time - struct storing time info
*/
void
funcDispClock(clocky time)
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

/*	funcInitTitle initializes all titles as null
	@param cinema - struct array to store info
*/
void
funcInitTitle(cin *cinema)
{
	int i;
	for(i=0;i<6;i++)
		cinema[i].title[0]='\0';
	
}


/*	funcInitAlgo runs all initialization functions when called
*/
void
funcInitAlgo(cin *cinema)
{
	int i,j;
	funcInitTitle(cinema);
	
	/*
	initializes all seats as empty
	initializes all times as 00:00nu
	initializes all seat counter as 0
	*/
	for(i=0;i<6;i++)
	{
		for(j=0;j<6;j++)
			{
				funcInitSeats(&cinema[i].show[j]);
				funcInitTime(&cinema[i].show[j].showstart);
				funcInitTime(&cinema[i].show[j].showend);
				cinema[i].show[j].takenS=0;
			}
	}
}

/*	funcDispSeats displays all seats with their number and letter, and shows taken seats as X
	@param a - showtime info
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
				if(j==9)
					printf("|  X  ");
				else
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
*/
int 
funcLoading(cin *cinema, 
			char strFname[50])
{
	FILE * fp;
	int i,j,k,rt,resp,max;
	char strTime[8];
	
	
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
		funcInitAlgo(cinema);
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
			max=6;
			k=0;
			cinema[i-1].nShows=0;
			for(j=0;j<max;j++)
			{
				fscanf(fp,"\r%[^\n]s",strTime);
				
				if(strTime[strlen(strTime)-1]!='m')
				{
					max=j;
					if(!feof(fp))
						fseek(fp,-1,SEEK_CUR);
				}
				else
				{
				
					//saves am/pm to struct info
					strcpy(cinema[i-1].show[j].showstart.half,strTime+strlen(strTime)-2);
					strTime[strlen(strTime)-2]='\0';
					
						
					//saves minutes to struct info
					cinema[i-1].show[j].showstart.min = atoi(strTime+strlen(strTime)-2);
					strTime[strlen(strTime)-3]='\0';
					
				
					//saves hours to struct info
					cinema[i-1].show[j].showstart.hour = atoi(strTime);
				
					cinema[i-1].show[j].showend=cinema[i-1].show[j].showstart;
				
					funcAddtime(&cinema[i-1].show[j].showend,cinema[i-1].runtime);
					
					//check if showtime is past 9pm, saves as last showing if it is
					if(cinema[i-1].show[j].showstart.hour>=9&&cinema[i-1].show[j].showstart.half[0]=='p'&&cinema[i-1].show[j].showstart.hour!=12&&k==0)
					{
						cinema[i-1].nShows++;
						k=1;
					}
					else if(cinema[i-1].show[j].showstart.hour==12&&cinema[i-1].show[j].showstart.half[0]=='a'&&k==0)
					{
						cinema[i-1].nShows++;
						k=1;
					}
					else if(cinema[i-1].show[j].showstart.hour<10&&cinema[i-1].show[j].showstart.half[0]=='a'&&k==0)
					{
						cinema[i-1].nShows++;
						k=1;	
					}
					else if(cinema[i-1].show[j].showstart.hour==10&&cinema[i-1].show[j].showstart.min<30&&cinema[i-1].show[j].showstart.half[0]=='a'&&k==0)
					{
						cinema[i-1].nShows++;
						k=1;
					}
					else if(k==0)
						cinema[i-1].nShows++;
				}
			}
			
			
		}
	}
	
	fclose(fp);
	return resp;
}

/*	funcLoadOption gets string input for filename to load
	@param cinema - struct array to store info
	
	@returns 1 if file is found, 0 if not found
*/
int 
funcLoadOption(cin *cinema)
{

	char strFname[50];
	
	line(40);
	printf("Enter File Name: ");
	scanf("\r%[^\n]s",strFname);
	line(40);
	
	return funcLoading(cinema,strFname);
	
}



/*	funcSched displays the schedule of all cinemas
	@param cinema - struct array to store info
*/
void
funcSched(cin *cinema)
{
	int i,j;
	
	for(i=0;i<6;i++)
	{
		line(25);
		printf(" Cinema %d\n",i+1);
		line(25);
			
		if(cinema[i].title[0]!='\0')
			printf(" Now Showing: %s\n",cinema[i].title);
		else
		{
			printf(" No Movie Showing\n");
		}
		line(40);
		
	
		for(j=0;j<6;j++)
		{
			printf(" Showtime No. %d      ",j+1);
			if(
			(j+1>cinema[i].nShows)
			||(cinema[i].show[j].showstart.half[0]=='n')
			)
			{
				printf("Showing Unavailable\n");
			}
			else
			{
	
				if(cinema[i].show[j].showstart.hour<10)
					printf(" ");
					
				funcDispClock(cinema[i].show[j].showstart);
				printf("  -  ");
				
				if(cinema[i].show[j].showend.hour<10)
					printf(" ");
					
				funcDispClock(cinema[i].show[j].showend);
				printf("\n");
			}
		}
		
		line(40);
	}
}

/*	funcPrintTix prints out text files for tickets
	@param cinema - struct array to store info
	@param cNum - cinema number
	@param sNum - show number
	@param strSeat - Seat number
	@param nTnum - ticket number
	
	pre-condition: valid seat no., cinema and showing no. provided when called
*/
void
funcPrintTix(cin *cinema, 
			int cNum,
			int sNum, 
			char strSeat[4])
{
	char strTix[30]="Ticket-c";

	char cC[2],cS[2];
	FILE * fp;
	
	//adds the cinema and show no. to ticket name
	itoa(cNum+1,cC,10);
	itoa(sNum+1,cS,10);
	strcat(strTix,cC);
	strcat(strTix,"-s");
	strcat(strTix,cS);
	strcat(strTix,"-");
	
	//adds the seat no. to ticket name
	strcat(strTix,strSeat);
	
	strcat(strTix,".txt");
	
	fp=fopen(strTix,"w+");
	
	fprintf(fp,"%d\n",cNum+1);
	fprintf(fp,"%s\n",cinema[cNum].title);
	

	
	fprintf(fp,"%d:",cinema[cNum].show[sNum].showstart.hour);

	if(cinema[cNum].show[sNum].showstart.min<10)
		fprintf(fp,"0%d",cinema[cNum].show[sNum].showstart.min);
	else
		fprintf(fp,"%d",cinema[cNum].show[sNum].showstart.min);
	                
	fprintf(fp,"%s\n",cinema[cNum].show[sNum].showstart.half);
	
	
	
	fprintf(fp,"%s",strSeat);
	
	
	fclose(fp);
}



/*	funcSeatSelect allows the user to reserve up to 4 seats from a selected cinema showing
	@param cinema - struct array to store info
*/
void
funcSeatSelect(cin *cinema)
{
	int nCinsel=0, nShowsel=0,nLoop=1,nTix=5,i,nRow,nColumn,nInvalid=0,rep=0;
	char strSeat[4][4];
	
	strSeat[0][2]='\0';
	strSeat[1][2]='\0';
	strSeat[2][2]='\0';
	strSeat[3][2]='\0';
	
	
	line(30);
	printf("      Seat Select\n");
	line(30);
	
	while(nLoop==1)
	{
		
		printf("Select Cinema: ");
		scanf("%d",&nCinsel);
		line(25);
		printf("Select Showing: ");
		scanf("%d",&nShowsel);
		line(25);
		
		if(nCinsel<1||nCinsel>6||nShowsel<1||nShowsel>6)
		{
			nLoop=1;
		}
		else
		{
			nLoop=0;
			nCinsel--;
			nShowsel--;
			if(cinema[nCinsel].title[0]=='\0')
			{
				line(25);
				printf("No movie showing in cinema selected\n");
				line(25);
				nLoop=1;
			}
			else if(
			(nShowsel+1>cinema[nCinsel].nShows)||
			(cinema[nCinsel].show[nShowsel].showstart.half[0]=='n')
			)
			{
				line(25);
				printf("Showtime selected is unavailable\n");
				line(25);
				nLoop=1;
			}
			else if(cinema[nCinsel].show[nShowsel].takenS>=50)
			{
				line(25);
				printf("Showing has no available seats\n");
				line(25);
				nLoop=0;
				nTix=0;
			}
		}
	}
	
	
	
	while((nTix<0||nTix>4))
	{
		printf("No. of tickets: ");
		scanf("%d",&nTix);
		line(25);
		if(cinema[nCinsel].show[nShowsel].takenS+nTix>50)
		{
			nTix=5;
			printf("Only %d seats available; please reselect\n",50-cinema[nCinsel].show[nShowsel].takenS);
		}	
		line(25);
	}
	
	funcDispSeats(cinema[nCinsel].show[nShowsel]);
	line(25);
	
	i=0;
	rep=nTix;
	while(i<rep)
	{

		
		switch(i)
		{
			case 0:
				printf("1st Seat: ");
				break;
			case 1:
				printf("2nd Seat: ");
				break;
			case 2:
				printf("3rd Seat: ");
				break;
			case 3:
				printf("4th Seat: ");
				break;
		}

		scanf("%s",strSeat[i]);
		line(25);
		
		nInvalid=0;
		
		switch(strSeat[i][0])
		{
			case 'A':
				nRow=0;
				break;
			case 'B':
				nRow=1;
				break;
			case 'C':
				nRow=2;
				break;
			case 'D':
				nRow=3;
				break;
			case 'E':
				nRow=4;
				break;	
			default:
				nInvalid=1;
				break;	
		}
		
		
		nColumn=atoi(strSeat[i]+1);
	
		nColumn--;
	

		if(nColumn>9||nColumn<0)
			nInvalid=1;
			
		if(nInvalid==1)
		{
			line(25);
			printf("Invalid Input Detected\n");
			line(25);
		}
		else if(cinema[nCinsel].show[nShowsel].seats[nRow][nColumn]==1)
		{
			line(25);
			printf("Seat selected is taken\n");
			line(25);
		}
		else
		{
			cinema[nCinsel].show[nShowsel].takenS++;
			cinema[nCinsel].show[nShowsel].seats[nRow][nColumn]=1;
			funcDispSeats(cinema[nCinsel].show[nShowsel]);
			funcPrintTix(cinema,nCinsel,nShowsel,strSeat[i]);
			line(25);
			printf("Seat Reserved Successfully\n");
			line(25);
			i++;
		}
		
	}
	
	
}

/*	funcSearchTitle searches for movie matching given string and its info
	@param cinema - struct array to store info
*/
void
funcSearchTitle(cin *cinema)
{
	int i,j=-1,k,nLoop=1;
	char strM[100];
	
	while(nLoop==1)
	{
		line(40);
		printf(" Search Movie Title: ");
		scanf("\r%[^\n]s",strM);
		line(40);
		
		for(i=0;i<6;i++)
		{
			if(strcmp(cinema[i].title,strM)==0)
				j=i;
		}
		
		line(40);
		if(j==-1)
		{
			printf("No Movie found\n");
			nLoop=0;
		}
		else
		{
			printf(" Cinema %d\n",j+1);
			line(30);
			printf(" Now Showing: %s\n",cinema[j].title);
			line(60);
			
			for(k=0;k<6;k++)
			{
				printf(" Showtime No. %d      ",k+1);
				if(
				(k+1>cinema[j].nShows)||
				(cinema[j].show[k].showstart.half[0]=='n')
				)
				{
					printf("Showing Unavailable\n");
				}
				else
				{
					if(cinema[j].show[k].showstart.hour<10)
						printf(" ");
						
					funcDispClock(cinema[j].show[k].showstart);
					printf("  -  ");
				
					if(cinema[j].show[k].showend.hour<10)
					printf(" ");
						
					funcDispClock(cinema[j].show[k].showend);
					
					printf("  Available Seats: %d",50-cinema[j].show[k].takenS);
					
					printf("\n");
				
				}
				
			}
			nLoop=0;
			line(60);
		}
		
	}
	

}

/*funcSearchClock shows all showtimes within 1 hour of time given
	@param cinema - struct array to store info
*/
void
funcSearchClock(cin *cinema)
{

	int nflag,nCount=0,i,j,k,nLoop=1;
	
	char str1[8], str2[8];
	
	clocky s1,s2,sc;
	funcInitTime(&s1);
	funcInitTime(&s2);
	funcInitTime(&sc);
	
	while(nLoop==1)
	{

		line(30);
		printf(" Enter Showtime Minimum: ");
		scanf(" %[^\n]s",str1);
		line(30);
		sscanf(str1,"%d:%d%2s",&s1.hour,&s1.min,s1.half);
	
		s2=s1;
		line(30);
		printf(" Enter Showtime Maximum: ");
		scanf(" %[^\n]s",str2);
		line(30);
		sscanf(str2,"%d:%d%2s",&s2.hour,&s2.min,s2.half);
		
		nLoop=0;
		
		if(s1.half[1]!='m')
		{
			nLoop=1;
		}
		
		if(s2.half[1]!='m')
		{
			nLoop=1;
		}
		
		
	
	}
	
	sc=s1;
	
	for(i=0;i<6;i++)
	{
		nflag=0;
		for(j=0;j<6;j++)
		{
			
			k=0;
			while(k>-1)
			{
				/*
				k is time added to s1 until it matches s2. 
				creating a loop that searches for matching showtimes from 1st time given to 2nd time given
				when s1 = s2 OR k reaches more that 24 hours, the loop closes
				*/
				funcAddtime(&s1,k);
				
				if((strcmp(s1.half,cinema[i].show[j].showstart.half)==0)&&(s1.hour==cinema[i].show[j].showstart.hour)&&(s1.min==cinema[i].show[j].showstart.min))
				{
					
					
					if
					(
					(j+1>cinema[i].nShows)||
					(cinema[i].show[j].showstart.half[0]=='n')
					)
					{
						
					}
					else
					{
						if(nflag==0)
						{
							line(30);
							printf("Cinema No. %d\n",i+1);
							line(30);
							printf("Now Showing: %s\n",cinema[i].title);
							line(60);
							
						}
						
						nflag=1;
					
						printf(" Showtime No. %d      ",j+1);
						
						nCount++;
						
						if(cinema[i].show[j].showstart.hour<10)
							printf(" ");
						
						funcDispClock(cinema[i].show[j].showstart);
						printf("  -  ");
				
						if(cinema[i].show[j].showend.hour<10)
							printf(" ");
						
						funcDispClock(cinema[i].show[j].showend);
					
						printf("  Available Seats: %d",50-cinema[i].show[j].takenS);
					
						printf("\n");
						
						
					}
					
				}
				
				if(strcmp(s1.half,s2.half)==0&&s1.min==s2.min&&s1.hour==s2.hour)
					k=-5;
				
				if(k>1440)
					k=-5;
					
				//printf("%d\n",k);
				k++;
				s1=sc;
			}
			
		}
	}
	line(40);
	printf("  %d showings available\n",nCount);
	line(40);
	
}






/*	funcSearchMenu choose between searching by name or time
	@param cinema - struct array to store info
*/
void
funcSearchMenu(cin *cinema)
{
	int i,nLoop=1;
	

	while(nLoop==1)
	{
		line(30);
		printf("       Search Movie\n");
		line(30);
		printf(" [1] Search Title\n [2] Search Time\n [3] Return to Menu\n");
		line(30);
		scanf("%d",&i);
		
		if(i==1)
			funcSearchTitle(cinema);
		else if(i==2)
			funcSearchClock(cinema);
		else if(i==3)
			nLoop=0;
		
	}
	
	
}


/*	funcRank prints the data of the most viewed showings in order
	@param cinema  - struct array to store info
*/
void
funcRank(cin *cinema)
{
	int i,j,k,m,m2,a,b,c,d,temp,flag,g;
	int list[36];
	
	//initialize all ints as 0
	for(g=0;g<36;g++)
	{
		list[g]=0;
	}
	
	k=0;
	//saves all no. of taken seats from every cinema and showing to list
	for(i=0;i<6;i++)
	{
		
		for(j=0;j<6;j++)
		{	
			flag=0;
			
		
			
			if(cinema[i].show[j].takenS>0&&flag==0)
			{
				list[k]=cinema[i].show[j].takenS;
				k++;
			}
		}	
	
	}
	
	//sorts list of no. of taken seats to descending
	for(m=0;m<k;m++)
	{
		for(m2=0;m2<k;m2++)
		{
			if(list[m2]<list[m2+1])
			{
				temp=list[m2];
				list[m2]=list[m2+1];
				list[m2+1]=temp;
			}
		}
	}
	


	d=1;
	//displays all showings with seats taken that match current int value being accessed
	for(a=0;a<36;a++)
	{
		//while the current no. of taken seats being accessed is same as previous int value, go to next int value in list
		while(list[a-1]==list[a]&&list[a]!=0)
		{
			a++;
		}
		//if the current int value accessed in list is 0, end the loop immediately
		if(list[a]==0)
			a=36;
		
		if(list[a]>0)
		{
		
			for(b=0;b<6;b++)
			{
				for(c=0;c<6;c++)
				{
					//if the current showing's no. of seats taken is same as value in list, print out its data
					if(cinema[b].show[c].takenS==list[a])
					{
						line(40);
						printf(" #%d Most Watched Showing\n",d);
						line(40);
						printf(" %s\n",cinema[b].title);
						line(40);
						printf(" Cinema No. %d	Showtime No. %d\n",b+1,c+1);
						line(40);
						printf(" ");
						funcDispClock(cinema[b].show[c].showstart);
						printf("  -  ");
						funcDispClock(cinema[b].show[c].showend);
						printf("\n");
						line(40);
						printf(" Seats Taken: %d\n",cinema[b].show[c].takenS);
						line(40);
						printf("\n");
						d++;
					}
			
				}
			}
		}
	}
}



/*	funcSaveExit saves info in a text file upon exiting
	@param cinema  - struct array to store info
*/
void
funcSaveExit(cin *cinema)
{
	FILE * fp;
	time_t now = time(NULL);
	struct tm *tm_info = localtime(&now);
	char strFname[30];
	strftime(strFname,sizeof(strFname),"%d-%m-%Y.txt",tm_info);
	
	fp=fopen(strFname,"w+");
	
	int i,j,k,l,nCount=0;
	char cRow;
	
	for(i=0;i<6;i++)
	{
		fprintf(fp,"Cinema No: %d\n",i+1);
		fprintf(fp,"Title: %s\n",cinema[i].title);
		for(j=0;j<6;j++)
		{
			nCount=0;
			fprintf(fp,"Time: ");
			
			if(cinema[i].show[j].showstart.hour!=0)
			{
			
				fprintf(fp,"%d:",cinema[i].show[j].showstart.hour);
			
				if(cinema[i].show[j].showstart.min>10)
					fprintf(fp,"%d",cinema[i].show[j].showstart.min);
				else
					fprintf(fp,"0%d",cinema[i].show[j].showstart.min);
			
				fprintf(fp,"%s\n",cinema[i].show[j].showstart.half);
			}
			else
				fprintf(fp,"\n");
			
			fprintf(fp,"Taken Seats:\n");
			
			for(k=0;k<5;k++)
			{
				for(l=0;l<10;l++)
				{
					if(cinema[i].show[j].seats[k][l]==1)
					{
						nCount++;
						switch(k)
						{
							case 0:
								cRow='A';
								break;
							case 1:
								cRow='B';
								break;
							case 2:
								cRow='C';
								break;
							case 3:
								cRow='D';
								break;
							case 4:
								cRow='E';
								break;
							default:
								break;	
						}
						
						
						fprintf(fp,"%c%d",cRow,l+1);
						
						if(nCount<cinema[i].show[j].takenS)
						{
							fprintf(fp,", ");
						}
							
					}
				}
			}
			
			fprintf(fp,"\n\n");
			
			
		}
		if(i!=5)
			fprintf(fp,"\n");
	}

	
	fclose(fp);
}


/*	funcMenu is a menu system to choose what task to perform
	@param cinema - struct array to store info
*/
void 
funcMenu(cin *cinema)
{
	int nLoop=1,nSelect;
	while(nLoop==1)
	{
		line(30);
		printf("    %s","Cinema Seating System\n");
		line(30);
		printf(" [1] Load Schedule\n [2] View Schedule\n [3] Seat Select\n [4] Search Movie\n [5] Ranking\n [6] Exit\n");
		line(30);
		scanf("%d",&nSelect);
		switch(nSelect)
		{
			case 1:
				funcLoadOption(cinema);
				break;
			case 2:
				funcSched(cinema);
				break;
			case 3:
				funcSeatSelect(cinema);
				break;
			case 4:
				funcSearchMenu(cinema);
				break;
			case 5:
				funcRank(cinema);
				break;
			case 6:
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
	int pl=0;
	
	
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
	

	funcMenu(cinema);
	
	funcSaveExit(cinema);
	
	return 0;
}