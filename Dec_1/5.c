/* hidden code */
int Order(Face face) {
  switch (face) {
    case ACE:
      return 14;
    case DEUCE:
      return 2;
    case THREE:
      return 3;
    case FOUR:
      return 4;
    case FIVE:
      return 5;
    case SIX:
      return 6;
    case SEVEN:
      return 7;
    case EIGHT:
      return 8;
    case NINE:
      return 9;
    case TEN:
      return 10;
    case JACK:
      return 11;
    case QUEEN:
      return 12;
    case KING:
      return 13;
    default:
      return -1; // Return -1 to indicate an invalid face value
  }
}

int OrderSuit(Suit suit) {
  if (suit == DIAMONDS) return 1;
  else return suit;
} 

bool BiggerThan(Card card1, Card card2) {
  int face1 = Order(card1.face);
  int face2 = Order(card2.face);

  if (face1 > face2) {
    return true;
  } else if (face1 < face2) {
    return false;
  } else {
    if (OrderSuit(card1.suit) > OrderSuit(card2.suit)) {
      return true;
    } else {
      return false;
    }
  }
}