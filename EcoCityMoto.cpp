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
EcoCityMoto::EcoCityMoto() : idUltimo(0), clientes(), motos() {
    cargarMotos("motos.txt");
    cargarClientes("prueba.sav");
    //cargarClientes("clientes_v2.csv");
}

/**
 * @brief funcion del contructor copia de EcoCityMoto
 **/
EcoCityMoto::EcoCityMoto(const EcoCityMoto& orig) : clientes(orig.clientes), idUltimo(orig.idUltimo), motos(orig.motos) {
}

/**
 * @brief destructor correspondiente de EcoCityMoto
 **/
EcoCityMoto::~EcoCityMoto() {
    guardaClientesItinerarios("prueba.sav");
}

/**
 * @brief funcion para lozalizar la moto mas cercana utilizando la ubicacion proporcionada
 * @param A es la ubicacion para poder utilizarla a la hora de buscar la moto
 * @return devuelve la moto que ha encontrado
 **/
Moto* EcoCityMoto::LocalizaMotoCercana(UTM &ubicacion) {
    Moto *moto;

    double maxDistancia = 9999999999, distancia;
    for (int i = 0; i < motos.size() - 1; i++) {
        if (motos[i].getStatus() == BLOQUEADA) {
            distancia = ubicacion.distancia(motos[i].getPosicion());
            if (distancia < maxDistancia) {
                maxDistancia = distancia;
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
void EcoCityMoto::desbloqueaMoto(Moto *moto, Cliente *cli) {
    moto->seActiva(cli);
}

/**
 * @brief funcion para cargar los clientes en el avl de la clase
 * @param A es el nombre del fichero
 **/
void EcoCityMoto::cargarClientes(std::string filename) {
    ifstream fe; //Flujo de entrada
    string linea; //Cada linea tiene un clienete
    int total = 1; //Contador de lineas o clientes

    //Variables auxiliares para almacenar los valores leidos
    string dni, nombre, pass, direccion, latitud, longitud, nItinerariosAux, id, dia, mes, anio, hora, minutosfecha, minutositinerario, moto;
    double maxLon = -9999999, maxLat = -9999999, minLon = 9999999, minLat = 9999999;
    int nItinerarios, idUltimoAux = 0;
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
                    getline(ss, nItinerariosAux, ';'); //Leemos el número de itinerarios

                    dlat = stod(latitud);
                    dlon = stod(longitud);
                    //calculamos Latitud y longitud max y min
                    if (dlon > maxLon)
                        maxLon = dlon;
                    if (dlon < minLon)
                        minLon = dlon;

                    if (dlat > maxLat)
                        maxLat = dlat;
                    if (dlat < minLat)
                        minLat = dlat;

                    //con todos los atributos leidos, se crea el cliente
                    //                cout<<dni<<endl;
                    UTM min(minLat, maxLon), max(maxLat, maxLon);
                    Cliente client(dni, pass, nombre, direccion, minLat, maxLon, this);

                    //Comrueba si hay itinerarios
                    if (nItinerariosAux == "") {
                        //Si no hay crea algunos aleatorios
                        int num = rand() % 10 + 1;
                        client.crearItinerarios(num, idUltimoAux, min, max);
                        idUltimoAux += num;
                    } else {
                        //Si hay los lee
                        nItinerarios = stoi(nItinerariosAux);
                        while (nItinerarios != 0) {
                            getline(fe, linea); //Toma una linea del fichero
                            stringstream ss;
                            nItinerarios--;
                            ss << linea;
                            //Leemos el id
                            getline(ss, id, ';'); //El carácter ; se lee y se elimina de ss
                            //Leemos el dia de la fecha
                            getline(ss, dia, ';'); //El caráter ; se lee y se elimina de ss
                            //Leemos el mes de la fecha
                            getline(ss, mes, ';'); //El caráter ; se lee y se elimina de ss
                            //Leemos el año de la fecha
                            getline(ss, anio, ';'); //El caráter ; se lee y se elimina de ss
                            //Leemos la hora de la fecha
                            getline(ss, hora, ';'); //El caráter ; se lee y se elimina de ss
                            //Leemos los minutos de la fecha
                            getline(ss, minutosfecha, ';'); //El caráter ; se lee y se elimina de ss

                            //Creamos la fecha
                            int diaaux = stoi(dia), mesaux = stoi(mes), anioaux = stoi(anio), horaaux = stoi(hora), minutosaux = stoi(minutosfecha);
                            Fecha fechaAux(diaaux, mesaux, anioaux, horaaux, minutosaux);

                            //Leemos los minutos del itinerario
                            getline(ss, minutositinerario, ';'); //El caráter ; se lee y se elimina de ss

                            //Leemos la latitud y longitud de inicio
                            getline(ss, latitud, ';'); //El caráter ; se lee y se elimina de ss
                            getline(ss, longitud, ';'); //El caráter ; se lee y se elimina de ss

                            dlat = stod(latitud);
                            dlon = stod(longitud);

                            UTM inicio(dlat, dlon);

                            //Leemos la latitud y longitud de fin
                            getline(ss, latitud, ';'); //El caráter ; se lee y se elimina de ss
                            getline(ss, longitud, ';'); //El caráter ; se lee y se elimina de ss

                            dlat = stod(latitud);
                            dlon = stod(longitud);

                            UTM fin(dlat, dlon);
                            //Leemos la matricula de la moto
                            getline(ss, moto, ';'); //El caráter ; se lee y se elimina de ss

                            //Buscamos la moto
                            Moto *motoaux = 0;
                            for (int i = 0; i < motos.size(); i++) {
                                if (motos[i].getId() == moto) {
                                    motoaux = &motos[i];
                                    break;
                                }
                            }
                            //if(id=="22939")
                            //cout<<id;
                            client.addItinerario(stoi(id), fechaAux, stoi(minutositinerario), motoaux, inicio, fin);
                        }
                    }
                    std::pair <std::string, Cliente> par(client.GetDNI(), client);
                    clientes.insert(par);
                    //                if (total % 100 == 0) {
                    //                    cout << "Leido cliente " << total << "\n  ";
                    //                }
                }
            }
            //   getline(fe, linea);
        }
        cout << "Total de clientes en el fichero: " << clientes.size() << endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        cerr << "No se puede abrir el fichero" << endl;
    }
}

/**
 * @brief funcion para cargar las motos en vector de EscoCityMotos
 * @param A es el nombre del fichero
 **/
void EcoCityMoto::cargarMotos(std::string filename) {
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
                //                if (total % 100 == 0) {
                //                    std::cout << "Leida moto " << total << "\n  ";
                //                }
            }
            getline(fe, linea); //Toma una linea del fichero
        }

        std::cout << "Total de motos en el fichero: " << motos.size() << std::endl;
        fe.close(); //Cerramos el flujo de entrada
    } else {
        std::cerr << "No se puede abrir el fichero" << std::endl;
    }
}

Cliente* EcoCityMoto::buscarCliente(std::string dni) {
    Cliente c, *aux;
    c.SetDni(dni);
    std::map<std::string, Cliente>::iterator i = clientes.find(dni);
    if (i != clientes.end()) {
        return &(*i).second;
    }
    throw std::invalid_argument("No se ha encontrado al cliente");
}

/**
 * @brief funcion para añadir un cliente nuevo o no al mapa
 * @param A es el cliente que queremos añadir
 * @return devuelve verdadero o falso segun si el cliente existe ya o no
 **/
bool EcoCityMoto::nuevoCliente(Cliente& c) {
    std::map<std::string, Cliente>::iterator i = clientes.find(c.GetDNI());
    if (i != clientes.end()) {
        throw std::invalid_argument("El cliente ya existe");
    }
    clientes[c.GetDNI()] = c;
    return true;
}

/**
 * @brief funcion para eliminar un cliente nuevo o no al mapa
 * @param A es el cliente que queremos eliminar
 * @return devuelve verdadero o falso segun si el cliente existe ya o no
 **/
bool EcoCityMoto::eliminarCliente(Cliente& c) {
    std::map<std::string, Cliente>::iterator i = clientes.find(c.GetDNI());
    if (i != clientes.end()) {
        clientes.erase(i);
        return true;
    }
    throw std::invalid_argument("El cliente no existe");
}

/**
 * @brief funcion para devolver el vector de motos
 * @return devuelve un puntero al vector de motos
 **/
std::vector<Moto>* EcoCityMoto::GetMotos() {
    return &motos;
}

/**
 * @brief funcion para guardar los cliente con su itinerario
 * @param A es el nombre del fichero del que queremos leer
 **/
void EcoCityMoto::guardaClientesItinerarios(std::string fileName) {
    ofstream fs; //Flujo de salida


    //Variables auxiliares para almacenar los valores leídos
    int total = 0;
    //Asociamos el flujo al fichero 
    fs.open(fileName, ofstream::trunc);

    if (fs.good()) {
        map<string, Cliente>::iterator it = clientes.begin();
        fs << "NIF;clave;nomape;dirección;latitud;longitud;nIti" << endl;
        while (it != clientes.end()) {
            total++;
            //            if(total%100==0)
            //                cout<<"Guardado cliente "<<total<<endl;
            Cliente cli = it->second;

            // if (cli.GetDni()=="52525252X")
            //   cout << ",";
            list<Itinerario> r = cli.getItinerario();
            list<Itinerario>::iterator it2 = r.begin();
            fs << cli.GetDNI() << ";" << cli.getPass() << ";" << cli.GetNOMBRE() << ";" <<
                    cli.GetDIRECCION() << ";" << cli.getPosicion().GetLatitud() << ";" <<
                    cli.getPosicion().GetLongitud() << ";" << cli.getItinerario().size() << endl;
            while (it2 != r.end()) {
                fs << it2->GetId() << ";" //Se escribe el id del 
                        //Se escribe la fecha
                        << it2->GetFecha().verDia() << ";" //Se escribe el dia
                        << it2->GetFecha().verMes() << ";" //se escribe el mes
                        << it2->GetFecha().verAnio() << ";" //Se escribe el año
                        << it2->GetFecha().verHora() << ";" //se escribe la hora
                        << it2->GetFecha().verMin() << ";" //Se escriben los minutos
                        //Se escribe la duracion del itinerario
                        << it2->GetMinutos() << ";" //Se escriben los minutos
                        //Se escribe la posicion de inicio
                        << it2->GetInicio().GetLatitud() << ";" //Se escribe la latitud
                        << it2->GetInicio().GetLongitud() << ";" //Se escribe la longitud
                        //Se escribe la posicion de fin
                        << it2->GetFin().GetLatitud() << ";" //Se escribe la latitud
                        << it2->GetFin().GetLongitud() << ";" //Se escribe la longitu
                        //Se escribe la moto
                        << it2->GetVehiculos()->GetId() << endl; //Se escribe la matrícula
                it2++;
            }
            it++;
        }

        fs.close(); //Cerramos el flujo de entrada        
    } else {
        std::cerr << "No se puede crear el fichero" << endl;
    }
}

/**
 * @brief funcion para devolver el mapa de clientes
 * @return devuelve el mapa de clientes
 **/
std::map<std::string, Cliente>& EcoCityMoto::getCliente() {
    return clientes;
}

/**
 * @brief funciom get para el idUltimo
 * @return devuelve el valor de idUltimo
 **/
unsigned int EcoCityMoto::getIdUltimo() const {
    return idUltimo;
}

/**
 * @brief funcion set para el idUltimo
 * @param A es el valor que queremos modificar al idUltimo
 **/
void EcoCityMoto::setIdUltimo(unsigned int idUltimo) {
    this->idUltimo = idUltimo;
}

/**
 * @brief funcion para agrupar las motos sin bateria
 * @return devuelve un vector de las motos con una bateria menos del 15%
 **/
std::vector<Moto> EcoCityMoto::localizaMotosSinBateria() {
    std::vector<Moto> aux;
    for (int i = 0; i < motos.size(); i++) {
        if (motos[i].getPorcentajeBateria() < 15) {
            aux.push_back(motos[i]);
        }
    }
    return aux;
}

/**
 * @brief funcion para tener una moto aleatoria dentro de las existentes
 * @return devuelve la moto que busca aleatoriamente
 **/
Moto* EcoCityMoto::GetMotoRand() {
    int aux = rand() % 1000;
    return &(motos[aux]);
}