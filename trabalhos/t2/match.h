#ifndef MATCH_H
#define MATCH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "matrix.h"

typedef enum order_e Order;
typedef enum orientatation_e Orientation;
typedef struct match_t Match;
typedef struct matches_t Matches;

enum order_e
{
    ORDER_DIRECT,
    ORDER_REVERSE,
    ORDER_N
};

enum orientatation_e
{
    ORIENTATION_HORIZONTAL,
    ORIENTATION_VERTICAL,
    ORIENTATION_MAIN_DIAGONAL,
    ORIENTATION_SECONDARY_DIAGONAL,
    ORIENTATION_N
};

struct match_t
{
    Order order;
    Orientation orientation;

    Vector2 start, end;
};

struct matches_t
{
    int size;
    int capacity;

    Match *results;
};

Matches create_matches(int capacity);
void release_matches(Matches *matches);

Matches search_word(Matrix *matrix, char *word);

void show_order(Order order);
void show_orientation(Orientation orientation);
void show_matches(Matches *matches, char *word);

#endif