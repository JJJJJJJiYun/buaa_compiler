.data
str0: .asciiz "<"
str1: .asciiz "<="
str2: .asciiz "=="
str3: .asciiz ">="
str4: .asciiz ">"
str5: .asciiz " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}"
str6: .asciiz "%c"
str7: .asciiz "n cannot be smaller or equal than 0!"
.text
add $fp, $sp, $zero
addi $gp, $gp, 65536
j main
nop
funcreturnint:
addi $sp, $sp, 8
sw $t0, -16($sp)
sw $t1, -20($sp)
sw $t2, -24($sp)
sw $t3, -28($sp)
sw $t4, -32($sp)
sw $t5, -36($sp)
sw $t6, -40($sp)
sw $s0, -44($sp)
sw $s1, -48($sp)
sw $s2, -52($sp)
sw $s3, -56($sp)
sw $s4, -60($sp)
sw $s5, -64($sp)
sw $s6, -68($sp)
sw $fp, -72($sp)
sw $ra, -76($sp)
add $fp, $sp, $zero
addi $sp, $sp, -80
lw $t8, 0($fp)
sub $t7, $zero, $t8
sw $t7, -12($fp)
lw $t9, -12($fp)
lw $t8, -4($fp)
add $t7, $t9, $t8
sw $t7, -12($fp)
lw $t9, -12($fp)
addi $t7, $t9, 2
sw $t7, -8($fp)
lw $t9, -8($fp)
addi $v0, $t9, 0
j funcreturnint$end
nop
funcreturnint$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 80
jr $ra
nop
funcreturnchar:
addi $sp, $sp, 4
sw $t0, -8($sp)
sw $t1, -12($sp)
sw $t2, -16($sp)
sw $t3, -20($sp)
sw $t4, -24($sp)
sw $t5, -28($sp)
sw $t6, -32($sp)
sw $s0, -36($sp)
sw $s1, -40($sp)
sw $s2, -44($sp)
sw $s3, -48($sp)
sw $s4, -52($sp)
sw $s5, -56($sp)
sw $s6, -60($sp)
sw $fp, -64($sp)
sw $ra, -68($sp)
add $fp, $sp, $zero
addi $sp, $sp, -72
lw $t9, 0($fp)
addi $t7, $t9, 0
sw $t7, -4($fp)
lw $t9, -4($fp)
addi $v0, $t9, 0
j funcreturnchar$end
nop
funcreturnchar$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 72
jr $ra
nop
funcrelation:
addi $sp, $sp, 4
sw $t0, -4($sp)
sw $t1, -8($sp)
sw $t2, -12($sp)
sw $t3, -16($sp)
sw $t4, -20($sp)
sw $t5, -24($sp)
sw $t6, -28($sp)
sw $s0, -32($sp)
sw $s1, -36($sp)
sw $s2, -40($sp)
sw $s3, -44($sp)
sw $s4, -48($sp)
sw $s5, -52($sp)
sw $s6, -56($sp)
sw $fp, -60($sp)
sw $ra, -64($sp)
add $fp, $sp, $zero
addi $sp, $sp, -68
lw $t9, 0($fp)
subi $t7, $t9, 7
bgez $t7, $label0
nop
li $v0, 4
la $a0, str0
syscall
j funcrelation$end
nop
j $label1
nop
$label0:
$label1:
lw $t9, 0($fp)
subi $t7, $t9, 7
bgtz $t7, $label2
nop
li $v0, 4
la $a0, str1
syscall
j funcrelation$end
nop
j $label3
nop
$label2:
$label3:
lw $t9, 0($fp)
li $t8, 17
bne $t9, $t8, $label4
nop
li $v0, 4
la $a0, str2
syscall
j funcrelation$end
nop
j $label5
nop
$label4:
$label5:
lw $t9, 0($fp)
subi $t7, $t9, 77
bltz $t7, $label6
nop
li $v0, 4
la $a0, str3
syscall
j $label7
nop
$label6:
li $v0, 4
la $a0, str4
syscall
$label7:
funcrelation$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 68
jr $ra
nop
funcprint:
sw $t0, 0($sp)
sw $t1, -4($sp)
sw $t2, -8($sp)
sw $t3, -12($sp)
sw $t4, -16($sp)
sw $t5, -20($sp)
sw $t6, -24($sp)
sw $s0, -28($sp)
sw $s1, -32($sp)
sw $s2, -36($sp)
sw $s3, -40($sp)
sw $s4, -44($sp)
sw $s5, -48($sp)
sw $s6, -52($sp)
sw $fp, -56($sp)
sw $ra, -60($sp)
add $fp, $sp, $zero
addi $sp, $sp, -64
li $v0, 4
la $a0, str5
syscall
li $v0, 1
li $t7, -10
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, str6
syscall
li $v0, 11
li $t7, 97
add $a0, $t7, $zero
syscall
funcprint$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 64
jr $ra
nop
funcdowhileandfor:
sw $t0, -16($sp)
sw $t1, -20($sp)
sw $t2, -24($sp)
sw $t3, -28($sp)
sw $t4, -32($sp)
sw $t5, -36($sp)
sw $t6, -40($sp)
sw $s0, -44($sp)
sw $s1, -48($sp)
sw $s2, -52($sp)
sw $s3, -56($sp)
sw $s4, -60($sp)
sw $s5, -64($sp)
sw $s6, -68($sp)
sw $fp, -72($sp)
sw $ra, -76($sp)
add $fp, $sp, $zero
addi $sp, $sp, -80
li $t7, 0
sw $t7, 0($fp)
$label8:
lw $t8, 0($fp)
addi $t7, $t8, 8
sll $t7, $t7, 2
lw $t9, 0($fp)
addu $t7, $t7, $gp
sw $t9, 0($t7)
lw $t9, 0($fp)
addi $t7, $t9, 1
sw $t7, 0($fp)
lw $t9, 0($fp)
subi $t7, $t9, 10
bgez $t7, $label9
nop
j $label8
nop
$label9:
li $t7, 0
sw $t7, 0($fp)
$label10:
lw $t9, 0($fp)
subi $t7, $t9, 10
bgez $t7, $label11
nop
lw $t8, 0($fp)
addi $t9, $t8, 8
sll $t9, $t9, 2
addu $t9, $t9, $gp
lw $t7, 0($t9)
sw $t7, -12($fp)
li $v0, 1
lw $t7, -12($fp)
add $a0, $t7, $zero
syscall
lw $t9, 0($fp)
addi $t7, $t9, 1
sw $t7, 0($fp)
j $label10
nop
$label11:
funcdowhileandfor$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 80
jr $ra
nop
funcrecursion:
addi $sp, $sp, 4
sw $t0, -20($sp)
sw $t1, -24($sp)
sw $t2, -28($sp)
sw $t3, -32($sp)
sw $t4, -36($sp)
sw $t5, -40($sp)
sw $t6, -44($sp)
sw $s0, -48($sp)
sw $s1, -52($sp)
sw $s2, -56($sp)
sw $s3, -60($sp)
sw $s4, -64($sp)
sw $s5, -68($sp)
sw $s6, -72($sp)
sw $fp, -76($sp)
sw $ra, -80($sp)
add $fp, $sp, $zero
addi $sp, $sp, -84
lw $t9, 0($fp)
subi $t7, $t9, 0
bgtz $t7, $label12
nop
li $v0, 4
la $a0, str7
syscall
li $v0, -1
j funcrecursion$end
nop
j $label13
nop
$label12:
$label13:
lw $t9, 0($fp)
li $t8, 1
bne $t9, $t8, $label14
nop
li $v0, 1
j funcrecursion$end
nop
j $label15
nop
$label14:
$label15:
lw $t9, 0($fp)
li $t8, 2
bne $t9, $t8, $label16
nop
li $v0, 1
j funcrecursion$end
nop
j $label17
nop
$label16:
$label17:
lw $t9, 0($fp)
subi $t7, $t9, 1
sw $t7, -4($fp)
lw $t7, -4($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcrecursion
nop
addi $t7, $v0, 0
sw $t7, -8($fp)
lw $t9, 0($fp)
subi $t7, $t9, 2
sw $t7, -12($fp)
lw $t7, -12($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcrecursion
nop
addi $t7, $v0, 0
sw $t7, -16($fp)
lw $t9, -8($fp)
lw $t8, -16($fp)
add $v0, $t9, $t8
j funcrecursion$end
nop
funcrecursion$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 84
jr $ra
nop
main:
sw $t0, -24($sp)
sw $t1, -28($sp)
sw $t2, -32($sp)
sw $t3, -36($sp)
sw $t4, -40($sp)
sw $t5, -44($sp)
sw $t6, -48($sp)
sw $s0, -52($sp)
sw $s1, -56($sp)
sw $s2, -60($sp)
sw $s3, -64($sp)
sw $s4, -68($sp)
sw $s5, -72($sp)
sw $s6, -76($sp)
sw $fp, -80($sp)
sw $ra, -84($sp)
add $fp, $sp, $zero
addi $sp, $sp, -88
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, 24($gp)
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, 28($gp)
li $v0, 12
syscall
add $t7, $v0, $zero
sw $t7, 72($gp)
addi $t7, $zero, 19
sll $t7, $t7, 2
li $t9, 122
addu $t7, $t7, $gp
sw $t9, 0($t7)
lw $t9, 24($gp)
lw $t8, 28($gp)
bne $t9, $t8, $label18
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcreturnint
nop
addi $t7, $v0, 0
sw $t7, 0($fp)
li $v0, 1
lw $t7, 0($fp)
add $a0, $t7, $zero
syscall
j $label19
nop
$label18:
$label19:
lw $t9, 24($gp)
lw $t8, 28($gp)
sub $t7, $t9, $t8
blez $t7, $label20
nop
lw $t7, 72($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcreturnchar
nop
addi $t7, $v0, 0
sw $t7, -4($fp)
li $v0, 11
lw $t7, -4($fp)
add $a0, $t7, $zero
syscall
j $label21
nop
$label20:
$label21:
lw $t9, 72($gp)
li $t8, 97
bne $t9, $t8, $label22
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcrelation
nop
j $label23
nop
$label22:
$label23:
lw $t9, 72($gp)
li $t8, 45
bne $t9, $t8, $label24
nop
jal funcprint
nop
j $label25
nop
$label24:
$label25:
lw $t9, 72($gp)
li $t8, 47
bne $t9, $t8, $label26
nop
jal funcdowhileandfor
nop
j $label27
nop
$label26:
$label27:
addi $t9, $zero, 19
sll $t9, $t9, 2
addu $t9, $t9, $gp
lw $t7, 0($t9)
sw $t7, -16($fp)
lw $t9, 72($gp)
lw $t8, -16($fp)
bne $t9, $t8, $label28
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcrecursion
nop
addi $t7, $v0, 0
sw $t7, -20($fp)
li $v0, 1
lw $t7, -20($fp)
add $a0, $t7, $zero
syscall
j $label29
nop
$label28:
$label29:
li $v0, 10
syscall