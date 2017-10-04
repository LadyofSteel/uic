/**
 *  @brief ObservableValue class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.Observable;

/**
 *  @brief ObservableValue class
 *
 *  This class extends the Observable class so that the
 *  MainWindow can automatically detect if this ObservableValue
 *  has changed. This class is used to detect any changes in the
 *  puzzle's move count and complexity.
*/
public class ObservableValue extends Observable
{
  private int value;  ///< Integer value to be "observed"


  /**
   *  @brief Constructor
  */
  public ObservableValue(int value)
  {
    super();
    this.value = value;
  }

  /**
   *  @brief Value getter
   *
   *  @return integer value
  */
  public int getValue()  { return value; }

  /**
   *  @brief Value setter
   *
   *  @param int new value
  */
  public void setValue(int newValue)
  {
    value = newValue;
    
    // Tell the observer that the value changed
    setChanged();
    notifyObservers();
  }
}
