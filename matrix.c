#include <stdio.h>

int main() {
    int matrix[10][10];
    int rows, cols, i, j;
    int zeroRows[10] = {0};
    int zeroCols[10] = {0};

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {
                zeroRows[i] = 1;
                zeroCols[j] = 1;
            }
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (zeroRows[i] == 1 || zeroCols[j] == 1) {
                matrix[i][j] = 0;
            }
        }
    }

    printf("Result matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}