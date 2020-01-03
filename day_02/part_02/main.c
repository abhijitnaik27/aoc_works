/* Advent of code 02/01/2020
 * Day 2: 1202 Program Alarm 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TARGET_OUTPUT 19690720

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
    unsigned int *out_res;
    unsigned int noun, verb;

    out_res = calloc(size, sizeof(unsigned int));
    if (out_res == NULL) {
        printf("Insufficient memory !!\n");
        return -1;
    }

    for (noun = 0; noun < 100; noun++) {
        for (verb = 0; verb < 100; verb++) {
            op_idx = 0;
            memcpy(out_res, cmd_input, size * sizeof(unsigned int));
            out_res[1] = noun;
            out_res[2] = verb;
            while (out_res[op_idx] != 99) {
                cur_op = &out_res[op_idx];
                lhs = cur_op[OPERAND_1_OFFSET];
                rhs = cur_op[OPERAND_2_OFFSET];
                switch (cur_op[OPERATION_OFFSET]) {
                    case OPCODE_ADD:
                        output = out_res[lhs] + out_res[rhs];
                        break;
                    case OPCODE_MUL:
                        output = out_res[lhs] * out_res[rhs];
                        break;
                    default:
                        printf("Undefined operation!!\n");
                        goto err_exit;
                        break;
                }

                res_idx = cur_op[OUTPUT_OFFSET];
                out_res[res_idx] = output;
                op_idx += NEXT_OPERATION_OFFSET;
            }
            if (out_res[0] == TARGET_OUTPUT) {
                break;
            }
        }

        if (out_res[0] == TARGET_OUTPUT) {
            break;
        }
    }

    printf("Noun = %u, Verb = %u\n", noun, verb);
    printf("answer %u\n", ((noun * 100) + verb));


    printf("\n");

    return 0;

err_exit:
    return -1;
}
