#include <stdio.h>
#define NUM_PAGE 20
#define NUM_FRAME 3

//finds the page with the longest refrence time and returns its index in frames
//foreward declaration
int findReplace(int frames[], int pages[], int pos){
	int i, j, max, indx, dist;
	int counter[3] = {NUM_PAGE - pos, NUM_PAGE - pos, NUM_PAGE - pos};
	//searches for next iteration of page and updates counter
	for(i = 0; i<NUM_FRAME; i++){
		for(j = pos; j<NUM_PAGE; j++){
			dist = j - pos;
			if(frames[i] == pages[j]){
				counter[i] = dist;
				break;
			}
		}
	}
	
	//checks which page will wait longest and returns it as frame to be replaced
	max = counter[0];
	indx = 0;
	for(i = 1; i<NUM_FRAME; i++){
		if(counter[i] >= max){
			max = counter[i];
			indx = i;
		}
	}
	return indx;
}

void optimal(int pages[], int frames[]){
	int i, j, faults, flag1, flag2, indx;
	faults = 0;
	flag1 = 0;
	flag2 = 0;
	indx = 0;
	//iterate through the pages
	for(i = 0; i < NUM_PAGE; i++){
		flag1 = flag2 = 0;
		
		//checking if page already in frames
		for(j = 0; j < NUM_FRAME; j++){
			//if yes, up pos and do nothing
			if(frames[j] == pages[i]){
				//pass on other conditions
			   flag1 = flag2 = 1;
			   break;
			   }
		}

		//checking for initial comparison with -1
		if(flag1 == 0){
			for(j = 0; j < NUM_FRAME; j++){
				//if yes, update pos and replace
				if(frames[j] == -1){
					faults++;
					frames[j] = pages[i];
					//pass on last condition
					flag2 = 1;
					break;
				}
			}    
		}
			
		//if page not in full frame, replace it to the proper page
		if(flag2 == 0){
			printf("REPLACING PAGE\n");
			indx = findReplace(frames, pages, i);
			faults++;
			frames[indx] = pages[i];
			//print frames after each iteration
			for(j = 0; j<NUM_FRAME; j++){
				printf("%i\t", frames[j]);
			}
			printf("\n");
		}
	}
	//print number of pagefaults
	printf("N° page faults\n");
	printf("%i", faults);
}

int main(){
	int frames[3] = {-1, -1, -1};
	int pages[20] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	optimal(pages, frames);
}