#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>

#include "WhySoSerial.h"
#include "serial.h"


#if defined(_WIN32)
#include <windows.h>
#endif

int main(int argc, char **argv) {
#if defined(_WIN32)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif
	std::cout << "Start" << std::endl;
	std::shared_ptr<std::vector<std::string>> ports = WSS::enumerate();
	if(ports != nullptr){
		for(auto port : (*ports.get())){
			std::cout << "Device: " << port << std::endl;
		}
	}
#if defined(_WIN32)
	Fl_Double_Window *window = make_window();
	window->end();
	window->show(argc, argv);
	return Fl::run();
#else
	return 0;
#endif
}
