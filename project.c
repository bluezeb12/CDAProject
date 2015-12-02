#include "spimcore.h"
#include <stdio.h>


/* ALU */
/* 10 Points */
void ALU(unsigned A,unsigned B,char ALUControl,unsigned *ALUresult,char *Zero)
{
    switch(ALUControl){
        //Z = A+B
        case 000:
            *ALUresult = A + B;
            break;
        //Z = A-B
        case 001:
            *ALUresult = A - B;
            break;
        //If A<B, Z = 1, otherwise Z = 0
        case 010:
            if((signed) A < (signed) B)
                *ALUresult = 1;
            else
                *ALUresult = 0;
            break;
        //If A<B, Z = 1, otherwise Z = 0 UNSIGNED
        case 011:
            if(A < B)
                *ALUresult = 1;
            else
                *ALUresult = 0;
            break;
        //Z = A AND B
        case 100:
            *ALUresult = A & B;
            break;
        //Z = A OR B
        case 101:
            *ALUresult = A | B;
            break;
        //Shift left B by 16 bits
        case 110:
            B << 16;   
            break;
         //Z = NOT A
         case 111:
            *ALUresult = ~A;
            break;
    }
    
    //Now check to see if the result is zero, and set the zero bit
    if(*ALUresult == 0)
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
	*op = (instruction >> 26) & 0b00000000000000000000000000111111; // instruction[31-26]
	*r1 = (instruction >> 21) & 0b11111; // instruction[25-21]
	*r2 = (instruction >> 16) & 0b11111; // instruction[20-16]
	*r3 = (instruction >> 11) & 0b11111; // instruction[15-11]
	*funct = (instruction) & 0b00000000000000000000000000111111; // instruction[5-0]
	*offset = (instruction) & 0b00000000000000001111111111111111; // instruction[15-0]
	*jsec = (instruction) & 0b00000011111111111111111111111111; // instruction[25-0]
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
        //addi
        case 8:
            control->RegDst = 0;
            control->RegWrite = 1;
            control->ALUSrc = 1;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 0;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 0;
            break;
        
        //slti
        case 10:
            control->RegDst = 0;
            control->RegWrite = 1;
            control->ALUSrc = 1;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 0;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 2;
            break;
            
        //sltiu
        case 11:
            control->RegDst = 0;
            control->RegWrite = 1;
            control->ALUSrc = 1;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 0;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 3;
            break;
            
        //beq
        case 4:
            control->RegDst = 2;
            control->RegWrite = 0;
            control->ALUSrc = 0;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 2;
            control->Jump = 0;
            control->Branch = 1;
            control->ALUOp = 1;
            break;
            
        //lw
        case 35:
            control->RegDst = 0;
            control->RegWrite = 1;
            control->ALUSrc = 1;
            control->MemRead = 1;
            control->MemWrite = 0;
            control->MemToReg = 1;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 0;
            break;
            
        //lui
        case 15:
            control->RegDst = 0;
            control->RegWrite = 0;
            control->ALUSrc = 1;
            control->MemRead = 0;
            control->MemWrite = 1;
            control->MemToReg = 0;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 6;
            break;
            
        //sw
        case 43:
            control->RegDst = 2; // 2 for dont care
            control->RegWrite = 0;
            control->ALUSrc = 1;
            control->MemRead = 1;
            control->MemWrite = 0;
            control->MemToReg = 2;
            control->Jump = 0;
            control->Branch = 0;
            control->ALUOp = 0;
            break;
        //End I Type Instructions
        
        //J Type Instructions
        //Jump
        case 2:
            control->RegDst = 0;
            control->RegWrite = 0;
            control->ALUSrc = 0;
            control->MemRead = 0;
            control->MemWrite = 0;
            control->MemToReg = 0;
            control->Jump = 1;
            control->Branch = 0;
            control->ALUOp = 0;
            break; 
        //End J Type Instructions
        
        default:
            return 1;
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
    //check to see if ALUresult is word aligned. and if it isn't return a halt code.
    if((ALUresult % 4) != 0)
        return 1;
        
    //if we are writing,
    //Write data to ALUresult * 4 index in Memory
    if(MemWrite == 1)
        Mem[ALUresult >> 2] = memdata;
    
    //if we are reading,
    //Read data from ALUresult * 4 index in Memory.
    if(MemRead == 1)
        *memdata = Mem[ALUresult >> 2];
        
    return 0;
}


/* Write Register */
/* 10 Points */
void write_register(unsigned r2,unsigned r3,unsigned memdata,unsigned ALUresult,char RegWrite,char RegDst,char MemtoReg,unsigned *Reg)
{
    if(RegWrite==1){
        //Memory to register
        if(MemtoReg == 1 && RegDst == 0)
            Reg[r2] = memdata;
        //memory to register but to r3
        else if(MemtoReg == 1 && RegDst == 1)
            Reg[r3] = memdata;
        
        //store ALUResult in r2
        else if(MemtoReg == 0 && RegDst == 0)
            Reg[r2] = ALUresult;
        //store ALUResult in r3
        else if(MemtoReg == 0 && RegDst == 1)
            Reg[r3] = ALUresult;
    }
}

/* PC update */
/* 10 Points */
void PC_update(unsigned jsec,unsigned extended_value,char Branch,char Jump,char Zero,unsigned *PC)
{
    //always increment by 4 no matter what.
    *PC += 4;
    
    //if branching, and we got a zero, add the extended_value, bitshifted (multiplied by 4)
    if(Zero == 1 && Branch == 1)
        *PC += extended_value << 2;
        
    //if jumping, jump to the Jump register, and multiply by 4 (word align)
    if(Jump == 1)
        *PC = (jsec << 2) | (*PC & 0xf0000000);
}
