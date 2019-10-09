enum suit { Clubs = 0, Diamonds, Hearts, Spades };
enum value { Deuce = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
enum rank { nothing=0,ePair,eTwoPair,eThreepair,eStraight,eFlush,eFullhouse, eFourpair,eStraightFlush,eRoyalFlush};

struct card {
	enum value Value;
	enum suit Suit;
};
struct Player {
	struct card PlayerCards[5];
	enum rank CardRank;
	int playernum;
	struct card highestvalue;
};

void TwoPair(struct Player* valueCheck);
void PrintCards(struct card card);
void Swap(struct card *card, int size);
void RankDeck(struct Player* deck);
void PrintRank(enum rank player);
void onePair(struct Player* valueCheck);
void threeOfaKind(struct Player* valueCheck);
void straight(struct Player* valueCheck);
void flush(struct Player* valueCheck);
void fullHouse(struct Player* valueCheck);
void fourOfaKind(struct Player* valueCheck);
void straightFlush(struct Player* valueCheck);
void royalFlush(struct Player* valueCheck);
void RankPlayers(struct Player* player, int to10);