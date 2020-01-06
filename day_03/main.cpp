//--- Day 3: Crossed Wires ---
#include <iostream>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

#ifdef DEBUG
#define DEBUG_PRINT(msg) \
    cout << msg << endl
#else
#define DEBUG_PRINT(msg)
#endif



//Structure to represent points in co-ordinate
struct co_ordinate {
    int x;
    int y;
    co_ordinate(int x_in, int y_in)
    {
        x = x_in;
        y = y_in;
    }

    co_ordinate():x(0),y(0){}

    void operator=(co_ordinate in) {
        x = in.x;
        y = in.y;
    }

    friend ostream& operator<<(ostream &out, co_ordinate co);
};

ostream& operator<<(ostream &out, co_ordinate co) {
    out << "(" << co.x << ", " << co.y << ")";
    return out;
}

class line {
    public:
        line(string trace):tarce_command(trace)
    {
        stringstream in_stream(tarce_command);
        string intermediate;
        struct co_ordinate start_pos(0, 0);
        struct co_ordinate end_pos(0, 0);

        // Tokenizing w.r.t. space ' '
        //Convert path from string to vector of co-ordinates
        while(getline(in_stream, intermediate, ',')) {
            to_coordinate(intermediate.c_str(), start_pos, end_pos);
            start_pos = end_pos; //For next line, current end is start
            trace_path.push_back(end_pos);
        }
    }


        /**
         * @brief Convert string to co-ordinate
         *
         * @param str - Movement in string
         * @param cur_pos - Current position
         * @param point - Co-ordinate for current movement
         *
         * @return
         */
        int to_coordinate(const char *str, struct co_ordinate &cur_pos,
                struct co_ordinate &point);

        void print_path(void)
        {
            vector<co_ordinate>::iterator it = trace_path.begin();
            for (;it != trace_path.end(); it++) {
                DEBUG_PRINT("(" << it->x << "," << it->y << ")");
            }
        }

        vector<co_ordinate> get_trace_path(void) { return trace_path; }


        /**
         * @brief Function to find out intersections
         *
         * Traces both lines and identifies intersections
         *
         * @param line_1 - Line 1 trace
         * @param line_2 - Line 2 trace
         *
         * @return Co-ordinates of intersection points
         */
        friend vector<co_ordinate> get_intersections(line &line_1, line &line_2);

    private:
        string tarce_command; //Path trace in string
        vector<co_ordinate> trace_path; //Path trace in vector of co-ordinates
};

//Detect intersection
vector<co_ordinate> get_intersections(line &line_1, line &line_2)
{
    vector<co_ordinate>::iterator it_1 = line_1.trace_path.begin();
    vector<co_ordinate> intersections;

    co_ordinate start_1(0, 0);
    //For each movement of line segment of line_1, identify segments of the
    //line_2 that may form intersection. The segment of line_2 may form
    //intersection only if the movement of current section is horizontal if
    //the line_1 segment is vertical or if line_1 segment is horizontal when
    //line_2 is vertical.
    for (;it_1 != line_1.trace_path.end(); ++it_1) {
        co_ordinate start_2(0, 0);
        co_ordinate cur_1 = *it_1;
        vector<co_ordinate>::iterator it_2 = line_2.trace_path.begin();
        for (;it_2 != line_2.trace_path.end(); ++it_2) {
            co_ordinate cur_2 = *it_2;
            DEBUG_PRINT("1:" << cur_1 << endl);
            DEBUG_PRINT("2:" << cur_2 << endl);

            if (cur_1.x == start_1.x) {
                //Since x is constant, segment has horizontal movement. In this case
                //consider only those segment of the other line which has moved
                //vertically
                if (cur_2.y == start_2.y) {
                    int low_val;
                    int high_val;
                    if (start_1.y > cur_1.y) {
                        low_val = cur_1.y;
                        high_val = start_1.y;
                    }
                    else {
                        low_val = start_1.y;
                        high_val = cur_1.y;
                    }

                    if ((cur_2.y >= low_val) && (cur_2.y <= high_val)) {
                        if (start_2.x >= cur_1.x) {
                            if ((start_2.x >= cur_1.x) && (cur_2.x <= cur_1.x)) {
                                co_ordinate cross(cur_1.x, cur_2.y);
                                intersections.push_back(cross);
                                DEBUG_PRINT("[1]inter " << cross << endl);
                                DEBUG_PRINT("low " << low_val << " high " << high_val << endl);
                            }
                        }
                        else {
                            if ((start_2.x <= cur_1.x) && (cur_2.x >= cur_1.x)) {
                                co_ordinate cross(cur_1.x, cur_2.y);
                                intersections.push_back(cross);
                                DEBUG_PRINT("[1]inter " << cross << endl);
                                DEBUG_PRINT("low " << low_val << " high " << high_val << endl);
                            }
                        }
                    }
                }
            } else {
                //Since y is constant, segment has vertical movement. In this case
                //consider only those segment of the other line which has moved
                //horizontally
                if (cur_2.x == start_2.x) {
                    int low_val;
                    int high_val;
                    if (start_1.x > cur_1.x) {
                        low_val = cur_1.x;
                        high_val = start_1.x;
                    }
                    else {
                        low_val = start_1.x;
                        high_val = cur_1.x;
                    }

                    if ((cur_2.x >= low_val) && (cur_2.x <= high_val)) {
                        if (start_2.y >= cur_1.y) {
                            if ((start_2.y >= cur_1.y) && (cur_2.y <= cur_1.y)) {
                                co_ordinate cross(cur_2.x, cur_1.y);
                                intersections.push_back(cross);
                                DEBUG_PRINT("[2]inter " << cross << endl);
                            }
                        }
                        else {
                            if ((start_2.y <= cur_1.y) && (cur_2.y >= cur_1.y)) {
                                co_ordinate cross(cur_2.x, cur_1.y);
                                intersections.push_back(cross);
                                DEBUG_PRINT("[2]inter " << cross << endl);
                            }
                        }
                    }
                }
            }
            start_2 = cur_2;
        }
        start_1 = cur_1;
    }

    return intersections;
}

int line::to_coordinate(const char *str, struct co_ordinate &cur_pos,
        struct co_ordinate &point)
{
    int adv = 0;
    char dir = 'U';

    if (str == NULL) {
        DEBUG_PRINT("str input is NULL" << endl);
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

    point = cur_pos;

    switch (dir) {
        case 'R':
            point.y += adv;
            break;
        case 'L':
            point.y -= adv;
            break;
        case 'D':
            point.x -= adv;
            break;
        case 'U':
            point.x += adv;
            break;
    }

    return 0;
}

//string line_1_path = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
//string line_2_path = "U62,R66,U55,R34,D71,R55,D58,R83";
//string line_1_path = "R8,U5,L5,D3";
//string line_2_path = "U7,R6,D4,L4";
string line_1_path = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
string line_2_path = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

int main()
{
   line line_1(line_1_path);
   line line_2(line_2_path);
   line_1.print_path();
   DEBUG_PRINT(endl);
   line_2.print_path();
   DEBUG_PRINT(endl);
   DEBUG_PRINT(endl);
   vector<co_ordinate> intersections = get_intersections(line_1, line_2);
   vector<co_ordinate>::iterator it = intersections.begin() + 1; //Delete intersection at (0, 0)

   co_ordinate low_co;
   int low_mh_len = INT_MAX;
   cout << "Intersection\t\t" << "Manhattan Dist" << endl;
   for (; it != intersections.end(); it++) {
       cout << (*it) << "\t\t" << (it->x + it->y) << endl;
       if (low_mh_len > it->x + it->y) {
           low_mh_len = it->x + it->y;
           low_co = *it;
       }
   }

   cout << "Nearest co-ordinate " << low_co << endl;

   return 0;
}
