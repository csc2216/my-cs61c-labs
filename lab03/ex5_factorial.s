.globl factorial

.data
n: .word 4

.text
# Don't worry about understanding the code in main
# You'll learn more about function calls in lecture soon
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

# factorial takes one argument:
# a0 contains the number which we want to compute the factorial of
# The return value should be stored in a0
factorial:
    li t0, 0 # loop var
    mv t1, a0 # n
    li a0, 1
Loop:
    addi t0, t0, 1
    mul a0, a0 , t0
    blt t0, t1, Loop

    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra
