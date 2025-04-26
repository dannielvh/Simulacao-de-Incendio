#ifndef FLORESTA_HPP
#define FLORESTA_HPP

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Floresta
{
private:
    int linhas;
    int colunas;
    vector<vector<int>> matriz;
    vector<vector<int>> matriz_Temporaria;

    ofstream arquivo_Saida;

    bool validar_Posicao(int linha, int coluna) const;
    bool propagacao_Vizinho(int linha, int coluna);

public:
    Floresta();

    vector<vector<int>> getMatriz();

    bool ler_Arquivo(string nome_Arquivo);
    bool salvar_Arquivo(string nome_Arquivo, int iteracao, int x, int y);

    bool propagacao_Incendio();
    bool fogo_Ativo();
    bool atualizar_Celulas(int linha, int coluna);

    void imprimir_Matriz();
    void fechar_Arquivo();

    int getLinhas() const
    {
        return linhas;
    }

    int getColunas() const
    {
        return colunas;
    }

    bool getCelula(int linha, int coluna, int &valor) const;
    bool setCelula(int linha, int coluna, int valor);
};

#endif