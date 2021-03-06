/****************************************************************************

                                                        Gang Yang
                                                        CSE12, FALL2016	
                                                        TUE SEP 29
                                Assignment One

File Name:      hw1.c
Description:    This program tests functions to display output strings and 
                numbers. 
****************************************************************************/
#include <stdio.h>

#define COUNT 8		/* number of hex digits to display */
#define DECIMAL 10	/* to indicate base 10 */
#define HEX 16		/* to indicate base 16 */
#define MAX 1024        /* max lenght for array*/
/* array used for ASCII conversion */
const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*--------------------------------------------------------------------------
Function Name:         baseout.
Purpose:               Takes in a positive number and displays in a given base.
Description:           initializing an array to store each digit of the number
                       use % to get values then devide number by base.store all
		       the values in the array and the use a loop to display 
		       values backward.
		       give a special case for hexdecimal using if sentence.
                       
Input:                 number: any positive integer.
                       base any positive integer.
		       filestream stream stdout or stderr
Result:                values of number%base.
                       values of hexdecimal with leading 0.
--------------------------------------------------------------------------*/
void baseout (int number, int base, FILE * stream) {
	/* YOUR CODE GOES HERE */
	char a[1024];             /*make a new array*/
        long index = 0;           /*index to put in the array*/
	long i;                   /*count for for loop*/
	if(base == HEX){
		/*let first 8 numbers of array to be 0*/
		for(i = 0; i<=COUNT; i++){
			a[i]=digits[0];
		}
	        
 	        while(number != 0){
		        
		        a[index] = digits[number%base];
			number = number/base;
		        index++;
	        }
		/*print out digit*/
		        for(;index>=0;index--){
	 	        fputc(a[index],stream);
         	}
	}
	else{


                  /*find out digit*/
		  do{
			 a[index] = digits[number%base];
			 number = number/base;
			 index ++;
		  }while(number != 0);
		  index--;
		  while(index>=0){
			   fputc(a[index],stream);
                           index --;
		  }
	}

}


/*--------------------------------------------------------------------------
Function Name:         decout.
Purpose:               takes in a positive number and displays it in decimal.
Description:           use the function baseout but the base is DECIMAL(10)
                       
Input:                 number: any positive integer.
                       filestream stream: stdout or stderr
Result:                each digit of the number.
                       no return value
--------------------------------------------------------------------------*/
void decout (unsigned int number, FILE * stream) {
	/* YOUR CODE GOES HERE */
	baseout(number,DECIMAL,stream);
}
/*--------------------------------------------------------------------------
Function Name:         writeline.
Purpose:               prints out a string.
Description:           using a loop and fputc to print out each character of 
                       message.
                       
Input:                 message: a NULL terminated character arrays.
                       stream: stdout or stderr
Result:                return the length of the message.
                       message is displayed .
--------------------------------------------------------------------------*/
int writeline (const char * message, FILE * stream) {
	/* YOUR CODE GOES HERE */
	long index = 0;
	/*using a while loop to print put each character of message */
	while(message[index]!=0){
		fputc(message[index],stream);
		index ++;
	}
	return(index);
}

/*--------------------------------------------------------------------------
Function Name:         hexout
Purpose:               Prints a number in base 16 to the parameter FILE stream
Description:           Goal is achieved via delegating to the baseout function
Input:                 number:  the number to display
                       stream:  where to display, likely stdout or stderr
Result:                Number in base 16 is displayed.
                       No return value.
--------------------------------------------------------------------------*/
void hexout (unsigned int number, FILE * stream) {

	/* Output "0x" for hexidecimal. */
	writeline ("0x", stream);
	baseout (number, HEX, stream);
}


/*--------------------------------------------------------------------------
Function Name:         newline.
Purpose:               prints out a newline character.
Description:           use fputc to printout a new line
                       
Input:                 stream: stdout or stderr.
Result:                prints out a line.
                       no return.
--------------------------------------------------------------------------*/
void newline (FILE * stream) {
	/* YOUR CODE GOES HERE */
    fputc('\n',stream);
}






int main (int argc, char *const* argv) {
        writeline ("Hello World", stdout);
        fprintf (stderr, "Ciao Mondo\n");
	newline(stdout);
	decout (123, stdout);
	newline(stdout);
	decout (0, stdout);
	newline(stdout);
	hexout (0xFEEDDAD, stdout);
	newline(stdout);
	return 0;
}
