#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#pragma once

#include <iostream>
#include <winsock2.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <string.h>

using namespace std;

/****** CALCULADORA ******/
int calculadora(int x, char oper,int y);
char obtenerOperacion(char op);
int calcularFactorial(int x);

/****** TIME ******/
string tiempoActual();

/****** ARCHIVOS ******/
void aniadir(string s);
string lectura();

#endif // FUNCIONES_H_INCLUDED
