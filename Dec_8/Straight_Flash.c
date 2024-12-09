#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef enum esuit {
   SPADES = 832, HEARTS = 574, DIAMONDS = 456, CLUBS = 192
} Suit;

typedef enum eface {
   ACE = 3947,
   DEUCE = 4537,
   THREE = 6696,
   FOUR = 7729,
   FIVE = 8374,
   SIX = 9295,
   SEVEN = 11491,
   EIGHT = 13638,
   NINE = 14554,
   TEN = 15332,
   JACK = 18987,
   QUEEN = 20215,
   KING = 213643
} Face;

typedef struct card {
   Suit suit;
   Face face;
} Card;
typedef Card Hand[5];
/* Code */
/* copyright cycuice */

/** see if 'hand' contains a straight flush.
 * if 'hand' does contain a straight flush, swap the largest card 
 * to be the first card in the hand (hand[0])
 * @param  hand a hand of cards (5 cards)
 * @return true if 'hand' contains a straight flush. 
 * Otherwise return false (and there is no need to swap the largest card) 
 */
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

int LargestPlace(Hand hand) {
  Card maybe_largest = hand[0];  
  int largest_place = 0;
  bool is_special = true;
  int special_array[5] = {0};  
  for (int i = 0; i < 5; i++) {
    switch (hand[i].face) {
      case ACE:
        special_array[0] += 1;
        break;
      case DEUCE:
        special_array[1] += 1;
        break;
      case THREE:
        special_array[2] += 1;
        break;
      case FOUR:
        special_array[3] += 1;
        break;
      case FIVE:
        special_array[4] += 1;
        break;
      default:
        break;
    }
  }
  
  for (int i = 0; i < 5; i++) {
    if (special_array[i] != 1) {
      is_special = false;
    }
  }
  if (is_special) {
    for (int i = 0; i < 5; i++) {
      if (hand[i].face == FIVE) {
        return i;
      }
    }
  }
  for (int i = 1; i < 5; i++) {
    if (BiggerThan(hand[i], maybe_largest)) {
      maybe_largest = hand[i];
      largest_place = i; 
    }
  }
  
  return largest_place;

}

void Swap(Hand hand) {
  Card temp = hand[0];
  int largest_place = LargestPlace(hand);
  hand[0] = FindLargest(hand);
  hand[largest_place] = temp;
}

// Check Flush
bool IsFlush(Hand hand) {
  int same_count = 0;
  for (int i = 1; i < 5; i++) {
    if (hand[i - 1].suit != hand[i].suit) {
      return false;
    }
  }
  return true;
}

// Check Straight
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
bool IsStraightFlush(Hand hand) {
  if (IsFlush(hand) && IsStraight(hand)) {
    Swap(hand);
    return true;
  }
  return false;
}

int main() {
  int count = 0;

  return 0;
}