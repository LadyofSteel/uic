/**
 *  @brief Tuple class file
 *
 *  CS 342 - Project 2
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
*/

import java.util.Collection;

/**
 *  @brief Tuple class
 *
 *  This is a custom class to implement a tuple
 *  data structure. The tuple components (First & Second)
 *  are immutable.
*/
public class Tuple<F, S>
{
  private final F first;  ///< First element of type F
  private final S second; ///< Second element of type S

  /**
   *  @brief Constructor
  */
  public Tuple(F first, S second)
  {
    this.first = first;
    this.second = second;
  }

  /**
   *  @brief First element getter
   *
   *  @return first element
  */
  public F getFirst()   { return first; }

  /**
   *  @brief Second element getter
   *
   *  @return second element
  */
  public S getSecond()  { return second; }
}
