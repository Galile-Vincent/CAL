/* copyright cycuice */

/** print the "suit" value and "face" value of a card ;
  * e.g., if 'suit' is SPADES and 'face' is EIGHT
  *       then print "Eight of Spades"
  * e.g., if 'suit' is CLUBS and 'face' is THREE
  *       then print "Three of Clubs"
  *       see declaration of Suit and Face for details
  * @param card a card with designated suit and face 
  */
void PrintCard(Card card) {
  const char* suits[] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  const char* faces[] = {
      "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven",
      "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

  int suitindex = -1, faceindex = -1;

  switch (card.suit) {
    case SPADES:
      suitindex = 0;
      break;
    case HEARTS:
      suitindex = 1;
      break;
    case DIAMONDS:
      suitindex = 2;
      break;
    case CLUBS:
      suitindex = 3;
      break;
  }

  switch (card.face) {
    case ACE:
      faceindex = 0;
      break;
    case DEUCE:
      faceindex = 1;
      break;
    case THREE:
      faceindex = 2;
      break;
    case FOUR:
      faceindex = 3;
      break;
    case FIVE:
      faceindex = 4;
      break;
    case SIX:
      faceindex = 5;
      break;
    case SEVEN:
      faceindex = 6;
      break;
    case EIGHT:
      faceindex = 7;
      break;
    case NINE:
      faceindex = 8;
      break;
    case TEN:
      faceindex = 9;
      break;
    case JACK:
      faceindex = 10;
      break;
    case QUEEN:
      faceindex = 11;
      break;
    case KING:
      faceindex = 12;
      break;
  }

  printf("%s of %s\n", faces[faceindex], suits[suitindex]);
}
