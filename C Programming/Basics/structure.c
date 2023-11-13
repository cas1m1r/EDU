#include <stdio.h>

typedef struct Card{
	int rank;
	char *suit;
}Card;

void showCard(struct Card c){
	if(c.rank < 11){
		printf("%d%s ", c.rank, c.suit);
	}else{
		switch(c.rank){
			case (11):
				printf("J%s ", c.suit);
				break;
			case (12):
				printf("Q%s ", c.suit);
				break;
			case (13):
				printf("K%s ",  c.suit);
				break;
			case (14):
				printf("A%s ", c.suit);
				break;
		}
	}
}

void main(){

	Card Deck[52];
	char* suits[4] = {"H", "C", "D", "S"};
	for(int i=2; i<=14; i++){
		for(int j=0; j < 4; j++){
			Card c;
			c.rank = i;
			c.suit = suits[j];
			showCard(c);
		}
		printf("\n");
	}

}