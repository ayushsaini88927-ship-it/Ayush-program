#include <stdio.h>

#define MAX 10

void inputMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("Enter element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX],
                 int result[MAX][MAX], int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX],
                      int result[MAX][MAX],
                      int r1, int c1, int r2, int c2)
{
    int i, j, k;

    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            result[i][j] = 0;

            for (k = 0; k < c1; k++)
            {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[MAX][MAX],
                     int transpose[MAX][MAX],
                     int rows, int cols)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }
}

int main()
{
    int choice;
    int a[MAX][MAX], b[MAX][MAX], result[MAX][MAX];
    int rows, cols, r1, c1, r2, c2;

    printf("===== MATRIX OPERATIONS =====\n");
    printf("1. Matrix Addition\n");
    printf("2. Matrix Multiplication\n");
    printf("3. Matrix Transpose\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("\nEnter rows and columns of matrices: ");
            scanf("%d %d", &rows, &cols);

            printf("\nEnter Matrix A:\n");
            inputMatrix(a, rows, cols);

            printf("\nEnter Matrix B:\n");
            inputMatrix(b, rows, cols);

            addMatrices(a, b, result, rows, cols);

            printf("\nMatrix A:\n");
            displayMatrix(a, rows, cols);

            printf("\nMatrix B:\n");
            displayMatrix(b, rows, cols);

            printf("\nAddition Result:\n");
            displayMatrix(result, rows, cols);
            break;

        case 2:
            printf("\nEnter rows and columns of Matrix A: ");
            scanf("%d %d", &r1, &c1);

            printf("Enter rows and columns of Matrix B: ");
            scanf("%d %d", &r2, &c2);

            if (c1 != r2)
            {
                printf("\nMatrix multiplication is not possible.\n");
                printf("Columns of Matrix A must equal rows of Matrix B.\n");
                return 0;
            }

            printf("\nEnter Matrix A:\n");
            inputMatrix(a, r1, c1);

            printf("\nEnter Matrix B:\n");
            inputMatrix(b, r2, c2);

            multiplyMatrices(a, b, result, r1, c1, r2, c2);

            printf("\nMultiplication Result:\n");
            displayMatrix(result, r1, c2);
            break;

        case 3:
            printf("\nEnter rows and columns of the matrix: ");
            scanf("%d %d", &rows, &cols);

            printf("\nEnter Matrix:\n");
            inputMatrix(a, rows, cols);

            transposeMatrix(a, result, rows, cols);

            printf("\nOriginal Matrix:\n");
            displayMatrix(a, rows, cols);

            printf("\nTranspose Matrix:\n");
            displayMatrix(result, cols, rows);
            break;

        default:
            printf("\nInvalid choice.\n");
    }

    return 0;
}
