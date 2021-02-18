package cashpoint;
import javax.swing.JOptionPane;
import java.lang.Math;




public class CashPoint {
    public static double balance = 109700.0;
    
    public static void invalidInput() {
        JOptionPane.showMessageDialog(null,"Invalid input");
    }
    
public static String showMainMenu() {                                           // main menu
             return JOptionPane.showInputDialog("Cash Point: Input your task\n"
                                                + "1. Check Balance\n"
                                                + "2. Cash Deposit\n"
                                                + "3. Cash Withdrawal\n" 
                                                + "4. Exit\n"
                                               , "<type [1 - 4] here>");
}
    
public static void checkBalance(double balance) {                               // balance menu
    String balance_str = String.format("Balance (HKD): %.2f\n", balance);
    JOptionPane.showMessageDialog(null, balance_str);
 } 

public static String showDepositMenu() {                                        // deposit menu
        return JOptionPane.showInputDialog("Cash Deposit (HKD):\n" + "Input # of $100 banknotes [20 max]"
                                               ,"<type [1-20] here>");
}

public static void depositCalculation(int deposit) {                            // show deposit result and add value
        int deposit_value = deposit*100;
        String display = String.format("HKD %d deposited\n", deposit_value);
        CashPoint.balance = CashPoint.balance + deposit*100;
        JOptionPane.showMessageDialog(null, display);
}
    
public static String showWithdrawMenu() {                                       // show withdraw menu
        return JOptionPane.showInputDialog("Cash Withdrawal: Choose your currency\n"
                                         + "1.Hongkong Dollar (HKD)\n"
                                         + "2. Korean Won (KRW)\n"
                                         , "<Type [1 or 2] here>");
}

public static String withdrawHKD() {                                            // HKD withdraw menu
        return JOptionPane.showInputDialog("Cash Withdrawal (HKD):\n"
                                           +"100 min, 10000 max"
                                           ,"<type [amount] here>");
}

public static String withdrawKRW() {                                            // KRW withdraw menu
        return JOptionPane.showInputDialog("Cash Withdrawal (KRW):\n"
                                           +"1000 min, 200000 max"
                                           ,"<type [amount] here>");
}

public static int withdrawHKDcalculation(int value) {                           
    while(true) {
        if(value>=100 && value<=10000) {                                        // check input range
            if(value>balance) {                                                 // not enough balance
            notEnough();
            return 0;                                                           // 0 means unsuccesful withdrawal 1 means successful withdrawal    
            }                                                                   // in Main method the action is determined by this return value
            else {      
                if (withdrawHKDwarning (value) == 1)                            // yes button is clicked
                return 1;
                else                                                            // no button is clicked
                return 0;    
            } 
        }   
        else  {                                                                 //not correct input range
            invalidInput();
            return 0;  
        }
    }
}

public static int  withdrawHKDwarning (int value) {                             //Method to check the confirmation of withdrawl
    double withdraw_value = Math.floor(value/100)*100;
    int result;
    String displayHKD = String.format("\"Banknotes provided for HKD are 500 & 1000 \n" +
                                      "\"Withdraw HKD %.0f or not\"", withdraw_value);
    result = JOptionPane.showConfirmDialog(null, displayHKD, "Message", JOptionPane.YES_NO_OPTION);  // the value of yes or no button   
    
    if(result == 0){                                                            // the value of yes button   
        withdrawshowoutput(withdraw_value);                                         
        balance = balance - withdraw_value;
        return 1;
    }
    else {                                                                      // no button  
        return 0;
    }
}   

public static void withdrawshowoutput(double value) {                           // HKD bill calculation
    
    double bill_500;
    double bill_100;
    bill_500 = Math.floor(value/500);
    bill_100 = (value - bill_500*500)/100;
    
    String display = String.format("HKD %.0f withdrawn\n"
                                       +"HKD 500 x %.0f\n"
                                       + "HKD 100 x %.0f\n", value, bill_500, bill_100);                                 
    JOptionPane.showMessageDialog(null, display);
        
}

public static String withdrawalmessage() {                                            // same procedure with HKD withdrawal
        return JOptionPane.showInputDialog("Cash Withdrawal (KRW):\n"
                                           +"1000 min, 200000 max"
                                           ,"input");
}
public static int withdrawKRWcalculation(int value) { 
    while(true) {
        double withdraw_value = Math.floor(value/1000)*1000;
        double kor_trans = withdraw_value/150;
        double kor_exc = krwExchange(kor_trans);

        if(value>=1000 && value<=200000) {
            if(kor_exc>balance) {
            notEnough();
            return 0;        
            }    
            else {     
                if (withdrawKRWwarning (value)==1)
                return 1;
                else
                return 0;    
            } 
        }   
        else  {
            invalidInput();
            
            return 0;  
        }
    }
}

public static int  withdrawKRWwarning (int value) {
    double withdraw_value = Math.floor(value/1000)*1000;
    double kor_trans = withdraw_value/150;
    double kor_exc = krwExchange(kor_trans);
    
    int result;
    String displayHKD = String.format("\"Banknotes provided for KRW are 10000 & 1000 \n" +
                                      "\"Withdraw KRW %.0f (HKD %.2f) or not\"", withdraw_value, kor_exc);
    result = JOptionPane.showConfirmDialog(null, displayHKD, "Message", JOptionPane.YES_NO_OPTION);
    
    if(result == 0){
        withdrawKRWshowoutput(withdraw_value);
        balance = balance - kor_exc;
        return 1;
    }
    else{
        return 0;
    }
}   

public static void withdrawKRWshowoutput(double value) {
    
    double bill_10000;
    double bill_1000;
    bill_10000 = Math.floor(value/10000);
    bill_1000 = (value - bill_10000*10000)/1000;
    
    String display = String.format("KRW %.0f withdrawn\n"
                                       +"KRW 10000 x %.0f\n"
                                       + "KRW 1000 x %.0f\n", value, bill_10000, bill_1000);                                 
    JOptionPane.showMessageDialog(null, display);
        
}

public static double krwExchange(double value) {                                //from HKD to KRW
    double result;
    result = Math.round(value*100);
    result= result/100;
    return result;

}        

public static void notEnough() {
    JOptionPane.showMessageDialog(null, "Not enough balance, input again");         // show error message if not enough balance
 } 

public static void bye() {
    JOptionPane.showMessageDialog(null, "Hope to serve you again");     // show bye message
 } 

    public static void main(String[] args)  {
    while(true)
    {
        String initinput = showMainMenu();
            
            if (initinput == null) {                                            // if x button is selected exit
                bye();        
                break;
            }
            else if (initinput.equals("4")) {                                   //if 4 is selected exit
                bye();
                break;
            }
            
            else if(initinput.equals("1")) {                                    //if 1 is  show balance
                checkBalance(balance);
            }
            
            else if (initinput.equals("2")) {                                   //if 2 is go to deposit menu
                while(true) {
                    String ori_deposit = showDepositMenu();                      // receive the deposited value in string 
                    if (ori_deposit == null)                                    // if x button is selected go to main menu
                        break;
                    else { 
                        int deposit = Integer.parseInt(ori_deposit);            // deposited value in string  to int
                        if(deposit>0 && deposit<21) {                           // check deposited value is within the range
                            depositCalculation(deposit);         
                            break;                                              // end of action go to main menu
                        }    
                        else {                                                  // if none of above is selected repeat
                            invalidInput();       
                            continue;
                        }
                    }    
                }
            }
            
            else if (initinput.equals("3")) { //if 3 is go to withdraw menu
                while(true) {  
                    boolean end_transaction = true;                             // variable to check the end of transation
                    String withdraw_input = showWithdrawMenu();                 // receive the action button
                    if (withdraw_input == null)                                 // if x button is selected go to main menu
                        break;                              
                    else if(withdraw_input.equals("1")) {                       // if 1 button is selected go to HKD menu
                        while(true) {
                            String to_cash = (withdrawHKD());                   // receive withdraw value in string
                            if (to_cash == null)                    
                            break;                                              // if x button is selected go to main menu
                            else {
                            int withdraw_value =Integer.parseInt(to_cash);      // change withdraw value into int
                            int flag = withdrawHKDcalculation(withdraw_value);  // flag for the return value from method
                                if (flag == 0)                                  // 0 for withdraw cancelled so go the withdraw input
                                    continue;                                   //continue loop line239
                                else if (flag == 1) {                           // 1 for withdraw succeeded 
                                    end_transaction = false;                    // change of the variable to check the transaction is successful
                                    break;                                      //break loop line239
                            }   
                            }
                        }      
                    }
                    
                    else if(withdraw_input.equals("2")) {                       // if 2 button is selected go to KRW menu
                        while(true) {
                            String to_cash = (withdrawKRW());                   // receive withdraw value in string
                            if (to_cash == null)                                // if x button is selected go to main menu
                            break;
                            else {
                            int withdraw_value =Integer.parseInt(to_cash);      // receive the withdraw value and change into int
                            int flag = withdrawKRWcalculation(withdraw_value);  // flag for the return value from method
                                if (flag == 0)                                  // 0 for withdraw cancelled so go the withdraw input
                                    continue;                                   //continue loop line257
                                else if (flag == 1) {                           // 1 for withdraw succeeded 
                                    end_transaction = false;                    // change of the variable to check the transaction is successful
                                    break;                                      //break loop line257
                                }
                             }
                        }   
                    }    
                    else {                                                      // if 1 or 2 button is not selected     
                    invalidInput();       
                    continue;                                                   //continue loop line233
                    }
                if(end_transaction == false)                                    //withdraw succeeded so break loop in line 233 and
                    break;                                                      //go to main menu
                else                                                            //withdraw input is cancelled
                    continue;                                                   // go to previous menu         
                }   
            }
            else {                                                              // one of 1,2,3,4 is not selected       
                invalidInput();       
                continue;
            }
        }
    }
}
        
        

    


