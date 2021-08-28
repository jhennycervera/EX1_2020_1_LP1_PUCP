/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 * Created on 16 de agosto de 2021, 11:38 AM
 */



/*
 * 
 */
#include "FuncAux.h"

int main(int argc, char** argv) {

    void *pedidos, *stock;
    leerDatos(pedidos, stock);
    atiende(pedidos, stock);
    imprimirDatos(pedidos);


    return 0;
}

