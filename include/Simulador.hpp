#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include <iostream>
#include <fstream>

#include "Floresta.hpp"
#include "Animal.hpp"
#include "Config.hpp"

class Simulador
{
    private:
        Floresta floresta;
        Animal animal;
        int iteracao;

        bool montar_Floresta();
        bool colocar_Animal();
        void executar_Iteracao();
        void mostrar_Estatistica();
        void estado_Animal();
        void mostrar_Animal();

    public:
        Simulador();
        
        void executar();
};

#endif