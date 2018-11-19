				//**************//
				//*****khak*****//
				//**************//	
				//*assignment*3*// 
				//**************//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines) {
 	FILE *f;
 	f = fopen(fileName, "a");
 	fprintf(f, "%s\n", ssData);
 	for (int i = 0; i < nrIOfileLines; i++) {
 		fprintf(f, "%s", oStringData[i]);
 	}
 	fprintf(f, "\n");
	fclose(f);
}

int isPalindrome(char str[]) { 
    for(int i = 0; i < strlen(str)/2; i++) {
        if(str [i] != str[strlen(str) - i - 1]) 
            return 0;
    }

    return 1;
}

char *getPalindrome(char str[]) {
    if(isPalindrome(str))
        return "Is_Palindrome";
    else
        return "Not_Palindrome";
}

int howManySubstrings(char subStr[], char str[])
{
    int cnt = 0;
    for(int i = 0; i < strlen(str) + 2; i++) {
         if(str[i] == subStr[0] && str[i + 1] == subStr[1] && str[i + 2] == subStr[2]) { 
            i += 2;
            cnt++;
         }
    }
    return cnt;
}

void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines) {
	for (int i = 0; i < nrIOfileLines; i++) {
		strcpy(oStringData[i], iStringData[i]); // initial
		strcat(oStringData[i], "\t");
		char ozgergen[101];
		snprintf(ozgergen, 10, "%d", howManySubstrings(subStr, iStringData[i]));
		strcat(oStringData[i], ozgergen);
		strcat(oStringData[i], "\t");
		strcat(oStringData[i], getPalindrome(iStringData[i]));
		strcat(oStringData[i], "\n");
	}	
}


void readFile(char fname[], char matrix[][50]) {
	FILE *f;
	int i = 0, j = 0;
	f = fopen(fname, "r");
	while(!feof(f)) {
		char c = getc(f);
		if (c == '\n') {
			i++;
			j = 0;
		} else {
			matrix[i][j++] = c;
		}	
	} 
	fclose(f);
}

int countFileLines(char fname[]) {
	FILE *f;
	int cnt = 0;
	f = fopen(fname, "r");
	while (!feof(f)) {
		char c = getc(f);
		if (c == '\n') cnt++;
	}
	fclose(f);
	return cnt;
}


int main () {

	char matrix1[1001][50], matrix2[1001][50];

	FILE *f;
	f = fopen("oStrings.txt", "w");

	readFile("subStrings.txt", matrix1);
	readFile("iStrings.txt", matrix2);

	int cntf1 = countFileLines("subStrings.txt");
	int cntf2 = countFileLines("iStrings.txt");

	char oStringData[1001][50];

	for (int i = 0; i < cntf1; i++) {
		checkSubstringPalindrome(matrix1[i], matrix2, oStringData, cntf2);
		writeFile("oStrings.txt", matrix1[i], oStringData, cntf2);
	}

	/*printf("%s\n", matrix2[3]);
	printf("%s\n", getPalindrome(matrix2[3]));

	for (int i = 0; i < cntf2; i++) {
		printf("%s\n", matrix2[i]);
		printf("%s\n", getPalindrome(matrix2[i]));
	}*/


	return 0;
}
