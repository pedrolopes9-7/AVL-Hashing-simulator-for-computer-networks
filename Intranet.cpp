/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Intranet.h"
#include "AVLTree.h"
#include "Tratamento.h"
#include "NoH.h"
#include "Hash.h"
#include <string>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

struct Device {
    string IPv4_ADDRESS;
    string DEFAULT_GATEWAY;
    string MAC_ADDRESS;
    string NAME;
    Package * last_received_package;
    Package * last_sent_package;
};

struct Package {
    string message;
    long time;
};

int returnIP(Device* n){
    int ip = ipSplit(n->IPv4_ADDRESS);

    return ip;
}

Device* insertDevice(string IPv4_ADDRESS, string DEFAULT_GATEWAY, string MAC_ADDRESS, string NAME) {
    Device * d = new Device;
    d->IPv4_ADDRESS = IPv4_ADDRESS;
    d->DEFAULT_GATEWAY = DEFAULT_GATEWAY;
    d->MAC_ADDRESS = MAC_ADDRESS;
    d->NAME = NAME;
    return d;
}

void printDevice(Device *d) {
    cout << "\nDISPOSITIVO: " << d->NAME << endl;
    cout << "IPv4: " << d->IPv4_ADDRESS << endl;
    cout << "GATEWAY PADRAO: " << d->DEFAULT_GATEWAY << endl;
    cout << "ENDEREÇO MAC: " << d->MAC_ADDRESS << endl;
}


bool sendPackage(Hash *tabela, struct Node* root, string message, string hostIPv4, string receiverIPv4) { // Enviar Pacotes na Rede
    clock_t Ticks[2];
    Ticks[0] = clock();
    NoH *hostHT = NULL; 
    NoH*receiverHT = NULL;
    Node* hostA = NULL;
    Node* receiverA = NULL;
    
    Package *pacote = criarPackage(message);
    
        if(tryIP(hostIPv4)){
            hostA = AVLsearch(root, ipSplit(hostIPv4));
                if(hostA == NULL){
                    
                    return false;
                }
            setPackEnv(getDevice(hostA), pacote);
        }else{
            Device *dadosPC = criarDevice(hostIPv4, "", "", "");
            hostHT = criarNo(dadosPC);
            bool aux = searchHashItem (tabela, hostHT);
                if(!aux){
                    return false;
                }
            (getNoDevice(hostHT)->last_sent_package = pacote);
        }
            if(tryIP(receiverIPv4)){
                receiverA = AVLsearch(root, ipSplit(receiverIPv4));
                    if(receiverA == NULL){
                        cout << "Sem Conexao" << endl;
                        return false;
                    }
                setPackReceb(getDevice(receiverA), pacote);
            }else{
                Device *dadosPC = criarDevice(receiverIPv4, "", "", "");
                receiverHT = criarNo(dadosPC);
                bool aux = searchHashItem(tabela, receiverHT);
                    if(!aux){
                        cout << "Sem Conexao" << endl;
                        return false;
                    }
                (getNoDevice(receiverHT)->last_received_package = pacote);
            }    

    Ticks[1] = clock();
    pacote->time = (Ticks[1] - Ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    cout << "TIME_ELAPSED " << pacote->time << "ms" << endl;
    return true;
}


Device* criarDevice (string endIPv4, string padraoGateway, string endMAC, string nomePC){ // Cria um novo Device
    Device *dadosPC = new Device ();
	dadosPC->IPv4_ADDRESS = endIPv4;
	dadosPC->DEFAULT_GATEWAY = padraoGateway;
	dadosPC->MAC_ADDRESS = endMAC;
	dadosPC->NAME = nomePC;
        dadosPC->last_received_package = criarPackage("");
        dadosPC->last_sent_package = criarPackage("");
    return dadosPC;
}

Package* criarPackage (string mensagem){ // Cria um novo pacote
    Package *dadosPacote = new Package ();
        dadosPacote->message = mensagem;
        dadosPacote->time = 0;
    return dadosPacote;
}

void liberarDevice (Device *dadosPC){ // Liberando a memoria alocada
    liberarPackage(dadosPC->last_received_package);
    liberarPackage(dadosPC->last_sent_package);
    delete dadosPC;
}

void liberarPackage(Package *dadosPacote) { // Liberando a memoria alocada
    delete dadosPacote;
}

string getDeviceIp(Device *dadosPC){ // Retorna o Ip da Maquina   
    return dadosPC->IPv4_ADDRESS;
}

void setDeviceIp (Device *dadosPC, string ip){ // Substitui o Ip da Maquina
    dadosPC->IPv4_ADDRESS = ip;
}

Package* getPackReceb(Device *dadosPC){ // Retorna o pacote Ultimo recebido
    return dadosPC->last_received_package;
}

void setPackReceb (Device *dadosPC, Package *pacote){ // Substitui o Package Recebido
    dadosPC->last_received_package = pacote;
}

Package* getPackEnv(Device *dadosPC){ // Retorna o pacote Ultimo enviado
    return dadosPC->last_sent_package;
}

void setPackEnv (Device *dadosPC, Package *pacote){ // Substitui o Package Enviado
    dadosPC->last_sent_package = pacote;
}

string getMensagemPack (Package *pacote){ // Retorna a Mensagem do Pacote
    return pacote->message;
}

