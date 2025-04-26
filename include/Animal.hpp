#ifndef ANIMAL_HPP
#define ANIMAL_HPP

class Floresta;

class Animal
{
    private:
        int linha_Atual;
        int coluna_Atual;
        int passos_Percorridos;
        int vezes_Agua;
        int iteracao_Parado;
        int iteracao_Morte;
        bool vida;

        int avaliar_Posicao(Floresta& floresta, int linha, int coluna);
        bool pode_Mover(Floresta& floresta, int linha, int coluna);

    public:
        Animal();
        Animal(int linha_Atual, int coluna_Atual);

        bool mover_Animal(Floresta& floresta);
        bool area_Segura(Floresta& floresta);

        bool verificar_Vivo()
        {
            return vida;
        }

        void matar_Animal(int iteracao) 
        {
            vida = false; iteracao_Morte = iteracao;
        }

        int getLinha() 
        {
            return linha_Atual;
        }

        int getColuna() 
        {
            return coluna_Atual;
        }

        int getPassos_Percorridos() 
        {
            return passos_Percorridos;
        }

        int getVezes_Aguas() 
        {
            return vezes_Agua;
        }

        int getIteracao_Morte() 
        {
            return iteracao_Morte;
        }
};

#endif