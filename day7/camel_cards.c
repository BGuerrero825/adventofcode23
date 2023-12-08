#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILEPATH "C:\\Users\\brian\\Dev\\adventofcode23\\day7\\input.txt"
#define CARDS_SIZE 5
const size_t LINE_SIZE = 1000;

struct hand{
    char cards[CARDS_SIZE];
    size_t bid;
};

void populate_hand_array(char *);
void sort_hand_array(struct hand *, struct hand *);
int lower_cards(char *, char *);
int card_to_int(char);
int total_hand_array(struct hand *, size_t *);

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
    sort_hand_array(high_card, high_card_sorted);
    sort_hand_array(one_pair, one_pair_sorted);
    sort_hand_array(two_pair, two_pair_sorted);
    sort_hand_array(three_kind, three_kind_sorted);
    sort_hand_array(full_house, full_house_sorted);
    sort_hand_array(four_kind, four_kind_sorted);
    sort_hand_array(five_kind, five_kind_sorted);
    size_t rank = 1;
    size_t index = 0;
    size_t total = 0;
    total = 0;
    total += total_hand_array(high_card_sorted, &rank);
    total += total_hand_array(one_pair_sorted, &rank);
    total += total_hand_array(two_pair_sorted, &rank);
    total += total_hand_array(three_kind_sorted, &rank);
    total += total_hand_array(full_house_sorted, &rank);
    total += total_hand_array(four_kind_sorted, &rank);
    total += total_hand_array(five_kind_sorted, &rank);
    printf("\n----- GRAND TOTAL -----\n%d", total);
	fclose(fp);
}

int total_hand_array(struct hand * hand_array, size_t * rank){
    size_t index = 0;
    size_t total = 0;
    while(hand_array[index].bid != 0){
        total += *rank * hand_array[index].bid;
        index++;
        (*rank)++;
    }
    return total;
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

void sort_hand_array(struct hand * hand_array, struct hand * hand_array_sorted){
    size_t array_size = 0;
    // get the number of populated elements in the array
    while(hand_array[array_size].bid != 0){
        array_size++;
    }
    // if array has less than 2 populated elements, don't sort
    if(array_size < 2){
        hand_array_sorted[0] = hand_array[0];
        return;
    }
    int selected[1000] = {0};
    size_t low_index = 0; 
    // outer loop: iterate through loop array_size times, each time selecting the lowest element
    for(int i = 0; i < array_size; i++){
        // inner loop: iterate each element in the array, record lowest and compare to newest element
        for(int j = 1; j < array_size; j++){
            if(selected[j] == 1) continue;
            if(lower_cards(hand_array[low_index].cards, hand_array[j].cards) == 1){
                low_index = j;
            }
        }
        selected[low_index] = 1;
        hand_array_sorted[i] = hand_array[low_index];
        // search for next unselected hand, use that as low_index starting val
        low_index = 0;
        for(int k = 0; selected[k] != 0; k++){
            low_index = k+1;
        }
    }

}
// takes in two cards sets and returns 1 if the second is lower
int lower_cards(char * low_cards, char * new_cards){
    for(int i = 0; i < CARDS_SIZE; i++){
        if(card_to_int(*(new_cards+i)) > card_to_int(*(low_cards+i))){
            return 0;
        }
        else if(card_to_int(*(new_cards+i)) < card_to_int(*(low_cards+i))){
            return 1;
        }
    }
    return 0;
}

int card_to_int(char card){
    if(card == '2') return 2;
    else if(card == '3') return 3;
    else if(card == '4') return 4;
    else if(card == '5') return 5;
    else if(card == '6') return 6;
    else if(card == '7') return 7;
    else if(card == '8') return 8;
    else if(card == '9') return 9;
    else if(card == 'T') return 10;
    else if(card == 'J') return 11;
    else if(card == 'Q') return 12;
    else if(card == 'K') return 13;
    else if(card == 'A') return 14;
    else return 0;
}