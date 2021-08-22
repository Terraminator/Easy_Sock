#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <locale>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

using namespace std;
#pragma comment(lib,"ws2_32.lib")





class EasySock {
public:
    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    struct hostent* host;
    locale local;
    char buffer[10000];
    string response;
    string ip;
    int port;


    EasySock(string in_ip, int in_port) {

        int lineCount = 0;
        int rowCount = 0;

        int i = 0;
        ip = in_ip;
        port = in_port;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed." << endl;
            system("pause");
        }

        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        SockAddr.sin_port = htons(port);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);
    }

    void connect_to_target() {
        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            cout << "Could not connect" << endl;
            system("pause");
        }
    }



    void send_to_target(string raw) {
        send(Socket, raw.c_str(), strlen(raw.c_str()), 0);
    }

    string recv_response() {
        response = recv(Socket, buffer, 10000, 0);
        return(response);

    }

    void clean_up() {
        closesocket(Socket);
        WSACleanup();
    }

};