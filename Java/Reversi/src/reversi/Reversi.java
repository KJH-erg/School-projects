package reversi;

import java.awt.Color;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;

/**
 * CSCI1130 Java Assignment
 * Reversi board game
 * 
 * Students shall complete this class to implement the game.
 * There are debugging, testing and demonstration code for your reference.
 * 
 * I declare that the assignment here submitted is original
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
 * @author based on skeleton code provided by Michael FUNG
 */
public class Reversi {

    // pre-defined class constant fields used throughout this app
    public static final int BLACK = -1;
    public static final int WHITE = +1;
    public static final int EMPTY =  0;

    // a convenient constant field that can be used by students
    public final int FLIP  = -1;
    
    // GUI objects representing and displaying the game window and game board
    protected JFrame window;
    protected ReversiPanel gameBoard;
    protected Color boardColor = Color.GREEN;

    // a 2D array of pieces, each piece can be:
    //  0: EMPTY/ unoccupied/ out of bound
    // -1: BLACK
    // +1: WHITE
    protected int[][] pieces;
    
    // currentPlayer:
    // -1: BLACK
    // +1: WHITE
    protected int currentPlayer;
    
    // STUDENTS may declare other fields HERE
    protected int [] resulting_direction = new int [2]; // fields for setting direction until this array piecese are flipped                  
    protected int end_decision = 0;                     //field to check the count of forced pass    
    
    /**
     * The only constructor for initializing a new board in this app
     */
    public Reversi() {
        window = new JFrame("Reversi");
        gameBoard = new ReversiPanel(this);
        window.add(gameBoard);
        window.setSize(850, 700);
        window.setLocation(100, 50);
        window.setVisible(true);
        
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // use of implicitly extended inner class with overriden method, advanced stuff
        window.addWindowListener(
            new WindowAdapter() {
                @Override
                public void windowClosing(WindowEvent e)
                {
                    sayGoodbye();
                }
            }
        );

        // a 8x8 board of pieces[1-8][1-8] surrounded by an EMPTY boundary of 10x10 
        pieces = new int[10][10];
        pieces[4][4] = WHITE;
        pieces[4][5] = BLACK;
        pieces[5][4] = BLACK;
        pieces[5][5] = WHITE;
        currentPlayer = BLACK;  // black plays first
        gameBoard.updateStatus(pieces, currentPlayer);
    }

    /**
     * setupDebugBoard for testing END-game condition
     * students can freely make any changes to this method for testing purpose
     * TEMPORARY testing case
     */
    protected void setupDebugBoardEndGame()
    {
        gameBoard.addText("setupDebugBoardEndGame():");
        for (int row = 1; row <= 8; row++)
            for (int col = 1; col <= 8; col++)
                pieces[row][col] = BLACK;
        pieces[5][8] = WHITE;
        pieces[6][8] = EMPTY;
        pieces[7][8] = EMPTY;
        pieces[8][8] = EMPTY;

        currentPlayer = BLACK;  // BLACK plays first
        
        gameBoard.updateStatus(pieces, currentPlayer);
    }

    
    /**
     * setupDebugBoard for testing MID-game condition
     * students can freely make any changes to this method for testing purpose
     * TEMPORARY testing case
     */
    protected void setupDebugBoardMidGame()
    {
        gameBoard.addText("setupDebugBoardMidGame():");

        int row, col, distance;
        
        // make all pieces EMPTY
        for (row = 1; row <= 8; row++)
            for (col = 1; col <= 8; col++)
                pieces[row][col] = EMPTY;
        
        // STUDENTS' TEST and EXPERIMENT
        // setup a star pattern as a demonstration, you may try other setups
        // relax, we will NOT encounter array index out of bounds, see below!!
        row = 5;
        col = 3;
        distance = 3;
        
        // beware of hitting the boundary or ArrayIndexOutOfBoundsException
        for (int y_dir = -1; y_dir <= +1; y_dir++)
            for (int x_dir = -1; x_dir <= +1; x_dir++)
            {
                try {
                    int move;
                    // setup some opponents
                    for (move = 1; move <= distance; move++)
                        pieces[row + y_dir * move][col + x_dir * move] = BLACK;

                    // far-end friend piece
                    pieces[row+y_dir * move][col + x_dir*move] = WHITE;
                }
                catch (ArrayIndexOutOfBoundsException e)
                {
                    // intentionally do nothing in this catch block
                    // this is simple and convenient in guarding array OOB
                }
            }
        // leave the center EMPTY for the player's enjoyment
        pieces[row][col] = EMPTY;
        
        // pieces[row][col] = 999;  // try an invalid piece

        
        // restore the fence of 10x10 EMPTY pieces around the 8x8 game board
        for (row = 1; row <= 8; row++)
            pieces[row][0] = pieces[row][9] = EMPTY;
        for (col = 1; col <= 8; col++)
            pieces[0][col] = pieces[9][col] = EMPTY;
        
        currentPlayer = WHITE;  // WHITE plays first
        // currentPlayer = 777;    // try an invalid player
        gameBoard.updateStatus(pieces, currentPlayer);
    }
    
 
    /**
     * STUDENTS' WORK HERE
     * 
     * As this is a GUI application, the gameBoard object (of class ReversiPanel)
     * actively listens to user's actionPerformed.On user clicking of a
    ReversiButton object, this callback method will be invoked to do some
    game processing.
     */
    
    // starting from North in clockwise direction, then give the direction in 2D array field
    protected int []giveDirection(int input) {
        int direction [] = new int [2];
        switch(input){
            case 0 :  direction [0]=0 ;direction [1]=-1; break;     // NORTH
            case 1 :  direction [0]=1 ;direction [1]=-1; break;     // NORTHEAST
            case 2 :  direction [0]=1 ;direction [1]=0; break;      // EAST
            case 3 :  direction [0]=1 ;direction [1]=1; break;     // SOUTHEAST
            case 4 :  direction [0]=0 ;direction [1]=1; break;     // SOUTH
            case 5 :  direction [0]=-1 ;direction [1]=1; break;     // SOUTHWEST
            case 6 :  direction [0]=-1 ;direction [1]=0; break;     // WEST
            case 7 :  direction [0]=-1 ;direction [1]=-1; break;    // NORTHWEST   
        }
        return direction;
    }
    
    // This method is to check the validity for the forced pass
    // return boolean value
    protected boolean checkValidityforFpass(int currentPlayer,int row, int col )
    {
        boolean nearpiece;                                                      //validity for opposite piece is  adjacent within the direction
        boolean outerpiece;                                                     // validity for existence of same piece within the direction
        
        int counter = 0;                                                        // For 8 directions
        for(int i = 0; i<8 ; i++)
        {
            int [] tmp_dir = giveDirection(i);                                   //array indicates the direciton
            nearpiece = checkNearpiece (i, currentPlayer,row,col,tmp_dir[0],tmp_dir[1]);  // check near piece
            outerpiece = checkOuterpiece(i, currentPlayer,row,col,tmp_dir[0],tmp_dir[1]); // check outer piece
            if(nearpiece&&outerpiece){                                                    //If both true
                counter= counter +1;                                                      // 1 is addated to counter  
            }
        }
        
        if (counter==0)                                                         // counter 0 indicates within 8 directions
        return false;                                                           //there are no cases both outer and inner pieces are satisfied                                                      
        else                                                                        
        return true;                                                            // else return true        
    }
   

    protected boolean checkValidity (int currentPlayer,int row, int col )       // method to check the validity of move and capture
    {                                                                           //and return the boolean value
        if (!(pieces[row][col]==0))                                             // in case userclick is not empty
            return false;                                                       //return false
        int result = checkCapture (currentPlayer,row, col);                     // int result of method checkCapture for each 8 directions    
        if(result ==0)                                                          // in case within 8directions with no valid capture 
            return false;
        else                                                                    // other cases = valid movement
            return true;
    }
    
    // method check valid movement of each direction and returns int result representing the frequency of thsoe valid moves
    protected int checkCapture (int currentPlayer,int row, int col )            
    {                                                                       
        boolean nearpiece;                                                      //validity for opposite piece is  adjacent within the direction
        boolean outerpiece;                                                     // validity for existence of same piece within the direction
        int counter = 0;
        for(int i = 0; i<8 ; i++)                                               // For 8 directions
        {

            int [] tmp_dir = giveDirection(i);                                                  //array indicates the direciton
            nearpiece = checkNearpiece (i, currentPlayer,row,col,tmp_dir[0],tmp_dir[1]);        // check near piece
            outerpiece = checkOuterpiece(i, currentPlayer,row,col,tmp_dir[0],tmp_dir[1]);       // check outer piece
            if(nearpiece&&outerpiece){                                                          //if check outer and inner pieces are satisfied
                changeColor(currentPlayer,row,col,resulting_direction[0],resulting_direction[1],tmp_dir[0],tmp_dir[1]);   //changecolor  
                counter= counter +1;                                            // 1 is addated to counter  
            }                   
        }   
        return counter;                                                         //counter is returned
    }
    
   //method checking validity for opposite piece is  adjacent within the direction
   protected boolean checkNearpiece (int input, int currentPlayer, int row, int col,int x,int y)
    {
        int new_row= row+y;                                                     // new row with given direction for adjacent piece of orignal piece  
        int new_col = col+x;                                                    // new col with given direction for adjacent piece of orignal piece    
            if(!(checkWithinBoundary(new_row)||checkWithinBoundary(new_col)))       // TO ensure pieces are within 1-8
            {
                if(FLIP*currentPlayer==pieces[new_row][new_col]){               // If near piece is opposite    
                return true;                                                    //return true
            }   
        }       
        return false;                                                           //no matching case return false
    }
   
    protected boolean checkOuterpiece (int input, int currentPlayer, int row, int col,int x,int y)
    {
        int new_row = row+2*y;                                                  // 2is multiplied to exclude the near piece
        int new_col= col+2*x;
            do{                                                                 // loop until one of condition is met
                if(checkWithinBoundary(new_row)||checkWithinBoundary(new_col))  // when piece is not within the 1-8
                    return false;                                               // return false
                if(pieces[new_row][new_col] == 0)                               // if piece is empty after near piece
                    return false;                                               // return false
                else if(pieces[new_row][new_col] == currentPlayer)              // if the piece is the identical with currentPlayer
                {  
                    resulting_direction[0] = new_row;                           // store the location current location in resulting_direction
                    resulting_direction[1] = new_col;
                    return true;
                }
                else                                                            // in case not matched
                {
                    new_row+=y;                                                 // move 1 step within the same direction
                    new_col+=x;
                }    
            } while(true);
        }
    
    protected boolean checkWithinBoundary(int value)                            // return true if row and col is not within 1-8
    {
        if(value>8)
            return true;
        else if(value<1)
            return true;
        else                                                                    // else return false
            return false;
    }
    
    protected void changeColor(int currentPlayer,int row,int col,int result_dirx,int result_diry, int x, int y)
    {
        int new_row = row+y;                                                    //excluding the current location by adding direction
        int new_col= col+x;                                                     // the same with the near piece of one direction
        while(true)
        {                                                           
            pieces[new_row][new_col]=currentPlayer;                             // change the color into currentPlayer
            new_row=new_row+y;                                                  // move one step along the direction
            new_col=new_col+x;
            if(result_dirx == new_row && result_diry==new_col)                  // when row and col meet result_dir from checkOuterpiece
            return;                                                             // exit
        }   
    }
    
    protected boolean checkForcedPass(int currentPlayer,int row,int col)        
    {
    int counter=0;                                                          // count the number of invalid position within 64 pieces
    for(int i = 1; i<9; i++)                                                    // loop to ensure check 64 pieces in the game
    {
        for(int j = 1; j<9; j++)
        {
            if(pieces[i][j]==0 && (checkValidityforFpass(currentPlayer,i, j)))  // from pieces[1][1]to pieces[8][8]if piece is empty and 
            {                                                                   // current player can place a piece
                counter = counter+1;                                            // add one to counter
            }
        }
    }
    if(counter == 0)                                                            // imply current player cannot place any piece
        return true;                                                
    else
        return false;
    }
    
    public void userClicked(int row, int col)
    {
    end_decision = 0;                                                           //variable to check the double forced pass
    if(!(checkValidity(currentPlayer, row, col)))                               // in case not validmove
        {       
            gameBoard.addText("Invalid move");                                  // print invalidmove and return 
            return;
        }
    else;                                                                       // if there is a valid move
    pieces[row][col] = currentPlayer;                                           // put piece of the player in clicked area
    currentPlayer = FLIP * currentPlayer;                                       // chagne the player     
    gameBoard.updateStatus(pieces, currentPlayer);                              // update the board       
    if (checkForcedPass(currentPlayer,row, col))                                // check the whether there is a valid move for the next player
    {
        gameBoard.addText("Forced Pass");                                       // if yes
        end_decision=end_decision+1;                                            // add 1 to end_decision
        currentPlayer = FLIP * currentPlayer;                                   // change the player
        gameBoard.updateStatus(pieces, currentPlayer);                          // update board
        if (checkForcedPass(currentPlayer,row, col))                            // In case the changed player cannot place again
            end_decision=end_decision+1;                                        //  add 1 to end_decision            
    }                                                                           // if end_decision is not two then it will be initialized into 0 as 
                                                                                //in Line350 when userclick is initialized again   
    if(end_decision ==2)                                                        // in case end_decision is two
    {
        gameBoard.addText("Double Forced Pass");                                    // print following lines
        gameBoard.addText("End game!");                                                         
    }       
}
        
        

    /**
     * sayGoodbye on System.out, before program termination
     */
    protected void sayGoodbye()
    {
        System.out.println("Goodbye!");
    }

    // main() method, starting point of basic Reversi game


    public static void main(String[] args) {
        Reversi game = new Reversi();
       
        // comment or remove the following statements for real game play
        //game.setupDebugBoardEndGame();
        //game.setupDebugBoardMidGame();
        // end of sample/ debugging code
        
        // *** STUDENTS need NOT write anything here ***
        
        // this application still runs in the background!!
        // the gameBoard object (of class ReversiPanel) listens and handles
        // user interactions as well as invoking method userClicked(row, col)
        
        // although this is end of main() method
        // THIS IS NOT THE END OF THE APP!
        
        
        
    }

}

