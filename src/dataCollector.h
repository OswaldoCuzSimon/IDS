/* 
 * File:   dataCollector.h
 * Author: Oswaldo Cruz Simon
 *
 * Created on 23 de marzo de 2016, 1:35
 */

#ifndef DATACOLLECTOR_H
#define	DATACOLLECTOR_H

using namespace std;

string to_string(int num);
vector<int> obtenerMuestra(vector<int> poblacion,int tamMuestra, int lenPalabra);
void createBinary(char urltext[], char urlbin[]);
map<int,string> getKeys();
string toVectorStr(vector<int> data);
vector<string> convertir(map<string,vector<int> > data);

void createBinary(char urltext[], char urlbin[]){
	FILE *fp;
	char title[100],*text,renglon[2000];
	int tecla;
	vector<int>  poblacion,muestra;
	map<string,vector<int> > data;
	
	srand (time(NULL));
	
	fp = fopen ( urltext, "r");
	if (fp==NULL) {fprintf(stderr,"File not found: %s\n",urltext); exit (1);}
	
	while(fscanf(fp,"%[^\n]",renglon)==1){
		getc(fp);
		text=renglon;
		if(sscanf(renglon,"%s %[^\n]",title,renglon)==2){
			printf("%s %s\n",title,text);
		}
		if(strlen(renglon)>0){
			while(sscanf(renglon,"%d",&tecla)==1){
				poblacion.push_back(tecla);
			}
			muestra=obtenerMuestra(poblacion,100,10);
			data.insert(pair<string,vector<int> > (title,muestra));
		}
	}
	fclose(fp);
	writeData(urlbin,data);
	
}
string to_string(int num){
	char str[10];
	sprintf(str,"%d",num);
	return string(str);
}
vector<int> obtenerMuestra(vector<int> poblacion,int tamMuestra, int lenPalabra){
	vector<int> muestra;
	int tam;
	tamMuestra=tamMuestra*lenPalabra;
	tam = poblacion.size();
	
	if(tamMuestra>tam){
		while(poblacion.size()<(unsigned int)tamMuestra){
			poblacion.push_back(0);
		}
		return poblacion;
	}
	int pos;
	while(muestra.size()<(unsigned int)tamMuestra){
		pos=rand()%(tam-lenPalabra+1);
		for (int i = 0; i < lenPalabra; i++) {
			muestra.push_back(poblacion[pos+i]);
		}
	}
	return muestra;
}
map<int,string> getKeys(){
	FILE *fp;
	int key;
	char value[11];
	map<int,string> keys;
	
	fp = fopen ( "keys.conf", "r" );        
	if (fp==NULL) {fputs ("File error",stderr); exit (1);}
	
	while(fscanf(fp,"%d %s",&key,value)==2){
		keys.insert( pair<int,string>(key,value) );
	}
	
	fclose ( fp );
	return keys;
}
vector<string> convertir(map<string,vector<int> > data){
	map<string,vector<int> >::iterator it;
	vector<string> v;
	
	for(it=data.begin();it!=data.end();it++){
		v.push_back(toVectorStr(it->second) );
	}
	return v;
}
string toVectorStr(vector<int> data){
	string str;
	
	for (unsigned int i = 0; i < data.size(); i++) {
		str.push_back((char)data[i]);
	}
	return str;
}
#endif	/* DATACOLLECTOR_H */

