#include <stdlib.h>

#include "universidade.h"

Universidade *criar_universidade()
{
    Universidade *universidade = (Universidade *)malloc(sizeof(Universidade));
    universidade->cursos = criar_cursos();

    return universidade;
}