#include "match.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

Vector2 get_forward_direction(Orientation orientation)
{
    switch (orientation)
    {
    case ORIENTATION_HORIZONTAL:
        return (Vector2) {1, 0};
    case ORIENTATION_VERTICAL:
        return (Vector2) {0, 1};
    case ORIENTATION_MAIN_DIAGONAL:
        return (Vector2) {1, 1};
    case ORIENTATION_SECONDARY_DIAGONAL:
        return (Vector2) {1, -1};
    default:
        return (Vector2) {0, 0};
    }
}

Matches create_matches(int capacity)
{
    return (Matches) {
        .size = 0,
        .capacity = capacity,
        .results = (Match *)malloc(capacity * sizeof(Match))
    };
}

void release_matches(Matches *matches)
{
    free(matches->results);
}

bool check_word(Matrix *matrix, char *word, Vector2 *start_position, Vector2 *direction)
{
    for (int i = 0; i < strlen(word); i++)
    {
        Vector2 position = {
            start_position->x + direction->x * i,
            start_position->y + direction->y * i
        };

        if (matrix->vector[position.y * matrix->width + position.x] != word[i])
        {
            return false;
        }
    }

    return true;
}

void check_for_matches(Matrix *matrix, Matches *matches, char *word, Vector2 *initial_position, Orientation orientation)
{
    int word_length = strlen(word);
    int word_offset = word_length - 1;

    Vector2 forward_direction = get_forward_direction(orientation);
    Vector2 backward_direction = {-forward_direction.x, -forward_direction.y};

    Vector2 start_position = *initial_position;

    while (is_in_bounds(matrix, &start_position))
    {
        Vector2 direct_end_position = {
            start_position.x + forward_direction.x * word_offset,
            start_position.y + forward_direction.y * word_offset
        };

        Vector2 reverse_end_position = {
            start_position.x + backward_direction.x * word_offset,
            start_position.y + backward_direction.y * word_offset
        };

        if (is_in_bounds(matrix, &direct_end_position))
        {
            if (check_word(matrix, word, &start_position, &forward_direction))
            {
                matches->results[matches->size++] = (Match) {
                    .order = ORDER_DIRECT,
                    .orientation = orientation,
                    .start = start_position,
                    .end = direct_end_position
                };
            }
        }

        if (is_in_bounds(matrix, &reverse_end_position))
        {
            if (check_word(matrix, word, &start_position, &backward_direction))
            {
                matches->results[matches->size++] = (Match) {
                    .order = ORDER_REVERSE,
                    .orientation = orientation,
                    .start = start_position,
                    .end = reverse_end_position
                };
            }
        }

        start_position.x += forward_direction.x;
        start_position.y += forward_direction.y;
    }
}

Matches search_word(Matrix *matrix, char *word)
{
    Matches matches = create_matches(matrix->width * matrix->height * ORDER_N * ORIENTATION_N);

    for (Vector2 position = {0, 0}; position.y < matrix->height; position.y++)
    {
        check_for_matches(matrix, &matches, word, &position, ORIENTATION_HORIZONTAL);
    }

    for (Vector2 position = {0, 0}; position.x < matrix->width; position.x++)
    {
        check_for_matches(matrix, &matches, word, &position, ORIENTATION_VERTICAL);
    }

    for (int k = 1; k <= matrix->width + matrix->height - 1; k++)
    {
        int x = MAX(k - matrix->height, 0);

        Vector2 main_position = { x, MAX(matrix->height - k, 0) };
        Vector2 secondary_position = { x, MIN(k, matrix->height) - 1 };

        check_for_matches(matrix, &matches, word, &main_position, ORIENTATION_MAIN_DIAGONAL);
        check_for_matches(matrix, &matches, word, &secondary_position, ORIENTATION_SECONDARY_DIAGONAL);
    }

    return matches;
}

void show_order(Order order)
{
    switch (order)
    {
    case ORDER_DIRECT:
        printf("DIRETA");
        break;
    case ORDER_REVERSE:
        printf("REVERSA");    
        break;
    }
}

void show_orientation(Orientation orientation)
{
    switch (orientation)
    {
    case ORIENTATION_HORIZONTAL:
        printf("HORIZONTAL");
        break;
    case ORIENTATION_VERTICAL:
        printf("VERTICAL");
        break;
    case ORIENTATION_MAIN_DIAGONAL:
        printf("DIAGONAL PRINCIPAL");
        break;
    case ORIENTATION_SECONDARY_DIAGONAL:
        printf("DIAGONAL SECUNDARIA");
        break;
    }
}

void show_matches(Matches *matches, char *word)
{
    for (int i = 0; i < matches->size; i++)
    {
        Match *match = &matches->results[i];

        printf("palavra \"%s\" ocorre na ", word);
        show_orientation(match->orientation);
        printf(" ");
        show_order(match->order);
        printf(", iniciando na posicao [%d, %d]", match->start.y + 1, match->start.x + 1);
        printf(" e terminando na posicao [%d, %d]\n", match->end.y + 1, match->end.x + 1);
    }

    printf("- %d/%d ocorrencias\n", matches->size, matches->capacity);
}