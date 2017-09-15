/**
 *  @brief CardPile class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.ArrayList;
import java.util.Collections;

/**
 *  @brief Card Pile class
*/
public class CardPile {
  private ArrayList<Card> _cards;

  /**
   *  @brief Constructor
  */
  public CardPile()
  {
    _cards = new ArrayList<Card>();
  }

  /**
   *  @brief Adds new card to pile
  */
  public void addCard(Card card)
  {
    _cards.add(card);
  }

  /**
   *  @brief Draws a card from pile
  */
  public Card drawCard()
  {
    Card temp = _cards.get(_cards.size() - 1);
    _cards.remove(_cards.size()-1);
    return temp;
  }

  /**
   *  @brief Shuffles cards in pile
  */
  public void shuffle()
  {
    Collections.shuffle(_cards);
  }

  /**
   *  @brief Cards getter
  */
  public ArrayList<Card> getCards()           { return _cards; }

  /**
   *  @brief Gets number of cards in pile
  */
  public int getNumberOfCards()               { return _cards.size(); }

  /**
   *  @brief Cards setter
  */
  public void setCards(ArrayList<Card> cards) { _cards = cards; }
}
