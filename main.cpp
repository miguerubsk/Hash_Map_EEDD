/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 19 de septiembre de 2019, 13:07
 */
#include <cstdlib>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <ctime>
#include "Cliente.h"
#include "EcoCityMoto.h"
#include "Moto.h"


using namespace std;

double calculardistaciamaslejana(vector<Cliente> v) {
    double distancia, maxDistancia = 0;
    for (int i = 0; i < v.size() - 1; i++) {
        for (int j = i + 1; j < v.size(); j++) {
            distancia = v[i].distancia(v[j]);

            if (distancia > maxDistancia)
                maxDistancia = distancia;
        }
    }
    return maxDistancia;
}

void MaxMinLatLon(vector<Cliente> v, double &maxLon, double &maxLat, double &minLon, double &minLat) {
    maxLon = -9999999, maxLat = -9999999, minLon = 9999999, minLat = 9999999;
    for (int i = 0; i < v.size(); i++) {
        double x = v[i].GetUTM().GetLongitud();
        if (x > maxLon)
            maxLon = x;
        else
            if (x < minLon)
            minLon = x;
        x = v[i].GetUTM().GetLatitud();
        if (x > maxLat)
            maxLat = x;
        else
            if (x < minLat)
            minLat = x;

    }
}

int main(int argc, char** argv) {
    try {
        EcoCityMoto prueba;
        Cliente *buscado;
        Cliente ejemplo("26529258T", "aguila", "Fernando", "Jaen", 37.3, 38.4, &prueba);
        if (prueba.nuevoCliente(ejemplo)) {
            cout << "-----SE HA AÑADIO EL CLIENTE-----" << endl;
            cout << "DNI: " << ejemplo.GetDNI() << endl;
            cout << "Nombre: " << ejemplo.GetNOMBRE() << endl;
            cout << "Latitud: " << ejemplo.GetUTM().GetLatitud() << endl;
            cout << "Longitud: " << ejemplo.GetUTM().GetLongitud() << endl;
            cout << "---------------------------------" << endl;
        } else {
            cout << "-----NO SE HA AÑADIO EL CLIENTE-----" << endl;
        }
        //cout << "Nº de clientes: " << prueba.GetClientesTHash().totalClientes() << endl;

        std::vector<Moto> probar;
        probar = prueba.localizaMotosSinBateria();
        cout << "Hay " << probar.size() << " motos sin bateria." << endl;
        
        buscado = prueba.buscarCliente("26529258T");
        if(buscado->GetDNI()=="26529258T"){
            cout<<"ENCONTRADO: "<<buscado->GetDNI()<<endl;
        }else{
            cout<<"NO ESTA EL CLIENTE: "<<buscado->GetDNI()<<endl;
        }
            ejemplo.desbloquearMoto(ejemplo.buscarMotoCercana());
        cout << "PORCENTAJE inicial: " << ejemplo.getItinerario().back().GetVehiculos()->getPorcentajeBateria() << endl;
        cout << "ESTADO inicial: " << ejemplo.getItinerario().back().GetVehiculos()->getEstado() << endl;
        ejemplo.terminarTrayecto();
        cout << "PORCENTAJE final: " << ejemplo.getItinerario().back().GetVehiculos()->getPorcentajeBateria() << endl;
        cout << "ESTADO final: " << ejemplo.getItinerario().back().GetVehiculos()->getEstado() << endl;
        cout << "-----SIGNIFICADO DEL ESTADO-----" << endl;
        cout << "0 = BLOQUEADA" << endl;
        cout << "1 = ACTIVA" << endl;
        cout << "2 = SINBATERIA" << endl;
        cout << "3 = ROTA" << endl;
        cout << "--------------------------------" << endl;
        cout << "Nº de clientes antes de eliminar: " << prueba.getClientes().totalClientes() << endl;
        if (prueba.eliminarCliente(ejemplo)) {
            cout << "El cliente " << ejemplo.GetNOMBRE() << " ha sido eliminado." << endl;
        } else {
            cout << "El cliente " <<ejemplo.GetNOMBRE() << " no ha sido eliminado." << endl;
        }
        cout << "Nº de clientes despues de eliminar: " << prueba.getClientes().totalClientes() << endl;

    } catch (std::string &e) {
        cout << e << endl;
    } catch (std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}