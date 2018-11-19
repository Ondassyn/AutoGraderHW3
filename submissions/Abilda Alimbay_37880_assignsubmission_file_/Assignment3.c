#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int countFileLines (char filename[]) { 	//a functions that would count filelines: if it will meet a '\n' character my variable answer would increase by 1
	FILE *counting= fopen (filename, "r");
	int answer=0;
	char ch;
	if (counting==NULL)
	{
		printf ("Can not open the file in\n");
		return 0;
	}
	do {
		ch=fgetc(counting);
		if (ch=='\n')
			answer++;
		else if (ch==EOF)
			break;
	} while (!feof(counting)); //not to take last eof character
	fclose(counting);
	return answer+1;
}
void readFile(char filename[], char twoDimArr[][50]){
	FILE *myfile=fopen(filename, "r");
	if (myfile==NULL)							//checking for validity
	{
		printf("Can not open the file\n");
		exit(0);
	}
	char copy[50];					//temporarily variable
	int countonedim, countseconddim, nrIOfilelines=countFileLines(filename);
	for (countonedim=0, countseconddim=0; countonedim < nrIOfilelines; countseconddim++) {
		int temp=0;
		while(temp<50) {					//here we are running till 50 because the max length is 50. in case we met '\n' we wiil reassign it to'\0' so that it would work in strcpy
			copy[temp]=getc(myfile);
			if(copy[temp]=='\n'){
				copy[temp]='\0';
				break;
			}
			temp++;
		}
		if (countonedim<nrIOfilelines) {
			if (countonedim!=nrIOfilelines-1 && strlen(copy)!=50)//actually this and the next if statement does ont make much of sense, it just was my trial to fix one magical extra line in the end of output
				strcpy(twoDimArr[countonedim], copy);				// i don't think that they helped, but it is close to the deadline and I was afraid of editing something
			if (countonedim==nrIOfilelines-1 && 50!=strlen(copy))
				strcpy(twoDimArr[countonedim], copy);
		}
		countonedim++;
		countseconddim=0;
	}
	fclose(myfile);
}
int isPalindrome(char str[])
{
	int sum=0, sum1=0, counter, counter1;
	for(counter=0, counter1=strlen(str)-1; counter<strlen(str) && counter1>=0; counter++, counter1--)		//here we are comparing the sum of chars from the beginning and the end
	{	sum+=(unsigned int)str[counter];																	//if them are palindrom they has to be the same
		sum1+=(unsigned int)str[counter1];
		if (sum!=sum1)																//for ex. : astana: sum1=(int)'a', sum2=(int)'a' equal going further sum1='a'+'s', sum2='a'+'n' sum1!=sum2->break;
			return 0;
	}
	return 1;
}
char *getPalindrome (char str[]) {
	int i=strlen("Not_Palindrome");
	char *Palindrome=(char *)malloc(i*sizeof(char));					//creating a block of memory for the size of Not_Palindrome, it would right enough to store Not_Palindrome and Is_Palindrome would anyway fit
	int n=isPalindrome(str);
	if (n==1)
		Palindrome="Is_Palindrome";
	else
		Palindrome="Not_Palindrome";
	return Palindrome;
}
int howManySubstrings(char subStr[], char str[]) {
	int i=0, count=0;
	int howmany=0;
	while(strlen(str)>i) {
		if(subStr[count]==str[i] && subStr[count+1]==str[i+1] && subStr[count+2]==str[i+2]){		//if and only if all three are equal than we are incrementing howmany
			howmany++;
			i+=2; //assignment says NONOVERLAPING so here it is
		}
		i++;
	}
	return howmany;
}
void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines) {
	int i=0, tp;
	char tempor[50]="";
	do {
		strcpy(oStringData[i], iStringData[i]);
		if(iStringData[i][0]==0) //!!!!!!!!!!!!		----------CHECHK FOR ECLIPSE ???0????----------------!!!!!!!!!!\\\\\\\\\\\\\\\///// I am writin code in devcpp and that helped me to get rid of extra
			break;																						// magical line in the end, 0 was the symvol that was the firs
		tp=strlen(oStringData[i]);
		oStringData[i][tp]='\t';
		oStringData[i][tp+1]=howManySubstrings(subStr, iStringData[i])+'0';
		oStringData[i][tp+2]='\t';
		oStringData[i][tp+3]='\0';
		if (getPalindrome(iStringData[i])=="Is_Palindrome")
			tp=0;
		else
			tp=1;
		char isPalindrome[15]="Is_Palindrome"; char notPalindrome[15]="Not_Palindrome";
		(tp>0) ? strcpy(tempor, notPalindrome) : strcpy(tempor, isPalindrome);
		strcat(oStringData[i], tempor);
	//	printf("%s\n", oStringData[i]);
		i++;
//		free(tempor);
	} while(i<nrIOfileLines);
}
void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfilelines)  {
	int num=countFileLines(ssData);
	char substrings[num][50];
	char newoStringData[nrIOfilelines][50];
	char iStringData[nrIOfilelines][50];
	readFile(ssData, substrings); readFile(fileName, iStringData);
	int counter=0, nestedcounter=0;
	FILE *output=fopen("oStrings.txt", "w");
	for (counter=0; counter<num; counter++) {					// while substrings did not end
		if(strlen(substrings[counter])==3) {
			fprintf(output, "%s\n", substrings[counter]);
			checkSubstringPalindrome(substrings[counter], iStringData, newoStringData, nrIOfilelines); //getting new oStringData for  new substring
			for(nestedcounter=0; nestedcounter<nrIOfilelines-1; nestedcounter++) {
				fprintf(output, "%s\n", newoStringData[nestedcounter]);
				//printf("%s\n", newoStringData[nestedcounter]);
			}
		}
		fprintf(output ,"\n");
	}
	fclose(output);
}
void threelinesarefun() {									///just to let my main function be cool)
	int nrIOfilelines=countFileLines("iStrings.txt");
	char fileName[50]="iStrings.txt", ssData[50]="subStrings.txt", oStringData[nrIOfilelines][50];
	writeFile(fileName, ssData, oStringData, nrIOfilelines);
}
int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);
	threelinesarefun();						//and now my main file contains just 3 lines!!
	return EXIT_SUCCESS;
}
//the code was Done By Abilda Alimbay
