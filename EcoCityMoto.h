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
    void cargarClientes(std::string filename);
    void cargarMotos(std::string filename);
    Moto* LocalizaMotoCercana(UTM &ubicacion);
    void desbloqueaMoto(Moto *moto, Cliente *cli);
    unsigned int getIdUltimo() const {
        return idUltimo;
    }
    std::map<std::string, Cliente>& getCliente() {
        return clientes;
    }
    void setIdUltimo(unsigned int idUltimo) {
        this->idUltimo = idUltimo;
    }

    Cliente* buscarCliente(std::string dni); 



private:
    unsigned int idUltimo;
    std::vector<Moto> motos;
    std::map<std::string, Cliente> clientes;
    

};

#endif /* ECOCITYMOTO_H */

