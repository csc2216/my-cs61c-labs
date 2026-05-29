.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    li t0 1
    blt a1 t0 err_38
    blt a2 t0 err_38
    blt a4 t0 err_38
    blt a5 t0 err_38
    bne a2 a4 err_38
    
    # Prologue
    # save original arguments in s registers
    addi sp sp -32
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw ra 28(sp)  
    
    mv s0 a0  # m0 pointer
    mv s1 a1  # m0 rows
    mv s2 a2  # m0 cols
    mv s3 a3  # m1 pointer
    mv s4 a4  # m1 rows (equal to m0 cols)
    mv s5 a5  # m1 cols
    mv s6 a6  # d pointer

    li t0 0
    li t1 0

    j outer_loop_start


err_38:
    li a0 38
    j exit


# t0: outer loop index
# t1: inner loop index
# t2: address of start of m0 in dot
# t3: address of start of m1 in dot
# t4: current address of output array
outer_loop_start:
    beq t0 s1 outer_loop_end  

    slli t2 s2 2   # bytes in a row of m0
    mul t2 t2 t0   # offset to the start of the current row of m0
    add t2 t2 s0   # address of the start of the current row of m0

inner_loop_start:
    beq t1 s5 inner_loop_end

    slli t3 t1 2
    add t3 t3 s3  # address of the start of the current column of m1

    slli t4 s5 2   # bytes in a row of output array
    mul t4 t4 t0   # offset to the start of the current row of output array
    add t4 t4 s6   # address of the start of the current row of output array
    slli t5 t1 2
    add t4 t4 t5   # address of the current element of output array

    # call dot product function
    addi sp sp -20
    sw t0 0(sp)  
    sw t1 4(sp)
    sw t2 8(sp)
    sw t3 12(sp)
    sw t4 16(sp)

    mv a0 t2  
    mv a1 t3  
    mv a2 s2
    li a3 1
    mv a4 s5

    jal dot

    lw t0 0(sp)
    lw t1 4(sp)
    lw t2 8(sp)
    lw t3 12(sp)
    lw t4 16(sp)
    addi sp sp 20

    sw a0 0(t4)  # store the result of the dot product in the output array

    addi t1 t1 1
    j inner_loop_start

inner_loop_end:

    addi t0 t0 1
    li t1 0
    j outer_loop_start


outer_loop_end:

    # Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw ra 28(sp)
    addi sp sp 32

    jr ra
