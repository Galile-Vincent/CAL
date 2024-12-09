/* hidden code */

/** see if 'hand' contains "four of a kind" (four cards of the same face value)
 * if 'hand' does contain "four of a kind", swap the largest card of the four cards 
 * to be the first card in the hand (hand[0])
 * @param hand a hand of cards (5 cards)
 * @return true if 'hand' does contain "four of a kind".
 * Otherwise, just return false (and there is no need to swap the largest card) 
 */
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