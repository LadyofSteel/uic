/**
 *  @brief Card Pile class header
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.Vector;

public class CardPile {
  private Vector<Card> _cards;

  public CardPile()
  {}

  public Vector<Card> getCards()            { return _cards; }
  public void setCards(Vector<Card> cards)  { _cards = cards; }
  public void shuffle() {}
}
