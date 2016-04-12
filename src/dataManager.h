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

void writeVector(string url, vector<char> &data);
void readVector(string url, vector<char> &data);

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

void writeVector(string url, vector<char> &data){
	try {
		fstream out(url.c_str(), ios::out | ios::binary);
		if (out.is_open()){
			
			out.write(reinterpret_cast<const char*>(&data[0]), data.size()*sizeof(char));
			
			cerr << "Operation successfully performed\n"<<data.size()<<" data writed\n";
		}else{
			cerr << "Error opening file";
			return;
		}
		out.close();
	}catch (std::ifstream::failure e) {
		std::cerr << "Exception opening/reading/closing file\n"<<url.c_str()<<endl;;
	}
}
void readVector(string url, vector<char> &data){
	try {
		fstream in(url.c_str(), ios::in | ios::binary);
		if (in.is_open()){
			in.seekg(0, ifstream::end);
			int size = in.tellg() / sizeof (char);
			in.seekg(0, ifstream::beg);
			data.resize(size);
			in.read(reinterpret_cast<char*>(&data[0]), size*sizeof(char));
			
			cerr << "Operation successfully performed\n";
		}else{
			cerr << "Error opening file";
			return;
		}
		in.close();
	}catch (std::ifstream::failure e) {
		std::cerr << "Exception opening/reading/closing file: "<<url.c_str()<<endl;
	}
}
#endif	/* DATAMANAGER2_H */

