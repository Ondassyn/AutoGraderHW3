#include<stdio.h>
#include<string.h>

void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines)  {

		FILE *file;
		file = fopen(filename, "w");

		if (file == NULL)
		{
			printf("There is no file to count lines");
			break;
		}
		checkSubstringPalindrome(subStr[], iStringData[][], oStringData[][], lines);
		fput(file, subStr[1]);
		fput(file, "\n");
		fput(file, oStringData[1][50]);
		fput(file, subStr[1]);
		fput(file, "\n");
		fput(file, oStringData[2][50]);

		fclose(file);


}

int isPalindrome(char str[])  {

	char str2[];

	  strcpy(str2, str);  // Copies the contents of str to str2
	  strrev(str2);  // Reversing the string str2

	  if (strcmp(str, str2) == 0)
	  {
		  return 1; // True = palindrome
	  }
	  else
	  {
		  return 0; // False = not palindrome
	  }
}

char *getPalindrome(char str[])  {

	char true[] = "Is_Palindrome";
	char false[] = "Not_Palindrome";

	if (isPalindrome(str) == 1)
	{
		return true; //getPalindrome() = true;
	}

	if (isPalindrome(str) == 0)
	{
		return false; //getPalindrome() = false;
	}
}

int howManySubstrings(char subStr[], char str[])  {


	int subcount = 0;
    int length = strlen(subStr);
    int occurence = 0;

    while (str != '\0') {
            if (strncmp(str++, subStr, length))
            	{
            	continue;
            	}
            if (!occurence)
            	{
            	str += length - 1;
            	}
            	subcount++;
    }
    return subcount;

}

void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines)  {

	int subStr1[] =
	{
	 howManySubstrings("sta", "Astana"),
	 howManySubstrings("sta", "Astana Astana"),
	 howManySubstrings("sta", "Astana Astana Astana"),
	 howManySubstrings("sta", "owlwo"),
	 howManySubstrings("sta", "111111"),
	 howManySubstrings("sta", "222 222"),
	 howManySubstrings("sta", "Almaty"),
	 howManySubstrings("sta", "Kazakhstan"),
	 howManySubstrings("sta", "anaana"),
	 howManySubstrings("sta", "AstanaanatsA"),
	 howManySubstrings("sta", "anana")
	};

	int subStr2[] =
	 {
	 howManySubstrings("ana", "Astana"),
	 howManySubstrings("ana", "Astana Astana"),
	 howManySubstrings("ana", "Astana Astana Astana"),
	 howManySubstrings("ana", "owlwo"),
	 howManySubstrings("ana", "111111"),
	 howManySubstrings("ana", "222 222"),
	 howManySubstrings("ana", "Almaty"),
	 howManySubstrings("ana", "Kazakhstan"),
	 howManySubstrings("ana", "anaana"),
	 howManySubstrings("ana", "AstanaanatsA"),
	 howManySubstrings("ana", "anana"),
	 };


	 char Palindrome[] =
	 {
	 getPalindrome("Astana"),
 	 getPalindrome("Astana Astana"),
 	 getPalindrome("Astana Astana Astana"),
 	 getPalindrome("owlwo"),
 	 getPalindrome("111111"),
 	 getPalindrome("222 222"),
 	 getPalindrome("Almaty"),
 	 getPalindrome("Kazakhstan"),
 	 getPalindrome("anaana"),
	 getPalindrome("AstanaanatsA"),
	 getPalindrome("anana")
	 };

	 subStr[2] = "sta, ana";

		 for(int j = 0; j < nrIOfileLines; j++){
			 oStringData[1][50] = {iStringData[][j] + "\t" + subStr1[j] + "\t" + Palindrome[j] + "\n"};
		 }
		 for(int i = 0; i < nrIOfileLines; i++){
		 	 oStringData[2][50] = {iStringData[][i] + "\t" + subStr2[i] + "\t" + Palindrome[i] + "\n"};
		 }
}
void readFile(char filename[], char twoDimArr[][50])  {

	int i = 0;
	int j = 0;
	char c;
	FILE *file;
	file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("There is no file to count lines");
		break;
	}
	for(; i < 50; i++) {
		for(; j < 50; j++)
		{
			c = fgetc(twoDimArr,i,j , file);
		}
	}
	fclose(file);
}

int countFileLines(char filename[])  {

	int lines = 0;
	char ch;

	FILE *file;
	file = fopen(filename, "r");

	if (file == NULL)
	{
		printf("There is no file to count lines");
		break;
	}
	while (((ch = fgetc(file)) != '\0'))
	{
		if (ch == '\n')
		{
			lines++;
		}
	}
	fclose(file);
	return lines;
}

int main() {

	char inStrings[] = "iStrings.txt";
	char subStrings[] = "subStrings.txt";
	char subStr[] = "sta, ana";

	char iStringData[][];
	char oStringData[][];
	countFileLines(inStrings);
	countFileLines(subStrings);
	isPalindrome(inStrings);
	getPalindrome(inStrings);
	howManySubstrings(subStr, inStrings)
	readFile("iStrings.txt", iStringData[][]);
	writeFile("Strings.txt", subStr, oStringData,  lines);


	return 0;
}
