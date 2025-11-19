#include<stdio.h>
#include<stdlib.h>

// // Write your functions here...
// int tb = 8*8;

// int* encodeString(char string[]) {
//     int* bit = malloc(sizeof(int));
//     int k = 0;
//     for(int i = 0; i < 9; i++) {
//         bit[k++] = string[i];
//     }
//     return bit;
// }
// short int* arrayToBitmask(int arr[]) {
//     short int* bt = malloc(tb*sizeof(short int));
//     for(int i = 0; i <4; i++) {
//         int value = 0;
//         for(int bit = 15; bit >= 0; bit-- )  {
//         value |= (bit>>bit) & 1;
//     }
//     bt = (short int)value;
    
// }return bt;

// // short int* value = malloc(sizeof(short int));
// // for(int i = 0; i < 64; i++) {
// //     for(int bit = 16; bit >= 0; bit--) {
// //         value |= (value<<arr[i]) & 1;
// //     }
// // }
// // return value;
// }
// void displayBitPattern(int arr[]) {
//     for(int i = 0; i<64; i++) {
//         printf("%d", arr[i]);
//         if (((i+1) % 16) == 0) {
//             printf(" ");
//         }
//     }
// }




/*
 * Convert 8 characters → 64-bit vector
 * Each char → 8 bits (MSB first)
 */
int* encodeString(char string[]) {
    int *bits = malloc(64 * sizeof(int));
    int k = 0;

    for (int i = 0; i < 8; i++) {
        unsigned char ch = string[i];

        // extract bits from MSB → LSB
        for (int b = 7; b >= 0; b--) {
            bits[k++] = (ch >> b) & 1;
        }
    }
    return bits;
}

/*
 * Convert 64 bits → 4 short ints
 * Each 16 bits = 1 short integer
 */
short int* arrayToBitmask(int arr[]) {
    short int *out = malloc(4 * sizeof(short int));

    for (int i = 0; i < 4; i++) {
        short int value = 0;

        for (int b = 0; b < 16; b++) {
            value <<= 1;
            value |= arr[i * 16 + b];
        }
        out[i] = value;
    }
    return out;
}

/*
 * Display 64 bits grouped into 8 groups of 8 bits
 */
void displayBitPattern(int arr[]) {
    for (int i = 0; i < 64; i++) {
        printf("%d", arr[i]);

        if ((i + 1) % 8 == 0) {
            printf(" ");
        }
    }
}
