/**
 *  @brief Card class
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

  public Card(String card)
  {
    String rank_str = card.substring(0, card.length() -1);
    int rank;

    switch(rank_str) {
      case "J":
        rank = 11;
        break;
      case "Q":
        rank = 12;
        break;
      case "K":
        rank = 13;
        break;
      case "A":
        rank = 14;
        break;
      default:
        rank = Integer.parseInt(rank_str);
        break;
    }

    setRank(rank);
    setSuit(card.charAt(card.length() - 1));
  }

  public String getCard() 
  {
    String card = "";
    int rank = getRank();

    switch(rank) {
      case 11:
        card += "J";
        break;
      case 12:
        card += "Q";
        break;
      case 13:
        card += "K";
        break;
      case 14:
        card += "A";
        break;
      default:
        card += rank;
        break;
    }

    return card + getSuit();
  }

  public int getRank()            { return _rank; }
  public char getSuit()           { return _suit; }
  public void setRank(int rank)   { _rank = rank; }
  public void setSuit(char suit)  { _suit = suit; }
}
