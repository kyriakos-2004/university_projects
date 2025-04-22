.data

n: .word 10
result: .word 0
msg: .asciiz "The sum of the numbers is: "
newline: .asciiz "\n"

.text

main:
lw $a0, n
jal sum_of_natural_numbers

sw $v0, result #--
li $v0, 4      # |---(print msg)
la $a0, msg    # |
syscall        #--

li $v0, 1       #--
lw $a0, result  # |---(print result)
syscall         #--

li $v0, 4       #--
la $a0, newline # |---(print newline)
syscall         #--

li $v0, 10 #--|(program exit)
syscall    #--|

sum_of_natural_numbers:
addi $t0, $zero, 1 #(i=1)
lw $t1, n
addi $t1, $t1, 1 #(n+=1 (<=))
add $t2, $t2, $zero #sum=0

for_loop:
slt $t3, $t0, $t1 #(i<=n)
beq $t3,$zero, end #((i<=n)==false)

add $t2, $t2, $t0 #(sum+=i)
addi $t0, $t0, 1 #(i+=1)
 
j for_loop

end:
add $v0, $t2,$zero #(return sum)

jr $ra
