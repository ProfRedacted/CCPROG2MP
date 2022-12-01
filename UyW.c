#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//custom header file for text color
#include "color.h"
/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
Wesley King Chen Uy, DLSU ID# 12133892
*********************************************************************************************************/
struct PlayerInfo
{
    char Name[4];
    int Streak;
    int time;
    int BStreak;
    int Frequency[6];
};
typedef struct PlayerInfo PlayerList;
/* 
    Stop Stop the program allowing the user to read for a while
    @param cEmpty Just a useless char to be scan for the player
*/
void 
Stop()
{
    char cEmpty = '&';
    printf("\nPress any key to continue\n");
    scanf(" %c", &cEmpty);
}
/* Capitalized if there is a lower case letter
    @param LowerWord[] The string checking if it capitalized or not
    @param i Counter for the loop

    @return CapWord or Capitalized version of the original word
*/
char 
*Capitalized(char LowerWord[])
{
    int i = 0;
    char *CapWord = LowerWord;
    while (i < strlen(LowerWord))
    {
        //Check if its a lowercase word
        if (LowerWord[i] >= 'a' && LowerWord[i] <= 'z')
        {
            CapWord[i] = LowerWord[i] -= 32;
        }
        i++;
    }
    return (CapWord);
}
/* CheckLetter Check if the char in the string are letter
    @param Word[] The work being check
    @param i Counter

    @return 0 if found special character or 1 if it's all letter
*/
int
CheckLetter(char Word[])
{
    int i;
    //Count the word and set it to max limit
    for (i = 0; i < strlen(Word); i++)
    {
        //Check if it's not a letter then return 0  
        if (!((Word[i] >= 'A' && Word[i] <= 'Z') || (Word[i] >= 'a' && Word[i] <= 'z')))
        {
            return 0;
        }
    }
    return 1;
}
/* CheckLength check the lenght of the word
    @param Word[] The word being question
    @return 1 if the word is 5 letters or 0 if it not
*/
int 
CheckLength(char Word[])
{    
    return (strlen(Word) == 5);
}
/*ValidWord Check if the input is valid or not
    @param Dict[] The dictionary array
    @param Input[] The input from earlier
    @param words the amount of words
    @param i index/counter
    
    @return 1 if the word is found inside the dict file. 0 if it can't*/
int 
ValidWord(char Dict[][6],
            char Input[], 
            int words)
{
    int i;
    //Loop until the max amount of words
    for (i = 0;i < words; i++)
    {
        //It will pass if the word is found
        if (strcmp(Capitalized(Dict[i]),Input) == 0)
        {
            return 1;
        }
    }
    return 0;
}
/* MainMenu is the main menu
    @param nDecision the number to be store in the game 

    @return nDecision the value to send back to the main*/
int 
MainMenu()
{
    int nDecision = 0;
    do
    {
        printf("Welcome to C Wordle\n");
        purple();
        printf("================================================================================\n");
        reset();
        printf("To begin, pick a number\n");
        printf("1. Classic\n");
        printf("2. Classic (Manual Input)\n");
        printf("3. Head-to-Head\n");
        printf("4. Zen\n");
        printf("5. Statistics\n");
        printf("6. Help\n");
        printf("7. Exit\n"); 
        printf("8. Delete Player\n");
        printf("9. Add new words\n");
        printf("Select a number:");
        scanf("%d",&nDecision);
    } while (nDecision > 8 && nDecision < 1);
    return nDecision;
}
/* SubMenu is the Statistic menu
    @param nDecision the number to be store in the game 

    @return nDecision the value to send back to the Function
*/
int SubMenu()
{
    int nDecision;
    printf("Welcome to the Statistics Menu\n");
    printf("Select your number\n");
    printf("1) Player Statistics\n");
    printf("2) All Time Score Statistics\n");
    printf("3) All Time Rankings\n");
    printf("0) Exit\n");
    printf("Select a number:");
    scanf("%d",&nDecision);
    return nDecision;
}
/* SubStatMenu is the Sub-Statistic menu
    @param nDecision the number to be store in the game 

    @return nDecision the value to send back to the Function
*/
int SubStatMenu()
{
    int nDecision;
    printf("All Time Rankings\n");
    printf("1)Best Streak\n");
    printf("2)N-turns win\n");
    printf("3)Best time\n");
    do
    {
        if (nDecision < 1 || nDecision > 3)
        {
            red();
            printf("Invalid Input\n");
            reset();
        }
        printf("Select a number:");
        scanf("%d",&nDecision);
    } while (nDecision < 1 || nDecision > 3);
    return nDecision;
}
/*
    MainGame is the main function of the game without this the wordle game wouldn't be working
    @param *Answer The chosen answer for the word
    @param MaxAttempt The amount of attempt the player can do before losing
    @param Dict[][6] The list of valid words
    @param words The amount of words in 
    @param *Result The word result out of the main algorithm
    @param Guess[] The input of the user
    @param nAttempt Count how many attempt the player did
    @param i,j Counter for the loop function
    @param Mark[] An indicator if the letter has been scanned or not

    @return nAttempts The amount of attempt the player did.
*/ 
int 
MainGame(char *Answer, 
        int MaxAttempt, 
        char Dict[][6], 
        int words)
{
    char *Result;
    char Guess[6];
    int nAttempt = 0;
    int Complete = 0;
    int i = 0;
    int j = 0;
    int Mark[5];
    Result = malloc (6 * sizeof(*Result));
    //6 attempts
    while (nAttempt != MaxAttempt && Complete == 0)
    {
        //Convert to xxxxx once the loop is done and didn't solve it yet
        strcpy(Result,"xxxxx\0");
        //Marker are being intialized and resetted after a loop
        Mark[0] = 0;
        Mark[1] = 0;
        Mark[2] = 0;
        Mark[3] = 0;
        Mark[4] = 0;
        //Scan the input word by the player and will keep on looping till the word is valid
        printf("You made %d attempt/s\n",nAttempt);
        printf("Enter your guess word\n");
        do
        {
            scanf("%s",Guess);
            Capitalized(Guess);
            if (!ValidWord(Dict,Guess,words))
            {
                printf("The word is not valid\n");
                printf("Enter a new one\n");
            }
        }while (!ValidWord(Dict,Guess,words));
        //Capitalized the word
        Capitalized(Guess);
        //Prevent more than 5 characters
        Answer[5] = '\0';
        Guess[5] = '\0';
        if (strcmp(Answer, Guess) != 0)
        {
            //first loop scan for matches
            for (i = 0;i <= 4; i++)
            {
                if (Answer[i] == Guess[i])
                {
                    Result[i] = Answer[i];
                    Mark[i] = 1;
                }
            }
            //second loop to scan for same letter but in different places
            for (i = 0; i <= 4; i++)
            {
                for (j = 0; j <= 4; j++)
                {
                    //While mark is not activated and Result[i] is still 'x' and Guess[i] has a similar character as [j]
                    if ((Guess[i] == Answer[j]) && Mark[j] == 0 && Result[i] == 'x') 
                    {
                        Result[i] = '+';
                        Mark[j] = 1;
                        j = 5;
                    }
                }
            }
        }
        //If the word is solved this function break the loops
        else if ((strcmp(Answer, Guess) == 0))
        {
            strcpy(Result,Answer);
            Complete = 1;
        }
        printf("%s\n",Result);
        nAttempt++;
    }
    //If the game is done and the player got it right
    if ((strcmp(Answer, Guess) == 0)) 
    {
        green();
        printf("You got it right the word is %s\n",Answer);
        reset();
        printf("You took %d attempts\n",nAttempt);
        free(Result);
        return nAttempt;
    }
    //If the game is done and the player got it wrong
    else
    {
        red();
        printf("You didn't guess it right, the word is %s\n",Answer);  
        reset();
        printf("Press any key to continue\n");
        free(Result);
        return -1;
    }
}
/* EnterManual will scan the chosen word and will check if the chosen word is valid
    @param Dict[][6] The dictionary array
    @param words The amount of words inside the dict array
    @param char *PickW Is where the manual input is gonna be stored
    
    @return *PickW after it been checked
*/
char 
*EnterManual(char Dict[][6],
            int words)
{
    char* PickW;
    PickW = malloc(6 * sizeof(*PickW));
    do  
    {
        printf("Enter the word for the game:");
        scanf("%s",PickW);
        Capitalized(PickW);
        //If the word cannot be found in the dictionary file
        if (!ValidWord(Dict,PickW,words))
        {
            red();
            printf("Error, Word is not part of dict can't be used\n");
            reset();
        }
    } while (!ValidWord(Dict,PickW,words));
    return PickW;
}
/*
    CheckProfile Check if the player has a profile or not
    @param MasterList[] The List of player and their own stats
    @param Name[] Manual input of the player
    
    @return i if found, -1 if the player is not found
*/
int 
CheckProfile (struct PlayerInfo MasterList[],
                            char Name[])
{
    int i;
    for (i = 0; i < 20;i++)
    {
        if (strcmp(MasterList[i].Name,Name) == 0)
        {
            //return the profile number position
            return i;
        }
    }
    //return if it can't find the profile name
    return -1;
}
/*
    CheckSpace Check if the Masterlist still has space for new players
    @param MasterList[] The List of player and their own stats
    @param Name[] Manual input of the player
    
    @return i if found, -1 if not found
*/
int 
CheckSpace(struct PlayerInfo MasterList[])
{
    int i;
    for (i = 0; i < 20;i++)
    {
        if (strcmp(MasterList[i].Name,"\0") == 0)
        {
            //return the space of the empty name
            return i;
        }
    }
    //return if the name list is full
    return -1;
}
/*
    CheckName Check if name is valid
    @param Name The manual input name of the player
    
    @return Capitalized form of Name
*/
char 
*CheckName(char *Name)
{
    //Check name if it's 3 letters and it's all valid
    while (strlen(Name) != 3 || !CheckLetter(Name)) 
    {
        red();
        printf("Invalid Name\n");
        reset();
        printf("Enter a new one\n");
        scanf("%s",Name);
    } 
    return Capitalized(Name);
}
/*
    IntialFreq Intialized the frequency to start at 1 instead of garbage values
    @param Frequency[] the array of digits for the frequency of the player
    @param i Counter
*/
void 
IntialFreq(int Frequency[])
{
    int i;
    for (i = 0;i < 6;i++)
    {
        Frequency[i] = 0;
    }
}
/*
    IntialNew Intialized the a new player
    @param *MasterList The list of player about to be change
    @param nAttempt The amount of attempts the player did during the main game
    @param time total time spent of solving the game
    @param Name the name of player inputted by the player
*/
void 
IntialNew (struct PlayerInfo *MasterList, 
            int nAttempt, 
            int time, 
            char* Name)
{    
    strcpy(MasterList->Name,Name);
    MasterList->Streak = 0;
    MasterList->BStreak = 0;
    IntialFreq(MasterList->Frequency);
    MasterList->time = time;
}
/*
    WinIncrease Increase stats when the player win
    @param *MasterList The list of player's stat about to be change
    @param time total time spent of solving the game
    @param nAttempt The amount of attempts the player did during the main game
*/
void 
WinIncrease (struct PlayerInfo *MasterList, 
            int time, 
            int nAttempt)
{
    MasterList->Streak++;
    MasterList->Frequency[nAttempt-1]++;
    if (MasterList->Streak > MasterList->BStreak)
    {
        MasterList->BStreak = MasterList->Streak;
    }
    if (MasterList->time > time)
    {
        MasterList->time = time;
    }
}
/*
    PrintPlayer Print a player statistics on the terminal
    @param *MasterList The list of player's stat about to be read
    @param j The player number
    @param i Counter
*/
void
PrintPlayer(struct PlayerInfo *MasterList, 
            int j)
{
    int i;
    printf("Name: %s\n",MasterList[j].Name);
    printf("Streak: %d\n",MasterList[j].Streak);
    printf("Best Streak: %d\n",MasterList[j].BStreak);
    printf("Best Time: %d\n",MasterList[j].time);
    printf("Frequency:\n");
    for (i = 0; i < 6; i++)
    {
        printf("%d win/s Attempts: %d\n",i+1,MasterList[j].Frequency[i]);
    } 
}
/*
    TotalFrequency Count the Frequency of the player
    @param *MasterList The list of player's stat about to be read
    @param Profile The amount of player in the game
    @param i,j Counter
    @param Total[] The total of each frequency of the masterlist
*/
void
TotalFreq(struct PlayerInfo *MasterList,
            int Profile)
{
    int i,j;
    int Total[6] = {0,0,0,0,0,0};
    for (i = 0;i < Profile; i++)
    {
        //Check if the player is real or not
        if (strcmp(MasterList[i].Name,"\0") != 0) 
        {
            //Move the profile within the loop
            for (j = 0;j < 6;j++)
            {
                //Add all of the values in the same frequency
                Total[j] += MasterList[i].Frequency[j];
            }
        }
    }
    for (i = 0; i < 6;i++)
    {
        printf("Total %d win/s attempts: %d\n",i+1,Total[i] );
    }
}
/*
    IntialMasterlist Intalized the empty playerlist to detect null name
    @param *MasterList The list of player's stat about to be change
    @param Profile The amount of player in the game
    @param i Counter
*/
void
IntialMasterlist(struct PlayerInfo *MasterList, 
                int Profile)
{
    int i,j;
    for (i = Profile; i < 20; i++)
    {
        strcpy(MasterList[i].Name,"\0");
    }
}
/*
    Storting Change the value between Player 1 and Player 2
    @param *Player1, *Player2 the number of player being swap 
    @param temp temporary storage of playerno
*/
void
Sorting(int *Player1,int *Player2)
{
    int temp;
    temp = *Player1;
    *Player1 = *Player2;
    *Player2 = temp;
}
    /*
    PrintBStreak Print the top 3 best streak in the game
    @param *MasterList The list of player's stat about to be change
    @param Profile The amount of player in the game
    @param PlayerNo The player number in the Masterlist array
    @param i,j Counter
*/
void
PrintBStreak(struct PlayerInfo *MasterList, 
            int Profile)
{
    int i,j;
    int PlayerNo[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    //
    for (i = 0; i < Profile - 1;i++)
    {
        //Prevent the last number to be scanned again
        for (j = 0; j < Profile - i - 1;j++) 
        {
            //Check if the content of masterlist is less than the next one
            if (MasterList[PlayerNo[j]].BStreak < MasterList[PlayerNo[j+1]].BStreak)
            {
                //Swap the PlayerNo
                Sorting(&PlayerNo[j],&PlayerNo[j+1]);
            }
        }
    }
    for (i = 0; i < 3; i++)
    {
        if (strcmp(MasterList[PlayerNo[i]].Name,"\0") != 0)
        {
            printf("Top %d Winstreak:%d\n",i+1, MasterList[PlayerNo[i]].BStreak);
        }
        else 
        {
            printf("Top %d Winstreak:%d\n",i+1,0);
        }
    }
}
/*
    BStreakName Print the top 5 best streak players in the game
    @param MasterList the list of Bstreak that will be tested against
    @param Profile the amount of profile in the game register
    @param i,j Counter for loop
    @param PlayerNo the total amount of player the game can hold
*/
void
BStreakName(struct PlayerInfo *MasterList, 
            int Profile)
{
    int i,j;
    int PlayerNo[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    for (i = 0; i < Profile - 1;i++)
    {
        //Prevent the last number to be scanned again
        for (j = 0; j < Profile - i -1;j++)
        {
            //Check if the content of masterlist is less than the next one
            if (MasterList[PlayerNo[j]].BStreak < MasterList[PlayerNo[j+1]].BStreak)
            {
                //Swap the PlayerNo
                Sorting(&PlayerNo[j],&PlayerNo[j+1]);
            }
        }
    }
    for (i = 0; i < 5; i++)
    {
        if (strcmp(MasterList[PlayerNo[i]].Name,"\0") != 0)
        {
            printf("Top Streak No.%d: %s\nBest Streak: %d\n",i+1,MasterList[PlayerNo[i]].Name,MasterList[PlayerNo[i]].BStreak);
        }
        else
        {
            printf("Top Streak No.%d: %s\nBest Streak: %d\n",i+1,"NA",0);
        }
    }
}
/*
    Besttime Print the top 5 best time players in the game
    @param MasterList the list of Masterlist's time that will be tested against
    @param Profile the amount of profile in the game register
    @param i,j Counter
    @param PlayerNo the total amount of player the game can hold
*/
void
BestTime(struct PlayerInfo *MasterList, 
        int Profile)
{
    int i,j;
    int PlayerNo[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    for (i = 0; i < Profile - 1;i++)
    {
        //Prevent the last number to be scanned again
        for (j = 0; j < Profile - i - 1;j++)
        {
            //Check if the content of masterlist is greater than the next one
            if (MasterList[PlayerNo[j]].time > MasterList[PlayerNo[j+1]].time)
            {
                //Swap the PlayerNo
                Sorting(&PlayerNo[j],&PlayerNo[j+1]);
            }
        }
    }
    printf("\n");   
    for (i = 0; i < 5; i++)
    {
        if (strcmp(MasterList[PlayerNo[i]].Name,"\0") != 0)
        {
            printf("Top Player No.%d: %s\nBest time: %d seconds\n",i+1,MasterList[PlayerNo[i]].Name,MasterList[PlayerNo[i]].time);
        }   
        else
        {
            printf("Top Player No.%d: %s\nBest time: %d seconds\n",i+1,"NA",0);
        }
    }
}
/*
    BestAttemps Print the top 5 best N-Attempts players in the game
    @param MasterList the list of Bstreak that will be tested against
    @param Profile the amount of profile in the game register
    @param i,j Counter for loop
    @param nAttempts to check which N the user wants to see
    @param PlayerNo the total amount of player the game can hold
*/
void
BestAttempt(struct PlayerInfo *MasterList,
            int Profile)
{
    int i,j;
    int nAttempts = 0;
    int PlayerNo[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
    printf("How many turns/attempts:");
    scanf("%d",&nAttempts);
    for (i = 0; i < Profile - 1;i++)
    {
        //Prevent the last one being scan again
        for (j = 0; j < Profile - i - 1;j++) 
        {
            //Check if the content of masterlist is less than the next one
            if (MasterList[PlayerNo[j]].Frequency[nAttempts-1] < MasterList[PlayerNo[j+1]].Frequency[nAttempts-1])
            {
                //Swap the PlayerNo
                Sorting(&PlayerNo[j],&PlayerNo[j+1]);
            }
        }
    }
    for (i = 0;i < 5; i++)
    {
        if (strcmp(MasterList[PlayerNo[i]].Name,"\0") != 0)
        {
            printf("Top %d-Turn Win No.%d: %s\nScore: %d\n",nAttempts,i+1,MasterList[PlayerNo[i]].Name,
                                                        MasterList[PlayerNo[i]].Frequency[nAttempts-1]);
        }
        else
        {
            printf("Top %d-Turn Win No.%d: %s\nScore: %d\n",nAttempts,i+1,"NA",0);
        }
    }
}
/* 
    ViewStats Open the statistics Board of the Player
    @param MasterList the player's List of the entire game
    @param Profile The player amount
    @param nSubDec the decision chosen in Statistics Menu
    @param nRankDec the decision in the SubStatMenu
    @param Name the name of the user Input
*/
void
ViewStats(struct PlayerInfo *MasterList, 
        int Profile)
{
    int nSubDec = 1;
    int nRankDec = 0;
    char Name[4];
    nSubDec = 10;
    while (nSubDec != 0)
    {
        system("cls");
        nSubDec = SubMenu();
        //Check if the input is valid and receive feedback when it out of bound
        if (nSubDec > 3 || nSubDec < 0)
        {
            red();
            printf("Invalid Input");
            reset();
            Stop();
        }
        switch (nSubDec)
        {
            case 1:
            printf("Enter your 3 letter name:");
            scanf("%s",Name);
            strcpy(Name,CheckName(Name));
            //Profile does exists
            if (CheckProfile(MasterList,Name) != -1)
            {
                PrintPlayer(MasterList,CheckProfile(MasterList,Name));
                Stop();
            }
            else
            {
                red();
                printf("\nThe player you requested does not exists");
                reset();
                Stop();
            }
            break;
            case 2:
            {
                TotalFreq(MasterList,Profile);
                PrintBStreak(MasterList,Profile);
                Stop();
            } 
            break;
            case 3: 
            {
                nRankDec = SubStatMenu();
                switch(nRankDec)
                {
                    case 1: 
                    {
                        BStreakName(MasterList,Profile);
                        Stop();
                        break;
                    }
                    case 2:
                    {
                        BestAttempt(MasterList,Profile);
                        Stop();
                        break;
                    }
                    case 3:
                    {
                        BestTime(MasterList,Profile);
                        Stop();
                        break;
                    }
                }
            }
            break;
        }
    }  
}
int
main(int argc, char *argv[])
{
    int nDecision = 0;
    int ExitDec = 0;
    int nAttempt;
    int i;
    int Player;
    int PlayerTime[2];
    int words;
    int Profile = 0;
    int rVal;
    PlayerList MasterList[20];
    char DictName[20];
    char Dict[6000][6];
    char Name[4];
    char Rword[6];
    char *Result, *PickW;
    clock_t start_t, end_t, total_t;
    FILE *fp;
    i = 0;
    srand(time(0));
    // If the command line is greater than 1 it will get the special dictionary file
    if (argc > 1) 
    {
        strcpy(DictName,argv[1]);
        fp = fopen(DictName,"r");
        //If file doesn't exist resort to using the normal dict.txt
        if (fp == NULL)
        {
            printf("Invalid file");
            fclose(fp);
            fp = fopen("dict.txt","r");
            Stop();
        }
        else
        {
            //Feedback for custom dictionary
            cyan();
            printf("Custom Dictionary Open\n");
            reset();
            Stop();
        }
    }
    else
    {
        fp = fopen("dict.txt","r");
    }
    //Check if the file exists
    if (fp == NULL) 
    {
        red();
        printf("No dictionary file can not be read");
        reset();
        return 1;
    }
    while (fscanf(fp,"%s",Dict[i]) != EOF)
    {
        i++;
    }
    //Check if the dict if over 6000 words
    if (i > 6000) 
    {
        words = 6000;
    }
    else
    {
        words = i;
    }
    fclose(fp);
    fp = fopen("Score.txt","r");
    //Read the player score on "Score.txt" if exist 
    if (fp)
    {
        i = 0;
        while (fscanf(fp, "%s %d %d %d %d %d %d %d %d %d ", MasterList[i].Name, 
                                                            &MasterList[i].Streak,
                                                            &MasterList[i].BStreak,
                                                            &MasterList[i].time,
                                                            &MasterList[i].Frequency[0],
                                                            &MasterList[i].Frequency[1],
                                                            &MasterList[i].Frequency[2],
                                                            &MasterList[i].Frequency[3],
                                                            &MasterList[i].Frequency[4],
                                                            &MasterList[i].Frequency[5]) != EOF)
        {
            i++;
        }
        //Count the players
        Profile = i; 
        fclose(fp);
    }
     //Close when it doesn't exist
    else if (fp == NULL)
    {
        fclose(fp);
    }
    //Set a max amount of profile if its scan over 20
    if (Profile > 20)
    {
        Profile = 20;
    }
    IntialMasterlist(MasterList,Profile);
    while (nDecision != 7)
    {
        system("cls");
        //Getting the RNG value for the game
        rVal = rand() % words; 
        nDecision = MainMenu();
        switch(nDecision)
        {
            case 1:
            {
                system("cls");
                strcpy(Rword ,Dict[rVal]);
                Capitalized(Rword);
                start_t = clock();
                nAttempt = MainGame(Rword, 6,Dict,words);
                end_t = clock();
                total_t = (end_t - start_t)/CLOCKS_PER_SEC;
                printf("Total time: %d seconds\n",total_t);
                //Enter the plater name to be stored in it
                printf("Enter your 3 letter name:");
                scanf("%s",Name);
                strcpy(Name,CheckName(Name));
                //Check if there is space and if profile exists
                if ((CheckProfile(MasterList,Name) == -1) && (CheckSpace(MasterList) != -1)) 
                {
                    //Replace empty space with new name
                    IntialNew(&MasterList[CheckSpace(MasterList)],nAttempt,total_t,Name); 
                    //Add 1 to the register players
                    Profile++; 
                }
                //Check if the player won or not
                if (nAttempt != -1)
                {
                    //Record win
                    WinIncrease(&MasterList[CheckProfile(MasterList,Name)],total_t,nAttempt); 
                }
                else
                {
                    //reset streak to be 0
                    MasterList[CheckProfile(MasterList,Name)].Streak = 0; 
                }
                printf("Do you want to exit\n");
                printf("1) Yes   2) No\n");
                do
                {    
                    //Exit if the player wants
                    printf("Select:");
                    scanf("%d",&ExitDec);
                    if (ExitDec == 1)
                    {
                        nDecision = 7;
                    }
                    else if (ExitDec == 2)
                    {
                        Stop();
                    }
                }while (ExitDec > 2 && ExitDec < 1);
            }
            break;
            case 2: 
            {
                strcpy(Rword,EnterManual(Dict,words));
                system("cls");
                Capitalized(Rword);
                start_t = clock();
                MainGame(Rword, 6,Dict,words);
                end_t = clock();
                total_t = (end_t - start_t)/CLOCKS_PER_SEC;
                printf("Total time: %d seconds\n",total_t);
                printf("Do you want to exit\n");
                printf("1) Yes   2) No\n");
                do
                {    
                    //Exit if the player wants
                    printf("Select:");
                    scanf("%d",&ExitDec);
                    if (ExitDec == 1)
                    {
                        nDecision = 7;
                    }
                    else if (ExitDec == 2)
                    {
                        Stop();
                    }
                }while (ExitDec > 2 && ExitDec < 1);
            }
            break;
            case 3: 
            {
                system("cls");
                Player = 0;
                while (Player < 2)
                {
                    printf("Player %d:\n",Player+1);
                    strcpy(Rword,EnterManual(Dict,words));
                    system("cls");
                    Capitalized(Rword);
                    // If player 1 is done, player 2 can see player 1 time
                    if (Player == 1) 
                    {
                        printf("Time to defeat: %d\n",PlayerTime[0]);
                    }
                    start_t = clock();
                    MainGame(Rword, 6,Dict,words);
                    end_t = clock();
                    total_t = (end_t - start_t)/CLOCKS_PER_SEC;
                    PlayerTime[Player] = total_t;
                    printf("Total time: %d seconds\n",PlayerTime[Player]);
                    Player++;
                }
                if (PlayerTime[0] > PlayerTime[1])
                {
                    green();
                    printf("\nPlayer 1 Wins\n");
                    reset();
                }
                else if (PlayerTime[0] < PlayerTime[1])
                {
                    green();
                    printf("\nPlayer 2 Wins\n");
                    reset();
                }
                else 
                {
                    printf("\nDraw!");
                }
                printf("Do you want to exit\n");
                printf("1) Yes   2) No\n");
                do
                {    
                    //Exit if the player wants
                    printf("Select:");
                    scanf("%d",&ExitDec);
                    if (ExitDec == 1)
                    {
                        nDecision = 7;
                    }
                    else if (ExitDec == 2)
                    {
                        Stop();
                    }
                }while (ExitDec > 2 && ExitDec < 1);
            }
            break;
            case 4: 
            {
                system("cls");
                strcpy(Rword ,Dict[rVal]);
                Capitalized(Rword);
                MainGame(Rword, -1,Dict,words);
                printf("Do you want to exit\n");
                printf("1) Yes   2) No\n");
                do
                {    
                    //Exit if the player wants
                    printf("Select:");
                    scanf("%d",&ExitDec);
                    if (ExitDec == 1)
                    {
                        nDecision = 7;
                    }
                    else if (ExitDec == 2)
                    {
                        Stop();
                    }
                }while (ExitDec > 2 && ExitDec < 1);
            }
            break;
            case 5: 
            {
                ViewStats(MasterList,Profile);
            }
            break;
            case 6: 
            {
                printf("Rules:\n");
                printf("This is just like the classic WORDLE, but text based instead\n");
                printf("Words must be a real word means not LKAGC or AAAAA unless manually inputted\n");
                printf("You only have 6 attempts on Classic and Head-to-Head\n");
                printf("Zen mode is the same but with no max attempts\n");
                printf("+ refers to word in the same letter in different position and x");
                printf("means no match words\n");
                Stop();
            }
            break;
            case 8:
            printf("Enter the 3 letter name that will be deleted:");
            scanf("%s",Name);
            strcpy(Name,CheckName(Name));
            if (CheckProfile(MasterList,Name) == -1)
            {
                red();
                printf("Player doesn't exists");
                reset();
                Stop();
            }
            else
            {
                MasterList[CheckProfile(MasterList,Name)].BStreak = -1;
                MasterList[CheckProfile(MasterList,Name)].time = 90000000;
                for (i = 0; i < 6; i++)
                {
                    MasterList[CheckProfile(MasterList,Name)].Frequency[i] = -1;
                }
                strcpy(MasterList[CheckProfile(MasterList,Name)].Name,"\0");
                printf("Player %s Deleted",Name);
                Stop();
            }
            break;
            case 9:
            //Only work if under 6000
            if (words < 6000) 
            {
                printf("Enter your word:");
                scanf("%s",Rword);
                //Check if the letter doesn't contains any special character or different length
                if (CheckLetter(Rword) && CheckLength(Rword)) 
                {
                    strcpy(Dict[words],Rword);
                    words++;
                    printf("New word entered\n");
                    Stop();
                }
                else
                {
                    red();
                    printf("Word has special character or more or less than 5");
                    reset();
                    Stop();
                }
            }
            else
            {
                printf("Dictionary is full");
            }
        }
    }
    fclose(fp);
    //Saving it in the file
    fp = fopen("Score.txt","w"); 
    i = 0;
    while (i < Profile)
    {
        //Check if the profile exists
        if (strcmp(MasterList[i].Name,"\0") != 0)
        {        
            fprintf(fp, "%s %d %d %d %d %d %d %d %d %d\n",  MasterList[i].Name, 
                                                            MasterList[i].Streak,
                                                            MasterList[i].BStreak,
                                                            MasterList[i].time,
                                                            MasterList[i].Frequency[0],
                                                            MasterList[i].Frequency[1],
                                                            MasterList[i].Frequency[2],
                                                            MasterList[i].Frequency[3],
                                                            MasterList[i].Frequency[4],
                                                            MasterList[i].Frequency[5]);
        }
        i++;
    }
    fclose(fp);
    free(Result);
    free(PickW);
    return 0;
}