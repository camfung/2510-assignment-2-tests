#include <stdio.h>

// include functions to be tested
int isValidYear(int year);
int isValidMonth(int month);
int isValidDay(int day, int month, int year);
int isLeapYear(int year);

int checkDate(int date[3]) {
    if (isValidYear(date[2]) && isValidMonth(date[0]) && isValidDay(date[1], date[0], date[2])) {
        return 1;  // valid date
    } else {
        return 0;  // invalid date
    }
}

int isValidYear(int year) {
    return (year >= 1950 && year <= 2010);
}

int isValidMonth(int month) {
    return (month >= 1 && month <= 12);
}

int isValidDay(int day, int month, int year) {
    if (month == 2) {
        if (isLeapYear(year)) {
            return (day >= 1 && day <= 29);
        } else {
            return (day >= 1 && day <= 28);
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return (day >= 1 && day <= 30);
    } else {
        return (day >= 1 && day <= 31);
    }
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

int main() {
// Test Case 1
// invalid year
int date1[3] = { 12, 3, 2023 };
int result1 = checkDate(date1);
if (result1 == 1) {
    printf("Test Case 1: Failed\n");
} else {
    printf("Test Case 1: Passed\n");
}

// Test Case 2
// invalid date (feb 30)
int date2[3] = { 2, 30, 2022 };
int result2 = checkDate(date2);
if (result2 == 1) {
    printf("Test Case 2: Failed\n");
} else {
    printf("Test Case 2: Passed\n");
}

// Test Case 3
// invalid date (feb 30)
int date3[3] = { 2, 30, 2024 };
int result3 = checkDate(date3);
if (result3 == 1) {
    printf("Test Case 3: Failed\n");
} else {
    printf("Test Case 3: Passed\n");
}

// Test Case 4
// 
int date4[3] = { 4, 31, 2023 };
int result4 = checkDate(date4);
if (result4 == 1) {
    printf("Test Case 4: Failed\n");
} else {
    printf("Test Case 4: Passed\n");
}

// Test Case 5
int date5[3] = { 13, 1, 2023 };
int result5 = checkDate(date5);
if (result5 == 1) {
    printf("Test Case 5: Failed\n");
} else {
    printf("Test Case 5: Passed\n");
}

// Test Case 6
int date6[3] = { 2, 1, -2023 };
int result6 = checkDate(date6);
if (result6 == 1) {
    printf("Test Case 6: Failed\n");
} else {
    printf("Test Case 6: Passed\n");
}

// Test Case 7
int date7[3] = { 2, 29, 2024 };
int result7 = checkDate(date7);
if (result7 == 1) {
    printf("Test Case 7: Passed\n");
} else {
    printf("Test Case 7: Failed\n");
}

// Test Case 8
int date8[3] = { 2, 29, 2022 };
int result8 = checkDate(date8);
if (result8 == 1) {
    printf("Test Case 8: Failed\n");
} else {
    printf("Test Case 8: Passed\n");
}


    return 0;
}
