/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   EcoCityMoto.cpp
 * Author: Fernando Jiménez Quesada y Miguel González García
 * 
 * Created on October 24, 2019, 12:07 PM
 */

#include "EcoCityMoto.h"
/**
     * @brief contrusctor por defecto de EcoCityMoto
**/
EcoCityMoto::EcoCityMoto(): idUltimo(0), clientes(), motos() {
    cargarClientes("clientes_v2.csv");
    cargarMotos("motos.txt");
}
/**
     * @brief funcion del contructor copia de EcoCityMoto
**/
EcoCityMoto::EcoCityMoto(const EcoCityMoto& orig): clientes(orig.clientes), idUltimo(orig.idUltimo), motos(orig.motos) {
}
/**
     * @brief destructor correspondiente de EcoCityMoto
**/
EcoCityMoto::~EcoCityMoto() {
}
/**
 * @brief funcion para lozalizar la moto mas cercana utilizando la ubicacion proporcionada
 * @param A es la ubicacion para poder utilizarla a la hora de buscar la moto
 * @return devuelve la moto que ha encontrado
 **/
Moto* EcoCityMoto::LocalizaMotoCercana(UTM &ubicacion){
    Moto *moto;
    
    double maxDistancia = 9999999999, distancia;
    for(int i = 0; i<motos.size()-1; i++){
        if(motos[i].getStatus()==BLOQUEADA){
            distancia=ubicacion.distancia(motos[i].getPosicion());
            if(distancia<maxDistancia){
                maxDistancia=distancia;
                moto = &motos[i];
            }
        }
    }
    
    return moto;
}
/**
 * @brief funcion para desbloquear la moto del cliente en cuestion
 * @param A es la moto que deseas desbloquear
 * @param B es el puntero al cliente responsable de dicha moto
 **/
void EcoCityMoto::desbloqueaMoto(Moto *moto, Cliente *cli){
    moto->seActiva(cli);
}
/**
 * @brief funcion para cargar los clientes en el avl de la clase
 * @param A es el nombre del fichero
 **/
void EcoCityMoto::cargarClientes(std::string filename){
    ifstream fe; //Flujo de entrada
    string linea; //Cada linea tiene un clienete
    int total = 0; //Contador de lineas o clientes

    //Variables auxiliares para almacenar los valores leidos
    string dni, nombre, pass, direccion, latitud, longitud;
    double dlat, dlon;



    //Asociamos el flujo al fichero 
    fe.open(filename);

    if (fe.good()) {
        getline(fe, linea);
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            getline(fe, linea); //Toma una linea del fichero
            stringstream ss; //Stream que trabaja sobre buffer interno         

            if (linea != "") {
                ++total;
            }

            if (total > 1) {
                //Inicializamos el contenido de ss
                ss << linea;

                //Leemos el NIF
                getline(ss, dni, ';'); //El caracter ; se lee y se elimina de ss

                //Leemos el pass
                getline(ss, pass, ';'); //El carater ; se lee y se elimina de ss

                //Leemos el nombre
                getline(ss, nombre, ';'); //El carater ; se lee y se elimina de ss

                //Leemos la direcciÃ³n
                getline(ss, direccion, ';'); //El carater ; se lee y se elimina de ss

                //Leemos la latitud y longitud
                getline(ss, latitud, ';'); //El carater ; se lee y se elimina de ss
                getline(ss, longitud, ';'); //El carater ; se lee y se elimina de ss

                dlat = stod(latitud);
                dlon = stod(longitud);

                //con todos los atributos leidos, se crea el cliente
                //                cout<<dni<<endl;
                Cliente client(dni, pass, nombre, direccion, dlat, dlon, this);
                std::pair <std::string, Cliente> aux(dni, client);
                clientes.insert(aux);
                if (total % 100 == 0) {
                    cout << "Leido cliente " << total << "\n  ";
                }
            }
        }

        cout << "Total de clientes en el fichero: " << total << endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}
/**
 * @brief funcion para cargar las motos en el otro avl de EscoCityMotos
 * @param A es el nombre del fichero
 **/
void EcoCityMoto::cargarMotos(std::string filename){
    std::ifstream fe; //Flujo de entrada
    std::string linea; //Cada linea tiene un clienete
    int total = 0; //Contador de lineas o clientes
    //Variables auxiliares para almacenar los valores leidos
    std::string mat, latitud, longitud, estado;
    double dlat, dlon;
    //Asociamos el flujo al fichero 
    fe.open(filename);

    if (fe.good()) {
        getline(fe, linea); //Toma una linea del fichero
        getline(fe, linea); //Toma una linea del fichero
        //Mientras no se haya llegado al final del fichero
        while (!fe.eof()) {
            
            
            std::stringstream ss; //Stream que trabaja sobre buffer interno         

            if (linea != "") {
                ++total;
            }

            if (total >= 1) {
                //Inicializamos el contenido de ss
                ss << linea;

                //Leemos la matricula
                getline(ss, mat, ';'); //El caracter ; se lee y se elimina de ss

                //Leemos el estado
                getline(ss, estado, ';'); //El carater ; se lee y se elimina de ss

                //Leemos la latitud y longitud
                getline(ss, latitud, ';'); //El carater ; se lee y se elimina de ss
                getline(ss, longitud, ';'); //El carater ; se lee y se elimina de ss

                dlat = stod(latitud);
                dlon = stod(longitud);
                int aux = stoi(estado);

                //con todos los atributos leidos, se crea la moto
                Moto moto(mat, dlat, dlon, aux);
                motos.push_back(moto);
                if (total % 100 == 0) {
                    std::cout << "Leida moto " << total << "\n  ";
                }
            }
            getline(fe, linea); //Toma una linea del fichero
        }

        std::cout << "Total de motos en el fichero: " << total << std::endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

Cliente* EcoCityMoto::buscarCliente(std::string dni) {
    Cliente c, *aux;
    c.SetDni(dni);
    std::map<std::string, Cliente>::iterator i = clientes.find(dni);
    if(i != clientes.end()){
        return &(*i).second;
    }
    throw std::invalid_argument("No se ha encontrado al cliente");
}
