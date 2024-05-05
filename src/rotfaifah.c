#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

#include "../include/rotfaifah.h"
#include "../include/textDecoration.h"

void clearScreen(void){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void getCurrentDate(char *dateStr, int size) {
    time_t t;
    struct tm *tm_info;

    time(&t); //get the current time in seconds and store in t
    tm_info = localtime(&t); //convert time to local time

    tm_info->tm_year += 543; //change the year from Christian Era to Buddhist era

    //get day
    strftime(dateStr, size, "%d/%m/%Y", tm_info); //formats the date, month, time in dateStr as the format date/month/year
}

void delLastEnteredLine(){
	printf("%c[1A back", 033);
  	for(int i=0; i<100; i++) printf("\b");
  	for(int i=0; i<100; i++) printf(" ");
  	for(int i=0; i<100; i++) printf("\b");
}

void TextShowUpDelay(char Text[], int _delay){
    int length = strlen(Text);
    for(int i=0; i<length; i++){
        delay(_delay);
        printf("%c", Text[i]);
    }
}

void delay(int milli_seconds){
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void printHeader(int totalLine, int totalStation){
	int MAX_DATE_LENGTH = 12;
	char currentDate[MAX_DATE_LENGTH];
    getCurrentDate(currentDate, sizeof(currentDate));
	char UpperLeft, UpperRight;
	char LowerLeft, LowerRight;
	char Vertical, Horizontal;
    //set to ASCII Character 218, 191, 192, 217, 179, 196 to create the box for header

	printf(ANSI_COLOR_LIGHT_WHITE);
	printf(" %c", BOX_UpperLeft);
	for(int i = 0;i<43;i++){
		printf("%c", BOX_Horizontal);
	}
	printf("%c \n", BOX_UpperRight);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "RotFaiFah Application" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                     %c \n", BOX_Vertical, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c Current Date: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%s" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "                  %c \n", BOX_Vertical, currentDate, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c Total Station: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE " | Total Line: " ANSI_STYLE_BOLD ANSI_COLOR_GOLD "%3d" ANSI_RESET_ALL ANSI_COLOR_LIGHT_WHITE "      %c \n", BOX_Vertical, totalStation, totalLine, BOX_Vertical);
//	printf(" %c                                           %c \n", BOX_Vertical, BOX_Vertical);
	printf(" %c", BOX_LowerLeft);
	for(int i = 0;i<43;i++){
		printf("%c", BOX_Horizontal);
	}
	printf("%c \n", BOX_LowerRight);
	printf(ANSI_RESET_ALL);
}

void printSplitedLine() { printf(ANSI_COLOR_LIGHT_GREEN ANSI_STYLE_STRIKE ANSI_STYLE_BOLD "=================================================\n" ANSI_RESET_ALL); }

void printOption(int opt, char *name) { printf("  %c " ANSI_COLOR_GOLD "[%d]" ANSI_RESET_ALL " %s\n", ARROW_ASCII, opt, name); }

void printEnterChoice(){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD " Enter your choice: " ANSI_RESET_ALL); }

void printMSGLightWhite(char *msg){ printf(ANSI_COLOR_LIGHT_WHITE ANSI_STYLE_BOLD "%s" ANSI_RESET_ALL, msg); }

void printMenu() { printf(ANSI_STYLE_BOLD " Menu:\n" ANSI_RESET_ALL); }

void printError(char *msg) {
	printf(ANSI_COLOR_LIGHT_RED "%s\n" ANSI_RESET_ALL, msg);
}

int count_string(char *main_string, char *sub_string) {
    int count = 0;
    char *ptr = main_string;
    while ((ptr = strstr(ptr, sub_string)) != NULL) {
        count++;
        ptr++; // Move pointer to search for the next occurrence
    }
    return count;
}

void enterAnyKey(){
	while (getchar() != '\n');
    printMSGLightWhite("Enter any key to continue...");
    char ch;
    while(1){
        ch = _getch();
       	break;
	}
}

void parse_csv_line_graph_station(char *line, Station *station) {
    const char *delim = ",";
    char *token = strtok(line, delim);

    int col = 0;
    int cCount = 0, iCount = 0;
    while (token != NULL) {
        switch (col) {
			case 0:
				station->staID = atoi(token);
				break;	
            case 1:
                strcpy(station->name, token);
                break;
            case 2:
                strcpy(station->shortCode, token);
                break;
            case 3:
                strcpy(station->fullCode, token);
                break;
            case 4:
                strcpy(station->connectionWith, token);
                break;
            case 5:
                strcpy(station->connectionWith2, token);
                break;
            case 6:
                station->conCount = atoi(token);
                cCount = atoi(token);
                break;
            case 7:
            case 11:
            case 15:
                station->connections[(col - 7)/4].staID = atoi(token);
                break;
            case 8:
            case 12:
            case 16:
                strcpy(station->connections[(col - 8)/4].sta, token);
                break;
            case 9:
            case 13:
            case 17:
                station->connections[(col - 9)/4].time = atoi(token);
                break;
            case 10:
            case 14:
            case 18:
                strcpy(station->connections[(col - 10)/4].platform, token);
                break;
            case 19:
                station->intCount = atoi(token);
                iCount = atoi(token);
                break;
            case 20:
            case 23:
            case 26:
            	station->interchanges[(col - 20)/3].staID = atoi(token);
                break;
            case 21:
            case 24:
            case 27:
                strcpy(station->interchanges[(col-21)/3].sta, token);
                break;
            case 22:
            case 25:
            case 28:
                station->interchanges[(col-22)/3].time = atoi(token);
                break;
            default:
                break;
        }
        col++;
        token = strtok(NULL, delim);
    }
    int unionTotal = 0;
    for(int i = 0;i < cCount;i++){
    	strcpy(station->connectAll[unionTotal].sta, station->connections[i].sta);
    	strcpy(station->connectAll[unionTotal].platform, station->connections[i].platform);
    	station->connectAll[unionTotal].time = station->connections[i].time;
    	station->connectAll[unionTotal].staID = station->connections[i].staID;
		station->connectAll[unionTotal].type = 1;
    	unionTotal++;
	}
	for(int i = 0; i < iCount;i++){
//		printf("Adding Interchange #%d of: %s %s\n", i, station->name, station->interchanges[i].sta);
		strcpy(station->connectAll[unionTotal].sta, station->interchanges[i].sta);
		station->connectAll[unionTotal].time = station->interchanges[i].time;
		char *platform = "999UKN";
		strcpy(station->connectAll[unionTotal].platform, platform);
		station->connectAll[unionTotal].staID = station->interchanges[i].staID;
		station->connectAll[unionTotal].type = 2;
		unionTotal++;
	}
	station->connectAllCount = unionTotal;
}
