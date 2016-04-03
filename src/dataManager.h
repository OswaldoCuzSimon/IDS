/* 
 * File:   dataManager2.h
 * Author: Oswaldo Cruz Simon
 *
 * Created on 23 de marzo de 2016, 1:02
 */

#ifndef DATAMANAGER2_H
#define	DATAMANAGER2_H

#include<fstream>

using namespace std;
void writeData(string url, map<string,vector<int> > data);
void readData(string url, map<string,vector<int> > data);
void writeData(string url, map<string,vector<int> > data){
	fstream out(url.c_str(), ios::out | ios::binary);
    
	if (out.is_open()){
		cerr << "Operation successfully performed\n";
		out.write((char *)&data, sizeof(map<string,vector<int> >));
	}else{
		cerr << "Error opening file";
		return;
	}
	
    out.close();
}
void readData(string url, map<string,vector<int> > data){
	fstream in(url.c_str(), ios::in | ios::binary);

	if (in.is_open()){
		cerr << "Operation successfully performed\n";
		in.read((char *)&data, sizeof(map<string,vector<int> >));
	}else{
		cerr << "Error opening file";
		return;
	}
    in.close();
}

#endif	/* DATAMANAGER2_H */

