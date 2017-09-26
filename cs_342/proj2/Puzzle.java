import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Puzzle extends JPanel implements ActionListener
{
  private JToggleButton buttons[];
  private final String buttonNames[] = 
  { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", ""};

  public Puzzle()
  {
    super( new GridLayout(4,4) );

    ButtonGroup group = new ButtonGroup();
    buttons = new JToggleButton[ buttonNames.length ];

    for (int count = 0; count < buttonNames.length; count++) {
      buttons[count] = new JToggleButton( buttonNames[count] );

      group.add( buttons[count] );
      this.add( buttons[count] );
      buttons[count].setSelected(true);
    }
  }

  public void actionPerformed(ActionEvent event)
  {
  }
}
