.import ../src/utils.s
.import ../src/../coverage-src/squared_loss.s

.data
.align 4
m0: .word 1 3 7 17
.align 4
m1: .word 4 8 2 11
.align 4
m2: .word -1 -1 -1 -1

.globl main_test
.text
# main_test function for testing
main_test:

    # load address to array m0 into a0
    la a0 m0

    # load address to array m1 into a1
    la a1 m1

    # load 0 into a2
    li a2 0

    # load address to array m2 into a3
    la a3 m2

    # call squared_loss function
    jal ra squared_loss
    # we expect squared_loss to exit early with code 36

    # exit normally
    li a0 0
    jal exit
