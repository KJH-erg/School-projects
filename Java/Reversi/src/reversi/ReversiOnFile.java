package reversi;

import java.awt.Color;
import java.io.File;
//FileNotFoundException is not used since I used Exception in general not specific FileNotFoundError
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 * ReversiOnFile is a subclass of Reversi, adding File I/O capabilities
 * for loading and saving game.
 *
 * I declare that the work here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   http://www.cuhk.edu.hk/policy/academichonesty
 * Faculty of Engineering Guidelines to Academic Honesty:
 *   https://www.erg.cuhk.edu.hk/erg/AcademicHonesty
 *
 * Student Name: Kim Jounghoon
 * Student ID  : 1155096482
 * Date        : 12/1/2020 
 * 
 */
public class ReversiOnFile extends Reversi {
    
    public static final char UNICODE_BLACK_CIRCLE = '\u25CF';
    public static final char UNICODE_WHITE_CIRCLE = '\u25CB';
    public static final char UNICODE_WHITE_SMALL_SQUARE = '\u25AB';
    
    // constructor to give a new look to new subclass game
    public ReversiOnFile()
    {
        window.setTitle("ReversiOnFile");
        gameBoard.setBoardColor(Color.BLUE);
    }


    // STUDENTS' WORK HERE    
    public void loadBoard(String filename)
    {
        int row, col;
        File input;                             
        Scanner sc;
        // 1) prepare an empty board
        for (row = 1; row <= 8; row++)
            pieces[row][0] = pieces[row][9] = EMPTY;
        for (col = 1; col <= 8; col++)
            pieces[0][col] = pieces[9][col] = EMPTY; 
        
        // 2) load board and current player from file in UTF-8 Charset encoding
        try                                                                     // if there is any error detected like file not found in this
        {                                                                       //  block skip go to catch block
        input = new File(filename);                                             // read filename
        sc = new Scanner(input,"UTF-8");                                        // scanner with UTF-8 Charset encodin
            for(int i=0; i<8; i++)                                              // first read 8 lines
            {
                String each_line = sc.nextLine();                               // read each line
                for(int j=0; j<8; j++)                                          // 8 loop for splitting line into each char
                {
                    char each_char = each_line.charAt(j);                       // save splitted char in   each_char      
                    switch (each_char) {                                        // switch condition convert unicode value
                        case UNICODE_BLACK_CIRCLE:                              // to pieces array value    
                        pieces[i+1][j+1]= -1;                                   // i and j are added to 1 since loop starts from 0 but
                        break;                                                  // pieces array in the game valid from 1 to 9        
                        case UNICODE_WHITE_CIRCLE:
                        pieces[i+1][j+1]= 1;
                        break;
                    default:
                        pieces[i+1][j+1]= 0;
                        break;
                    }
                }
            }                                                                   // after reading pieces
        String currentPlayerinput = sc.nextLine();                              // read the current player        
        char Current_Player = currentPlayerinput.charAt(0);                             
            if(Current_Player== UNICODE_BLACK_CIRCLE)
                currentPlayer = -1;
            else
                currentPlayer = 1;                                              // set currentPlayer varialbe depending on the saved value
                              // update the status
        gameBoard.addText("Loaded board from " + filename);                     //  print the statement in the game
        System.out.println("Loaded board from " + filename);
        gameBoard.updateStatus(pieces, currentPlayer);    
        }
   
        catch(Exception e)                                                      // Exception is used to deal with any type of error in the try block
        {
            gameBoard.addText("Cannot load board from " + filename);            // print the statement
            System.out.println("Cannot load board from " + filename);
            setupBoardDefaultGame();                                            //setup the default game    
        }
    }

    public void setupBoardDefaultGame()                                         // the method to set up the default game if loading failed
    {
        pieces = new int[10][10];
        pieces[4][4] = WHITE;
        pieces[4][5] = BLACK;
        pieces[5][4] = BLACK;
        pieces[5][5] = WHITE;
        currentPlayer = BLACK;  // black plays first
        gameBoard.updateStatus(pieces, currentPlayer);
    }
    
    
    // STUDENTS' WORK HERE 
    // method to save the current game
    public void saveBoard(String filename) throws NullPointerException          // thorws NullPointerException to the sayGoodbye method
    {
        if(filename == null)                                                    // if the received filename string is null
            throw new NullPointerException();                                   // thorws NullPointerException error
        // 1) open/overwrite a file for writing text in UTF-8 Charset encoding
                 
        try                                                                     // if there is any error detected within this block go to catch block
        {
            // 2) save board to the file on 8 lines of 8 Unicode char on each line
            PrintStream write= new PrintStream(filename,"UTF-8");               // printstream write
            for(int i=0; i<8; i++)                                              // double 8 loop to deal with 64 pieces
            {
                for(int j=0; j<8; j++)
                {            
                    int each_num = pieces[i+1][j+1];                            // i and j are added to 1 since loop starts from 0 but    
                    switch (each_num) {                                         // pieces array in the game valid from 1 to 9       
                        case -1:                                                //Switch contion to print on file depending on the value of pieces
                            write.print(UNICODE_BLACK_CIRCLE);
                            break;
                        case 1:
                            write.print(UNICODE_WHITE_CIRCLE);
                            break;
                        default:
                            write.print(UNICODE_WHITE_SMALL_SQUARE);
                            break;
                    }
                }
            write.print("\n");// at the 8 pieces on line is separated
            }
        // 3) save current player on line 9 and display successful messages
            if(currentPlayer==-1)
                write.print(UNICODE_BLACK_CIRCLE);
            else
                write.print(UNICODE_WHITE_CIRCLE);
            
            gameBoard.addText("Saved board to " + filename);                    // after the successful saving print the statement    
            System.out.println("Saved board to " + filename);    
        }
        // 4) in case of any Exception:
        catch(Exception e)                                                      // in case of any error
        {
            gameBoard.addText("Cannot save board to " + filename);              //print the statement and the method is finished
            System.out.println("Cannot save board to " + filename);
        }
    }
    

    // STUDENTS' WORK HERE    
    /**
     * Override sayGoodbye method of super class, to save board
     */
    @Override
    public void sayGoodbye()                                                        
    {
        System.out.println("Goodbye!");
        try
        {    
            String filename = JOptionPane.showInputDialog("Save board filename");   // receive the file name to do saved    
            saveBoard(filename);                                                    // call saveBoard method
        }
        catch(NullPointerException e)                                               // if nullpointexception is thrown from the saveBoard 
        {
            gameBoard.addText("Cannot save board to " + "null");                    // print statement
            System.out.println("Cannot save board to " + "null");                   // do not save anything 
        }
    }
    
    // main() method, starting point of subclass ReversiOnFile
    public static void main(String[] args) {
        ReversiOnFile game = new ReversiOnFile();
        String filename = JOptionPane.showInputDialog("Load board filename");
        game.loadBoard(filename);
        
        // comment or remove the following statements for real game play
        // game.setupDebugBoardEndGame();
        //  game.saveBoard("game4.txt");
        //  game.setupDebugBoardMidGame();
       //game.saveBoard("game8.txt");
        // end of sample/ debugging code
    }
}
