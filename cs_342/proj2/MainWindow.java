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
import javax.swing.JMenu;

import java.awt.Container;
import java.awt.BorderLayout;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 *  @brief MainWindow class
*/
public class MainWindow extends JFrame
{
  private Container container;
  private JMenuBar menu;
  private Puzzle puzzleGrid;

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

    fileMenu.add(newPuzzleItem);
    fileMenu.add(resetItem);
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

  public static void main( String args[] )
  {
    MainWindow application = new MainWindow();
    application.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
  } 
}
