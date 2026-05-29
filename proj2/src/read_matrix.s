.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp sp -28
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw ra 24(sp)

    mv s0 a0  # filename pointer
    mv s1 a1  # pointer to num_rows
    mv s2 a2  # pointer to num_cols

    # open the file
    mv a0 s0  # filename pointer
    mv a1 x0  # mode = "r"
    jal fopen

    li t0 -1
    beq a0 t0 fopen_error  

    mv s3 a0  # save file descriptor in s3

    # read in the dimensions of the matrix
    mv a0 s3  # file descriptor
    mv a1 s1  # pointer to num_rows
    li a2 4   # size of int
    jal fread
    
    li t0 4
    bne a0 t0 fread_error


    mv a0 s3  # file descriptor
    mv a1 s2  # pointer to num_cols
    li a2 4   # size of int
    jal fread

    li t0 4
    bne a0 t0 fread_error

    # allocate memory for the matrix
    lw t0 0(s1)  # num_rows
    lw t1 0(s2)  # num_cols
    mul t0 t0 t1  # num_rows * num_cols
    slli s4 t0 2  # num_rows * num_cols * size of int in s4
    mv a0 s4  # size of memory to allocate
    jal malloc

    beq a0 x0 malloc_error
    mv s5 a0  # save pointer to matrix in s5

    # read in the matrix
    mv a0 s3  # file descriptor
    mv a1 s5  # pointer to matrix (already allocated)
    mv a2 s4  # number of bytes to read in (num_rows * num_cols * size of int)
    jal fread

    bne a0 s4 fread_error

    # close the file
    mv a0 s3  # file descriptor
    jal fclose

    bne a0 x0 fclose_error

    # Epilogue
    mv a0 s5  # pointer to matrix in memory
    lw a1 0(s1)  # num_rows
    lw a2 0(s2)  # num_cols

    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw ra 24(sp)
    addi sp sp 28

    jr ra


malloc_error:
    li a0 26
    j exit

fopen_error:
    li a0 27
    j exit        

fclose_error:
    li a0 28
    j exit

fread_error:
    li a0 29
    j exit