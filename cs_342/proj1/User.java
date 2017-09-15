/**
 *  @brief User class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.ArrayList;
import java.util.Iterator;
import java.io.Console;

/**
 *  @brief User class
*/
public class User extends Player {
  /**
   *  @brief Constructor
  */
  public User(String name)
  {
    super(name);
  }
  
  /**
   *  @brief Play turn
   *
   *  Instructs the user to play his/her turn of the game
  */
  public String[] playTurn()
  {
    System.out.println("\nAlright, you're up! Here are your cards:");

    Hand hand = this.getHand();
    hand.evaluate();

    this.showCards();

    String input;
    String[] discard_cards;

    boolean valid_input = false;
    while (true) {
      input = System.console().readLine("Choose the cards you wish to discard (e.g 4H 10C KS): ");

      if (input.isEmpty())
        return new String[0];

      discard_cards = input.split(" ");

      if (hand.getCards().get(0).getRank() != 14) {
        if (discard_cards.length < 4)
          return discard_cards;
      } else {
        return discard_cards;
      }

      System.out.println("Invalid input! Stop trying to break the game...");
    }
  }
}

