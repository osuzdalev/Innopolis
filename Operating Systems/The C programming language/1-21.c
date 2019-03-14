#include <stdio.h>
#include <stdbool.h>

#define TAB 4
#define SPACE ' '
#define MAXBUF 1024

int getLine(char s[],int lim){
	int i, j;
	char c;
	
	for(i = 0; i<lim-1 && ((c = getchar()) != EOF && c != '\n'); i++){
		s[i] = c;
	}
	if (c == '\n'){
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return i;
}

bool checkBeginningTabBlock(int offset){
	int v;
	v = TAB - (offset % TAB);
	return (v==TAB);
}

int main(){
	char line[MAXBUF];
	char blanks[MAXBUF];
	int head, tail;
	int space, offset;
	int i, j, k;
	
	head = tail = space = offset = 0;
	
	while (getLine(line, MAXBUF) > 0) {
		for(i = 0; line[i] != '\0'; i++){
			//if char is a space: prepare for 2 possible scenarios
			//1. followed by a char
			//2.followed by another space -> belongs to a space strings
			if(line[i] == SPACE) {
				//if first space
				if(space == 0) {
					blanks[tail] = SPACE;
					tail++;
					space = 1;
				}
				//if second space
				else {
					blanks[tail] = SPACE;
					tail++;
				}
			}
			//if char is a char: check if it was precedented by a:
			//1. char
			//2. space			
			//3. space string
			else{
				//1.
				if(!space) {
					printf("%c", line[i]);
					offset++;
				}
				//2.
				else if(space && (tail == 1)) {
					printf("SPACE ");
					printf("%c", line[i]);
					offset = offset + 2;
					tail = 0;
					space = 0;
				}
				//3.
				else if(space && (tail > 1)){
					//iterating through blanks array
					for(j = 0; j<tail; j++){
						if (checkBeginningTabBlock(offset) && (tail - j >= 4)) {
							printf("TAB ");
							j = j + 3;
							offset = offset + 4;
						}
						else{
							printf("SPACE ");
							offset++;
						}
					}
					printf("%c", line[i]);
					tail = 0;
					space = 0;
				}
			}
		}
	}
}