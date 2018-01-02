/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Five-Card Poker                                                    
* Date: November 17th, 2017                                                                         
* Description: Create the game of Poker
*******************************************************************************************/

/*
ISSUE WITH MY MAIN LOOP, IT ONLY PLAYS ONE ROUND! (WHY!?!?)
IT WAS WORKING FINE DURING BREAK :(
*/

#include "header.h"

int main(void)
{
	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char *face[13] = { "Ace", "Duece", "Three", "Four", "Five", "Six", "Seven", "Eight",
	"Nine", "Ten", "Jack", "Queen", "King" };
	bool game = true;
	int option = 0, pairs = 0, three = 0, four = 0, flush = 0, straight = 0, st_flush = 0, full = 0;
	int computer_point = 0, user_point = 0, user_high = 0, computer_high = 0, round = 0;
	int deck[4][13] = { 0 };

	Hand user_hand, computer_hand;

	srand((unsigned)time(NULL));
	do
	{
		do
		{
			option = determine_option();
			switch (option)
			{
			case 1: rules();
				system("pause");
				system("cls");
				break;
			case 3: printf("Goodbye!\n");
				game = false;
				return 0;
			}
		} while (option != 2 && option != 3);

		while (round < 10)
		{
			printf("Round Number %d", round + 1);
			printf("\n\n");
			clear_whole_deck(deck);
			clear_decks(&user_hand);
			clear_decks(&computer_hand);
			shuffle_deck(deck);
			deal(deck, &user_hand);
			deal(deck, &computer_hand);
			printf("Cards have been dealt to the players...\n\n");
			system("pause");
			system("cls");
			for (int player = 0; player < 2; player++)
			{
				switch (player)
				{
				case 0:
					printf("PLAYER: \n\n");
					pairs = 0, three = 0, four = 0, flush = 0, straight = 0, st_flush = 0, full = 0;
					display_hand(&user_hand, face, suit);
					replace_cards(&user_hand, face, suit);
					pairs = one_pair(&user_hand);
					pairs = two_pairs(&user_hand, pairs);
					three = three_of_a_kind(&user_hand);
					four = four_of_a_kind(&user_hand);
					flush = isflush(&user_hand);
					straight = isstraight(&user_hand);
					st_flush = straight_flush(&user_hand, flush, straight);
					// full = full_house(&user_hand, three, pairs);
					user_point = result_points(pairs, three, four, flush, straight, st_flush, full);
					user_high = highest_card(&user_hand);
					system("pause");
					system("cls");
					break;
				case 1:
					printf("COMPUTER: \n\n");
					pairs = 0, three = 0, four = 0, flush = 0, straight = 0, st_flush = 0, full = 0;
					// display_hand(&computer_hand, face, suit);
					printf("The computer is deciding his changes...\n");
					Sleep(2000); // Stack overflow
					ai_replace_cards(&computer_hand, face, suit);
					pairs = one_pair(&computer_hand);
					pairs = two_pairs(&computer_hand, pairs);
					three = three_of_a_kind(&computer_hand);
					four = four_of_a_kind(&computer_hand);
					flush = isflush(&computer_hand);
					straight = isstraight(&computer_hand);
					st_flush = straight_flush(&computer_hand, flush, straight);
					// full = full_house(&computer_hand, three, pairs);
					printf("The computer's hand consists of...");
					computer_point = result_points(pairs, three, four, flush, straight, st_flush, full);
					computer_high = highest_card(&computer_hand);
					system("pause");
					system("cls");
					break;
				}
			}
			printf("Players Hand: \n\n");
			display_hand(&user_hand, face, suit);
			printf("\n\nComputers Hand: \n\n");
			display_hand(&computer_hand, face, suit);
			determine_winner(user_point, computer_point, user_high, computer_high);
			round += 1;
			system("pause");
			system("cls");
		}
	} while (game == true);
}
