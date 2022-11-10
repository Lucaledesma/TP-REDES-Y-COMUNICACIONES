#include <iostream>
#include <winsock2.h>
#include <string.h>
#include <math.h>
#include <sstream>
#include <fstream>
#include <ctime>
#define TAM_BUFFER 2048

using namespace std;

void menu(){
    cout << "\n-------------------------------------" << endl;
    cout << "|     ELIGE UNA OPCION: (1/2/3)     |" << endl;
    cout << "|-----------------------------------|" << endl;
    cout << "|  1) Realizar calculo:             |" << endl;
    cout << "|  2) Ver Registro de Actividades:  |" << endl;
    cout << "|  3) Cerrar Sesion:                |" << endl;
    cout << "-------------------------------------" << endl;
}

class Client{
public:
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    char buffer[TAM_BUFFER];

    Client()
    {
        cout<<"Conectando al servidor..."<<endl<<endl;
        WSAStartup(MAKEWORD(2,0), &WSAData);
        server = socket(AF_INET, SOCK_STREAM, 0);
        addr.sin_addr.s_addr = inet_addr("192.168.0.17");
        addr.sin_family = AF_INET;
        addr.sin_port = htons(5000);
        connect(server, (SOCKADDR *)&addr, sizeof(addr));
        cout << "Conectado al Servidor!" << endl;
    }

    void Enviar(char mensaje[])
    {
        strcpy(this->buffer, mensaje);
        send(server, buffer, sizeof(buffer), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    string Recibir()
    {
        recv(server, buffer, sizeof(buffer), 0);
        string buf=buffer;
        memset(buffer, 0, sizeof(buffer));
        return buf;
    }

    void CerrarSocket()
    {
       closesocket(server);
       WSACleanup();
       cout << "\nSocket cerrado." << endl << endl;
    }
};

int main()
{
    cout << "TP REDES - CALCULADORA" << endl;
    Client *Cliente = new Client();

    clock_t t;
    string opcion = "";

    while((opcion != "0") && (opcion != "3")){

        string operacion;

        menu();
        char opMenu[TAM_BUFFER];

        t = clock();

        cin.getline(opMenu,TAM_BUFFER,'\n');

        t = clock()-t;

        if ((int(t)/CLOCKS_PER_SEC) > 120){
            strcpy(opMenu, "0");
        }

        Cliente->Enviar(opMenu);

        opcion = Cliente->Recibir();

        if(opcion=="1"){

            char result[TAM_BUFFER] = "";

            while(strcmp(result,"volver")!=0){
                cout << "\nOPERACIONES DISPONIBLES : (a+b) | (a-b) | (a*b) | (a/b) | (a^b) | (a!) | Volver al menu: 'volver'" << endl;
                cout << "INGRESA LA OPERACION : " << endl;

                cin.getline(result,TAM_BUFFER,'\n');

                if (strcmp(result,"volver")!=0){
                    Cliente->Enviar(result);

                    operacion = Cliente->Recibir();

                    cout << "\n**************************************************" << endl;
                    cout << operacion << endl;
                    cout << "**************************************************" << endl;
                }else{
                    Cliente->Enviar("volver");
                    system("pause");
                }
            }

        } else if (opcion=="2"){

            Cliente->Enviar("archivo");

            cout << "*************************" << endl;
            cout << "REGISTRO DE ACTIVIDADES" << endl;
            cout << "*************************\n" << endl;

            cout << Cliente->Recibir() << endl;

            system("pause");

        } else if (opcion=="3"){
            Cliente->Enviar("close");
            Cliente->CerrarSocket();

            system("pause");

        } else if (opcion=="0"){
            Cliente->Enviar("inactive");
            cout << "\nCliente desconectado por inactividad." << endl;
            Cliente->CerrarSocket();

            system("pause");
        }

        system("cls");
    }

    cout << "Gracias por participar!" << endl;

}
