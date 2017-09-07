/**
 *  @brief Card class header
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

public class Card {
  private int _rank;
  private char _suit;

  public Card(int rank, char suit)
  {
    setRank(rank);
    setSuit(suit);
  }

  public int getRank()            { return _rank; }
  public char getSuit()           { return _suit; }
  public void setRank(int rank)   { _rank = rank; }
  public void setSuit(char suit)  { _suit = suit; }

}
