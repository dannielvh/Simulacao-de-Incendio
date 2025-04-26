#include <iostream>
#include <fstream>

#include "Floresta.hpp"
#include "Animal.hpp"
#include "Config.hpp"

using namespace std;

Floresta::Floresta() : linhas(0), colunas(0)
{
    this->arquivo_Saida = ofstream("output.dat");
}

bool Floresta::ler_Arquivo(string nome_Arquivo)
{
    ifstream arquivo(nome_Arquivo);

    if(!arquivo.is_open())
    {
        cerr << "Erro ao tentar abrir o arquivo: " << nome_Arquivo << endl;
        return false;
    }

    int linhas_Fogo, colunas_Fogo;

    arquivo >> linhas >> colunas >> linhas_Fogo >> colunas_Fogo;

    if(linhas <= 0 || colunas <= 0)
    {
        cerr << "As dimensões são inválidas." << endl;
        arquivo.close();
        return false;
    }

    matriz.resize(linhas, vector<int>(colunas, 0));
    matriz_Temporaria.resize(linhas, vector<int>(colunas, 0));

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(!(arquivo >> matriz[i][j]))
            {
                cerr << "Erro ao ler a posição (" << i << ", " << j << ") do arquivo." << endl;
                arquivo.close();
                return false;
            }
        }
    }

    if(validar_Posicao(linhas_Fogo, colunas_Fogo))
    {
        matriz[linhas_Fogo][colunas_Fogo] = 2;
        cout << "Fogo iniciado em " << linhas_Fogo << ", "<< colunas_Fogo << endl;
    }

    else
    {
        cerr << "Posição inical do fogo inválida." << endl;
        arquivo.close();
        return false;
    }

    arquivo.close();
    return true;
}

bool Floresta::salvar_Arquivo(string nome_Arquivo, int iteracao, int x, int y)
{
    if(!arquivo_Saida.is_open())
    {
        arquivo_Saida.open(nome_Arquivo, ios::app);

        if(!arquivo_Saida.is_open())
        {
            cerr << "Erro ao tentar abrir o arquivo de escrita: " << nome_Arquivo << endl;
            return false;
        }
    }

    arquivo_Saida << "ITERAÇÃO: " << iteracao << "\n";

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            arquivo_Saida << matriz[i][j] << " ";
        }
        arquivo_Saida << "\n";
    }
    arquivo_Saida << "\n";

    arquivo_Saida << "Estado do animal:\n";

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(x == i && y == j) {
                arquivo_Saida << "X ";
            } else {
                arquivo_Saida << matriz[i][j] << " ";
            }
        }
        arquivo_Saida << "\n";
    }
    arquivo_Saida << "\n";


    return true;
}

bool Floresta::validar_Posicao(int linha, int coluna) const
{
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

bool Floresta::propagacao_Vizinho(int linha, int coluna)
{
    if(!validar_Posicao(linha, coluna))
    {
        return false;
    }

    if(matriz[linha][coluna] == 1)
    {
        matriz_Temporaria[linha][coluna] = 2;
        return true;
    }
    return false;
}

bool Floresta::propagacao_Incendio()
{
    vector<vector<int>> nova_Matriz = matriz;

    bool incendiou = false;

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(matriz[i][j] == 2)
            {
                nova_Matriz[i][j] = 3;

                if(forma_Propagacao == 0)
                {
                    if(i > 0 && matriz[i-1][j] == 1) // Cima
                    {
                        nova_Matriz[i-1][j] = 2;
                        incendiou = true;
                    }

                    if(i < linhas - 1 && matriz[i+1][j] == 1) // Baixo
                    {
                        nova_Matriz[i+1][j] = 2;
                        incendiou = true;
                    }

                    if(j > 0 && matriz[i][j-1] == 1) // Esquerda
                    {
                        nova_Matriz[i][j-1] = 2;
                        incendiou = true;
                    }

                    if(j < colunas - 1 && matriz[i][j+1] == 1) // Direita
                    {
                        nova_Matriz[i][j+1] = 2;
                        incendiou = true;
                    }
                }

                else
                {
                    if(vento_Cima && i > 0 && matriz[i-1][j] == 1)
                    {
                        nova_Matriz[i-1][j] = 2;
                        incendiou = true;
                    }

                    if(vento_Baixo && i < linhas - 1 && matriz[i+1][j] == 1)
                    {
                        nova_Matriz[i+1][j] = 2;
                        incendiou = true;
                    }

                    if(vento_Esquerda && j > 0 && matriz[i][j-1] == 1)
                    {
                        nova_Matriz[i][j-1] = 2;
                        incendiou = true;
                    }

                    if(vento_Direita && j < colunas - 1 && matriz[i][j+1] == 1)
                    {
                        nova_Matriz[i][j+1] = 2;
                        incendiou = true;
                    }
                }
            }
        }
    }

    matriz = nova_Matriz;
    return incendiou;
}

bool Floresta::fogo_Ativo()
{
    for(const auto& linha : matriz)
    {
        for(int valor : linha)
        {
            if(valor == 2)
            {
                return true;
            }
        }
    }
    return false;
}

bool Floresta::atualizar_Celulas(int linha, int coluna)
{
    if(!validar_Posicao(linha, coluna))
    {
        return false;
    }

    if(matriz[linha][coluna] == 4)
    {
        matriz[linha][coluna] = 0;
    }
    
    else
    {
        return false;
    }

    bool atualizou_Posicao = false;

    if(validar_Posicao(linha-1, coluna) && matriz[linha-1][coluna] != 4)
    {
        matriz[linha-1][coluna] = 1;
        atualizou_Posicao = true;
    }

    if(validar_Posicao(linha+1, coluna) && matriz[linha+1][coluna] != 4)
    {
        matriz[linha+1][coluna] = 1;
        atualizou_Posicao = true;
    }

    if(validar_Posicao(linha, coluna-1) && matriz[linha][coluna-1] != 4)
    {
        matriz[linha][coluna-1] = 1;
        atualizou_Posicao = true;
    }

    if(validar_Posicao(linha, coluna+1) && matriz[linha][coluna+1] != 4)
    {
        matriz[linha][coluna+1] = 1;
        atualizou_Posicao = true;
    }

    return atualizou_Posicao;
}

void Floresta::imprimir_Matriz()
{
    for(const auto& linha : matriz)
    {
        for(int valor : linha)
        {
            cout << valor << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

vector<vector<int>> Floresta::getMatriz() {
    return matriz;
}

void Floresta::fechar_Arquivo()
{
    if(arquivo_Saida.is_open())
    {
        arquivo_Saida.close();
    }
}

bool Floresta::getCelula(int linha, int coluna, int& valor) const
{
    if(!validar_Posicao(linha, coluna))
    {
        return false;
    }

    valor = matriz[linha][coluna];
    return true;
}

bool Floresta::setCelula(int linha, int coluna, int valor)
{
    if(!validar_Posicao(linha, coluna))
    {
        return false;
    }

    matriz[linha][coluna] = valor;
    return true;
}