/* hidden code */

/** see if 'hand' contains a "pair" (two cards of the same face values)
 * if 'excludeACard' is true, then this "pair", if exists, must not include 'excludedCard'
 * if 'hand' does contain such a pair, swap the largest card of the two cards 
 * to be the first card in the hand (hand[0])
 * otherwise, just return false (and there is no need to swap the largest card)
 * @param hand a hand of cards (5 cards)
 * @param  exclude_a_card when true, the card in the third parameter doesn't count as a pair. 
 *                     If false, disregard the third parameter. 
 * @param excluded_card the card that doesn't count as a pair. Only useful 
 *                     when the second parameter is true.
 * @return true if 'hand' does contain such a pair and the first cards must be the largest card.  
 *              Otherwise return false (and there is no need to swap the largest card)
 * Note: cards belonging to "three of a kind" or "four of a kind", are not considered
 * a part of a "pair"
 */
bool Equal(Card card1, Card card2) {
  return card1.face == card2.face && card1.suit == card2.suit;
}
bool HasOnePair(Hand hand, bool exclude_a_card, Card excluded_card) {
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
  int pairfacevalue = -1;
  for (int i = 0; i < 4; i++) {
    int current = face_arr[i];
    int count = 0;
    for (int j = 0; j < 5; j++) {
      if (current == face_arr[j]) {
        count++;
      }
    }
    if (count >= 3) return false;
    if (count == 2 && !(exclude_a_card && Equal(hand[i], excluded_card))) {
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