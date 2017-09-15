/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <iostream>
#include "NoH.h"
#include "Intranet.h"

using namespace std;


struct noH {
    Device* pc;
    NoH *prox;
};

NoH* criarNo (Device *dadosPc){
    NoH *novoNo = new NoH;
    novoNo->pc = dadosPc;
    novoNo->prox = NULL;
    return novoNo;
}

void liberarNo (NoH *dadosNo){
    delete dadosNo;
}

NoH* getNo (NoH *dadosNo){
    return dadosNo;
}

void setNo (NoH *dadosNo, NoH *novoNo){
    dadosNo = novoNo;
}

Device* getNoDevice (NoH *dadosNo){
    return dadosNo->pc;
}

void setNoDevice (NoH *dadosNo, Device *dadosPc){
    dadosNo->pc = dadosPc;
}

NoH* getNoProx (NoH *dadosNo){
    return dadosNo->prox;
}

void setNoProx (NoH *dadosNo, NoH* prox){
    dadosNo->prox = prox;
}
