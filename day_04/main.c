/*
 * Day 04 - Possible passcode combinations
 * */

#include <stdio.h>
#include <memory.h>
#include <stdint.h>

#define start_val   367479
#define end_val     893698

#define NUM_DIGITS  6

/*
 * Decimate value val into character array
 * */
void decimate(uint32_t val, uint8_t *arr)
{
    int i = 0;
    while (val) {
        arr[i++] = val % 10;
        val /= 10;
    }
}

bool is_valid_pass_comb(uint8_t *arr)
{
    int i;
    bool valid = false;
    uint32_t adj = 0;

    for (i = NUM_DIGITS - 1; i > 0; i--) {
        if (arr[i] > arr[i - 1]) {
            valid = false;
            break;
        }

        if (arr[i] == arr[i - 1]) {
            adj++;
        } else {
            if (adj == 1) {
                valid = true;
            }
            adj = 0;
        }
    }

    //For part 2, the combination must have at least one pair of identical
    //adjacent numbers
    if ((i == 0) && (adj == 1)) {
        valid = true;
    }

    return valid;
}

int main()
{
    uint32_t i;
    uint8_t arr[NUM_DIGITS];
    uint32_t count = 0;

    for (i = start_val; i <= end_val; i++) {
        memset(arr, 0, sizeof(arr));
        decimate(i, arr);
        if (is_valid_pass_comb(arr)) {
            count++;
        }
    }

    printf("Number of possible password combinations %u\n", count);

    return 0;
}
