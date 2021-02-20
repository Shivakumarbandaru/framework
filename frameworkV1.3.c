#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_FILE_NAME "data.dat"
#define FIELD_FILE_NAME "fields.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define MENU_LINE_LENGTH 20
#define FIELD_LINE_LENGTH 20
#define LINE_LENGTH 20

void showMenu();
void create();
void read();
void exitProgram();
int getLineCount();
char** storeLinesIntoArray();

void main()
{
	int countOfFields = getLineCount(FIELD_FILE_NAME);
	int countOfMenuLines = getLineCount(MENU_FILE_NAME);
	char **arrayOfFieldLines = storeLinesIntoArray(FIELD_FILE_NAME);
	char **arrayOfMenuLines = storeLinesIntoArray(MENU_FILE_NAME);
	showMenu();
}

int getLineCount(char* FILE_NAME)
{
	int lineCounter = 0;
	FILE *fpText; 
	char line[LINE_LENGTH];
	fpText = fopen(FILE_NAME, "r");
	if(fpText == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(line, sizeof(line), fpText) > 0)
		{
			lineCounter = lineCounter + 1;
		}
	}
	fclose(fpText);
	return lineCounter;
}

char** storeLinesIntoArray(char* FILE_NAME)
{
	char **list;
	int lineCounter = 0;
	FILE *fpText; 
	char line[LINE_LENGTH];
	int countOfLines = getLineCount(FILE_NAME);
	fpText = fopen(FILE_NAME, "r");
	if(fpText == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		list = (char**)malloc(countOfLines * sizeof(char*));
		while(fgets(line, sizeof(line), fpText) > 0)
		{
			line[strlen(line) - 1] = '\0';
			list[lineCounter] = (char*)malloc(LINE_LENGTH);
			strcpy(list[lineCounter], line);
			lineCounter++;
		}
	}
	fclose(fpText);
	return list;
}

void showMenu()
{
	int option;
	while(1)
	{
		int countOfMenuLines = getLineCount(MENU_FILE_NAME);
		char **arrayOfMenuLines = storeLinesIntoArray(MENU_FILE_NAME);
		for(int counter = 0; counter < countOfMenuLines; counter++)
		{
			printf("%s\n", arrayOfMenuLines[counter]);
		}
		printf("\nEnter your option: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				create();
				break;
			case 2:
				read();
				break;
			case 3:
				exitProgram();
				break;
			default:
				printf("Error! Please select a correct option.\n");
				break;
		}
	}
}

void create()
{  
	FILE *fpData;
	fpData = fopen(DATA_FILE_NAME, "a");
	char fieldValue[FIELD_LINE_LENGTH];
	int countOfFields = getLineCount(FIELD_FILE_NAME);
	char **arrayOfFieldLines = storeLinesIntoArray(FIELD_FILE_NAME);
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		for(int counter = 0; counter < countOfFields; counter++)
		{
			fflush(stdin);
			printf("Enter %s: ", arrayOfFieldLines[counter]);
			gets(fieldValue);
			fwrite(fieldValue, FIELD_LINE_LENGTH, 1, fpData);
		}
	}
	fclose(fpData);
}

void read()
{
	FILE *fpData;
	fpData = fopen(DATA_FILE_NAME, "r");
	char fieldValue[FIELD_LINE_LENGTH];
	int countOfFields = getLineCount(FIELD_FILE_NAME);
	char **arrayOfFieldLines = storeLinesIntoArray(FIELD_FILE_NAME);
	for(int counter = 0; counter < countOfFields; counter++)
	{
		printf("%s\t", arrayOfFieldLines[counter]);
	}
	printf("\n");
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{	
		int counter = 0;
		while(fread(fieldValue, FIELD_LINE_LENGTH, 1, fpData) > 0)
		{
			printf("%s\t", fieldValue);
			counter = counter + 1;
			if(counter == countOfFields)
			{
				printf("\n");
				counter = 0;
			}
		}
	}
	fclose(fpData);
}

void exitProgram()
{
	printf("Thank you.");
	exit(0);
}
