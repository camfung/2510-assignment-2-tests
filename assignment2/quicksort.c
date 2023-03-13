#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>
#include <math.h>
#include <time.h>

#define EPSILON 0.00001 // small value for floating-point error

void throwError(char* error) {
    printf("COMP2510ERROR: %s, exiting.\n", error);
    // exit(1);
}

typedef struct Node {
    int date[3];
    char* charDate; 
    char* firstName; 
    char* lastName;
    float gpa;
    int toefl;
    int isDomestic;
    char* line; 

} Node;
void printNode(Node* node) {
    printf("%s %s %s %f %d %d\n\n", node->firstName, node->lastName, node->charDate, node->gpa, node->isDomestic, node->toefl);
}
void printNodeInt(Node* node) {
    printf("%s %s %d-%d-%d %f %d %d\n\n", node->firstName, node->lastName, node->date[0], node->date[1], node->date[2], node->gpa, node->isDomestic, node->toefl);
}
void printNodeLine(Node* node) {
    printf("%s\n", node->line);
}
// print the array returned from makearray
void printArray(Node** array, int size) {
    for (int i = 0; i < size; i++) {
        printNodeLine(array[i]);
    }
}
 
int checkGPA(float* gpa) {
    if (*gpa >= 0-EPSILON && *gpa <= 4.3+EPSILON) {
        return 1; 
    } else {
        throwError("Invalid GPA");
        return 0;
    }
}
float getGPA(char* stringGPA) {
    float temp = atof(stringGPA);
    checkGPA(&temp);
    return temp; 
}

int getMonthNumber(char* monthString) {

    // Declare the array of strings
    char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    // Loop through the array to find the index of the month string
    for (int i = 0; i < 12; i++) {
        if (strcmp(months[i], monthString) == 0) {
            return i + 1; // Add 1 to the index to get the month number (1-12)
        }
    }
    throwError("Invalid month");
}
int isLeapYear(int year) {
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}
int isValidYear(int year) {
    if (year >= 1950 && year <= 2010) {
        return 1;
    } else {
        throwError("Invalid year");
    }
}
int isValidMonth(int month) {
    if (month >= 1 && month <= 12) {
        return 1;
    } else {
        throwError("Invalid month");
    }
}
int isValidDay(int day, int month, int year) {
    if (month == 2) {
        if (isLeapYear(year)) {
            if (day >= 1 && day <= 29) {
                return 1;
            } else {
                throwError("Invalid day");
            }
        } else {
            if (day >= 1 && day <= 28) {
                return 1;
            } else {
                throwError("Invalid day");
            }
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day >= 1 && day <= 30) {
            return 1;
        } else {
            throwError("Invalid day");
        }
    } else {
        if (day >= 1 && day <= 31) {
            return 1;
        } else {
            throwError("Invalid day");
        }
    }
}
int checkDate(int date[3]) {
    if (isValidYear(date[2]) && isValidMonth(date[0]) && isValidDay(date[1], date[0], date[2])) {
        return 1;
    }
}
void setDate(char* stringDate, int* date) {
    char* str = (char*) malloc(strlen(stringDate) * sizeof(char) + 1);

    strcpy(str, stringDate);
 
    // Returns first token
    char* token = strtok(str, "-");
 
    // Keep printing tokens while one of the
    // delimiters present in str[].
    int i = 0 ; 

    while (token != NULL) {
        if (i == 0) {
            date[i++] = getMonthNumber(token);
            // print date 
            // printf("%d\n", date[0]);
        } else if (i == 1) {
            date[i++] = atoi(token);
            // printd date
            // printf("%d\n", date[1]);
        } else if (i == 2) {
            date[i++] = atoi(token);
            // print date 
            // printf("%d\n", date[2]);

        }
        token = strtok(NULL, " - ");
    }
    // print date
    // printf("%d-%d-%d\n", date[0], date[1], date[2]);
    checkDate(date);
}
 

void makeArray(char** lines, int numlines, Node** arr) {
    for (int i = 0; i < numlines; i++) {
        arr[i] = (Node*) malloc(sizeof(Node));

        arr[i]->line = (char*) malloc(sizeof(char) * strlen(lines[i]));
        char* str = (char*) malloc(sizeof(char) * strlen(lines[i]) + 1);
        strcpy(arr[i]->line, lines[i]);
        strcpy(str, lines[i]);

        char* token = strtok(str, " ");
        arr[i]->firstName = (char*) malloc(sizeof(char) * strlen(token));
        // strcpy(arr[i]->firstName, token);
        for (int j = 0; token[j]; j++) {
            arr[i]->firstName[j] = tolower(token[j]);}
        arr[i]->firstName[strlen(token)] = '\0';

        token = strtok(NULL, " ");
        arr[i]->lastName = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(arr[i]->lastName, token);
        for (int j = 0; token[j]; j++) {
            arr[i]->lastName[j] = tolower(token[j]);}
        arr[i]->lastName[strlen(token)] = '\0';

        token = strtok(NULL, " ");
        arr[i]->charDate = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(arr[i]->charDate, token);
        // setDate(token, arr[i]->date);

        token = strtok(NULL, " ");
        arr[i]->gpa = getGPA(token); 

        token = strtok(NULL, " ");
        if (strcmp(token, "I") == 0) {
            arr[i]->isDomestic = 0;
        } else if (strcmp(token,"D") == 0) {
            arr[i]->isDomestic = 1;
            token = strtok(NULL, " ");
            if (token != NULL) {
                throwError("Invalid domestic/international status");
            }
        } else {
            throwError("Invalid domestic/international status");
        }

        if (!(arr[i]->isDomestic)) {
            token = strtok(NULL, " ");
            arr[i]->toefl = atoi(token);
        } else {
            arr[i]->toefl = 0;
        }

        setDate(arr[i]->charDate, arr[i]->date);

        // printNode(arr[i]);
    }
}

int compare(const void* a, const void* b) {
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;

    if (nodeA->gpa < nodeB->gpa) {
        return -1;
    } else if (nodeA->gpa > nodeB->gpa) {
        return 1;
    } else {
        return 0;
    }
}

int compareTo(Node* a, Node* b) {
    // Compare year of birth
    if (a->date[2] < b->date[2]) {
        return -1;
    } else if (a->date[2] > b->date[2]) {
        return 1;
    }

    // Compare month of birth
    if (a->date[1] < b->date[1]) {
        return -1;
    } else if (a->date[1] > b->date[1]) {
        return 1;
    }

    // Compare day of birth
    if (a->date[0] < b->date[0]) {
        return -1;
    } else if (a->date[0] > b->date[0]) {
        return 1;
    }

    // Compare last name alphabetically
    int lastNameCmp = strcmp(a->lastName, b->lastName);
    if (lastNameCmp != 0) {
        return lastNameCmp;
    }

    // Compare first name alphabetically
    int firstNameCmp = strcmp(a->firstName, b->firstName);
    if (firstNameCmp != 0) {
        return firstNameCmp;
    }

    // Compare GPA
    if (a->gpa < b->gpa) {
        return -1;
    } else if (a->gpa > b->gpa) {
        return 1;
    }

    // Compare TOEFL score (domestic takes precedence if TOEFL score not available)
    if (a->toefl == -1 && b->toefl == -1) {
        // Both domestic
        if (a->isDomestic && !b->isDomestic) {
            return -1;
        } else if (!a->isDomestic && b->isDomestic) {
            return 1;
        } else {
            return 0;
        }
    } else if (a->toefl == -1) {
        // A is domestic, B is international
        return -1;
    } else if (b->toefl == -1) {
        // A is international, B is domestic
        return 1;
    } else {
        // Compare TOEFL scores
        if (a->toefl < b->toefl) {
            return -1;
        } else if (a->toefl > b->toefl) {
            return 1;
        } else {
            // Same TOEFL scores, compare domestic/international status
            if (a->isDomestic && !b->isDomestic) {
                return -1;
            } else if (!a->isDomestic && b->isDomestic) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}


void quicksort(Node** nodes, int left, int right) {
    int i = left, j = right;
    Node* pivot = nodes[(left + right) / 2];

    while (i <= j) {
        while (compareTo(nodes[i], pivot) < 0) {
            i++;
        }
        while (compareTo(nodes[j], pivot) > 0) {
            j--;
        }
        if (i <= j) {
            Node* temp = nodes[i];
            nodes[i] = nodes[j];
            nodes[j] = temp;
            i++;
            j--;
        }
    }

    if (left < j) {
        quicksort(nodes, left, j);
    }
    if (i < right) {
        quicksort(nodes, i, right);
    }
}



void freeArray(Node** arr, int numlines) {
    for (int i = 0; i < numlines; i++) {
        free(arr[i]->line);
        free(arr[i]->firstName);
        free(arr[i]->lastName);
        free(arr[i]->charDate);
        free(arr[i]);
    }
}


int main() {
        clock_t start_time, end_time;
    double time_elapsed;

    start_time = clock(); // save start time

// char* lines[] = {
//     "John Smith Jan-1-2000 4.33 D",
//     "Anna Lee Apr-30-1999 -1.0 I 80",
//     "Chris Evans Feb-15-2001 5.0 D",
//     "Sarah Park Jan-1-1990 4.0 I 120",
//     "Tom Hanks Dec-31-2002 0.000001 D",
//     "Lucy Liu Nov-30-1998 4.3333 I 100",
//     "Michael Jordan Mar-15-1985 -2.0 D",
//     "Emma Watson Apr-30-1995 0.9 I 90",
//     "Daniel Radcliffe Feb-29-2000 4.34 D",
//     "Jennifer Lawrence Dec-32-1992 0.000000000001 I 115"
// };

// char* lines[] = {
//     "John Smith Jan-30-2000 3.7 D",
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
//     "John Smith Jan-30-2000 3.7 D"
// };


char* lines[] = {
    "John Smith Jan-30-1955 3.7 D",
    "Anna Lee Apr-30-1965 3.2 I 80",
    "Chris Evans Feb-25-1975 3.5 D",
    "Sarah Park Jan-1-1985 4.0 I 120",
    "Tom Hanks Dec-31-1995 2.8 D",
    "Lucy Liu Nov-30-2005 3.9 I 100",
    "Mike Johnson May-15-2000 3.4 D",
    "Amy Lee Aug-10-1990 3.8 I 90"
};



    int numlines = 8;
    Node** arr = (Node**) malloc(sizeof(Node*) * numlines); 
    
    makeArray(lines, numlines, arr);

    printArray(arr, numlines);

    quicksort(arr, 0, numlines - 1);

    printf("\n");

    printArray(arr, numlines);

    freeArray(arr, numlines);

    end_time = clock(); // save end time

    time_elapsed = ((double) (end_time - start_time)) / CLOCKS_PER_SEC; // calculate elapsed time
    printf("Time taken: %f seconds\n", time_elapsed);

    return 0;

}