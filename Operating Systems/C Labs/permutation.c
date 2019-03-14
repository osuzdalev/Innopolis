#include <stdio.h>
#include <string.h>

void swap(char *cht1, char *cht2){
	char temp;
	temp = *cht1;
	*cht1 = *cht2;
	*cht2 = temp;
}

void charPermu(char *str, int left, int right)
{
	if (left == right)
		printf("\n%s  \n", str);
	else
	{
		for (int i = left; i <= right; i++)
		{
			printf("%d ", i);
			swap((str+left), (str+i));
			printf("%s ", str);
			charPermu(str, left+1, right);
			swap((str+left), (str+i));
			printf("%s ", str);
		}
	}
}
int main() {
	char str[] = "abc";
	charPermu(str, 0, strlen(str) - 1);
}