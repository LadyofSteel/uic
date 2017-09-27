import java.util.ArrayList;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Puzzle extends JPanel
{
  private JToggleButton buttons[];
  private ArrayList<Integer> puzzlePieces;

  public Puzzle()
  {
    super( new GridLayout(4,4) );
    initPieces();
    initGrid();
  }

  private void initPieces()
  {
    puzzlePieces = new ArrayList<Integer>();

    for (int i = 1; i < 17; i++)
      puzzlePieces.add(i);
  }

  private void initGrid()
  {
    ButtonGroup toggleGroup = new ButtonGroup();
    buttons = new JToggleButton[ puzzlePieces.size() ];

    for (int i = 0; i < puzzlePieces.size(); i++) {
      if (puzzlePieces.get(i) == 16)
        buttons[i] = new JToggleButton("");
      else
        buttons[i] = new JToggleButton( String.valueOf(puzzlePieces.get(i)) );

      toggleGroup.add( buttons[i] );
      this.add( buttons[i] );
      buttons[i].setSelected(true);
    }
  }
}
