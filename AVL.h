/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVL.h
 * Author: Fernando Jiménez Quesada y Miguel González García
 *
 * Created on October 22, 2019, 4:13 PM
 */

#ifndef AVL_H
#define AVL_H

#include <iostream>

#include "ListaDEnlazada.h"

template <typename U>
class NodoAVL {
public:
    NodoAVL <U> *izq, *der;
    U dato;
    char bal; // -1, 0 , 1 para un árbol avl

    NodoAVL(U &ele) : izq(0), der(0), bal(0), dato(ele) {
    }
};

template <typename T>
class AVL {
    NodoAVL<T> *raiz;
    unsigned int numEle = 0;
private:
    int inserta(NodoAVL <T>* &c, T &dato);
    void recorreInorden(NodoAVL <T> *p, int nivel);
    NodoAVL <T>* buscaClave(T &ele, NodoAVL<T> *p);
    unsigned int altura_aux(NodoAVL<T> *p, int nivel, unsigned  int &result);
    void rotIzqda(NodoAVL <T>* &p);
    void rotDecha(NodoAVL <T>* &p);
    void borrar(NodoAVL<T>* p);
    void copia(NodoAVL<T>* &q, NodoAVL<T> *p);
public:
    AVL<T>();
    AVL<T>(const AVL<T> & origen);
    virtual ~AVL();
    AVL<T>& operator=(const AVL<T>& orig);
    bool busca(T& dato, T* &result);
    bool buscaIt(T& dato, T* &result);

    void recorreInorden() {
        recorreInorden(raiz, 0);
    }

    bool inserta(T &dato) {
        numEle++;
        return inserta(raiz, dato);
    }
    unsigned int numElementos();
    unsigned int altura();
};

/**
 * @brief funcion del contructor copia del avl
 * @param A es el nodo del arbol inicial que queremos copiar en el nuevo avl
 * @param B es el nodo p que utilizamos del arbol que queremos copiar 
 **/
template<typename T>
void AVL<T>::copia(NodoAVL<T>* &q, NodoAVL<T> *p) {
    if (p) {
        q = new NodoAVL<T> (*p);
        copia(q->izq, p->izq);
        copia(q->der, p->der);
    } else
        q = 0;
}

/**
 * @brief funcion del contructor por defecto del avl
 **/
template <typename T>
AVL<T>::AVL() {
    raiz = 0;
}

/**
 * @brief funcion del contructor copia del avl
 * @param A es el arbol que tenemos que hacer la copia
 **/
template <typename T>
AVL<T>::AVL(const AVL<T> & origen) {
    copia(raiz, origen.raiz);
    numEle = origen.numEle;
}

/**
 * @brief funcion para destruir el avl correctamente al finalizar el programa
 **/
template <typename T>
AVL<T>::~AVL() {
    borrar(raiz);
    numEle = 0;
    raiz = 0;
}

/**
 * @brief funcion para poder utilizar el operador igual en el avl
 * @param A es el arbol que tenemos que igualar para poder sacarlo
 * @return devuelve el arbol del resultado del operador
 **/
template<typename T>
AVL<T>& AVL<T>::operator=(const AVL<T>& orig) {
    if (this != &orig) {
        borrar(raiz);
        copia(raiz, orig.raiz);
    }
    return *this;
}

/**
 * @brief funcion para hacer una rotacion a la izquierda en un nodo p del avl
 * @param A es el nodo del avl del que vamos a partir para hacer la rotacion a izquierdas
 **/
template<typename T>
void AVL<T>::rotIzqda(NodoAVL<T>* &p) {
    NodoAVL<T> *q = p, *r;
    p = r = q->der;
    q->der = r->izq;
    r->izq = q;
    q->bal++;
    if (r->bal < 0) q->bal += -r->bal;
    r->bal++;
    if (q->bal > 0) r->bal += q->bal;
}

/**
 * @brief funcion para hacer una rotacion a la derecha en un nodo p del avl
 * @param A es el nodo del avl del que vamos a partir para hacer la rotacion a derechas
 **/
template<typename T>
void AVL<T>::rotDecha(NodoAVL<T>* &p) {
    NodoAVL<T> *q = p, *l;
    p = l = q->izq;
    q->izq = l->der;
    l->der = q;
    q->bal--;
    if (l->bal > 0) q->bal -= l->bal;
    l->bal--;
    if (q->bal < 0) l->bal -= -q->bal;
}

/**
 * @brief funcion para insertar un dato en el arbol
 * @param A es el nodo del avl que vamos a utilizar para poder movernos en el avl
 * @param B es el dato que queremos insertar en el avl
 * @return devuelve el valor de la variable deltaH para poder verificar la insercion
 **/
template<typename T>
int AVL<T>::inserta(NodoAVL<T>* &c, T &dato) {
    NodoAVL<T> *p = c;
    int deltaH = 0;
    if (!p) {
        p = new NodoAVL<T>(dato);
        c = p;
        deltaH = 1;
    } else if (dato > p->dato) {
        if (inserta(p->der, dato)) {
            p->bal--;
            if (p->bal == -1) deltaH = 1;
            else if (p->bal == -2) {
                if (p->der->bal == 1) rotDecha(p->der);
                rotIzqda(c);

            }
        }
    } else if (dato < p->dato) {
        if (inserta(p->izq, dato)) {
            p->bal++;
            if (p->bal == 1) deltaH = 1;
            else if (p->bal == 2) {
                if (p->izq->bal == -1) rotIzqda(p->izq);
                rotDecha(c);

            }
        }
    }

    return deltaH;
}

/**
 * @brief funcion para poder recorrer en Inorden el avl
 * @param A es el nodo del avl que vamos a utilizar para recorrer el avl
 **/
template <typename T>
void AVL<T>::recorreInorden(NodoAVL<T> *p, int nivel) {
    if (p) {
        recorreInorden(p->izq, nivel + 1);
        std::cout <<  p->dato;
        std::cout << " En el nivel " << nivel << std::endl;
        recorreInorden(p->der, nivel + 1);
    }
}

/**
 * @brief funcion para que muestre los numeros de elementos del avl
 * @return devuelve el numero de elementos del arbol
 **/
template <typename T>
unsigned int AVL<T>::numElementos() {
    return numEle;
}

/**
 * @brief funcion para sacar la altura del avl
 * @param A es el nodo del avl que vamos a utilizar para el calculo de la altura
 * @return devuelve el valor de la altura del arbol 
 **/
template <typename T>
unsigned int AVL<T>::altura() {
    unsigned int result=0;
    altura_aux(this->raiz, 0 ,result);
    return result;
}

/**
 * @brief funcion auxiliar para poder calcular la altura del avl
 * @param A es el nodo del avl que vamos a utilizar para el calculo de la altura
 * @return devuelve el valor de la altura del arbol 
 **/
template<typename T>
unsigned int AVL<T>::altura_aux(NodoAVL<T> *p, int nivel, unsigned int &result) {
        if (p){
        altura_aux(p->izq,nivel+1,result);
        if (nivel>result)
            result=nivel;
        altura_aux(p->der,nivel+1,result);
    }
}

/**
 * @brief funcion para saber si un dato se encuentra en el avl
 * @param A es el dato que deseemos buscar en el arbol
 * @param B es un Nodo del avl 
 * @return devuelve el nodo p si lo encuentra para utilizarlo en la funcion de busca  
 **/
template <typename T>
NodoAVL<T> *AVL<T>::buscaClave(T &ele, NodoAVL<T> *p) {
    if (!p)
        return 0;
    else if (ele < p->dato)
        return buscaClave(ele, p->izq);
    else if (ele > p-> dato)
        return buscaClave(ele, p->der);
    else return p;
}

/**
 * @brief funcion para saber si un dato se encuentra en el avl
 * @param A es el dato que deseemos buscar en el arbol
 * @param B es una variable auxiliar para poder utilizarla en dicho algoritmo
 * @return TRUE O FALSE dependiendo si encuentra o no el dato en el avl    
 **/
template <typename T>
bool AVL<T>::busca(T &ele, T* &result) {
    NodoAVL<T> *p = buscaClave(ele, raiz);
    if (p) {
        result = &(p->dato);
        return true;
    }
    return false;
}

/**
 * @brief funcion para saber si un dato se encuentra en el avl
 * @param A es el dato que deseemos buscar en el arbol
 * @param B es una variable auxiliar para poder utilizarla en dicho algoritmo
 * @return TRUE O FALSE dependiendo si encuentra o no el dato en el avl    
 **/
template<typename T>
bool AVL<T>::buscaIt(T& dato, T* &result) {
    NodoAVL<T> *aux = raiz; 
    while (aux != 0) {
        if (dato < aux->dato) {
            aux = aux->izq;
        } else {
            if (dato > aux->dato) {
                aux = aux->der;
            } else {
                result = &(aux->dato);
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief funcion para complementar el destructor del arbol
 * @param A Puntero a Nodo del avl para poder borrarlo por la izq y der
 **/
template<typename T>
void AVL<T>::borrar(NodoAVL<T>* p) {
    if (p) {
        borrar(p->izq);
        borrar(p->der);
        delete p;
        p = 0;
    }
}

#endif /* AVL_H */

