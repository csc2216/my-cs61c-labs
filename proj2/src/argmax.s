.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    li t0 1
    li t1 1
    li t2 0
    addi t4 a1 -1
    bge a1 t1 loop_start
    li a0 36 
    j exit

# t0 for the loop var, t1 for the cur_int, t2 for cur_largest_index, t3 for cur_largest_int, t4 for a1 - 1
loop_start:
    beq a1 t0 loop_end
    slli t1 t0 2
    add t1 t1 a0
    lw t1 0(t1)
    slli t3 t2 2
    add t3 t3 a0
    lw t3 0(t3)
    blt t3 t1 loop_continue
    addi t0 t0 1
    j loop_start
    
loop_continue:
    mv t2 t0
    addi t0 t0 1
    j loop_start

loop_end:
    # Epilogue
    mv a0 t2
    
    jr ra
