/* hidden code */

/** see if 'hand' contains a full house ("three of a kind" + "a pair")
 * if 'hand' does contain a full house, swap the largest card of the "three of a kind"
 * to be the first card in the hand (hand[0]) and return true
 * @param hand a hand of cards (5 cards)
 * @return true if 'hand' does contain a full house. 
 *              Otherwise, just return false (and there is no need to swap the largest card)
 */
bool Equal(Card card1, Card card2) {
  return card1.face == card2.face && card1.suit == card2.suit;
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
// Check pair
bool HasOnePair(Hand hand) {
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
// Check Three of kind
bool HasThreeOfAKind(Hand hand) {
  int face_arr[5] = {0};

  for (int i = 0; i < 5; i++) {
    face_arr[i] = Order(hand[i].face);
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
bool IsFullHouse(Hand hand) {
  if (HasOnePair) {
    if (HasThreeOfAKind) {
      return true;
    }
  }
  return false;
}