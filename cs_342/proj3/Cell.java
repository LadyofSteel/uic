/**
 *  @brief Cell class file
 *
 *  CS 342 - Project 3
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

import javax.swing.JButton;
import javax.swing.ButtonGroup;
import javax.swing.AbstractAction;

import java.awt.event.ActionEvent;

/**
 *  @brief Cell class
 *
 *  This class represents a single cell on the Sudoku grid.
 *  Every cell keeps track of its candidates list and x-y coordinates.
*/
public class Cell extends JButton
{
  private int value;        ///< Cell integer value
  private int xPosition;    ///< Cell x coordinate
  private int yPosition;    ///< Cell y coordinate
  private boolean isFixed;  ///< Cell fixed status (i.e its value cannot be changed)

  /**
   *  @brief Constructor 1
   *
   *  @param int x position
   *  @param int y position
  */
  public Cell(int x, int y)
  {
    super("");
    setCellValue(0);
    setXPosition(x);
    setYPosition(y);
    setFixed(false);
  }

  /**
   *  @brief Constructor 2
   *
   *  @param int x position
   *  @param int y position
   *  @param int new cell value
   *  @param boolean fixed cell
  */
  public Cell(int x, int y, int newValue, boolean fixed)
  {
    super( String.valueOf(newValue) );
    setCellValue(newValue);
    setXPosition(x);
    setYPosition(y);
    setFixed(fixed);
  }

  /**
   *  @brief Getter for cell value
   *
   *  @return integer cell value
  */
  public int getCellValue()
  {
    return value;
  }

  /**
   *  @brief Getter for x-position
   *
   *  @return integer position value
  */
  public int getXPosition()
  {
    return xPosition;
  }

  /**
   *  @brief Getter for y-position
   *
   *  @return integer position value
  */
  public int getYPosition()
  {
    return yPosition;
  }

  /**
   *  @brief Checks if cell is fixed
   *
   *  @return boolean cell is fixed
  */
  public boolean isFixed()
  {
    return isFixed;
  }

  /**
   *  @brief Setter for cell value
   *
   *  @param int new value
  */
  public void setCellValue(int newValue)
  {
    value = newValue;

    if (newValue > 0)
      this.setText(String.valueOf(newValue));
    else
      this.setText("");
  }

  /**
   *  @brief Setter for x position
   *
   *  @param int new x position
  */
  public void setXPosition(int newValue)
  {
    xPosition = newValue;
  }

  /**
   *  @brief Setter for y position
   *
   *  @param int new y position
  */
  public void setYPosition(int newValue)
  {
    yPosition = newValue;
  }

  /**
   *  @brief Setter for cell fixed status
   *
   *  @param boolean fixed status
  */
  public void setFixed(boolean fixed)
  {
    isFixed = fixed;
  }

  /**
   *  @brief Check if cell is empty
   *
   *  @return boolean cell is empty
  */
  public boolean isEmpty()
  {
    return getCellValue() == 0;
  }
}
