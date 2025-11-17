/********* a1_data_structures.h ********
	
	Student Name 	= Cameron MacGillivray
	Student Number	= 101354857
*/

#ifndef A2_DATA_STRUCTURES_H
#define A2_DATA_STRUCTURES_H

#include <stdbool.h>

#define NUM_ACTIVITIES 3


typedef struct activity {
    unsigned short int id;
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}activity_t;

typedef struct milestone {
    unsigned short int id;
    activity_t activity_list[NUM_ACTIVITIES];
    _Bool completed;
    float actual_cost;
    short int actual_duration;
}milestone_t;

typedef struct project {
    char * project_name;
    float planned_cost, actual_cost;
    unsigned short int planned_duration, actual_duration;
    _Bool completed;
}project_t;

#endif /* A2_DATA_STRUCTURES_H */
