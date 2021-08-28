/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FuncAux.h
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 *
 * Created on 22 de agosto de 2021, 12:22 PM
 */

#ifndef FUNCAUX_H
#define FUNCAUX_H
#define MAX 100
#include <fstream>
using namespace std;  //para manejar un objeto o libreria que este en el espacio stdio

enum Ped {
    FECHA, RUC, COD, NOMBRE, CANT_SOL, CANT_ATEN
};

enum Stock {
    COD_S, STOCK
};

void imprimirDatos(void *);
void procesarPedidosCliente(ifstream &, void**, int , int&);
void leerPedidos(void * &);
void leerStock(void * &) ;
void leerDatos(void * &, void* &) ;
void imprimirLinea(ofstream &, char , int ) ;
void fSepararFecha(int , int&, int &, int &) ;

void imprimirDatos(void *);

int compararPed(void * , void *);

void intercambiar(void * &, void *&) ;

void ordenarPedidosFecha(void * *, int , int ) ;
int compararPed1(void * , void *) ;

void ordenarPedidosRuc(void * *, int , int ) ;
int modificarStock(void * , int , int );

void atiende(void * , void * ) ;


#endif /* FUNCAUX_H */

