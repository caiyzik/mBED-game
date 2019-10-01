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
    
	################### TOP HUE #####################################
		 	addi $7, $0, 1 			#j = 1
		 	addi $8, $0, 312			#j < 7

		 	addi $9, $0, 0          # m = 0

			addi $10, $0, 3 		# length = 3
		 	addi $15, $0, 24
		 	addi $12, $0, 28        #end offset = start offset + 12

ArrLoop3: 	addi $15, $15, 48
			addi $12, $12, 56
BigLoop3:  	add $11, $0, $15 
			addi $13, $11, 4 		# get offset of next element 
			addi $16, $0, 0

LilLoop3: 	lw $3, Array($11) 			# R2 = Array[i]
		 	lw $4, Array($13) 			# R3 = Array[i+1]
		 	andi $3, $3, 0x3F
		 	andi $4, $4, 0x3F   			# if Array[i+1] < Array[i]
		 	slt $6, $3, $4 
		 	beq $6, $0, Swap3 			#then swap the values
		 	j Next3 					#else increment the counters


	Swap3:	lw $5, Array($11) 			#temp = Array[i]
			lw $4, Array($13)
			sw $4, Array($11) 			#Array[i] = Array[i+1]
			sw $5, Array($13)			#Array[i+1] = temp
			addi $16, $16, 1  			#increment swap count
		
	Next3:  addi $11, $11, 4 			
			addi $13, $13, 4

			bne $13, $12, LilLoop3 		#is i<52*length

			beq $16, $0, Again 		#is m<length
			j BigLoop3
			
Again:		bne $15, $8, ArrLoop3 
	#################################################################

			swi	522						# tally errors
		
End:		swi	523			# redisplay diamond
			jr	$31			# return to caller