#include <iostream>

enum Type {
  STRAIGHT_FLUSH = 20,
  FOUR_OF_KIND = 19,
  FULL_HOUSE = 18,
  FLUSH = 17,
  STRAIGHT = 16,
  THREE_OF_KIND = 15,
  TWO_PAIR = 14,
  ONE_PAIR = 13,
  ZLICH = 12
};

enum Suit {
  SPADES = 832, 
  HEARTS = 574, 
  CLUBS = 400,
  DIAMONDS = 300,
  DEFAULT_Suit = -1
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
  ACE = 13,
  DEFAULT_Face = -1
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

  return DEFAULT_Face;
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
  return DEFAULT_Suit;
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

std::string GetCardType_Upper(Type type) {
  switch (type) {
    case STRAIGHT_FLUSH:
      return "Straight flush";
    case FOUR_OF_KIND:
      return "Four of a kind";
    case FULL_HOUSE:
      return "Full house";
    case FLUSH:
      return "Flush";
    case STRAIGHT:
      return "Straight";
    case THREE_OF_KIND:
      return "Three of a kind";
    case TWO_PAIR:
      return "Two pairs";
    case ONE_PAIR:
      return "One pair";
    default:
      return "Zilch";
  }
}

std::string GetCardType_Lower(Type type) {
  switch (type) {
    case STRAIGHT_FLUSH:
      return "straight flush";
    case FOUR_OF_KIND:
      return "four of a kind";
    case FULL_HOUSE:
      return "full house";
    case FLUSH:
      return "flush";
    case STRAIGHT:
      return "straight";
    case THREE_OF_KIND:
      return "three of a kind";
    case TWO_PAIR:
      return "two pairs";
    case ONE_PAIR:
      return "one pair";
    default:
      return "zilch";
  }
}

class Card {
 private:
  Face face;
  Suit suit;
 public:
  Card() {
    suit = DEFAULT_Suit;
    face = DEFAULT_Face;
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
  void Print(Card second) {
    std::string card = GetFaceString(face) + " of " +GetSuitString(suit) + ",";
    std::cout << card << std::endl;
    std::string card2 = GetFaceString(second.GetFace()) + " of " + 
        GetSuitString(second.GetSuit()) + ".";
    std::cout << card2 << std::endl;
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
  Card largest;
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

  // For four of kind and three of kind
  void FindLargest(Card *maxcard, Face face);

  bool IsFlush(Card *maxcard);

  bool IsStraight(Card *maxcard);

  bool IsStraightFlush(Card *largest);

  bool IsFourOfKind(Card *largest);

  bool IsThreeOfKind(Card *largest);

  bool HasOnePair(Card excluded_card, Card *largest);

  bool IsTwoPair(Card *largest1, Card *largest2);

  bool IsFullHouse(Card *largest);

  Type IninialHand();

  Card GetLargest() {
    return largest;
  }
};

class Player {
 private:
  Hand hand;
  Type type;
 public:
  Player() {
  }
  explicit Player(Hand hand) {
    this->hand = hand;
  }
  Hand GetHand() {
    return hand;
  }
  bool InputHand();

  Type GetType() {
    return type;
  }
};

void Play(Player p1, Player p2) {
  Type type1 = p1.GetType();
  Type type2 = p2.GetType();
  bool win = false;

  if (type1 > type2) {
    win = true;
  } else if (type1 == type2) {
    if (type1 == TWO_PAIR) {
      Card p1_high, p1_low, p2_high, p2_low;
      p1.GetHand().IsTwoPair(&p1_high, &p1_low);
      p2.GetHand().IsTwoPair(&p2_high, &p2_low);
      
      // Compare higher pairs first
      if (p1_high.GetFace() > p2_high.GetFace()) {
        win = true;
      } else if (p1_high.GetFace() == p2_high.GetFace()) {
        // If higher pairs are equal, compare lower pairs
        if (p1_low.GetFace() > p2_low.GetFace()) {
          win = true;
        } else if (p1_low.GetFace() == p2_low.GetFace()) {
          // If both pairs are equal, compare suit of higher pair
          win = p1_high.GetSuit() > p2_high.GetSuit();
        }
      }
    } else {
      Card card1 = p1.GetHand().GetLargest();
      Card card2 = p2.GetHand().GetLargest();
      bool is_special = p1.GetHand().IsSpecial() && p2.GetHand().IsSpecial();
      is_special = is_special && (type1 == STRAIGHT && type2 == STRAIGHT);
      if (card1.BiggerThan(card2, is_special)) {
        win = true;
      }
    }
  }
  std::string player1 = GetCardType_Upper(type1) + " (";
  std::string player2 = GetCardType_Lower(type2) + " (";
  if (type1 == TWO_PAIR) {
    Card card1;
    Card card2;
    p1.GetHand().IsTwoPair(&card1, &card2);
    player1 += GetFaceString(card1.GetFace()) + " of " +
        GetSuitString(card1.GetSuit()) + " and " +
        GetFaceString(card2.GetFace()) + " of " +
        GetSuitString(card2.GetSuit()) + ")";
  } else {
    player1 += GetFaceString(p1.GetHand().GetLargest().GetFace()) + " of " +
        GetSuitString(p1.GetHand().GetLargest().GetSuit()) + ")";
  }
  if (type2 == TWO_PAIR) {
    Card card1;
    Card card2;
    p2.GetHand().IsTwoPair(&card1, &card2);
    player2 += GetFaceString(card1.GetFace()) + " of " +
        GetSuitString(card1.GetSuit()) + " and " +
        GetFaceString(card2.GetFace()) + " of " +
        GetSuitString(card2.GetSuit()) + ")";
  } else {
    player2 += GetFaceString(p2.GetHand().GetLargest().GetFace()) + " of " +
        GetSuitString(p2.GetHand().GetLargest().GetSuit()) + ")";
  }
  if (p1.GetType() == FULL_HOUSE && p2.GetType() == FULL_HOUSE) {
    Card card1;
    Card card2;
    p1.GetHand().IsThreeOfKind(&card1);
    p2.GetHand().IsThreeOfKind(&card2);
    if (card1.BiggerThan(card2, false)) {
      win = true;
    } else {
      win = false;
    }
  }

  std::string result = win ? " wins over " : " loses to ";
  std::cout << player1 << result << player2 << ".";
}

int main() {
  Player p1, p2;
  if (p1.InputHand()) {
    if (p2.InputHand()) {
      Play(p1, p2);
    } else {  // second input set not okay
      std::cout << "Input Error in second hand of cards!\n";
    }
  } else {  // first input set not okay
    std::cout << "Input Error in first hand of cards!\n";
  }
  return 0;
}

bool Player::InputHand() {
  int count = 0;
  int sum = 0;
  Card cards[5];
  std::string face, suit;
  while (std::cin >> suit) {
    if (suit == "-1") {
      break;
    }
    std::cin >> face;
    cards[count] = Card(GetFaceType(face), GetSuitType(suit));
    sum += cards[count].GetFace();
    count++;
  }
  if (count == 5) {
    hand = Hand(cards);
    if (sum == 23) { 
      hand.SetSpecial(true);
    } else {
      hand.SetSpecial(false);
    }
    type = hand.IninialHand();
    return true;
  }
  return false;
}

Type Hand::IninialHand() {
  Card maxcard;
  bool is_straightflush = IsStraightFlush(&maxcard);
  if (is_straightflush) {
    largest = maxcard;
    return STRAIGHT_FLUSH;
  }
  bool is_four = IsFourOfKind(&maxcard);
  if (is_four) {
    largest = maxcard;
    return FOUR_OF_KIND;
  }
  bool is_fullhouse = IsFullHouse(&maxcard);
  if (is_fullhouse) {
    largest = maxcard;
    return FULL_HOUSE;
  }
  bool is_flush = IsFlush(&maxcard);
  if (is_flush) {
    largest = maxcard;
    return FLUSH;
  }
  bool is_straight = IsStraight(&maxcard);
  if (is_straight) {
    largest = maxcard;
    return STRAIGHT;
  }
  bool is_three = IsThreeOfKind(&maxcard);
  if (is_three) {
    largest = maxcard;
    return THREE_OF_KIND;
  }
  Card largest1, largest2;
  bool is_two_pair = IsTwoPair(&largest1, &largest2);
  if (is_two_pair) {
    largest = largest1;
    return TWO_PAIR;
  }
  bool is_pair = HasOnePair(Card(), &largest1);
  if (is_pair) {
    largest = largest1;
    return ONE_PAIR;
  }
  FindLargest(&largest);
  return ZLICH;
}

bool Hand::IsFullHouse(Card *largest) {
  int arr_card[15] = {0};
  for (int i = 0; i < 5; i++) {
    arr_card[cards[i].GetFace()]++;
  }
  bool has_three = false, has_pair = false;
  Face three_face = DEFAULT_Face;
  for (int i = 1; i <= 13; i++) {
    if (arr_card[i] == 3) {
      has_three = true;
      three_face = Face(i);
    } else if (arr_card[i] == 2) {
      has_pair = true;
    }
  }
  if (has_three && has_pair) {
    FindLargest(largest, three_face); // Largest card from three-of-a-kind
    return true;
  }
  return false;
}

bool Hand::IsTwoPair(Card *largest1, Card *largest2) {
  Card firstpair;
  if (!HasOnePair(Card(), &firstpair)) {
    return false;
  }
  Card secondpair;
  if (!HasOnePair(firstpair, &secondpair)) {
    return false;
  }

  bool is_bigger = firstpair.BiggerThan(secondpair, false);
  if (is_bigger) {
    *largest1 = firstpair;
    *largest2 = secondpair;
  } else {
    *largest1 = secondpair;
    *largest2 = firstpair;
  }
  return true;
}

bool Hand::HasOnePair(Card excluded_card, Card *largest) {
  int arr_card[15] = {0};
  for (int i = 0; i < 5; i++) {
    arr_card[cards[i].GetFace()]++;
  }
  if (excluded_card.GetFace() != DEFAULT_Face) {
    arr_card[excluded_card.GetFace()]--;
  }
  for (int i = 0; i < 15; i++) {
    if (arr_card[i] == 2) {
      FindLargest(largest, Face(i));
      return true;
    }
  }
  return false;
}

bool Hand::IsThreeOfKind(Card *maxcard) {
  int arr_card[15] = {0};
  for (int i = 0; i < 5; i++) {
    arr_card[cards[i].GetFace()]++;
  }
  for (int i = 0; i < 15; i++) {
    if (arr_card[i] == 3) {
      FindLargest(maxcard, Face(i));
      return true;
    }
  }
  return false;
}

bool Hand::IsFourOfKind(Card *maxcard) {
  int arr_card[15] = {0};
  for (int i = 0; i < 5; i++) {
    arr_card[cards[i].GetFace()]++;
  }
  for (int i = 0; i < 15; i++) {
    if (arr_card[i] == 4) {
      FindLargest(maxcard, Face(i));
      return true;
    }
  }
  return false;
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

// For the Four Of A kind
void Hand::FindLargest(Card *maxcard, Face face) {
  Card largest = cards[0];
  for (int i = 1; i < 5; i++) {
    if (cards[i].GetFace() == face) {
      largest = cards[i];
      break;
    }
  }
  for (int i = 0; i < 5; i++) {
    if (cards[i].GetFace() == face && cards[i].BiggerThan(largest, false)) {
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
