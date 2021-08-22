#include "EasySock.hpp"


int main(){
	cout << "Example Program to use Easysock";
	string url = "scanme.nmap.org";
	EasySock easysock("45.33.32.156", 80);
	easysock.connect_to_target();
	easysock.send_to_target("GET / HTTP / 1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n");
	string response = easysock.recv_response();
	easysock.clean_up();
	cout << response << endl;
}