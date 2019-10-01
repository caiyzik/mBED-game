#   SortDiamond size-hue sorter
#
#   <date>                <your name here>

.data
Array:		.alloc 169				# allocate static space for diamond

.text

# comments go here

SortDiamond: addi	$01, $00, Array		# set memory base
			swi	521			# create sort diamond and update memory
			
			#Registers:
			# 1 - base address
			# 2 - error count

			# 3 - current value
			# 4 - next value
			# 5 - temp
			# 6 - logical

			# 7 - arrloop counter (j)
			# 8 - arrloop counter comparision 
			# 11 - lil loop counter (current index address offset) (n)
			# 12 - lil loop counter comparision
			# 13 - next index address offset
			# 14 - 52
			# 15 - starting address
			# 16 - swap count
			# 17 - 64
			#9 - 7

			addi $9, $0, 7
			addi $14, $0, 52       #hold 52 here so we can add it to and mult stuff by it
			addi $17, $0, 64

			addi $18, $0, 0
			addi $19, $0, 30

		 	############# DIAMETER SORT ##################
While:   	addi $18, $18, 1         #swapcount = 0
		 	
		 	addi $7, $0, 0 			#j = 1
		 	addi $8, $0, 13			#j < 7
		 	addi $15, $0, 264		# start = 264; left side 
		 	addi $12, $0, 420       # end offset = start offset + length*52

ArrLoop: 	slti $4, $7, 7
			beq $4, $0, RightHalf
			addi $15, $15, -48      #update start address
			addi $12, $12, 56		#update end address
			j BigLoop
			
RightHalf:  addi $15, $15, 56    		#update the start address
			addi $12, $12, -48 			#update end address 

BigLoop:  	add $11, $0, $15        # n = start
			addi $13, $11, 52 		# n + 1 = start + 52; get offset of next element 
			addi $16, $0, 0        #swapcount = 0

LilLoop: 	lw $3, Array($11) 		# R3 = Array[n]
		 	lw $4, Array($13) 		# R4 = Array[n+1]			
		 	slt $6, $3, $4 			# if Array[n+1] < Array[n]
		 	beq $6, $0, Swap 		# then swap the values
		 	j Next 					# else increment the counters

	Swap:	lw $5, Array($11) 		# temp = Array[n]
			sw $4, Array($11) 		# Array[n] = Array[n+1]
			sw $5, Array($13)		# Array[n+1] = temp
			addi $16, $16, 1  		# increment swap count
		
	Next:   addi $11, $11, 52 		# n+52; add 52 to go down the column
			addi $13, $13, 52
			   
			bne $13, $12, LilLoop 	#is i<52*length; if so go to beginning of the loop

			bne $16, $0, BigLoop 	#is m<length

			addi $7, $7, 1       	#j++ 
			bne $7, $9, Again
			addi $15, $0, 80
		 	addi $12, $0, 652        #end offset = start offset + length*52

Again:		bne $7, $8, ArrLoop     

			swi	522						# tally errors
		
			#check to see if errors is zero if not go back to while
			beq $2, $0, End
			bne $18, $19, While

End:		swi	523			# redisplay diamond
			jr	$31			# return to caller
