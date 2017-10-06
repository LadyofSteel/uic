/**
 *  @brief Puzzle class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.List;
import java.util.Stack;
import java.util.Timer;
import java.util.Arrays;
import java.util.ArrayList;
import java.util.TimerTask;
import java.util.Collections;

import javax.swing.JToggleButton;
import javax.swing.ButtonGroup;
import javax.swing.AbstractAction;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;

/**
 *  @brief Puzzle class
 *
 *  This class consists of the puzzle grid and the auto-solver.
 *  It's a panel that has a 4x4 GridLayout of toggle buttons, which represents
 *  the puzzle grid. The puzzle shuffling, solving, redrawing, and button-switching
 *  is all handled here.
*/
public class Puzzle extends JPanel
{
  private ArrayList<JToggleButton> pieces;  ///< Array of buttons as the puzzle pieces
  private Stack<Integer> undoStack;         ///< Stack for undo command
  private String values;                    ///< String representation of puzzle pieces
  private Solver solver;                    ///< Solver object for auto-solve
  public ObservableValue complexity;        ///< Observable value for puzzle complexity
  public ObservableValue moves;             ///< Observable value for move count

  /**
   *  @brief Constructor
   *
   *  Initializes the pieces in ascending order and sets up a grid layout.
  */
  public Puzzle()
  {
    super( new GridLayout(4,4) );
    values = new String("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
    undoStack = new Stack<>();
    solver = new Solver();
    initGrid();
    complexity = new ObservableValue(0);
    moves = new ObservableValue(0);
  }

  /**
   *  @brief Initializes the grid
   *
   *  Initializes the grid layout with toggle buttons as the puzzle pieces.
  */
  private void initGrid()
  {
    ButtonGroup toggleGroup = new ButtonGroup();
    pieces = new ArrayList<JToggleButton>(16);
    List<String> buttonTexts = Arrays.asList( values.split(" ") );

    for (int i = 0; i < buttonTexts.size(); i++) {
      if ( buttonTexts.get(i).equals("16") )
        pieces.add(new JToggleButton(""));
      else
        pieces.add(new JToggleButton(buttonTexts.get(i)));

      pieces.get(i).addActionListener(new ButtonAction());

      toggleGroup.add( pieces.get(i) );
      this.add( pieces.get(i) );
      pieces.get(i).setSelected(true);
    }
  }

  /**
   *  @brief ButtonAction private class
   *
   *  This private class is used as the action listener for the
   *  toggle buttons in Puzzle.
   *
   *  @sa https://stackoverflow.com/questions/11438048
  */
  private class ButtonAction extends AbstractAction
  {
    public ButtonAction() { super(); }

    @Override
    public void actionPerformed(ActionEvent event)
    {
      JToggleButton pressedButton = (JToggleButton) event.getSource();

      if ( canMove(pressedButton) ) {
        undoStack.push(getEmptyPosition());
        moveToEmptySpot(pressedButton);
        moves.setValue(moves.getValue() + 1);

        checkIfWon();
      }
    }
  } // end of inner private class

  /**
   *  @brief Gets the position of the empty piece
   *
   *  @return integer index of empty piece
  */
  private int getEmptyPosition()
  {
    List<String> buttonTexts = Arrays.asList( values.split(" ") );
    int emptyPosition = buttonTexts.indexOf("16");

    return emptyPosition;
  }

  /**
   *  @brief Checks if selected piece can move
   *
   *  The indexes of the pieces are [0, 1, ... , 15] in a 4x4 grid.
   *
   *  @param JToggleButton the selected piece
   *  @return boolean if selected piece can move
  */
  private boolean canMove(JToggleButton selectedPiece)
  {
    int emptyPosition = getEmptyPosition();
    int selectedPosition = pieces.indexOf(selectedPiece);
    int diff = selectedPosition - emptyPosition;

    switch(diff) {
      case 1:
        if ( (emptyPosition % 4) == 3 ) // if empty is on last column
          break;
        return true;
      case -1:
        if ( (emptyPosition % 4) == 0 ) // if empty is on first column
          break;
        return true;
      case 4:
        return true;
      case -4:
        return true;
      default:
        break;
    }

    pieces.get(emptyPosition).setSelected(true);
    return false;
  }

  /**
   *  @brief Moves the selected piece to the empty spot
   *
   *  The pieces don't really "move", per se, but their texts switch and
   *  the selected button is toggled to create the "move" effect.
   *
   *  @param JToggleButton the selected piece
  */
  private void moveToEmptySpot(JToggleButton selectedPiece)
  {
    ArrayList<String> newValues = new ArrayList<>(Arrays.asList( values.split(" ") ));

    int emptyPosition = newValues.indexOf("16");
    int selectedPosition = pieces.indexOf(selectedPiece);

    String selectedText = selectedPiece.getText();

    newValues.set(emptyPosition, selectedText);
    newValues.set(selectedPosition, "16");

    pieces.get(selectedPosition).setSelected(true);

    updatePieces(newValues);
    redraw();
  }

  /**
   *  @brief Checks if the pieces are in correct sequence
  */
  private void checkIfWon()
  {
    String winSequence = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    if (values.equals(winSequence)) {
      JOptionPane.showMessageDialog( this,
          "You just solved the puzzle! YOU WIN!",
          "Noice!", JOptionPane.PLAIN_MESSAGE );

      moves.setValue(0);
      undoStack.clear();
    }
  }
  
  /**
   *  @brief Updates the pieces to the new given values
   *
   *  @param ArrayList<String> array of new values
  */
  private void updatePieces(ArrayList<String> newValues)
  {
    String newPieces = new String("");

    for (String value : newValues) {
      newPieces = newPieces.concat(value);
      newPieces = newPieces.concat(" ");
    }

    values = newPieces.trim();
  }

  /**
   *  @brief Redraws the grid with the new piece arrangement
  */
  public void redraw()
  {
    List<String> buttonTexts = Arrays.asList(values.split(" "));

    for (int i = 0; i < pieces.size(); i++) {
      if ( buttonTexts.get(i).equals("16") )
        pieces.get(i).setText("");
      else
        pieces.get(i).setText(buttonTexts.get(i));
    }
  }

  /**
   *  @brief Shuffles the pieces to create new puzzle
  */
  public void newPuzzle()
  {
    values = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    // Using temp string to exclude the last element "16" from being shuffled
    String temp = values.substring(0, values.lastIndexOf(" "));
    ArrayList<String> newValues = new ArrayList<>( Arrays.asList(temp.split(" ")) );

    Collections.shuffle(newValues);

    while (!isSolvable(newValues))
      Collections.shuffle(newValues);

    newValues.add("16");
    updatePieces(newValues);

    undoStack.clear();

    // Always set the last piece to be "empty"
    pieces.get(15).setSelected(true);

    moves.setValue(0);
    redraw();
  }

  /**
   *  @brief Resets the pieces to the corrent arrangement
  */
  public void reset()
  {
    values = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    complexity.setValue(0);
    moves.setValue(0);
    undoStack.clear();

    // Always set the last piece to be "empty"
    pieces.get(15).setSelected(true);
    redraw();
  }

  /**
   *  @brief Checks if the current puzzle arrangement is solvable
   *
   *  @param List<String> list of piece values
   *  @return boolean if puzzle is solvable
  */
  private boolean isSolvable(List<String> values)
  {
    int inversionCount = getInversionCount(new ArrayList<String>(values));

    if ( (inversionCount & 1) == 0 )
      return true;
    else
      return false;
  }

  /**
   *  @brief Gets the inversion count for current puzzle arrangement
   *
   *  @param List<String> list of piece values
   *  @return int inversion count
  */
  private int getInversionCount(List<String> values)
  {
    int inversionCount = 0;
    
    for (int i = 15; i > 0; i--) {
      int maxValueIndex = values.indexOf( String.valueOf(i) );

      if (maxValueIndex < 0)
        System.out.println("ERROR: inversion count");

      inversionCount += (values.size() - 1) - maxValueIndex;
      values.remove(maxValueIndex);
    }

    complexity.setValue(inversionCount);
    return inversionCount;
  }

  /**
   *  @brief Undo last move
  */
  public void undo()
  {
    if (!undoStack.empty()) {
      moveToEmptySpot( pieces.get(undoStack.pop()) );
      moves.setValue(moves.getValue() - 1);
    } else {
      System.out.println("Undo stack is empty!");
    }
  }

  /**
   *  @brief Undo all moves
  */
  public void undoAll()
  {
    TimerTask timerTask = new TimerTask() {
      @Override
      public void run()
      {
        if (!undoStack.empty()) {
          undo();
        } else {
          this.cancel();
        }
      }
    };

    Timer timer = new Timer(true);
    timer.scheduleAtFixedRate(timerTask, 0, 300);
  }

  /**
   *  @brief Auto-solves the current puzzle
  */
  public void solve()
  {
    // First check if solution is found
    if (solver.solve(values)) {
      TimerTask timerTask = new TimerTask() {
        @Override
        public void run()
        {
          if (!solver.movementStack.empty()) {
            int moveIndex = solver.movementStack.pop();
            moveToEmptySpot(pieces.get(moveIndex));
          } else {
            this.cancel();
          }
        }
      };

      Timer timer = new Timer(true);
      timer.scheduleAtFixedRate(timerTask, 0, 300);
    }
  }

}
