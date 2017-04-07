#include "matrix_expansion.h"
#include <stdlib.h>

struct naive_priv {
    float values[4][4];
};

#define PRIV(x) \
    ((struct naive_priv *) ((x)->priv))

static void assign(Matrix *thiz, const Matrix *that)
{
    /*map the same matrix size from that to thiz*/
    thiz->row = that->row;
    thiz->col = that->col;

    thiz->data = malloc(sizeof(float) * thiz->row);
    for(int i = 0; i < thiz->row; i++)
        thiz->data[i] = malloc(sizeof(float) * thiz->col);
    /*map the same data from that to thiz*/
    for (int i = 0; i < thiz->row; i++)
        for (int j = 0; j < thiz->col; j++)
            thiz->data[i][j] = that->data[i][j];
}

static const float epsilon = 1 / 10000.0;

static bool equal(const Matrix *l, const Matrix *r)
{
    /*if nxm matrix and axb matrix ,n!=a or m!=b you can say they
      are not equal*/
    if((l->row!=r->row)||(l->col!=r->col))
        return false;
    for (int i = 0; i < l->row; i++)
        for (int j = 0; j < l->col; j++)
            if (l->data[i][j] + epsilon < r->data[i][j] ||
                    r->data[i][j] + epsilon < l->data[i][j])
                return false;
    return true;
}

bool mul(Matrix *dst, const Matrix *l, const Matrix *r)
{
    /*A(nxm) matrix multiple with B(ixj) matrix,m must be equal
      to i ,if m is not equal to i ,they can't mutiple.Otherwise,
      the new matrix(nxj)*/
    if(l->col != r->row)
        return false;
    dst->data = malloc(l->row * sizeof(float));
    for(int i =0; i< l->row; i++)
        dst->data[i]=malloc(r->col * sizeof(float));
    for (int i = 0; i < l->row; i++)
        for (int j = 0; j < r->col; j++)
            for (int k = 0; k < l->col; k++)
                dst->data[i][j] += l->data[i][k] *
                                   r->data[k][j];
    return true;
}

Matrix * create(int rows, int cols,float value[][cols])
{
    Matrix *m = malloc(sizeof(Matrix));
    m->row = rows;
    m->col = cols;
    m->data = malloc(sizeof(float) * rows);
    for(int i = 0; i < rows; i++)
        m->data[i] = malloc(sizeof(float) * cols);

    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            m->data[i][j]=value[i][j];
    return m;
}



MatrixAlgo NaiveMatrixProvider = {
    .assign = assign,
    .equal = equal,
    .mul = mul,
    .create = create,
};
