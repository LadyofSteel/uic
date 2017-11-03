/**
 *  @brief CandidatesList class file
 *
 *  CS 342 - Project 3
 *  University of Illinois at Chicago
 *
 *  @author Daniel Kloza
*/

import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.lang.Math;

public class CandidatesList{
    public ArrayList<Integer> list;

    private ArrayList<Integer> backup;

    CandidatesList()
    {
        list = new ArrayList<Integer>(Collections.nCopies(9, 1));
        backup = new ArrayList<Integer>(Collections.nCopies(9, 1));
    }

    public void clear(int val)
    {
        if(val <= 0)
            return;

        backup();
        list.set(val-1, 0);
    }

    public void add(int val)
    {
        if(val <= 0)
            return;

        backup();
        list.set(val-1, 1);
    }

    private void backup()
    {
        backup.clear();
        for(int c : list)
            backup.add(c);
    }

    //restores candidate list of cell from backup 
    public void clearCell()
    {
        for(int i = 0; i < backup.size(); ++i)
            list.set(i, backup.get(i));
    }
}
