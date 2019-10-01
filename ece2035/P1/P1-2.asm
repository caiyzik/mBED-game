#   SortDiamond size-hue sorter
#
#   2/28/18                Tiffany Montgomery

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
			# 7 - start address
			# 8 - end address
			# 9 - current counter
			# 10 - next address offset
			# 11 - final start value
			# 12 - swap count
			# 13 - diameter 1 
			# 14 - diameter 2
			
			addi $11, $0, 412

While:		addi $7, $0, 76		#start = 76
			addi $8, $0, 308	#end = 316
			addi $16, $16, 0
			
Coloop: 	addi $8, $8, 56	
			add $9, $0, $7 		#i = start
			
Loop:		addi $10, $9, -52	#i+1 = start - 52
			lw $3, Array($9)    # $3 = Array[i]
			lw $4, Array($10)	# $4 = Array[i+1]
			slt $6, $3, $4 		#if Array[i+1] > Array[i] $6 is true
			bne $6, $0, SwapDH

Next1:		addi $10, $9, 52
			lw $4, Array($10)
			slt $6, $3, $4
			beq $6, $0, SwapDL

Next2: 		andi $13, $3, 0x3F   #Get the hue of Array[i]
			addi $10, $9, -4 	#Get the element to the right of Array[i]
			lw $4, Array($10)  
			andi $14, $4, 0x3F	#Get the hue of Array[i+1]
			slt $6, $13, $14 		
			bne $6, $0, SwapHL
			
Next3:		addi $10, $9, 4    #Get the value of the element to the left of Array[i]
			lw $4, Array($10)   
			andi $14, $4, 0x3F	#Get the hue
			slt $6, $13, $14      
			beq $6, $0, SwapHH
			j Inc

SwapDH:     lw $5, Array($9) 		# temp = Array[i]
			sw $4, Array($9) 		# Array[n] = Array[n+1]
			sw $5, Array($10)		# Array[n+1] = temp
			lw $3, Array($9)
			addi $16, $16, 1
			j Next1
SwapDL: 	lw $5, Array($9) 		# temp = Array[i]
			sw $4, Array($9) 		# Array[n] = Array[n+1]
			sw $5, Array($10)		# Array[n+1] = temp
			lw $3, Array($9)
			addi $16, $16, 1	
			j Next2
SwapHL:     lw $5, Array($9) 		# temp = Array[i]
			sw $4, Array($9) 		# Array[n] = Array[n+1]
			sw $5, Array($10)		# Array[n+1] = temp
			lw $3, Array($9)
			addi $16, $16, 1
			j Next3
SwapHH: 	lw $5, Array($9) 		# temp = Array[i]
			sw $4, Array($9) 		# Array[n] = Array[n+1]
			sw $5, Array($10)		# Array[n+1] = temp
			lw $3, Array($9)
			addi $16, $16, 1

Inc:		addi $9, $9, 48
			bne $9, $8, Loop
			
			addi $7, $7, 56
			bne $7, $11, Coloop
			
			swi	522					# tally errors

			beq $16, $0, End
			j While
			
	End:		swi	523			# redisplay diamond
			jr	$31			# return to caller
