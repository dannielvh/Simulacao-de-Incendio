# Trabalho-01---AEDS
Aluno: Danniel Vieira Holanda

Professor: Michel Pires da Silva

Disciplina: Algoritmos e Estrutura de Dados I

## 🦌 Introdução

Este trabalho, desenvolvido em C++, tem como implementação um simulador de propagação de incêndio em uma floresta. Simulando uma matriz bidimensional, que representa a floresta, composta por células que representam partes da floresta, cada uma com seu estado próprio. Além disso, considerando também, a existência de um animal dentro da floresta que se movimenta a cada iteração, assim como as chamas do incêndio que se propagam de maneira ortogonal a cada iteração.

## 📖 Metodologia

No início da simulação do incêndio a primeira coisa a ser feita dentro do programa é a leitura da matriz, que se encontra no arquivo "input.dat", recolhendo as informações mais importantes para a implementação como um todo, ou seja, as dimensões da matriz, e a posição do início do incêndio. Logo após a leitura do arquivo, o animal será colocado na primeira posição de valor 0 que encontrar, assim, colocando o animal numa posição segura.

### 🔥 Propagação do fogo

Antes de explicar a propagação do fogo, é importante falar sobre as configurações da floresta. As células da matriz, cada uma contendo um número inteiro, representam o seu estado dentro da matriz, sendo assim, temos que: 0 (Área segura); 1 (Árvore saudável); 2 (Árvore em chamas); 3 (Árvore queimada); 4 (Água). Em cada uma dessas posições o incêndio reagirá de uma maneira específica.

A propagação do incêndio, após a verificação de se o foco inicial das chamas se encontra em uma posição válida (verificando se está dentro, ou não, da matriz), acontecerá de maneira ortogonal, considerando aqui o primeiro caso sendo sem a influência do vento. Assim, a cada iteração do programa, as árvores saudáveis que estão acima, abaixo, à direita e à esquerda da posição inicial do fogo também serão incendiadas, como é possível ver na função propagacao_Incendio da classe Floresta, desenvolvida nas linhas 117 - 190. Logo, na próxima iteração, essas árvores saudáveis agora estarão incendiadas, e a que antes queimava, agora será considerada uma árvore queimada dentro da matriz.

## 🖥️ Autor

Linkedin: 

Instagram: 
