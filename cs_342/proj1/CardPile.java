/**
 *  @brief Card Pile class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.Vector;
import java.util.Collections;

public class CardPile {
  private Vector<Card> _cards;

  public CardPile()
  {
    _cards = new Vector<Card>();
  }

  public void addCard(Card card)
  {
    _cards.add(card);
  }

  public Card drawCard()
  {
    Card temp = _cards.lastElement();
    _cards.remove(_cards.size()-1);
    return temp;
  }

  public void shuffle()
  {
    Collections.shuffle(_cards);
  }

  // Getter(s) & setter(s)
  public Vector<Card> getCards()            { return _cards; }
  public int getNumberOfCards()             { return _cards.size(); }
  public void setCards(Vector<Card> cards)  { _cards = cards; }
}
