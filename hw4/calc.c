/*******************************************************************************
 *                                                            Gang Yang
 *                                                            CSE 12, fall16
 *                                                            DUE 10-21
 *                        
 *                              Assignment 4
 * File name: calc.c
 * Description: In this assignment, I will develop a program that will
 * simulate a top-of-the-line calculator that will perform such advance
 * commands as addition,
 * subtractions,multiplication,division,exponentiation,and factorial
 *
 * ****************************************************************************/
#include <ctype.h>
#include <stdio.h>
#include "calc.h"
#include "mylib.h"
#include "stack.h"

#define CHARACTER(word) ((char) ((word) & 0x000000FF))
#define INDEX(word) (((word) & 0x0000FF00) >> 8)
#define PRIORITY(word) ((word) & 0x0000FE00)
/* BYTE to use in setupword */
#define BYTE 8
/* SIGN_BIT to use in setupword */
#define SIGN_BIT (1L<<63L)
/* the index of factorial operator */
#define INDEX_FACT 8
#define INDEX_SPACE 7

static char operators[] = "()+-*/^ !";

static long add (long, long);
static long divide (long, long);
static long exponent (long, long);
static long fact (long, long);
static long mult (long, long);
static long setupword (int);
static long sub (long, long);

/* functions is a array of pointer points to functions that takes in two 
 * parameters*/
static long (*functions[]) (long, long) =
    { NULL, NULL, add, sub, mult, divide, exponent, NULL, fact };

/* Function Name:             eval
 * Purpose:                   This function evaluate mathematical expressions
 *                            from "postfix" notation,
 * Description:               This function will take a pointer to a stack as
 *                            a parameter. It will use this stack as one of
 *                            its needed stacks. the other stak will be local 
 *                            After evaluation, the parameter stack will be
 *                            empty.
 * Input:                     stack1: pointers to Stacks containing "postfix"
 *                            expressions to evaluate.
 * Output:                    no output
 * Result:                    return long, return the final result of all
 *                            operation
 */
long eval (Stack * stack1) {
     /* creat a local stack to hold reverse stack1 */
     Stack * stack2 = new_Stack(CALCSTACKSIZE);
     /* op1 is the first operand
      * op2 is the second operand 
      * word is the item that will be popped or pushed
      * result is the result after the operand is operated */
     long op1,op2,word;
     long result = 0;
     /* put all items of stack1  to stack2 reverse */
     /* keep loopping until stack1 is empty */
     while (isempty_Stack(stack1) == FALSE){
             pop(stack1,&word);
	     push(stack2,word);
     }
     /* pop one item from stack2 each time and check if it is digit,
      * if it is, push it to stack1
      * if not, pop the last two items from stack1 as the operands 
      * and operate */
     /* keep operating until stack2 is empty */
       while (isempty_Stack(stack2) == FALSE){
             pop(stack2,&word);
             /* check if the popped item is a digit */
             if (INDEX(word) == 0){
                     push(stack1,word);
	     }
	     /* encounter a non-digit, do the operation */
	     else {  
		     /* do a special chesk for factorial calculatio */
		     if (INDEX(word) == INDEX_FACT){
                             pop(stack1,&op1);
			     result = functions[INDEX(word)](op1,op2);
			     push(stack1,result);
		     }
		     else {
	                     pop(stack1,&op1);
		             pop(stack1,&op2);
		             result = functions[INDEX(word)](op1,op2);
		             push(stack1,result);
		     }
	     } 
     }
     /* check if stack1 is empty, pop out the last result */
     if (isempty_Stack(stack1) == FALSE){
     pop(stack1,&result);
     }
     delete_Stack(&stack2);
     return result;
}

/* Function Name:             intopost
 * Purpose:                   This function convert "infix" mathematical
 *                            expressions entered by the use into their
 *                            "postfix" wquivalents.
 * Description:               This function will take a pointer to a stack as
 *                            a parameter. It will use this stack as one of
 *                            its needed stacks. the other stak will be local 
 *                            The parameter stack will also serve as the place
 *                            to store the resultant post-fix expression. The
 *                            return value from intopost if either EOF when ^D
 *                            is entered or a non-zero value indicating that
 *                            the function succeeded.
 * Input:                     stack1: pointers to empty Stacks used to store
 *                            "postfix expressions".
 * Output:                    no output
 * Result:                    return EOF when ^D is entered
 *                            return TRUE when function succeeded
 */
long intopost (Stack * stack1) {
     /* creat a local stack to hold operators */
     Stack * stack2 = new_Stack(CALCSTACKSIZE);
     /* input character */
     int character;
     /* item to be popped or pushed */
     long item = 0;
     /* digit to be inputed */
     long digit = 0;
     character = fgetc(stdin);
     /* process each character of the input in turn */
     /* keep reading character from the buffer until it encounters a
      * new line character */
     while (character != '\n'){
	     /* check EOF error */
             if (character == EOF){
		     delete_Stack(&stack2);
                     return EOF;
             }
	     /*check if character is blank*/
             while (character == operators[INDEX_SPACE]){
		     character = fgetc(stdin);
		     /* if the character is a new line character, end
		      * the loop */
             }
	     if (character == '\n'){
                     break;
	     }
	     /* check if character is a digit */
	     if (isdigit(character)){
                     ungetc(character,stdin);
		     digit = decin();
		     push(stack1,digit);
             }
	     /* check if character is '(' */
	     else if (character == operators[0]){
                     push(stack2,setupword(character));
	     }
	     /* check if character is ')' */
	     else if (character == operators[1]){
		     /* check if stack2 is empty, if it is not, top stack2 
		      * to get the last item on it */
		     if (isempty_Stack(stack2) == FALSE){
                             top(stack2,&item);
		     }
		     /* check if the first '(' is encountered */
	             while ((int)item != operators[0]){
                             pop (stack2,&item);
		             push (stack1,item);
	             }
		     /* pop out the operator[0] in stack1 */
		     pop (stack1,&item);
	     }
	     /* deal with other operators */
	     else {
		     /* check if stack2 is empty, if it is not, top stack2 to
		      * get the last item in order to compare with input 
		      * character*/
		     if (isempty_Stack(stack2) == FALSE){
                             top(stack2,&item);
		     }
		     /* check if stack2 if empty */
	             /* check the priority of top symbol */
		     while (isempty_Stack(stack2) == FALSE && 
			PRIORITY(item) >= PRIORITY(setupword(character))){
                                     pop (stack2,&item);
			             push (stack1,item);
				     /* check if the stack2 is empty now, if it 
				      * is not, top stack2 again to make the 
				      * next compare */
				     if (isempty_Stack(stack2) == FALSE){
				     top (stack2,&item);
				     }
		     }
		     push (stack2,setupword(character));
	     }
	     character = fgetc(stdin);
     }
     /* pushing all symbols popped from stack2 to stack1 */
     /* check if stack2 is empty */
     while (isempty_Stack(stack2) == FALSE){
	     pop(stack2,&item);
	     push(stack1,item);
	     /* check if the last item is '(' */
	     if ((int)item == operators[0]){
                     pop(stack1,&item);
	     }
	     /* if the last item in stack2 is not '(' push to stack1*/
     }
     delete_Stack(&stack2);
     return TRUE;
}

static long add (long augend, long addend) {
    return augend + addend;
}

static long divide (long divisor, long dividend) {
    return dividend / divisor;
}

/* Function Name:             exponent
 * Purpose:                   This function raises base to the power exponent.
 * Description:               This function will use a while loop to keep
 *                            multiplying until the power reaches 0.
 * Input:                     power: any positive integer
 *                            base:  any positive integer 
 * Output:                    no output
 * Result:                    return result of base to power exponent
 */
static long exponent (long power, long base) {
     /* result to hold the final result
      * initialize it to 1*/	
     long result = 1;
     /* keep multiplying until power reaches 0 */
     while (power > 0){
             result = result*base;
	     power--;
     }
     return result;
}

/* Function Name:             fact
 * Purpose:                   This function calculates xxx factorial
 * Description:               This function will use a while loop to keep
 *                            multiplying until the xxx reaches 1.
 * Input:                     xxx: any positive integer
 *                            ignored:  any valid integer 
 * Output:                    no output
 * Result:                    return result of xxx factorial
 */
static long fact (long xxx, long ignored) {
     /* result to hold the final result */	
     long result = xxx;
     /* keep multiplying until xxx reaches 1 */
     while(xxx>1){
             result = result*(--xxx);
     }
     return result;

}

static long mult (long factorx, long factory) {
    return factorx * factory;
}

/* Function Name:             setupword
 * Purpose:                   This function is a constructor function for longs
 *                            representing operators to be stored on the stacks
 * Description:               This function The representation for the 
 *                            operators should have everything associated with 
 *                            that operator: a distinction from numbers, 
 *                            the index in the functions array corresponding to 
 *                            that operator, and the priority of the operator 
 *                            and the ASCII code. 
 * Input:                     character:  expected to be ASCII 
 *                            codes for operators entered by the user, 
 *                            which are also expected to be found inside the 
 *                            operators[] array. 
 * Output:                    no output
 * Result:                    returns a long that can be stored on the stacks
 */
static long setupword (int character) {
     /* use index to get the index of the operator */	
     long index = 0;
     /* check character with each item in operators until they match 
      * get correct index number */
     while (operators[index] != character){
             index++;
     }
     /* return a value containing the sign-bit set to '1', 
      * the index in the next-to-rightmost byte, 
      * and the ASCII character in the rightmost byte.*/
     return SIGN_BIT|(index<<BYTE)|character;
}

static long sub (long subtrahend, long minuend) {
    return minuend - subtrahend;
}

