# I-type
    addi t0, x0, 7
    slti t1, x0, 4
    sltiu t2, x0, 3
    xori s0, t0, 10
    ori s1, t0, 2
    andi a0, t0, 5
    slli t0, t0, 2
    srli t0, t0, 1
    srai t0, t0, 1

# R-type
    add t0, t1, t2
    sub t0, t1, t2
    sll t0, t1, t2
    slt t0, t1, t2
    sltu t0, t1, t2
    xor t0, t1, t2
    srl t0, t1, t2
    sra t0, t1, t2
    or t0, t1, t2
    and t0, t1, t2
    mul t0, t1, t2
    mulh t0, t1, t2
    mulhu t0, t1, t2

# Load and Store
    addi t0, x0, 625
    li t1, 0xf00
    li t2, 0
    sb t0, 1(t1)
    sh t0, 2(t1)
    sw t0, 0(t1)
    lb t2, 1(t1)
    lh t2, 2(t1)
    lw t2, 0(t1)

#jal, jalr, auipc, lui
    lui t0, 0x12345
    auipc t1, 0x12345
    jal ra, yeah
    
    li t0, 0
    jal x0, finish

yeah:
    jalr x0, ra, 0

finish:
       
