#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EPSILON 0.00001 // small value for floating-point error

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
    printf("%s %s %s %f %d %d\n", node->firstName, node->lastName, node->charDate, node->gpa, node->isDomestic, node->toefl);
}

void printNodeInt(Node* node) {
    printf("%s %s %d-%d-%d %f %d %d\n", node->firstName, node->lastName, node->date[0], node->date[1], node->date[2], node->gpa, node->isDomestic, node->toefl);
}

int getMonthNumber(char* monthString);
int isLeapYear(int year);
int isValidYear(int year);
int isValidMonth(int month);
int isValidDay(int day, int month, int year);
int checkDate(int date[3]);
void setDate(char* stringDate, int* date);
int checkGPA(float* gpa);
float getGPA(char* stringGPA);

void throwError(char* error) {
    printf("COMP2510ERROR: %s, exiting.\n", error);
    exit(1);
}
char* readFile(FILE* file, int count) {
    rewind(file);
    char c;
    char* entireFile = (char*) malloc(count * sizeof(char) + 1);

    int index = 0;
    while ((c = fgetc(file)) != EOF) {
        entireFile[index] = c;
        index++;
    }
    entireFile[index] = '\0';
    return entireFile;
}
int countLines(FILE* file) {
    rewind(file);
    char c;
    int count = 0;
    while ((c = getc(file)) != EOF) {
        if (c == '\n') { count++; }
    }

    return ++count;
}
int countFile(FILE* file) {
    char c;
    int count = 0;
    while ((c = getc(file)) != EOF) {
        count++;
        if (c>127){
            printf("Error: “COMP2510ERROR: non ascii character found.\n");
            return 0;
        }
    }
    return count;
}
void splitLines(char** lines, char* input, int* numLines) {
    char* str = (char*) malloc(sizeof(char) * strlen(input) + 1);

    strcpy(str, input);

    char* token = strtok(str, "\n");

    for (int i = 0; i < *numLines; i++) {
        lines[i] = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(lines[i], token);
        token = strtok(NULL, "\n");
    }

}
void makeArray(char** lines, int numlines, Node** arr) {
    for (int i = 0; i < numlines; i++) {
        arr[i] = (Node*) malloc(sizeof(Node));

        arr[i]->line = (char*) malloc(sizeof(char) * strlen(lines[i]));
        char* str = (char*) malloc(sizeof(char) * strlen(lines[i]) + 1);
        strcpy(str, lines[i]);

        char* token = strtok(str, " ");
        arr[i]->firstName = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(arr[i]->firstName, token);

        token = strtok(NULL, " ");
        arr[i]->lastName = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(arr[i]->lastName, token);

        token = strtok(NULL, " ");
        arr[i]->charDate = (char*) malloc(sizeof(char) * strlen(token));
        strcpy(arr[i]->charDate, token);

        token = strtok(NULL, " ");
        arr[i]->gpa = getGPA(token);

        token = strtok(NULL, " ");
        if (strcmp(token, "I") == 0) {
            arr[i]->isDomestic = 0;
        } else if (strcmp(token,"D") == 0) {
            arr[i]->isDomestic = 1;
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

        printNodeInt(arr[i]);
    }
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


int alphabetical_order(char* str1, char* str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] < str2[i]) {
            return 1;
        } else if (str1[i] > str2[i]) {
            return -1;
        }
        i++;
    }

    if (str1[i] == '\0' && str2[i] != '\0') {
        return 1;
    } else if (str1[i] != '\0' && str2[i] == '\0') {
        return -1;
    } else {
        return 0;
    }
}

void freeArray(Node** arr, int numLines) {
    for (int i = 0; i < numLines; i++) {
        free(arr[i]->line);
        free(arr[i]);
    }
    free(arr);
}

void freeLines(char** lines, int numLines) {
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);
}

int main(int argc, char** argv) {
    FILE* infile = fopen("input.txt", "r");

    if (infile == NULL) {
        exit(69);
    }

    int fileLen = countFile(infile);

    int numLines = countLines(infile);

    char* charFile = readFile(infile, fileLen);

    char** lines = (char**) malloc(sizeof(char*) * numLines);
    splitLines(lines, charFile, &numLines);

    Node** arr = (Node**) malloc(sizeof(Node*) * numLines);

    makeArray(lines, numLines, arr);

    freeArray(arr, numLines);
    // freeLines(lines, numLines);

    return 0;
}


