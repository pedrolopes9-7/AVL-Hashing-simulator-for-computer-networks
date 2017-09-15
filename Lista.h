/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Lista.h
 * Author: Rainer
 *
 * Created on 5 de Julho de 2017, 09:16
 */

#ifndef LISTA_H
#define LISTA_H

#include <iostream>
#include "NoH.h"

using namespace std;

typedef struct lista Lista;

Lista* criarLista (); // criando uma nova Lista
bool ehLiVazia (Lista *dadosLista); // verifica se a Lista é Vazia
void liberarLista (Lista *dadosLista); // apaga a Lista e libera memoria
bool addIni (Lista *dadosLista, NoH *dadosNo); // adiciona na Primeira Posicao da Lista
bool addFim (Lista *dadosLista, NoH *dadosNo); // adiciona na Ultima Posicao da Lista
bool addPos (Lista *dadosLista, NoH *dadosNo, int posicao); // adiciona em qualquer Posicao da Lista
bool addOrd (Lista *dadosLista, NoH *dadosNo); // adiciona na Lista de forma Ordenada
int buscarLista (Lista *dadosLista, string ip); // Busca um Elemento na Lista, Verifica se Pertence
NoH* buscarNoLista (Lista *dadosLista, string ip); // Retorna o No Anterior ao No buscado.
bool atualizarNoLista (Lista *dadosLista, string oldVlr, string novoVlr); // Atualiza um Elemento na Lista
bool retirarIni (Lista *dadosLista); // retira da Primeira Posicao da Lista
bool retirarFim (Lista *dadosLista); // retira da Ultima Posicao da Lista
bool retirarPos (Lista *dadosLista, int posicao); // retira de qualquer Posicao da Lista
void imprimirLista(NoH *dadosNo); // imprimir Lista
NoH* getPrimeiroLi (Lista *dadosLista); // retorna o Primeiro Elemento da Lista
void setPrimeiroLi (Lista *dadosLista, NoH *dadosNo); // Altera o Ponteiro do primeiro No da Lista
NoH* getUltimoLi (Lista *dadosLista); // retorna o Ultimo Elemento da Lista
void setUltimoLi (Lista *dadosLista, NoH *dadosNo); // Altera o Ponteiro do ultimo No da Lista
int getSizeLi (Lista *dadosLista); // retorna o Tamanho da Lista
void setSizeLi (Lista *dadosLista, int size); // Altera o Tamanho da Lista


#endif /* LISTA_H */

