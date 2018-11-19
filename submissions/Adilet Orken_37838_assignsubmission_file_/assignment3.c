#include <stdio.h>
#include <string.h>

void intoa(int sn, char ossn[]) {
	int i, z;
	if ((z = sn) < 0)
		sn = -sn;
	i = 0;
	do {
		ossn[i++] = sn % 10 + '0';
	} while ((sn /= 10) > 0);
	if (z < 0)
		ossn[i++] = '-';
	ossn[i] = '\0';
	strrev(ossn);
}

void writeFile(char fileName[], char ssData[], char oStringData[][50],
		int nrIOfileLines) {
	int i;
	FILE *of = fopen("oStrings.txt", "a");
	fprintf(of,"%s\n", ssData);
	for (i = 0; i < nrIOfileLines; i++) {
		fprintf(of,"%s", oStringData[i]);
	}
	fclose(of);
}
int isPalindrome(char str[]) {
	char rstr[strlen(str)];
	strcpy(rstr, str);
	strrev(rstr);
	if (strcmp(rstr, str) == 0) {
		return 1;
	} else {
		return 0;
	}
}
char *getPalindrome(char str[]) {
	int i = isPalindrome(str);
	if (i == 1) {
		return "Is_Palindrome";
	}

	else {
		return "Not_Palindrome";
	}
}

int howManySubstrings(char subStr[], char str[]) {
	int i, j = 0, count = 0, n = 0;
	int strl, substrl;

	strl = strlen(str);
	substrl = strlen(subStr);
	for (i = 0; i < strl; i++) {
		while (j <= substrl) {
			if (str[j + i] == subStr[j]) {
				count++;
				j++;
				continue;
			} else {
				break;
				j = 0;
				count = 0;
			}
		}
		if (count == substrl) {
			n++;
			i = j + i + 1;
		}
	}
		return n;
}
void checkSubstringPalindrome(char subStr[], char iStringData[][50],
		char oStringData[][50], int nrIOfileLines) {
	int i = 0, sn = 0;
	char p[20], oss[20];
	for (i = 0; i < nrIOfileLines; i++) {
		sn = howManySubstrings(subStr, iStringData[i]);
		strcpy(p, getPalindrome(iStringData[i]));
		intoa(sn, oss);
		strcpy(oStringData[i], iStringData[i]);
		strcat(oStringData[i], "\t");
		strcat(oStringData[i], oss);
		strcat(oStringData[i], "\t");
		strcat(oStringData[i], p);
		strcat(oStringData[i], "\n");
		printf("%s", oStringData[i]);
	}
}

int countFileLines(char filename[]) {
	FILE *fo;
	fo = fopen(filename, "r");
	int l = 0;
	char c = 0;
	while (!feof(fo)) {

		c = fgetc(fo);
		if (c == '\n') {
			l++;
		}
	}
	fclose(fo);
	return l;
}

void readFile(char filename[], char twoDimArr[][50]) {
	int i, p, k = countFileLines(filename);
	FILE *f = fopen(filename, "r");
	for (i = 0; i < k; i++) {
		fgets(twoDimArr[i], 50, f);
		p = strlen(twoDimArr[i]);
		while (twoDimArr[i][p - 1] == '\n' || twoDimArr[i][p - 1] == '\r') {
			twoDimArr[i][p - 1] = '\0';
			p--;
		}
	}
	fclose(f);
}

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *of;
	of = fopen("oStrings.txt", "w");
	int j = countFileLines("iStrings.txt");
	int i = countFileLines("subStrings.txt");
	int p = 0;

	char substr[i][50], istr[j][50], ostr[j][50];
	readFile("subStrings.txt", substr);
	readFile("iStrings.txt", istr);
	for (p = 0; p < i; p++) {
		checkSubstringPalindrome(substr[p], istr, ostr, j);
		writeFile("oStrings.txt", substr[p], ostr, j);
	}
	fclose(of);
}
