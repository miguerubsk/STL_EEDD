/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ListaDEnlazada.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on 4 de octubre de 2019, 9:44
 */

#ifndef LISTADENLAZADA_H
#define LISTADENLAZADA_H

#include <stdexcept>

template <class T>
class Nodo {
private:
    //Creamos el dato tipo T
    T dato;
    //Creamos el nodo siguiente
    Nodo<T>* siguiente;
    //Creamos el nodo anterior
    Nodo<T>* anterior;
    //En la practica ponia el uso de la clase friend pero la hemos comentado porque da mil errores con los templates.
public:
    //Creamos los constructores por defecto, parametros y copia.
    Nodo();

    Nodo(T &aDato, Nodo *aAnt, Nodo *aSig) : dato(aDato), anterior(aAnt), siguiente(aSig) {
    }
    Nodo(const Nodo<T>& orig);
    //Creamos los metodos gets y set

    T& getDato() {
        return dato;
    }

    void setDato(T& mdato) {
        dato = mdato;
    }

    Nodo<T>* getSiguiente() {
        return siguiente;
    }

    Nodo<T>* getAnterior() {
        return anterior;
    }

    void setSiguiente(Nodo<T>* sig) {
        siguiente = sig;
    }

    void setAnterior(Nodo<T>* ant) {
        anterior = ant;
    }
    //Creamos el destructor.

    ~Nodo() {
        siguiente = 0;
    }
};

template <class T>
Nodo<T>::Nodo() : dato() {
    siguiente = 0;
    anterior = 0;
}

//Implementamos el constructor copia

template <class T>
Nodo<T>::Nodo(const Nodo<T>& orig) : dato(orig.dato) {
    siguiente = orig.siguiente;
    anterior = orig.anterior;
}

template <class T>
class Iterador {
private:
    //Creamos un nodo.
    Nodo<T>* nodo;
    //En la practica ponia el uso de la clase friend pero la hemos comentado porque da mil errores con los templates.
    //friend class ListaEnlazada;

public:

    //Creamos los metodos constructores de la clase Iterador por defecto, por parametros y por copia
    Iterador();
    Iterador(const Iterador<T>& orig);

    Iterador(Nodo<T> *mNodo) : nodo(mNodo) {
    }
    //Creamos los metodos para saber si hay un nodo  siguiente y anterior

    bool haySiguiente() {
        return nodo->getSiguiente() != 0;
    }

    bool hayAnterior() {
        return nodo->getAnterior() != 0;
    }
    //Creamos los metodos para pasar de un nodo a otro uno para el anterior y otro para el siguiente.

    void siguiente() {
        nodo = nodo->getSiguiente();
    }

    void anterior() {
        nodo = nodo->getAnterior();
    }
    //Creamos el metodo para obtener el dato;

    T& getDato() {
        return nodo->getDato();
    }

    T *getdatoaux() {
        return &nodo->getDato();
    }
    
    //Creamos el metodo para obtener el nodo.

    Nodo<T>* getNodo() {
        return nodo;
    }
    //Creamos un metodo para saber si un nodo existe o no.
    bool existe();
    //Creamos el destructor de la clase Iterador.
    ~Iterador();
    //Creamos los operadores == y !=
    bool operator==(Iterador<T>& i);
    bool operator!=(Iterador<T>& i);

    bool fin() {
        return nodo == 0;
    }


};

//Implementamos el constructor por defecto de la clase Iterador.

template <class T>
Iterador<T>::Iterador() {
    nodo = 0;
}

//Implementamos el constructor copia de la clase Iterador.

template <class T>
Iterador<T>::Iterador(const Iterador<T>& orig) {
    nodo = orig.nodo;
}

//Implementamos el metodo de si existe un nodo o no.

template <class T>
bool Iterador<T>::existe() {
    return nodo != 0;
}

//Implementamos el destructor de la clase Iterador.

template <class T>
Iterador<T>::~Iterador() {
    nodo = 0;
}

//Implementamos el operador ==

template <class T>
bool Iterador<T>::operator==(Iterador<T>& i) {
    return nodo == i.nodo;
}

//Implementamos el operador !=

template <class T>
bool Iterador<T>::operator!=(Iterador<T>& i) {
    return nodo != i.nodo;
}

template <class T>
class ListaDEnlazada {
private:
    Nodo<T>* cabecera;
    Nodo<T>* cola;
    int numeroelementos;

public:

    ListaDEnlazada() {
        cabecera = cola = 0;
        numeroelementos = 0;
    };

    ListaDEnlazada(Nodo<T>* cabe, Nodo<T>* col) {
        cabecera = cabe;
        cola = col;
    }
    ListaDEnlazada(const ListaDEnlazada &orig);
    //Creamos el operador = de la clase.
    ListaDEnlazada<T> &operator=(const ListaDEnlazada &lista);
    //Creamos los metodos para obtener los iteradores de Inicio y Final.

    Iterador<T> iteradorInicio() {
        return Iterador<T>(cabecera);
    }

    Iterador<T> iteradorFinal() {
        return Iterador<T>(cola);
    }
    //Creamos los metodos de insertar un dato al inicio y al final, y en una posicion dada.
    void insertarInicio(T& mdato);
    void insertarFinal(T& mdato);
    void insertar(Iterador<T>& i, T& mdato);
    //creamos los metodos de borrar los datos al inicio y al final, y en una posiciï¿½n dada.
    void borrarInicio();
    void borrarFinal();
    void borrar(Iterador<T> &i);
    ~ListaDEnlazada();

    T &inicio() {
        return cabecera->getDato();
    }

    T & final() {
        return cola->getDato();
    }
    void setNumeroelementos(int numeroelementos);
    int getNumeroelementos() const;
    ListaDEnlazada<T> &UnirListas(ListaDEnlazada<T> &l1, ListaDEnlazada<T> &l2);
    ListaDEnlazada<T>& Concatena(ListaDEnlazada<T> &l);
};

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::operator=(const ListaDEnlazada& lista) {
        while (this->cabecera != 0) {
            this->borrarFinal();
        }
        
        Nodo<T> *aux = lista.cabecera;

        while (aux != 0) {
            this->insertarFinal(aux->getDato());
            aux = aux->getSiguiente();
        }
        
        return *this;
}

template <class T>
void ListaDEnlazada<T>::setNumeroelementos(int numeroelementos) {
    this->numeroelementos = numeroelementos;
}

template <class T>
int ListaDEnlazada<T>::getNumeroelementos() const {
    return numeroelementos;
}

template <class T>
void ListaDEnlazada<T>::insertarInicio(T& mdato) {
    Nodo<T> *nodo;
    nodo = new Nodo<T>(mdato, 0, cabecera);
    //si no hay ningun elememto, la lista esta vacia
    if (cola == 0) {
        cola = nodo;
    }

    if (cabecera != 0) {
        cabecera->setAnterior(nodo);
    }
    cabecera = nodo;

    numeroelementos++;
}

template <class T>
ListaDEnlazada<T>::ListaDEnlazada(const ListaDEnlazada &orig) {
    Nodo<T> *p;
    cabecera = 0;
    cola = 0;
    numeroelementos = 0;
    p = orig.cabecera;

    while (p != 0) {
        insertarFinal(p->getDato()); // .leer(i++));
        p = p->getSiguiente();
    }
}

template <class T>
void ListaDEnlazada<T>::insertarFinal(T& mdato) {

    Nodo<T>* nodo = new Nodo<T>(mdato, cola, 0);
    //si no hay ningun elememto, la lista esta vacia
    if (cola != 0)
        cola->setSiguiente(nodo);
    if (cabecera == 0) {
        cabecera = nodo;

    }
    //nodo->setAnterior(cola);
    cola = nodo;
    numeroelementos++;
}

template <class T>
void ListaDEnlazada<T>::insertar(Iterador<T>& i, T& mdato) {
    //Comprobamos que el iterador este apuntando a algun elemento
    if (!i.existe())throw std::out_of_range("Fuera de rango");

    //Si el iterador apunta al mismo nodo que la cabecera, usamos el metodo insertarInicio().
    if (i.getNodo() == cabecera) {
        insertarInicio(mdato);
    } else {
        //Si el iterador apunta al mismo nodo que la cola, usamos el metodo insertarFinal()
        if (i.getNodo() == cola) insertarFinal(mdato);
        else {
            //Si el iterador apunta a una posicion entre la cabecera y la cola, debemos insertarlo en la posicion .
            Nodo<T>* nodo = new Nodo<T>(mdato, i->anterior(), i);
            i.getNodo()->setSiguiente(nodo);
            numeroelementos++;
        }
    }
}

template <class T>
void ListaDEnlazada<T>::borrarInicio() {
    //Si existen elementos entramos si no lanzamos la excepcion.
    if (!cabecera) throw std::out_of_range("Fuera de rango");
    //Si solo hay un elemento en la lista, la cola y la cabecera seran iguales, al borrarlas las dos quedaran a 0
    if (cabecera == cola) {

        delete cabecera;
        cabecera = cola = 0;
        numeroelementos--;
    } else {
        //Si hay mas de un elemento en la lista, la cola y la cabecera seran distintas, entonces borraremos al inicio la cabecera
        //y pasaremos al siguiente nodo y se eliminara el que apunte a la cabecera en ese momento.

        Nodo<T>* nodo = cabecera;
        cabecera = nodo->getSiguiente();
        delete nodo;
        numeroelementos--;
    }
}

template <class T>
void ListaDEnlazada<T>::borrarFinal() {
    //Si existen elementos entramos si no lanzamos la excepcion.
    if (!cabecera) throw std::out_of_range("Fuera de rango");
    //Si solo hay un elemento en la lista, la cola y la cabecera seran iguales, al borrarlas las dos quedaran a 0
    if (cabecera == cola) {

        delete cabecera;
        cabecera = cola = 0;
        numeroelementos--;
    } else {
        //Si hay mas de un elemento en la lista, la cola y la cabecera seran distintas, entonces borraremos al inicio la cola
        //y pasaremos al siguiente nodo y se eliminara el que apunte a la cola en ese momento.

        Nodo<T>* nodo = cola;
        cola->setSiguiente(0);
        delete nodo;
        numeroelementos--;
    }
}

template <class T>
void ListaDEnlazada<T>::borrar(Iterador<T>& i) {
    //    //Comprobamos que el iterador exista y si no existe lanzamos la excepcion.
    if (!i.existe()) throw std::out_of_range("Fuera de rango");
    //Si el iterador es igual a la cabecera usamos la funcion borrarInicio()
    if (i.getNodo() == cabecera) borrarInicio();
    else {
        //Si el iterador es igual a la cola usamos la funcion borrarFinal()
        if (i.getNodo() == cola) borrarFinal();
        else {
            i->getNodo()->getAnterior()->setSiguiente(i.getNodo()->getSiguiente());
            i.getNodo()->getSiguiente()->setAnterior(i.getNodo()->getAnterior());
            delete i.getNodo();
            numeroelementos--;
        }
    }
}

template <class T>
ListaDEnlazada<T>::~ListaDEnlazada() {
    while (cabecera != cola) {
        Iterador<T>* it = new Iterador<T>(cabecera);
        cabecera = cabecera->getSiguiente();
        delete it;
    }
    delete cabecera;
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::Concatena(ListaDEnlazada<T> &lista) {
    if (!this->iteradorInicio().haySiguiente() || !lista.iteradorInicio().haySiguiente()) throw std::string("Lista vacia");
    ListaDEnlazada<T> listaauxiliar(*this);
    Iterador<T> auxiliar1 = lista.iteradorInicio();

    for (int x = 0; x < lista.getNumeroelementos(); x++) {
        listaauxiliar.insertarFinal(auxiliar1.getDato());
        auxiliar1.siguiente();

    }
    return listaauxiliar;
}

template <class T>
ListaDEnlazada<T>& ListaDEnlazada<T>::UnirListas(ListaDEnlazada<T> &L1, ListaDEnlazada<T> &L2) {
    if (!L1.iteradorInicio().haySiguiente() || !L2.iteradorInicio().haySiguiente()) throw std::string("Lista vacia");
    Iterador<T> auxiliar = L1.iteradorInicio();
    Iterador<T> auxiliar1 = L2.iteradorInicio();
    for (int i = 0; i < L1.getNumeroelementos(); i++) {
        this->insertarFinal(auxiliar.getDato());
        auxiliar.siguiente();

    }
    for (int x = 0; x < L2.getNumeroelementos(); x++) {
        this->insertarFinal(auxiliar1.getDato());
        auxiliar1.siguiente();

    }
    return *this;
}


#endif /* LISTADENLAZADA_H */

