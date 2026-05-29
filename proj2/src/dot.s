.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    li t0 0
    li t1 0
    li t3 0
    li t5 0
    li t6 1
    # Prologue
    bge a2 t6 check_stride_arr0
    li a0 36
    j exit
    
check_stride_arr0:
    bge a3 t6 check_stride_arr1
    li a0 37
    j exit
    
check_stride_arr1:
    bge a4 t6 loop_start
    li a0 37
    j exit
    
# t0 for loop var, t1/t2 for cur_relative_ptr/cur_int of arr0, t3/t4 for cur_relative_ptr/cur_int of arr1, t5 for acc_dot_product
loop_start:
    beq t0 a2 loop_end
    slli t2 t1 2
    slli t4 t3 2
    add t2 t2 a0
    add t4 t4 a1
    lw t2 0(t2)
    lw t4 0(t4)
    mul t2 t2 t4
    add t5 t5 t2
    
    add t1 t1 a3
    add t3 t3 a4
    addi t0 t0 1
    
    j loop_start

loop_end:
    # Epilogue
    mv a0 t5
    jr ra
