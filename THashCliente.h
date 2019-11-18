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

enum Estado {
    vacia, disponible, ocupada
};

class Entrada {
public:
    long clave;
    Estado marca;
    Cliente dato;

    Entrada(long aClave, Cliente aDato) : clave(aClave), dato(aDato), marca(vacia) {
    }

    ~Entrada() {
    };
};

class THashCliente {
private:
    std::vector<Entrada> v;
    unsigned int tamafisico, ntermrep, nterm, maxcoli, totalcoli, primorelativo;

    inline int PrimoPorDebajo(unsigned x) {
        x = x - 1;
        while (!primo(x)) {
            --x;
        }
        return x;
    }

    inline bool primo(unsigned n) {
        float x = sqrt(n);
        for (int i = 2; i < x; ++i)
            if (n % i == 0)
                return false;
        return true;
    }

    inline unsigned int fcuadratica(unsigned long int clave, int i) {
        unsigned long int y = clave + pow(i, 2);
        return y % tamafisico;
    };

    inline unsigned int fdoble(unsigned long int clave, int i) {
        return ((clave % tamafisico) + (i * (primorelativo - (clave % (primorelativo))))) % tamafisico;
    }
public:
    THashCliente();
    THashCliente(const THashCliente& orig);
    ~THashCliente();
    bool inserta(long int clave, Cliente &p){
        unsigned int i=0,j;
        bool hueco = false;
        
        while (!hueco) { //mientras intente acceder a una casilla que no esta vacia, sigue intentadolo
            j=fdoble(clave, i);           
            if (v[j].marca==vacia || v[j].marca==ocupada ) { //si esta vacia u ocupada por su termino se mete
               ntermrep++;
                if (v[j].marca==vacia){
                    nterm++;
                    v[j].marca=ocupada;
                    v[j].clave=clave;
                }     
               // NO FUNCIONAAAAA
                //v.push_back(&p);                                                
                hueco = true;   //habia un hueco y meto el termino ahi
            }else
                ++i;   //la casilla no esta disponible y se da una colision
        }
         if (i>maxcoli){
            maxcoli=i;            
        }
        totalcoli+=i;
        
        return hueco;
    };
    
    bool borra(long int clave){
        unsigned x,i=0;
        bool borrado = false;
        while (!borrado) {
            x=fdoble(clave, i);
            //si no esta ocupada por su termino, mira si esta libre para dejar de buscar
            if (v[x].marca==ocupada){
                    v[x].marca=disponible; //lo borro y la dejo marcada
                    v.clear();
                    borrado=true;  
                    nterm--;             
            }else{
                if (v[x].marca==vacia)
                    break;
                else
                    ++i;   //No he dado aun con su posicion
            }//No he dado aun con su posicion
        }
        return borrado;
    }

    Cliente* busca(long int clave){  
        unsigned i=0,x;
        bool esta = false;
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
    }    

 
   

    //devuelve el tamaño fisico de la tabla
    unsigned int tamanio(){return tamafisico;}
    
    int unsigned totalClientes(){
       unsigned int x=0;
       x=v.size();
       return x;
    };
    
    int terminos(){return nterm;};
    int maxcolisiones(){return maxcoli;}
    float colisionesMedias(){return (float)totalcoli/nterm;}
    float carga(){return (float)nterm/tamafisico;}
};

#endif /* THASHCLIENTE_H */

