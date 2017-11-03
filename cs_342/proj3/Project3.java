/**
 *  @brief Project3 main class file
 *
 *  CS 342 - Project 3
 *  Univeristy of Illinois at Chicago
 *
 *  @author Margi Gandhi
 *  @author Ammar Subei
*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;

public class Project3 extends JFrame implements ActionListener
{
    private Game game;
    private String userInput;
    private boolean checkInput;
    private Container container;

    private JLabel infoLabel;
    private JPanel mainGrid;
    private JPanel buttonsPanel;
    private JPanel[] subGrids;

    public class CustomButtonGroup extends ButtonGroup
    {
        @Override
        public void setSelected(ButtonModel model, boolean selected)
        {
            if (selected)
                super.setSelected(model, selected);
            else
                clearSelection();
        }
    }

    public Project3()
    {
        super("Sudoku");   

        game = new Game();
        infoLabel = new JLabel();
        mainGrid = new JPanel(new GridLayout(3, 3, 1, 1));
        subGrids = new JPanel[9];
        userInput = new String();
        checkInput = false;

        buttonsPanel = new JPanel();
        buttonsPanel.setLayout( new BoxLayout(buttonsPanel, BoxLayout.Y_AXIS) );

        // Initialize array of subgrids
        for (int i = 0; i < 9; i++) {
            subGrids[i] = new JPanel(new GridLayout(3, 3, 1, 1));
            subGrids[i].setBorder(BorderFactory.createMatteBorder(3,0,3,3,Color.BLACK));
        }

        // Add buttons to all subgrids
        // NOTE: This is super ugly and inefficient.
        // A better alternative is to avoid using subgrids in the first place.
        // Instead, we can use a 9x9 grid and just add the buttons directly.
        for (int subgrid = 0; subgrid < 9; subgrid++) {
            for (int i = 0; i < 3; i++) {
                for (int yPos = 0; yPos < 3; yPos++) {
                    for (int xPos = 0; xPos < 3; xPos++) {
                        Cell myCell = game.cells.get((3*(subgrid%3))+xPos).get((3*(subgrid/3))+yPos);

                        myCell.addActionListener(
                            new ActionListener()
                            {
                                public void actionPerformed(ActionEvent event)
                                {
                                    Cell cell = (Cell) event.getSource();
                                    int x = cell.getXPosition();
                                    int y = cell.getYPosition();

                                    if ( !cell.isFixed() ) {
                                        if ( userInput.isEmpty() ) {
                                            return;
                                        } else if ( userInput.equals("C") ) {
                                            game.candidates.clearCell(x, y, cell.getCellValue());
                                            cell.setCellValue(0);
                                        } else if ( userInput.equals("?") ) {
                                            ArrayList<Integer> list = game.candidates.getCandidates(x,y);
                                            StringBuilder builder = new StringBuilder("Candidates: ");
                                            
                                            for (int i = 0; i < list.size(); i++) {
                                                builder.append(list.get(i) + 1);
                                                builder.append(" ");
                                            }

                                            infoLabel.setVisible(true);
                                            infoLabel.setText(builder.toString());
                                        } else if (checkInput) {
                                            if ( game.isInputCorrect(x, y, Integer.parseInt(userInput) - 1) ) {
                                                System.out.println("INPUT CORRECT");
                                                cell.setBackground(null);
                                                cell.setCellValue(Integer.parseInt(userInput));
                                                game.candidates.updateCell(x, y, Integer.parseInt(userInput));

                                                checkIfWon();
                                            } else {
                                                System.out.println("INPUT INCORRECT");
                                                cell.setBackground(Color.RED);
                                            }
                                        } else {
                                            cell.setBackground(null);
                                            cell.setCellValue(Integer.parseInt(userInput));
                                            game.candidates.updateCell(x, y, Integer.parseInt(userInput));

                                            checkIfWon();
                                        }
                                    }
                                }
                            });

                        subGrids[subgrid].add(myCell);
                    }
                }
            }

            mainGrid.add(subGrids[subgrid]);
        }

        CustomButtonGroup toggleGroup = new CustomButtonGroup();

        // Add number buttons
        for (int i = 1; i < 10; i++) {
            JToggleButton button = new JToggleButton(String.valueOf(i));
            button.setAlignmentX(Component.CENTER_ALIGNMENT);
            button.setPreferredSize(new Dimension(60,50));
            button.addActionListener(this);

            toggleGroup.add(button);
            buttonsPanel.add(button);
            buttonsPanel.add(Box.createVerticalGlue());
        }

        // Add clear button
        JToggleButton clearButton = new JToggleButton("C");
        clearButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        clearButton.setPreferredSize(new Dimension(60,50));
        clearButton.addActionListener(this);

        toggleGroup.add(clearButton);
        buttonsPanel.add(clearButton);
        buttonsPanel.add(Box.createVerticalGlue());

        // Add help button
        JToggleButton helpButton = new JToggleButton("?");
        helpButton.setAlignmentX(Component.CENTER_ALIGNMENT);
        helpButton.setPreferredSize(new Dimension(60,50));
        helpButton.addActionListener(this);

        toggleGroup.add(helpButton);
        buttonsPanel.add(helpButton);

        // set up File menu and its menu items
        JMenu fileMenu = new JMenu("File");
        fileMenu.setMnemonic('F');

        JMenuItem loadItem = new JMenuItem("Load Puzzle");
        loadItem.setMnemonic('L');
        fileMenu.add( loadItem );
        loadItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    if ( !game.loadFile() ) {
                        JOptionPane.showMessageDialog( Project3.this,
                            "File not loaded. Please try again.",
                            "Load", JOptionPane.PLAIN_MESSAGE );
                    }
                }
            });

        JMenuItem storeItem = new JMenuItem("Save Puzzle");
        storeItem.setMnemonic('S');
        fileMenu.add(storeItem);
        storeItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    if ( !game.saveFile() ) {
                        JOptionPane.showMessageDialog( Project3.this,
                            "File not saved. Please try again.",
                            "Save", JOptionPane.PLAIN_MESSAGE );
                    }
                }
            });

        JMenuItem exitItem = new JMenuItem("Exit");
        exitItem.setMnemonic('E');
        fileMenu.add(exitItem);
        exitItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    System.exit(0); 
                }
            });

        // set up Help menu and its menu items
        JMenu helpMenu = new JMenu("Help");
        helpMenu.setMnemonic('H');

        JMenuItem playItem = new JMenuItem("Sudoku");
        playItem.setMnemonic('S');
        helpMenu.add(playItem);
        playItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    JOptionPane.showMessageDialog( Project3.this,
                        "To Solve a sudoku puzzle, each row of nine squares must contain numbers\n" +
                        "from 1 through 9, each column must also contain the numbers 1 through 9,\n" +
                        "and each box must contain the numbers 1 throuh 9. The main point is to not\n" +
                        "have any duplicates in any of the aforementioned groups (rows, columns, boxes).",
                        "Help", JOptionPane.PLAIN_MESSAGE );
                }
            });

        JMenuItem interfaceItem = new JMenuItem("User Interface");
        interfaceItem.setMnemonic('U');
        helpMenu.add(interfaceItem);
        interfaceItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    JOptionPane.showMessageDialog( Project3.this,
                        "The program navigation is mainly through the menubar.\n\n" +
                        "To load a new puzzle, click on File->Load Puzzle.\n" +
                        "To save the current puzzle, click on File->Save Puzzle.\n" +
                        "To exit the program, click on File->Exit or the (x) button.\n" +
                        "To get hints or help for solving the puzzle, check the Hints menu.\n\n" +
                        "To fill in a cell, click once on one of the buttons on the right, then click on an empty cell.\n" +
                        "If you click again on the same button on the right, the cells will not be updated.\n" +
                        "To check if your input was correct, check the Hints->Check on fill box.\n" +
                        "To clear a non-fixed cell (not input from file), use the \"C\" button.\n" +
                        "To display the possible values for an empty cell, use the \"?\" button.\n" +
                        "To get more information about the program, check the Help menu.\n",
                        "Interface", JOptionPane.PLAIN_MESSAGE );
                }
            });

        JMenuItem aboutItem = new JMenuItem("About...");
        aboutItem.setMnemonic('A');
        helpMenu.add(aboutItem);
        aboutItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    JOptionPane.showMessageDialog( Project3.this,
                        "Authors:\n" +
                        "Margi Gandhi - mgandh9\n" +
                        "Ammar Subei - asubei2\n" +
                        "Daniel Kloza - dkloza2\n\n" +
                        "NOTES: Only two solving algorithms were implemented: Single and Hidden Single.\n" +
                        "Since only two algorithms are at our disposal, the program might not be able to fully solve\n" +
                        "the entire puzzle when clicking on Hints->Solve All. In that case, the program will fill\n" +
                        "in as much as it can.",
                        "About", JOptionPane.PLAIN_MESSAGE );
                }
            });

        // set up Hints menu and its menu items
        JMenu hintsMenu = new JMenu("Hints");
        hintsMenu.setMnemonic('I'); 

        JCheckBoxMenuItem checkItem = new JCheckBoxMenuItem("Check on fill");
        checkItem.setMnemonic('C');
        hintsMenu.add(checkItem);
        checkItem.addItemListener(
            new ItemListener()
            {
                public void itemStateChanged(ItemEvent e)
                {
                    JCheckBoxMenuItem check = (JCheckBoxMenuItem) e.getSource();

                    if (check.isSelected()) {
                        checkInput = true;
                    } else {
                        checkInput = false;
                    }
                }
            });

        JMenuItem singleAlgorithmItem = new JMenuItem("Single");
        singleAlgorithmItem.setMnemonic('S');
        hintsMenu.add(singleAlgorithmItem);
        singleAlgorithmItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    game.solveSingle();
                    checkIfWon();
                }
            });

        JMenuItem hiddenSingleAlgorithmItem = new JMenuItem("Hidden Single");
        hiddenSingleAlgorithmItem.setMnemonic('H');
        hintsMenu.add(hiddenSingleAlgorithmItem);
        hiddenSingleAlgorithmItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    game.solveHiddenSingle();
                    checkIfWon();
                }
            });

        JMenuItem lockedItem = new JMenuItem("Locked Candidate");
        lockedItem.setMnemonic('L');
        hintsMenu.add(lockedItem);
        lockedItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    //game.solveLockedCandidate();
                    //checkIfWon();
                }
            });

        JMenuItem pairsItem = new JMenuItem("Naked Pairs");
        pairsItem.setMnemonic('N');
        hintsMenu.add(pairsItem);
        pairsItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    //game.solveNakedPairs();
                    //checkIfWon();
                }
            });

        JMenuItem allFourAlgorithmItem = new JMenuItem("Solve All");
        allFourAlgorithmItem.setMnemonic('A');
        hintsMenu.add(allFourAlgorithmItem);
        allFourAlgorithmItem.addActionListener(
            new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    game.solvePuzzle();
                    checkIfWon();
                }
            });

        JMenuBar menuBar = new JMenuBar();  
        menuBar.add(fileMenu);
        menuBar.add(helpMenu);
        menuBar.add(hintsMenu); 

        setJMenuBar(menuBar);  

        // get content pane and set its layout
        container = getContentPane();

        container.setLayout( new BorderLayout() );
        container.add(mainGrid, BorderLayout.CENTER);
        container.add(buttonsPanel, BorderLayout.LINE_END);
        container.add(infoLabel, BorderLayout.PAGE_END);

        setSize(500, 500);
        setVisible(true);
    }

    public void checkIfWon()
    {
        if (game.isSolved()) {
            JOptionPane.showMessageDialog( Project3.this,
                "Congratulations! You solved the puzzle!",
                "Noice", JOptionPane.PLAIN_MESSAGE );
        }
    }

    public void actionPerformed(ActionEvent event)
    { 
        JToggleButton toggledButton = (JToggleButton) event.getSource();

        if ( userInput.equals(toggledButton.getText()) ) {
            if ( toggledButton.getText().equals("?") )
                infoLabel.setVisible(false);

            userInput = "";
        } else {
            userInput = toggledButton.getText();
        }
    }

    public static void main(String args[])
    {
        Project3 application = new Project3();
        application.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    } 
}
