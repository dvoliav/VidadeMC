#include <stdlib.h>
#include <string.h>

#include "core/musicas.h"

static Musica* listaMusicas = NULL;

void adicionarMusica(
    char nome[],
    int pontuacao,
    char qualidade[]
)
{
    Musica* nova = malloc(sizeof(Musica));

    strcpy(nova->nome, nome);

    nova->pontuacao = pontuacao;

    strcpy(nova->qualidade, qualidade);

    nova->postada = false;

    nova->prox = NULL;

    if (listaMusicas == NULL)
    {
        listaMusicas = nova;
    }
    else
    {
        Musica* atual = listaMusicas;

        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }

        atual->prox = nova;
    }
}

Musica* obterListaMusicas(void)
{
    return listaMusicas;
}