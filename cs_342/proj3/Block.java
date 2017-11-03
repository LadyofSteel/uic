/**
 *  @brief Block class file
 *
 *  CS 342 - Project 3
 *  Univeristy of Illinois at Chicago
 *
 *  @author Daniel Kloza
*/

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.lang.Math;

public class Block{
    public CandidatesList[][] array;

    Block()
    {
        array = new CandidatesList[3][3];

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                array[i][j] = new CandidatesList();
            }
        }
    }

    //removes any candidate with the value val in this block
    public void clear(int val)
    {
        for(int x = 0; x < 3; ++x)
            for(int y = 0; y < 3; ++y)
                array[x][y].clear(val);
    }

    //adds candidate into every list in this block
    public void add(int val)
    {
        for(int x = 0; x < 3; ++x)
            for(int y = 0; y < 3; ++y)
                    array[x][y].add(val);
    }

    public void insert(int x, int y, int val)
    {
        //modulus 3 maps [x][y] to its corresponding values in the subarray
        array[x % 3][y % 3].add(val);
    }

    //get array candidacy
    public ArrayList<Integer> getCandidacy(int x, int y)
    {
        return array[x % 3][y % 3].list;
    }

    //clears specified cell, return back to the previous candidates list
    public void clearCell(int x, int y){
        array[x % 3][y % 3].clearCell();
    }
}
