#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#include <conio.h>
// Constants for candidate names, voter list, and vote statistics files
#define CANDIDATE1 "Vladimir Putin"
#define CANDIDATE2 "Kim Jong-un"
#define CANDIDATE3 "Narendra Modi"
#define CANDIDATE4 "Joe Biden"
#define CANDIDATE5 "NOTA"
#define VOTER_LIST "voters.txt"
#define VOTE_STATISTICS "votestatistics.txt"

// Variables to store vote counts and invalid votes
int votesCount1=0, votesCount2=0, votesCount3=0, votesCount4=0, votesCount5=0;
int inValidvotes=0;
static int i=0;

struct vote		// Structure to store voter information
{
  int voter_id;
  char voter_name[50];
  char voter_surname[50];
  char voter_phone[15];
  char voter_password[30];
  int voter_check;
}v[50];

void interface1()	// Function to display the initial interface
{
    printf("\n\t\t=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*");
    printf("\n\t\t=*=*=*=*=*     \033[1;36m ONLINE VOTING SYSTEM \033[0m     =*=*=*=*=*");
    printf("\n\t\t=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*");
    printf("\n");
}

void interface2()	// Function to display the welcome interface
{
    printf("\n\t\t=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");
    printf("\n\t\t=*=*=*=*=*            \033[1;36m WELCOME \033[0m             =*=*=*=*=");
    printf("\n\t\t=*=*=*=*=*              \033[1;36m TO \033[0m                =*=*=*=*=");
    printf("\n\t\t=*=*=*=*=*        \033[1;36m ONLINE ELECTION \033[0m         =*=*=*=*=");
    printf("\n\t\t=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=");
    printf("\n");
    printf("\033[0m\n\n");
    getch();
}

void check_required()	// Function to initialize voter check status
{
    int noo=0;
    for(noo=0;noo<50;noo++)
    {
        v[noo].voter_check=0;  
    }
    getchar();
}

void saveVotingStatistics()		// Function saves the vote counts to a file.
{
    FILE* file = fopen(VOTE_STATISTICS, "w");
    if (file == NULL)
    {
        printf("Error: Could not open file for writing\n");
        return;
    }
    fprintf(file, "%d\n", votesCount1);
    fprintf(file, "%d\n", votesCount2);
    fprintf(file, "%d\n", votesCount3);
    fprintf(file, "%d\n", votesCount4);
    fprintf(file, "%d\n", votesCount5);
    fprintf(file, "%d\n", inValidvotes);

    fclose(file);
}

void castVote()	// Function to cast a vote
{
    system("cls");
    interface1();
    interface2();
    int choice;
    int var;
    int hi = 0, ji = 0;
    int hii = 0;
    char passwerd[30];
    printf("\n\t\t Enter your voter id : ");
    scanf("%d", &var);

    FILE* f = fopen(VOTER_LIST, "r");
    if (f == NULL)
    {
        printf("\n\t\t Error: Could not open file for reading");
        return;
    }
    // Read voter information from file
    while (fscanf(f, "%d,%[^,],%[^,],%d,%s\n", &v[hi].voter_id, v[hi].voter_name, v[hi].voter_surname, &v[hi].voter_phone, v[hi].voter_password) != EOF)
	{
        if (var == v[hi].voter_id)
        {
            fclose(f);
            do {
                printf("\n\t\t Enter your password: ");
                scanf("%s", passwerd);
                if (strcmp(v[hi].voter_password, passwerd) == 0)
				{
                    if (v[hi].voter_check == 0)
					{
                        printf("\n\t\t Voter name : %s", v[hi].voter_name);
                        printf("\n\t\t ### Please choose your Candidate ####");	// Display the candidates for voting
                        printf("\n\t\t 1. %s", CANDIDATE1);
                        printf("\n\t\t 2. %s", CANDIDATE2);
                        printf("\n\t\t 3. %s", CANDIDATE3);
                        printf("\n\t\t 4. %s", CANDIDATE4);
                        printf("\n\t\t 5. %s", CANDIDATE5);
                        printf("\n\n Input your choice (1 - 5) : ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                            case 1: votesCount1++; break;
                            case 2: votesCount2++; break;
                            case 3: votesCount3++; break;
                            case 4: votesCount4++; break;
                            case 5: votesCount5++; break;
                            default: inValidvotes++;
                        }
                        v[hi].voter_check++;
                        saveVotingStatistics(); // Update voting statistics
                        printf("\033[32m");
                        printf("\n\t\tThank you for voting");
                        printf("\033[0m\n\n");
                    }
                    else	 // If the voter ID is not found or the vote has already been cast
                    {
                        printf("\033[1;31m");
                        printf("\n\t\t Sorry you have already voted!!!");
                        printf("\033[0m\n\n");
                    }
                    hii = 0;
                }
                else {
                    printf("\033[1;31m");
                    printf("\n\t\tYou have entered the password incorrectly!!!");
                    printf("\n\t\t Please re-enter the password correctly.....");
                    printf("\033[0m\n\n");
                    hii++;
                }
            }while (hii != 0 && hii <= 3);
            break;
            system("cls");
        }
        hi++;
    }

    if (feof(f))
    {
        printf("\033[1;31m");
        printf("\n\t\t Sorry the voter id does not exist!!!");
        printf("\033[0m\n\n");
    }
    fclose(f);
    printf("\n\n Press any key to go back to the main menu.....");
    getch();
}

void votesCount()	// Function to display individual votes
{
	system("cls");
	interface1();
	interface2();
	printf("\n\t\t ##### Voting Statics ####");
	printf("\n\t\t %s - %d ", CANDIDATE1, votesCount1);

	printf("\n\t\t %s - %d ", CANDIDATE2, votesCount2);
	printf("\n\t\t %s - %d ", CANDIDATE3, votesCount3);
	printf("\n\t\t %s - %d ", CANDIDATE4, votesCount4);
	printf("\n\t\t %s - %d ", CANDIDATE5, votesCount5);
	printf("\n\t\t Invalid votes - %d ", inValidvotes);
	saveVotingStatistics();	// Update voting statistics
	fflush(stdin);
	getchar();
} 

void getLeadingCandidate()	// Function to determine & display leading candidate
{
    system("cls");
    interface1();
    interface2();
    printf("\n\n  #### Leading Candiate ####\n\n");
    if(votesCount1>votesCount2 && votesCount1>votesCount3 && votesCount1 >votesCount4)
    printf("[%s]",CANDIDATE1);
    else if (votesCount2>votesCount3 && votesCount2>votesCount4 && votesCount2 >votesCount1)
    printf("[%s]",CANDIDATE2);
    else if(votesCount3>votesCount4 && votesCount3>votesCount2 && votesCount3 >votesCount1)
    printf("[%s]",CANDIDATE3);
    else if(votesCount4>votesCount1 && votesCount4>votesCount2 && votesCount4 >votesCount3)
    printf("[%s]",CANDIDATE4);
    else
    printf("----- Warning !!! No-win situation----");    
    fflush(stdin);
    getchar();
}

void loadVotingStatistics()		// Function to load the vote counts from a file.
{
    FILE* file = fopen(VOTE_STATISTICS, "r");
    if (file == NULL) {
        votesCount1 = 0;
        votesCount2 = 0;
        votesCount3 = 0;
        votesCount4 = 0;
        votesCount5 = 0;
        inValidvotes = 0;
        return;
    }

    fscanf(file, "%d", &votesCount1);
    fscanf(file, "%d", &votesCount2);
    fscanf(file, "%d", &votesCount3);
    fscanf(file, "%d", &votesCount4);
    fscanf(file, "%d", &votesCount5);
    fscanf(file, "%d", &inValidvotes);

    fclose(file);
}

void voterList()	// Function to displays the list of voters
{
    system("cls");
    interface1();
    interface2();
    printf("\n\n  #### Voter List ####\n\n");

    FILE* f = fopen(VOTER_LIST, "r");
    if (f == NULL)
    {
        printf("Error: Could not open file for reading\n");
        return;
    }
    printf("Voter ID\tName\t\tSurname\t\tPhone\n");
    printf("-----------------------------------------------------\n");

    while (fscanf(f, "%d,%[^,],%[^,],%[^,],%s\n", &v[i].voter_id, v[i].voter_name, v[i].voter_surname, v[i].voter_phone, v[i].voter_password) == 5)
    {
        printf("%d\t\t%s\t\t%s\t\t%s\n", v[i].voter_id, v[i].voter_name, v[i].voter_surname, v[i].voter_phone);
    }
    fclose(f);
    fflush(stdin);
    getchar();
}

void returningofficer()		//  Login function for the returning officer
{ 
    system("cls");
    interface1();
    interface2();
    char returning_password[]="password";
    char enter_password[30];
    printf("\n\t\tEnter the password: ");
    scanf("%s",enter_password);
      if(strcmp(returning_password,enter_password)==0)
      {
       int choice_officer=0;
       do{
        printf("\n\t\t 1. Find Vote Count");
        printf("\n\t\t 2. Find leading Candidate");
        printf("\n\t\t 3. Show voter's list");
		printf("\n\t\t 0. Exit");
        printf("\n\t\t Please enter your choice : ");
        scanf("%d", &choice_officer);

        switch(choice_officer)
        {
        case 1: votesCount();break;
        case 2: getLeadingCandidate();break;
        case 3: voterList();break;
        default: printf("\n Please wait,you are being directed to home page");
        }
      }while(choice_officer!=0);
      }
      else
     
 {
        printf("\033[1;31m");
		printf("\n\t\t Please renter the password correctly");
        printf("\033[0m\n\n");
      }
fflush(stdin);
getchar();
}

void voterlogin()		// Login function for voters
{
    system("cls");
    interface1();
    interface2();
    int choice_voter;
    do
    {
        printf("\n\t\t 1.Cast your vote");
        printf("\n\t\t 0.Exit");
        printf("\n\t\t Please enter your choice:");
        scanf("%d",&choice_voter);
        
        switch(choice_voter)
        {
            case 1: castVote();break;
            default: printf("\n Please wait you are being directed to home page");
        }
    }
    while(choice_voter!=0);
    fflush(stdin);
    getchar();
}

void voterregistration()		// Function for voter registration
{
    system("cls");
    interface1();
    interface2();
    srand(time(0));		
    int id = rand();	// generates a random voter ID
    printf("\n\t\t Your voter id is %d", id);
    printf("\n\t\t Please enter the voter id allotted to you: ");
    scanf("%d", &v[i].voter_id);
    printf("\n\t\t Enter your name: ");
    scanf(" %s", v[i].voter_name);
    printf("\n\t\t Enter your surname: ");
    scanf(" %s", v[i].voter_surname);
    printf("\n\t\t Enter your phone number (10 digits): ");
    scanf(" %10s", v[i].voter_phone);
    printf("\n\t\t Enter your password: ");
    scanf(" %s", v[i].voter_password);
    printf("\033[32m");
    printf("\n\t\t You have successfully completed the registration!!!");
    printf("\033[0m\n\n");
    i++;
    id++;
    fflush(stdin);
    getchar();

    FILE* f = fopen(VOTER_LIST, "a");
    if (f == NULL)
    {
        printf("Error: Could not open file for writing\n");
        return;
    }

    fprintf(f, "%d,%s,%s,%s,%s\n", v[i - 1].voter_id, v[i - 1].voter_name, v[i - 1].voter_surname, v[i - 1].voter_phone, v[i - 1].voter_password);
    fclose(f);
}

int main()
{
    loadVotingStatistics();
    int choice;

    do {
        system("cls");
        interface1();
        interface2();
        printf("\n\t\t\t ###### Welcome to Election 2023 #####");
        Sleep(150);
        printf("\n\n\t\t If you are a new voter please register yourself first by selecting choice 3");
        Sleep(150);
        printf("\n\t\t 1. Returning officer login ");
        Sleep(150);
        printf("\n\t\t 2. Voter login ");
        Sleep(150);
        printf("\n\t\t 3. Voter registration");
        Sleep(150);
        printf("\n\t\t 0. Exit");
        Sleep(150);
        printf("\n\t\t Please enter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                returningofficer();
                break;
            case 2:
                voterlogin();
                break;
            case 3:
                voterregistration();
                break;
            default:
                Sleep(150);
                printf("\033[34m");
                printf("\n Thank you ");
                printf("\033[0m\n\n");
        }
    } while (choice != 0);
    fflush(stdin);
    sleep(100);
    return 0;
}

