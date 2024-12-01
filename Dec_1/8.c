/* copyright cycuice */

/** see if 'hand' contains a straight.
 *  if 'hand' does contain a straight, 
 *  swap the largest card to be the first card (i.e., hand[0]) 
 *  @return true if hand contains a straight. Otherwise, 
 *         just return false (and there is no need to swap the largest card) 
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
int OrderRight(Face face) {
  switch (face) {
    case ACE:
      return 1;
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
bool IsStraight(Hand hand) {
  int face_arr[5] = {0};
  bool check_a = false;
  for (int i = 0; i < 5; i++) {
    if (OrderRight(hand[i].face) == 2) {
      check_a = true;
    }
  }
  if (check_a) {
    for (int i = 0; i < 5; i++) {
      face_arr[i] = OrderRight(hand[i].face);
    }
  } else {
    for (int i = 0; i < 5; i++) {
      face_arr[i] = Order(hand[i].face);
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

  Swap(hand);
  return true;
}