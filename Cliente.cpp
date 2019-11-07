/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 27, 2019, 11:14 PM
 */

#include "Cliente.h"
/**
     * @brief funcion para desbloquear la moto que esta asociada a cliente
     * @param A es la moto en cuestion que queremos desbloquear
**/
void Cliente::desbloquearMoto(Moto *m) {
    acceso->desbloqueaMoto(m, this);
    Fecha fecha;
    UTM final;
    acceso->setIdUltimo(acceso->getIdUltimo()+1);
    Itinerario itinerario(acceso->getIdUltimo(), m->getPosicion(), final, fecha, 0, m);
    rutas.push_back(itinerario);
}

void Cliente::addItinerario(int id, Fecha fecha,int minutos, Moto *moto, UTM inicio, UTM fin){
    //TODO
}

void Cliente::terminarTrayecto() {
    auto iterador = rutas.begin();
    Fecha fechafin;
    srand(time(NULL));
    rutas.back().SetMinutos((fechafin.verHora()*60 + fechafin.verMin()) - (rutas.back().GetFecha().verHora()*60 + rutas.back().GetFecha().verMin()));
    rutas.back().SetFin(posicion);
    rutas.back().GetVehiculos()->setPosicion(posicion);
    rutas.back().GetVehiculos()->seDesactiva();
}
/**
     * @brief funcion para buscar la moto mas cercana al cliente en cuestion
     * @return devuelve la moto la cual es la mas cercana del cliente(this)
**/
Moto * Cliente::buscarMotoCercana() {
    Moto* m = acceso->LocalizaMotoCercana(posicion);
    return m;
}
/**
     * @brief funcion para devolver la lista de itinerarios
     * @return devuelve la lista doblemente enlazada de los itinerarios del cliente
**/
list<Itinerario>& Cliente::getItinerario() {
    return rutas;
}
//OPERADOR << PARA CLIENTE
/**
     * @brief funcion para el operador << de la clase Cliente
     * @param A ostream &os
     * @param B const Cliente & obj  
     * @return devuelve el contenido de las variables de cliente
**/
ostream& operator<<(ostream & os, const Cliente & obj) {
    return os << "DNI: " << obj.GetDNI() << " | " << "Nombre: " << obj.GetNOMBRE() << " | " << "Direccion: " << obj.GetDIRECCION() << " Id del ultimo " << obj.acceso->getIdUltimo() << " | " << "\n";
}


std::string Cliente::GuardaCliente() {
    std::string lineadatos = dni + ";" + pass + ";" + nombre 
            + ";" + direccion + ";" + std::to_string(posicion.GetLatitud()) + ";" + std::to_string(posicion.GetLongitud()) 
            + ";" + std::to_string(rutas.size());
    return lineadatos;
}