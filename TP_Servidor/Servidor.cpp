#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <ctime>
#include "funciones.h"
#define TAM_BUFFER 2048

using namespace std;

class Server{
public:
    WSADATA WSAData;
    SOCKET server, client;
    SOCKADDR_IN serverAddr, clientAddr;
    char buffer[TAM_BUFFER];

    Server()
    {
        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);

        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(5000);

        bind(server, (SOCKADDR *)&serverAddr, sizeof(serverAddr));
        listen(server, 0);

        cout << "Escuchando para conexiones entrantes." << endl;

        string s;
        s = tiempoActual();
        s = s + " ============================";
        aniadir(s);

        s = tiempoActual();
        s = s + " =======Inicia Servidor=======";
        aniadir(s);

        s = tiempoActual();
        s = s + " ============================";
        aniadir(s);

        int clientAddrSize = sizeof(clientAddr);
        if((client = accept(server, (SOCKADDR *)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
        {
            s = tiempoActual();
            s = s + " Socket creado. Puerto de escucha:5000.";
            aniadir(s);

            s = tiempoActual();
            s = s + " Conexion Aceptada";
            aniadir(s);

            cout << "Cliente conectado!\n" << endl;
        }
    }

    void Enviar(char mensaje[])
    {
        strcpy(this->buffer, mensaje);
        send(client, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
        cout << "Mensaje enviado!\n" << endl;
    }

    string Recibir()
    {
      recv(client, buffer, sizeof(buffer), 0);
      cout << "El cliente dice: " << buffer << endl;
      string buf=buffer;
      memset(buffer, 0, sizeof(buffer));
      return buf;
    }

    void CerrarSocket()
    {
        closesocket(client);
        cout << "Socket cerrado, cliente desconectado." << endl;
    }
};

class Calculadora{
public:
    Calculadora(){ }

    string Respuesta(string aux){
        string suma1;
        string suma2;

        string resp;
        string a;
        string b;
        stringstream stream;

        char operacion = ' ';
        int prueba = 0;

        if (((aux.length()) < 20) && (!aux.empty())){

            for (int i=0; i < aux.length() ;i++){

                if ((aux[i] == '+') || (aux[i] == '-') || (aux[i] == '*') || (aux[i] == '/') || (aux[i] == '^') || (aux[i] == '!') ||
                    (aux[i] == '0') || (aux[i] == '1') || (aux[i] == '2') || (aux[i] == '3') || (aux[i] == '4') || (aux[i] == '5') ||
                    (aux[i] == '6') || (aux[i] == '7') || (aux[i] == '8') || (aux[i] == '9')){

                    if ((aux[i] != '+') && (aux[i] != '-') && (aux[i] != '*') && (aux[i] != '/') && (aux[i] != '^') && (aux[i] != '!') && (prueba == 0)){
                        suma1 = suma1 + aux[i];
                    }
                    else if ((aux[i] != '+') && (aux[i] != '-') && (aux[i] != '*') && (aux[i] != '/') && (aux[i] != '^') && (aux[i] != '!') && (operacion != '!') && (prueba == 1)){
                        suma2 = suma2 + aux[i];
                    }
                    else if(((aux[i] == '+') || (aux[i] == '-') || (aux[i] == '*') || (aux[i] == '/') || (aux[i] == '^')) && (prueba == 0)){
                        operacion = obtenerOperacion(aux[i]);
                        prueba = 1;
                    }
                    else if((aux[i] == '!') && (prueba == 0)){
                        operacion = obtenerOperacion(aux[i]);
                        prueba = 1;
                    }
                    else if((operacion == '!') && (prueba == 1)){
                        a = "No se pudo realizar la operacion. La operacion esta mal formada: ";
                        b = aux;
                        resp = a + b;
                        return resp;
                    }
                    else {
                        a = "No se pudo realizar la operacion. La operacion esta mal formada: ";
                        b = aux;
                        resp = a + b;
                        return resp;
                    }
                }
                else {
                    a = "No se pudo realizar la operacion, se encontro un caracter no valido: ";
                    b = aux[i];
                    resp = a + b;
                    return resp;
                }
            }

            if (suma1.empty()){
                a = "No se pudo realizar la operacion. La operacion esta mal formada: ";
                b = aux;
                resp = a + b;
                return resp;
            }

            int x = 0;
            int y = 0;
            int resultado = 0;

            if (!suma1.empty()){
                x = stoi(suma1);
            }

            if (!suma2.empty()){
                y = stoi(suma2);
            }

            if((y == 0) && (operacion != '!')){
                resultado = x;
            }
            else if(operacion != '!'){
                resultado = calculadora(x, operacion, y);
            }
            else if(operacion == '!'){
                resultado = calcularFactorial(x);
            }

            a = "Resultado: ";

            stream << resultado;
            stream >> b;

            resp = a + b;
            return resp;

        }
        else{;
            resp = "La operacion tiene que tener entre 1 y 20 caracteres.";
            return resp;
        }
    };

};

int main()
{
    Server *Servidor = new Server();
    Calculadora *Calcu = new Calculadora();
    int i = 0;

    while(i==0){

        string opMenu;
        opMenu = Servidor->Recibir();

        char arr1[opMenu.length() + 1];

        for (int i = 0; i < sizeof(arr1); i++) {
            arr1[i] = opMenu[i];
        }

        Servidor->Enviar(arr1);

        string op;

        do{
            op = Servidor->Recibir();

            if((op!="archivo") && (op!="close") && (op!="inactive") && (op!="volver")){

                string resp = Calcu->Respuesta(op);

                char arr2[resp.length() + 1];

                for (int i = 0; i < sizeof(arr2); i++) {
                    arr2[i] = resp[i];
                }
                Servidor->Enviar(arr2);

                string s = tiempoActual();
                s = s + " Cliente: " + op + " ---> " +resp;
                aniadir(s);
            }
            else if(op=="archivo"){

                string arch = lectura();

                char arc[arch.length() + 1];

                for (int i = 0; i < sizeof(arc); i++) {
                    arc[i] = arch[i];
                }
                Servidor->Enviar(arc);

                string s = tiempoActual();
                s = s + " El Cliente solicito ver el Archivo.";
                aniadir(s);
            }
            else if(op=="close"){

                string s = tiempoActual();
                s = s + " Conexion Cerrada.\n";
                aniadir(s);
                i++;

            }
            else if(op=="inactive"){

                string s = tiempoActual();
                s = s + " Conexion Cerrada por Inactividad.\n";
                aniadir(s);
                i++;

            }
        }while((op!="archivo") && (op!="close") && (op!="inactive") && (op!="volver"));

    }

    Servidor->CerrarSocket();

}
