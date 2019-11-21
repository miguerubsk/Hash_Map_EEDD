/* 
 * File:   THashCliente.h
 * Author: admin
 *
 * Created on 8 de noviembre de 2019, 00:32
 */

#ifndef THASHCLIENTE_H
#define	THASHCLIENTE_H
#include <vector>
#include <iostream>
#include "Cliente.h"
#define limite 20

enum Estado{LIBRE,OCUPADA,DISPONIBLE};

 //clave para dispersion de cadenas 
 inline unsigned long djb2(const unsigned char *str){
        unsigned long hash = 5381;
        int c;
        while (c = *str++)
            hash = ((hash<<5)+hash)+c;
        return hash;
}

class THashCliente {
private:    
    class Entrada {
     public:
        unsigned long clave;
        std::string dni;
        Estado marca;  //0(libre), 1(ocupada), 2(disponible)
        Cliente dato;
        Entrada(): marca(LIBRE), clave(0), dni(""), dato(Cliente()) {}    
        ~Entrada(){};
    };
    
    unsigned long tamaf;
    unsigned long tamal; 
    unsigned long maxCol;
    unsigned long sumaColisiones;
    unsigned long prelativo;
    std::vector<Entrada> tabla;  
    
   //funciones privadas
     
    // Funciones sobre numeros primos
    inline bool esprimo(unsigned n) {
        for (unsigned i = 2; i <= sqrt(n); ++i)
            if (n % i == 0)
                return false;
        return true;
    }

    inline int primo_menor(unsigned numero) {
        int i = numero-1;
        while (!esprimo(i)) {
            --i;
        }
        return i;
    }

    //  la función de dispersión es cuadratica
    inline unsigned hash(unsigned long clave, int i) {
        unsigned long posicionfinal;
                                        // peor FUNCION DE DISPERSION
        posicionfinal= (clave+(i*i)) % tamaf;
        return posicionfinal;
    }
    
  //  la funcion de dispersion es doble
    inline unsigned hash2(unsigned clave, int i) {
        unsigned long posicion,posicionfinal;

        posicion = clave % tamaf;   // mejor FUNCION DE DISPERSION        
        posicionfinal = (posicion + (i* (prelativo-(clave % (prelativo))))) % tamaf;
        return posicionfinal;
    }

    //  la funcion de dispersion es doble
    inline unsigned hash3(unsigned clave, int i) {
        unsigned long posicion,posicionfinal;

        posicion = clave % tamaf;   // mejor FUNCION DE DISPERSION        
        posicionfinal = (posicion + (i* (1+(clave % (prelativo))))) % tamaf;
        return posicionfinal;
    }
public:
    THashCliente(unsigned long tam=1):tamaf(tam), tabla(tamaf,Entrada()),
            tamal(0), maxCol(0), sumaColisiones(0)
    {
        prelativo=primo_menor(tamaf);
    };
           
  
    bool insertar(const std::string& dni, Cliente &cli){
        unsigned i=0,y;
        int p=-1, final;
        bool encontrado = false;
        unsigned long clave=djb2((unsigned char*)dni.c_str());
       
        while (!encontrado && i<limite) {
            y=hash2(clave, i);           
            if (tabla[y].marca==LIBRE ) {
                if (p==-1)
                    final=y;
                else
                    final=p;
                tamal++;
                tabla[final].dni=dni;
                tabla[final].marca=OCUPADA;
                tabla[final].clave=clave;                             
                tabla[final].dato=cli;  //push_back(dato);                                                
                encontrado = true;   //Encontre un sitio libre  
            }else{
                if (tabla[y].marca==DISPONIBLE)
                    p=y;
                else
                    if (tabla[y].dni==dni)
                        return false;  //tb encontrado
                ++i;   //No he dado aun con una posicion libre
            }
        }
         if (i>maxCol){
            maxCol=i;            
        }
        //std::cout << "Intentos " << i << std::endl; 
        sumaColisiones+=i;
        
        return encontrado;
    }
 
    bool borrar(unsigned long clave, const std::string &dni){
        unsigned i=0,y=0;
        bool fin = false;
        while (!fin && i<limite) {
            y=hash2(clave, i);
            if (tabla[y].marca==OCUPADA && tabla[y].dni==dni){              
                  //  cout << std::endl << "Borrado con " << i << " intentos." << std::endl;
                    tabla[y].marca=DISPONIBLE; //lo encontre lo borro y salgo del bucle
                    
                    fin=true;  
                    tamal--;             
            }else{
                if (tabla[y].marca==LIBRE)
                    break;
                else
                    ++i;   //No he dado aun con su posicion
            }//No he dado aun con su posicion
        }
        return fin;
    }
    
    bool buscar(unsigned long clave, const std::string &dni, Cliente* &cli){  
        unsigned i=0,y=0;
        bool enc = false;
        while (!enc && i<limite) {
            y=hash2(clave, i);
            if (tabla[y].marca==OCUPADA && tabla[y].dni==dni){
                  //  cout << std::endl << "Buscado con " << i << " intentos." << std::endl;                    
                cli=&(tabla[y].dato);
                enc=true;
            }else{
                if (tabla[y].marca==LIBRE){
                    i=limite;
                    cli=0;
                }else
                    ++i;   //No he dado aun con su posicion
            }          
                
        }        
        return enc;  //std::vector<Cliente*>();   //no encontrado
    }    
    
    //funciones publicas
    unsigned int numClientes(){
        return tamal;
    }
            
    unsigned long maxColisiones() const {
        return maxCol;
    }        

    float promedioColisiones() const {
        return (float)sumaColisiones/tamal;
    }
    
    float factorCarga(){
        return (float)tamal/tamaf;
    }
    
    ~THashCliente(){}
    
    void redispersar (unsigned long tam){
    //unsigned int tam= tabla.size()*2;
    vector<Entrada> aux(tam,Entrada());
    tamaf=tam;
    maxCol=0;
    sumaColisiones=0;
    prelativo=primo_menor(tamaf);
    for (int i=0; i<tabla.size(); i++){
       
        unsigned intento=0,y;
        bool encontrado = false;
        if (tabla[i].marca==OCUPADA){           
            //unsigned long clave=djb2((unsigned char*)tabla[i].dni.c_str());
            while (!encontrado && intento<limite) {
                y=hash2(clave, intento);           
                if (aux[y].marca==LIBRE || aux[y].marca==DISPONIBLE) {                 
                    aux[y].dni=tabla[i].dni;
                    aux[y].marca=OCUPADA;
                    aux[y].clave=tabla[i].clave;                             
                    aux[y].dato=tabla[i].dato;  //push_back(dato);                                                
                    encontrado = true;   //Encontre un sitio libre  
                }else
                    
                    ++intento;   //No he dado aun con una posicion libre
            }
             if (intento>maxCol){
                maxCol=intento;            
            }
            //std::cout << "Intentos " << i << std::endl; 
            sumaColisiones+=intento;
            if (!encontrado)
                cout << " Cliente no insertado: " << tabla[i].dni << endl  ; 
        } 
    }
    tabla=aux;       
}

    void setMaxCol(unsigned long maxCol) {
        this->maxCol = maxCol;
    }
    
  
};

#endif	/* THASHCLIENTE_H */

