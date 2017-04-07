#include "matrix_expansion.h"
#include <stdio.h>
MatrixAlgo *matrix_providers[] = {
    &NaiveMatrixProvider,
};

int main()
{

    MatrixAlgo *algo = matrix_providers[0];
    float value[2][3] = {
        { 1, 2, 3},
        { 4, 5, 6},
    };
    Matrix *A;
    A=algo->create(2,3,value);
    printf("%f",A->data[0][1]);
}

