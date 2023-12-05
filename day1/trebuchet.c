#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	// take_input();
	
}



void take_input(){
	char * input = malloc(sizeof(char)*20);
	printf("Type something: ");
	scanf("%s", input);
	char * output = malloc(sizeof(char)*30); 
	strcat(strcat(output, "You said, "), input);
	printf("%s", output);
	free(input);
}
