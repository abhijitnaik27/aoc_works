/* Advent of code 02/01/2020
 * Day 2: 1202 Program Alarm 
 */
#include <stdio.h>
#define OPCODE_ADD          	    1
#define OPCODE_MUL          	    2

#define OPERATION_OFFSET    	    0
#define OPERAND_1_OFFSET    	    1
#define OPERAND_2_OFFSET    	    2
#define OUTPUT_OFFSET       	    3
#define NEXT_OPERATION_OFFSET       4

unsigned int cmd_input[] = {1,12,2,3,1,1,2,3,1,3,4,3,1,5,0,3,2,13,1,19,1,19,10,23,2,10,23,27,1,27,6,31,1,13,31,35,1,13,35,39,1,39,10,43,2,43,13,47,1,47,9,51,2,51,13,55,1,5,55,59,2,59,9,63,1,13,63,67,2,13,67,71,1,71,5,75,2,75,13,79,1,79,6,83,1,83,5,87,2,87,6,91,1,5,91,95,1,95,13,99,2,99,6,103,1,5,103,107,1,107,9,111,2,6,111,115,1,5,115,119,1,119,2,123,1,6,123,0,99,2,14,0,0};

//unsigned char cmd_input[] = {1,1,1,4,99,5,6,0,99};
//unsigned int cmd_input[] = {2,4,4,5,99,0};
int main()
{
	unsigned int op_idx = 0;
	unsigned int res_idx = 0;
    unsigned int output;
    unsigned int *cur_op = NULL;
    unsigned int size = sizeof(cmd_input)/sizeof(unsigned int);
    unsigned int i;
    unsigned char lhs, rhs;



    while (cmd_input[op_idx] != 99) {
        cur_op = &cmd_input[op_idx];
        lhs = cur_op[OPERAND_1_OFFSET];
        rhs = cur_op[OPERAND_2_OFFSET];
        switch (cur_op[OPERATION_OFFSET]) {
            case OPCODE_ADD:
                output = cmd_input[lhs] + cmd_input[rhs];
                break;
            case OPCODE_MUL:
                output = cmd_input[lhs] * cmd_input[rhs];
                break;
            default:
                printf("Undefined operation!!\n");
                goto err_exit;
                break;
        }

        res_idx = cur_op[OUTPUT_OFFSET];
        if (res_idx == 123) {
            printf("%u %c %u = %u\n", cur_op[OPERAND_1_OFFSET], cur_op[OPERATION_OFFSET] == 1 ? '+' : '*', cur_op[OPERAND_2_OFFSET], output);
        }
        cmd_input[res_idx] = output;
        op_idx += NEXT_OPERATION_OFFSET;
    }

    printf("op_idx %u, size %u\n", op_idx, size);

    for (i = 0; i < size; i++) {
        printf("%u,", cmd_input[i]);
    }

    printf("\n");

    return 0;

err_exit:
    return -1;
}
