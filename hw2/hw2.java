/****************************************************************************

                                                Gang Yang
                                                CSE 12, Fall2016
                                                10-7
                              Assignment 2

File Name:      hw2.java 
Description:    This program reads strings and integers from the user,
                processes them, and prints them back to the user.Program
                terminates when user enters ^D.At termination, program
                outputs sizes of various types of C/C++ pre defined types. 

****************************************************************************/


/**
 * The hw2 class is a direct port of hw2.c to java.
 * As you already know in java when you pass literal strings like
 * <P>
 *   writeline("a literal string\n", stream);
 * <P>
 * in C is considered a char[], but in java it's automatically
 * converted and treated as a String object.  Therefore 
 * the function writeline accepts literal strings and 
 * String types.  The getaline function returns a String type.
 */

import java.io.*;        // System.in and System.out
import java.util.*;      // Stack
/*
class name: MyLibCharacter

Description: 

Data Files:  character - type Character - private instance variable

Constructions:  MyLibCharacter - give character a new value

Public functions:  charValue() - print out the value of character
                   toString() - return "" and character as a string
*/
class MyLibCharacter {
        private Character character;

        public MyLibCharacter (int ch) {
                character = new Character ( (char) ch );
        }

        public char charValue () {
                return character.charValue ();
        }

        public String toString () {
                return "" + character;
        }
}
/*
class name: hw2
Description: this class holds public functions and private data
Data Files:
Public Functions: baseout: take integer and display in given base
                  clrbuf:  remove character in System.in buffer
		  writeline: prints out 
		  digiterror: handles erroneous user input
		  decin: accepts integer input from the user
		  decout: takes in a positive number and display it in decimal
		  getaline: read a string from the user
                  hexout: prints a number in base 16 to the parameter
		  newline: prints our a newline
*/
public class hw2 {
	private static final int ASCII_ZERO = 48;
	private static final int COUNT = 16;		// # of hex digits
        private static final int MAX = 1024;            // max length of array
	private static final int hexMax = 15;           
	//max length of hexdecimal 

	private static final int CR = 13;		// Carriage Return
	private static final int MAXLENGTH = 80;	// Max string length

	private static final int EOF = -1;		// process End Of File

	private static final int DECIMAL = 10;		// to indicate base 10
	private static final int HEX = 16;		// to indicate base 16

	private static final char digits[] = 	// for ASCII conversion
	     new String("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ").toCharArray();

	private static final String DEBUG_GETALINE = 
		"[*DEBUG:  The length of the string just entered is ";

	private static final String DIGIT_STRING = "digit ";
	private static final String REENTER_NUMBER ="\nPlease reenter number: ";
	private static final String OUT_OF_RANGE = " out of range!!!\n";
	private static final String CAUSED_OVERFLOW = " caused overflow!!!\n";
	private static final String DEBUG_WRITELINE =
		"\n[*DEBUG:  The length of the string displayed is ";

	private static Stack<MyLibCharacter> InStream =
		new Stack<MyLibCharacter>();

	private static boolean debug_on = false;
//	private static int hexCounter = 0; // counter for the number hex digits

        /**
        * Takes in a positive number and displays in a given base.
        *
        * @param    Numeric value to be displayed.
        * @param    Base to used to display number.
        * @param    Where to display, likely System.out or System.err.
        */
        private static void baseout (int number, int base, PrintStream stream) {
            // make a new character array
            char a[] = new char[MAX];              	    
	    // index to input in the array
            int index = 0;
	    // counter use for hexdecimal
	    int hexCounter = 0;
	    // find the hexdecimal case
            if (base == HEX)                 
                {
		    // let 8 numbers of array to 0
                    for (int i = 0; i<COUNT; i++) {     
                        a[i]=digits[0];
                    }
		    // find out digits
                    do {
                        a[hexCounter]= digits[number%base];
                        number = number/base;
                        hexCounter++;
                    } while (number !=0);
		    // give hexCounter a total number
	            while (hexCounter<15) {
		        hexCounter++;
		    }
		    // printout ecah digit
                    while(hexCounter>=0) {              
                        stream.print(a[hexCounter]);
                        hexCounter--;
                    }
                }
	    // normal case
            else {
		// find out digit
                do {
                    a[index] = digits[number%base];   
                    number = number/base;
                    index ++;
                } while(number != 0);
		// the last digit is no needed
                index--;
		// print out the digits
                for (; index>=0; index--) {       
                    stream.print(a[index]);
                }
            }
        }


	/* Functino name:     clrbuf
	 * Purpose:           this function remove any characters in the
	 *                    System.in buffer
	 * Description:       thic function calls fgetc repeatedly unitl a
	 *                    newline characte is detected.
	 * Input:             character: most recent character read from
	 *                    system.in
	 * Result:            extra character is removed
	 */
	public static void clrbuf (int character) {
	    char ch =(char) character;
	    // repeatedly calling fgetc until ch meet a new line
            while(ch != '\n') {
                ch = (char)fgetc(System.in);
	    }	
        }


	/* Function name:     decin
           Purpose:           this function reads a decimal number from 
                              System.in and converts it from a sequence of ASCII
                              characters into a decimal integer.
           Description:       this function returns a converted value. 
                              when an overflew occurs or non-digit characters
                              are entered, the user is prompted to reenter the 
                              number using the digiterror function
           Input:             
           Result:            this function will return the number digit     
        */
      
        public static int decin() {
            int character = 0;
            int sum=0;
	    // temp to store the prior value of sum
	    int temp=0;                              
	    character = fgetc(System.in);
	    // using while loop to input decimal
            while (character != '\n'){
		// check for EOF
	        if (character == EOF) {
	            return EOF;
		}
                // check for correct digits
		// if true, do sum algorithm
	        if (character >= digits[0]&& character<=digits[9]){
	            temp = sum;
                    sum = sum *10;
                    sum += character - ASCII_ZERO;
	            // check if the current divided by 10 is equal to prior sum
		    // if true, continue take in digits
		    if (sum/10 == temp) {
			character =fgetc(System.in);
	            }
		    // if false, call digiterror and let sum equal to 0,
		    else {
                        digiterror(character, CAUSED_OVERFLOW);
	        	sum = 0;
	                character = fgetc(System.in);
                     }
                }
		// if not correct input digit, call digiterror and reenter
                else {
                      digiterror(character, OUT_OF_RANGE);
	              sum = 0;
       	              character =fgetc(System.in);
                }
            }	
            return sum;
        }


        /**
        * Takes in a positive number and displays it in decimal.
        *
        * @param    positive numeric value to be displayed.
        * @param    Where to display, likely System.out or System.err.
        */
        public static void decout (int number, PrintStream stream) {
            // call baseout
            baseout(number,DECIMAL, stream);          
        }
	

	/*---------------------------------------------------------------------
	Function Name:          digiterror
	Purpose:                This function handles erroneous user input.
	Description:            This function  displays and error message to the
	                        user,and asks for fresh input.
	Input:                  character:  The character that began the problem
				message:  The message to display to the user.
	Result:                 The message is displayed to the user.
				The result in progress needs to be set to 0 in
				decin after the call to digiterror.
	----------------------------------------------------------------------*/
	public static void digiterror (int character, String message) {

		/* handle error */
		clrbuf (character);

		/* output error message */
		writeline (DIGIT_STRING, System.err);
		fputc ( (char)character, System.err);
		writeline (message, System.err);

		writeline (REENTER_NUMBER, System.err);
	}


	/*Function name:  getaline
	 * Purpose:       this function read characters from System.in
	 *                and store them into message array
	 * Description:   the number of characters stored into message must not
	 *                exceed maxlength(including NULL character) extra
	 *                character are removed by calling clrbuf
	 * Input:         message[]: array to hold the character entered
	 *                maxlength: the characters array stored must not exceed
	 *                this maxlength
	 * Result:        input characters are stored into array, extra
	 *                characters will be removed.
	 *                return the number of characters stored in the array
	 */
        public static int getaline( char message[], int maxlength ){
            int character;
            int index = 0;
	    //loop that store each character input by user into array one by one
            do {
                character = fgetc(System.in);
		// check EOF
	        if (character == EOF) {
		    return EOF;
		}
		// if the string reach maxlength, call clrbuf and get rid 
		// of the extra characters
		// end the loop
	        if (index == maxlength) {
                    clrbuf(character);
	            break;
	        }
	        message[index] = (char)character;
                index ++;
            } while(character != '\n');
	    //store '\0' in the array after the last user entered character
            message[--index] = '\0';
	    //when the debug is on, print out dubug message
	    if (debug_on) {
	        System.err.print(DEBUG_GETALINE + index+"]");
            }
            return (index);
        }
        


        /**
        * Takes in a positive number and displays it in hex.
        *
        * @param    A positive numeric value to be displayed in hex.
        * @param    Where to display, likely System.out or System.err.
        */
        public static void hexout (int number, PrintStream stream) {

                // Output "0x" for hexidecimal.
                writeline ("0x", stream);
                baseout (number, HEX, stream);
        }



        /**
        * Returns a character from the input stream.
        *
        * @return  <code>char</code> 
        */
        public static int fgetc(InputStream stream) {

                char ToRet = '\0';

                // Check our local input stream first.
                //   If it's empty read from System.in
                if (InStream.isEmpty ()) {

                        try {
                                // Java likes giving the user the
                                // CR character too. Dumb, so just 
                                // ignore it and read the next character
                                // which should be the '\n'.                  
                                ToRet = (char) stream.read ();
                                if (ToRet == CR)
                                        ToRet = (char) stream.read ();
                                
                                // check for EOF
                                if ((int) ToRet == 0xFFFF)
                                        return EOF;
                        }

                        // Catch any errors in IO.
                        catch (EOFException eof) {

                                // Throw EOF back to caller to handle
                                return EOF;
                        }

                        catch (IOException ioe) {

                                writeline ("Unexpected IO Exception caught!\n",
                                                        System.out);
                                writeline (ioe.toString (), System.out);
                        }

                }

                // Else just pop it from the InStream.
                else
                        ToRet = ((MyLibCharacter) InStream.pop ()).charValue ();
                return ToRet;
        }


        /**
        * Displays a single character.
        *
        * @param    Character to display.
        */
        public static void fputc(char CharToDisp, PrintStream stream) {

                // Print a single character.
                stream.print (CharToDisp);   

                // Flush the system.out buffer, now. 
                stream.flush ();
        }


        /**
        * Prints out a newline character.
        * @param    Where to display, likely System.out or System.err.
        *
        */
        public static void newline ( PrintStream stream ) {
                //call fputc function
                fputc('\n',stream);
        }

        /**
        * Prints out a string.
        *
        * @param    A string to print out.
        * @param    Where to display, likely System.out or System.err.
        * @return     <code>int</code> The length of the string.
        */
        public static int writeline (String message, PrintStream stream) {
            int index = 0;
	    // new integer to count how many characters to be displayed
	    int counter =0;
            // print out each character in message using a while loop
            while(index<message.length()) {
		// check when message reaches a null character
		if (message.charAt(index) != '\0'){
                fputc(message.charAt(index),stream);
		counter ++;
		}
                index ++;
		
            }
            if (debug_on) {
	        System.err.println(DEBUG_WRITELINE + counter+"]");
	    }
            return(--counter);
        }

	/**
	* Places back a character into the input stream buffer.
	*
	* @param    A character to putback into the input buffer stream.
	*/
	public static void ungetc (int ToPutBack) {

		// Push the char back on our local input stream buffer.
		InStream.push (new MyLibCharacter (ToPutBack));
	}


	public static void main( String[] args ) {

		int base;                    /* to hold output base */
		char buffer[] = new char[MAXLENGTH];       /* to hold string */

		int number;                  /* to hold number entered */
		int strlen;                  /* length of string */

		/* initialize debug states */
		debug_on = false;

		/* check command line options for debug display */
		for (int index = 0; index < args.length; ++index) {
			if (args[index].equals("-x"))
				debug_on = true;
		} 

		/* infinite loop until user enters ^D */
		while (true) {
			writeline ("\nPlease enter a string:  ", System.out);

			strlen = getaline (buffer, MAXLENGTH);
			newline (System.out);

			/* check for end of input */
			if ( EOF == strlen )
				break;

			writeline ("The string is:  ", System.out);
			writeline ( new String(buffer), System.out);

			writeline ("\nIts length is ", System.out);
			decout (strlen, System.out);
			newline (System.out);

			writeline ("\nPlease enter a decimal number:  ",
				System.out);
			if ((number = decin ()) == EOF)
				break;

			writeline ("\nPlease enter an output base (2-36):  ",
				System.out);
			if ((base = decin ()) == EOF)
				break;

			writeline ("Number entered is:  ", System.out);
			decout (number, System.out);

			writeline ("\nAnd in hexidecimal is:  ", System.out);
			hexout (number, System.out);

			writeline ("\nAnd in base ", System.out);
			decout (base, System.out);
			writeline (" is:  ", System.out);
			baseout (number, base, System.out);

			writeline ("\nNumber entered multiplied by 8 is:  ",
			System.out);
			decout (number << 3, System.out);
			writeline ("\nAnd in hexidecimal is:  ", System.out);
			hexout (number << 3, System.out);

			newline (System.out);
		}
	}
}
