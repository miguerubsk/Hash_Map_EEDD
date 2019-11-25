/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   THashCliente.h
 * Author: Fernando
 *
 * Created on November 18, 2019, 4:17 PM
 */

#ifndef THASHCLIENTE_H
#define THASHCLIENTE_H

#include "Cliente.h"
#include <vector>
//class Cliente;
enum Estado {
    vacia, disponible, ocupada
};

class Entrada {
public:
    Cliente dato;
    long clave;
    std::string dni;
    Estado marca;

    Entrada(): marca(vacia), clave(0), dni(""), dato(Cliente()) {}
    ~Entrada() {
    };
};

class THashCliente {
private:
    std::vector<Entrada> v;
    unsigned int tamf, taml, maxcoli, totalColisiones, primorelativo;

    int PrimoPorDebajo(unsigned x);

    bool EsPrimo(unsigned n);

    inline unsigned int hash(unsigned long int clave, int i) {
        unsigned long posicionfinal;
        posicionfinal= (clave+(i*i)) % tamf;
        return posicionfinal;
    };

    inline unsigned int hash2(unsigned long int clave, int i) {
        unsigned long posicion,posicionfinal;
        posicion = clave % tamf;
        posicionfinal = (posicion + (i* (primorelativo-(clave % (primorelativo))))) % tamf;
        return posicionfinal;
    }
    
    unsigned hash3(unsigned clave, int i) {
        unsigned long posicion,posicionfinal;

        posicion = clave % tamf;
        posicionfinal = (posicion + (i* (1+(clave % (primorelativo))))) % tamf;
        return posicionfinal;
    }
    
    vector<string> getDNIClientes();
    
unsigned long djb2(const unsigned char *str){
   unsigned long hash = 5381;
   int c;
   while (c = *str++)
       hash = ((hash<<5)+hash)+c;
   return hash;
}
    
public:
    THashCliente(int tam);
    ~THashCliente();
    bool inserta(const std::string& dni, Cliente &cli);
    bool borra(long int clave);
    bool borracliente(string& dni);
    bool busca(const std::string &dni, Cliente* &cli);    

    //devuelve el tamaño fisico de la tabla
    unsigned int tamanio(){return tamf;}
    int unsigned totalClientes(){return taml;}
    int maxcolisiones(){return maxcoli;}
    float colisionesMedias(){return (float)totalColisiones/taml;}
    float carga(){return (float)taml/tamf;}
};

#endif /* THASHCLIENTE_H */

