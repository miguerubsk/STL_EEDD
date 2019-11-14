/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EcoCityMoto.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 24, 2019, 12:07 PM
 */

#ifndef ECOCITYMOTO_H
#define ECOCITYMOTO_H

#include "Moto.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "Cliente.h"

class Moto;

class EcoCityMoto {
public:
    EcoCityMoto();
    EcoCityMoto(const EcoCityMoto& orig);
    virtual ~EcoCityMoto();
    Moto* LocalizaMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);
    unsigned int getIdUltimo() const;
    std::map<std::string, Cliente>& getCliente();
    void setIdUltimo(unsigned int idUltimo);
    Cliente* buscarCliente(std::string dni);
    bool nuevoCliente(Cliente &c);
    bool eliminarCliente(Cliente &c);
    std::vector<Moto>* GetMotos();
    std::vector<Moto> localizaMotosSinBateria();
    Moto* GetMotoRand();


private:

    unsigned int idUltimo;
    std::vector<Moto> motos;
    std::map<std::string, Cliente> clientes;

    void cargarClientes(std::string filename);
    void cargarMotos(std::string filename);
    void guardaClientesItinerarios(std::string fileName);
};

#endif /* ECOCITYMOTO_H */

