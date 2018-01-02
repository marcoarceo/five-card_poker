/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Five-Card Poker                                                    
* Date: November 17th, 2017                                                                         
* Description: Create the game of Poker
*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h> // Found this on stack overflow to make the system sleep

typedef struct hand
{
	int hand_row[5];
	int hand_column[5];
	/*int hand_pairs;
	int hand_threes;
	int hand_fours;
	int hand_flush;
	int hand_straight;*/
}Hand;

void display_menu(void);
int get_option(void);
int determine_option(void);
void shuffle_deck(int *deck[][13]);
void deal(const int *deck[][13], Hand *player_hand);
int one_pair(Hand *player_hand);
int two_pairs(Hand *player_hand, int pairs);
int three_of_a_kind(Hand *player_hand);
int four_of_a_kind(Hand *player_hand);
int isflush(Hand *player_hand);
int isstraight(Hand *player_hand);
int straight_flush(Hand *player_hand, int flush, int straight);
int highest_card(Hand *player_hand);
// int full_house(Hand *player_hand, int three, int pair);
void replace_cards(Hand *player_hand, const char *face[], const char *suit[]);
void ai_replace_cards(Hand *player_hand, const char *face[], const char *suit[]);
int result_points(int pairs, int three, int four, int flush, int straight, int st_flush, int full);
int determine_winner(int user_point, int computer_point, int user_high, int computer_high);
void clear_decks(Hand *player_hand);