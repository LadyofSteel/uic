/**
 *  @brief Game class file
 *
 *  CS 342 - Project 3
 *  Univeristy of Illinois at Chicago
 *
 *  @author Ammar Subei
 *  @author Daniel Kloza
*/

import java.io.*;
import java.nio.file.Files;
import java.nio.charset.Charset;

import java.util.List;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

import javax.swing.JFileChooser;

/**
 *  @brief Game class
 *
 *  This class handles the general game logic for Sudoku.
*/
public class Game
{
  public ArrayList< List<Cell> > cells; ///< 2D array of cells for the puzzle
  public Candidates candidates;         ///< Candidates object

  /**
   *  @brief Constructor
  */
  public Game()
  {
    cells = new ArrayList< List<Cell> >();
    candidates = new Candidates();

    // Init the 9x9 cells
    for (int i = 0; i < 9; i++) {
      ArrayList<Cell> row = new ArrayList<Cell>();

      for (int j = 0; j < 9; j++)
        row.add(new Cell(j, i));

      cells.add(row);
    }
  }

  /**
   *  @brief Checks if the puzzle has been solved
   *
   *  @return boolean puzzle is solved
  */
  public boolean isSolved()
  {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        ArrayList<Integer> cellCandidates = candidates.getCandidates(i, j);

        if ( !cellCandidates.isEmpty() )
          return false;
      }
    }

    return true;
  }

  /**
   *  @brief Checks if the input value is correct
   *
   *  Given the (x,y) position of a cell, this function checks if
   *  the input value is correct (i.e is part of the candidates list).
   *
   *  @param int x position
   *  @param int y position
   *  @param int value to check
   *  @return boolean value is correct
  */
  public boolean isInputCorrect(int x, int y, int value)
  {
    ArrayList<Integer> list = candidates.getCandidates(x, y);
    if (list.isEmpty())
      return true;

    return list.contains(value);
  }

  /**
   *  @brief Loads a user input file
   *
   *  Pops up a dialog box for the user to select a text file to load.
   *
   *  @return boolean file load successful
  */
  public boolean loadFile()
  {
    JFileChooser fileChooser = new JFileChooser();
    if ( fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION ) {
      File file = fileChooser.getSelectedFile();
      ArrayList<Integer> values = new ArrayList<Integer>();

      try {
        Scanner scanner = new Scanner(file);

        while (scanner.hasNextInt())
          values.add(scanner.nextInt());
      } catch (FileNotFoundException e) {
        System.out.println("ERROR: File does not exist!");
        return false;
      }

      // First clear out all cells
      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          Cell cell = cells.get(j).get(i);

          cell.setCellValue(0);
          cell.setFixed(false);
        }
      }

      // Then reset candidates object.
      // Assign to null to implicitly call GC
      candidates = null;
      candidates = new Candidates();

      int i = 0;
      while (i < values.size()) {
        int yPos = values.get(i++) - 1;
        int xPos = values.get(i++) - 1;
        int value = values.get(i++);

        cells.get(xPos).get(yPos).setCellValue(value);
        cells.get(xPos).get(yPos).setFixed(true);
      }

      candidates.updateCell(cells);
      return true;
    }

    return false;
  }

  /**
   *  @brief Saves the current puzzle to user specified file
   *
   *  Pops up a dialog box for the user to select a text file to save the
   *  current Sudoku puzzle to.
   *
   *  @return boolean file save successful
  */
  public boolean saveFile()
  {
    JFileChooser fileChooser = new JFileChooser();
    if ( fileChooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION ) {
      File file = fileChooser.getSelectedFile();
      ArrayList<String> lines = new ArrayList<String>();

      for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
          String value = cells.get(j).get(i).getText();

          if (!value.isEmpty()) {
            lines.add(String.format("%d %d %s", i+1, j+1, value));
          }
        }
      }

      try {
        Files.write(file.toPath(), lines, Charset.forName("UTF-8"));
      } catch (IOException e) {
        System.out.println("ERROR: Unable to write to file!");
        return false;
      }

      return true;
    }

    return false;
  }

  /**
   *  @brief Performs Single solving algorithm
   *   
   *  @return boolean resolved a cell
  */
  public boolean solveSingle()
  {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (cells.get(j).get(i).isEmpty()) {
          ArrayList<Integer> cellCandidates = candidates.getCandidates(i, j);

          if (cellCandidates.size() == 1) {
            int singleValue = cellCandidates.get(0) + 1;
            cells.get(j).get(i).setCellValue(singleValue);
            candidates.updateCell(i, j, singleValue);
            return true;
          }
        }
      }
    }

    return false;
  }

  /**
   *  @brief Performs Hidden Single solving algorithm
   *   
   *  @return boolean resolved a cell
  */
  public boolean solveHiddenSingle()
  {
    ArrayList< List<Integer> > groupCandidates = new ArrayList< List<Integer> >();

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (cells.get(j).get(i).isEmpty()) {

          // Check candidates for entire row
          int row = i;
          for (int col = 0; col < 9; col++) {
            if ( cells.get(col).get(row).isEmpty() ) {
              groupCandidates.add(candidates.getCandidates(row, col));
            }
          }

          // If we find a hidden single among the cells in the row,
          // figure out which cell had it and update that cell.
          int singleValue = hasHiddenSingle(groupCandidates);
          if (singleValue != 0) {
            for (int col = 0; col < 9; col++) {
              Cell cell = cells.get(col).get(row);
              if ( cell.isEmpty() ) {
                if ( candidates.getCandidates(row, col).contains(singleValue) ) {
                  cell.setCellValue(singleValue + 1);
                  candidates.updateCell(row, col, singleValue + 1);
                  return true;
                }
              }
            }
          }

          // Reset to check next group
          groupCandidates.clear();

          // Check candidates for entire column
          int col = j;
          for (row = 0; row < 9; row++) {
            if ( cells.get(col).get(row).isEmpty() ) {
              groupCandidates.add(candidates.getCandidates(row, col));
            }
          }

          // If we find a hidden single among the cells in the column,
          // figure out which cell had it and update that cell.
          singleValue = hasHiddenSingle(groupCandidates);
          if (singleValue != 0) {
            for (row = 0; row < 9; row++) {
              Cell cell = cells.get(col).get(row);
              if ( cell.isEmpty() ) {
                if ( candidates.getCandidates(row, col).contains(singleValue) ) {
                  cell.setCellValue(singleValue + 1);
                  candidates.updateCell(row, col, singleValue + 1);
                  return true;
                }
              }
            }
          }

          // Reset to check next group
          groupCandidates.clear();

          // Check candidates for entire block
          Block cellBlock = candidates.getCellBlock(i, j);
          for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
              if ( cells.get(y).get(x).isEmpty() ) {
                groupCandidates.add(cellBlock.array[x][y].list);
              }
            }
          }

          // If we find a hidden single among the cells in the block,
          // figure out which cell had it and update that cell.
          singleValue = hasHiddenSingle(groupCandidates);
          if (singleValue != 0) {
            for (int x = 0; x < 3; x++) {
              for (int y = 0; y < 3; y++) {
                Cell cell = cells.get(y).get(x);
                if ( cell.isEmpty() ) {
                  if ( candidates.getCandidates(x, y).contains(singleValue) ) {
                    cell.setCellValue(singleValue + 1);
                    candidates.updateCell(x, y, singleValue + 1);
                    return true;
                  }
                }
              }
            }
          }
        }
      }
    }

    return false;
  }

  /**
   *  @brief Performs Locked Candidate solving algorithm
   *   
   *  @return boolean resolved a cell
  */
  public boolean solveLockedCandidate()
  {
    // TODO: implement locked candidate solver
    return false;
  }

  /**
   *  @brief Performs Naked Pairs solving algorithm
   *   
   *  @return boolean resolved a cell
  */
  public boolean solveNakedPairs()
  {
    // TODO: implement naked pairs solver
    //candidates.nakedPairs();
    return false;
  }

  /**
   *  @brief Runs all available algorithms until puzzle is solved
  */
  public void solvePuzzle()
  {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        Cell cell = cells.get(i).get(j);
        
        while ( cell.isEmpty() ) {
          if ( solveSingle() )
            continue;
          else if ( solveHiddenSingle() )
            continue;
          else if ( solveLockedCandidate() )
            continue;
          else if ( solveNakedPairs() )
            continue;
          else
            return;
        }
      }
    }
  }

  /**
   *  @brief Checks and returns any hidden single value
   *
   *  Given a list of candidates lists, this function merges all
   *  of the lists to one new list, sorts the new list, and checks if
   *  there exists a single instance of any value. If such a value exists,
   *  the function returns that value. Otherwise, the function will return 0.
   *
   *  @param List<List<Integer>> list of candidates lists pertaining to a group
   *  @return int single instance value
  */
  private int hasHiddenSingle(ArrayList< List<Integer> > groupCandidates)
  {
    ArrayList<Integer> sortedList = new ArrayList<Integer>();

    for (List<Integer> list : groupCandidates)
      sortedList.addAll(list);

    Collections.sort(sortedList);

    int instances = 1;
    for (int i = 0; i < sortedList.size() - 1; i++) {
      if ( sortedList.get(i) == sortedList.get(i+1) ) {
        instances++;
      } else if (instances > 1) {
        if (i == sortedList.size() - 1)
          return sortedList.get(i + 1);

        instances = 1;
      } else if (instances == 1) {
        return sortedList.get(i);
      }
    }

    return 0;
  }
}
