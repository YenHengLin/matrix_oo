#ifndef MATRIX_EXPANSION_H_
#define MATRIX_EXPANSION_H_

#include <stdbool.h>

/* predefined shortcut */
#define DECLARE_MATRIX(col, row) \
    typedef struct { float values[col][row]; } Mat ## col ## x ## row
DECLARE_MATRIX(3, 3);
DECLARE_MATRIX(4, 4);

typedef struct _Matrix {
    int row, col;
    float **data;
} Matrix;

typedef struct {
    void (*assign)(Matrix *thiz, const Matrix *that);
    bool (*equal)(const Matrix *l, const Matrix *r);
    bool (*mul)(Matrix *dst, const Matrix *l, const Matrix *r);
    Matrix * (*create)(int rows, int cols,float value[][cols]);
} MatrixAlgo;

/* Available matrix providers */
extern MatrixAlgo NaiveMatrixProvider;

#endif /* MATRIX_EXPANSION_H_ */
