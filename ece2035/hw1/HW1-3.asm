# HW1-3
# Student Name:
# Date:
#
# This program computes the maximum magnitude for the elements of array A
# and stores the value of the element with maximum magnitude at the label maxmag:
#

.data
# DO NOT change the following three labels (you may change the initial values):
A:     .word 1, -14, 9, 10, -11, 6, 56, -60, 78, 100, 4,  -5, 0,  3,  -5,  9

maxmag: .alloc 1
	
.text
                # $1 - temp max value
                # $2 - next comparison value
                # $3 - address increment
                # $4 - logical if less than
                # $5 - final address 
                
                
                addi $5, $0, 60     #initialize final increment value
                addi $3, $0, 4  	#initialize counter

                lw $1, A($0) 		#load first element from array in memory

        Loop: 	lw $2, A($3)             #load the value to compare temp max to
                slt $4, $1, $2      #determine is $1 (current max) is less than the next value
                
                bne $4, $0, New    #if $1(current max) is less than $2
        New: 	lw $1, A($3)      #load the value in $2 in $1

                addi $3, $3, 4 		#increment the counter
                bne $3, $5, Loop

                sw $2, maxmag($0) 	#store the max value in maxmag

                jr $31   # return to OS


