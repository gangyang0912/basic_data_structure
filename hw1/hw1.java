/****************************************************************************

                                                        Gang Yang
                                                        CSE12, FALL2016	
                                                        TUE SEP 29
                                Assignment One

File Name:      hw1.java
Description:    This program tests functions to display output strings and 
                numbers. 
****************************************************************************/
/**
 * The hw1 class is a direct port of hw1.c to java.
 * As you already know in java when you pass literal strings like
 * <P>
 *   writeline("a literal string\n", stream);
 * <P>
 * in C is considered a char[], but in java it's automatically
 * converted and treated as a String object.  Therefore 
 * the function writeline accepts literal strings and 
 * String types.
 */

import java.io.*;      // System.out
/*class hw1
 *
 *Description: implements the functions 
 *
 * Data Fields: 
 *
 * Public functions: 
 *  
 *         baseout: takes in a positive number and displays in a given base
 *         decout: Takes in a positive number and displays it in decimal
 *         hexout: Takes in a positive number and displays it in hex
 *         newline: print a line
 *         writeline: print message
 */
public class hw1 {
 private static final int COUNT = 8; // number of hex digits to display
 private static final int DECIMAL = 10; // to indicate base 10
 private static final int HEX = 16;  // to indicate base 16
 private static final int MAX = 1024; //max length for array
 private static final char digits[] =  // used for ASCII conversion
  new String("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ").toCharArray();
 private static int hexCounter = 0; // counter for the number hex digits


 /**
 * Takes in a positive number and displays in a given base.
        *
        * @param    Numeric value to be displayed.
        * @param    Base to used to display number.
        * @param    Where to display, likely System.out or System.err.
        */
 private static void baseout (int number, int base, PrintStream stream) {
  // YOUR CODE GOES HERE
	 char a[] = new char[MAX];              //make a new character array 
	 int index = 0;                         //index to input in the array 
	  if (base == HEX)                 // find the hexdecimal case 
	{
		for (int i = 0; i<COUNT; i++){    //let 8 numbers of array to 0 
			a[i]=digits[0];     
		}
		do{
		
		        a[hexCounter]= digits[number%base]; //find out digit
			number = number/base;         
			hexCounter++;
		}while(number !=0);
		while(hexCounter>=0){              //printout each digit
			stream.print(a[hexCounter]);
			hexCounter--;
		}
	}
	else{
	  do{
		 a[index] = digits[number%base];   // find out digit
		 number = number/base;
		 index ++;
	  }while(number != 0);
	  	  index--;                 //the last index is no needed
	  for (; index>=0; index--){       //print put the digits
		   stream.print(a[index]);	 
	  }
	}
 }


        /**
        * Takes in a positive number and displays it in decimal.
        *
        * @param    positive numeric value to be displayed.
        * @param    Where to display, likely System.out or System.err.
        */
 public static void decout (int number, PrintStream stream) {
  // YOUR CODE GOES HERE
	 baseout(number,DECIMAL, stream);          //call baseout
 }


        /**
        * Displays a single character.
        *
        * @param    Character to display.
        * @param    Where to display, likely System.out or System.err.
        */
        public static void fputc(char CharToDisp, PrintStream stream) {

                // Print a single character.
                stream.print (CharToDisp);   

                // Flush the system.out buffer, now. 
                stream.flush ();
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
        * Prints out a newline character.
        * @param    Where to display, likely System.out or System.err.
        *
        */
        public static void newline ( PrintStream stream ) {
  // YOUR CODE GOES HERE
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
  // YOUR CODE GOES HERE
        	int index = 0;
		//print out each character in message using a while loop
        	while(index < message.length()){
        	
        		fputc(message.charAt(index),stream);
        		index ++;
        	}
          return(message.length());
        }


 public static void main( String[] args ) {

         System.err.print ("Ciao Mondo\n");
         writeline ("Hello World", System.out);
         
  newline(System.out);
  decout (123, System.out);
  newline(System.out);
  decout (0, System.out);
  newline(System.out);
  hexout (0xFEEDDAD, System.out);
  newline(System.out);
 }
}
