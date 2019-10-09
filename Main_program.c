#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Header.h"
#include "func.h"


int main(int argc, char** argv) {

	srand(time(NULL));
	//Initialize variables
	struct card aCard[52];
	enum Suit cardsuit = 0;
	enum Value cardvalue = 0;
	struct Player* player;
	int Numplayer, cardarray, cardnumber = 0, i = 0, SecondNum = 0, size = 0, c = 0, to10;
	char answer;
	printf("Would you like to play Texas Hold'em instead?? Y/N : "); //if player wants to play texas hold'em
	scanf_s("%c", &answer);
	printf("How many player would you like to play with choose between 2 to 7 : ");
	scanf_s(" %d", &to10);
	if (to10 > 7 || to10 < 2)
		return 0;

	player = (struct Player*)malloc(to10 * sizeof(struct Player));
	if (player == NULL) {
		printf("memory not allocated");
		exit(0);
	}
	//initiallize deck of cards
	for (cardvalue = Deuce; cardvalue <= ace; cardvalue++)//regular version
	{
		for (cardsuit = Clubs; cardsuit <= Spades; cardsuit++)
		{
			aCard[i] = (struct card) { cardvalue, cardsuit };//pass to next card every one for loop
			i++;
		}
	}
	Swap(aCard,size);//randomize cards

	if (answer == 'y' || answer == 'Y') {//if answer is yes
		int shareofcards = 0;
		for (Numplayer = 0; Numplayer < to10; Numplayer++)
		{
			shareofcards = 0;
			for (cardarray = 0; cardarray < 5; cardarray++)
			{
				(player+Numplayer)->playernum= Numplayer + 1;//assign player number by using 'Numplayer' and plus 1 because numpalyer is initiallized wtih 0
				if (shareofcards < 3) {//give 3 same cards to player so every player has first three same cards
					(player + Numplayer)->PlayerCards[cardarray] = (struct card) { aCard[shareofcards].Value, aCard[shareofcards].Suit };
				}
				else  //after recieve 3 same cards give them extra two cards that are different
					//after giving first three samecards you will need different algorhithms, because the order need to be 123 45 123 67 123 89 ... 
					//so pattern of that is you have to multiply by num of player by 2 and add 2 on card number
					(player + Numplayer)->PlayerCards[cardarray] = (struct card) { aCard[2 * Numplayer + cardnumber + 2].Value, aCard[2 * Numplayer + cardnumber + 2].Suit };
				cardnumber++;
				shareofcards++;
			}
		}
	}
	else if (answer == 'n' || answer == 'N') { //if the answer is no
		//give 5 cards each player
		for (Numplayer = 0; Numplayer < to10; Numplayer++)
		{
			for (cardarray = 0; cardarray < 5; cardarray++)
			{
				(player + Numplayer)->playernum = Numplayer + 1; //assgin player number by counting and give a card 5 each to player
				(player + Numplayer)->PlayerCards[cardarray] = (struct card) { aCard[cardnumber].Value, aCard[cardnumber].Suit };// this is just simple counting up algorithm
				cardnumber++;
			}
		}
	}
	else
		return 0;
	
	//print out what kind of cards player has
	if (answer == 'y' || answer == 'Y') { //if game is texas hold'em
		printf("\tCards on Table\n---------------------------------\n");
		for (Numplayer = 0; Numplayer < 1; Numplayer++)
		{
			for (cardarray = 0; cardarray < 3; cardarray++)
			{
				printf("|\t");//extra design
				PrintCards((player+Numplayer)->PlayerCards[cardarray]);//print out first three cards that are sharing
				printf("\t\t|");//extra design
				printf("\n");//extra design
			}
			printf("|\t");//extra design
			printf("\t\t\t|");//extra design
			printf("\n");
			
		}
		printf("---------------------------------\n");
		for (Numplayer = 0; Numplayer < to10; Numplayer++)
		{
			for (cardarray = 3; cardarray < 5; cardarray++)
			{
				PrintCards(player[Numplayer].PlayerCards[cardarray]);//print out the other two cards that player is holding
				printf("\n");
			}
			printf("\n");
		}

		
	}
	else {
		for (Numplayer = 0; Numplayer < to10; Numplayer++)
		{
			for (cardarray = 0; cardarray < 5; cardarray++)
			{
				PrintCards(player[Numplayer].PlayerCards[cardarray]);//if its just normal game print out all 5 cards
				printf("\n");
			}
			printf("\n\n");
		}
	}
	

	//ranking deck
	for (Numplayer = 0; Numplayer < to10; Numplayer++)
	{
		RankDeck(player[Numplayer].PlayerCards);
	
	}

	RankPlayers(player, to10);

	//this is testing function with test player
	{
		////----------------------------------------------------------------------------------------------------test
		//struct Player testplayer;
		//int testplayercard = 5;
		//testplayer.PlayerCards[0] = (struct card) { four, Hearts };
		//testplayer.PlayerCards[1] = (struct card) { Deuce, Clubs};
		//testplayer.PlayerCards[2] = (struct card) { Deuce, Clubs };
		//testplayer.PlayerCards[3] = (struct card) { six, Hearts};
		//testplayer.PlayerCards[4] = (struct card) { six, Hearts};

		//RankDeck(testplayer.PlayerCards);
		//testplayercard = 0;
		//for (testplayercard = 0; testplayercard < 5; testplayercard++)
		//{
		//	PrintCards(testplayer.PlayerCards[testplayercard]);
		//	printf("\n");
		//	
		//}
		//PrintRank(testplayer.CardRank);
		////----------------------------------------------------------------------------------------------------test
	}

	printf("\n");
	system("Pause");
	return 0;
}

