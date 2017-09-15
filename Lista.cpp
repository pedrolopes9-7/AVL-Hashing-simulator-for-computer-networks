/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include "NoH.h"
#include "Lista.h"

using namespace std;

struct lista {
    NoH *prim;
    NoH *fim;
    int size;
};


Lista* criarLista (){ // criando uma nova Lista
    Lista *novaLista = new Lista;
    novaLista->prim = NULL;
    novaLista->fim = NULL;
    novaLista->size = 0;
    
    return novaLista;
}

bool ehLiVazia (Lista *dadosLista){ // verifica se a Lista é Vazia
    if (dadosLista->prim == NULL){
        return true; // Lista Vazia        
    }
    return false; // Lista nao Vazia
}

void liberarLista (Lista *dadosLista){ // apaga a Lista e libera memoria
    NoH *anterior;
    NoH *p;
        setNo(p, dadosLista->prim); // O No auxiliar recebe o primeiro da Lista.
        while (p != NULL){
            setNo(anterior, p); // anterior recebe o atual
            setNo(p, getNoProx(p)); // o atual recebe o proximo
            liberarNo(anterior); // deleta o anterior
        }
    delete [] dadosLista; // deletando a lista
}

bool addIni (Lista *dadosLista, NoH *dadosNo){ // adiciona na Primeira Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }    
        if(!ehLiVazia(dadosLista)){ // nao é vazia1
            setNoProx(dadosNo, dadosLista->prim); // Faz o novo No apontar para onde o primeiro apontava, ou seja para o segundo.
            dadosLista->prim = dadosNo; // Coloca o novo No como primeiro.
            dadosLista->size ++; // aumenta o tamanho da Lista
        }else{ // é vazia
            dadosLista->prim = dadosNo; // coloca o novo No como primeiro
            dadosLista->fim = dadosNo; // coloca o novo No como ultimo
            dadosLista->size ++; // Aumenta o tamanho da Lista
        }
    return true;
}

bool addFim (Lista *dadosLista, NoH *dadosNo){ // adiciona na Ultima Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }
        if(!ehLiVazia(dadosLista)){
            setNoProx(dadosNo, NULL); // faz o novo No, apontar para NULL, indicando que ele vai ser o ultimo.
            setNoProx(dadosLista->fim, dadosNo); // Faz o no que estava em ultimo apontar para o novo No.
            setNo(dadosLista->fim, dadosNo); // Coloca o No como ultimo
            dadosLista->size ++; // Aumenta o tamanho da Lista
            return true;
        }else{
            return addIni(dadosLista, dadosNo); // chma o metodo de adicionar quando a lista é vazia.
        }   
}

bool addPos (Lista *dadosLista, NoH *dadosNo, int posicao){ // adiciona em qualquer Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }
        if(ehLiVazia(dadosLista) || posicao == 0){ // Primeira posicao ou Lista Vazia
            return addIni(dadosLista, dadosNo); // Metodo para adicionar no inicio ou quando Lista é Vazia
        }else{
            if(posicao >= dadosLista->size){ // Ultima posicao da Lista
                return addFim(dadosLista, dadosNo); // Metodo para adicionar na ultima posicao da Lista.
            }else{ // adiciona nas demais posicões.
                NoH *p = dadosLista->prim;
                    for (int i = 0; i < (posicao - 2); i++){
                        p = getNoProx(p);
                    }
                setNoProx(dadosNo, getNoProx(p)); // O novo No, vai apontar para onde o No anterior apontava.
                setNoProx(p, dadosNo); // O No anterior vai apontar para o novo No.
                dadosLista->size ++; // Aumenta o tamanho da Lista
                return true;
            }
        }
}

bool addOrd (Lista *dadosLista, NoH *dadosNo){ // adiciona na Lista de forma Ordenada
    if(dadosLista == NULL){
        return false;
    }
        if(ehLiVazia(dadosLista)){ // Se a lista está vazia adiciona no inicio.
            return addIni(dadosLista, dadosNo);
        }else{
            NoH *p = dadosLista->prim;
            NoH *ant = NULL;
                while (p != NULL && returnIP(getNoDevice(p)) < returnIP(getNoDevice(dadosNo))){
                    ant = p; // O No anterior recebe o atual.
                    p = getNoProx(p); // o atual recebe o proximo
                }

            if(ant == NULL){
                return addIni(dadosLista, dadosNo);
            }else{
                setNoProx(dadosNo, getNoProx(ant)); // O novo No, vai apontar para onde o No anterior apontava.
                setNoProx(ant, dadosNo); // O No anterior vai apontar para o novo No.
                dadosLista->size ++; // Aumenta o tamanho da Lista
                return true;
            }            
        }
}

int buscarLista (Lista *dadosLista, string ip){ // Busca um Elemento na Lista, Verifica se Pertence
    if(dadosLista == NULL){
        return -1;
    }
        if(ehLiVazia(dadosLista)){ // Se a lista está vazia, nao possui o elemento.
            return -1;
        }else{
            int cont = 0; // contador para saber a posicao
            NoH *p = dadosLista->prim; // O No auxiliar recebe o primeiro da Lista.
            while (p != NULL){
                if(getDeviceIp(getNoDevice(p)) == ip){
                    return cont;
                }
                    p = getNoProx(p); // o atual recebe o proximo
                    cont ++;
            }
        }
}

NoH* buscarNoLista (Lista *dadosLista, string ip){ // Retorna o No Anterior ao No buscado.
    if(dadosLista == NULL){
        return NULL;
    }
        NoH *anterior = dadosLista->prim;
        
        if(!ehLiVazia(dadosLista)){ // Se a lista está vazia, nao possui o elemento.
             // O No auxiliar recebe o primeiro da Lista.
            if(getNoProx(anterior) != NULL){
                while(getNoProx(getNoProx(anterior)) != NULL){
                    if(getDeviceIp(getNoDevice(getNoProx(anterior))) == ip){
                        return anterior;
                    }
                    anterior = getNoProx(anterior);     
                }
            }
            if(getDeviceIp(getNoDevice(anterior)) == ip){
                return anterior;
            }
        }
    
    return NULL;
}

bool atualizarNoLista (Lista *dadosLista, string oldVlr, string novoVlr){ // Atualiza um Elemento na Lista
    if(dadosLista == NULL){
        return false;
    }    
        if(!ehLiVazia(dadosLista)){ // Se a lista nao está vazia
            NoH *anterior = buscarNoLista(dadosLista, oldVlr);
            if(anterior != NULL){
                if(getDeviceIp(getNoDevice(anterior)) == oldVlr){
                    setDeviceIp(getNoDevice(anterior), novoVlr); // O No recebe o novo Valor.
                }else{
                    setDeviceIp(getNoDevice(getNoProx(anterior)), novoVlr); // O No recebe o novo Valor.
                }
                return true;
            }
        }
    return false;
            
}

bool retirarIni (Lista *dadosLista){ // retira da Primeira Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }
        if(!ehLiVazia(dadosLista)){ // Se a lista não está vazia, retira o No na primeira posicao.
            NoH *aux = dadosLista->prim; // No aux recebe o primeiro elemento da Lista.
            dadosLista->prim = getNoProx(aux); // Faz a Lista receber na primeira posicao, o segundo No da Lista.
            liberarNo(aux); // Desaloca memória do antigo No da Lista.
            dadosLista->size --; // Diminui o tamanho da Lista
            return true;
        }else{  // Se a lista está vazia, nao possui o elemento.            
            return false;
        }
}

bool retirarFim (Lista *dadosLista){ // retira da Ultima Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }
        if(!ehLiVazia(dadosLista)){ // Se a lista não está vazia, retira o No na ultima posicao.
            NoH *p = dadosLista->prim; // O No auxiliar recebe o primeiro da Lista.
            NoH *ant = NULL;
                while (getNoProx(p) != NULL){  // o correto seria p->prox != NULL.
                    ant = p; // O No anterior recebe o atual.
                    p = getNoProx(p); // O atual recebe o proximo
                }
                    if(ant == NULL){
                        dadosLista->fim = getNoProx(p);
                        dadosLista->prim = getNoProx(p);
                        dadosLista->size --; // Diminui o tamanho da Lista 
                    }else{
                        liberarNo(dadosLista->fim); // Desalocando a ultima posicao da Lista.
                        setNoProx(ant, NULL); // Atualizando a nova ultima posicao da Lista.
                        dadosLista->fim = ant; // Atualizando a ultima posicao da Lista para o No anterior.                        
                        
                        dadosLista->size --; // Diminui o tamanho da Lista
                    }
        }else{  // Se a lista está vazia, nao possui o elemento.            
            return -1;
        }
    return 0;
}

bool retirarPos (Lista *dadosLista, int posicao){ // retira de qualquer Posicao da Lista
    if(dadosLista == NULL){
        return false;
    }    
        if(ehLiVazia(dadosLista) || posicao == 0){ // Primeira posicao ou Lista Vazia
            return retirarIni(dadosLista); // Metodo para retirar do inicio ou quando Lista é Vazia
        }else{
            if(posicao >= dadosLista->size){ // Ultima posicao da Lista
                return retirarFim(dadosLista); // Metodo para retirar na ultima posicao da Lista.
            }else{ // retira nas demais posicões.
                NoH *p = dadosLista->prim; // O No auxiliar recebe o primeiro da Lista.
                    for (int i = 0; i < (posicao - 1); i++){
                        p = getNoProx(p); // O atual recebe o proximo
                    }
            NoH *aux = getNoProx(p); // O No auxiliar, recebe o No na posicao a ser deletado.            
            setNoProx(p, getNoProx(aux)); // O No anterior recebe o No depois do No que vai ser desalocado.
            liberarNo(aux); // Desalocando a posicao desejada da Lista.
            dadosLista->size --; // Diminui o tamanho da Lista
            return true;
            }
        }
}

void imprimirLista(NoH *dadosNo){
    if (dadosNo != NULL) {
        printDevice(getNoDevice(dadosNo));
        cout << endl;
        imprimirLista(getNoProx(dadosNo));
    }
}

NoH* getPrimeiroLi (Lista *dadosLista){ // retorna o Primeiro Elemento da Lista
    return dadosLista->prim;
}

void setPrimeiroLi (Lista *dadosLista, NoH *dadosNo){ // Altera o Ponteiro do primeiro No da Lista
    dadosLista->prim = dadosNo;
}

NoH* getUltimoLi (Lista *dadosLista){ // retorna o Ultimo Elemento da Lista
    return dadosLista->fim;
}

void setUltimoLi (Lista *dadosLista, NoH *dadosNo){ // Altera o Ponteiro do ultimo No da Lista
    dadosLista->fim = dadosNo;
}

int getSizeLi (Lista *dadosLista){ // retorna o Tamanho da Lista
    return dadosLista->size;
}

void setSizeLi (Lista *dadosLista, int size){ // Altera o Tamanho da Lista
    dadosLista->size = size;
}