#include "spimcore.h"
#include <stdio.h>


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch(ALUControl){
        //Z = A+B
        case 000:
            break;
        //Z = A-B
        case 001:
            break;
        //If A<B, Z = 1, otherwise Z = 0
        case 010:
            break;
        //If A<B, Z = 1, otherwise Z = 0 UNSIGNED
        case 011:
            break;
        //Z = A AND B
        case 100:
            break;
        //Z = A OR B
        case 101:
            break;
        //Shift left B by 16 bits
        case 110:
             break;
         //Z = NOT A
         case 111:
            break;
    }
    
    //Now check to see if the result is zero, and set the zero bit
    if(*ALUResult == 0)
        *Zero = 1;
    else
        *Zero = 0;
}

/* instruction fetch */
/* 10 Points */
int instruction_fetch(unsigned PC,unsigned *Mem,unsigned *instruction)
{
	//Multiply by 4 to get the proper address in memory
	unsigned index = PC >> 2;

	if(index % 4 != 0)
	    return 1;
	*instruction = Mem[index];
}


/* instruction partition */
/* 10 Points */
void instruction_partition(unsigned instruction, unsigned *op, unsigned *r1,unsigned *r2, unsigned *r3, unsigned *funct, unsigned *offset, unsigned *jsec)
{
    
}



/* instruction decode */
/* 15 Points */
int instruction_decode(unsigned op,struct_controls *controls)
{
    switch(op){
        //R Type Instructions
        case 0:
            control->RegDst = 1;
            control->RegWrite = 1;
            control->ALUSrc = 0;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 0;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 7;
            break;
        //End R Type Instructions
        
        //I Type Instructions
        
        //End I Type Instructions
        
        //J Type Instructions
        
        //End J Type Instructions
    }
}

/* Read Register */
/* 5 Points */
void read_register(unsigned r1,unsigned r2,unsigned *Reg,unsigned *data1,unsigned *data2)
{
    *data1 = Reg[r1];
    *data2 = Reg[r2];
}


/* Sign Extend */
/* 10 Points */
void sign_extend(unsigned offset,unsigned *extended_value)
{
    unsigned negative = offset >> 15;
    //if the number is negative (MSB = 1), extend with 1s
    if(negative == 1)
        *extended_value = offset | 0xFFFF0000;
    //otherwise extend with 0's
    else
        *extended_value = offset | 0x0000FFFF;
}

/* ALU operations */
/* 10 Points */
int ALU_operations(unsigned data1,unsigned data2,unsigned extended_value,unsigned funct,char ALUOp,char ALUSrc,unsigned *ALUresult,char *Zero)
{
    
}

/* Read / Write Memory */
/* 10 Points */
int rw_memory(unsigned ALUresult,unsigned data2,char MemWrite,char MemRead,unsigned *memdata,unsigned *Mem)
{
    
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{

}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{

}
