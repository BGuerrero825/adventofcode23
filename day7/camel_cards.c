#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILEPATH "C:\\Users\\brian\\Dev\\adventofcode23\\day7\\ez_input.txt"
#define CARDS_SIZE 5
const size_t LINE_SIZE = 1000;

void populate_hand_array(char * line);
int check_game(char * line);
int startswith(const char * prefix, const char * token);
int endswith(const char * suffix, const char * token);
void slice(char* token, char* segment, size_t start, size_t end);

struct hand{
    char cards[CARDS_SIZE];
    size_t bid;
};
enum values{zero, one, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

struct hand high_card[1000] = {{0}}, one_pair[1000] = {{0}}, two_pair[1000] = {{0}}, three_kind[1000] = {{0}},
            full_house[1000] = {{0}}, four_kind[1000] = {{0}}, five_kind[1000] = {{0}};
struct hand high_card_sorted[1000] = {{0}}, one_pair_sorted[1000] = {{0}}, two_pair_sorted[1000] = {{0}}, three_kind_sorted[1000] = {{0}},
            full_house_sorted[1000] = {{0}}, four_kind_sorted[1000] = {{0}}, five_kind_sorted[1000] = {{0}};

int main(){
    // open a file to read
	FILE * fp;
	fp = fopen(INPUT_FILEPATH, "r");
	// give an error if file doesn't exist
	if(!fp){
		perror(INPUT_FILEPATH);
	}
	char line[LINE_SIZE];
	while(fgets(line, LINE_SIZE, fp) != NULL){
		printf("\n%s", line);
        populate_hand_array(line);
	}
	fclose(fp);
}

void populate_hand_array(char * line){
    char * cards = strtok(line, " ");
    int bid = atoi(strtok(NULL, " "));
    int curr_count = 0;
    int top_count = 1;
    int second_count = 1;
    int skips[CARDS_SIZE] = {0};
    // outer loop: iterate char to compare to
    for(int i = 0; i < CARDS_SIZE; i++){
        if(skips[i] == 1) continue;
        // inner loop: iterate char being compared
        for(int j = 0; j < CARDS_SIZE; j++){
            // add to current count if chars match
            if(*(cards+i) == *(cards+j)){
                curr_count++;
                skips[j] = 1;
            }
        }
        // keep track of top occurences in hand
        if(curr_count > top_count){
            second_count = top_count;
            top_count = curr_count;
        }
        else if(curr_count > second_count) second_count = curr_count;
        curr_count = 0;
    }
    // determine which array to populate based on hand occurences
    struct hand * array_to_populate;
    if(top_count == 5) array_to_populate = five_kind;
    else if(top_count == 4) array_to_populate = four_kind;
    else if(top_count == 3 && second_count == 2) array_to_populate = full_house;
    else if(top_count == 3) array_to_populate = three_kind;
    else if(top_count == 2 && second_count == 2) array_to_populate = two_pair;
    else if(top_count == 2) array_to_populate = one_pair;
    else array_to_populate = high_card;

    struct hand new_hand;
    // copy memory from the cards char pointer into the struct char array (hacky af) 
    memcpy_s(&new_hand.cards, sizeof(char) * CARDS_SIZE, cards, sizeof(char) * CARDS_SIZE); 
    new_hand.bid = bid;
    int i = 0;
    while((array_to_populate + i)->bid != 0){
        i++;
    }
    array_to_populate[i] = new_hand;
    printf("top count: %d, second count: %d", top_count, second_count);
    //printf("%c", *new_hand.cards);
    //printf("%c", *(new_hand.cards + 1));
}

void sort_hand_array(){
    int i;
    while((two_pair[i].bid != 0)){
        
        i++;
    }
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