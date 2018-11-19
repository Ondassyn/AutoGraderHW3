#include <stdio.h>
#include <string.h>

int countFileLines(char filename[]){
FILE*file;
file=fopen(filename,"r");
char ch;
int count=0;
do{
	ch=fgetc(file);
	if(ch=='\n'){
	count++;}   // count the number of \n occurrence in the file
	}while(!feof(file));
fclose(file);
return count;
}


int isPalindrome(char str[]){
	int i=0;
		int length=strlen(str);  // find the length of the string
		char rstr[length]; // initialize new array of chars of the same length as the string above
			do{
				rstr[i]=str[length-1];  //reversing string and saving it to rstr[] array
				i++;
				length--;
			}while(length!=0);
			rstr[i]='\0';
			int a=strcmp(str,rstr); // comparing reverse rstr[] array of char with the original one
			      if(a==0){
			        return 1;   // if they are equal return true
			      }
			      else{
			        return 0; // if they are not equal return false
			      }}
char *getPalindrome(char str[]){
	if(isPalindrome(str)== 1){
		return "Is_Palindrome";  // if the isPalindrome is 1 return is_Palindrome
	}else{
		return "Not_Palindrome";  // if the isPalindrome is 0 return Not_Palindrome
	}}


int howManySubstrings(char subStr[], char str[]){
	int b=0, a=0;
	int count =0,number=0;
	  do{    a = 0;
	        count = 0;
	        while ((subStr[a]==str[b] )){
	      if(str[b]=='\0'&&subStr[a]=='\0'){
	        	   count--;}
	            count++; //while substring char is equal to string char increment count  that is a number of time they were equal in a row
	            b++;a++;
	           }
	   if (count == strlen(subStr)){ //if the number of times they were equal in a row is equal to the length of substring
	        count = 0;
	            number++;  //increment the "number" of substring occurrence
	        }
	        else
	            b++;
	    }while(b< strlen(str));
return number;}


void checkSubstringPalindrome(char subStr[], char iStringData[][50], char oStringData[][50], int nrIOfileLines){
	  char str[50];
	  int i=0,j=0;
	  int subcount;
	    for(i=0;i<nrIOfileLines;i++){
	    	for(j=0;iStringData[i][j]!='\n';j++){

	    		str[j]=iStringData[i][j];      //converting 2d array into 1d array
	    		oStringData[i][j]=iStringData[i][j];}
	            str[j]='\0';
	            subcount=howManySubstrings(subStr,str);
	            oStringData[i][j]='\t';
	            j++;
	            oStringData[i][j]=subcount;
	            j++;
	            oStringData[i][j]='\t';
	            j++;
	          char *ch=getPalindrome(str);
	        while(*ch!='\0') {
	    	 oStringData[i][j]= *ch;
	    	     j++;
	    	      ch++;
	    	     }
	        oStringData[i][j]='\n';
	    }

}

void readFile(char filename[], char twoDimArr[][50]){
	FILE*file;
	file=fopen(filename,"r");
 int i = 0;
 int j=0;
 int count = countFileLines(filename);
 for(i=0;i<count;){
	 for(j=0;twoDimArr[i][j]!='\n';++j){   //loading symbols from .txt file into 2d array
		twoDimArr[i][j]=getc(file);
if (twoDimArr[i][j]==EOF){
	 break;}
if (twoDimArr[i][j]=='\n'){   //every time the line in file ends with \n start loading next row of array;
       i++;
        j=-1;
       }}}

fclose(file);}
void writeFile(char fileName[], char ssData[], char oStringData[][50], int nrIOfileLines){
FILE *output;
output=fopen(fileName,"a");
if(output==NULL) printf("Can't open %s",fileName);
fprintf(output,"%s\n",ssData);
int i,j;
for(i=0;i<nrIOfileLines;i++){
	for(j=0;oStringData[i][j]!='\n';j++){
		fprintf(output,"%c",oStringData[i][j]);
		if(oStringData[i][j]=='\t'){
			j=j+1;
			fprintf(output,"%i",oStringData[i][j]); /* due to the fact that number of substring occurrence is of type integer we write the value of array
			                                         into the file as %i every time the value of the previous is \t */
			j=j+1;
			fprintf(output,"%c",oStringData[i][j]);
			}
		}
	fprintf(output,"\n");    // to end every row of 2d array with a new line
}
fprintf(output,"\n");
fclose(output);
}

int main(){
	char filename[]="subStrings.txt";
	char file[]="iStrings.txt";
    char *output="oStrings.txt";
    remove("oStrings.txt");

	int count1;
	count1 = countFileLines(filename);
	char twoDimArr1[count1][50];
	readFile(filename, twoDimArr1);

	int count2;
	count2 = countFileLines(file);
	char twoDimArr2[count2][50];
	readFile(file, twoDimArr2);

	int i,j;
  	char subStr[50];
  char oStringData[count2][50];

  	for(i=0;i<count1;i++){
    	for(j=0;twoDimArr1[i][j]!='\n';j++){    //converting 2d array of substring into 1d array
    		subStr[j]=twoDimArr1[i][j];
    	}
    	subStr[j]='\0';        //every time a row of a substring in 2d array ends call the functions to check for being a palindrome and number of substr occurrence
    	checkSubstringPalindrome(subStr, twoDimArr2,oStringData, count2);
    	writeFile(output, subStr, oStringData, count2); //write results to file of every substring
    	j=0;
    }
	return 0;
}


