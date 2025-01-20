#pragma once
struct el {
    int klucz;
    struct el* nast;
};
typedef struct el elListy;
typedef elListy* lista;