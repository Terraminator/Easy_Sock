#include "EasySock.hpp"


int main(){
	cout << "Example Program how to use Easysock" << endl;
	cout << "Building easysock object..." << endl;
	EasySock easysock("64.13.139.230", 23);
	cout << "Connecting to telehack.com..." << endl;

	easysock.connect_to_target();
	cout << "Sending starwars to target..." << endl;
	easysock.send_to_target("starwars");
	cout << "Receiving Response..." << endl;
	string response = easysock.recv_response();
	cout << "Response: " << response << endl;
	cout << "Cleaning up and closing socket..." << endl;
	easysock.clean_up();
	cout << "Example Finished!!!";
}