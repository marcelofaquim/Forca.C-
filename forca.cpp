#include <iostream>
#include <string> //Biblioteca que permite o uso de string
#include <map>
#include<vector>
#include <fstream>
// Bibliotecas para sortear numeros 
#include <ctime>
#include<cstdlib>
using namespace std;

//Variaveis Global

 string palavra_secreta = "melancia";

 //"map" vai mapear a palavra de modo que o codigo vai entender se a palavra foi chutada ou não
 map<char, bool> chutou;

 //Vetor criado, não preciso colocar nenhum tamanho nele, apenas o conteudo, se chama vetor dinamico

vector<char> chutes_errados;

//BOOL paramentro para escrever uma função
bool letra_existe(char chute) {
   
   // C++ 11, foi utlizado abaixo com suas novas funcionalidades
   //Para chamar a função com o c++11 no cmd usasse "g++ forca.cpp -o forca.exe-std=C++11"
   //Ou criar um arquivo chamado MakeFile e chamar ele no terminal como "mingw32-make forca" se for windowns
   //Linus chama direto "make forca"

    for(char letra : palavra_secreta){
        if(chute == letra){
            return true;
        }
    }
    return false;
}

bool nao_acertou(){
    for(char letra : palavra_secreta){
        if(!chutou[letra]){
            return true;
        }
    }
    return false;
}

bool nao_enforcou(){
    return chutes_errados.size() < 5;
}

void imprime_cabecalho(){
    cout <<"**************************" <<endl;
    cout <<"*    Jogo da Forca       *" <<endl;
    cout <<"**************************" <<endl;
    cout <<endl;
}

void imprime_erros(){
       //Imprimindo o Vector de chutes errados

    cout << "Chutes Errados: ";
    for(char letra: chutes_errados){
        cout << letra << " ";
    }

    cout << endl;

}

void imprime_palavra(){
    for(char letra : palavra_secreta){
            if(chutou [letra]){
                cout << letra << " ";
            }
            else{
                cout << "_ ";
            }
        }

        cout << endl;

}

void chuta(){
     cout << "Chute uma letra: ";

        char chute;

        // "CIN= cogido que lê / recebe"
        cin >> chute;

        chutou[chute] = true;

        if(letra_existe(chute)){
            cout << "Voce acertou! Seu chute esta na palavra. " << endl;
        }
        else{
            cout <<"Voce errou! tente novamente" << endl;
            chutes_errados.push_back(chute);
        }

        cout << endl;
    }

    vector<string> le_arquivo(){
        //ifstream responsavel por lê valores de um arquivo
        ifstream arquivo;
        arquivo.open("palavra.txt");

        if(arquivo.is_open()) {
    
                int quantidade_palavras;
                arquivo >> quantidade_palavras;

                vector<string> palavras_do_arquivo;

                for(int i = 0; i<quantidade_palavras; i++){
                string palavra_lida;
                arquivo >> palavra_lida;
        
                palavras_do_arquivo.push_back(palavra_lida);
            }

                arquivo.close(); //fechando arquivos, para evitar erros futuros
                return palavras_do_arquivo;

        }
        else{
            cout << " Não foi possivel acessar o banco de palavras..." <<endl;

            exit(0); // programa irá parar se houver qualqur erro no arquivo
        }
    }



    void sorteia_palavra(){
        vector<string> palavras = le_arquivo();

        srand(time(NULL));;
        int indice_sorteado = rand() % palavras.size();

        palavra_secreta = palavras[indice_sorteado];
    }

    void salva_arquivo(vector<string> nova_lista){
        ofstream arquivo;
        arquivo.open("palavra.txt");
        if(arquivo.is_open()){
            arquivo << nova_lista.size() << endl;

            for(string palavra : nova_lista){
                arquivo << palavra << endl;
            }

            arquivo.close();
        }

        else{
            cout << " Não foi possivel acessar o banco de palavras..." <<endl;
            exit(0);
        }
    }

    void adiciona_palavra(){
        cout << " Digite uma nova palavra, usando letras maiuculas" <<endl;

        //recebendo palavra que o usuario vai digitar
        string nova_palavra;
        cin >> nova_palavra;

        // adicionando palavras no final da lista existente
        vector<string> lista_palavras = le_arquivo();
        lista_palavras.push_back(nova_palavra);

        //Reescrevendo o banco de palavras, adicionando a palvra nova
        salva_arquivo(lista_palavras);

    }

int main() {
    
    imprime_cabecalho();
    // laços de repetições

    le_arquivo();
    sorteia_palavra();

    while(nao_acertou() && nao_enforcou()) {
        imprime_erros();

        imprime_palavra();

        chuta();   
    }

    cout << "fim de jogo!" <<endl;
    cout << "A palavra secreta era: " <<palavra_secreta << endl;
    if(nao_acertou()){
        cout << "Voce perdeu! Tente novamente!" <<endl;
    }
    else {
        cout << "Parabens! Voce acertou a palavra secreta" <<endl;

        //Fazendo o usuario interagir adiconando uma nova palavra no jogo

        cout << " Você desejar adicionar uma nova palavra no jogo? (S/N) " << endl;
        char resposta;
        cin >> resposta;
        if(resposta == 'S'){
            adiciona_palavra();
        }
    }
} 

