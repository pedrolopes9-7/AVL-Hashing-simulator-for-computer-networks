/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hash.h
 * Author: rainer
 *
 * Created on 24 de Agosto de 2017, 11:37
 */

#ifndef HASH_H
#define HASH_H

#include <iostream>
#include "NoH.h"
#include "Lista.h"


using namespace std;

typedef struct hash Hash;

Hash* criarHash (int sizeListas, int sizePesos);  // Cria uma Tabelha Hash
int indiceHash (Hash *dadosHash, NoH *dadosNo); // Retorna o Indice da Chave na Tabela Hash
NoH* searchHashNo(Hash *dadosHash, NoH *dadosNo); // Retorna um ponteiro para o No anterior ao procurado.
bool searchHashItem (Hash *dadosHash, NoH *dadosNo); // Se o item existir retorna o No por referencia, com todos os dados
bool addHash(Hash *dadosHash, NoH *dadosNo); // Insere um novo No / Item na Tabela Hash
bool removeHash (Hash *dadosHash, NoH *dadosNo); // Remove um Item / No da Tabela Hash
int getItenHT(Hash *dadosHash); // Retorna a quantidade de Itens
int getSizeLiHT (Hash *dadosHash); // Retorna o tamanho da Lista
void setSizeLiHT (Hash *dadosHash, int tamanho); // Muda o tamanho da Lista
int getSizePeHT (Hash *dadosHash); // Retorna o tamanho da Pesos
Lista* getListaHT (Hash *dadosHash, int pos); // Retorna a Lista da Tabela Hash

#endif /* HASH_H */

