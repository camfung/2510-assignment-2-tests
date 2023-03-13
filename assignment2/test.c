#include <stdio.h>

int main() {
    float num = 2.443663;
    float rounded_num = ((int)(num * 100 + 0.5)) / 100.0;
    printf("Original number: %.6f\n", num);
    printf("Rounded number: %f\n", rounded_num);
    return 0;

}