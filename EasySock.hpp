#define _WINSOCK_DEPRECATED_NO_WARNINGS
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
#include <thread>

using namespace std;
#pragma comment(lib,"ws2_32.lib")





class EasySock {
public:
    WSADATA wsaData;
    SOCKET Socket;
    SOCKADDR_IN SockAddr;
    struct hostent* host;
    locale local;
    char buffer[1024];
    string response;
    string sip;
    int port;
    int response_length;


    EasySock(string in_ip, int in_port) {
        int lineCount = 0;
        int rowCount = 0;

        sip = in_ip;
        char ip[50];
        int i;
        for (i = 0; i < sip.length() + 1; i++) {
            ip[i] = sip[i];
        }

        port = in_port;

        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            cout << "WSAStartup failed." << endl;
            system("pause");
        }

        Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        SockAddr.sin_port = htons(port);
        SockAddr.sin_family = AF_INET;
        SockAddr.sin_addr.s_addr = inet_addr(ip);
    }

    void connect_to_target() {
        if (connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
            cout << "Could not connect" << endl;
            system("pause");
        }
    }

    void timer_start(int* finished, int sleeptime) {
        Sleep(sleeptime);
        *finished = 1;

    }

    void send_to_target(string raw) {
        send(Socket, raw.c_str(), strlen(raw.c_str()), 0);
    }


    string recv_response() {
        int finished_timer = 0;
        thread timer(&EasySock::timer_start, this, &finished_timer, 10000);
        while ((response_length = recv(Socket, buffer, 1024, 0)) > 0) {
            response += string(buffer);
            if (finished_timer == 1) {
                timer.join();
                cout << "Timeout no more data recieved!" << endl;
                finished_timer = 0;
                return(response);
            }
        }
        return(response);
    }

    void clean_up() {
        closesocket(Socket);
        WSACleanup();
    }

};