/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rainer
 *
 * Created on 26 de Agosto de 2017, 09:53
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "Intranet.h"
#include "AVLTree.h"
#include "Tratamento.h"
#include "Hash.h"
#include "Lista.h"

using namespace std;

/*
 * 
 */

void menu(Node **root, Hash *tabela); // Menu Principal
void inserirDispositivos (Node **root, Hash *tabela); // Inserir Dispositivos na Rede
void removerDispositivos (Node **root, Hash *tabela); // Remover Dispositivos na Rede
void exibirDispositivos (Node **root, Hash *tabela); // Imprimir todos os Dispositivos da Rede
void enviarPacotes (Node **root, Hash *tabela); // Enviar Pacotes na Rede
void exibirPacotes (Node **root, Hash *tabela); // Exibir Pacotes de um Dispositivo Conectado


int main(int argc, char** argv) {
    Node *root = NULL;
    Hash *tabela = criarHash(255, 12);

    do{
        
        menu (&root, tabela);
        
    }while(true);
    
    return 0;
}

void menu(Node **root, Hash *tabela){
    cout << "Rede" << endl;
    cout << "Escolha entre as opções:\n" << endl;
    cout << "0 - Sair" << endl;    
    cout << "1 - Inserir novo Dispositivo na Intranet" << endl;
    cout << "2 - Remover Dispositivo" << endl;
    cout << "3 - Exibir todos os Dispositivos" << endl;
    cout << "4 - Enviar Pacotes" << endl;
    cout << "5 - Quantidade de Dispositivos Conectados\n" << endl;
    
    int opcao;
    
    cin >> opcao;
    cout << endl;
    
    switch (opcao){
        case 0:{
            exit(0);
        }break;
        case 1:{
            inserirDispositivos(&(*root), tabela);
        }break;
        case 2:{
            removerDispositivos(&(*root), tabela);          
        }break;
        case 3:{
            exibirDispositivos(&(*root), tabela);
        }break;
        case 4:{
            enviarPacotes(&(*root), tabela);
        }break;
        case 5:{
            exibirPacotes(&(*root), tabela);
        }break;
        default:{
            cout << "Opcao Invalida" << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void inserirDispositivos (Node **root, Hash *tabela){ // Inserir Dispositivos na Rede
    string ipv4, gateway, mac, name;
    cout << "Criando um Dispositivo" << endl;
    cout << "Entre com os seguintes dados:\n" << endl;
    cout << "IPv4:" << endl;
    cin >> ipv4;
    cout << "Gateway:" << endl;
    cin >> gateway;
    cout << "MAC:" << endl;
    cin >> mac;
    cout << "Nome PC:" << endl;
    cin >> name;

    Device *dadosPC = criarDevice(ipv4, gateway, mac, name);
    bool aux;

        if(tryIP(ipv4)){
            (*root) = insertNode((*root), dadosPC); // Adiciona dispositivo na Intranet.
                if(root != NULL){

                }
            aux = true;
        }else{
            NoH *dadosNo = criarNo(dadosPC);
            aux = addHash(tabela, dadosNo); // Adiciona dispositivo na Internet
        }

            if(aux){
                cout << "Dispositivo incluido com sucesso" << endl;
            }else{
                cout << "Operacao Cancelada" << endl;
            }
}

void removerDispositivos (Node **root, Hash *tabela){ // Remover Dispositivos na Rede
    string ipv4;
    cout << "Excluindo um Dispositivo" << endl;
    cout << "Entre com os seguintes dados:\n" << endl;
    cout << "IPv4:" << endl;
    cin >> ipv4;
    int ip = ipSplit(ipv4);

    bool aux;

        if(tryIP(ipv4)){
            (*root) = deleteNode((*root), (Device*) getDevice(AVLsearch(*root, ip))); // Remove dispositivo na Intranet.
            aux = true;
        }else{
            Device *dadosPC = criarDevice(ipv4, "", "", "");
            NoH *dadosNo = criarNo(dadosPC);
            aux = removeHash(tabela, dadosNo); // Remove dispositivo na Internet
        }

            if(aux){
                cout << "Dispositivo excluido com sucesso" << endl;
            }else{
                cout << "Operacao Cancelada" << endl;
            }
}

void exibirDispositivos (Node **root, Hash *tabela){ // Imprimir todos os Dispositivos da Rede
    cout << "Rede" << endl;
    cout << "Dispositivos da Intranet: \n" << endl;
        preOrder(*root);
        
    cout << "Dispositivos da Internet: \n" << endl;
    for(int i = 0; i < getSizeLiHT(tabela); i++){
        if(!ehLiVazia(getListaHT(tabela, i))){
            cout << "Dispositivos: " << endl;
            imprimirLista(getPrimeiroLi(getListaHT(tabela, i)));  
        }
    }        
}

void enviarPacotes (Node **root, Hash *tabela){ // Enviar Pacotes na Rede
    string ipv4End1, ipv4End2, message;

    cout << "Enviando Pacotes na Rede" << endl;
    cout << "Entre com os seguintes dados:\n" << endl;
    cout << "IPv4 Origem:" << endl;
    cin >> ipv4End1;
    cout << "IPv4 Destino:" << endl;
    cin >> ipv4End2;
    cout << "Mensagem:" << endl; 
    cin >> message;
    
    bool aux = sendPackage(tabela, *root, message, ipv4End1, ipv4End2);
        if(aux){
            cout << "\n Pacote Enviado" << endl;
        }else{
            cout << "\n Sem Conexao" << endl;
        }
}

void exibirPacotes (Node **root, Hash *tabela){ // Exibir Pacotes de um Dispositivo Conectado
    string ipv4;
    cout << "Rede" << endl;
    cout << "Pacotes de um Dispositivo" << endl;
    cout << "Entre com os seguintes dados:\n" << endl;
    cout << "IPv4:" << endl;
    cin >> ipv4;
    
        if(tryIP(ipv4)){
            Node *dadosNo = AVLsearch(*root, ipSplit(ipv4));
                if(dadosNo != NULL){
                    cout << "Pacotes Enviados" << endl;
                    cout << getMensagemPack(getPackEnv(getDevice(dadosNo))) << endl;
                    cout << "Pacotes Recebidos" << endl;
                    cout << getMensagemPack(getPackReceb(getDevice(dadosNo))) << endl;
                }else{
                    cout << "Dispositivo nao esta conectado" << endl;
                }
        }else{
            Device *dadosPC = criarDevice(ipv4, "", "", "");
            NoH *dadosNo = criarNo(dadosPC);
            bool aux = searchHashItem(tabela, dadosNo);
                if(aux){
                    cout << "Pacotes Enviados" << endl;
                    cout << getMensagemPack(getPackEnv(getNoDevice(dadosNo))) << endl;
                    cout << "Pacotes Recebidos" << endl;
                    cout << getMensagemPack(getPackReceb(getNoDevice(dadosNo))) << endl;
                }else{
                    cout << "Dispositivo nao esta conectado" << endl;
                }
        }
        
        
   
}

    