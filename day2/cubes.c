#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILEPATH "C:\\Users\\brian\\Dev\\adventofcode23\\day2\\input.txt"
const size_t LINE_SIZE = 1000;
const int GREEN_MAX = 13;
const int BLUE_MAX =  14;
const int RED_MAX = 12;

int check_game(char * line);
int startswith(const char * prefix, const char * token);
int endswith(const char * suffix, const char * token);
void slice(char* token, char* segment, size_t start, size_t end);


int main(){
	// open a file to read
	FILE * fp;
	fp = fopen(INPUT_FILEPATH, "r");
	// give an error if file doesn't exist
	if(!fp){
		perror(INPUT_FILEPATH);
	}
	// get each line of the file while null not returned (EOF) and increment a sum using check_game()
	char line[LINE_SIZE];
	size_t sum = 0;
	while(fgets(line, LINE_SIZE, fp) != NULL){
		printf("\n%s", line);
		sum += check_game(line);
	}
	printf("\n\n--- GAMES SUM --- : %d\n", sum);
	fclose(fp);
}

int check_game(char * line){
	// initialize token pointers, splitting on whitespace
	char * prev_token = strtok(line, " ");
	char * token = strtok(NULL, " ");
	// parse game number from the 2nd token
	char * game_str;
	slice(token, game_str, 0, strlen(token)-1);
	int game_num = atoi(game_str);
	// iterate tokens in line
	while(token != NULL){
		// printf("%s | ", token);
		//check if any colors drawn were over their respective max size, jump to oversize label if so
		if(startswith("green", token)){
			if(atoi(prev_token) > GREEN_MAX){
				goto oversize;
			}
		}
		else if(startswith("blue", token)){
			if(atoi(prev_token) > BLUE_MAX){
				goto oversize;
			}
		}
		else if(startswith("red", token)){
			if(atoi(prev_token) > RED_MAX){
				goto oversize;
			}
		}
		// update tokens in line
		prev_token = token; 	
		token = strtok(NULL, " ");
	}
	return game_num;
	// label to exit out of oversize games 
	oversize:
		printf("OVERSIZE ---- color: %s amount: %s\n", token, prev_token);
		return 0;
}

int startswith(const char * prefix, const char * token){
	return strncmp(prefix, token, strlen(prefix)) == 0;
}

int endswith(const char * suffix, const char * token){
	return strncmp(suffix, token + (strlen(token) - strlen(suffix)), strlen(suffix)) == 0;
}

void slice(char* token, char* segment, size_t start, size_t end){
    strncpy(segment, token + start, end - start);
}