#include <stdio.h>
#include <stdlib.h>

char *line_trace[9] = {"R75","D30","R83","U83","L12","D49","R71","U7","L72"};
char *line_2[8] = {"U62","R66","U55","R34","D71","R55","D58","R83"};

struct co_ordinate {
    int x;
    int y;
};

struct path;
struct path {
    struct co_ordinate point;
    struct path *next;
};

int get_co_ordinate(char *str, struct co_ordinate *cur_pos,
        struct co_ordinate *point)
{
    int adv = 0;
    char dir = 'U';

    if (str == NULL) {
        printf("str input is NULL\n");
        return -1;
    }

    if (point == NULL) {
        printf("point input is NULL\n");
        return -1;
    }

    while (*str != '\0') {
        switch (*str) {
            case 'R':
            case 'L':
            case 'D':
            case 'U':
                dir = *str;
                break;
            default:
                if (*str >= '0' && *str <= '9') {
                    adv = (adv * 10) + (*str - '0');
                } else {
                    return -1;
                }
                break;
        }
        str++;
    }

    switch (dir) {
        case 'R':
            point->x = cur_pos->x + adv;
            break;
        case 'L':
            point->x = cur_pos->x - adv;
            break;
        case 'D':
            point->y = cur_pos->y - adv;
            break;
        case 'U':
            point->y = cur_pos->y + adv;
            break;
    }

    return 0;
}

int main()
{
    unsigned int i;
    struct co_ordinate cur_pos;
    struct co_ordinate point;
    struct path *line_1 = NULL;
    struct path *temp;
    struct path *head;
    int ret = 0;

    cur_pos.x = 0;
    cur_pos.y = 0;

    for (i = 0; i < 9; i++) {
        ret = get_co_ordinate(line_trace[i], &cur_pos, &point);
        if (ret != 0) {
            printf("Invalid input\n");
            return -1;
        }

        temp = calloc(sizeof(*line_1), 1);
        if (temp == NULL) {
            printf("Insufficient memory\n");
            return -1;
        }

        temp->next = NULL;
        if (line_1 == NULL) {
            line_1 = temp;
            head = temp;
        } else {
            line_1->next = temp;
            line_1 = line_1->next;
        }

        cur_pos.x = point.x;
        cur_pos.y = point.y;

        line_1->point.x = cur_pos.x;
        line_1->point.y = cur_pos.y;
    }

    temp = head;
    /* Print co-ordinates */
    while (temp != NULL) {
        printf("%d %d\n", temp->point.x, temp->point.y);
        temp = temp->next;
    }

    return 0;
}
