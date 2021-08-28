/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/*
 * Author: Jhenny Cervera Vargas
 * Codigo: 20182841
 */


#include <iostream>
#include <iomanip>        
#include <fstream>
#include <cstring>
#define MAX 100

#include "FuncAux.h"
using namespace std;


void procesarPedidosCliente(ifstream &ArchPed, void**auxPed, int ruc, int&numPed) {

    char aux, auxNombre[50], *nombreProd;
    int dd, mm, aa, codProd, cantSoli;


    while (1) {
        ArchPed >> aa >> aux >> mm >> aux >> dd >> aux >> codProd>>aux;
        ArchPed.getline(auxNombre, 50, ',');
        //separar memoria para nombreProd y copiar
        nombreProd = new char[strlen(auxNombre) + 1];
        strcpy(nombreProd, auxNombre);
        ArchPed>>cantSoli;

        //imprimo
        cout.fill('0');
        cout << aa << '/' << right << setw(2) << mm << '/' << setw(2) << dd;
        cout.fill(' ');
        cout << left << setw(5) << ' ' << setw(10) << codProd << setw(50) << nombreProd << cantSoli << endl;

        int fecha = aa * 10000 + mm * 100 + dd;

        void** pedido = new void*[6]; //para cada producto separar memoria

        pedido[FECHA] = new int(fecha);
        pedido[RUC] = new int(ruc);
        pedido[COD] = new int(codProd);
        pedido[NOMBRE] = nombreProd;
        pedido[CANT_SOL] = new int(cantSoli);
        pedido[CANT_ATEN] = new int(0);

        auxPed[numPed] = pedido;
        numPed++;

        if (ArchPed.get() == '\n') break;
    }
    cout << endl;

}

void leerPedidos(void * &pedidosGenerico) {

    ifstream ArchPed("pedidos.csv", ios::in);
    if (!ArchPed) {
        cout << "No se puede abrir el archivo pedidos.csv" << endl;
        exit(1);
    }

    int ruc, numPed = 0;
    char auxClient[30], *cliente;
    void** pedidos, *auxPed[100];
    while (1) {
        ArchPed>>ruc;
        if (ArchPed.eof()) break;
        ArchPed.get();
        ArchPed.getline(auxClient, 30, ',');
        cliente = new char[strlen(auxClient) + 1]; //leer en el stack porq no se usa en el reporte
        strcpy(cliente, auxClient);

        cout << left << setw(10) << ruc << setw(30) << cliente << endl;

        procesarPedidosCliente(ArchPed, auxPed, ruc, numPed);
    }

    pedidos = new void*[numPed];
    for (int i = 0; i < numPed; i++) {
        pedidos[i] = auxPed[i];
    }
    pedidos[numPed] = nullptr;

    pedidosGenerico = pedidos;
}

void leerStock(void * &stockGenerico) {

    ifstream ArchStock("stock.csv", ios::in);
    if (!ArchStock) {
        cout << "No se puede abrir el archivo stock.csv" << endl;
        exit(1);
    }

    int cod, cant, numStock = 0;
    char aux;

    void **stock, *auxSt[100];
    cout << "STOCK" << endl;
    while (1) {

        ArchStock>>cod;
        if (ArchStock.eof()) break;
        ArchStock >> aux>>cant;

        //cout<<left<<setw(10)<<cod<<setw(10)<<cant<<endl;
        void **st = new void *[2];

        st[COD_S] = new int (cod);
        st[STOCK] = new int (cant);
        auxSt[numStock] = st;
        numStock++;
    }
    stock = new void*[numStock];
    for (int i = 0; i < numStock; i++) {
        stock[i] = auxSt[i];
    }
    stock[numStock] = nullptr;

    stockGenerico = stock;
    ArchStock.close();
}

void leerDatos(void * &pedidos, void* &stock) {

    leerPedidos(pedidos);
    leerStock(stock);
    //imprimir pedidos
    //imprimir stock
}

void imprimirLinea(ofstream &Arch, char c, int cant) {

    Arch.fill(c);
    Arch << setw(cant) << c << endl;
    Arch.fill(' ');
}

void fSepararFecha(int fecha, int&dd, int &mm, int &aa) {

    aa = fecha / 10000;
    fecha = fecha % 10000;
    mm = fecha / 100;
    dd = fecha % 100;

}

void imprimirDatos(void *pedidosGenerico) {

    ofstream ArchRep("reporte.txt", ios::out);

    void **ped = (void **) pedidosGenerico;

    int fecha, dd, mm, aa, codPrd, cantS, cantAten;
    char *prod;

    ArchRep << setw(40) << "REPORTE DE ATENCION" << endl;
    int rucAnt = -1;
    for (int i = 0; ped[i] != nullptr; i++) {

        void **pedReg = (void**) ped[i];
        if (rucAnt != *(int*) pedReg[RUC]) {
            //
            ArchRep << endl << left << setw(10) << "RUC:" << *(int*) pedReg[RUC] << endl;
            imprimirLinea(ArchRep, '=', MAX);
            ArchRep << left << setw(10) << "Fecha" << setw(10) << "Cod Producto" << setw(10) << "Producto" << setw(15) << "Cant. Solicitada" << "Cant. Atendida" << endl;
            imprimirLinea(ArchRep, '=', MAX);
        }

        
        fecha = *(int*) pedReg[FECHA];
        codPrd = *(int*) pedReg[COD];
        prod = (char*) pedReg[NOMBRE];
        cantS = *(int*) pedReg[CANT_SOL];
        cantAten = *(int*) pedReg[CANT_ATEN];
        fSepararFecha(fecha, dd, mm, aa);
        ArchRep.fill('0');
        ArchRep << right << aa << "/" << setw(2) << mm << "/" << setw(2) << dd;
        ArchRep.fill(' ');
        ArchRep << left << setw(5) << ' ' << setw(10) << codPrd << setw(35) << prod << setw(10) << cantS << cantAten << endl;
  

        rucAnt = *(int*) pedReg[RUC];
    }

}

int compararPed(void * pedIGen, void *pedJGen) {

    void ** pedI = (void **) pedIGen;
    void ** pedJ = (void **) pedJGen;

    return (*(int*) pedI[FECHA]) - (*(int*) pedJ[FECHA]);

}

void intercambiar(void * &pedI, void *&pedJ) { //pasar por referencia

    void * aux;
    aux = pedI;
    pedI = pedJ;
    pedJ = aux;
}

void ordenarPedidosFecha(void * *ped, int ini, int fin) {

    if (ini >= fin) return;

    int pivote = ini;

    for (int i = ini + 1; i <= fin; i++) {

        if (compararPed(ped[ini], ped[i]) > 0) { //ini - i
            pivote++;
            intercambiar(ped[i], ped[pivote]);
        }
    }
    intercambiar(ped[ini], ped[pivote]);

    ordenarPedidosFecha(ped, ini, pivote - 1);
    ordenarPedidosFecha(ped, pivote + 1, fin);

}

int compararPed1(void * pedIGen, void *pedJGen) {

    void ** pedI = (void **) pedIGen;
    void ** pedJ = (void **) pedJGen;

    return (*(int*) pedI[RUC]) - (*(int*) pedJ[RUC]);

}

void ordenarPedidosRuc(void * *ped, int ini, int fin) {

    if (ini >= fin) return;

    int pivote = ini;

    for (int i = ini + 1; i <= fin; i++) {

        if (compararPed1(ped[ini], ped[i]) > 0) { //ini - i
            pivote++;
            intercambiar(ped[i], ped[pivote]);
        }
    }
    intercambiar(ped[ini], ped[pivote]);

    ordenarPedidosRuc(ped, ini, pivote - 1);
    ordenarPedidosRuc(ped, pivote + 1, fin);

}

int modificarStock(void * stockGen, int codPed, int cant_Sol) {
    //TODO buscar el pedido y verificar si tiene la cantidad en stock para atender
    //si tengo cantidad decuelvo cant y reduzco stock
    //sino retorna lo que hay y dejar el stock en 0

    void ** stock = (void**) stockGen;
    for (int i = 0; stock[i] != nullptr; i++) {
        int cod = *(int*) ((void**) stock[i])[COD_S];
        cout << left << setw(10) << cod << setw(10) << codPed << endl;
        if (codPed == cod) {
            int *cant_s = (int*) ((void**) stock[i])[STOCK]; //modificar por medio de puntero

            if (*cant_s - cant_Sol >= 0) { //(*cant_s) es el valor
                (*cant_s) -= cant_Sol;
                return cant_Sol;
            }
            else {
                int aux = (*cant_s);
                (*cant_s) = 0;
                return aux;
            }
        }
    }
    return 0; //valor de retorno por defecto si no encuentro el prod
}

void atiende(void * pedidosGen, void * stockGen) {
    int i;
    void** ped = (void**) pedidosGen;

    for (i = 0; ped[i] != nullptr; i++);

    ordenarPedidosFecha(ped, 0, i - 1);
    imprimirDatos(pedidosGen);



    for (i = 0; ped[i] != nullptr; i++) {

        void** pedido = (void**) ped[i];
        int cant_atendida = modificarStock(stockGen, *(int*) pedido[COD], *(int*) pedido[CANT_SOL]);
        *(int*) pedido[CANT_ATEN] = cant_atendida;

        cout << left << setw(10) << *(int*) pedido[COD] << setw(10) << *(int*) pedido[CANT_SOL] << setw(10) << cant_atendida << endl;

    }

    ordenarPedidosRuc(ped, 0, i - 1);
}
