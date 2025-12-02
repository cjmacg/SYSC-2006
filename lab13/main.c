/* SYSC 2006 - Lab 13 - demonstrate ADT dictionary/map.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

int main(void)
{
    printf("Creating a dictionary of names & email addresses\n");
    dict_t *addresses = make_dictionary();

    printf("Adding key: %s, value: %s\n", "Lynn", "lynn.marshall@carleton.ca");
    put(addresses, "Lynn", "lynn.marshall@carleton.ca");

    // Multiple keys can be associated with the duplicate values
    printf("Adding key: %s, value: %s\n", "Don", "donald.bailey@carleton.ca");
    put(addresses, "Don", "donald.bailey@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Donald", "donald.bailey@carleton.ca");
    put(addresses, "Donald", "donald.bailey@carleton.ca");

    printf("Adding key: %s, value: %s\n", "Babak", "babak.esfandiari@carleton.ca");
    put(addresses, "Babak", "babak.esfandiari@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Greg", "gregory.franks@carleton.ca");
    put(addresses, "Greg", "gregory.franks@carleton.ca");
    printf("Adding key: %s, value: %s\n", "Jason", "jason.jaskolka@carleton.ca");
    put(addresses, "Jason", "jason.jaskolka@carleton.ca");

    printf("Email for Babak is %s\n", get(addresses, "Babak"));
    printf("Email for Lynn is %s\n", get(addresses, "Lynn"));
    printf("Email for Jason is %s\n", get(addresses, "Jason"));
    printf("Email for Don is %s\n", get(addresses, "Don"));
    printf("Email for Donald is %s\n", get(addresses, "Donald"));
    printf("Email for Greg is %s\n", get(addresses, "Greg"));

    printf("Changing %s to %s\n", "Babak", "babak@sce.carleton.ca");
    put(addresses, "Babak", "babak@sce.carleton.ca");
    printf("Email for Babak is now %s\n", get(addresses, "Babak"));


    print_dictionary(addresses);
    // Exercise 2 Tests
    printf("Testing replace:\n");
    _Bool result = replace(addresses, "Babak", "new_email@example.com");
    printf("Result for existing key (Babak): %d (Expected: 1)\n", result);

    result = replace(addresses, "Ghost", "boo");
    printf("Result for missing key (Ghost): %d (Expected: 0)\n", result);

    printf("Dictionary after replace:\n");
    print_dictionary(addresses);

    // Exercise 3 Tests
    printf("\nTesting clear:\n");
    clear(addresses);
    printf("Dictionary after clear (Should be all NULL):\n");
    print_dictionary(addresses);
    return EXIT_SUCCESS;
}
