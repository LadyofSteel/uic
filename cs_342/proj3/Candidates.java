/**
 *  @brief Candidates class file
 *
 *  CS 342 - Project 3
 *  Univeristy of Illinois at Chicago
 *
 *  @author Daniel Kloza
*/

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.lang.Math;

//Candidates class, for keeping track of possible candidates
public class Candidates {
    private Block[][] blocks;

    Candidates()
    {
        blocks = new Block[3][3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                blocks[i][j] = new Block();
            }
        }
    }

    public Block getCellBlock(int x, int y)
    {
      return blocks[mapToBlock(x)][mapToBlock(y)];
    }

    public ArrayList<Integer> getCandidates(int x, int y)
    {
        ArrayList<Integer> list = blocks[mapToBlock(x)][mapToBlock(y)].getCandidacy(x, y);
        ArrayList<Integer> candidates = new ArrayList<Integer>(); 

        for (int i = 0; i < list.size(); i++) {
            if (list.get(i) == 1) {
                candidates.add(i);
            }
        }

        return candidates;
    }

    public void updateCell(ArrayList< List<Cell> > cells)
    {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                Cell cell = cells.get(i).get(j);

                // Only update the cell if it's not empty
                if ( !cell.isEmpty() ) {
                    int x = cell.getXPosition();
                    int y = cell.getYPosition();
                    int value = cell.getCellValue();

                    updateCell(x, y, value);
                }
            }
        }
    }

    //call this when filling in a value from the cell
    public void updateCell(int x, int y, int newVal)
    {
        if (newVal <= 0)
            return;

        int blockX = mapToBlock(x);
        int blockY = mapToBlock(y);

        //remove newVal
        clearRow(x, blockX, newVal);
        clearCol(y, blockY, newVal);
        blocks[blockX][blockY].clear(newVal);
    }

    //clears value of specified cell, returning the previous candidate list
    public void clearCell(int x, int y, int cellValue)
    {
        //roll back the cleared cell back to the candidates list it had prior
        int blockX = mapToBlock(x);
        int blockY = mapToBlock(y);
        blocks[blockX][blockY].clearCell(x,y);

        //reinsert cellValue into all of the candidates list in the group
        blocks[blockX][blockY].add(cellValue); //insert into box
        insertCandidateCol(y, blockY, cellValue);
        insertCandidateRow(x, blockX, cellValue);
    }

    //clears passed in row of all instances of passed in value
    private void clearRow(int row, int blockRow, int valToClear)
    {
        int subRow = row % 3;
        for(int blockCol = 0; blockCol < 3; ++blockCol)
            for(int subCol = 0; subCol < 3; ++subCol)
                blocks[blockRow][blockCol].array[subRow][subCol].clear(valToClear);
    }

    //clears passed in col of all instances of passed in value
    private void clearCol(int col, int blockCol, int valToClear)
    {
        int subCol = col % 3;
        for(int blockRow = 0; blockRow < 3; ++blockRow)
            for(int subRow = 0; subRow < 3; ++subRow)
                blocks[blockRow][blockCol].array[subRow][subCol].clear(valToClear);
    }

    private void insertCandidateCol(int col, int blockCol, int valToAdd)
    {
        int subCol = col % 3; for(int blockRow = 0; blockRow < 3; ++blockRow)
            for(int subRow = 0; subRow < 3; ++subRow)
                blocks[blockRow][blockCol].array[subRow][subCol].add(valToAdd);
    }

    private void insertCandidateRow(int row, int blockRow, int valToAdd)
    {
        int subRow = row % 3;
        for(int blockCol = 0; blockCol < 3; ++blockCol)
            for(int subCol = 0; subCol < 3; ++subCol)
                blocks[blockRow][blockCol].array[subRow][subCol].add(valToAdd);
    }
    
    // pass in x or y index, returns which row/col of block 
    private int mapToBlock(int coord)
    {
        if (coord >= 0 && coord <= 2)
            return 0;
        else if (coord >= 3 && coord <= 5)
            return 1;
        else
            return 2;
        }

    /*public void nakedPairs()
    {
        ArrayList<ArrayList<Integer>> pairs = new ArrayList<>();
        HashMap<ArrayList<Integer>, Boolean> processed = new HashMap<>();

        //check rows
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(getCandidates(i,j).size() == 2)
                    pairs.add(getCandidates(i,j));
            }

            for(ArrayList<Integer> p : pairs){
                if(Collections.frequency(pairs, p) == 2 && !processed.containsKey(p)){
                    //clear out every instance of this pair in all groups
                    //TODO: keep track of coordinates where each pair was found
                    clearRow(i, mapToBlock(i), p.get(0));
                    clearRow(i, mapToBlock(i), p.get(1));
                    clearCol(j, mapToBlock(j), p.get(0));
                    clearCol(j, mapToBlock(j), p.get(1));

                    blocks[mapToBlock(i)][mapToBlock(j)].clear(p.get(0));
                    blocks[mapToBlock(i)][mapToBlock(j)].clear(p.get(1));

                    processed.put(p, true);
                }
            }

            pairs.clear();
            processed.clear();
        }
    } */
}
