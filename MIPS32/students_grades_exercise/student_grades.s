.data

arrayIndex: .space 40
arrayMarks: .space 40
numstudents: .word 10
addmsg: .asciiz "1. Add Student\n"
dispmsg: .asciiz "2. Display All Students\n"
searchmsg: .asciiz "3. Search by Index Number\n"
dispavgmsg: .asciiz "4. Display Average Marks\n"
exitmsg: .asciiz "5. Exit\n"
choicemsg: .asciiz "Enter your choice: "
notfound_err: .asciiz "Student not found.\n\n"
student_added: .asciiz "Student added successfully!\n\n"
exitingmsg: .asciiz "Exiting program."
index_msg: .asciiz "Index No: "
enter_index_msg: .asciiz "Enter index number: "
enter_index_search_msg: .asciiz "Enter index number to search: "
enter_mark_msg: .asciiz "Enter marks: "
marks_msg: .asciiz ", Marks: "
avgmarks_msg: .asciiz "Average Marks: "
newline: .asciiz "\n"

.text

main:
li $t0,0
li $t1,10
la $t2, arrayIndex
la $t3, arrayMarks

initialize_arr:
beq $t0,$t1, end_initialization
mul $t4, $t0, 4
add $t5, $t2, $t4
li $t6,-1
sw $t6, 0($t5)
add $t5, $t3, $t4
sw $t6, 0($t5)
addi $t0,$t0,1
j initialize_arr

end_initialization:
la $s0, arrayIndex
la $s1, arrayMarks

students_grade_organizer:
li $v0, 4
la $a0, addmsg
syscall 

li $v0, 4
la $a0, dispmsg
syscall 

li $v0, 4
la $a0, searchmsg
syscall 

li $v0, 4
la $a0, dispavgmsg
syscall 

li $v0, 4
la $a0, exitmsg
syscall 

li $v0, 4
la $a0, choicemsg
syscall

li $v0, 5
syscall

li $t0, 1
beq $v0,$t0, add_student
li $t0, 2
beq $v0,$t0, disp_all_students
li $t0, 3
beq $v0,$t0, search_students
li $t0, 4
beq $v0,$t0, disp_avg_marks
li $t0, 5
beq $v0,$t0, exiting
li $v0, 4
la $a0, newline
syscall
j students_grade_organizer

add_student:
li $v0, 4
la $a0, enter_index_msg
syscall

li $v0, 5
syscall
addi $t0,$v0,0

li $v0, 4
la $a0, enter_mark_msg
syscall

li $v0, 5
syscall
addi $t1,$v0,0

mul $t2,$t0,4
add $t3, $s0, $t2
sw $t0, 0($t3)
add $t3, $s1, $t2
sw $t1, 0($t3)
 
li $v0, 4
la $a0, student_added
syscall

j students_grade_organizer
 
disp_all_students:
li $t0,0
li $t1,10

disp_all_loop:
beq $t0,$t1, end_disp_all_loop
mul $t2, $t0, 4
add $t3, $s0, $t2
add $t4, $s1, $t2
lw $t3, 0($t3)
lw $t4, 0($t4)
li $t5, -1
beq $t3,$t5, cont

li $v0, 4
la $a0, index_msg
syscall

li $v0, 1
addi $a0, $t3, 0
syscall

li $v0, 4
la $a0, marks_msg
syscall

li $v0, 1
addi $a0, $t4, 0
syscall

li $v0, 4
la $a0, newline
syscall

addi $t0,$t0,1
j disp_all_loop

cont:
addi $t0,$t0,1
j disp_all_loop

end_disp_all_loop:
li $v0, 4
la $a0, newline
syscall
j students_grade_organizer

search_students:
li $v0, 4
la $a0, enter_index_search_msg
syscall

li $v0, 5
syscall

addi $t0,$v0,0
la $t1, arrayIndex
mul $t3,$t0,4
add $t3,$t1,$t3
lw $t3, 0($t3)
li $t4,-1
beq $t4,$t3, not_found
 
li $v0, 4
la $a0, index_msg
syscall

li $v0, 1
addi $a0, $t3, 0
syscall

li $v0, 4
la $a0, marks_msg
syscall

la $t4, arrayMarks
mul $t3,$t0,4
add $t3,$t4,$t3
lw $t3, 0($t3)
li $v0, 1
addi $a0, $t3, 0
syscall

li $v0, 4
la $a0, newline
syscall

li $v0, 4
la $a0, newline
syscall
j students_grade_organizer

not_found:
li $v0, 4
la $a0, notfound_err
syscall
j students_grade_organizer

disp_avg_marks:
li $v0, 4
la $a0, avgmarks_msg
syscall

li $t0,0
li $t1, 10
li $t2, -1
la $t3, arrayMarks
li $t5,0
li $t6,0

avg_loop:
beq $t0,$t1, end_avg_loop
mul $t4,$t0,4
add $t4,$t4,$t3
lw $t4,0($t4)
beq $t4,$t2, skip
add $t5,$t5,$t4
addi $t6,$t6,1
addi $t0,$t0,1
j avg_loop

end_avg_loop:
li $v0, 1
beq $t6,$zero, div_zero
div $t6,$t5,$t6
addi $a0, $t6, 0
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, newline
syscall
j students_grade_organizer

div_zero:
addi $t6,$t6,1
div $t6,$t5,$t6
addi $a0, $t6, 0
syscall
li $v0, 4
la $a0, newline
syscall
li $v0, 4
la $a0, newline
syscall
j students_grade_organizer

skip:
addi $t0,$t0,1
j avg_loop

exiting:
li $v0, 4
la $a0, exitingmsg
syscall
li $v0, 10
syscall
