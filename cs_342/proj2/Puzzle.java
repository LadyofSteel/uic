/**
 *  @brief Puzzle class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.List;
import java.util.Arrays;
import java.util.ArrayList;
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
  private ArrayList<JToggleButton> buttons;
  private String puzzlePieces;

  public Puzzle()
  {
    super( new GridLayout(4,4) );
    puzzlePieces = new String("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16");
    initGrid();
  }

  private void initGrid()
  {
    ButtonGroup toggleGroup = new ButtonGroup();
    buttons = new ArrayList<JToggleButton>(16);
    List<String> buttonTexts = Arrays.asList( puzzlePieces.split(" ") );

    for (int i = 0; i < buttonTexts.size(); i++) {
      if ( buttonTexts.get(i).equals("16") )
        buttons.add(new JToggleButton(""));
      else
        buttons.add(new JToggleButton(buttonTexts.get(i)));

      buttons.get(i).addActionListener(new ButtonAction());

      toggleGroup.add( buttons.get(i) );
      this.add( buttons.get(i) );
      buttons.get(i).setSelected(true);
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
    public ButtonAction()
    {
      super();
    }
        
    @Override
    public void actionPerformed(ActionEvent event)
    {
      JToggleButton pressedButton = (JToggleButton) event.getSource();

      if ( canMove(pressedButton) )
        moveToEmptySpot(pressedButton);
    }
  } // end of inner private class

  private boolean canMove(JToggleButton pressedButton)
  {
    List<String> buttonTexts = Arrays.asList( puzzlePieces.split(" ") );

    int emptyPosition = buttonTexts.indexOf("16");
    int buttonPosition = buttons.indexOf(pressedButton);
    int diff = buttonPosition - emptyPosition;

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

    buttons.get(emptyPosition).setSelected(true);
    return false;
  }

  private void moveToEmptySpot(JToggleButton pressedButton)
  {
    ArrayList<String> buttonValues = new ArrayList<>(Arrays.asList( puzzlePieces.split(" ") ));

    int emptyPosition = buttonValues.indexOf("16");
    int buttonPosition = buttons.indexOf(pressedButton);

    String buttonText = pressedButton.getText();

    buttonValues.set(emptyPosition, buttonText);
    buttonValues.set(buttonPosition, "16");

    updatePieces(buttonValues);
    redraw();

    checkIfWon();
  }

  private void checkIfWon()
  {
    String winSequence = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    if (puzzlePieces.equals(winSequence)) {
      JOptionPane.showMessageDialog( this,
          "You just solved the puzzle! YOU WIN!",
          "Noice!", JOptionPane.PLAIN_MESSAGE );
    }
  }
  
  private void updatePieces(ArrayList<String> values)
  {
    String newPieces = new String("");

    for (String value : values) {
      newPieces = newPieces.concat(value);
      newPieces = newPieces.concat(" ");
    }

    puzzlePieces = newPieces.trim();
  }

  public void redraw()
  {
    List<String> buttonTexts = Arrays.asList(puzzlePieces.split(" "));

    for (int i = 0; i < buttons.size(); i++) {
      if ( buttonTexts.get(i).equals("16") )
        buttons.get(i).setText("");
      else
        buttons.get(i).setText(buttonTexts.get(i));
    }
  }

  public void shuffle()
  {
    puzzlePieces = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    // Using temp string to exclude the last element "16" from being shuffled
    String temp = puzzlePieces.substring(0, puzzlePieces.lastIndexOf(" "));
    ArrayList<String> values = new ArrayList<>( Arrays.asList(temp.split(" ")) );

    Collections.shuffle(values);

    while (!isSolvable(values))
      Collections.shuffle(values);

    values.add("16");
    updatePieces(values);

    // Always set the last piece to be "empty"
    buttons.get(15).setSelected(true);
    redraw();
  }

  public void reset()
  {
    puzzlePieces = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";

    // Always set the last piece to be "empty"
    buttons.get(15).setSelected(true);
    redraw();
  }

  private boolean isSolvable(List<String> values)
  {
    int inversionCount = getInversionCount(new ArrayList<String>(values));

    System.out.println(inversionCount);

    if ( (inversionCount & 1) == 0 )
      return true;
    else
      return false;
  }

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
    
    return inversionCount;
  }
}
