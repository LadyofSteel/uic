/**
 *  @brief Player class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.ArrayList;

/**
 *  @brief Player class
*/
public abstract class Player {
  private Hand _player_hand;
  private String _name;
  
  /**
   *  @brief Constructor
  */
  public Player(String name)
  {
    _name = name;
    _player_hand = new Hand();
  }

  /**
   *  @brief Adds new card to player
   *
   *  This is used when the player is being dealt some cards
  */
  public void addCard(Card card)
  {
    _player_hand.addCard(card);
  }

  /**
   *  @brief Displays the player's cards
   *
   *  It prints the player's name, followed by the sorted cards in his hand
  */
  public void showCards()
  {
    ArrayList<Card> cards = this.getHand().getCards();

    System.out.println("Player " + this.getName() + ":");
    for (int i = 0; i < cards.size(); i++) {
      System.out.println("(" + (i+1) + ")  " + cards.get(i).getCard());
    }
  }

  /**
   *  @brief Displays the hand evaluation
  */
  public void showEvaluation()
  {
    Hand hand = this.getHand();
    System.out.println(hand.getEvaluation().getName() + "\n");
  }

  /**
   *  @brief Abstract method to play turn
   *
   *  This function should be implemented in User and Opponent classes
  */
  public abstract String[] playTurn();

  /**
   *  @brief Current hand getter
  */
  public Hand getHand()   { return _player_hand; }

  /**
   *  @brief Player name getter
  */
  public String getName() { return _name; }
}
