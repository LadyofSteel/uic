import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class MainWindow extends JFrame implements ActionListener
{
  private Container container;
  private Puzzle puzzleGrid;

  // set up GUI
  public MainWindow()
  {
    super( "Puzzle Game" );

    // set up layouts
    puzzleGrid = new Puzzle();

    // get content pane and set its layout
    container = getContentPane();
    container.setLayout( new BorderLayout() );

    container.add( puzzleGrid, BorderLayout.CENTER );
    setSize( 400, 400 );
    setVisible( true );

  } // end constructor GridLayoutDemo

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
