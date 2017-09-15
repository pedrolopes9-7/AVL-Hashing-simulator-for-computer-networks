/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Intranet.h
 * Author: rainer
 *
 * Created on 26 de Agosto de 2017, 09:59
 */

#ifndef INTRANET_H
#define INTRANET_H

#include <string>
#include <iostream>
#include <vector>
#include "AVLTree.h"
#include "Hash.h"

using namespace std;

    struct Device;
    struct Connection;
    struct Package;
    struct Device* insertDevice(string, string, string, string);
    int returnIP(struct Device* n);
    void printDevice(struct Device *d);
    bool sendPackage(Hash *tabela, struct Node* root, string message, string hostIPv4, string receiverIPv4); // Enviar Pacotes na Rede
    Device* criarDevice (string endIPv4, string padraoGateway, string endMAC, string nomePC); // Cria um novo Device
    Package* criarPackage (string mensagem); // Cria um novo pacote
    void liberarDevice (Device *dadosPC); // Liberando a memoria alocada
    void liberarPackage (Package *dadosPacote); // Liberando a memoria alocada
    string getDeviceIp(Device *dadosPC); // Retorna o Ip da Maquina
    void setDeviceIp (Device *dadosPC, string ip); // Substitui o Ip da Maquina
    Package* getPackReceb(Device *dadosPC); // Retorna o pacote Ultimo recebido
    void setPackReceb (Device *dadosPC, Package *pacote); // Substitui o Package Recebido
    Package* getPackEnv(Device *dadosPC); // Retorna o pacote Ultimo enviado
    void setPackEnv (Device *dadosPC, Package *pacote); // Substitui o Package Enviado
    string getMensagemPack (Package *pacote); // Retorna a Mensagem do Pacote
    
#endif /* INTRANET_H */

