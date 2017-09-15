/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NoF.h
 * Author: Rainer
 *
 * Created on 5 de Julho de 2017, 09:22
 */

#ifndef NOH_H
#define NOH_H

#include <iostream>
#include "Intranet.h"

using namespace std;

typedef struct noH NoH;

NoH* criarNo (struct Device *dadosPc);
void liberarNo (NoH *dadosNo);
NoH* getNo (NoH *dadosNo);
void setNo (NoH *dadosNo, NoH *novoNo);
struct Device* getNoDevice (NoH *dadosNo);
void setNoDevice (NoH *dadosNo, struct Device *dadosPc);
NoH* getNoProx (NoH *dadosNo);
void setNoProx (NoH *dadosNo, NoH* prox);




#endif /* NOH_H */

