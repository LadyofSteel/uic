/**
 *  @brief MainWindow class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JMenu;

import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.BorderLayout;

import java.util.Observer;
import java.util.Observable;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 *  @brief MainWindow class
*/
public class MainWindow extends JFrame implements Observer
{
  private Container container;    ///< Java container object
  private JMenuBar menu;          ///< Menu bar object
  private Puzzle puzzleGrid;      ///< Puzzle grid object
  private JLabel complexityLabel; ///< Text label for puzzle complexity
  private JLabel moveCountLabel;  ///< Text label for user move count

  @Override
  public void update(Observable o, Object arg)
  {
    complexityLabel.setText( String.valueOf(puzzleGrid.complexity.getValue()) );
    moveCountLabel.setText( String.valueOf(puzzleGrid.moves.getValue()) );
  }

  /**
   *  @brief Constructor
   *
   *  First initializes the menu bar with all its items
   *  and action listeners. Then sets up the UI labels and
   *  the puzzle grid.
  */
  public MainWindow()
  {
    super("Puzzle Game" );
    initMenuBar();

    JPanel labelsPanel = new JPanel(new FlowLayout());
    JLabel label1 = new JLabel("Puzzle complexity:");
    JLabel label2 = new JLabel("Move count:");
    complexityLabel = new JLabel("0");
    moveCountLabel = new JLabel("0");

    labelsPanel.add(label1);
    labelsPanel.add(complexityLabel);
    labelsPanel.add(label2);
    labelsPanel.add(moveCountLabel);

    puzzleGrid = new Puzzle();
    puzzleGrid.complexity.addObserver(this);
    puzzleGrid.moves.addObserver(this);

    // Get content pane and set its layout
    container = getContentPane();
    container.setLayout( new BorderLayout() );
    this.setJMenuBar(menu);

    container.add( labelsPanel, BorderLayout.PAGE_START );
    container.add( puzzleGrid, BorderLayout.CENTER );

    setSize(400,400);
    setVisible(true);
  }

  /**
   *  @brief Initializes menu bar
   *
   *  Adds all necessary menubar items and their action listeners.
  */
  private void initMenuBar()
  {
    menu = new JMenuBar();

    JMenu fileMenu = new JMenu("File");
    fileMenu.setMnemonic('F');

    JMenuItem newPuzzleItem = new JMenuItem("New Puzzle");
    newPuzzleItem.setMnemonic('N');
    newPuzzleItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            puzzleGrid.shuffle();
          }
        });

    JMenuItem resetItem = new JMenuItem("Reset");
    resetItem.setMnemonic('R');
    resetItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            puzzleGrid.reset();
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
    undoItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            puzzleGrid.undo();
          }
        });

    JMenuItem undoAllItem = new JMenuItem("Undo All");
    undoAllItem.setMnemonic('A');
    undoAllItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            puzzleGrid.undoAll();
          }
        });

    JMenu helpMenu = new JMenu("Help");
    helpMenu.setMnemonic('H');

    JMenuItem instructionsItem = new JMenuItem("Instructions");
    instructionsItem.setMnemonic('I');
    instructionsItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            JOptionPane.showMessageDialog( MainWindow.this,
                "TODO: instructions here",
                "Instructions", JOptionPane.PLAIN_MESSAGE );
          }
        });

    JMenuItem aboutItem = new JMenuItem("About...");
    aboutItem.setMnemonic('A');
    aboutItem.addActionListener(
        new ActionListener() {
          public void actionPerformed(ActionEvent event)
          {
            JOptionPane.showMessageDialog( MainWindow.this,
                "TODO: about stuff here",
                "About", JOptionPane.PLAIN_MESSAGE );
          }
        });

    fileMenu.add(newPuzzleItem);
    fileMenu.add(resetItem);
    fileMenu.add(solveItem);
    fileMenu.add(exitItem);
    editMenu.add(undoItem);
    editMenu.add(undoAllItem);
    helpMenu.add(instructionsItem);
    helpMenu.add(aboutItem);

    menu.add(fileMenu);
    menu.add(editMenu);
    menu.add(helpMenu);
  }

  /**
   *  @brief Main function
  */
  public static void main( String args[] )
  {
    MainWindow application = new MainWindow();
    application.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
  } 
}
