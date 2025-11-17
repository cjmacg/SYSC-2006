/********* a1_functions.c ********
	
	Student Name 	= Cameron MacGillivray
	Student Number	= 101354857
*/
#include "a2_functions.h"
#include "a2_data_structures.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define HOURLY_RATE 40.0f

static unsigned short int ceil_days_from_hours_int(int total_hours) {
    int numerator = 2 * total_hours + 14;
    return (unsigned short int)(numerator / 15);
}

/*
   Initialize all fields in an activity as per the instructions (3)
*/
void init_activity(activity_t * activity_to_int, unsigned short int id,  unsigned short int planned_duration) {
    activity_to_int->id = id;
    activity_to_int->planned_duration = planned_duration;
    activity_to_int->planned_cost = planned_duration * HOURLY_RATE;
    activity_to_int->actual_cost = 0.0f;
    activity_to_int->actual_duration = 0;
    activity_to_int->completed = 0;
}


/*
   Initialize all fields in the milestone as per the instructions (3)
   The implementation of your function MUST call the function init_activity.
   You may assume that the id input parameter is valid (i.e., it is unique)
   planned_duration contains the plan duration for each activity
*/
void init_milestone(milestone_t * milestone_to_int, unsigned short int id, unsigned short int num_activities, unsigned short int * planned_duration) {
    unsigned short int i;
    milestone_to_int->id = id;
    milestone_to_int->completed = 0;
    milestone_to_int->actual_cost = 0.0f;
    milestone_to_int->actual_duration = 0;
    for (i = 0; i < num_activities && i < NUM_ACTIVITIES; i++) {
        init_activity(&milestone_to_int->activity_list[i], (unsigned short int)(i + 1), planned_duration[i]);
    }
    for (; i < NUM_ACTIVITIES; i++) {
        init_activity(&milestone_to_int->activity_list[i], (unsigned short int)(i + 1), 0);
    }
}


/*
   Initialize all fields in the project as per the instructions (4)
   number_activities contains the number of activities per milestone
*/
project_t init_project(char * project_name, milestone_t * milestone_list, int number_milestones, const int * number_activities) {
    int i, j;
    int total_planned_hours = 0;
    float total_planned_cost = 0.0f;
    project_t p;
    p.project_name = project_name;
    p.actual_cost = 0.0f;
    p.actual_duration = 0;
    p.completed = 0;
    for (i = 0; i < number_milestones; i++) {
        int n = number_activities[i];
        if (n > NUM_ACTIVITIES) n = NUM_ACTIVITIES;
        for (j = 0; j < n; j++) {
            total_planned_cost += milestone_list[i].activity_list[j].planned_cost;
            total_planned_hours += milestone_list[i].activity_list[j].planned_duration;
        }
    }
    p.planned_cost = total_planned_cost;
    p.planned_duration = ceil_days_from_hours_int(total_planned_hours);
    return p;
}


/*
   Print the main menu as per the instructions (5)
*/
void print_main_menu(void) {
    printf("Please select an option:\n");
    printf("1. Update activity\n");
    printf("2. Print stats\n");
    printf("3. Exit\n");
}


/*
   Print out milestone stats as per the instructions (6)
   number_activities contains the number of activities per milestone
*/
static void compute_planned_for_milestone(const milestone_t *m, int n_activities, int *planned_hours_out, float *planned_cost_out, int *completed_count_out) {
    int j;
    int planned_hours = 0;
    float planned_cost = 0.0f;
    int completed_count = 0;
    if (n_activities > NUM_ACTIVITIES) n_activities = NUM_ACTIVITIES;
    for (j = 0; j < n_activities; j++) {
        planned_cost += m->activity_list[j].planned_cost;
        planned_hours += m->activity_list[j].planned_duration;
        if (m->activity_list[j].completed) completed_count++;
    }
    *planned_hours_out = planned_hours;
    *planned_cost_out = planned_cost;
    *completed_count_out = completed_count;
}

void print_milestone_stats(const milestone_t *list, int num, const int *num_activities) {
    int i;
    for (i = 0; i < num; i++) {
        const milestone_t *m = &list[i];
        int planned_hours = 0;
        float planned_cost = 0.0f;
        int completed_count = 0;
        int n = num_activities[i];
        compute_planned_for_milestone(m, n, &planned_hours, &planned_cost, &completed_count);
        printf("Milestone %hu\n", m->id);
        if (!m->completed) {
            printf("%d out of %d activities completed.\n", completed_count, (n < NUM_ACTIVITIES ? n : NUM_ACTIVITIES));
            printf("Planned duration (hours): %d\n", planned_hours);
            printf("Planned cost: $%.2f\n", planned_cost);
        } else {
            unsigned short int planned_days = ceil_days_from_hours_int(planned_hours);
            unsigned short int actual_days = ceil_days_from_hours_int((int)m->actual_duration);
            float cost_diff = m->actual_cost - planned_cost;
            int day_diff = (int)actual_days - (int)planned_days;
            if (cost_diff < 0.0f) {
                printf("Under budget by $%.2f\n", -cost_diff);
            } else if (cost_diff > 0.0f) {
                printf("Over budget by $%.2f\n", cost_diff);
            } else {
                printf("On budget\n");
            }
            if (day_diff < 0) {
                printf("Early by %d days\n", -day_diff);
            } else if (day_diff > 0) {
                printf("Late by %d days\n", day_diff);
            } else {
                printf("On time\n");
            }
        }
    }
}


/*
   Print out project stats as per the instructions (6)
   number_activities contains the number of activities per milestone
   The implementation MUST call print_stats_milestone
*/
void print_project_stats(project_t proj, const milestone_t *list, int num, const int *num_activities) {
    int i, j;
    int total_planned_hours = 0;
    float total_planned_cost = 0.0f;
    printf("Project: %s\n", proj.project_name);
    if (!proj.completed) {
        printf("Project not completed.\n");
        print_milestone_stats(list, num, num_activities);
        return;
    }
    for (i = 0; i < num; i++) {
        int n = num_activities[i];
        if (n > NUM_ACTIVITIES) n = NUM_ACTIVITIES;
        for (j = 0; j < n; j++) {
            total_planned_cost += list[i].activity_list[j].planned_cost;
            total_planned_hours += list[i].activity_list[j].planned_duration;
        }
    }
    {
        unsigned short int planned_days = ceil_days_from_hours_int(total_planned_hours);
        float cost_diff = proj.actual_cost - total_planned_cost;
        int day_diff = (int)proj.actual_duration - (int)planned_days;
        if (cost_diff < 0.0f) {
            printf("Under budget by $%.2f\n", -cost_diff);
        } else if (cost_diff > 0.0f) {
            printf("Over budget by $%.2f\n", cost_diff);
        } else {
            printf("On budget\n");
        }
        if (day_diff < 0) {
            printf("Early by %d days\n", -day_diff);
        } else if (day_diff > 0) {
            printf("Late by %d days\n", day_diff);
        } else {
            printf("On time\n");
        }
    }
}


/*
   Update milestone per the instructions (6)
*/
void update_milestone(milestone_t *ms, int n_activities) {
    int j;
    int all_completed = 1;
    float total_cost = 0.0f;
    int total_hours = 0;
    if (n_activities > NUM_ACTIVITIES) n_activities = NUM_ACTIVITIES;
    for (j = 0; j < n_activities; j++) {
        if (!ms->activity_list[j].completed) {
            all_completed = 0;
        }
        total_cost += ms->activity_list[j].actual_cost;
        total_hours += ms->activity_list[j].actual_duration;
    }
    if (all_completed && n_activities > 0) {
        ms->completed = 1;
        ms->actual_cost = total_cost;
        ms->actual_duration = (short int)total_hours;
    }
}


/*
   Update project per the instructions (6)
   number_activities contains the number of activities per milestone
*/
void update_project(const milestone_t *milestone_array, int num_milestones, const int *number_activities, project_t *my_project) {
    int i;
    int all_completed = 1;
    float total_cost = 0.0f;
    int total_hours = 0;
    (void)number_activities; //unused so far.
    for (i = 0; i < num_milestones; i++) {
        const milestone_t *m = &milestone_array[i];
        if (!m->completed) {
            all_completed = 0;
        }
        total_cost += m->actual_cost;
        total_hours += (int)m->actual_duration;
    }
    if (all_completed && num_milestones > 0) {
        my_project->completed = 1;
        my_project->actual_cost = total_cost;
        my_project->actual_duration = ceil_days_from_hours_int(total_hours);
    }
}

/*
Initialize all milestones and activities with the data available in the file
as per the instructions in (2)
*/
milestone_t * initialize_milestone_list_from_file(char * file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        return NULL;
    }

    int num_milestones;
    if (fscanf(fp, "%d", &num_milestones) != 1 || num_milestones <= 0) {
        fclose(fp);
        return NULL;
    }

    milestone_t *milestones = malloc((size_t)num_milestones * sizeof(milestone_t));
    if (milestones == NULL) {
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < num_milestones; i++) {
        unsigned short int planned_duration[NUM_ACTIVITIES];
        int tmp;

        for (int j = 0; j < NUM_ACTIVITIES; j++) {
            if (fscanf(fp, "%d", &tmp) != 1) {
                tmp = 0;
            }
            if (tmp < 0) {
                tmp = 0;
            }
            planned_duration[j] = (unsigned short int) tmp;
        }

        init_milestone(&milestones[i], (unsigned short int)(i + 1),
                       NUM_ACTIVITIES, planned_duration);
    }

    fclose(fp);
    return milestones;
}


/*
   Update activity per the instructions (6)
*/

void update_activity(activity_t * activity_to_update) {
    int duration_input;
    int completed_input;

    printf("Updating activity %hu\n", activity_to_update->id);

    printf("Enter actual duration (hours): ");
    if (scanf("%d", &duration_input) != 1) {
        duration_input = 0;
    }
    if (duration_input < 0) {
        duration_input = 0;
    }
    activity_to_update->actual_duration = (unsigned short int) duration_input;
    activity_to_update->actual_cost = activity_to_update->actual_duration * HOURLY_RATE;

    printf("Is the activity completed? (1 for yes, 0 for no): ");
    if (scanf("%d", &completed_input) != 1) {
        completed_input = 0;
    }
    activity_to_update->completed = completed_input ? 1 : 0;
}