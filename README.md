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

### 🐾 Animal

A movimentação do animal, demonstrada no arquivo Animal.cpp nas linhas 66 - 132, na função mover_Animal, funciona com uma certa prioridade para aonde ele vai se movimentar na próxima iteração, sempre a melhor escolha vai ser chegar na posição da água (4), se não encontrar água ao seu redor ele procura uma árvore saudável (1) ou uma área segura (0), em último caso ele vai para um árvore queimada (3). Ele também anda apenas de maneira ortogonal, sempre verificando se está dentro da matriz. Podendo até mesmo ficar parado na mesma posição por um determinado número de iterações.

O animal quando encontra uma posição de valor 4 (Água), ele faz com que as árvores que estivessem incendiadas ao redor se apaguem, voltando a serem apenas árvores saudáveis, facilitando sua movimentação, por isso que a prioridade dele sempre é ir para a posição de valor 4.

Se o animal por algum motivo for atingido pelas chamas, ele ganha uma segunda chance, fazendo com que ela consiga escapar uma vez. Caso ocorra de novo, a mesma oportunidade não será concedida novamente. O programa faz com que o animal sempre vá se movimentar primeiro, e só então as chamas avançam, fazendo com que ela consiga escapar com uma certa facilidade maior.

### 🤖 Simulação

Após tudo ser construído, a floresta montada, o animal bem posicionado e o fogo ter sido iniciado, o loop da simulação se inicia. Na função executar, da classe Simulador, começamos garantindo a limpeza do arquivo de saída e aí se executa as iterações.

A função executar_Iteracao começa verificando se animal ainda está vivo, se sim, então ele se movimentará e logo depois as chamas do incêndio serão propagadas de acordo com a configuração que estiver sendo executada. Logo depois então será verificado novamente se o animal está vivo ou se foi atingido pelas chamas, se tiver acontecido algo do tipo, ele receberá a chance de se movimentar novamente ou então será morto pelo fogo. E pra finalizar as coisas, a matriz do jeito que estiver será mostrada dentro do arquivo de saída com o identificador daquela determinada iteração para identificar a qual passo da simulação se refere, e logo abaixo a matriz só que dessa vez mostrando a posição do animal naquela iteração. Importante lembrar que não só as matrizes serão mostradas dentro do arquivo de saída como no terminal também, para que seja possível o usuário acompanhar o desenvolvimento da simulação no terminal, mas sem influenciar em nada, apenas como um observador.

Ao final da simulação, ou todas as árvores saudáveis na matriz que fosse possível para queimar naquela determinada configuração terão queimado ou o animal terá sido morto, e então as estatísticas finais do programa serão mostradas, mostrando quanto passos foram dados, quantas vezes o animal encontrou água e qual foi a sua última posição dentro da matriz, finalizando assim o programa.

## 📈 Caso de testes

Para demonstrar um caso de teste da simulação. Usando a seguinte matriz:

```bash

5 5 1 1
0 1 1 0 0
1 2 1 0 1
1 1 1 0 0
1 0 1 1 0
0 0 1 0 0
```

O fogo vai começar na posição [1, 1] em uma matriz 5x5, considerando o vento desligado, assim as chamas irão se propagar de maneira ortogonal.

```bash

ITERAÇÃO 0:
1 2 1 1 4 
2 3 2 1 1 
1 2 1 1 4 
0 0 0 1 1 
1 4 1 0 4

Posição do animal na ITERAÇÃO 0:
1 2 1 1 4 
2 3 2 1 1 
1 2 1 1 4 
0 X 0 1 1 
1 4 1 0 4

ITERAÇÃO 1:
2 3 2 1 4 
3 3 3 2 1 
2 3 2 1 4 
0 0 0 1 1 
1 4 1 0 4

Posição do animal na ITERAÇÃO 1:
2 3 2 1 4 
3 3 3 2 1 
2 3 2 1 4 
0 0 0 1 1 
1 X 1 0 4

ITERAÇÃO 2:
3 3 3 2 4 
3 3 3 3 2 
3 3 3 2 4 
0 1 0 1 1 
1 0 1 0 4

Posição do animal na ITERAÇÃO 2:
3 3 3 2 4 
3 3 3 3 2 
3 3 3 2 4 
0 1 0 1 1 
1 X 1 0 4

ITERAÇÃO 3:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 1 0 2 1 
1 0 1 0 4

Posição do animal na ITERAÇÃO 3:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 X 0 2 1 
1 0 1 0 4

ITERAÇÃO 4:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 1 0 3 2 
1 0 1 0 4

Posição do animal na ITERAÇÃO 4:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 1 0 3 2 
1 X 1 0 4

ITERAÇÃO 5:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 1 0 3 3 
1 0 1 0 4

Posição do animal na ITERAÇÃO 5:
3 3 3 3 4 
3 3 3 3 3 
3 3 3 3 4 
0 X 0 3 3 
1 0 1 0 4

RESULTADOS:

SOBREVIVEU
Posição final dele dentro da floresta: (3, 1)
Percorreu 5 passos dentro da floresta enquanto estava fugindo do incêndio.
Encontrou 1 fontes d'água.
```

## ⚙️ Como executar o programa

Como executar o programa de simulação de incêndio proposto nesse trabalho:

```bash

make clean
make
make run
```

## 🖥️ Autor

Danniel Vieira Holanda

Linkedin: www.linkedin.com/in/danniel-vieira-81861a334
