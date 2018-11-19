/*
 * hw3.c
 *
 *  Created on: Nov 8, 2018
 *      Author: abok
 */


#include <stdio.h>
#include <string.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines);

int isPalindrome(char str[]);

char *getPalindrome(char str[]);

int howManySubstrings(char subStr[], char str[]);

void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines);

void readFile(char filename[], char twoDimArr[][50]);

int countFileLines(char filename[]);


int main()
{
	int numOfLines1, numOfLines2, numOfLines;
	int i = 0, j = 0;

	numOfLines1 = countFileLines("subString.txt");
	numOfLines2 = countFileLines("iStrings.txt");
	numOfLines = numOfLines2 + 1;

	char ssData[numOfLines1][50], iStringData[numOfLines2][50], oStringData[50][50];

	readFile("subString.txt", ssData);
	readFile("iStrings.txt", iStringData);

	//numOfOccur = howManySubstrings(ssData[0], iStringData[0]);
	//getPalindrome(iStringData[0]);
//	while (i < numOfLines || j < numOfLines1){

		checkSubstringPalindrome(ssData[j], iStringData[i], oStringData[50], numOfLines);
		writeFile("oString.txt", ssData[j], oStringData[50], numOfLines);
//	}
	return 0;
}


void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines)
{
	FILE *file;
	int i;

	file = fopen(fileName, "w");
	if (file == NULL)
	{
		printf("Problem opening the file.");
	}

	fprintf(file, "%s\n", ssData);
	for (i = 0; i < nrIOfileLines; i++)
	{
		fprintf(file, "%s", oStringData[i]);
	}

	fclose(file);
}


int isPalindrome(char str[])
{
	int len = strlen(str);
	char revStore[len];
	int i, j = 0, k = 0;
	_Bool isPal;

	for (i = len - 1; i > -1; i--)
	{
		revStore[j] = str[i];
		j++;
	}
	revStore[len] = '\0';

	while (k < len)
	{
		if (revStore[k] != str[k])
		{
			isPal = 0;
			break;
		}
		if (revStore[k] == str[k] && k == (len - 1))
		{
			isPal = 1;
			break;
		}
		k++;
	}
	return isPal;
}


char *getPalindrome(char str[])
{
	if (isPalindrome(str))
	{
		return "Is_Palindrome";
	}
	else
	{
		return "Not_Palindrome";
	}
}


int howManySubstrings(char subStr[], char str[])
{
	int i, j = 0, numOfOccur = 0;
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] != subStr[j])
		{
			return 0;
		}
		if (str[i] == subStr[j] && j == 2)
		{
			numOfOccur++;
			return numOfOccur;
		}
		j++;
	}
}


void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines)
{
	int i;
	for(i = 0; i < nrIOfileLines; i++)
	{
		strcpy(oStringData[i],iStringData[i] + "\t" + (char)howManySubstrings(subStr, iStringData[i]) + "\t" + getPalindrome(iStringData[i]) + "\n");
	}
}


void readFile(char filename[], char twoDimArr[][50])
{
	FILE *file;
	int n = 0;
	file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Problem opening the file.");
	}

	while(fgets(twoDimArr[n], 50, file) != NULL)
	{
		n++;
	}
	fclose(file);
}


int countFileLines(char filename[])
{
	FILE *file;
	int count = 0;
	char twoDimArr[50][50];
	file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("Problem opening the file.");
	}

	while(fgets(twoDimArr[count], 50, file) != NULL)
	{
		count++;
	}
	fclose(file);

	return count;
}
