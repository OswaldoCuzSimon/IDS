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
vector<char> obtenerMuestra(vector<char> poblacion,int tamMuestra, int lenPalabra);
void createBinary(char urltext[], char urlbin[]);
void printData(map<string,vector<int> > data);
void printData(vector<char> data);
map<int,string> getKeys();
string toVectorStr(vector<int> data);
vector<string> convertir(vector<char> data);
void printData(vector<string> data);

void createBinary(char urltext[], char urlbin[]){
	FILE *fp;
//	char title[100],*text,renglon[1000000];
	int tecla;
	vector<char> data;
	srand (time(NULL));
	
	fp = fopen ( urltext, "r");
	if (fp==NULL) {fprintf(stderr,"File not found: %s\n",urltext); return;}
	/*int key;
	char c;
	while(fscanf(fp,"%s",title)==1){
		vector<int>  poblacion;
		while(1){
			int r=fscanf(fp,"%d%c",&key,&c);
			if(r<=0||c=='\n'||isalpha(c)){
				if(poblacion.size()>0){
					vector<int> muestra=obtenerMuestra(poblacion,100,10);
//					fprintf(stderr,"%s\n",title);
				}
				break;
			}
//			fprintf(stderr,"%d ",key);
			poblacion.push_back(c);
			
		}
	}*/
	while(fscanf(fp,"%d",&tecla)==1){
		data.push_back((char)tecla);
	}
	printf("%d\n",data.size());
	vector<char> muestra=obtenerMuestra(data,(int)(data.size()/2),10);
	fclose(fp);
	printData(muestra);
	writeVector(urlbin,muestra);
	
}
string to_string(int num){
	char str[10];
	sprintf(str,"%d",num);
	return string(str);
}
vector<char> obtenerMuestra(vector<char> poblacion,int tamMuestra, int lenPalabra){
	vector<char> muestra;
	int tam;
	tam = poblacion.size();
	
	if(tamMuestra>tam){
		while(poblacion.size()<(unsigned int)tamMuestra){
			poblacion.push_back((char)0);
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
	char filename[]="keys.conf";
	fp = fopen ( filename, "r" );        
	if (fp==NULL) {fprintf (stderr,"File error %s\n",filename); return keys;}
	
	while(fscanf(fp,"%d %s",&key,value)==2){
		keys.insert( pair<int,string>(key,value) );
	}
	
	fclose ( fp );
	return keys;
}
vector<string> convertir(vector<char>  data, int strSize){
	vector<string> v;
	unsigned int i;
	for(i=0;i<data.size();i+=strSize){
		string s;
		for (int j = i; j < strSize; j++) {
			s.push_back(data[j]);
		}
		v.push_back(s);
		s.clear();
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
void printData(map<string,vector<int> > data){
	map<string,vector<int> >::iterator it;
	for(it=data.begin();it!=data.end();it++){
		cout<<it->first<<" ";
		for (int i:it->second) {
			cout<<i<<" ";
		}
		cout<<endl;
	}
	
}
void printData(vector<char> data){
	for (int i:data) {
		cout<<(int)i<<" ";
	}
	cout<<endl;
}
void printData(vector<string> data){
	for(string s: data){
		cout<<s<<" ";
	}
}
#endif	/* DATACOLLECTOR_H */

