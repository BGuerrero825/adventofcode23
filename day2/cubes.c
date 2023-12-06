#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILEPATH "C:\\Users\\brian\\Dev\\adventofcode23\\day2\\input.txt"
const size_t LINE_SIZE = 1000;

int main(){
	// open a file
	FILE * fp;
	fp = fopen(INPUT_FILEPATH, "r");
	// give an error if file doesn't exist
	if(!fp){
		perror(INPUT_FILEPATH);
	}
	// get each line of the file while null not returned (EOF)
	char line[LINE_SIZE];
	while(fgets(line, LINE_SIZE, fp) != NULL){
		printf("%s -------- ", line);
		check_game(line);
		printf("\n");
	}
	fclose(fp);
}

int check_game(char * line){
	int green_count, blue_count, red_count = 0;
	char * token = strtok(line, " ");
	char * prev_token;
	int game_num = 0;
	while(token != NULL){
		printf("%s\n", token);
		prev_token = token; 	
		token = strtok(NULL, " ");
	}
}