.data
num1: .float 0.0
num2: .float 0.0
space: .asciiz " " 
equals: .asciiz " = "
error_msg: .asciiz "Error: Diviosoin by zero is not allowed!\n"
result_msg: .asciiz "Result: "
repeat_msg: .asciiz "\nPerform another calculation? (1 for Yes/ 0 for No ): "
opperation_msg: .asciiz "Enter operation (+ ,-, *, /, %): "
exiting_msg: .asciiz "Exiting the program!"
addition: .asciiz "+"
substruction: .asciiz "-"
division: .asciiz "/"
multiplication: .asciiz "*"
modulo: .asciiz "%"
operator: .space 2
msg1: .asciiz "\nEnter first number: "
msg2: .asciiz "Enter second number: "
newline: .asciiz "\n"

.text

main:

calculator:
li $v0, 4
la $a0, msg1
syscall

li $v0, 6
syscall

swc1 $f0, num1  

li $v0, 4
la $a0, msg2
syscall

li $v0, 6
syscall

swc1 $f0, num2  

li $v0, 4
la $a0, opperation_msg
syscall

li $v0, 8
la $a0, operator
li $a1, 2
syscall

li $v0, 4
la $a0, newline
syscall

la $t0, operator
la $t1, addition
la $t2, substruction
la $t3, multiplication
la $t4, division
la $t5, modulo

lb $t0, 0($t0)
lb $t1, 0($t1)
lb $t2, 0($t2)
lb $t3, 0($t3)
lb $t4, 0($t4)
lb $t5, 0($t5)

beq $t0,$t1, calc_add
beq $t0,$t2, calc_sub
beq $t0,$t3, calc_mul
beq $t0,$t4, calc_div
beq $t0,$t5, calc_mod

calc_mod:
lwc1 $f1, num2
li.s $f2, 0.0
c.eq.s $f1,$f2
bc1t division_zero
 
li $v0, 4
la $a0, result_msg
syscall

li $v0, 2
lwc1 $f12,num1
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 4
la $a0, operator
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 2
lwc1 $f12,num2
syscall

li $v0, 4
la $a0, equals
syscall

li $v0, 2
lwc1 $f1, num1
lwc1 $f2, num2
abs.s $f3, $f1
abs.s $f2, $f2

while:
c.le.s $f2,$f3
bc1t while_body
j done

while_body:
sub.s $f3,$f3,$f2
j while

done:
li.s $f4,0.0
c.lt.s $f1,$f4
bc1t neg_mod
add.s $f12,$f3,$f4
syscall
j end

neg_mod:
li.s $f5,-1.0
mul.s $f3, $f3,$f5
add.s $f12,$f3,$f4
syscall

end:
li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit

calc_div:
lwc1 $f1, num2
li.s $f2, 0.0
c.eq.s $f1,$f2
bc1t division_zero
 
li $v0, 4
la $a0, result_msg
syscall

li $v0, 2
lwc1 $f12,num1
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 4
la $a0, operator
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 2
lwc1 $f12,num2
syscall

li $v0, 4
la $a0, equals
syscall

li $v0, 2
lwc1 $f5, num1
lwc1 $f7, num2
div.s $f12, $f5,$f7
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit

calc_mul:
li $v0, 4
la $a0, result_msg
syscall

li $v0, 2
lwc1 $f12,num1
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 4
la $a0, operator
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 2
lwc1 $f12,num2
syscall

li $v0, 4
la $a0, equals
syscall

li $v0, 2
lwc1 $f0, num1
lwc1 $f1, num2
mul.s $f12, $f0,$f1
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit

calc_sub:
li $v0, 4
la $a0, result_msg
syscall

li $v0, 2
lwc1 $f12,num1
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 4
la $a0, operator
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 2
lwc1 $f12,num2
syscall

li $v0, 4
la $a0, equals
syscall

li $v0, 2
lwc1 $f0, num1
lwc1 $f1, num2
sub.s $f12, $f0,$f1
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit

calc_add:
li $v0, 4
la $a0, result_msg
syscall

li $v0, 2
lwc1 $f12,num1
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 4
la $a0, operator
syscall

li $v0, 4
la $a0, space
syscall

li $v0, 2
lwc1 $f12,num2
syscall

li $v0, 4
la $a0, equals
syscall

li $v0, 2
lwc1 $f0, num1
lwc1 $f1, num2
add.s $f12, $f0,$f1
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit 

exit:
li $v0, 4
la $a0, exiting_msg
syscall

li $v0, 10
syscall

division_zero:
li $v0, 4
la $a0, error_msg
syscall

li $v0, 4
la $a0, repeat_msg
syscall

li $v0, 5
syscall

addi $t0,$zero,1
beq $v0,$t0,calculator
j exit 
