/**
 *  @brief Game class
 *
 *  CS 342 - Project 1
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.ArrayList;
import java.util.Collections;
import java.io.Console;

/**
 *  @brief Game class
*/
public class Game {
  private ArrayList<Player> _players;
  private CardPile _deck;
  private String _user_name;

  /**
   *  @brief Welcoming prompt
  */
  private void welcome()
  {
    System.out.println("Welcome to Poker - Five Card (by Ammar Subei)");
    _user_name = System.console().readLine("Please enter your name: ");
  }

  /**
   *  @brief Prompts user to enter # opponents
  */
  private int getNumOpponents()
  {
    String input = System.console().readLine("Please enter number of opponents (1 to 3): ");
    int opponents = Integer.parseInt(input);

    while (opponents < 1 || opponents > 3) {
      System.out.println("Invalid input.");
      input = System.console().readLine("Please enter number of opponents (1 to 3): ");
      opponents = Integer.parseInt(input);
    }

    return opponents;
  }

  /**
   *  @brief Initializes the game
  */
  private void init(int num_opponents)
  {
    System.out.println("\nGame is starting");

    _players = new ArrayList<Player>(num_opponents + 1);

    this.initDeck();
    this.initPlayers(num_opponents);
  }

  /**
   *  @brief Initializes the cardpile deck
  */
  private void initDeck()
  {
    _deck = new CardPile();

    for (char suit : "DHCS".toCharArray()) {
      for (int i = 2; i < 15; i++) {
        _deck.addCard(new Card(i, suit));
      }
    }

    _deck.shuffle();
    System.out.println("The deck has been shuffled");
  }

  /**
   *  @brief Initializes the players
  */
  private void initPlayers(int num_opponents)
  {
    _players.add(new User(_user_name));
    for (int i = 0; i < num_opponents; i++)
      _players.add(new Opponent("CPU" + (i+1)));

    Collections.shuffle(_players);
    System.out.println("All players are ready\n");
  }

  /**
   *  @brief Deals cards to all players
  */
  private void dealCards()
  {
    System.out.println("Dealing out the cards");

    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < _players.size(); j++) {
        _players.get(j).addCard(_deck.drawCard());
      }
    }

    System.out.println("Cards have been dealt\n");
  }

  /**
   *  @brief Handles discard and draw phase
   *
   *  It asks every player to play their turn, which consists of choosing what cards to discard
  */
  private void discardAndDraw()
  {
    System.out.println("Starting turns to discard and draw cards");

    for (int i = 0; i < _players.size(); i++) {
      Player player = _players.get(i);
      System.out.println(player.getName() + "'s turn");
      String[] player_input = player.playTurn();

      if (player_input.length == 0 || player_input == null)
        continue;

      for (String card : player_input) {
        player.getHand().discard(card);
        player.getHand().addCard(_deck.drawCard());
      }
    }

    System.out.println("All players have finished their turn\n");
  }

  /**
   *  @brief Prints out each player's hand
   *
   *  The player hands are re-evaluated before printing the info
  */
  private void showHands()
  {
    for (int i = 0; i < _players.size(); i++) {
      Player player = _players.get(i);
      Hand hand = player.getHand();
      hand.evaluate();
      player.showCards();
      player.showEvaluation();
    }
  }

  /**
   *  @brief Computes the results 
   *
   *  It compares each player's hand and keeps track of the highest hand.
   *  It returns the winner's name
  */
  private String results()
  {
    boolean isTie = false;
    Player winner = _players.get(0);

    for (int i = 1; i < _players.size(); i++) {
      Hand hand1 = winner.getHand();
      Hand hand2 = _players.get(i).getHand();

      int result = hand1.compareToHand(hand2);

      if (result > 0) {
        winner = _players.get(i);
        isTie = false;
      } else if (result == 0) {
        isTie = true;
      }
    }

    if (isTie)
      return new String();
    else
      return winner.getName();
  }

  /**
   *  @brief Displays the results
  */
  private void end(String winner)
  {
    if (winner.isEmpty()) {
      System.out.println("We have a tie! Hot diggity!");
    } else {
      System.out.println("Game has ended");
      System.out.println(winner + " is the winner!! YAY!");
    }
  }

  /**
   *  @brief Main function
  */
  public static void main(String a[])
  {
    Game newGame = new Game();

    newGame.welcome();
    int numOfOpponents = newGame.getNumOpponents();

    newGame.init(numOfOpponents);

    newGame.dealCards();
    newGame.discardAndDraw();

    newGame.showHands();
    String winner = newGame.results();

    newGame.end(winner);
  }
}
