#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

// My name: Ron Yakov
//ID number: 314710922

#define MAX_NAME_LEN 20
#define SIZE 14

struct statistic
{
	int index;
	int amount;
}; typedef struct statistic STATISTIC;

struct Card
{
	char typeOfCard; //r(regular) p(plus) s(stop) d(change direction) t(taki) c(change color)
	char color;
	int num;
}; typedef struct Card CARD;

struct Player
{
	char name[MAX_NAME_LEN];
	CARD* cards;
	int numOfCards;
	int spaceForCards;
}; typedef struct Player PLAYER;

void resetStatistic(STATISTIC stat[], int size);
void getArrOfCardsToPlayers(PLAYER players[], int size);
void printCard(CARD card);
void printPlayerCards(PLAYER player);
char getRandomColor();
void getRandomCard(CARD* empty, STATISTIC stat[]);
void getRandomStarterCard(CARD* empty, STATISTIC stat[]);
void getPlayerInfo(PLAYER players[], int size, STATISTIC stat[]);
CARD* myRealloc(CARD cards[], int size, int newSize);
void addCardToPlayer(PLAYER* player, STATISTIC stat[]);
void swapCards(CARD cards[], int a, int b);
bool playRegularCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard);
void playColorCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard);
bool playDirctionAndStopCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard);
bool playPlusCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard);
void game(PLAYER players[], int size, CARD upperCard, STATISTIC stat[]);
void mergeSort(STATISTIC stat[], int size);
STATISTIC* merge(STATISTIC stat1[], int size1, STATISTIC stat2[], int size2);
void copyArr(STATISTIC dest[], STATISTIC src[], int size);
void printStatistic(STATISTIC stat[], int size);

void main()
{
	srand(time(NULL));
	PLAYER* players;
	int numOfPlayers, i;
	CARD upperCard;
	STATISTIC stat[SIZE];

	printf("************  Welcome to TAKI game !!! ***********\n");
	printf("Please enter the number of players:\n");
	scanf("%d", &numOfPlayers);

	players = (PLAYER*)malloc(numOfPlayers * sizeof(PLAYER));
	if (players == NULL)
	{
		printf("ERROR! Memory allocation failed !!!\n");
		exit(1);
	}

	resetStatistic(stat, SIZE);

	getArrOfCardsToPlayers(players, numOfPlayers);

	getPlayerInfo(players, numOfPlayers, stat);

	getRandomStarterCard(&upperCard,stat);

	game(players, numOfPlayers, upperCard, stat);

	for (i = 0; i < numOfPlayers; i++)
		free(players[i].cards);

	free(players);

	mergeSort(stat, SIZE);

	printStatistic(stat, SIZE);
}

//This function gets statistic array and its size and reset it
void resetStatistic(STATISTIC stat[], int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		stat[i].amount = 0;
		stat[i].index = i;
	}
}

//This function gets an array of players and its size, and give a memory space
// of 4 cards to each player. 
void getArrOfCardsToPlayers(PLAYER players[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		players[i].cards = (CARD*)malloc(4 * sizeof(CARD));

		if (players[i].cards == NULL)
		{
			printf("ERROR! Memory allocation failed !!!\n");
			exit(-1);
		}
	}
}

//This function gets a card and prints it
void printCard(CARD card)
{
	printf("*********\n");
	printf("*       *\n");

	switch (card.typeOfCard)
	{
	case 'r':
		printf("*   %d   *\n",card.num);
		printf("*   %c   *\n", card.color);
		break;

	case 'p':
		printf("*   +   *\n");
		printf("*   %c   *\n", card.color);
		break;

	case 's':
		printf("*  STOP *\n");
		printf("*   %c   *\n", card.color);
		break;

	case 'd':
		printf("*  <->  *\n");
		printf("*   %c   *\n", card.color);
		break;

	case 't':
		printf("*  TAKI *\n");
		printf("*   %c   *\n", card.color);
		break;

	case 'c':
		printf("* COLOR *\n");

		//if there is a color in the card
		if (card.color == 'R' || card.color == 'G' || card.color == 'Y' || card.color == 'B')
			printf("*   %c   *\n", card.color);
		else
			printf("*       *\n");
		break;
	}

	printf("*       *\n");
	printf("*********\n");
}

//This function gets a player and prints its cards
void printPlayerCards(PLAYER player)
{
	int i;
	for (i = 0; i < player.numOfCards; i++)
	{
		printf("Card #%d:\n", i + 1);
		printCard(player.cards[i]);
		printf("\n");
	}
}

//this function return a random color (R = red, B = blue, G = green, Y= yellow)
char getRandomColor()
{
	char res;
	int i;

	i = rand() % 4;

	switch (i)
	{
	case 0:
		res = 'R';
		break;

	case 1:
		res = 'B';
		break;

	case 2:
		res = 'G';
		break;

	case 3:
		res = 'Y';
		break;
	}

	return res;
}

//this function gets an empty card and statistic array, and fills the empty card with random values and the statistic in the right place
void getRandomCard(CARD *empty, STATISTIC stat[])
{
	CARD tmp;
	int typeOf;
	typeOf = rand() % 14;

	switch (typeOf)
	{
	case 0: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 1;
		tmp.color = getRandomColor();
		stat[0].amount++;
		break;

	case 1: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 2;
		tmp.color = getRandomColor();
		stat[1].amount++;
		break;

	case 2: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 3;
		tmp.color = getRandomColor();
		stat[2].amount++;
		break;

	case 3: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 4;
		tmp.color = getRandomColor();
		stat[3].amount++;
		break;

	case 4: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 5;
		tmp.color = getRandomColor();
		stat[4].amount++;
		break;

	case 5: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 6;
		tmp.color = getRandomColor();
		stat[5].amount++;
		break;

	case 6: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 7;
		tmp.color = getRandomColor();
		stat[6].amount++;
		break;

	case 7: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 8;
		tmp.color = getRandomColor();
		stat[7].amount++;
		break;

	case 8: //regular card
		tmp.typeOfCard = 'r';
		tmp.num = 9;
		tmp.color = getRandomColor();
		stat[8].amount++;
		break;

	case 9: //plus card
		tmp.typeOfCard = 'p';
		tmp.color = getRandomColor();
		stat[9].amount++;
		break;

	case 10: //stop card
		tmp.typeOfCard = 's';
		tmp.color = getRandomColor();
		stat[10].amount++;
		break;

	case 11: //change direction card
		tmp.typeOfCard = 'd';
		tmp.color = getRandomColor();
		stat[11].amount++;
		break;

	case 12: //taki card
		tmp.typeOfCard = 't';
		tmp.color = getRandomColor();
		stat[12].amount++;
		break;

	case 13: //change color card
		tmp.typeOfCard = 'c';
		stat[13].amount++;
		break;
	}

	*empty = tmp;
}

//this function gets an empty card and statistic array, and fills the empty card with random number and random color
//the function also fills the statistic in the right place
void getRandomStarterCard(CARD * empty, STATISTIC stat[])
{
	CARD temp;
	temp.typeOfCard = 'r';
	temp.color = getRandomColor();
	temp.num = (rand() % 9) + 1;

	switch (temp.num)
	{
	case 1:
		stat[0].amount++;
		break;
	case 2:
		stat[1].amount++;
		break;
	case 3:
		stat[2].amount++;
		break;
	case 4:
		stat[3].amount++;
		break;
	case 5:
		stat[4].amount++;
		break;
	case 6:
		stat[5].amount++;
		break;
	case 7:
		stat[6].amount++;
		break;
	case 8:
		stat[7].amount++;
		break;
	case 9:
		stat[8].amount++;
		break;

	}
	*empty = temp;
}

//This function gets an array of players and its size and statistic array, and gets for each player
//their name and 4 random cards.
void getPlayerInfo(PLAYER players[], int size, STATISTIC stat[])
{
	int i,j;

	for (i = 0; i < size; i++)
	{
		printf("Please enter the first name of player #%d:\n", i + 1);
		scanf("%s", players[i].name);

		for (j = 0; j < 4; j++)
		{
			getRandomCard(&players[i].cards[j], stat);
		}

		players[i].numOfCards = 4;
		players[i].spaceForCards = 4;
	}
}

//this function gets an array of cards, its size and a new bigger size. The function returns a new array
//of cards with the new size
CARD* myRealloc(CARD cards[], int size, int newSize)
{
	int i;
	CARD* newCards = (CARD*)malloc(newSize * sizeof(CARD));
	
	if (newCards == NULL) //check if memory allocation did not succeed 
	{
		printf("ERROR! Memory allocation failed !!!\n");
		exit(-1);
	}

	else
	{
		for (i = 0; i < size; i++)
			newCards[i] = cards[i];

		free(cards);
	}

	return newCards;
}

//this function gets a player information and statistic array, and adds one more random card to to the players hand
void addCardToPlayer(PLAYER* player, STATISTIC stat[])
{
	PLAYER tmp = *player;
	
	if (tmp.numOfCards == tmp.spaceForCards)
	{
		tmp.cards = myRealloc(tmp.cards, tmp.spaceForCards, 2 * tmp.spaceForCards);
		tmp.spaceForCards *= 2;
	}

	getRandomCard(&tmp.cards[tmp.numOfCards], stat);
	tmp.numOfCards += 1;

	*player = tmp;
}

//this function gets an array of cards and two indexes. The function swap between the two cards
//that place in the indexes in the array
void swapCards(CARD cards[], int a, int b)
{
	CARD tmp;
	tmp = cards[a];
	cards[a] = cards[b];
	cards[b] = tmp;
}

//this function gets a player information, the place of the chosen card in the array and the upper card in the deck
//the function checks if the player chose a legal card to play, and return true if he did or false if he didn't
bool playRegularCardTurn(PLAYER *player, int placeOfChosenCard, CARD *upperCard)
{
	bool res;
	PLAYER tmpPlayer = *player;
	CARD tmpUpCard = *upperCard;

	//if the number or color of the chosen card and the upper card match
	if ((tmpPlayer.cards[placeOfChosenCard].num == tmpUpCard.num) || (tmpPlayer.cards[placeOfChosenCard].color == tmpUpCard.color))
	{
		res = true;
		tmpUpCard = tmpPlayer.cards[placeOfChosenCard];
		swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, placeOfChosenCard);
		tmpPlayer.numOfCards -= 1;
	}
	else
	{
		res = false;
	}

	*player = tmpPlayer;
	*upperCard = tmpUpCard;
	return res;
}

//this function gets a player information, the place of the chosen card in the array and the upper card in the deck
//the function changes the color of the change color card to the choice the player wanted
void playColorCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard)
{
	int colorChois;
	PLAYER tmpPlayer = *player;
	CARD tmpUpCard = *upperCard;

	tmpUpCard = tmpPlayer.cards[placeOfChosenCard];
	swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, placeOfChosenCard);
	tmpPlayer.numOfCards -= 1;

	printf("Please enter your color choice:\n");
	printf("1 - Yellow\n2 - Red\n3 - Blue\n4 - Green\n");
	scanf("%d", &colorChois);
	while (colorChois>4||colorChois<1)
	{
		printf("Invalid color! Try again.\n");
		printf("1 - Yellow\n2 - Red\n3 - Blue\n4 - Green\n");
	}

	switch (colorChois)
	{
	case 1:
		tmpUpCard.color = 'Y';
		break;
	case 2:
		tmpUpCard.color = 'R';
		break;
	case 3:
		tmpUpCard.color = 'B';
		break;
	case 4:
		tmpUpCard.color = 'G';
		break;
	}


	*player = tmpPlayer;
	*upperCard = tmpUpCard;
}

//this function gets a player information, the place of the chosen card in the array and the upper card in the deck
//the function checks if the player chose a legal card to play, and return true if he did or false if he didn't
bool playDirctionAndStopCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard)
{
	bool res;
	PLAYER tmpPlayer = *player;
	CARD tmpUpCard = *upperCard;

	//if the color of the chosen card and the upper card match
	if (tmpPlayer.cards[placeOfChosenCard].color == tmpUpCard.color)
	{
		res = true;
		tmpUpCard = tmpPlayer.cards[placeOfChosenCard];
		swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, placeOfChosenCard);
		tmpPlayer.numOfCards -= 1;
	}
	else
	{
		res = false;
	}

	*player = tmpPlayer;
	*upperCard = tmpUpCard;
	return res;
}

//this function gets a player information, the place of the chosen card in the array and the upper card in the deck
//the function checks if the player chose a legal card to play, and return true if he did or false if he didn't
bool playPlusCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard)
{
	bool res;
	PLAYER tmpPlayer = *player;
	CARD tmpUpCard = *upperCard;

	//if the color or the type of the chosen card and the upper card match
	if (tmpPlayer.cards[placeOfChosenCard].color == tmpUpCard.color || tmpPlayer.cards[placeOfChosenCard].typeOfCard == tmpUpCard.typeOfCard)
	{
		res = true;
		tmpUpCard = tmpPlayer.cards[placeOfChosenCard];
		swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, placeOfChosenCard);
		tmpPlayer.numOfCards -= 1;
	}
	else
	{
		res = false;
	}

	*player = tmpPlayer;
	*upperCard = tmpUpCard;
	return res;
}

//this function gets a player information, the place of the chosen card in the array and the upper card in the deck
//the function checks if the player chose a legal card to play, and return true if he did or false if he didn't
//also the function play the hand of the taki card
bool playTakiCardTurn(PLAYER* player, int placeOfChosenCard, CARD* upperCard)
{
	bool res, endTakiTurn = true;
	int playerChoise;
	PLAYER tmpPlayer = *player;
	CARD tmpUpCard = *upperCard;

	//if the color of the chosen card and the upper card match
	if (tmpPlayer.cards[placeOfChosenCard].color == tmpUpCard.color)
	{
		res = true;
		endTakiTurn = false;
		tmpUpCard = tmpPlayer.cards[placeOfChosenCard];
		swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, placeOfChosenCard);
		tmpPlayer.numOfCards -= 1;
	}
	else
	{
		res = false;
	}

	while (endTakiTurn == false && tmpPlayer.numOfCards != 0)
	{
		printf("\nUpper card:\n");
		printCard(tmpUpCard);
		printf("\n%s's turn:\n\n", tmpPlayer.name);
		printPlayerCards(tmpPlayer);

		printf("Please enter 0 if you want to finish your turn\n");
		printf("or 1-%d if you want to put one of your cards in the middle:\n", tmpPlayer.numOfCards);
		scanf("%d", &playerChoise);

		while (playerChoise < 0 || playerChoise > tmpPlayer.numOfCards)
		{
			printf("Invalid choice! Try again.\n");
			printf("Please enter 0 if you want to finish your turn\n");
			printf("or 1-%d if you want to put one of your cards in the middle:\n", tmpPlayer.numOfCards);
			scanf("%d", &playerChoise);
		}


		while (tmpPlayer.cards[playerChoise - 1].color != tmpUpCard.color && playerChoise != 0)
		{
			printf("Invalid card! Try again.\n");
			printf("Please enter 0 if you want to finish your turn\n");
			printf("or 1-%d if you want to put one of your cards in the middle:\n", tmpPlayer.numOfCards);
			scanf("%d", &playerChoise);
		}

		if (playerChoise == 0)
			endTakiTurn = true;

		else
		{
			tmpUpCard = tmpPlayer.cards[playerChoise - 1];
			swapCards(tmpPlayer.cards, tmpPlayer.numOfCards - 1, playerChoise - 1);
			tmpPlayer.numOfCards -= 1;
		}


	}

	*player = tmpPlayer;
	*upperCard = tmpUpCard;
	return res;
}

//this function gets player array its size, the first card in the middle, and statistic array
//the function plays the game of taki, in the end says who won and update in the game the statistic array
void game(PLAYER players[], int size, CARD upperCard, STATISTIC stat[])
{
	int i = 0, direction = 1; //when direction < 0 the turns go backwords
	int playerChoise;
	bool noWinner = true, finishTurn, plusCardTurn;

	while (noWinner)
	{
		printf("\nUpper card:\n");
		printCard(upperCard);
		printf("\n%s's turn:\n\n", players[i].name);
		printPlayerCards(players[i]);

		
		finishTurn = false;
		while (finishTurn == false)
		{
			plusCardTurn = false;

			printf("Please enter 0 if you want to take a card from the deck\n");
			printf("or 1-%d if you want to put one of your cards in the middle:\n", players[i].numOfCards);
			scanf("%d", &playerChoise);

			if (playerChoise == 0)
			{
				addCardToPlayer(&players[i], stat);
				finishTurn = true;
			}
			else
			{
				switch (players[i].cards[playerChoise - 1].typeOfCard)
				{
				case 'r':
					finishTurn = playRegularCardTurn(&players[i], playerChoise - 1, &upperCard);
					break;
				
				case 'c':
				    playColorCardTurn(&players[i], playerChoise - 1, &upperCard);
					finishTurn = true;
					break;

				case 'd':
					finishTurn = playDirctionAndStopCardTurn(&players[i], playerChoise - 1, &upperCard);
					if (finishTurn)
						direction *= -1;
					break;

				case 's':
					finishTurn = playDirctionAndStopCardTurn(&players[i], playerChoise - 1, &upperCard);
					if (finishTurn)
					{
						if (direction == 1) //the direction is forwards
							if (i < size - 1)
								i++;
							else
								i = 0;

						else // the direction is backwards
							if (i > 0)
								i--;
							else
								i = size - 1;
					}
					break;

				case 'p':
					finishTurn = playPlusCardTurn(&players[i], playerChoise - 1, &upperCard);
					plusCardTurn = true;
					break;

				case 't':
					finishTurn = playTakiCardTurn(&players[i], playerChoise - 1, &upperCard);
					if (finishTurn)
					{
						if (upperCard.typeOfCard == 'p')
							plusCardTurn = true;

						if (upperCard.typeOfCard == 's')
						{
							if (direction == 1) //the direction is forwards
								if (i < size - 1)
									i++;
								else
									i = 0;

							else // the direction is backwards
								if (i > 0)
									i--;
								else
									i = size - 1;
						}
					}
					break;
				}
			}


			if (players[i].numOfCards == 0 && upperCard.typeOfCard != 'p')
				noWinner = false;

			else if (players[i].numOfCards == 0 && upperCard.typeOfCard == 'p')
			{
				finishTurn = true;
				addCardToPlayer(&players[i], stat);

				if (direction == 1) //the direction is forwards
					if (i < size - 1)
						i++;
					else
						i = 0;

				else // the direction is backwards
					if (i > 0)
						i--;
					else
						i = size - 1;
			}


			else if (finishTurn == false)
				printf("Invalid card! Try again.\n");

			else if (finishTurn == true && plusCardTurn == false)
			{
				if (direction == 1) //the direction is forwards
					if (i < size - 1)
						i++;
					else
						i = 0;
				
				else // the direction is backwards
					if (i > 0)
						i--;
					else
						i = size - 1;
			}

		}
	}

	printf("\nThe winner is... %s!\n\n", players[i].name);
}

//a function that gets a statistic array and its size and sort it
void mergeSort(STATISTIC stat[], int size)
{
	STATISTIC* tmpArr = NULL;
	if (size <= 1)
		return;

	mergeSort(stat, size / 2);
	mergeSort(stat + size / 2, size - size / 2);
	tmpArr = merge(stat, size / 2, stat + size / 2, size - size / 2);
	if (tmpArr)
	{
		copyArr(stat, tmpArr, size);
		free(tmpArr);
	}

	else
	{
		printf("ERROR! Memory allocation failed !!!\n");
		exit(1);
	}
}

//a function that gets two statistic arrays and their sizes and return a sorted statistic array that its the combination
//between the two
STATISTIC* merge(STATISTIC stat1[], int size1, STATISTIC stat2[], int size2)
{
	int ind1, ind2, resInd;
	STATISTIC* res = (STATISTIC*)malloc((size1 + size2) * sizeof(STATISTIC));

	if (res)
	{
		ind1 = ind2 = resInd = 0;

		while ((ind1 < size1) && (ind2 < size2))
		{
			if (stat1[ind1].amount > stat2[ind2].amount)
			{
				res[resInd] = stat1[ind1];
				ind1++;
			}
			else
			{
				res[resInd] = stat2[ind2];
				ind2++;
			}
			resInd++;
		}

		while (ind1 < size1)
		{
			res[resInd] = stat1[ind1];
			ind1++;
			resInd++;
		}
		while (ind2 < size2)
		{
			res[resInd] = stat2[ind2];
			ind2++;
			resInd++;
		}
	}

	return res;
}

//a function that copies the src array into the dest array
void copyArr(STATISTIC dest[], STATISTIC src[], int size)
{
	int i;

	for (i = 0; i < size; i++)
		dest[i] = src[i];
}

//a function that gets the statistics of the game and prints them on the screen
void printStatistic(STATISTIC stat[], int size)
{
	int i;
	printf("************ Game Statistics ************\n");
	printf("Card # | Frequency\n");
	printf("__________________\n");
	for (i = 0; i < size; i++)
	{
		switch (stat[i].index)
		{
		case 0:
			printf("   1   |%4d\n", stat[i].amount);
			break;
		case 1:
			printf("   2   |%4d\n", stat[i].amount);
			break;
		case 2:
			printf("   3   |%4d\n", stat[i].amount);
			break;
		case 3:
			printf("   4   |%4d\n", stat[i].amount);
			break;
		case 4:
			printf("   5   |%4d\n", stat[i].amount);
			break;
		case 5:
			printf("   6   |%4d\n", stat[i].amount);
			break;
		case 6:
			printf("   7   |%4d\n", stat[i].amount);
			break;
		case 7:
			printf("   8   |%4d\n", stat[i].amount);
			break;
		case 8:
			printf("   9   |%4d\n", stat[i].amount);
			break;
		case 9:
			printf("   +   |%4d\n", stat[i].amount);
			break;
		case 10: 
			printf(" STOP  |%4d\n", stat[i].amount);
			break;
		case 11:
			printf("  <->  |%4d\n", stat[i].amount);
			break;
		case 12:
			printf(" TAKI  |%4d\n", stat[i].amount);
			break;
		case 13:
			printf(" COLOR |%4d\n", stat[i].amount);
			break;
		}
	}
	printf("\n");
}