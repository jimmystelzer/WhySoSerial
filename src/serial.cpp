#include <iostream>
#if defined(__linux__)
#include <dirent.h>
#endif
#if defined(_WIN32)	
#include <windows.h>
#endif
#include "serial.h"


namespace WSS{
	using namespace std;
	shared_ptr<vector<string>> enumerate(){
		shared_ptr<vector<string>> dev = nullptr;
			

#if defined(__linux__)
		DIR * devices_dir = opendir("/dev");
		if(devices_dir == nullptr){
			cout << "Fail to enumerate. Error in open devices directory" << endl;
		}else{
			struct dirent* dir_entry = nullptr;
			while((dir_entry = readdir(devices_dir))){
				if(dir_entry != nullptr){
					string device_name(dir_entry->d_name);
					if(device_name.compare(0, 4, "ttyS") == 0 || device_name.compare(0, 6, "ttyUSB") == 0
							|| device_name.compare(0, 6, "ttyACM") == 0 || device_name.compare(0, 6, "rfcomm") == 0){
						if(dev == nullptr){
							dev = make_shared<vector<string>>();
						}
						dev->push_back(device_name);
					}
				}else{
					break;
				}
			}

		}
#endif
#if defined(_WIN32)	
		size_t ucchMax = 65536;
		char *lpTargetPath = (char *) malloc(ucchMax);
		char *token;
		if(lpTargetPath != nullptr){
			SetLastError(0);
			QueryDosDeviceA(nullptr, lpTargetPath, ucchMax);
			while(GetLastError() == ERROR_INSUFFICIENT_BUFFER){
				SetLastError(0);
				ucchMax += 65536;
				char *rel_lpTargetPath = (char *)realloc(lpTargetPath, ucchMax);
				if(rel_lpTargetPath == nullptr){
					free(lpTargetPath);
				}
				lpTargetPath = rel_lpTargetPath;
				rel_lpTargetPath = nullptr;
				QueryDosDeviceA(nullptr, lpTargetPath, ucchMax);
			}

			// lpTargetPath is a block of concatened cstrings with \0 separators
			for(token = lpTargetPath; *token; token+=strlen(token)+1){
				string device_name(token);

				if(device_name.compare(0, 3, "COM") == 0){
					if(dev == nullptr){
						dev = make_shared<vector<string>>();
					}
					dev->push_back(device_name);
				}
			}

			free(lpTargetPath);
		}
#endif

		return dev;
	}
		
}
