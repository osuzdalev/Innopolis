#include <stdio.h>
#define MAX 100

void printLine(char s[], int lim){
	int i;
	for(i =0; i<lim; i++){
		printf("%c", s[i]);
	}
}

void reverse(char s[], int lim){
	int i, j;
	char ch;

	j = lim-1;
	for(i = 0; i<j; i++){
		ch = s[i];
		s[i] = s[j];
		s[j] = ch;
		j--;
	}
}

//fills an array and returns its size
int getLine(char s[], int lim){
	int i;
	char c;
	
	//stops when char is 'Enter' or EOF
	for(i = 0; i<lim-1 && (c = getchar()) != EOF && c != '\n'; i++){
		s[i] = c;
	}
	if(c == '\n'){
		s[i] = c;
		i++;
	}
	//places last char in array as 'stop'
	s[i] = '\0';
	return i;
	
}
int main(){
	char s[MAX];
	int len;
	
	while ((len = getLine(s, MAX)) != 0){
		reverse(s, len);
		printLine(s, len);
		printf("%c", '\n');
	}	
}