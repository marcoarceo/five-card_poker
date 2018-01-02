/*******************************************************************************************
* Programmer: Marco Arceo                                                                      
* Class: CptS 121, Fall  2017; Lab Section 21                                    
* Programming Assignment: Five-Card Poker                                                    
* Date: November 17th, 2017                                                                         
* Description: Create the game of Poker
*******************************************************************************************/

#include "header.h"

/*************************************************************
- Function: etc...
- Date Last Modified: 11/20/17
- Description: Displays the menu.
- Input parameters: The users option.
- Returns: Option
*************************************************************/

void rules()
{ // https://www.pagat.com/poker/rules/
	printf("1. Players place an initial bet, if required by the game being played, by placing some of their chips into a central common area known as the pot or pool.\n");
	printf("2. The dealer deals cards to the players.\n");
	printf("3. Players look at their own cards, and have the opportunity to increase their bet, placing extra chips into the pot. All other players must then either put in chips to bring their contribution to the pot to at least an equal amount or fold, discarding their cards and abandoning any chips they have so far contributed to the pot. \n");
	printf("4. Players who have not folded are known as active players. When all active players have contributed an equal amount to the pot, that is the end of the betting round. According to the variant being played, further cards may be dealt or players may have an opportunity to exchange some cards, after which there is another betting round, and so on.\n");
	printf("5. When the last betting round has ended there is a showdown: all active players show their cards, and the owner of the best five-card hand takes the contents of the pot. If at any point only one active player remains, that player automatically wins the pot without having to show any cards. \n");
	printf("6. The objective is of course to win money, and there are two ways to do this: \n");
	printf("\t1. To have the best five-card hand at the showdown.\n");
	printf("\t2. To persuade all the other players to fold. \n");
	printf("\nYou will now be directed back to the menu!\n\n");
}

void display_menu() // Displays the menu options
{
	int menu_option = 0;

	printf("WELCOME TO THE GAME OF POKER!\n\n");
	printf("1. Display game rules\n");
	printf("2. Play Game\n");
	printf("3. Exit\n");
}

int get_option(void) // Gets the option from the user
{ // Used in previous PA's
	int option = 0, status = 0;

	status = scanf("%d", &option);
	if (status == 0)
	{
		printf("Failed at reading the option!\n");
	}
	return option;
}

int determine_option(void) // Determines if the option is valid
{ // Used in previous PA's
	int option = 0;

	do // input validation loop
	{
		display_menu();
		option = get_option();
		system("cls");
	} while ((option < 1) || (option > 3));

	return option;
}

/*************************************************************
- Function: shuffle()
- Date Last Modified: 11/21/17
- Description: Shuffles cards in the deck.
- Input parameters: Pointers to deck.
- Returns: Nothing
*************************************************************/

void shuffle_deck(int *deck[][13])
{
	int row = 0, column = 0, card = 0;

	for (card = 1; card <= 52; card++)
	{
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] != 0);
		deck[row][column] = card;
	}
}

/*************************************************************
- Function: deal()
- Date Last Modified: 11/21/17
- Description: Deals Cards to the players.
- Input parameters: Pointers to player_hand.
- Returns: Nothing
*************************************************************/

// Modified O'Fallons Code

void deal(const int *deck[][13], Hand *player_hand)
{
	int row = 0, column = 0, card = 0, test = 0;

	for (card = 0; card < 5; card++)
	{
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] == 0);
		player_hand->hand_row[card] = row;
		player_hand->hand_column[card] = column;
		deck[row][column] = 0;
	}
}

/*************************************************************
- Function: display_hand()
- Date Last Modified: 11/21/17
- Description: Displays the players hand.
- Input parameters: Pointers to player_hand.
- Returns: Nothing
*************************************************************/

void display_hand(Hand *player_hand, const char *face[], const char *suit[])
{
	int row_index = 0, col_index = 0;

	for (int i = 1; i <= 5; i++)
	{
		row_index = player_hand->hand_row[i - 1];
		col_index = player_hand->hand_column[i - 1];
		printf("%d) %5s of %-8s\n", i, face[col_index], suit[row_index]);
	}
}

/*************************************************************
- Function: one_pair()
- Date Last Modified: 11/22/17
- Description: Computes if pair or not.
- Input parameters: Pointers to player_hand.
- Returns: Integer for score.
*************************************************************/

// One_Pair Function was inspired by Vikram Singh (Github)!!!!

// I had a similar design to this one but all i added was the card_numbers array and the first 'for' loop

int one_pair(Hand *player_hand)
{
	int repetition = 0, pairs = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	for (int number = 0; number < 13; number++)
	{
		if (card_numbers[number] == 2)
		{
			repetition = 1;
		}
	}

	if (repetition == 1)
	{
		pairs = 1;
		return pairs;
	}
	return pairs;
}

/*************************************************************
- Function: two_pairs()
- Date Last Modified: 11/22/17
- Description: Computes if two pairs or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

// This is a copy of my pair function since its essentially the same
// The only difference is that repetition gets incremented by ++

int two_pairs(Hand *player_hand, int pairs)
{
	int repetition = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	for (int number = 0; number < 13; number++)
	{
		if (card_numbers[number] == 2 && pairs == 1)
		{
			repetition++;
		}
	}

	if (repetition == 2)
	{
		pairs = 2;
		return pairs;
	}
	return pairs;
}

/*************************************************************
- Function: three_of_a_kind()
- Date Last Modified: 11/22/17
- Description: Computes if three_of_a_kind or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

// Copy of my two_pairs function except this one looks for three of the same kind

int three_of_a_kind(Hand *player_hand)
{
	int repetition = 0, three = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	for (int number = 0; number < 13; number++)
	{
		if (card_numbers[number] == 3)
		{
			repetition = 1;
		}
	}

	if (repetition == 1)
	{
		three = 1;
		return three;
	}
	return three;
}

/*************************************************************
- Function: four_of_a_kind()
- Date Last Modified: 11/22/17
- Description: Computes if four_of_a_kind or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

// Copy of my two_pairs function except this one looks for four of the same kind

int four_of_a_kind(Hand *player_hand)
{
	int repetition = 0, four = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	for (int number = 0; number < 13; number++)
	{
		if (card_numbers[number] == 4)
		{
			repetition = 1;
		}
	}

	if (repetition == 1)
	{
		four = 1;
		return four;
	}
	return four;
}

/*************************************************************
- Function: isflush()
- Date Last Modified: 11/22/17
- Description: Computes if flush or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

// Copy of my two_pairs function except this one looks for for a flush

int isflush(Hand *player_hand)
{
	int repetition = 0, flush = 0, card_suits[5] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_suits[player_hand->hand_row[index]]++;
	}

	for (int number = 0; number < 5; number++)
	{
		if (card_suits[number] == 5)
		{
			repetition = 1;
		}
	}

	if (repetition == 1)
	{
		flush = 1;
		return flush;
	}
	return flush;
}

/*************************************************************
- Function: isstraight()
- Date Last Modified: 11/22/17
- Description: Computes if straight or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

// Mix of my previous functions with yahtzee code
int isstraight(Hand *player_hand)
{
	int consecutive = 0, straight = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	for (int number = 0; number < 13; number++)
	{
		// This if statement was copied from my yahtzee program
		if (card_numbers[number] >= 1 && card_numbers[number + 1] >= 1 && card_numbers[number + 2] >= 1 && card_numbers[number + 3] >= 1 && card_numbers[number + 4] >= 1)
		{
			consecutive = 1;
		}
	}
	
	if (consecutive == 1)
	{
		straight = 1;
		return straight;
	}
	return straight;
}

/*************************************************************
- Function: straight_flush()
- Date Last Modified: 11/22/17
- Description: Computes if straight flush or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
- EXTRA CREDIT FUNCTION
*************************************************************/

int straight_flush(Hand *player_hand, int flush, int straight)
{
	int st_flush = 0;

	if (flush == 1 && straight == 1)
	{
		st_flush = 1;
		return st_flush;
	}
	else
	{
		return st_flush;
	}
}

/*************************************************************
- Function: highest_card()
- Date Last Modified: 11/22/17
- Description: Calculates the highest card in the hand.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
*************************************************************/

int highest_card(Hand *player_hand)
{
	int highest_value = 0, card_numbers[13] = { 0 };

	for (int index = 0; index < 5; index++)
	{
		card_numbers[player_hand->hand_column[index]]++;
	}

	highest_value = card_numbers[0];

	for (int number = 1; number < 13; number++)
	{
		if (card_numbers[number] == 0)
		{
			highest_value = 13;
		}
		else if (card_numbers[number] > highest_card)
		{ 
			highest_value = card_numbers[number];
		}
	}
	return highest_card;
}

/*************************************************************
- Function: full_house()
- Date Last Modified: 11/22/17
- Description: Computes if full_house or not.
- Input parameters: Pointers to player_hand.
- Returns: 1 or 0.
- EXTRA CREDIT FUNCTION
- Function wasnt working correctly
*************************************************************/

//int full_house(Hand *player_hand, int three, int pair)
//{
//	int full = 0;
//
//	if (three == 1 && pair == 1)
//	{
//		full = 1;
//		return full;
//	}
//	else
//	{
//		return full;
//	}
//}

/*************************************************************
- Function: replace_cards()
- Date Last Modified: 11/23/17
- Description: Replaces cards in the Users hand.
- Input parameters: Pointers to hand, face, and suit.
- Returns: Nothing
*************************************************************/

void replace_cards(Hand *player_hand, const char *face[], const char *suit[])
{
	int number = 0, replace = 0;

	do
	{
		printf("\nHow many cards (up to 3) would you like to replace?: ");
		scanf("%d", &number);
		if (number == 0)
		{
			return;
		}
	} while (number < 1 || number > 3);

	for (int index = 0; index < number; index++)
	{
		do
		{
			printf("\nWhich card do you want replaced?: ");
			scanf("%d", &replace);
		} while (replace < 1 || replace > 5);
		player_hand->hand_column[replace - 1] = rand() % 13;
		player_hand->hand_row[replace - 1] = rand() % 4;
		system("cls");
		display_hand(player_hand, face, suit);
	}
}

/*************************************************************
- Function: ai_replace_cards()
- Date Last Modified: 11/23/17
- Description: Replaces cards in the computers hand.
- Input parameters: Pointers to hand, face, and suit.
- Returns: Nothing
- NOT THE BEST SIMULATION, SORRY!
*************************************************************/

void ai_replace_cards(Hand *player_hand, const char *face[], const char *suit[])
{
	int number = 0, replace = 0;

	do
	{
		number = (rand() % 3) + 1;
		if (number == 0)
		{
			return;
		}
	} while (number < 1 || number > 3);

	for (int index = 0; index < number; index++)
	{
		do
		{
			replace = (rand() % 5) + 1;
		} while (replace < 1 || replace > 5);
		player_hand->hand_column[replace - 1] = rand() % 13;
		player_hand->hand_row[replace - 1] = rand() % 4;
		system("cls");
		// display_hand(player_hand, face, suit);
	}
}

/*************************************************************
- Function: result_points()
- Date Last Modified: 11/23/17
- Description: Determines the result of the cards.
- Input parameters: All the results.
- Returns: Point total
*************************************************************/

int result_points(int pairs, int three, int four, int flush, int straight, int st_flush, int full)
{
	int points = 0;

    /*if (full != 0)
	{
		printf("\nFull House!\n");
		points = 10;
		return points;
	}*/
	if (st_flush != 0)
	{
		printf("\nStraight Flush!\n");
		points = 10;
		return points;
	}
	else if (four != 0)
	{
		printf("\nFour of a kind!\n");
		points = 8;
		return points;
	}
	else if (flush != 0)
	{
		printf("\nFlush!\n");
		points = 6;
		return points;
	}
	else if (straight != 0)
	{
		printf("\nStraight!\n");
		points = 5;
		return points;
	}
	else if (three != 0)
	{
		printf("\nThree of a kind!\n");
		points = 4;
		return points;
	}
	else if (pairs > 1)
	{
		printf("\nTwo Pairs!\n");
		points = 3;
		return points;
	}
	else if (pairs == 1)
	{
		printf("\nOne Pair!\n");
		points = 2;
		return points;
	}
	else
	{
		printf("\nNothing!\n");
		points = 0;
		return points;
	}
}

/*************************************************************
- Function: determine_winner()
- Date Last Modified: 11/23/17
- Description: Determines who won the round.
- Input parameters: user and computer points.
- Returns: Nothing
*************************************************************/

int determine_winner(int user_point, int computer_point, int user_high, int computer_high)
{
	if (user_point > computer_point)
	{
		printf("\nUser Wins!\n\n");
	}
	if (computer_point > user_point)
	{
		printf("\nComputer Wins!\n\n");
	}
	else if (user_point == computer_point) // Uses the high valued card to break the tie
	{
		if (user_high > computer_high)
		{
			printf("\nUser Wins!\n\n");
		}
		if (computer_high > user_high)
		{
			printf("\nComputer Wins!\n\n");
		}
		else if (user_high == computer_high)
		{
			printf("\nThis round is a tie!\n\n");
		}
	}
}

/*************************************************************
- Function: clear_decks()
- Date Last Modified: 11/25/17
- Description: Clears the decks for the main loop.
- Input parameters: hands.
- Returns: Nothing
*************************************************************/

void clear_decks(Hand *player_hand)
{
	for (int index = 0; index < 5; index++)
	{
		player_hand->hand_row[index] = 0;
	}

	for (int number = 0; number < 13; number++)
	{
		player_hand->hand_column[number] = 0;
	}
}

void clear_whole_deck(int *deck[][13])
{
	int row = 0, column = 0, card = 0;

	for (card = 1; card <= 52; card++)
	{
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (deck[row][column] != 0);
		deck[row][column] = 0;
	}
}


