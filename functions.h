#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//make bool variables to if the player has certain hand ranking is true
bool bPair, bTwopair, bFullhouse, bThreepair, bFourpair, bStraight, bFlush, bStraightFlush, bRoyalFlush;
void RankDeck(struct Player *deck) {
	//initiallize the variables
	bPair = false;
	bTwopair = false;
	bThreepair = false;
	bFourpair = false;
	bStraight = false;
	bFlush = false;
	bFullhouse = false;
	bStraightFlush = false;
	bRoyalFlush = false;
	int c, d, n = 5, countplayer = 0, i = 0;

	enum value swap;
	swap = Deuce;
	for (c = 0; c < n - 1; c++) //use bubble sort to sort value of player's card
	{
		for (d = 0; d < n - c - 1; d++)
		{
			if (deck->PlayerCards[d].Value> deck->PlayerCards[d + 1].Value)
			{
				swap = deck->PlayerCards[d].Value;
				deck->PlayerCards[d].Value = deck->PlayerCards[d + 1].Value;
				deck->PlayerCards[d + 1].Value = swap;
			}
		}
	}
	//check if cards has any rank
	onePair(deck);
	TwoPair(deck);
	threeOfaKind(deck);
	straight(deck);
	flush(deck);
	fullHouse(deck);
	fourOfaKind(deck);
	straightFlush(deck);
	royalFlush(deck);
	//if bool is true change bool to enum CardRank
	{
		if (bRoyalFlush)
			deck->CardRank = eRoyalFlush;
		else if (bStraightFlush)
			deck->CardRank = eStraightFlush;
		else if (bFourpair)
			deck->CardRank = eFourpair;
		else if (bFullhouse)
			deck->CardRank = eFullhouse;
		else if (bFlush)
			deck->CardRank = eFlush;
		else if (bStraight)
			deck->CardRank = eStraight;
		else if (bThreepair)
			deck->CardRank = eThreepair;
		else if (bTwopair)
			deck->CardRank = eTwoPair;
		else if (bPair)
			deck->CardRank = ePair;
		else
			deck->CardRank = nothing;
	}

}
void PrintRank(enum rank player) {
	//print out what kind of enum ranking player has
	const char* rank = "";
	switch (player) {
	case ePair: rank = "Pair"; break;
	case eTwoPair: rank = "Two Pair"; break;
	case eThreepair: rank = "ThreePair"; break;
	case eStraight: rank = "Straight"; break;
	case eFlush: rank = "Flush"; break;
	case eFullhouse: rank = "fullhouse"; break;
	case eFourpair: rank = "Four Pair"; break;
	case eStraightFlush: rank = "Straight Flush"; break;
	case eRoyalFlush: rank = "Royal Flush"; break;
	case nothing: rank = "nothing"; break;
	default: rank = "nothing"; break;
	}
	printf("%s", rank);
}
void onePair(struct Player* valueCheck)
{
	//this function will go through all the cards and if it finds any cards that has same value
	int i = 0, j = 0;
	for (i = 0; i < 5; i++)//check from first card
		for (j = 0; j < 5; j++)//if any card is same as card[i]
			if (i != j) {
				if (valueCheck->PlayerCards[i].Value == valueCheck->PlayerCards[j].Value) {
					bPair = true;
					valueCheck->highestvalue.Value = valueCheck->PlayerCards[i].Value;

				}

			}

}
void TwoPair(struct Player* valueCheck)
{
	//this function will go through all the cards and find first same two cards and assign that as 'firstnum' and
	//if it find another same two cards that are not equal to 'firstnum' then bool Twopair will be true
	int i = 0, j = 0, count = 0, counttwo = 0, firstnum = 0;
	for (i = 0; i < 5; i++) {//check from first card
		for (j = 0; j < 5; j++) {//comepare with card[i] and card[j
			if (i != j)//let program dont count same card as i, only different card
				if (valueCheck->PlayerCards[i].Value != firstnum) {//dont count first Pair card that you've already counted
					if (valueCheck->PlayerCards[i].Value == valueCheck->PlayerCards[j].Value) {//any time if card[i] and card[j] is smae
						firstnum = valueCheck->PlayerCards[i].Value;//if its same let first card be card you've found
						count++;//count one up if found one pair
						if (count == 2) {//if found two pair
							bTwopair = true;
							//let second card be highest value of the player be cause we've bubble sort already so last card will be highest card
							valueCheck->highestvalue.Value = firstnum;

						}

					}
				}

		}
	}

}
void threeOfaKind(struct Player* valueCheck)
{
	//this function will go through all the cards and if it finds 3 cards that has same value
	int i = 0, j = 0, count = 1;
	for (i = 0; i < 5; i++) {//check from first card
		for (j = 0; j < 5; j++)
			if (i != j) //let program dont count same card as i, only different card
				if (valueCheck->PlayerCards[i].Value == valueCheck->PlayerCards[j].Value) {//any time if card[i] and card[j] is smae
					count++;//count one up if found same card
					if (count == 3) {//if it founds 3 same card
						bThreepair = true;
						count = 1;
						//let second card be highest value of the player be cause we've bubble sort already so last card will be highest card
						valueCheck->highestvalue.Value = valueCheck->PlayerCards[i].Value;
					}
				}
		count = 1;//if did not found 3 reset count to 1
	}
}
void straight(struct Player* valueCheck)
{
	//this function will start from first cards and if first card and second card - 1 is same it will jump to third and fourth and so on
	//and finally all 5 cards has eqaul to first card and second card -1 is true bool straight will be true
	int i = 0, count = 0;
	for (i = 0; i < 5; i++)//check from first card
	{
		if (valueCheck->PlayerCards[i].Value == valueCheck->PlayerCards[i + 1].Value - 1) {//the deck is bubble sorted so if the (next card - 1) is same value as prev card
			count++;
			if (count == 4) {
				bStraight = true;
				//let second card be highest value of the player be cause we've bubble sort already so last card will be highest card
				valueCheck->highestvalue.Value = valueCheck->PlayerCards[4].Value;

			}

		}
	}

}
void flush(struct Player* valueCheck)
{
	//if all cards has same suit bool flush will be true
	int i = 0, j = 0, count = 0;
	for (i = 0; i < 5; i++)//check from first card
	{
		for (j = 0; j < 5; j++)//the card we comparing with card[i]
		{
			if (valueCheck->PlayerCards[i].Suit == valueCheck->PlayerCards[j].Suit) {
				count++;//if card[i] suit is same as card[j] count one up
				if (count == 4) {//if it founds 4 times
					bFlush = true;//flush true
				}
			}
		}count = 0;//if card[i] could not found 4 times reset count value

	}

}
void fullHouse(struct Player* valueCheck)
{
	//if bool two pair and three pair are on that two bool variable will turn false and bool full house will be true
	if (bTwopair&&bThreepair) {
		bTwopair = false;
		bThreepair = false;
		bFullhouse = true;
	}
}
void fourOfaKind(struct Player* valueCheck)
{
	//this function will go through all the cards and if it finds 4 cards that has same value
	int i = 0, j = 0, count = 0;
	for (i = 0; i < 5; i++) {//check from first card
		for (j = 0; j < 5; j++)
			if (i != j)//let program dont count same card as i, only different card
				if (valueCheck->PlayerCards[i].Value == valueCheck->PlayerCards[j].Value) {//any time if card[i] and card[j] is smae
					count++;//count one up if found same card
					if (count == 3) {//if it founds 3 same card that are different position
						bFourpair = true;
						count = 0;
						valueCheck->highestvalue.Value = valueCheck->PlayerCards[i].Value;

					}
				}
		count = 0;//if not found 4 times reset count to 0
	}
}
void straightFlush(struct Player* valueCheck)
{
	//if bool straight and boo flush are on that two bool variable will turn false and bool striaght flush will be true
	if (bStraight&&bFlush) {
		bStraight = false;
		bFlush = false;
		bStraightFlush = true;
	}
}
void royalFlush(struct Player* valueCheck)
{
	//if the cards has straight, flush which is stragiht flush, turn that three bool into false and make royalflush true
	if (bStraightFlush && valueCheck->PlayerCards[4].Value == ace)
	{
		bStraight = false;
		bFlush = false;
		bStraightFlush = false;
		bRoyalFlush = true;
	}
}
void Swap(struct card *card, int size) {
	//initaillize variables
	int randnum, u, limit = 0;
	struct card temp;
	for (u = 51 - size; u > 0; u--)
	{
		//starting from the end, this function will measure random number from 0 to number left over and 'limit' variable will measure 0 to leftover
		//store first card in to temporary and put random card into first card and put first card where random card was
		// rand() is random number between 0 and 1
		//remainder of deck of size and if program is running Texas hold'em let size = 16 if not 0, and minus of that
		//minus limit to decrease size of array
		//and plus limit all of that to exclude the card we have already used
		//and swap the cards
		randnum = rand() % (52 - size - limit) + limit;
		temp = card[randnum];
		card[randnum] = card[u];
		card[u] = temp;
		++limit;
	}

}
void PrintCards(struct card countcard) {
	//intiallize variables
	const char *v, *s;
	int i = 0;

	switch (countcard.Value) { //switch enum value name to string
	case Deuce: v = "Deuce"; break;
	case three: v = "three"; break;
	case four: v = "four"; break;
	case five: v = "five"; break;
	case six: v = "six"; break;
	case seven: v = "seven"; break;
	case eight: v = "eight"; break;
	case nine: v = "nine"; break;
	case ten: v = "ten"; break;
	case jack: v = "jack"; break;
	case queen: v = "queen"; break;
	case king: v = "king"; break;
	case ace: v = "ace"; break;
	default: v = "";
	}
	switch (countcard.Suit) {//switch enum suit name to string
	case Clubs: s = "Clubs"; break;
	case Diamonds: s = "Diamonds"; break;
	case Hearts: s = "Hearts"; break;
	case Spades: s = "Spades"; break;
	default: s = "";
	}
	//use switch to print out enums and sometimes we only need to print out value or value and suit so use if else
	if (s == "")
		printf("%s", v);
	else
		printf("%s of %s", v, s);//print suit and value name as string

}
void RankPlayers(struct Player* player, int to10) {
	int c = 0, d = 0, n = to10;
	struct Player swap;
	//use bubble sort to sort by rank of cards and value of that rank,
	// to do that add card rank and value because they can be numeric value
	// so highest total of that will be highest rank player
	//and bubble sort will sort low to high rank value
	for (c = 0; c < n - 1; c++)
	{
		for (d = 0; d < n - c - 1; d++)
		{
			if ((player[d].CardRank + player[d].highestvalue.Value) >(player[d + 1].CardRank + player[d + 1].highestvalue.Value))
			{
				swap = player[d];
				player[d] = player[d + 1];
				player[d + 1] = swap;
			}
		}
	}
	//lastly print out top rank of the player
	printf("\nPlayer %d with a ", player[to10 - 1].playernum);
	PrintRank(player[to10 - 1].CardRank);
	printf("("); PrintCards(player[to10 - 1].highestvalue); printf(")");
	printf("\n");

}
