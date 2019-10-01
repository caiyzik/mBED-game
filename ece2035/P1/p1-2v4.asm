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

			# 7 - start
			# 8 - end
			# 9 - swapcnt
			# 10 - n
			# 11 - m
			# 12 - dend
			# 13 - hend
			# 14 - dinc
			# 15 - hinc
			# 16 - sorttype
			# 18 - inc
			# 19 - Arrloop counter
			# 20 - Arrloop counter comp
			# 21 - 64

			addi $7, $0, 24		#start = 24
			addi $9, $0, 1 		#swapcnt = 1
			addi $12, $0, 700	#dend = 700
			addi $13, $0, 24    #hend = 24
			addi $14, $0, 52 	#dinc = 52
			addi $15, $0, 4		#hinc = 4
			addiu $16, $0, 1 
			addi $19, $0, 0
			addi $20, $0, 16
			addi $21, $0, 64

ArrLoop: 	andi $6, $16, 1
			bne $6, $0, DINC
			add $8, $0, $13 	#end = hend
			add $18, $0, $15	#inc = hinc
			addi $12, $12, -48  #increment diameter end point diagonally up left
			j While
	DINC:  	add $8, $0, $12 	#end = hend
			add $18, $0, $14	#inc = hinc
			addi $13, $13, 56  #increment diameter end point diagonally down right
	While:  addi $9, $0, 0 		#swapcnt = 0
			add $10, $0, $7 	#n = start
	Loop: 	add $11, $10, $18 	#m = n + inc
			lw $3, Array($10) 	# $3 <- Array[n]
			lw $4, Array($11)	# $4 <- Array[m]
			andi $6, $16, 1 
			bne $6, $0, COMP
			div $3, $20
			mfhi $3
			div $4, $20
			mfhi $4
	COMP:	slt $6, $3, $4
			bne $6, $0, Next
			lw $5, Array($10)
			lw $4, Array($11)
			sw $4, Array($10)
			sw $5, Array($11)
			addi $9, $9, 1
	Next: 	add $10, $10, $18
			add $11, $11, $18
			bne $11, $8, Loop
			bne $9, $0, While
			addi $19, $19, 1
			xori $6, $6, 1
			bne $19, $20, ArrLoop

ArrLoop2: 	andi $6, $16, 1
			bne $6, $0, DINC2
			add $8, $0, $13 	#end = hend
			add $18, $0, $15	#inc = hinc
			addi $12, $12, -48  #increment diameter end point diagonally up left
			j While2
	DINC2:  	add $8, $0, $12 	#end = hend
			add $18, $0, $14	#inc = hinc
			addi $13, $13, 56  #increment diameter end point diagonally down right
	While2:  addi $9, $0, 0 		#swapcnt = 0
			add $10, $0, $7 	#n = start
	Loop2: 	add $11, $10, $18 	#m = n + inc
			lw $3, Array($10) 	# $3 <- Array[n]
			lw $4, Array($11)	# $4 <- Array[m]
			andi $6, $16, 1 
			bne $6, $0, COMP2
			div $3, $20
			mfhi $3
			div $4, $20
			mfhi $4
	COMP2:	slt $6, $3, $4
			bne $6, $0, Next2
			lw $5, Array($10)
			lw $4, Array($11)
			sw $4, Array($10)
			sw $5, Array($11)
			addi $9, $9, 1
	Next2: 	add $10, $10, $18
			add $11, $11, $18
			bne $11, $8, Loop2
			bne $9, $0, While2
			addi $19, $19, 1
			xori $6, $6, 1
			bne $19, $20, ArrLoop2

			swi	522						# tally errors
	

End:		swi	523			# redisplay diamond
			jr	$31			# return to caller