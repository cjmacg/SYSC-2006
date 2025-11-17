/********* main.c ********
	
	Student Name 	= Cameron MacGillivray
	Student Number	= 101354857
*/

//Completed the includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_data_structures.h"
#include "a2_functions.h"


int main() {
    char file_name[256];
    FILE *fp = NULL;
    int num_milestones = 0;

    //welcome msg
    printf("Welcome to the project tracker.\n");

    // get file name, open, and re-prompt on invalid file / format
    while (1) {
        printf("Enter the project file name: ");
        if (scanf("%255s", file_name) != 1) {
            printf("Error reading file name.\n");
            return EXIT_FAILURE;
        }

        fp = fopen(file_name, "r");
        if (fp == NULL) {
            printf("Could not open file '%s'. Please try again.\n", file_name);
            continue;
        }

        if (fscanf(fp, "%d", &num_milestones) != 1 || num_milestones <= 0) {
            printf("Invalid file format for '%s'. Please try again.\n", file_name);
            fclose(fp);
            fp = NULL;
            continue;
        }

        fclose(fp);
        fp = NULL;
        break;  // valid file and num_milestones obtained
    }

    //init all milestones and activities
    milestone_t *milestone_list = initialize_milestone_list_from_file(file_name);
    if (milestone_list == NULL) {
        printf("Failed to initialize milestones from file '%s'.\n", file_name);
        return EXIT_FAILURE;
    }

    int *number_activities = malloc((size_t)num_milestones * sizeof(int));
    if (number_activities == NULL) {
        printf("Memory allocation failed.\n");
        free(milestone_list);
        return EXIT_FAILURE;
    }
    for (int i = 0; i < num_milestones; i++) {
        number_activities[i] = NUM_ACTIVITIES;
    }

    // init project w/file name (without extension) as project name
    char project_name[256];
    strncpy(project_name, file_name, sizeof(project_name) - 1);
    project_name[sizeof(project_name) - 1] = '\0';
    char *dot = strrchr(project_name, '.');
    if (dot != NULL) {
        *dot = '\0';
    }

    project_t my_project = init_project(project_name, milestone_list, num_milestones, number_activities);

   //print main menu and loop
    int choice = 0;
    do {
        print_main_menu();
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            /* Clear invalid input */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* discard */
            }
            printf("Invalid input. Please try again.\n");
            continue;
        }

        // Get user choice and handle it as per the instructions
        if (choice == 1) {
            int ms_id, act_id;

            // get milestone id, handle invalid input
            printf("Enter milestone id (1-%d): ", num_milestones);
            if (scanf("%d", &ms_id) != 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    /* discard */
                }
                printf("Invalid milestone id input.\n");
                continue;
            }
            if (ms_id < 1 || ms_id > num_milestones) {
                printf("Invalid milestone id.\n");
                continue;
            }

            // get activity id, handle invalid input
            printf("Enter activity id (1-%d): ", NUM_ACTIVITIES);
            if (scanf("%d", &act_id) != 1) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    /* discard */
                }
                printf("Invalid activity id input.\n");
                continue;
            }
            if (act_id < 1 || act_id > NUM_ACTIVITIES) {
                printf("Invalid activity id.\n");
                continue;
            }

            /* Update selected activity */
            update_activity(&milestone_list[ms_id - 1].activity_list[act_id - 1]);

            // Update corresponding milestone and project */
            update_milestone(&milestone_list[ms_id - 1], number_activities[ms_id - 1]);
            update_project(milestone_list, num_milestones, number_activities, &my_project);

        } else if (choice == 2) {
            print_project_stats(my_project, milestone_list, num_milestones, number_activities);
        } else if (choice == 3) {
            printf("Exiting program.\n");
        } else {
            printf("Invalid choice. Please select 1, 2, or 3.\n");
        }

    } while (choice != 3);

    free(number_activities);
    free(milestone_list);

    return EXIT_SUCCESS;
}
