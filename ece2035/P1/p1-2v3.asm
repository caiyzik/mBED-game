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
			# 9 - bigloop counter  (m)
			# 10 - bigloop counter comparision (length)
			# 11 - lil loop counter (current index address offset) (n)
			# 12 - lil loop counter comparision
			# 13 - next index address offset
			# 14 - 52
			# 15 - starting address
			# 16 - swap count
			# 17 - 64

			addi $14, $0, 52       #hold 52 here so we can add it to and mult stuff by it
			addi $17, $0, 64

			addi $18, $0, 0
			addi $19, $0, 30

		 	############# LEFT DIAMETER ##################
While:   	addi $18, $18, 1         #swapcount = 0

		 	addi $8, $0, 24		

		 	addi $15, $0, 312		# start = 264; left side 

		 	addi $12, $0, 364       # end offset = start offset + length*52

ArrLoop: 	addi $15, $15, -48      #update start address
			addi $12, $12, 56		#update end address

InnerWhile: add $11, $0, $15        # n = start
			addi $13, $11, 52 		# n + 1 = start + 52; get offset of next element 
			addi $16, $0, 0         #swapcount = 0

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

			bne $16, $0, InnerWhile    #if swapcount is zero go to next column

			bne $15, $8, ArrLoop 



			############# RIGHT DIAMETER ####################
		 	addi $8, $0, 304		

ArrLoop2: 	addi $15, $15, 56      #update start address
			addi $12, $12, -48		#update end address

InnerWhile2: add $11, $0, $15        # n = start
			addi $13, $11, 52 		# n + 1 = start + 52; get offset of next element 
			addi $16, $0, 0         #swapcount = 0

LilLoop2: 	lw $3, Array($11) 		# R3 = Array[n]
		 	lw $4, Array($13) 		# R4 = Array[n+1]			
		 	slt $6, $3, $4 			# if Array[n+1] < Array[n]
		 	beq $6, $0, Swap2 		# then swap the values
		 	j Next2 					# else increment the counters

	Swap2:	lw $5, Array($11) 		# temp = Array[n]
			sw $4, Array($11) 		# Array[n] = Array[n+1]
			sw $5, Array($13)		# Array[n+1] = temp
			addi $16, $16, 1  		# increment swap count
		
	Next2:   addi $11, $11, 52 		# n+52; add 52 to go down the column
			addi $13, $13, 52
			   
			bne $13, $12, LilLoop2 	#is i<52*length; if so go to beginning of the loop

			bne $16, $0, InnerWhile2    #if swapcount is zero go to next column

			bne $15, $8, ArrLoop2 

				################### TOP HUE #####################################
		 		addi $7, $0, 1 			#j = 1
		 	addi $8, $0, 7			#j < 7

		 	addi $9, $0, 0          # m = 0

			addi $10, $0, 3 		# length = 3
		 	addi $15, $0, 72
		 	addi $12, $15, 12        #end offset = start offset + 12
		 	addi $16, $0, 0

ArrLoop3: 	addi $9, $0, 1          #m = 1

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
		
	Next3:  addi $11, $11, 4 			#increment current val offset by 53 to go down the column
			addi $13, $13, 4

			bne $13, $12, LilLoop3 		#is i<52*length
			beq $16, $0, NextCol3

			addi $9, $9, 1 				#m++
			bne $9, $10, BigLoop3 		#is m<length

NextCol3:	addi $10, $10, 2 			#length = length + 2
			#update the start address
			addi $15, $15, 48
			addi $12, $12, 56

			addi $7, $7, 1       	 #j++ 
			bne $7, $8, ArrLoop3 


			################### BOTTOM HUE #####################################

			addi $7, $0, 1 			#j = 1
		 	addi $8, $0, 6			#j < 6

		 	addi $9, $0, 0          # m = 0

			addi $10, $0, 11 		# length = 3
		 	addi $15, $0, 368
		 	addi $12, $15, 44        #end offset = start offset + 12

ArrLoop4: 	addi $9, $0, 1          #m = 1

BigLoop4:  	add $11, $0, $15 
			addi $13, $11, 4 		# get offset of next element 
			addi $16, $0, 0

LilLoop4: 	lw $3, Array($11) 			# R2 = Array[i]
		 	lw $4, Array($13) 			# R3 = Array[i+1]
		 	andi $3, $3, 0x3F
		 	andi $4, $4, 0x3F  			
		 	slt $6, $3, $4 				# if Array[i+1] < Array[i]
		 	beq $6, $0, Swap4 			#then swap the values
		 	j Next4 					#else increment the counters

	Swap4:	lw $5, Array($11) 			#temp = Array[i]
			lw $4, Array($13)
			sw $4, Array($11) 			#Array[i] = Array[i+1]
			sw $5, Array($13)			#Array[i+1] = temp
			addi $16, $16, 1  			#increment swap count
		
	Next4:  addi $11, $11, 4 			#increment current val offset by 53 to go down the column
			addi $13, $13, 4

			bne $13, $12, LilLoop4 		#is i<52*length
			beq $16, $0, NextCol4

			addi $9, $9, 1 				#m++
			bne $9, $10, BigLoop4 		#is m<length

NextCol4:	addi $10, $10, -2 			#length = length + 2
			#update the start address
			addi $15, $15, 56
			addi $12, $12, 48

			addi $7, $7, 1       	 #j++ 
			bne $7, $8, ArrLoop4 


	

			swi	522						# tally errors
		
			#check to see if errors is zero if not go back to while
			beq $2, $0, End
			bne $18, $19, While

End:		swi	523			# redisplay diamond
			jr	$31			# return to caller