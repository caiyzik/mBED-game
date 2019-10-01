#include <stdio.h>
#include <stdlib.h>

/* 
 Student Name: Tiffany Montgomery
 Date: January 29, 2018

ECE 2035 Homework 1-2

This is the only file that should be modified for the C implementation
of Homework 1.

This program computes the maximum magnitude for the elements of array A
and prints the value of the element with maximum magnitude out.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

*/

//DO NOT change the following declaration (you may change the initial value).
int A[] = {1, -14, 9, 10, -11, 6, 56, -160, 78, 100, 4,  -5, 0,  150,  -5, 9};

int maxmag;
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

  //idea: store a positive version of each number before doing comparisons....

  for (i = 1; i < 15; i++){
    if (maxmag < 0 && A[i] > 0){
      if (0-maxmag < A[i])
        maxmag = A[i];
    }
    else if (maxmag > 0 && A[i] < 0){
      if (maxmag < 0-A[i])
        maxmag = A[i];
    }
    else if (maxmag < 0 && A[i] <= 0){
      if (0-maxmag < 0-A[i])
        maxmag = A[i];
    }
    else if (maxmag < A[i]){
      maxmag = A[i];
    }
    printf("Current max val: %d\n", maxmag);
    
        	 
  }

  printf("%d is the value of the element with maximum magitude. \n", maxmag);
  return 0;
}

