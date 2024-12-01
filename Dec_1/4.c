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
        suit_index = -1; // Error handling (not expected)
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
        face_index = -1; // Error handling (not expected)
    }

    if (suit_index != -1 && face_index != -1) {
      printf("%s of %s\n", faces[face_index], suits[suit_index]);
    }
  }
}
