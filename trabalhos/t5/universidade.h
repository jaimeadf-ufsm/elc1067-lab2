#ifndef _UNIVERSIDADE_H_
#define _UNIVERSIDADE_H_

#include "cursos.h"

typedef struct universidade Universidade;

struct universidade {
    Curso *cursos;
};

Universidade *criar_universidade();

#endif
