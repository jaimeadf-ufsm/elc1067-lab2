#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct vector2_t Vector2;
typedef struct matrix_t Matrix;

struct vector2_t
{
    int x, y;
};

struct matrix_t
{
    int width, height;
    char *vector;
};

Matrix create_matrix(int width, int height);
void release_matrix(Matrix *matrix);

bool is_in_bounds(Matrix *matrix, Vector2 *position);

void fill_matrix(Matrix *matrix);
void show_matrix(Matrix *matrix);

#endif