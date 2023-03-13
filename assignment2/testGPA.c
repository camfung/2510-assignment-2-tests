#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void throwError(char* error) {
    printf("COMP2510ERROR: %s, exiting.\n", error);
}
void setGPA(char* stringGPA, float* gpa) {
    *gpa = atof(stringGPA);
    printf("%f\n", *gpa);
}
#define EPSILON 0.00001 // small value for floating-point error

int checkGPA(float* gpa) {
    if (*gpa >= 0-EPSILON && *gpa <= 4.3+EPSILON) {
        return 1; 
    } else {
        throwError("Invalid GPA");
        return 0;
    }
}



int main() {
        // Test Case 1
    char stringGPA1[] = "3.50";
    float gpa1[2];
    setGPA(stringGPA1, gpa1);
    int result1 = checkGPA(gpa1);
    if (result1 == 1) {
        printf("Test Case 1: Passed\n");
    } else {
        printf("Test Case 1: Failed\n");
    }

    // Test Case 2
    char stringGPA2[] = "4.00000000";
    float gpa2[2];
    setGPA(stringGPA2, gpa2);
    int result2 = checkGPA(gpa2);
    if (result2 == 1) {
        printf("Test Case 2: Passed\n");
    } else {
        printf("Test Case 2: Failed\n");
    }

    // Test Case 3
    char stringGPA3[] = "2.99";
    float gpa3[2];
    setGPA(stringGPA3, gpa3);
    int result3 = checkGPA(gpa3);
    if (result3 == 1) {
        printf("Test Case 3: Passed\n");
    } else {
        printf("Test Case 3: Failed\n");
    }

    // Test Case 4
    char stringGPA4[] = "4.4";
    float gpa4[2];
    setGPA(stringGPA4, gpa4);
    int result4 = checkGPA(gpa4);
    if (result4 == 0) {
        printf("Test Case 4: Passed\n");
    } else {
        printf("Test Case 4: Failed\n");
    }

    // Test Case 5
    char stringGPA5[] = "-2.50";
    float gpa5[2];
    setGPA(stringGPA5, gpa5);
    int result5 = checkGPA(gpa5);
    if (result5 == 0) {
        printf("Test Case 5: Passed\n");
    } else {
        printf("Test Case 5: Failed\n");
        // print the result 
        printf("result: %d\n", result5);
    }

    // Test Case 6
    char stringGPA6[] = "3.123";
    float gpa6[2];
    setGPA(stringGPA6, gpa6);
    int result6 = checkGPA(gpa6);
    if (result6 == 1) {
        printf("Test Case 6: Passed\n");
    } else {
        printf("Test Case 6: Failed\n");
    }

    // Test Case 7
    char stringGPA7[] = "1.101";
    float gpa7[2];
    setGPA(stringGPA7, gpa7);
    int result7 = checkGPA(gpa7);
    if (result7 == 1) {
        printf("Test Case 7: Passed\n");
    } else {
        printf("Test Case 7: Failed\n");
    }
    return 1;
}