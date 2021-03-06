/****************************************************************************

                                                        Gang Yang
                                                        CSE 12, fall 2016
                                                        10-29, 2016
                                                        
                                Assignment Five

File Name:      stack.c
Description:    In this assignment, we are going to create a polymorphic 
                generic container based on a linked-list data structure.

****************************************************************************/


#include <stdio.h>
#include "list.h"
#include "stack.h"
/*---------------------------------------------------------------------------
Function Name:                delete_Stack
Purpose:                      This function deallocates all memory associated
                              with the stack and sets it pointer in the calling
			      			  functon to NULL
Description:                  This function first checks that the parameter of
                              spp is not a null pointer and that the pointer
			      			  it's pointing to is not a null pointer. Then the
			         		  function use free to deallocated the memory.
Input:                        **spp: double pointer to the stack that is 
                              to be deleted
Output:                       if spp or *spp are NULL pointer, output error
                              message
			    			  if debug is on, output debug message.
Result:                       current stack is deleted
                              void functio, no return.
---------------------------------------------------------------------------*/
void delete_Stack (Stack ** spp) {
        delete_List (spp);
}
/*---------------------------------------------------------------------------
Function Name:                isempty_Stack 
Purpose:                      check if the stack is empty 
Description:                  call isempty_List to check
							  returns true is this_Stack is empty, and false
                              if it is not.
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is a null pointer, output error
                              message
Result:                       return TRUE or FALSE.
---------------------------------------------------------------------------*/
long isempty_Stack (Stack * this_stack) {
        return isempty_List (this_stack);
}
/*---------------------------------------------------------------------------
Function Name:                new_Stack
Purpose:                      allocates and initializes a new Stack object
Description:                  this function allocates memory to hold
                              stacksize number of longs, initializes the
                              stack infrastructure 
Input:                        copy_func (void *(*)(void *)) - copyfunction
							  delete_func (void (*)(void *)) - deletefunction
							  write_func (FILE *(*)(void*,FILE*)) - 
							  writefunction
Output:                       if debug is on, output debug message
Result:                       returns a pointer to the first storage space
                              in the stack.
---------------------------------------------------------------------------*/
Stack * new_Stack (void *(*copy_func) (void *),
        void (*delete_func) (void *),
        FILE *(*write_func) (void *, FILE *)) {

        return new_List (copy_func, delete_func, write_func);
}
/*---------------------------------------------------------------------------
Function Name:                pop
Purpose:                      this function removes an item from the top of
                              the stack and sends it back through the output 
                              parameter item.        
Description:                  call remove_List to do the pop
							  this function first do error checks on the 
                              pointers, then check if the stack is empty, if
                              it is, output error message, if not, let long 
                              pointer be the last input element and remove the 
                              last input element.
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is null, output error message
                              if item is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns the value popped
---------------------------------------------------------------------------*/
void * pop (Stack * this_stack) {
        return remove_List (this_stack, END);
}
/*---------------------------------------------------------------------------
Function Name:                push
Purpose:                      this function add item to the top of this_Stack
Description:                  call insert to do push
							  this function has a local variable, first the
                              function checks if this_Stack is null, then it
                              checks if this_Stack is empty. if it is, output 
                              error message, if not, let last user input 
                              element equals to item. 
Input:                        *this_Stack: pointer to the stack
							  *element: pointer to the element we want to push
							  in.
Output:                       if this_Stack is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns true upon success and false upon failure.
---------------------------------------------------------------------------*/
long push (Stack * this_stack, void * element) {
        return insert (this_stack, element, END);
}
/*---------------------------------------------------------------------------
Function Name:                top
Purpose:                      this function send back the item on the top of
                              the stack through the output parameter item.
Description:                  call view to top
							  this function first do error checks on the 
                              pointers, then check if the stack is empty, if
                              it is, output error message, if not, let long 
                              pointer be the last input element.
Input:                        *this_Stack: pointer to the stack
Output:                       if this_Stack is null, output error message
                              if item is null, output error message
                              if debug is on, output debug message
                              if this_Stack is empty, output error message
Result:                       Returns the pointer to the value of the top node
---------------------------------------------------------------------------*/
void * top (Stack * this_stack) {
        return view (this_stack, END);
}

FILE * write_Stack (Stack * this_stack, FILE * stream) {
        return write_List (this_stack, stream);
}
