#include <iostream>
#include <fstream>

#include "Simulador.hpp"

Simulador::Simulador() : iteracao(0)
{}

bool Simulador::montar_Floresta()
{
    if(!floresta.ler_Arquivo("input.dat"))
    {
        cerr << "Erro ao tentar carregar os dados da floresta." << endl;
        return false;
    }

    return true;
}

bool Simulador::colocar_Animal()
{
    for(int i = 0; i < floresta.getLinhas(); i++)
    {
        for(int j = 0; j < floresta.getColunas(); j++)
        {
            int valor;

            if(floresta.getCelula(i, j, valor) && valor == 0)
            {
                animal = Animal(i, j);
                return true;
            }
        }
    }

    return false;
}

void Simulador::executar_Iteracao()
{
    if(animal.verificar_Vivo())
    {
        animal.mover_Animal(floresta);
    }

    floresta.propagacao_Incendio();

    if(animal.verificar_Vivo())
    {
        int estado;

        floresta.getCelula(animal.getLinha(), animal.getColuna(), estado);

        if(estado == 2)
        {
            if(!animal.mover_Animal(floresta))
            {
                animal.matar_Animal(iteracao);
            }
        }
    }

    cout << "ITERAÇÃO: " << iteracao << endl;
    floresta.imprimir_Matriz();
    mostrar_Animal();

    floresta.salvar_Arquivo("output.dat", iteracao, animal.getLinha(), animal.getColuna());
    estado_Animal();

    iteracao++;
}

void Simulador::mostrar_Animal() {
    for(int i = 0; i < floresta.getLinhas(); i++)
    {
        for(int j = 0; j < floresta.getColunas(); j++)
        {
            if(animal.getLinha() == i && animal.getColuna() == j) {
                cout << "X ";
            } else {
                cout << floresta.getMatriz()[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Simulador::estado_Animal()
{
    ofstream arquivo("output.dat", ios::app);

    if(!arquivo)
    {
        return;
    }

    arquivo << " ANIMAL: " << endl;

    if(animal.verificar_Vivo())
    {
        arquivo << "Vivo - Posição (" << animal.getLinha() << ", " << animal.getColuna() << ")" << endl;
        arquivo << "Passos dados: " << animal.getPassos_Percorridos() << endl;
        arquivo << "Número de vezes que encontrou água: " << animal.getVezes_Aguas() << endl;;
    }

    else
    {
        arquivo << "Morto na iteração: " << animal.getIteracao_Morte() << endl;
    }

    arquivo << endl;
}

void Simulador::mostrar_Estatistica()
{
    ofstream arquivo("output.dat", ios::app);

    arquivo << "--- ESTATÍSTICAS FINAIS ---\n" << endl;

    arquivo << "Número total de iterações: " << iteracao << endl;
    arquivo << "Estado do animal: ";

    if(animal.verificar_Vivo())
    {
        arquivo << "       SOBREVIVEU" << endl;;
        arquivo << "Posição final dele dentro da floresta: (" << animal.getLinha() << ", " << animal.getColuna() << ")" << endl;
    }

    else
    {
        arquivo << "MORTO" << endl;
        arquivo << "Morreu na iteração: " << animal.getIteracao_Morte() << endl;
    }

    arquivo << "Percorreu " << animal.getPassos_Percorridos() << " passos dentro da floresta enquanto estava fugindo do incêndio." << endl;
    arquivo << "Encontrou " << animal.getVezes_Aguas() << " fontes d'água." << endl;
}

void Simulador::executar()
{
    ofstream clearFile("output.dat");
    clearFile.close();

    if(!montar_Floresta())
    {
        return;
    }

    if(!colocar_Animal())
    {
        cerr << "Não foi possível colocar o animal dentro da floresta (Nenhuma área segura existente)." << endl;
        return;
    }

    while(iteracao < numMax_Iteracoes && floresta.fogo_Ativo())
    {
        executar_Iteracao();
    }

    mostrar_Estatistica();
    floresta.fechar_Arquivo();
}