import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MainWindow extends JFrame implements ActionListener
{
  private Container container;
  private Puzzle puzzleGrid;
  private JMenuBar menu;

  // set up GUI
  public MainWindow()
  {
    super( "Puzzle Game" );
    initMenuBar();

    puzzleGrid = new Puzzle();

    // get content pane and set its layout
    container = getContentPane();
    container.setLayout( new BorderLayout() );
    this.setJMenuBar(menu);

    container.add( puzzleGrid, BorderLayout.CENTER );
    setSize( 400, 400 );
    setVisible( true );

  } // end constructor GridLayoutDemo

  private void initMenuBar()
  {
    menu = new JMenuBar();

    JMenu fileMenu = new JMenu("File");
    fileMenu.setMnemonic('F');

    JMenuItem newItem = new JMenuItem("New");
    newItem.setMnemonic('N');
    JMenuItem exitItem = new JMenuItem("Exit");
    exitItem.setMnemonic('E');

    newItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            JOptionPane.showMessageDialog(MainWindow.this,
                "BLABLABLA",
                "NEW", JOptionPane.PLAIN_MESSAGE);
          }
        });

    exitItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            System.exit(0);
          }
        });

    JMenu editMenu = new JMenu("Edit");
    editMenu.setMnemonic('E');

    JMenuItem undoItem = new JMenuItem("Undo");
    undoItem.setMnemonic('U');
    JMenuItem undoAllItem = new JMenuItem("Undo All");
    undoAllItem.setMnemonic('A');
    JMenuItem solveItem = new JMenuItem("Solve");
    solveItem.setMnemonic('S');
    JMenuItem shuffleItem = new JMenuItem("Shuffle");
    shuffleItem.setMnemonic('H');

    fileMenu.add(newItem);
    fileMenu.add(exitItem);
    editMenu.add(undoItem);
    editMenu.add(undoAllItem);
    editMenu.add(solveItem);
    editMenu.add(shuffleItem);

    menu.add(fileMenu);
    menu.add(editMenu);
  }

  // handle button events by toggling between layouts
  public void actionPerformed( ActionEvent event )
  { 
    container.validate();
  }

  public static void main( String args[] )
  {
    MainWindow application = new MainWindow();
    application.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
  } 

} // end class GridLayoutDemo
