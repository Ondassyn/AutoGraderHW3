#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int isPalindrome(char c[]){
    for (int j=0; j<strlen(c)-1; j++){
        if (c[j] != c[strlen(c)-j-1]){
            return 0;
        }
    }
    return 1;
}

char *getPalindrome(char c[]){
    if (isPalindrome(c)){
        return "Is_Palindrome";
    } else {
        return "Not_Palindrome";
    }
}

int howManySubstrings(char subS2[], char c[]){
    int m = 0;
    for (int j=0; j<strlen(c)-2; j++){
        int n = 0;
        for (int i=0; i<3; i++){
            if (c[j+i] == subS2[i]){
                n++;
            }
        }
        if (n==3){
            m++;
            j+=2;
        }
    }
    return m;
}

void checkSubstringPalindrome(char subS2[], char inp[][51], char outp[][101], int l){
    for (int j=0; j<l; j++){
        char g[5];
        itoa(howManySubstrings(subS2, inp[j]), g, 10);
        strcpy(outp[j], inp[j]);
        strcat(outp[j], "\t");
        strcat(outp[j], g);
        strcat(outp[j], "\t");
        strcat(outp[j], getPalindrome(inp[j]));
        strcat(outp[j], "\n");
    }
}

void readFile(char fname[], char c[][51]){
    FILE *inputf;
    inputf = fopen(fname, "r");
    if (inputf == NULL){
        return 1;
    }
    int j = 0;
    char a[51];
    while (!feof(inputf)){
        fgets(a, 51, inputf);
        while (a[strlen(a)-1] == '\n'){
            a[strlen(a)-1] = '\0';
        }
        if (strlen(a) > 0){
            strcpy(c[j], a);
            j++;
        }
    }
    fclose(inputf);
}

int countFileLines(char fname[]){
    FILE *inputf;
    inputf = fopen(fname, "r");
    int j = 0;
    char c[51];
    while (!feof(inputf)){
        fgets(c, 51, inputf);
        while (c[strlen(c)-1] == '\n'){
            c[strlen(c)-1] = '\0';
        }
        if (strlen(c)!=0 && !feof(inputf)){
            j++;
        }
    }
    return j;
}
void writeFile(char fname[], char subS2[], char oS2[][101], int k){
    FILE *outputf;
    outputf = fopen(fname, "a");
    if (outputf == NULL){
        return 1;
    }
    fprintf(outputf, "%s\n", subS2);
    for (int j=0; j<k; j++){
        fprintf(outputf, "%s", oS2[j]);
    }
    fprintf(outputf, "\n");
    fclose (outputf);
}


int main(){

    int n1 = countFileLines("subStrings.txt");
    char subS1[n1][51];
    readFile("subStrings.txt", subS1);

    int n2 = countFileLines("iStrings.txt");
    char iS1[n2][51];
    readFile("iStrings.txt", iS1);



    char oS1[n2][101];
    FILE *os;
    os = fopen("oStrings.txt", "w");
    fclose(os);

    for (int j=0; j<n1; j++){
        checkSubstringPalindrome(subS1[j], iS1, oS1, n2);
        writeFile("oStrings.txt", subS1[j], oS1, n2);
    }
    return 0;
}
