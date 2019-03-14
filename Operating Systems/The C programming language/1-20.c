#include <stdio.h>

#define SPACE ' '
#define TAB '\t'
#define MAXBUFFER 1024

int CompSpaceNum(int TabSize, int Offset){
	return TabSize - (Offset % TabSize);
}

int getLine(char s[], int lim){
	int i;
	char c;
	
	for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++){
		s[i] = c;
	}
	if(c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	
	return i;
}

int main(){
	int TABSIZE = 4;
	char line[MAXBUFFER];
	
	int i, j, k, offset;
	
	while (getLine(line, MAXBUFFER) > 0){
		for(i = 0, offset = 0; line[i] != '\0'; i++){
			if (line[i] == TAB) {
				j = CompSpaceNum(TABSIZE, offset);
				for(k = 0; k<j; k++){
					putchar(SPACE);
					offset++;
				}
			}
			else{
				putchar(line[i]);
				offset++;
			}
		}
	}
	return 0;
}