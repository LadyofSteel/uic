/**
 *  @brief Hand class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Collections;
import java.util.Comparator;

/**
 *  @brief Hand class
*/
public class Hand {
  private ArrayList<Card> _hand;
  private ArrayList<Integer> _rank_occurrences;
  private Evaluation _eval;

  /**
   *  @brief Hand evaluation enum
   *
   *  This is used to identify the hand more easily
  */
  public enum Evaluation
  {
    HighCard(1, "High Card"),
    TwoKind(2, "Two Of A Kind"),
    TwoPair(3, "Two Pair"),
    ThreeKind(4, "Three Of A Kind"),
    Straight(5, "Straight"),
    Flush(6, "Flush"),
    FullHouse(7, "Full House"),
    FourKind(8, "Four Of A Kind"),
    StraightFlush(9, "Straight Flush");
    
    private int _value;
    private String _name;

    /**
     *  @brief Enum constructor
    */
    private Evaluation(int value, String name) 
    {
      _value = value;
      _name = name;
    }

    /**
     *  @brief Enum value getter
    */
    public int getValue()    { return _value; }

    /**
     *  @brief Enum name getter
    */
    public String getName()  { return _name; }
  }

  /**
   *  @brief Constructor 1
  */
  public Hand()
  {
    _hand = new ArrayList<Card>();
    _rank_occurrences = new ArrayList<>(13);

    for (int i = 0; i < 13; i++)
      _rank_occurrences.add(0);
  }

  /**
   *  @brief Constructor 2
  */
  public Hand(ArrayList<Card> cards)
  {
    _hand = cards;
    _rank_occurrences = new ArrayList<>(13);
    for (int i = 0; i < 13; i++)
      _rank_occurrences.add(0);
  }

  /**
   *  @brief Adds a card to hand
  */
  public void addCard(Card card)
  {
    _hand.add(card);
  }

  /**
   *  @brief Adds a card to hand
  */
  public void addCard(String card)
  {
    _hand.add(new Card(card));
  }

  /**
   *  @brief Discards given card from hand
  */
  public void discard(int card_to_remove)
  {
    _hand.remove(card_to_remove);
  }

  /**
   *  @brief Discards given card from hand
  */
  public void discard(Card card_to_remove)
  {
    int card_position = _hand.indexOf(card_to_remove);
    _hand.remove(card_position);
  }

  /**
   *  @brief Adds a card to hand
  */
  public void discard(String card_to_remove)
  {
    Iterator<Card> iterator = _hand.iterator();

    while (iterator.hasNext()) {
      Card card = iterator.next();

      if (card_to_remove.equals(card.getCard())) {
        int card_position = _hand.indexOf(card);
        _hand.remove(card_position);
        return;
      }
    }
  }

  /**
   *  @brief Compares hands
   *
   *  This is a long one because I had to write it at the last minute.
   *  It compares the current hand to the given hand, and returns an int to
   *  determine the higher hand of the two. Returns -1 for current hand,
   *  returns 1 for input hand, and returns 0 for a tie.
  */
  public int compareToHand(Hand hand)
  {
    int eval1 = this.getEvaluation().getValue();
    int eval2 = hand.getEvaluation().getValue();

    if (eval1 == eval2) {
      if (eval1 == 1) {         // High card tie
        for (int i = 0; i < 5; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 2) {  // Two of a kind tie
        for (int i = 0; i < 5; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 3) {  // Two pair tie
        for (int i = 0; i < 5; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 4) {  // Three of a kind tie
        for (int i = 0; i < 3; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 5) {  // Straight tie
        int rank1 = this.getCards().get(0).getRank();
        int rank2 = hand.getCards().get(0).getRank();

        if (rank1 > rank2)
          return -1;
        else if (rank1 < rank2)
          return 1;
        else
          return 0;
      } else if (eval1 == 6) {  // Flush tie
        for (int i = 0; i < 5; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 7) {  // Full house tie
        for (int i = 0; i < 3; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else if (eval1 == 8) {  // Four of a kind tie
        for (int i = 0; i < 4; i++) {
          int rank1 = this.getCards().get(i).getRank();
          int rank2 = hand.getCards().get(i).getRank();

          if (rank1 > rank2)
            return -1;
          else if (rank1 < rank2)
            return 1;
        }
        return 0;
      } else {  // Straight flush tie
        int rank1 = this.getCards().get(0).getRank();
        int rank2 = hand.getCards().get(0).getRank();

        if (rank1 > rank2)
          return -1;
        else if (rank1 < rank2)
          return 1;
        else
          return 0;
      }
    } else if (eval1 > eval2) {
      return -1;
    } else {
      return 1;
    }
  }

  /**
   *  @brief Evaluates the current hand
  */
  public void evaluate()
  {
    // Use extra-credit sort
    this.sort();

    if (isFourKind()) {
      setEvaluation(Evaluation.FourKind);
    } else if (isFlush()) {
      if (isStraight()) {
        setEvaluation(Evaluation.StraightFlush);
      } else {
        setEvaluation(Evaluation.Flush);
      }
    } else if (isStraight()) {
      setEvaluation(Evaluation.Straight);
    } else if (isThreeKind()) {
      if (isTwoKind()) {
        setEvaluation(Evaluation.FullHouse);
      } else {
        setEvaluation(Evaluation.ThreeKind);
      }
    } else if (isTwoPair()) {
      setEvaluation(Evaluation.TwoPair);
    } else if (isTwoKind()) {
      setEvaluation(Evaluation.TwoKind);
    } else {
      setEvaluation(Evaluation.HighCard);
    }
  }

  /**
   *  @brief Sorts the cards
   *
   *  This sort method is the extra-credit sort described in the project description.
   *  It basically uses an list of the rank occurrences, where an element represents the
   *  number of occurrences of the card rank represented by the index.
   *  It uses this list of occurrences and sorts the hand by getting the highest occurrences
   *  first.
  */
  private void sort()
  {
    for (int i = 0; i < 13; i++)
      _rank_occurrences.set(i, 0);

    this.checkRankOccurrences();

    // We remove the matching cards from the original hand into a new sorted list
    ArrayList<Card> sortedHand = new ArrayList<Card>();

    // Clone the occurrences list to be able to use it later
    ArrayList<Integer> clone_occurrences = new ArrayList<Integer>(_rank_occurrences);

    while (!_hand.isEmpty()) {
      // Since the cards start from 2 to 14 (A), we must increment the index of
      // the occurrence list to get the actual card rank
      int rank = findMax(clone_occurrences) + 2;

      for (int i = 0; i < _hand.size(); i++) {
        Card card = _hand.get(i);

        if (card.getRank() == rank) {
          sortedHand.add(card);
          int card_position = _hand.indexOf(card);
          _hand.remove(card_position);
          i--;
        }
      }
    }
    
    this.setHand(sortedHand);
  }

  /**
   *  @brief Find the max occurrence
  */
  private int findMax(ArrayList<Integer> occurrences)
  {
    int max = 0;
    int max_index = 0;
    for (int i = 0; i < occurrences.size(); i++) {
      int occurrence = occurrences.get(i);
      if (occurrence >= max) {
        max = occurrence;
        max_index = i;
      }
    }

    occurrences.set(max_index, 0);
    return max_index;
  }

  /**
   *  @brief Checks the occurrences of each rank in hand
  */
  private void checkRankOccurrences()
  {
    Iterator<Card> iterator = _hand.iterator();
    
    while(iterator.hasNext()) {
      Card card = iterator.next();
      int card_rank = card.getRank();

      // Since the cards start from 2 to 14 (A), we must decrement the
      // card rank by 2 to fill the list indexes correctly
      int count = _rank_occurrences.get(card_rank - 2) + 1;
      _rank_occurrences.set(card_rank - 2, count);
    }
  }

  /**
   *  @brief Checks if hand is two of a kind
  */
  private boolean isTwoKind()
  {
    return this.getOccurrences().contains(2);
  }

  /**
   *  @brief Checks if hand is two pair
  */
  private boolean isTwoPair()
  {
    int count = 0;
    for (int i : _rank_occurrences) {
      if (i == 2)
        count++;
    }

    return count == 2;
  }

  /**
   *  @brief Checks if hand is three of a kind
  */
  private boolean isThreeKind()
  {
    return this.getOccurrences().contains(3);
  }

  /**
   *  @brief Checks if hand is straight
  */
  private boolean isStraight()
  {
    int difference = 0;

    for (int i = 0, j = 1; j < _hand.size(); i++, j++) {
      Card card1 = _hand.get(i);
      Card card2 = _hand.get(j);
      int rank1 = card1.getRank();
      int rank2 = card2.getRank();

      difference = rank1 - rank2;
      if (difference > 1 || difference < 1) {
        if (difference != 9) {
          return false;
        }
      }
    }
    return true;
  }

  /**
   *  @brief Checks if hand is flush
  */
  private boolean isFlush()
  {
    for (int i = 0, j = 1; j < _hand.size(); i++, j++) {
      Card card1 = _hand.get(i);
      Card card2 = _hand.get(j);
      char suit1 = card1.getSuit();
      char suit2 = card2.getSuit();

      if (suit1 != suit2)
        return false;
    }
    return true;
  }

  /**
   *  @brief Checks if hand is four of a kind
  */
  private boolean isFourKind()
  {
    return this.getOccurrences().contains(4);
  }

  /**
   *  @brief Cards getter
  */
  public ArrayList<Card> getCards()           { return _hand; }

  /**
   *  @brief Rank occurrences getter
  */
  public ArrayList<Integer> getOccurrences()  { return _rank_occurrences; }

  /**
   *  @brief Hand evaluation getter
  */
  public Evaluation getEvaluation()           { return _eval; }

  /**
   *  @brief Number of cards getter
  */
  public int getNumberOfCards()               { return _hand.size(); }

  /**
   *  @brief Cards setter
  */
  public void setHand(ArrayList<Card> cards)  { _hand = cards; }

  /**
   *  @brief Hand evaluation setter
  */
  public void setEvaluation(Evaluation eval)  { _eval = eval; }
}

