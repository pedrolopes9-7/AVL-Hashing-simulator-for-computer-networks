/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include "Hash.h"
#include "Lista.h"
#include "NoH.h"
#include "Vetor.h"
#include "Tratamento.h"

using namespace std;


struct hash {
    int qtdItens;
    int sizeListas;
    int sizePesos;
    int *pesos;
    Lista* *vetor;
};

Hash* criarHash (int sizeListas, int sizePesos){  // Cria uma Tabelha Hash
    Hash *dadosHash = new Hash();
    dadosHash->qtdItens = 0;
    dadosHash->sizeListas = sizeListas;
    dadosHash->sizePesos = sizePesos;
    
    dadosHash->vetor = criarVetLista (sizeListas); // inicializando as listas
        for(int i = 0; i < sizeListas; i++){
            dadosHash->vetor[i] = criarLista();
        }
    
    dadosHash->pesos = new int [sizePesos];
    srand (time(NULL)); // criando numero aleatorio
        for(int i = 0; i < sizePesos; i++){
            dadosHash->pesos[i] = rand() % 10000;
        }
    return dadosHash;
}

int indiceHash (Hash *dadosHash, NoH *dadosNo){ // Retorna o Indice da Chave na Tabela Hash
    int i;
    unsigned int soma = 0;
    string chave = changeInttoString(returnIP(getNoDevice(dadosNo)));
    int comp =  chave.length(); // retorna o tamanho da string chave.
        for (i = 0; i < comp; i++){
            soma += (unsigned int) chave[i] * dadosHash-> pesos[i % dadosHash-> sizePesos];
        }
    return (soma % dadosHash-> sizeListas);
}

NoH* searchHashNo(Hash *dadosHash, NoH *dadosNo){ // Retorna um ponteiro para o No anterior ao procurado.
    int i = indiceHash(dadosHash, dadosNo); 
   
        if(ehLiVazia(dadosHash->vetor[i])){// é vazia
            return NULL;
        }
    
    NoH *anterior = buscarNoLista(dadosHash->vetor[i], getDeviceIp(getNoDevice(dadosNo)));

    return anterior;
}

bool searchHashItem (Hash *dadosHash, NoH *dadosNo){ // Se o item existir retorna o No por referencia, com todos os dados
    NoH *anterior = searchHashNo(dadosHash, dadosNo);  // retorna o no anterior do valor que busco
    
        if(anterior == NULL){
            return false;
        }
            if(getNoProx(anterior) != NULL){
                dadosNo = getNoProx(anterior);                
            }else{
                dadosNo = anterior;
            }
    return true;
}

bool addHash(Hash *dadosHash, NoH *dadosNo){ // Insere um novo No / Item na Tabela Hash
    if(!searchHashNo(dadosHash, dadosNo)){ // Item nao existe na Tabela Hash
        bool aux = addFim(dadosHash->vetor[indiceHash(dadosHash, dadosNo)], dadosNo);
            if(aux){
                dadosHash->qtdItens ++;
                return true;
            }
    }
    return false;
}

bool removeHash (Hash *dadosHash, NoH *dadosNo){ // Remove um Item / No da Tabela Hash
    NoH *anterior = searchHashNo(dadosHash, dadosNo);  // retorna o no anterior do valor que busco
    
        if(anterior != NULL){
            int indice = indiceHash(dadosHash, anterior); // Armazena a posicao da lista na Tabela Hash
            int pos = buscarLista(dadosHash->vetor[indice], getDeviceIp(getNoDevice(dadosNo))); // Armazena a posicao do No na lista.
            bool aux = retirarPos(dadosHash->vetor[indice], pos);
                if(aux){
                    dadosHash->qtdItens --;
                    return true;
                }
        }
    return false;
}

int getItenHT(Hash *dadosHash){ // Retorna a quantidade de Itens
    return dadosHash->qtdItens;
}
 
int getSizeLiHT (Hash *dadosHash){ // Retorna o tamanho da Lista
    return dadosHash->sizeListas;
}

void setSizeLiHT (Hash *dadosHash, int tamanho){ // Muda o tamanho da Lista
    dadosHash->sizeListas = tamanho;
}

int getSizePeHT (Hash *dadosHash){ // Retorna o tamanho da Pesos
    return dadosHash->sizePesos;
}

Lista* getListaHT (Hash *dadosHash, int pos){ // Retorna a Lista da Tabela Hash
    return dadosHash->vetor[pos];
}