.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

    # Prologue
    addi sp sp -28
    sw a2 0(sp)  # save number of rows
    sw a3 4(sp)  # save number of columns
    sw s0 8(sp)
    sw s1 12(sp)
    sw s2 16(sp)
    sw s3 20(sp)
    sw ra 24(sp)

    mv s0 a0  # filename pointer
    mv s1 a1  # pointer to start of matrix

    #open the file to write
    li t0 1  
    mv a0 s0  # filename pointer
    mv a1 t0  # mode = "w"
    jal fopen

    li t0 -1
    beq a0 t0 fopen_error 

    mv s2 a0  # save file descriptor in s2

    # write the dimensions of the matrix to the file
    li s3 1   
    mv a0 s2  # file descriptor
    mv a1 sp  # pointer to number of rows
    mv a2 s3   # one item
    li a3 4   # size of int
    jal fwrite

    blt a0 s3 fwrite_error

    addi t0 sp 4  # pointer to number of columns
    mv a0 s2  # file descriptor
    mv a1 t0  # pointer to number of columns
    mv a2 s3   # one item
    li a3 4   # size of int
    jal fwrite

    blt a0 s3 fwrite_error

    # write the matrix to the file
    lw t0 0(sp)  # number of rows
    lw t1 4(sp)  # number of columns
    mul s3 t0 t1  # total number of elements in the matrix
    mv a0 s2  # file descriptor
    mv a1 s1  # pointer to start of matrix
    mv a2 s3  # number of elements to write
    li a3 4   # size of each element
    jal fwrite

    blt a0 s3 fwrite_error

    # close the file
    mv a0 s2  # file descriptor
    jal fclose

    bne a0 x0 fclose_error

    # Epilogue
    lw s0 8(sp)
    lw s1 12(sp)
    lw s2 16(sp)
    lw s3 20(sp)
    lw ra 24(sp)
    addi sp sp 28

    jr ra


fopen_error:
    li a0 27
    j exit        

fclose_error:
    li a0 28
    j exit

fwrite_error:
    li a0 30
    j exit        
