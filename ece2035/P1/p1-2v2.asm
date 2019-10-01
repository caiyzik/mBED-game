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

			# 3 - current values
			# 4 - next value
			# 5 - temp
			# 6 - logical

			# 7 - arrloop counter
			# 8 - arrloop counter comparision 
			# 9 - bigloop counter 
			# 10 - bigloop counter comparision (length)
			# 11 - lil loop counter
			# 12 - lil loop counter comparision
			# 13 - next index address 
			# 14 - 52
			# 15 - start address
			# 16 - swap count

		 	#####initialize all "variables"######

		 	addi $14, $0, 52       #hold 52 here so we can add it to and mult stuff by it
		 	addi $16, $0, 0


		 	
		 	addi $7, $0, 1 			#j = 1
		 	addi $8, $0, 7			#j < 7

		 	addi $9, $0, 0          # m = 0
		 

		 	############# LEFT DIAMETER ##################

		 	addi $10, $0, 3 		# length = 3 
		 	addi $15, $0, 264
		 	add $12, $0, $10        #end offset = start offset + length*52
		 	mult $12, $14
		 	mflo $12  
		 	add $12, $12, $15

ArrLoop: 	addi $9, $0, 1          #m = 1

BigLoop:  	add $11, $0, $15 
			addi $13, $11, 52 		# get offset of next element 

LilLoop: 	lw $3, Array($11) 			# R2 = Array[i]
		 	lw $4, Array($13) 			# R3 = Array[i+1]
		 	srl $3, $3, 6
		 	srl $4, $4, 6 			# if Array[i+1] < Array[i]
		 	slt $6, $3, $4 
		 	beq $6, $0, Swap 			#then swap the values
		 	j Next 					#else increment the counters


	Swap:	lw $5, Array($11) 			#temp = Array[i]
			lw $4, Array($13)
			sw $4, Array($11) 			#Array[i] = Array[i+1]
			sw $5, Array($13)			#Array[i+1] = temp
			addi $16, $16, 1  			#increment swap count
		
	Next:   addi $11, $11, 52 			#increment current val offset by 53 to go down the column
			addi $13, $13, 52

			bne $13, $12, LilLoop 		#is i<52*length

			addi $9, $9, 1 				#m++
			bne $9, $10, BigLoop 		#is m<length

			addi $10, $10, 2 			#length = length + 2
			#update the start address
			addi $15, $15, -48
			addi $12, $12, 56

			addi $7, $7, 1       	 #j++ 
			bne $7, $8, ArrLoop       


			############# RIGHT DIAMETER ####################

			addi $7, $0, 1 			#j = 1
		 	addi $8, $0, 6			#j < 6

		 	addi $9, $0, 0          # m = 0

			addi $10, $0, 11 		# length = 11 
		 	addi $15, $0, 80
		 	add $12, $0, $10        #end offset = start offset + length*52
		 	mult $12, $14
		 	mflo $12  
		 	add $12, $12, $15

ArrLoop2: 	addi $9, $0, 1          #m = 1

BigLoop2:  	add $11, $0, $15 
			addi $13, $11, 52 		# get offset of next element 

LilLoop2: 	lw $3, Array($11) 			# R2 = Array[i]
		 	lw $4, Array($13) 			# R3 = Array[i+1]
		 	srl $3, $3, 6
		 	srl $4, $4, 6 			# if Array[i+1] < Array[i]
		 	slt $6, $3, $4 
		 	beq $6, $0, Swap2 			#then swap the values
		 	j Next2 					#else increment the counters


	Swap2:	lw $5, Array($11) 			#temp = Array[i]
			lw $4, Array($13)
			sw $4, Array($11) 			#Array[i] = Array[i+1]
			sw $5, Array($13)			#Array[i+1] = temp
			addi $16, $16, 1  			#increment swap count
		
	Next2:  addi $11, $11, 52 			#increment current val offset by 53 to go down the column
			addi $13, $13, 52

			bne $13, $12, LilLoop2 		#is i<52*length

			addi $9, $9, 1 				#m++
			bne $9, $10, BigLoop2 		#is m<length

			addi $10, $10, -2 			#length = length + 2
			#update the start address
			addi $15, $15, 56
			addi $12, $12, -48

			addi $7, $7, 1       	 #j++ 
			bne $7, $8, ArrLoop2       


			swi	522						# tally errors
		
			#check to see if errors is zero if not go back to while
			#bne $2, $0, While

			swi	523			# redisplay diamond
			jr	$31			# return to caller