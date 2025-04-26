# Trabalho-01-AEDS
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

Como explicado anteriormente, as células da matriz contam com reações diferentes ao incêndio, como por exemplo, se o incêndio tentar chegar a uma posição que seja de uma área segura (0), nada vai acontecer, assim como nas posições que tiverem água, que também não entrarão em combustão. As árvores saudáveis passarão a queimar, e as que já foram queimadas não serão incendiadas novamente.

Já o incêndio com intervenção do vento, funciona de uma maneira um pouco diferente. As quatro constantes de booleano que estão registradas no arquivo Config.hpp servem para verificar se o incêndio deve agir em um determinada direção, fazendo com que em casos que o vento esteja "ligado" para uma determinada direção, as chamas irão tender a se espalhar pra lá. A propagação nesse caso funciona do mesmo jeito que quando não se tem essa influência, verifica se a célula naquela direção é uma árvore saudável e se está dentro da matriz, e assim será queimada. Isso muda, quando a variável forma_Propagação dentro da classe Config estiver como 1, assim o programa saberá que deve contar com a influência do vento.

## 🖥️ Autor

Linkedin: 

Instagram: 
