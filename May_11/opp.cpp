#include <iostream>

enum Face {
  ACE = 1,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
};

enum Suit {
  HEARTS,
  DIAMONDS,
  CLUBS,
  SPADES
};

Face GetFaceType(std::string face) {
  if (face == "A") {
    return ACE;
  }
  if (face == "2") {
    return TWO;
  }
  if (face == "3") {
    return THREE;
  }
  if (face == "4") {
    return FOUR;
  }
  if (face == "5") {
    return FIVE;
  }
  if (face == "6") {
    return SIX;
  }
  if (face == "7") {
    return SEVEN;
  }
  if (face == "8") {
    return EIGHT;
  }
  if (face == "9") {
    return NINE;
  }
  if (face == "10") {
    return TEN;
  }
  if (face == "J") {
    return JACK;
  }
  if (face == "Q") {
    return QUEEN;
  }
  if (face == "K") {
    return KING;
  }
  return ACE;
}

Suit GetSuitType(std::string suit) {
  if (suit == "H") {
    return HEARTS;
  }
  if (suit == "D") {
    return DIAMONDS;
  }
  if (suit == "C") {
    return CLUBS;
  }
  if (suit == "S") {
    return SPADES;
  }
  return HEARTS;
}


std::string GetFaceString(Face face) {
  switch (face) {
    case ACE:
      return "Ace";
    case TWO:
      return "Deuce";
    case THREE:
      return "Three";
    case FOUR:
      return "Four";
    case FIVE:
      return "Five";
    case SIX:
      return "Six";
    case SEVEN:
      return "Seven";
    case EIGHT:
      return "Eight";
    case NINE:
      return "Nine";
    case TEN:
      return "Ten";
    case JACK:
      return "Jack";
    case QUEEN:
      return "Queen";
    case KING:
      return "King";
    default:
      return "Ace";
  }
}

std::string GetSuitString(Suit suit) {
  switch (suit) {
    case HEARTS:
      return "Hearts";
    case DIAMONDS:
      return "Diamonds";
    case CLUBS:
      return "Clubs";
    case SPADES:
      return "Spades";
    default:
      return "Hearts";
  }
}


class Card {
 private:
  Face face;
  Suit suit;
 public:
  Card() {
  }
  explicit Card(Face face, Suit suit) {
    this->face = face;
    this->suit = suit;
  }
  Suit GetSuit() {
    return suit;
  }
  Face GetFace() {
    return face;
  }
  void Print(bool changeline) {
    std::string card = GetFaceString(face) + " of " +GetSuitString(suit);
    std::cout << card;
    std::cout << (changeline ? "\n" : "");
  }

  /**
   * see if 'this card' is bigger than 'card'
   * compare faces first ; if faces are equal, then compare suits
   * @param card the card that needs to compare with
   * @return     true if 'this card' is bigger than the input 'card'. Return false otherwise
   */
  bool BiggerThan(Card card);
};

class Hand {
 private:
  Card cards[5];
 public:
  Hand() {
  }
  explicit Hand(Card cards[]) {
    for (int i = 0; i < 5; i++) {
      this->cards[i] = cards[i];
    }
  }
  void Print() {
    for (int i = 0; i < 5; i++) {
      cards[i].Print(true);
    }
  }
};


int main() {
  Hand hand;
  Card cards[5];
  for (int i = 0; i < 5; i++) {
    std::string face, suit;
    std::cin >> suit >> face;
    cards[i] = Card(GetFaceType(face), GetSuitType(suit));
  }
  hand = Hand(cards);
  hand.Print();
  return 0;
}

bool Card::BiggerThan(Card card) {
  if (face > card.GetFace()) {
    return true;
  } else if (face == card.GetFace()) {
    return suit > card.GetSuit();
  }
  return false;
}