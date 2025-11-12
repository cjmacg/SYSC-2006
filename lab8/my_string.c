#include "my_string.h"
#include <stdio.h>   // printf


// Exercise 11

/* Calculate how many times the target character appears in the string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use array-indexing. 
*/

int count_char(const char * my_str, char target){

   int count = 0;
   for (int i = 0; my_str[i] != '\0'; i++) {
      if (my_str[i] == target) {
         count++;
      }
   }
   return count;
}

// Exercise 12

/* Calculate how many times the target character appears in the string my_str
For example:
count_char("Hello world ",'l') return 3
count_char("Hello world ",'a') return 0
Your implementation must use a walking pointer.
*/


int count_char_wp(const char * my_str, char target){
   int count = 0;
   for (const char *p = my_str; *p != '\0'; p++) {
      if (*p == target) {
         count++;
      }
   }
   return count;
}