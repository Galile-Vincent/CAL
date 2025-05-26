#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include "Four.cpp" // Assume the provided code is in poker.cpp

// Helper function to create a hand from string inputs
Hand createHand(const std::vector<std::string>& suits, const std::vector<std::string>& faces) {
    assert(suits.size() == 5 && faces.size() == 5);
    Card cards[5];
    for (int i = 0; i < 5; ++i) {
        cards[i] = Card(GetFaceType(faces[i]), GetSuitType(suits[i]));
    }
    Hand hand(cards);
    return hand;
}

// Helper function to simulate input for Player::InputHand
bool simulateInput(Player& player, const std::string& input) {
    std::istringstream iss(input);
    std::cin.rdbuf(iss.rdbuf());
    bool result = player.InputHand();
    std::cin.rdbuf(std::cin.rdbuf()); // Restore cin
    return result;
}

// Test hand evaluation
void testHandEvaluation() {
    // Test Straight Flush
    std::vector<std::string> suits = {"H", "H", "H", "H", "H"};
    std::vector<std::string> faces = {"2", "3", "4", "5", "6"};
    Hand sf = createHand(suits, faces);
    Card maxcard;
    assert(sf.IsStraightFlush(&maxcard) == true);
    assert(sf.IninialHand() == STRAIGHT_FLUSH);
    assert(maxcard.GetFace() == SIX);

    // Test Four of a Kind
    suits = {"H", "D", "C", "S", "H"};
    faces = {"7", "7", "7", "7", "8"};
    Hand fok = createHand(suits, faces);
    assert(fok.IsFourOfKind(&maxcard) == true); // Fixed typo: sf -> fok
    assert(fok.IninialHand() == FOUR_OF_KIND);
    assert(maxcard.GetFace() == SEVEN);

    // Test Full House
    suits = {"H", "D", "C", "H", "D"};
    faces = {"9", "9", "9", "Q", "Q"};
    Hand fh = createHand(suits, faces);
    assert(fh.IsFullHouse(&maxcard) == true);
    assert(fh.IninialHand() == FULL_HOUSE);
    assert(maxcard.GetFace() == NINE);

    // Test Flush
    suits = {"S", "S", "S", "S", "S"};
    faces = {"2", "4", "6", "8", "K"};
    Hand fl = createHand(suits, faces);
    assert(fl.IsFlush(&maxcard) == true);
    assert(fl.IninialHand() == FLUSH);
    assert(maxcard.GetFace() == KING);

    // Test Straight (Ace-high)
    suits = {"H", "D", "C", "S", "H"};
    faces = {"10", "J", "Q", "K", "A"};
    Hand st = createHand(suits, faces);
    assert(st.IsStraight(&maxcard) == true);
    assert(st.IninialHand() == STRAIGHT);
    assert(maxcard.GetFace() == ACE);

    // Test Straight (Ace-low, special case)
    suits = {"H", "D", "C", "S", "H"};
    faces = {"A", "2", "3", "4", "5"};
    Hand st_low = createHand(suits, faces);
    st_low.SetSpecial(true);
    assert(st_low.IsStraight(&maxcard) == true);
    assert(st_low.IninialHand() == STRAIGHT);
    assert(maxcard.GetFace() == FIVE);

    // Test Three of a Kind
    suits = {"H", "D", "C", "S", "H"};
    faces = {"8", "8", "8", "4", "J"};
    Hand tok = createHand(suits, faces);
    assert(tok.IsThreeOfKind(&maxcard) == true);
    assert(tok.IninialHand() == THREE_OF_KIND);
    assert(maxcard.GetFace() == EIGHT);

    // Test Two Pair
    suits = {"H", "D", "C", "S", "H"};
    faces = {"6", "6", "Q", "Q", "3"};
    Hand tp = createHand(suits, faces);
    Card largest1, largest2;
    assert(tp.IsTwoPair(&largest1, &largest2) == true);
    assert(tp.IninialHand() == TWO_PAIR);
    assert(largest1.GetFace() == QUEEN);
    assert(largest2.GetFace() == SIX);

    // Test One Pair
    suits = {"H", "D", "C", "S", "H"};
    faces = {"5", "5", "7", "J", "K"};
    Hand op = createHand(suits, faces);
    assert(op.HasOnePair(Card(), &maxcard) == true);
    assert(op.IninialHand() == ONE_PAIR);
    assert(maxcard.GetFace() == FIVE);

    // Test Zilch (High Card)
    suits = {"H", "D", "C", "S", "H"};
    faces = {"2", "4", "6", "8", "Q"};
    Hand z = createHand(suits, faces);
    assert(z.IninialHand() == ZLICH);
    assert(z.GetLargest().GetFace() == QUEEN);
}

// Test Card::BiggerThan
void testCardComparison() {
    Card c1(ACE, HEARTS);
    Card c2(KING, HEARTS);
    Card c3(ACE, DIAMONDS);
    Card c4(FIVE, SPADES);
    Card c5(FIVE, CLUBS);

    // Test face comparison
    assert(c1.BiggerThan(c2, false) == true);
    assert(c2.BiggerThan(c1, false) == false);

    // Test suit comparison (same face)
    assert(c1.BiggerThan(c3, false) == true); // HEARTS > DIAMONDS
    assert(c3.BiggerThan(c1, false) == false);

    // Test special case (Ace-low straight)
    assert(c1.BiggerThan(c4, true) == false); // ACE is low
    assert(c4.BiggerThan(c1, true) == true);

    // Test suit comparison in special case
    assert(c4.BiggerThan(c5, true) == true); // SPADES > CLUBS
}

// Test Player::InputHand
void testInputHand() {
    Player p;

    // Valid input (Straight Flush)
    std::string input = "H 2 H 3 H 4 H 5 H 6 -1";
    assert(simulateInput(p, input) == true);
    assert(p.GetType() == STRAIGHT_FLUSH);

    // Invalid input (too few cards)
    input = "H 2 H 3 H 4 -1";
    assert(simulateInput(p, input) == false);

    // Invalid input (invalid suit)
    input = "X 2 H 3 H 4 H 5 H 6 -1";
    assert(simulateInput(p, input) == true); // Handles gracefully, sets DEFAULT_Suit
    assert(p.GetHand().GetCard(0).GetSuit() == DEFAULT_Suit);

    // Invalid input (invalid face)
    input = "H X H 3 H 4 H 5 H 6 -1";
    assert(simulateInput(p, input) == true); // Handles gracefully, sets DEFAULT_Face
    assert(p.GetHand().GetCard(0).GetFace() == DEFAULT_Face);

    // Special case (Ace-low straight, sum = 23)
    input = "H A D 2 C 3 S 4 H 5 -1";
    assert(simulateInput(p, input) == true);
    assert(p.GetHand().IsSpecial() == true);
    assert(p.GetType() == STRAIGHT);
}

// Test Play function
void testPlay() {
    // Test Straight Flush vs Four of a Kind
    std::vector<std::string> suits = {"H", "H", "H", "H", "H"};
    std::vector<std::string> faces = {"2", "3", "4", "5", "6"};
    Hand h1 = createHand(suits, faces);
    suits = {"H", "D", "C", "S", "H"};
    faces = {"7", "7", "7", "7", "8"};
    Hand h2 = createHand(suits, faces);
    Player p1(h1);
    Player p2(h2);
    p1.GetHand().IninialHand();
    p2.GetHand().IninialHand();
    std::stringstream ss;
    std::streambuf* oldCout = std::cout.rdbuf(ss.rdbuf());
    Play(p1, p2);
    std::cout.rdbuf(oldCout);
    std::string output = ss.str();
    assert(output.find("Straight flush") != std::string::npos);
    assert(output.find("wins over") != std::string::npos);

    // Test Two Pair vs Two Pair (tiebreaker)
    suits = {"H", "D", "C", "S", "H"};
    faces = {"Q", "Q", "6", "6", "3"};
    h1 = createHand(suits, faces);
    faces = {"J", "J", "6", "6", "3"};
    h2 = createHand(suits, faces);
    p1 = Player(h1);
    p2 = Player(h2);
    p1.GetHand().IninialHand();
    p2.GetHand().IninialHand();
    ss.str("");
    std::cout.rdbuf(ss.rdbuf());
    Play(p1, p2);
    std::cout.rdbuf(oldCout);
    output = ss.str();
    assert(output.find("Two pairs (Queen") != std::string::npos);
    assert(output.find("wins over") != std::string::npos);

    // Test Full House vs Full House (tiebreaker on three-of-a-kind)
    suits = {"H", "D", "C", "H", "D"};
    faces = {"K", "K", "K", "Q", "Q"};
    h1 = createHand(suits, faces);
    faces = {"Q", "Q", "Q", "K", "K"};
    h2 = createHand(suits, faces);
    p1 = Player(h1);
    p2 = Player(h2);
    p1.GetHand().IninialHand();
    p2.GetHand().IninialHand();
    ss.str("");
    std::cout.rdbuf(ss.rdbuf());
    Play(p1, p2);
    std::cout.rdbuf(oldCout);
    output = ss.str();
    assert(output.find("Full house (King") != std::string::npos);
    assert(output.find("wins over") != std::string::npos);
}

int main() {
    testHandEvaluation();
    testCardComparison();
    testInputHand();
    testPlay();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}