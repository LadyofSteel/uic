import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MainWindow extends JFrame implements ActionListener
{
  private Container container;
  private JMenuBar menu;
  private Puzzle puzzleGrid;

  // Set up GUI
  public MainWindow()
  {
    super("Puzzle Game" );
    initMenuBar();

    puzzleGrid = new Puzzle();

    // Get content pane and set its layout
    container = getContentPane();
    container.setLayout( new BorderLayout() );
    this.setJMenuBar(menu);

    container.add( puzzleGrid, BorderLayout.CENTER );

    setSize(400,400);
    setVisible(true);
  }

  private void initMenuBar()
  {
    menu = new JMenuBar();

    JMenu fileMenu = new JMenu("File");
    fileMenu.setMnemonic('F');

    JMenuItem shuffleItem = new JMenuItem("Shuffle");
    shuffleItem.setMnemonic('H');

    shuffleItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            puzzleGrid.shuffle();
          }
        });

    JMenuItem solveItem = new JMenuItem("Solve");
    solveItem.setMnemonic('S');
    JMenuItem exitItem = new JMenuItem("Exit");
    exitItem.setMnemonic('E');

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

    JMenu helpMenu = new JMenu("Help");
    helpMenu.setMnemonic('H');

    JMenuItem instructionsItem = new JMenuItem("Instructions");
    instructionsItem.setMnemonic('I');
    JMenuItem aboutItem = new JMenuItem("About...");
    aboutItem.setMnemonic('A');
    JMenuItem licenseItem = new JMenuItem("License");
    licenseItem.setMnemonic('L');

    fileMenu.add(shuffleItem);
    fileMenu.add(solveItem);
    fileMenu.add(exitItem);
    editMenu.add(undoItem);
    editMenu.add(undoAllItem);
    helpMenu.add(instructionsItem);
    helpMenu.add(aboutItem);
    helpMenu.add(licenseItem);

    menu.add(fileMenu);
    menu.add(editMenu);
    menu.add(helpMenu);
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

}
