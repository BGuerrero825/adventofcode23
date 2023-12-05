#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
	// take_input();
	parse_file();	
}

void parse_file(){
	FILE *fp;
	char buff[255];
	int i = 0;
	fp = fopen("input_cubes.txt", "r");
	while(fscanf(fp, "%s", buff) != EOF){
		printf("%s", buff);
		i++;
	}
	fclose(fp);
	printf("\niterations: %d\n", i);
	printf("buff contents: %s\n", buff);
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
