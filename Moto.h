/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Moto.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 24, 2019, 12:07 PM
 */

#ifndef MOTO_H
#define MOTO_H

#include <string>
#include <stdexcept>
#include "UTM.h"
#include <ctime>
#include <climits>
//#include "Cliente.h"
class Cliente;

enum Status {
    BLOQUEADA, ACTIVA, SINBATERIA, ROTA
};

class Moto {
public:
    Moto();
    Moto(const Moto& orig);
    Moto(std::string _id, double _latitud, double _longitud, int _estado, float _porcentajeBateria = UINT_MAX);
    UTM &getPosicion();
    std::string getId() const;
    Status &getStatus();
    virtual ~Moto();
    Moto& operator=(const Moto &orig);
    bool operator<(const Moto &orig);
    bool operator==(const Moto &orig);
    bool seActiva(Cliente *cli);
    void seDesactiva();
    std::string GetId() const;
    void setEstado(Status estado);
    Status getEstado() const;
    void setUsadoPor(Cliente* usadoPor);
    Cliente* getUsadoPor() const;
    void setPosicion(UTM posicion);
    void setId(std::string id);
    void setPorcentajeBateria(float porcentajeBateria);
    float getPorcentajeBateria() const;


private:
    float porcentajeBateria;
    std::string id;
    UTM posicion;
    Cliente *usadoPor;
    Status estado;
};

#endif /* MOTO_H */

