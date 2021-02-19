#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_FILE_NAME "data1.dat"
#define FIELD_FILE_NAME "fields.cfg"
#define MENU_FILE_NAME "menu.cfg"
#define LINE_LENGTH 20

void showMenu();
void create();
void read();
void exitProgram();

int getFieldCount();
char** storeFieldList();
char** storeMenuList();
int countOfMenu;

void main()
{
	int countOfField = getFieldCount();
	char **fieldItem = storeFieldList(countOfField);
	char **menuItem = storeMenuList();
	showMenu(menuItem, fieldItem, countOfField);
}

int getFieldCount()
{
	int fieldCounter = 0;
	FILE *fpField; 
	char fieldName[LINE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(fieldName, sizeof(fieldName), fpField) > 0)
		{
			fieldCounter = fieldCounter + 1;
		}
	}
	fclose(fpField);
	return fieldCounter;
}

char** storeFieldList(int countOfField)
{
	char **fieldList;
	int counter = 0;
	FILE *fpField; 
	char fieldLine[LINE_LENGTH];
	fpField = fopen(FIELD_FILE_NAME, "r");
	if(fpField == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		fieldList = (char**)malloc(countOfField * LINE_LENGTH);
		fseek(fpField, 0, SEEK_SET);
		while(fgets(fieldLine, sizeof(fieldLine), fpField) > 0)
		{
			fieldLine[strlen(fieldLine) - 1] = '\0';
			fieldList[counter] = (char*)malloc(LINE_LENGTH);
			strcpy(fieldList[counter], fieldLine);
			counter++;
		}
	}
	fclose(fpField);
	return fieldList;
}

char** storeMenuList()
{
	char **menuList;
	countOfMenu = 0;
	int counter = 0;
	FILE *fpMenu; 
	char menuLine[LINE_LENGTH];
	fpMenu = fopen(MENU_FILE_NAME, "r");
	if(fpMenu == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		while(fgets(menuLine, sizeof(menuLine), fpMenu) > 0)
		{
			countOfMenu = countOfMenu + 1;
		}
		menuList = (char**)malloc(countOfMenu * LINE_LENGTH);
		fseek(fpMenu, 0, SEEK_SET);
		while(fgets(menuLine, sizeof(menuLine), fpMenu) > 0)
		{
			menuList[counter] = (char*)malloc(LINE_LENGTH);
			strcpy(menuList[counter], menuLine);
			counter++;
		}
	}
	fclose(fpMenu);
	return menuList;
}

void showMenu(char **menuItem, char **fieldItem, int countOfField)
{
	int option;
	while(1)
	{
		for(int counter = 0; counter < countOfMenu; counter++)
		{
			printf("%s", menuItem[counter]);
		}
		printf("\nEnter your option: ");
		scanf("%d", &option);
		switch(option)
		{
			case 1:
				create(countOfField, fieldItem);
				break;
			case 2:
				read(countOfField, fieldItem);
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

void create(int countOfField, char **fieldItem)
{  
	FILE *fpData;
	fpData = fopen(DATA_FILE_NAME, "a");
	char fieldName[LINE_LENGTH];
	char fieldValue[LINE_LENGTH];
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{
		for(int counter = 0; counter < countOfField; counter++)
		{
			fflush(stdin);
			printf("Enter %s: ", fieldItem[counter]);
			gets(fieldValue);
			fwrite(fieldValue, LINE_LENGTH, 1, fpData);
		}
	}
	fclose(fpData);
}

void read(int countOfField, char **fieldItem)
{
	FILE *fpData;
	fpData = fopen(DATA_FILE_NAME, "r");
	char fieldValue[LINE_LENGTH];
	int counter;
	for(counter = 0; counter < countOfField; counter++)
	{
		printf("%s\t", fieldItem[counter]);
	}
	printf("\n");
	if(fpData == NULL)
	{
		printf("Error!");
		exit(0);
	}
	else
	{	
		counter = 0;
		while(fread(fieldValue, LINE_LENGTH, 1, fpData) > 0)
		{
			printf("%s\t", fieldValue);
			counter = counter + 1;
			if(counter == countOfField)
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
