#include <iostream>

enum Suit {
  SPADES = 832, 
  HEARTS = 574, 
  CLUBS = 400,
  DIAMONDS = 300
};

enum Face {
  DEUCE = 1,
  THREE = 2,
  FOUR = 3,
  FIVE = 4,
  SIX = 5,
  SEVEN = 6,
  EIGHT = 7,
  NINE = 8,
  TEN = 9,
  JACK = 10,
  QUEEN = 11,
  KING = 12,
  ACE = 13
};

Face GetFaceType(std::string face) {
  if (face == "A") {
    return ACE;
  }
  if (face == "2") {
    return DEUCE;
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
    case DEUCE:
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
    std::string card = GetFaceString(face) + " of " +GetSuitString(suit) + ".";
    std::cout << card;
    std::cout << (changeline ? "\n" : "");
  }

  /**
   * see if 'this card' is bigger than 'card'
   * compare faces first ; if faces are equal, then compare suits
   * @param card the card that needs to compare with
   * @return     true if 'this card' is bigger than the input 'card'. Return false otherwise
   */
  bool BiggerThan(Card card, bool is_special);
};

class Hand {
 private:
  Card cards[5];
  bool is_special;
 public:
  Hand() {
  }
  explicit Hand(Card cards[]) {
    for (int i = 0; i < 5; i++) {
      this->cards[i] = cards[i];
    }
  }
  bool IsSpecial() {
    return is_special;
  }
  void SetSpecial(bool is_special) {
    this->is_special = is_special;
  }
  void Print() {
    for (int i = 0; i < 5; i++) {
      cards[i].Print(true);
    }
  }
  Card GetCard(int index) {
    return cards[index];
  }
  void FindLargest(Card *maxcard);

  bool IsFlush(Card *maxcard);

  bool IsStraight(Card *maxcard);

  bool IsStraightFlush(Card *largest);
};

bool InputHand(Hand &hand) {
  int count = 0;
  int sum = 0;
  Card cards[5];
  std::string face, suit;
  while (std::cin >> suit >> face) {
    cards[count] = Card(GetFaceType(face), GetSuitType(suit));
    sum += cards[count].GetFace();
    count++;
    if (count == 5) {
      hand = Hand(cards);
      if (sum == 23) { 
        hand.SetSpecial(true);
      } else {
        hand.SetSpecial(false);
      }
      return true;
    }
  }
  return false;
}

int main() {
  Hand hand;
  if (InputHand(hand)) {
    Card maxcard;
    bool is_straightflush = hand.IsStraightFlush(&maxcard);
    if (is_straightflush) {
      // std::cout << "Flush!" << std::endl;
      maxcard.Print(true);
    } else {
      std::cout << "Not a straight flush." << std::endl;
    }
    
  } else {
    std::cout << "Input Error!" << std::endl;
  }
  return 0;
}

bool Card::BiggerThan(Card card, bool is_special) {
  int rank_face[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  if (is_special) {
    rank_face[ACE] = 0;
  }
  if (rank_face[face] > rank_face[card.GetFace()]) {
    return true;
  } else if (face == card.GetFace()) {
    return suit > card.GetSuit();
  }
  return false;
}

void Hand::FindLargest(Card *maxcard) {
  Card largest = cards[0];
  for (int i = 1; i < 5; i++) {
    if (cards[i].BiggerThan(largest, is_special)) {
      largest = cards[i];
    }
  }
  *maxcard = largest;
}

bool Hand::IsFlush(Card *maxcard) {
  bool is_flush = true;
  for (int i = 1; i < 5; i++) {
    if (cards[i].GetSuit() != cards[0].GetSuit()) {
      is_flush = false;
      break;
    }
  }
  if (is_flush) {
    FindLargest(maxcard);
  }
  return is_flush;
}

bool Hand::IsStraight(Card *maxcard) {
  bool is_straight = false;
  int arr_card[15] = {0};
  int max = 0;
  for (int i = 0; i < 5; i++) {
    arr_card[cards[i].GetFace()]++;
    if (cards[i].GetFace() == ACE) {
      arr_card[0]++;
    }
    if (cards[i].GetFace() > max) {
      max = cards[i].GetFace();
    }
  }

  int count = 0;
  for (int i = max; i > max - 5; i--) {
    if (arr_card[i] == 1) {
      count++;
    }
  }
  if (count == 5) {
    is_straight = true;
  } else if (arr_card[0] == 1 && arr_card[1] == 1 && arr_card[2] == 1 &&
             arr_card[3] == 1 && arr_card[4] == 1) {
    is_straight = true;
  }

  if (is_straight) {
    FindLargest(maxcard);
  }
  return is_straight;
}

bool Hand::IsStraightFlush(Card *largest) {
  bool is_straight_flush = false;
  Card temp;
  bool is_flush = IsFlush(&temp);
  bool is_straight = IsStraight(&temp);
  if (is_flush && is_straight) {
    is_straight_flush = true;
    *largest = temp;
  }
  return is_straight_flush;
}