#include <iostream>

#include "Animal.hpp"
#include "Floresta.hpp"
#include "Config.hpp"

using namespace std;

Animal::Animal() :
    linha_Atual(-1),
    coluna_Atual(-1),
    passos_Percorridos(0),
    vezes_Agua(0),
    iteracao_Parado(0),
    iteracao_Morte(-1),
    vida(false) {}

Animal::Animal(int linha_Atual, int coluna_Atual) : 
    linha_Atual(linha_Atual),
    coluna_Atual(coluna_Atual),
    passos_Percorridos(0),
    vezes_Agua(0),
    iteracao_Parado(0),
    iteracao_Morte(-1),
    vida(true) {}

bool Animal::pode_Mover(Floresta& floresta, int linha, int coluna)
{
    int valor;

    if(!floresta.getCelula(linha, coluna, valor))
    {
        return false;
    }

    return valor != 2;
}

int Animal::avaliar_Posicao(Floresta& floresta, int linha, int coluna)
{
    int valor;

    if(!floresta.getCelula(linha, coluna, valor))
    {
        return -1;
    }

    if(valor == 4) return 3;
    if(valor == 0) return 2;
    if(valor == 1) return 1;
    if(valor == 2) return 0;
    return -1;
}

bool Animal::area_Segura(Floresta& floresta)
{
    int valor;

    if(!floresta.getCelula(linha_Atual, coluna_Atual, valor))
    {
        return false;
    }
    return valor == 0;
}

bool Animal::mover_Animal(Floresta& floresta)
{
    if(!vida)
    {
        return false;
    }

    int valor_Atual;
    floresta.getCelula(linha_Atual, coluna_Atual, valor_Atual);

    if(valor_Atual == 4)
    {
        vezes_Agua++;
        floresta.atualizar_Celulas(linha_Atual, coluna_Atual);
        return true;
    }

    if(area_Segura(floresta))
    {
        iteracao_Parado++;

        if(iteracao_Parado < numMax_Parado)
        {
            return true;
        }
    }

    else
    {
        iteracao_Parado = 0;
    }

    int melhor_Prioridade = -1;
    int melhor_Linha = linha_Atual;
    int melhor_Coluna = coluna_Atual;

    int direcao[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    for(int i = 0; i < 4; i++)
    {
        int linha_Nova = linha_Atual + direcao[i][0];
        int coluna_Nova = coluna_Atual + direcao[i][1];

        if(pode_Mover(floresta, linha_Nova, coluna_Nova))
        {
            int prioridade = avaliar_Posicao(floresta, linha_Nova, coluna_Nova);

            if(prioridade > melhor_Prioridade)
            {
                melhor_Prioridade = prioridade;
                melhor_Linha = linha_Nova;
                melhor_Coluna = coluna_Nova;
            }
        }
    }

    if(melhor_Prioridade >= 0 && (melhor_Linha != linha_Atual || melhor_Coluna != coluna_Atual))
    {
        linha_Atual = melhor_Linha;
        coluna_Atual = melhor_Coluna;
        passos_Percorridos++;

        return true;
    }

    return false;
}