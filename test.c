// test.c - enter a hex value and print as decimal
// 
// Fred J. Frigo
// 12-Sep-2024
// 
// To compile:  gcc test.c -o test 
//

#include <stdio.h>

int main() {

    int value;
    printf("Input your 8 bit byte in hex : ");
    scanf( "%x", &value);
    printf("Decimal Value = %d\n", value);
    printf("Hex value = %x\n", value);
    return 0;
}
