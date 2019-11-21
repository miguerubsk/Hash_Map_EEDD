/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashCliente.cpp
 * Author: Fernando
 * 
 * Created on November 18, 2019, 4:17 PM
 */

#include "THashCliente.h"

THashCliente::THashCliente(int tam=0) {
    tamf=tam;
    primorelativo=PrimoPorDebajo(tam);
    taml=0;
    maxcoli=0;
    totalColisiones=0;
    Cliente();
}

vector<string> THashCliente::getDNIClientes(){
    vector<string> aux;
    for (int i=0; i < v.size(); ++i){
        if (v[i].marca == ocupada){
            aux.push_back(v[i].dato.GetDNI());
        }
    }
    return aux;
}

THashCliente::~THashCliente() {
}

bool THashCliente::inserta(const std::string& dni, Cliente &cli){
    unsigned i=0,y;
    int p=-1, final;
    bool encontrado = false, aux=false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());

    while (!encontrado) {
        y=fcuadratica(clave, i);           
        if (v[y].marca==vacia ) {
            if (p==-1)
                final=y;
            else
                final=p;
            taml++;
            v[final].dato.GetDNI()=dni;
            v[final].marca=ocupada;
            v[final].clave=clave;                             
            v[final].dato=cli;  //push_back(dato);                                                
            encontrado = true;   //Encontre un sitio libre  
        }else{
            if (v[y].marca==disponible && aux==false){
                p=y;
                aux=true;
            }
            else
                if (v[y].dato.GetDNI()==dni)
                    return false;
            ++i;
        }
    }
     if (i>maxcoli){
        maxcoli=i;            
    }

    totalColisiones+=i;

    return encontrado;
};

bool THashCliente::borra(long int clave){
    unsigned x,i=0;
    bool borrado = false;
    while (!borrado) {
        x=fdoble(clave, i);
        //si no esta ocupada por su termino, mira si esta libre para dejar de buscar
        if (v[x].marca==ocupada){
                v[x].marca=disponible; //lo borro y la dejo marcada
                v.clear();
                borrado=true;  
                taml--;             
        }else{
            if (v[x].marca==vacia)
                break;
            else
                ++i;   //No he dado aun con su posicion
        }//No he dado aun con su posicion
    }
    return borrado;
};

bool THashCliente::busca(const std::string& dni, Cliente* &cli){  
    unsigned i=0,x;
    bool esta = false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());
    while (!esta) {
        x=fdoble(clave, i);
        if (v[x].marca==ocupada){                    
            return &(v[x].dato);       
        }else{
            if (v[x].marca==vacia)
                esta=true;
            else
                ++i;   //no estaba en esa posicion y aumenta un aumento
        }          

    }
    //std::vector<Cliente*> vi;
    return 0;   //no encontrado
};

bool THashCliente::EsPrimo(unsigned n) {
    float x = sqrt(n);
    for (int i = 2; i < x; ++i)
        if (n % i == 0)
            return false;
    return true;
}

int THashCliente::PrimoPorDebajo(unsigned x) {
    x = x - 1;
    while (!EsPrimo(x)) {
        --x;
    }
    return x;
}