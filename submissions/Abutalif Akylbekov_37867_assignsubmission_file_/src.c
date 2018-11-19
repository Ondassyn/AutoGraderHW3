#include <stdio.h>
#include <string.h>

//functions forward declaration
void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrlIOLines);
int isPalindrome(char str[]);
char *getPalindrome(char str[]);
int howManySubstrings(char subStr[], char str[]);
void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines);
void readFile(char filename[], char fileContent[][50]);
int countFileLines(char filename[]);

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	int linesInSs = countFileLines("subStrings.txt");
	int linesInIOStr = countFileLines("iStrings.txt");
	char iStringData[linesInIOStr][50];
	char subStr[linesInSs][50];
	char oStringData[linesInIOStr][50];
	readFile("iStrings.txt", iStringData);
	readFile("subStrings.txt", subStr);
	int i;
	//formats the oStringData and writes data to the oStrings.txt for each substring
	for(i = 0; i < linesInSs; i++)
	{
		checkSubstringPalindrome(subStr[i], iStringData, oStringData, linesInIOStr);
		writeFile("oStrings.txt", subStr[i],oStringData, linesInIOStr);
	}
	return 0;
}

//counts lines in a file
int countFileLines(char filename[])
{
	FILE* f = fopen(filename, "r");
	char c;
	int lines = 0;
	//runs through every char in file if sees a new line, increments no of lines
	do
	{
		c = getc(f);
		if(c=='\n')
			lines++;
	}
	while(c!=EOF);
	fclose(f);
	//returns counted lines
	return lines;
}

//reads the file and saves its content in 2d char array
void readFile(char filename[], char fileContent[][50])
{
	FILE *f = fopen(filename, "r");
	char c;
	int i , j;
	i = 0;
	//treats each line as a string and saves it to the array
	do
	{
		j = 0;
		do
		{
			c = fgetc(f);
			if(c!='\n' && c!=EOF && c!='\r')
			{
				fileContent[i][j]=c;
				j++;
			}
		}
		while(c!='\n'&& c!=EOF);
		//adds null character at the end of string
		fileContent[i][j] = '\0';
		++i;
	}
	while(c!=EOF);
	fclose(f);
}

//checks if a string is a palindrome
int isPalindrome(char str[])
{
	int len = strlen(str);
	int i;
	//runs to the middle of a string and sees if evenly distanced chars from both ends are equal
	for(i = 0; i < len/2; i++)
	{
		if(str[i]!=str[len-1-i])
			return 0; // if at least 1 pair is not equal the word is not a palindrome
	}
	return 1;
}

//returns a string depending on the value of isPalindrome
char *getPalindrome(char str[])
{
	if(isPalindrome(str))
		return "Is_Palindrome";
	return "Not_Palindrome";
}

//finds amount of substrings in a string
int howManySubstrings(char subStr[], char str[])
{
	int count = 0, i;
	//goes through each letter except the last of the cheched string
	for(i = 0; i<strlen(str)-2; i++)
	{
		//check if a letter and following three letter of the string are the same as the 3 letters of the substring
		if(subStr[0]==str[i] && subStr[1]==str[i+1] && subStr[2]==str[i+2])
			count++;//increments number of counter if true
	}
	return count;
}

//formats the output string array
void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines)
{
	int i, subscount = 0;
	char *palindrome_res, itos[20];
	//runs through each line of iStringData
	for(i = 0; i < nrIOfileLines; i++)
	{
		//finds amount of substrings in a line
		subscount = howManySubstrings(subStr, iStringData[i]);
		//turns the number of substring in a line to a string
		sprintf(itos, "%d", subscount);
		//gets the result of palindrome test
		palindrome_res = getPalindrome(iStringData[i]);
		//assigns the first letter in each line of oStringData to a null character
		//(needed for the implementation of the "strcat" function from string.h)
		oStringData[i][0]='\0';
		//concatenate a line from inData to line in outData
		strcat(oStringData[i], iStringData[i]);
		//concatenate horizontal tab to a line of outData
		strcat(oStringData[i], "\t");
		//concatenate number of substrings to a line of outData
		strcat(oStringData[i], itos);
		//concatenate another horizontal tab to a line of outData
		strcat(oStringData[i], "\t");
		//concatenates the result of palindrome test to a line of outData
		strcat(oStringData[i], palindrome_res);
	}
}

//writes the content of oStringData to the oStrings.txt
void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrlIOLines)
{
	FILE *f = fopen(fileName, "a");
	int i;
	fprintf(f,"%s\n", ssData);//prints the substring
	for(i = 0; i < nrlIOLines; i++)
	{
		fprintf(f, "%s\n", oStringData[i]);//prints the content of outData
	}
	fprintf(f, "\n");//indentation between each substring block
	fclose(f);
}
