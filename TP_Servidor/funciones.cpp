#include <iostream>
#include <winsock2.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string.h>
#include "funciones.h"

using namespace std;

/********************* CALCULADORA *********************/

int calculadora(int x, char oper,int y)
{
    int res = 0;

    switch(oper){
        case '+':
            res = x+y;
        break;

        case '-':
            res = x-y;
        break;

        case '*':
            res = x*y;
        break;

        case '/':
            res = x/y;
        break;

        case '^':
            res = pow(x,y);
        break;

        default:
            return 0;
        }

    return res;
}

char obtenerOperacion(char op){

    char operacion = ' ';

    switch(op){
        case '+':
            operacion = '+';
        break;

        case '-':
            operacion = '-';
        break;

        case '*':
            operacion = '*';
        break;

        case '/':
            operacion = '/';
        break;

        case '^':
            operacion = '^';
        break;

        case '!':
            operacion = '!';
        break;
    }

    return operacion;
}

int calcularFactorial(int x){

    int factorial = 1;

    for (int i=1; i <= x ;i++){

        factorial = factorial * i;

    }

    return factorial;
}

/********************* TIME *********************/
string tiempoActual(){
    time_t now = time(0);
    tm * time = localtime(&now);
    string a;
    stringstream streamAnio;
    stringstream streamMes;
    stringstream streamDia;
    stringstream streamHora;
    stringstream streamMin;
    string tiempo;
    int anio = 1900+(time->tm_year);
    int mes = (time->tm_mon)+1;
    int dia = (time->tm_mday);
    int hr = (time->tm_hour);
    int mn = (time->tm_min);

    streamAnio << anio;
    streamAnio >> a;
    tiempo += a + "-";

    streamMes << mes;
    streamMes >> a;
    tiempo += a + "-";

    streamDia << dia;
    streamDia >> a;
    tiempo += a + "_";

    streamHora << hr;
    streamHora >> a;
    tiempo += a + ":";

    streamMin << mn;
    streamMin >> a;
    tiempo += a;

    return tiempo;
}

/********************* ARCHIVOS *********************/
void aniadir(string s){
    ofstream archivo;

    archivo.open("server.log.txt", ios::app);

    if(archivo.fail()){
        cout << "ERROR AL ABRIR ARCHIVO" << endl;
        exit(1);
    }

    archivo<<s<<endl;

    archivo.close();

}

string lectura(){
    ifstream archivo;
    string s;
    string texto;

    archivo.open("server.log.txt", ios::in);

    if(archivo.fail()){
        cout << "ERROR AL ABRIR ARCHIVO" << endl;
        exit(1);
    }

    while(!archivo.eof()){
        getline(archivo,s);
        texto = texto + s;
        texto = texto + "\n";
    }

    archivo.close();

    return texto;
}
