#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int suit; // Values from Suit enum
    int face; // Values from Face enum
} Card;

typedef Card Hand[5];

typedef enum esuit {
    SPADES = 832, HEARTS = 574, DIAMONDS = 456, CLUBS = 192
} Suit;

typedef enum eface {
    ACE = 3947, DEUCE = 4537, THREE = 6696, FOUR = 7729, FIVE = 8374,
    SIX = 9295, SEVEN = 11491, EIGHT = 13638, NINE = 14554, TEN = 15332,
    JACK = 18987, QUEEN = 20215, KING = 213643
} Face;

/* copyright cycuice */
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
