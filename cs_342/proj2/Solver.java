/**
 *  @brief Solver class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.Collections;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Arrays;
import java.util.Stack;
import java.util.List;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 *  @brief Solver class
 *
 *  Handles the solving of given puzzle.
*/
public class Solver
{
  public Stack<Integer> movementStack;  ///< Stack of movement values

  /**
   *  @brief Constructor
  */
  public Solver()
  {
    movementStack = new Stack<>();
  }

  /**
   *  @brief Solves the given puzzle arrangement
   *
   *  @param String puzzle arrangement to solve
   *  @return solve successful
  */
  public boolean solve(String puzzle)
  {
    String winSequence = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    HashSet<String> visited = new HashSet<>();
    ArrayList<Tuple> queue = new ArrayList<>();

    queue.add( new Tuple<String,Integer>(puzzle, -1) );

    int i = 0;
    while ( i < queue.size() ) {
      Tuple<String, Integer> current = queue.get(i);
      String currentArrangement = current.getFirst();

      // If reached win sequence
      if (currentArrangement.equals(winSequence))
        break;

      // If already visited
      if (visited.contains(currentArrangement)) {
        i++;
        continue;
      }

      for (String arrangement : getPossibleArrangements(currentArrangement)) {
        queue.add(new Tuple<String,Integer>(arrangement, i));
      }

      i++;
      visited.add(currentArrangement);
    }

    // No solution found
    if (i == queue.size())
      return false;

    int nextArrangement = (Integer) queue.get(i).getSecond();
    while (nextArrangement != -1) {
      int moveIndex = getMoveIndex( (String) queue.get(i).getFirst(),
          (String) queue.get(nextArrangement).getFirst() );

      movementStack.push(moveIndex);
      i = nextArrangement;
      nextArrangement = (Integer) queue.get(i).getSecond();
    }

    return true;
  }

  /**
   *  @brief Gets the move to get from one arrangement to another
   *
   *  @param String puzzle arrangement to move from
   *  @param String puzzle arrangement to move to
   *  @return integer value of move
  */
  private int getMoveIndex(String fromArrangement, String toArrangement)
  {
    if (fromArrangement.equals(toArrangement) ||
        fromArrangement == null ||
        toArrangement == null)
      return -1;

    List<String> from = Arrays.asList( fromArrangement.split(" ") );
    List<String> to = Arrays.asList( toArrangement.split(" ") );

    int index;
    for (index = 0; index < from.size() && index < to.size(); index++) {

      if ( !from.get(index).equals(to.get(index)) )
        if (from.get(index).equals("16"))
          break;
    }

    if (index < from.size() || index < to.size())
      return index;

    return -1;
  }

  /**
   *  @brief Gets all possible arrangements
   *
   *  @param String current arrangement
   *  @return ArrayList of possible arrangements
  */
  private ArrayList<String> getPossibleArrangements(String current)
  {
    ArrayList<String> arrangements = new ArrayList<>();

    List<String> pieces = Arrays.asList( current.split(" ") );

    int emptyPosition = pieces.indexOf("16");

    if (emptyPosition % 4 == 3) { // Last column
      ArrayList<String> state1 = new ArrayList<>(pieces);
      ArrayList<String> state2 = new ArrayList<>(pieces);

      Collections.swap(state1, emptyPosition, emptyPosition-1);

      if (emptyPosition == 3) { // Top right corner
        Collections.swap(state2, emptyPosition, emptyPosition+4);
      } else if (emptyPosition == 15) { // Botton right corner
        Collections.swap(state2, emptyPosition, emptyPosition-4);
      } else {
        Collections.swap(state2, emptyPosition, emptyPosition-4);

        ArrayList<String> state3 = new ArrayList<>(pieces);
        Collections.swap(state3, emptyPosition, emptyPosition+4);

        String string3 = listToString(state3);
        arrangements.add(string3);
      }

      String string1 = listToString(state1);
      String string2 = listToString(state2);
      arrangements.add(string1);
      arrangements.add(string2);
    } else if (emptyPosition % 4 == 0) { // First column
      ArrayList<String> state1 = new ArrayList<>(pieces);
      ArrayList<String> state2 = new ArrayList<>(pieces);

      Collections.swap(state1, emptyPosition, emptyPosition+1);

      if (emptyPosition == 0) { // Top left corner
        Collections.swap(state2, emptyPosition, emptyPosition+4);
      } else if (emptyPosition == 12) { // Bottom left corner
        Collections.swap(state2, emptyPosition, emptyPosition-4);
      } else {
        Collections.swap(state2, emptyPosition, emptyPosition-4);

        ArrayList<String> state3 = new ArrayList<>(pieces);
        Collections.swap(state3, emptyPosition, emptyPosition+4);

        String string3 = listToString(state3);
        arrangements.add(string3);
      }

      String string1 = listToString(state1);
      String string2 = listToString(state2);
      arrangements.add(string1);
      arrangements.add(string2);
    } else if (emptyPosition - 4 < 0) { // First row
      ArrayList<String> state1 = new ArrayList<>(pieces);
      ArrayList<String> state2 = new ArrayList<>(pieces);
      ArrayList<String> state3 = new ArrayList<>(pieces);

      Collections.swap(state1, emptyPosition, emptyPosition-1);
      Collections.swap(state2, emptyPosition, emptyPosition+1);
      Collections.swap(state3, emptyPosition, emptyPosition+4);

      String string1 = listToString(state1);
      String string2 = listToString(state2);
      String string3 = listToString(state3);
      arrangements.add(string1);
      arrangements.add(string2);
      arrangements.add(string3);
    } else if (emptyPosition + 4 > 15) {
      ArrayList<String> state1 = new ArrayList<>(pieces);
      ArrayList<String> state2 = new ArrayList<>(pieces);
      ArrayList<String> state3 = new ArrayList<>(pieces);

      Collections.swap(state1, emptyPosition, emptyPosition-1);
      Collections.swap(state2, emptyPosition, emptyPosition+1);
      Collections.swap(state3, emptyPosition, emptyPosition-4);

      String string1 = listToString(state1);
      String string2 = listToString(state2);
      String string3 = listToString(state3);
      arrangements.add(string1);
      arrangements.add(string2);
      arrangements.add(string3);
    } else {
      ArrayList<String> state1 = new ArrayList<>(pieces);
      ArrayList<String> state2 = new ArrayList<>(pieces);
      ArrayList<String> state3 = new ArrayList<>(pieces);
      ArrayList<String> state4 = new ArrayList<>(pieces);

      Collections.swap(state1, emptyPosition, emptyPosition-1);
      Collections.swap(state2, emptyPosition, emptyPosition+1);
      Collections.swap(state3, emptyPosition, emptyPosition-4);
      Collections.swap(state4, emptyPosition, emptyPosition+4);

      String string1 = listToString(state1);
      String string2 = listToString(state2);
      String string3 = listToString(state3);
      String string4 = listToString(state4);

      arrangements.add(string1);
      arrangements.add(string2);
      arrangements.add(string3);
      arrangements.add(string4);
    }

    return arrangements;
  }

  /**
   *  @brief Converts ArrayList to string
   *
   *  @param ArrayList<String> input ArrayList
   *  @return String result
  */
  private String listToString(ArrayList<String> input)
  {
    String newPieces = new String("");

    for (String value : input) {
      newPieces = newPieces.concat(value);
      newPieces = newPieces.concat(" ");
    }

    return newPieces.trim();
  }
}
