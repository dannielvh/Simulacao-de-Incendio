#ifndef CONFIG_HPP
#define CONFIG_HPP

// Forma de propagação do vento (0 = SEM INFLUÊNCIA DO VENTO / 1 = COM INFLUÊNCIA DO VENTO)
const int forma_Propagacao = 0;

// Direções do vento, quando ele for influenciar na propagação do incêndio
const bool vento_Cima = true;
const bool vento_Baixo = true;
const bool vento_Direita = true;
const bool vento_Esquerda = true;

// Número máximo de iterações que vai rodar o programa
const int numMax_Iteracoes = 50;

// Número máximo de iterações parado
const int numMax_Parado = 1;

#endif