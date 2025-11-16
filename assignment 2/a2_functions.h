/********* a1_functions.h ********
	
	Student Name 	= 
	Student Number	= 
*/

#include "a2_data_structures.h"


/* 
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int, unsigned short int id,  unsigned short int planned_duration);

/* 
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
   You may assume that the id input parameter is valid (i.e., it is unique)
   planned_duration contains the plan duration for each activity
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int id, unsigned short int num_activities, unsigned short int * planned_duration);


/* 
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char * project_name, milestone_t *milestone_list, int number_milestones, const int * number_activities);


/* 
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void);

/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void print_milestone_stats(const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t details, const milestone_t * list_milestones, int num_milestones, const int * number_activities);

/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t * milestone_to_update, int activities_in_milestone);

/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t * milestone_array, int num_milestones, const int * number_activities, project_t * my_project);

/*
Initialize all milestones and activities with the data available in the file
as per the instructions in (2)
*/
milestone_t * initialize_milestone_list_from_file (char * file_name); 

/*
   Update activity per the instructions (6)
*/
void update_activity(activity_t * activity_to_update);


// Extra function prototypes/declarations go here



