#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name:
 Date:

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

This program computes the maximum magnitude for the elements of array A
and prints the value of the element with maximum magnitude out.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/

//DO NOT change the following declaration (you may change the initial value).
int A[] = {1, -14, 9, 10, -11, 6, 56, -60, 78, 100, 4,  -5, 0,  3,  -5, 9};

unsigned maxmag;
/*
For the grading scripts to run correctly, the above declarations
must be the first lines of code in this file (for this homework
assignment only).  Under penalty of grade point loss, do not change
these line, except to replace the initial values while you are testing
your code.

Also, do not include any additional libraries.
 */

int i;

int main() {

  maxmag = 0; // temporary initial value for shell (replace this)

  // Your program should use this print statement.
  // Do not change the format!

  for (i = 0; i < 16; i++){
  	if (A[i] > maxmag)
  		maxmag = A[i];
  	 
  }
  printf("%d is the value of the element with maximum magnitude.\n”, maxmag);

  return 0;
}

