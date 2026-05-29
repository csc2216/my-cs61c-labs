.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
    # Check for correct number of command line arguments
    li t0 5
    bne a0 t0 arg_error

    # Prologue
    addi sp sp -32
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw ra 28(sp)

    lw s0 4(a1)  # pointer to filepath string of m0
    lw s1 8(a1)  # pointer to filepath string of m1
    lw s2 12(a1)  # pointer to filepath string of input matrix
    lw s3 16(a1)  # pointer to filepath string of output file
    mv s6 a2  # silent mode flag

    # space for pointers to num_rows and num_cols of m0, m1, and input matrix  
    addi sp sp -24

    # Read pretrained m0
    addi t0 sp 4
    mv a0 s0  # filename pointer
    mv a1 sp  # pointer to num_rows of m0
    mv a2 t0  # pointer to num_cols of m0
    jal read_matrix

    mv s0 a0  # save pointer to m0 in s0
    
    # Read pretrained m1
    addi t0 sp 8
    addi t1 sp 12
    mv a0 s1  # filename pointer
    mv a1 t0  # pointer to num_rows of m1
    mv a2 t1  # pointer to num_cols of m1
    jal read_matrix

    mv s1 a0  # save pointer to m1 in s1

    # Read input matrix
    addi t0 sp 16
    addi t1 sp 20
    mv a0 s2  # filename pointer
    mv a1 t0  # pointer to num_rows of input matrix
    mv a2 t1  # pointer to num_cols of input matrix
    jal read_matrix

    mv s2 a0  # save pointer to input matrix in s2

    # Compute h = matmul(m0, input)
    lw t0 0(sp)  # num_rows of m0
    lw t1 20(sp)  # num_cols of input matrix
    mul a0 t0 t1  # number of elements in h
    slli a0 a0 2  # size of h in bytes
    jal malloc

    beq a0 x0 malloc_error
    mv s4 a0  # save pointer to h in s4

    mv a0 s0  # m0 pointer
    lw a1 0(sp)  # m0 num_rows
    lw a2 4(sp)  # m0 num_cols
    mv a3 s2  # input matrix pointer
    lw a4 16(sp)  # input matrix num_rows
    lw a5 20(sp)  # input matrix num_cols
    mv a6 s4  # h pointer
    jal matmul

    # Compute h = relu(h)
    lw t0 0(sp)  # num_rows of m0
    lw t1 20(sp)  # num_cols of input matrix    
    mv a0 s4  # h pointer
    mul a1 t0 t1  # number of elements in h
    jal relu

    # Compute o = matmul(m1, h)
    lw t0 8(sp)  # num_rows of m1
    lw t1 20(sp)  # num_cols of h (same as num_cols of input matrix)
    mul a0 t0 t1  # number of elements in o
    slli a0 a0 2  # size of o in bytes
    jal malloc

    beq a0 x0 malloc_error
    mv s5 a0  # save pointer to o in s5

    mv a0 s1  # m1 pointer
    lw a1 8(sp)  # m1 num_rows
    lw a2 12(sp)  # m1 num_cols
    mv a3 s4  # h pointer
    lw a4 0(sp)  # h num_rows (same as m0 num_rows)
    lw a5 20(sp)  # h num_cols (same as input matrix num_cols)
    mv a6 s5  # o pointer 
    jal matmul

    # Write output matrix o
    mv a0 s3  # filename pointer
    mv a1 s5  # pointer to start of o
    lw a2 8(sp)  # num_rows of o (same as num_rows of m1)
    lw a3 20(sp)  # num_cols of o (same as num_cols of input matrix)
    jal write_matrix

    # Compute and return argmax(o)
    lw t0 8(sp)  # num_rows of m1
    lw t1 20(sp)  # num_cols of h (same as num_cols of input matrix)
    mv a0 s5  # o pointer
    mul a1 t0 t1  # number of elements in o
    jal argmax

    mv s0 a0  # move classification result into s0 to return later

    # If enabled, print argmax(o) and newline
    li t0 1
    beq s6 t0 end
    jal print_int
    li a0 '\n'
    jal print_char

    j end

end:
    # Epilogue
    mv a0 s4  # free h
    jal free

    mv a0 s5  # free o
    jal free

    mv a0 s0  # move classification result back into a0 to return

    addi sp sp 24
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


malloc_error:
    li a0 26
    j exit

arg_error:
    li a0 31
    j exit    
