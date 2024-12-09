/* hidden code */

/** see if 'hand' contains two pairs. If 'hand' does contain two pairs, 
 * swap the largest card of each pair to be the 1st and 2nd card in the hand
 * (hand[0] and hand[1])
 * @param hand a hand of cards (5 cards)
 * @return true if 'hand' does contain two pairs. 
                Otherwise return false (and there is no need to swap the largest card)
 * Important : "two pairs" means there are no "three of a kind"!!!
 */
bool Equal(Card card1, Card card2) {
  return card1.face == card2.face;
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

  return true;
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
  return true;
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

