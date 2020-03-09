#include <stdio.h>
#include <stdlib.h>

char *line_1_path[9] = {"R75","D30","R83","U83","L12","D49","R71","U7","L72"};
char *line_2_path[8] = {"U62","R66","U55","R34","D71","R55","D58","R83"};

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

    point->x = cur_pos->x;
    point->y = cur_pos->y;

    switch (dir) {
        case 'R':
            point->x += adv;
            break;
        case 'L':
            point->x -= adv;
            break;
        case 'D':
            point->y -= adv;
            break;
        case 'U':
            point->y += adv;
            break;
    }

    return 0;
}

int translate_to_co_ordinate(char *line_trace[], unsigned int size,
        struct path **co_path)
{
    unsigned int i;
    struct co_ordinate cur_pos;
    struct co_ordinate point;
    struct path *line_1 = NULL;
    struct path *temp;
    struct path *head;

    int ret = 0;

    if (*co_path == NULL) {
        printf("%s:%d Invalid input\n", __func__, __LINE__);
        return -1;
    }

    cur_pos.x = 0;
    cur_pos.y = 0;

    for (i = 0; i < size; i++) {
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

        cur_pos.x = point.x;
        cur_pos.y = point.y;

        if (line_1 == NULL) {
            line_1 = temp;
            head = temp;
        } else {

            line_1->next = temp;
            line_1 = line_1->next;
        }



        line_1->point.x = cur_pos.x;
        line_1->point.y = cur_pos.y;
    }

    *co_path = head;
    
    return 0;
}

int main()
{
    struct path *co_path_line1;
    struct path *co_path_line2;
    struct path *temp;
    struct path *trace_1;
    struct path *trace_2;
    int ret;
    unsigned int j;
    unsigned int i;

    ret = translate_to_co_ordinate(line_1_path, 9,
            &co_path_line1);

    if (ret) {
        return -1;
    }

    temp = co_path_line1;

    printf("\n\n");
    while (temp != NULL) {
        printf("(%d,%d)", temp->point.x, temp->point.y);
        temp = temp->next;
        if (temp && (temp->next))
            printf("->");
    }

    printf("\n\n");

    ret = translate_to_co_ordinate(line_2_path, 8,
            &co_path_line2);
    if (ret) {
        return -1;
    }
    temp = co_path_line2;

    printf("\n\n");
    while (temp != NULL) {
        printf("%d %d\n", temp->point.x, temp->point.y);
        temp = temp->next;
    }

    return 0;
}
