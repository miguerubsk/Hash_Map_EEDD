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

THashCliente::THashCliente(int tam=0):v(tam, Entrada()) {
    tamf=tam;
    primorelativo=PrimoPorDebajo(tam);
    taml=0;
    maxcoli=0;
    totalColisiones=0;
    Cliente();
}



THashCliente::~THashCliente() {
}

vector<string> THashCliente::iterar(){
    vector<string> aux;
    for (int i=0; i < v.size(); ++i){
        if (v[i].marca == ocupada){
            aux.push_back(v[i].dato.GetDNI());
        }
    }
    return aux;
}

bool THashCliente::inserta(const std::string& dni, Cliente &cli){
    unsigned i=0,y;
    int p=-1, final;
    bool encontrado = false, aux=false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());

    while (!encontrado) {
        y=hash(clave, i);           
        if (v[y].marca==vacia ) {
            if (p==-1)
                final=y;
            else
                final=p;
            taml++;
            v[final].dni=dni;
            v[final].marca=ocupada;
            v[final].clave=clave;
            v[final].dato=cli;
            encontrado = true;
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
        x=hash2(clave, i);
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

bool THashCliente::borracliente(string& dni) {
    int intento = 0;
    unsigned long int clave;
    do {
        clave = hash(djb2((unsigned char*) dni.c_str()), intento);
        if (v[clave].marca == vacia) {
            return false;
        } else {
            if (v[clave].marca == ocupada && v[clave].dato.GetDNI() == dni) {
                v[clave].marca = disponible;
                taml--;
                return true;
            }
        }
        intento++;

    } while (v[clave].marca != vacia);
    return false;
}


bool THashCliente::busca(const std::string& dni, Cliente* &cli){  
    unsigned i=0,x;
    bool esta = false;
    unsigned long clave=djb2((unsigned char*)dni.c_str());
    while (!esta) {
        x=hash2(clave, i);
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

void THashCliente::redispersar (unsigned long tam){
    //unsigned int tam= tabla.size()*2;
    vector<Entrada> aux(tam,Entrada());
    tamf=tam;
    totalColisiones=0;
    primorelativo=PrimoPorDebajo(tamf);
    for (int i=0; i<v.size(); i++){       
        unsigned intento=0,y;
        bool encontrado = false;
        if (v[i].marca==ocupada){           
            //unsigned long clave=djb2((unsigned char*)tabla[i].dni.c_str());
            while (!encontrado) {
                y=hash2(v[i].clave, intento);           
                if (aux[y].marca==vacia || aux[y].marca==disponible) {                 
                    aux[y].dni=v[i].dni;
                    aux[y].marca=ocupada;
                    aux[y].clave=v[i].clave;                             
                    aux[y].dato=v[i].dato;  //push_back(dato);                                                
                    encontrado = true;   //Encontre un sitio libre  
                }else
                    
                    ++intento;   //No he dado aun con una posicion libre
            }
            //std::cout << "Intentos " << i << std::endl; 
            totalColisiones+=intento;
            if (!encontrado)
                cout << " Cliente no insertado: " << v[i].dni << endl  ; 
        } 
    }
    v=aux;       
}