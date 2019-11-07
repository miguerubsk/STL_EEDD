/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 23 de septiembre de 2019, 22:30
 */

#ifndef CLIENTE_H
#define CLIENTE_H

#include "Itinerario.h"
#include "EcoCityMoto.h"
#include <list>
#include <iostream>
#include <math.h>
#include <random>
#include <ctime>
#include <stdlib.h>
#include <time.h>

using namespace std;

class EcoCityMoto;

class Cliente {
private:
    string dni;
    string pass;
    string nombre;
    string direccion;
    list<Itinerario> rutas;
    EcoCityMoto *acceso;
    UTM posicion;
    

public:
    
    void addItinerario(int id, Fecha fecha,int minutos, Moto *moto, UTM inicio, UTM fin);
    //Constructor

    Cliente() : dni("0"), pass("0"), nombre("0"), direccion("0"), posicion(0.0, 0.0), rutas() {
    }

    Cliente(string _dni, string _pass, string _nombre, string _direccion, double _latitud, double _longitud, EcoCityMoto *_acceso = 0) :
    dni(_dni), pass(_pass), nombre(_nombre), direccion(_direccion), posicion(_latitud, _longitud), acceso(_acceso) {
    }

    Cliente(const Cliente& orig) : dni(orig.dni), pass(orig.pass), nombre(orig.nombre), direccion(orig.direccion),posicion(orig.posicion), rutas(orig.rutas), acceso(orig.acceso) {
    }
    
    string GetDNI() const {
        return dni;
    }

    string GetNOMBRE() const {
        return nombre;
    }

    string GetDIRECCION() const {
        return direccion;
    }

    UTM GetUTM() const {
        return posicion;
    }

    bool operator==(const Cliente& orig) {
        std::size_t found = this->dni.find(orig.dni);

        if (found != std::string::npos)
            return true;

        return false;
    }

    bool operator<(Cliente& right) const {
        return (dni < right.dni);
    }

    bool operator>(Cliente& right) const {
        return (dni > right.dni);
    }

    void SetDireccion(string direccion) {
        this->direccion = direccion;
    }

    void SetDni(string dni) {
        this->dni = dni;
    }

    void SetNombre(string nombre) {
        this->nombre = nombre;
    }

    void SetPass(string pass) {
        this->pass = pass;
    }

    void SetPosicion(UTM posicion) {
        this->posicion = posicion;
    }

    Cliente& operator=(const Cliente &orig) {
        dni = orig.dni;
        nombre = orig.nombre;
        direccion = orig.direccion;
        pass = orig.pass;
        posicion = orig.posicion;
        rutas = orig.rutas;
        acceso = orig.acceso;
        return *this;
    }

    double distancia(const Cliente &cli) {
        return sqrt(pow((cli.posicion.GetLatitud() - this->posicion.GetLatitud()), 2) + pow((cli.posicion.GetLongitud() - this->posicion.GetLongitud()), 2));
    }

    void crearItinerarios(int num, int IdUltimo, const UTM &min, const UTM &max) {
        double lat;
        double longi;
        for (int i = 0; i < num; i++) {
            //GENERAR COORDENADAS RANDOM
            std::mt19937 rnd(std::time(NULL));
            std::uniform_real_distribution<> latitud(min.GetLatitud(), max.GetLatitud());
            std::uniform_real_distribution<> longitud(min.GetLongitud(), max.GetLongitud());
            UTM inicio(latitud(rnd), longitud(rnd));
            UTM fin(latitud(rnd), longitud(rnd));

            //GENERAR FECHA RANDOM
            Fecha fechaRandom;
            srand(time(NULL) + IdUltimo + i);
            int dia = 1 + rand() % (28 - 1);
            int mes = 1 + rand() % (12 - 1);
            int hora = 0 + rand() % (24 - 0);
            int minutos = 0 + rand() % (60 - 0);
            fechaRandom.asignarDia(dia, mes, 2019);
            fechaRandom.asignarHora(hora, minutos);

            int minutosRandom = 0 + rand() % (120 - 0);
            Itinerario itinerarioAux(++IdUltimo, inicio, fin, fechaRandom, minutosRandom);
            rutas.push_back(itinerarioAux);
        }
    }
    void desbloquearMoto(Moto *m);
    void terminarTrayecto();
    Moto * buscarMotoCercana();
    list<Itinerario>& getItinerario();
    
    friend ostream& operator<<(ostream & os, const Cliente & obj);
    
};

#endif /* CLIENTE_H */