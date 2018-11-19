#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

void writeFile(char fileName[], char subString[], char Output[][50], int stringLines) {
     FILE *f;
     f = fopen(fileName, "a");
     
     if (f == NULL) {
        return;
     }
     
     fprintf(f, "%s\n", subString);
     
     for (int j = 0; j < stringLines; j++) {
         fprintf(f, "%s", Output[j]);
     }
     fprintf(f, "\n");
     fclose(f);
}

// Returns 1 if strings is isPalindrome and 0 otherwise
int isPalindrome(char s[]) {
    int n = strlen(s);
    int l = 0, r = n - 1;
    while (l < r) {
          if (s[l] != s[r])
             return 0;
          l++, r--;
    }
    return 1; 
}

char *getPalindrome(char s[]) {
     if (!isPalindrome(s)) {
        return "Not_Palindrome";
     } else {
        return "Is_Palindrome";
     }
}

int howManySubstrings(char t[], char s[]) {
    int n = strlen(s);
    int m = strlen(t);
    int cnt = 0;
  
    for (int i = 0; i < n - m + 1; i++) {
        _Bool have = 1;
        for (int j = 0; j < m; j++) {
            if (s[i + j] != t[j])
                have = 0;
        }
        if (have) {
            cnt++;
            // Jumps so it will not count overlaps
            i += m - 1;
        }                                                  
    }
    return cnt;
}

// Converts integer to string
char *intToString(int x) {
    int r = 0;
    char *a = (char*)malloc(sizeof(char) * 10);
    // Special case
    if (x == 0) {
       a[0] = '0', a[1] = '\0';
       return a;
    }
    // Inserting digits to array
    while (x > 0) {
          a[r++] = (char)(x % 10 + (int)'0');
          x /= 10;    
    }
    // Reversing Digits
    int l = 0;
    a[r--] = '\0';
    while (l < r) {
        char c = a[r];
        a[r] = a[l], a[l] = c;
        l++, r--;
    }
    return a;
}

void checkSubstringPalindrome(char sub[], char sIn[][50], char Answer[][50], int Lines) {
    for (int i = 0; i < Lines; i++) {
        Answer[i][0] = '\0';
        strcat(Answer[i], sIn[i]);
        strcat(Answer[i], "\t");
        strcat(Answer[i], intToString(howManySubstrings(sub, sIn[i])));
        strcat(Answer[i], "\t");
        strcat(Answer[i], getPalindrome(sIn[i]));
        strcat(Answer[i], "\n");
    }
}

void readFile(char filename[], char In[][50]) {
     FILE *f;
     f = fopen(filename, "r");
     if (f == NULL) {
        return;
     }
     char x;
     int L = 0, l = 0;
     // False while first encounter of non space, true otherwise 
     _Bool encounter = 0;     
     while (fscanf(f, "%c", &x) == 1) {
           if (x == '\n') { 
              // Removing all spaces at the end
              while (l - 1 >= 0 && In[L][l - 1] == ' ') l--;
              In[L][l] = '\0';
              L++, l = 0;
              encounter = 0;
           } else {
              // Remvoing all spaces at the beginning
              if (x == ' ' && !encounter) {
                 continue;
              }
              if (x != ' ') encounter = 1;
              In[L][l++] = x;
           }
     }

     fclose(f);    
}

int countFileLines(char filename[]) {
     FILE *f;
     f = fopen(filename, "r");
     if (f == NULL) {
        return 0;
     }
     char x;
     int L = 0;
     
     while (fscanf(f, "%c", &x) == 1) 
           if (x == '\n') L++;
     
     fclose(f);
     
     return L;  
}

int main(void) {
    
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));
    
    int subLines = countFileLines("subStrings.txt");
    int stringLines = countFileLines("iStrings.txt");
    
    char subStrings[subLines][50], strings[stringLines][50]; 
    
    readFile("subStrings.txt", subStrings);
    readFile("iStrings.txt", strings);

    char Output[stringLines][50];
    for (int i = 0; i < subLines; i++) {

        checkSubstringPalindrome(subStrings[i], strings, Output, stringLines);
        
        writeFile("oStrings.txt", subStrings[i], Output, stringLines);
    }
    return 0;       
}