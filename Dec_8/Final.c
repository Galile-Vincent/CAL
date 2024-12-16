#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
typedef enum Suit {
  SPADES = 832,
  HEARTS = 574,
  DIAMONDS = 456,
  CLUBS = 192
} Suit;

typedef enum Face {
  ACE,
  DEUCE,
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
} Face;

typedef struct Card {
  Suit suit;
  Face face;
} Card;

typedef Card Hand[5];

bool Equal(Card card1, Card card2) {
  return card1.face == card2.face;
}

void PrintCard(Card card);
bool InputHand(Hand hand);
void PrintHand(Hand hand);
bool BiggerThan(Card card1, Card card2);
Card FindLargest(Hand hand);
bool IsFlush(Hand hand);
bool IsStraight(Hand hand);
bool IsStraightFlush(Hand hand);
bool IsFourOfAKind(Hand hand);
bool HasThreeOfAKind(Hand hand);
bool HasOnePair(Hand hand, bool exclude_a_card, Card excluded_card);
bool IsTwoPairs(Hand hand);
bool IsOnePairs(Hand hand);
bool IsFullHouse(Hand hand);

void GetTextType(int rank, char arr[50]) {
  switch (rank) {
    case 10:
      strcpy(arr, "full house");
      break;
    case 9:
      strcpy(arr, "straight flush");
      break;
    case 8:
      strcpy(arr, "four of a kind");
      break;
    case 7:
      strcpy(arr, "full house");
      break;
    case 6:
      strcpy(arr, "flush");
      break;
    case 5:
      strcpy(arr, "straight");
      break;
    case 4:
      strcpy(arr, "three of a kind");
      break;
    case 3:
      strcpy(arr, "two pairs");
      break;
    case 2:
      strcpy(arr, "one pair");
      break;
    case 1:
      strcpy(arr, "zilch");
      break;
    default:
      strcpy(arr, "Unknown Type");
      break;
  }
}

int GetHandRank(Hand hand) {
  if (IsFullHouse(hand)) return 10;
  if (IsStraightFlush(hand)) return 9;
  if (IsFourOfAKind(hand)) return 8;
  if (IsFullHouse(hand)) return 7;
  if (IsFlush(hand)) return 6;
  if (IsStraight(hand)) return 5;
  if (HasThreeOfAKind(hand)) return 4;
  if (IsTwoPairs(hand)) return 3;
  if (IsOnePairs(hand)) return 2;
  return 1;
}
void GetCardString(Card card, char card_arr[100]) {
  char suits[4][10] = {"Spades", "Hearts", "Diamonds", "Clubs"};

  char faces[13][10] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven",
      "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

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
  char cardString[100] = {0};
  strcpy(card_arr, faces[faceindex]);
  strcat(card_arr, " of ");
  strcat(card_arr, suits[suitindex]);
}

// New function to convert card to string representation
void Print(Hand hand1, int rank1, Hand hand2, int rank2) {
  char rank1_type[100];
  char rank2_type[100];
  char card1[100];
  char card2[100];

  // Convert rank numbers to text descriptions.
  GetTextType(rank1, rank1_type);
  GetTextType(rank2, rank2_type);

  // Capitalize the first letter of rank types.
  rank1_type[0] -= ('a' - 'A');

  // Generate card descriptions for hand1.
  if (rank1 == 3) { // Pair
    char temp[100];
    GetCardString(hand1[0], temp);
    strcpy(card1, temp);
    strcat(card1, " and ");
    GetCardString(hand1[1], temp);
    strcat(card1, temp);
  } else if (rank1 == 2) { // Single card
    GetCardString(hand1[0], card1);
  } else if (rank1 == 10 || rank1 == 8 || rank1 == 4) {
    GetCardString(hand1[0], card1);
  } else { // High card
    GetCardString(FindLargest(hand1), card1);
  }

  // Generate card descriptions for hand2.
  if (rank2 == 3) { // Pair
    char temp1[100];
    GetCardString(hand2[0], temp1);
    strcpy(card2, temp1);
    strcat(card2, " and ");
    GetCardString(hand2[1], temp1);
    strcat(card2, temp1);
  } else if (rank2 == 2) { // Single card
    GetCardString(hand2[0], card2);
  } else if (rank2 == 10 || rank2 == 8 || rank2 == 4) {
    GetCardString(hand2[0], card2);
  } else { // High card
    GetCardString(FindLargest(hand2), card2);
  }

  if (rank1 == 3 && rank2 == 3) {
    int face1_1, face1_2, face2_1, face2_2;
    face1_1 = hand1[0].face;
    face1_2 = hand1[1].face;
    face2_1 = hand2[0].face;
    face2_2 = hand2[1].face;
    if (face1_1 > face2_1) {
      printf("%s (%s) wins over %s (%s).",
          rank1_type, card1, rank2_type, card2);
    }

    else if (face1_1 < face2_1) {
      printf("%s (%s) loses to %s (%s).",
          rank1_type, card1, rank2_type, card2);
    }

    else if (face1_1 == face2_1) {
      if (face1_2 > face2_2) {
        printf("%s (%s) wins over %s (%s).",
            rank1_type, card1, rank2_type, card2);
      }

      else if (face1_2 < face2_2) {
        printf("%s (%s) loses to %s (%s).",
            rank1_type, card1, rank2_type, card2);
      }

      else if (face1_2 == face2_2) {
        if (BiggerThan(FindLargest(hand1), FindLargest(hand2))) {
          printf("%s (%s) wins over %s (%s).",
              rank1_type, card1, rank2_type, card2);
        }

        else if (BiggerThan(FindLargest(hand2), FindLargest(hand1))) {
          printf("%s (%s) loses to %s (%s).",
              rank1_type, card1, rank2_type, card2);
        }
      }

    }
  }

  // Compare ranks and determine the winner.
  else if (rank1 > rank2) {
    printf("%s (%s) wins over %s (%s).", rank1_type,
        card1, rank2_type, card2);
  } else if (rank1 < rank2) {
    printf("%s (%s) loses to %s (%s).", rank1_type,
        card1, rank2_type, card2);
  } else {
    // If ranks are equal, compare the largest cards.
    if (BiggerThan(FindLargest(hand1), FindLargest(hand2))) {
      printf("%s (%s) wins over %s (%s).", rank1_type,
          card1, rank2_type, card2);
    } else if (BiggerThan(FindLargest(hand2), FindLargest(hand1))) {
      printf("%s (%s) loses to %s (%s).", rank1_type,
          card1, rank2_type, card2);
    } else {
      // Handle tie cases based on rank type.
      if (rank1 == 3) { // Tie in pairs.
        if (BiggerThan(hand1[0], hand2[0])) {
          printf("%s (%s) wins over %s (%s).", rank1_type,
              card1, rank2_type, card2);
        } else if (BiggerThan(hand2[0], hand1[0])) {
          printf("%s (%s) loses to %s (%s).", rank1_type,
              card1, rank2_type, card2);
        } else {
          printf("It's a tie with pairs: %s (%s) and %s (%s).", rank1_type,
              card1, rank2_type, card2);
        }
      } else if (rank1 == 2) { // Tie in single cards.
        if (BiggerThan(hand1[0], hand2[0])) {
          printf("%s (%s) wins over %s (%s).", rank1_type,
              card1, rank2_type, card2);
        } else if (BiggerThan(hand2[0], hand1[0])) {
          printf("%s (%s) loses to %s (%s).", rank1_type,
              card1, rank2_type, card2);
        } else {
          printf("It's a tie with single cards: %s (%s) and %s (%s).",
              rank1_type, card1, rank2_type, card2);
        }
      } else { // Tie in high cards.
        printf("It's a tie with high cards: %s (%s) and %s (%s).",
            rank1_type, card1, rank2_type, card2);
      }
    }
  }
}


void Play(Hand hand1, Hand hand2) {
  // Get hand ranks
  int rank1 = GetHandRank(hand1);
  int rank2 = GetHandRank(hand2);
  // Print the comparison results
  Print(hand1, rank1, hand2, rank2);
}

int main() {
  Hand firsthand, secondhand;

  if (InputHand(firsthand)) {
    if (InputHand(secondhand)) {
      Play(firsthand, secondhand);
    } else {  // second input set not okay
      printf("Input Error in second hand of cards!\n");
    }
  } else {  // first input set not okay
    printf("Input Error in first hand of cards!\n");
  }
  return 0;
}

void PrintCard(Card card) {
  char suits[4][10] = {"Spades", "Hearts", "Diamonds", "Clubs"};

  char faces[13][10] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven",
      "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

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

  printf("%s of %s", faces[faceindex], suits[suitindex]);
}

bool InputHand(Hand hand) {
  char suit_char;
  char face_str[10];
  int card_count = 0;

  while (1) {
    // -1 situation
    scanf(" %c", &suit_char);
    if (suit_char == '-') {
      int num = 0;
      scanf("%d", &num);
      if (num == 1) {
        break;
      } else {
        return false;
      }
    }

    // Card Count bigger than 5
    if (card_count >= 5) {
      return false;
    }

    scanf(" %s", face_str);

    // Add suit
    int suit;
    switch (suit_char) {
      case 'S':
        suit = SPADES;
        break;
      case 'H':
        suit = HEARTS;
        break;
      case 'D':
        suit = DIAMONDS;
        break;
      case 'C':
        suit = CLUBS;
        break;
      default:
        return false;
    }

    // Add face
    int face = -1;
    if (strcmp(face_str, "A") == 0) face = ACE;       // Ace
    else if (strcmp(face_str, "2") == 0) face = DEUCE; // Deuce
    else if (strcmp(face_str, "3") == 0) face = THREE; // Three
    else if (strcmp(face_str, "4") == 0) face = FOUR;  // Four
    else if (strcmp(face_str, "5") == 0) face = FIVE;  // Five
    else if (strcmp(face_str, "6") == 0) face = SIX;   // Six
    else if (strcmp(face_str, "7") == 0) face = SEVEN; // Seven
    else if (strcmp(face_str, "8") == 0) face = EIGHT; // Eight
    else if (strcmp(face_str, "9") == 0) face = NINE;  // Nine
    else if (strcmp(face_str, "10") == 0) face = TEN;  // Ten
    else if (strcmp(face_str, "J") == 0) face = JACK;  // Jack
    else if (strcmp(face_str, "Q") == 0) face = QUEEN; // Queen
    else if (strcmp(face_str, "K") == 0) face = KING;  // King
    else return false;

    // Store the card
    hand[card_count].suit = suit;
    hand[card_count].face = face;
    card_count++;
  }

  return (card_count == 5);
}

void PrintHand(Hand hand) {
  char suits[4][10] = {"Spades", "Hearts", "Diamonds", "Clubs"};
  char faces[13][10] = {
      "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven",
      "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

  for (int i = 0; i < 5; i++) {
    // Determine the index for face and suit
    int suit_index, face_index;

    switch (hand[i].suit) {
      case SPADES:
        suit_index = 0;
        break;
      case HEARTS:
        suit_index = 1;
        break;
      case DIAMONDS:
        suit_index = 2;
        break;
      case CLUBS:
        suit_index = 3;
        break;
      default:
        suit_index = -1;
    }

    switch (hand[i].face) {
      case ACE:
        face_index = 0;
        break;
      case DEUCE:
        face_index = 1;
        break;
      case THREE:
        face_index = 2;
        break;
      case FOUR:
        face_index = 3;
        break;
      case FIVE:
        face_index = 4;
        break;
      case SIX:
        face_index = 5;
        break;
      case SEVEN:
        face_index = 6;
        break;
      case EIGHT:
        face_index = 7;
        break;
      case NINE:
        face_index = 8;
        break;
      case TEN:
        face_index = 9;
        break;
      case JACK:
        face_index = 10;
        break;
      case QUEEN:
        face_index = 11;
        break;
      case KING:
        face_index = 12;
        break;
      default:
        face_index = -1;
    }

    if (suit_index != -1 && face_index != -1) {
      printf("%s of %s\n", faces[face_index], suits[suit_index]);
    }
  }
}

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

Card FindLargest(Hand hand) {
  Card maybe_largest = hand[0];
  int special_array[5] = {0};
  bool is_special = true;
  for (int i = 0 ; i < 5; i++) {
    switch (hand[i].face) {
      case ACE:
        special_array[0]+=1;
        break;
      case DEUCE:
        special_array[1]+=1;
        break;
      case THREE:
        special_array[2]+=1;
        break;
      case FOUR:
        special_array[3]+=1;
        break;
      case FIVE:
        special_array[4]+=1;
        break;
      default:
        break;
    }
  }
  for (int i = 0 ; i < 5; i++) {
    if (special_array[i] != 1) {
      is_special = false;
    }
  }
  if (is_special) {
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == FIVE) {
        return hand[i];
      }
    }
  }
  for (int i = 1; i < 5; i++) {
    if (BiggerThan(hand[i], maybe_largest)) {
      maybe_largest = hand[i];
    }
  }
  return maybe_largest;
}

bool IsFlush(Hand hand) {
  int same_count = 0;
  for (int i = 1; i < 5; i++) {
    if (hand[i - 1].suit != hand[i].suit) {
      return false;
    }
  }
  return true;
}

bool IsStraight(Hand hand) {
  int face_arr[5] = {0};
  bool check_a = false;
  for (int i = 0; i < 5; i++) {
    if (Order(hand[i].face) == 2) {
      check_a = true;
    }
  }
  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
  }
  if (check_a) {
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == ACE) {
        face_arr[i] = 1;
      }
    }
  }
  // Sort
  for (int i = 0; i < 5 - 1; i++) {
    for (int j = 0; j < 5 - i - 1; j++) {
      if (face_arr[j] > face_arr[j + 1]) {
        int temp = face_arr[j];
        face_arr[j] = face_arr[j + 1];
        face_arr[j + 1] = temp;
      }
    }
  }
  // Check Straight
  for (int i = 1; i < 5; i++) {
    if ((face_arr[i] - face_arr[i - 1]) != 1) {
      return false;
    }
  }
  return true;
}
// Check Flush
bool IsFlushCheck(Hand hand) {
  int same_count = 0;
  for (int i = 1; i < 5; i++) {
    if (hand[i - 1].suit != hand[i].suit) {
      return false;
    }
  }
  return true;
}

// Check Straight
bool IsStraightCheck(Hand hand) {
  int face_arr[5] = {0};
  bool check_a = false;
  for (int i = 0; i < 5; i++) {
    if (Order(hand[i].face) == 2) {
      check_a = true;
    }
  }
  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
  }
  if (check_a) {
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == ACE) {
        face_arr[i] = 1;
      }
    }
  }
  // Sort
  for (int i = 0; i < 5 - 1; i++) {
    for (int j = 0; j < 5 - i - 1; j++) {
      if (face_arr[j] > face_arr[j + 1]) {
        int temp = face_arr[j];
        face_arr[j] = face_arr[j + 1];
        face_arr[j + 1] = temp;
      }
    }
  }
  // Check Straight
  for (int i = 1; i < 5; i++) {
    if ((face_arr[i] - face_arr[i - 1]) != 1) {
      return false;
    }
  }
  return true;
}

bool IsStraightFlush(Hand hand) {
  if (IsFlushCheck(hand) && IsStraightCheck(hand)) {
    return true;
  }
  return false;
}

bool IsFourOfAKind(Hand hand) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    switch (hand[i].face) {
      case ACE:
        face_arr[i] = 14;
        break;
      case DEUCE:
        face_arr[i] = 2;
        break;
      case THREE:
        face_arr[i] = 3;
        break;
      case FOUR:
        face_arr[i] = 4;
        break;
      case FIVE:
        face_arr[i] = 5;
        break;
      case SIX:
        face_arr[i] = 6;
        break;
      case SEVEN:
        face_arr[i] = 7;
        break;
      case EIGHT:
        face_arr[i] = 8;
        break;
      case NINE:
        face_arr[i] = 9;
        break;
      case TEN:
        face_arr[i] = 10;
        break;
      case JACK:
        face_arr[i] = 11;
        break;
      case QUEEN:
        face_arr[i] = 12;
        break;
      case KING:
        face_arr[i] = 13;
        break;
      default:
        face_arr[i] = -1; // Indicate invalid face value
        break;
    }
  }
  int fourfacevalue = -1;
  for (int i = 0; i < 2; i++) {
    int current = face_arr[i];
    int count = 0;
    for (int j = 0; j < 5; j++) {
      if (current == face_arr[j]) {
        count++;
      }
    }
    if (count == 4) {
      fourfacevalue = current;
      break;
    }
  }

  if (fourfacevalue == -1) {
    return false;
  }

  int largestindex = -1;
  for (int i = 0; i < 5; i++) {
    if (face_arr[i] == fourfacevalue) {
      if (largestindex == -1 || BiggerThan(hand[i], hand[largestindex])) {
        largestindex = i;
      }
    }
  }
  if (largestindex != 0) {
    Card temp = hand[0];
    hand[0] = hand[largestindex];
    hand[largestindex] = temp;
  }

  return true;
}

bool HasThreeOfAKind(Hand hand) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    switch (hand[i].face) {
      case ACE:
        face_arr[i] = 14;
        break;
      case DEUCE:
        face_arr[i] = 2;
        break;
      case THREE:
        face_arr[i] = 3;
        break;
      case FOUR:
        face_arr[i] = 4;
        break;
      case FIVE:
        face_arr[i] = 5;
        break;
      case SIX:
        face_arr[i] = 6;
        break;
      case SEVEN:
        face_arr[i] = 7;
        break;
      case EIGHT:
        face_arr[i] = 8;
        break;
      case NINE:
        face_arr[i] = 9;
        break;
      case TEN:
        face_arr[i] = 10;
        break;
      case JACK:
        face_arr[i] = 11;
        break;
      case QUEEN:
        face_arr[i] = 12;
        break;
      case KING:
        face_arr[i] = 13;
        break;
      default:
        face_arr[i] = -1; // Indicate invalid face value
        break;
    }
  }
  int threefacevalue = -1;
  for (int i = 0; i < 2; i++) {
    int current = face_arr[i];
    int count = 0;
    for (int j = 0; j < 5; j++) {
      if (current == face_arr[j]) {
        count++;
      }
    }
    if (count > 3) return false;
    if (count == 3) {
      threefacevalue = current;
      break;
    }
  }

  if (threefacevalue == -1) {
    return false;
  }

  int largestindex = -1;
  for (int i = 0; i < 5; i++) {
    if (face_arr[i] == threefacevalue) {
      if (largestindex == -1 || BiggerThan(hand[i], hand[largestindex])) {
        largestindex = i;
      }
    }
  }
  if (largestindex != 0) {
    Card temp = hand[0];
    hand[0] = hand[largestindex];
    hand[largestindex] = temp;
  }

  return true;
}

bool IsOnePairs(Hand hand) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
  }
  int pairfacevalue = -1;
  for (int i = 0; i < 4; i++) {
    int current = face_arr[i];
    int count = 0;
    for (int j = 0; j < 5; j++) {
      if (current == face_arr[j]) {
        count++;
      }
    }
    if (count == 2) {
      pairfacevalue = current;
      break;
    }
  }

  if (pairfacevalue == -1) {
    return false;
  }
  int largestindex = -1;
  for (int i = 0; i < 5; i++) {
    if (face_arr[i] == pairfacevalue) {
      if (largestindex == -1 || BiggerThan(hand[i], hand[largestindex])) {
        largestindex = i;
      }
    }
  }
  if (largestindex != 0) {
    Card temp = hand[0];
    hand[0] = hand[largestindex];
    hand[largestindex] = temp;
  }

  return true;
}

bool HasOnePair(Hand hand, bool exclude_a_card, Card excluded_card) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
  }
  int pairfacevalue = -1;
  for (int i = 0; i < 4; i++) {
    int current = face_arr[i];
    int count = 0;
    if (!exclude_a_card) {
      for (int j = 0; j < 5; j++) {
        if (current == face_arr[j]) {
          count++;
        }
      }
    } else if (exclude_a_card && !Equal(excluded_card, hand[i])) {
      for (int j = 0; j < 5; j++) {
        if (current == face_arr[j]) {
          count++;
        }
      }
    }
    if (count == 2) {
      pairfacevalue = current;
      break;
    }
  }

  if (pairfacevalue == -1) {
    return false;
  }

  int largestindex = -1;
  for (int i = 0; i < 5; i++) {
    if (face_arr[i] == pairfacevalue) {
      if (largestindex == -1 || BiggerThan(hand[i], hand[largestindex])) {
        largestindex = i;
      }
    }
  }
  if (largestindex != 0) {
    Card temp = hand[0];
    hand[0] = hand[largestindex];
    hand[largestindex] = temp;
  }

  return true;
}
bool OnePair(Hand hand) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
  }
  int pairfacevalue = -1;
  for (int i = 0; i < 4; i++) {
    int current = face_arr[i];
    int count = 0;
    for (int j = 0; j < 5; j++) {
      if (current == face_arr[j]) {
        count++;
      }
    }
    if (count == 2) {
      return true;
    }
  }

  return false;
}
bool IsTwoPairs(Hand hand) {
  if (IsFourOfAKind(hand) || HasThreeOfAKind(hand)) {
    return false;
  }

  Card firstpaircard;
  Card secondpaircard;
  Hand temphand;

  for (int i = 0; i < 5; ++i) {
    temphand[i] = hand[i];
  }

  if (!HasOnePair(temphand, false, firstpaircard)) {
    return false;
  }

  firstpaircard = temphand[0];

  if (!HasOnePair(temphand, true, firstpaircard)) {
    return false;
  }

  secondpaircard = temphand[0];

  if (BiggerThan(firstpaircard, secondpaircard)) {
    hand[0] = firstpaircard;
    hand[1] = secondpaircard;
  } else {
    hand[0] = secondpaircard;
    hand[1] = firstpaircard;
  }

  return true;
}

bool IsFullHouse(Hand hand) {
  if (OnePair(hand)) {
    if (HasThreeOfAKind(hand)) {
      return true;
    }
  }
  return false;
}
