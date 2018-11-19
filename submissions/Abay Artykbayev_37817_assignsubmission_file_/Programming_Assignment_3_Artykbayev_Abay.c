#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50],
		int nrIOfileLines) {
	FILE *file = fopen(fileName, "a"); // Opening the output file for appending. The file is already checked in main() before calling this function
	fprintf(file, "%s\n", ssData); //Printing the substring to the file
	int i;
	for (i = 0; i < nrIOfileLines; i++) { //Printing the contents of 2D output array
		fprintf(file, "%s", oStringData[i]);
	}
	fprintf(file, "\n"); //A blank line between each block (VERY important in automatic grading)
	fclose(file); //Closing the file
}

int isPalindrome(char str[]) {
	int i;
	for (i = 0; i <= (strlen(str) - 1) / 2; i++) // This loops checks if the first and last elements are same
		if (str[i] != str[strlen(str) - 1 - i]) // and, if they are not same, 0 is returned, meaning this string is not a palindrome
			return 0;
	return 1; //1 is returned of the string is a palindrome
}

char *getPalindrome(char str[]) {
	if (isPalindrome(str) == 0) // Calling the isPalindrome function
		return "Not_Palindrome"; // returning "Not_Palindrome" if the result from isPalindrome is 0
	return "Is_Palindrome"; // otherwise, returning "Is_Palindrome"
}

int howManySubstrings(char subStr[], char str[]) {
	int i, j, k, number_of_subStr = 0; // i, j and k are function iterator variables
	_Bool isSubStr;
	for (i = 0; i <= strlen(str) - strlen(subStr); i++) {
		isSubStr = 1;
		for (j = 0, k = i; j < strlen(subStr); j++, k++) { // Checking if the next strlen(subStr) characters of the string are same with the substring
			if (str[k] != subStr[j]) {
				isSubStr = 0;
				break;
			}
		}
		if (isSubStr == 1) { //If the checked substring is actually a substring, then the number_of_subStr variable is incremented
			number_of_subStr++;
			i = k - 1;
		}
	}
	return number_of_subStr; //Returning the number of substrings
}

void checkSubstringPalindrome(char subStr[], char iStringData[][50],
		char oStringData[][50], int nrIOfileLines) {
	int i;
	for (i = 0; i < nrIOfileLines; i++) {
		sprintf(oStringData[i], "%s\t%d\t%s\n", iStringData[i], //Calling the howManySubstrings and getPalindrome functions
				howManySubstrings(subStr, iStringData[i]), // Printing everything into the 2D output array
				getPalindrome(iStringData[i]));
	}
}

void readFile(char filename[], char twoDimArr[][50]) {
	FILE *file = fopen(filename, "r"); //Opening the file for reading
	if (file == NULL) { //Checking the file
		printf("Cannot open the file %s.\n", filename);
		exit(-1); //Terminating the program if the file cannot be opened
	}

	int i;
	for (i = 0; !feof(file); i++) {
		fgets(twoDimArr[i], 50, file); //Reading line by line from the file
		while (twoDimArr[i][strlen(twoDimArr[i]) - 1] == '\n' //removing unnecessary white spaces and newlines from the end of the string
		|| twoDimArr[i][strlen(twoDimArr[i]) - 1] == '\r'
				|| twoDimArr[i][strlen(twoDimArr[i]) - 1] == ' ') {
			twoDimArr[i][strlen(twoDimArr[i]) - 1] = '\0';
		}
	}
	fclose(file); //Closing the file
}

int countFileLines(char filename[]) {
	FILE *file = fopen(filename, "r"); //Opening the file for reading
	if (file == NULL) { //Checking the file
		printf("Cannot open the file %s.\n", filename);
		exit(-1); //Terminating the program if the file cannot be opened
	}
	int number_of_lines = 0;
	while (!feof(file)) { // While not at the end of file,
		if (getc(file) == '\n') { //Incrementing the number_of_lines variable if the newline character is read
			number_of_lines++;
		}
	}
	fclose(file); //Closing the file
	return number_of_lines; //Returning the number_of_lines
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *output = fopen("oStrings.txt", "w"); //Opening the output file for writing, thus clearing it from the contents of previous runs
	if (output == NULL) { //Checking the file
		printf("Cannot open/create the output file.\n");
		exit(-1); //Terminating the program if the file cannot be opened
	}
	fclose(output); //Closing the file as it is no longer needed in the main

	int iString_lines = countFileLines("iStrings.txt"); // Calling the countFileLines function for iStrings.txt and subStrings.txt,
	int subString_lines = countFileLines("subStrings.txt"); // and storing the result in the corresponding variables

	char subStringData[subString_lines][50]; //Declaring 2D array for storing the contents of subStrings.txt
	char iStringData[iString_lines][50]; //Declaring 2D array for storing the contents of iStrings.txt
	char oStringData[iString_lines][50]; //Declaring 2D array for storing the contents of oStrings.txt

	readFile("subStrings.txt", subStringData); //Calling the readFile function for reading the contents of subStrings.txt
	readFile("iStrings.txt", iStringData); //Calling the readFile function for reading the contents of iStrings.txt

	int i;
	for (i = 0; i < subString_lines; i++) { //For each string from the iStrings.txt
		checkSubstringPalindrome(subStringData[i], iStringData, oStringData,
				iString_lines); // Calling the checkSubstringPalindrome function to check the for subStrings and "palindromness"
		writeFile("oStrings.txt", subStringData[i], oStringData, iString_lines); //Writing the subString and the contents of 2D outut array into the oStrings.txt
	}

	return 0;
}
