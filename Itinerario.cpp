/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Itinerario.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 * 
 * Created on 5 de octubre de 2019, 11:33
 */

#include "Itinerario.h"
#include "Moto.h"

Itinerario::Itinerario(int _id, UTM &_inicio, UTM &_fin, Fecha &_fecha, int _minutos, Moto *_moto):
                id(_id), inicio(_inicio), fin(_fin), fecha(_fecha), minutos(_minutos), vehiculos(_moto)
{
}

void Itinerario::SetVehiculos(Moto* vehiculos) {
    this->vehiculos = vehiculos;
}

Moto* Itinerario::GetVehiculos() {
    return vehiculos;
}

Itinerario::Itinerario(const Itinerario& orig):
             id(orig.id), inicio(orig.inicio), 
             fin(orig.fin), fecha(orig.fecha), minutos(orig.minutos), vehiculos(orig.vehiculos)
{
}

Itinerario::~Itinerario() {
}
