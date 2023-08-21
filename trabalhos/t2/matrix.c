#include "matrix.h"

Matrix create_matrix(int width, int height)
{
    return (Matrix) {
        .width = width,
        .height = height,
        .vector = (char *)calloc(width * height, sizeof(char))
    };
}

void release_matrix(Matrix *matrix)
{
    free(matrix->vector);
}

bool is_in_bounds(Matrix *matrix, Vector2 *position)
{
    return position->x >= 0 && position->x < matrix->width && position->y >= 0 && position->y < matrix->height;
}

void fill_matrix(Matrix *matrix)
{
    int index = 0;
    int size = matrix->width * matrix->height;

    int character;

    do
    {
        character = getchar();
    } while (isspace(character));

    do
    {
        if (isalpha(character) && index < size)
        {
            matrix->vector[index++] = (char)character;
        }

        character = getchar();
    } while (character != '\n');
}

void show_matrix(Matrix *matrix)
{
    printf("    ");

    for (int x = 0; x < matrix->width; x++)
    {
        printf(" %4d", x + 1);
    }

    printf("\n");

    for (int y = 0; y < matrix->height; y++)
    {
        printf("%4d", y + 1);

        for (int x = 0; x < matrix->width; x++)
        {
            printf(" %4c", matrix->vector[y * matrix->width + x]);
        }

        printf("\n");
    }
}
