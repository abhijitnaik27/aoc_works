/* Advent of code 01/01/2020
 * Day 1: The Tyranny of the Rocket Equation
 */
#include <stdio.h>
#define LENGTH 10

/* Function to convert string to integer */
unsigned int string_to_int(char *line)
{
    unsigned int mass = 0;

    while (*line != '\n') {
        mass *= 10;
        mass += *line - '0';
        line++;
    }

    return mass;
}

/* Function to get the mass of the fuel recursively
 *
 */
unsigned long int cal_fuel(unsigned int mass)
{
    unsigned int fuel_mass = 0;
    unsigned int cumulative_mass = 0;

    if ((mass / 3) <= 2) {
        return 0;
    }

    fuel_mass = (mass / 3) - 2;
    cumulative_mass = fuel_mass + cal_fuel(fuel_mass);

    return cumulative_mass;
}

int main()
{
    FILE *fp = NULL;
    char line[LENGTH];
    unsigned int mass;
    unsigned long int sys_mass = 0;

    fp = fopen("input.txt", "rb");
    if (fp == NULL) {
        perror("Unable to open input.txt\n");
        return -1;
    }

    while (fgets(line, LENGTH, fp)) {
        mass = string_to_int(line);
        sys_mass += cal_fuel(mass);
    }

    printf("%lu\n", sys_mass);
    fclose(fp);

    return 0;
}
