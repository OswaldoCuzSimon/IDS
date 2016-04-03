/* 
 * File:   algorithmAIS.h
 * Author: Oswaldo Cruz Simon
 *
 * Created on 23 de marzo de 2016, 1:38
 */

#ifndef ALGORITHMAIS_H
#define	ALGORITHMAIS_H

using namespace std;
class GenericNegativeSelection{
	private:
	int r;
	unsigned int detectorSize,strSize;
	
	int min3(int a,int b,int c){return min(min(a,b),c);}
	string generateRandomElement();
	vector<string> alterate(vector<string> self);
	vector<string> generateRandomSet(int size);
	public:
		GenericNegativeSelection(int r, int detectorSize,int strSize);
		vector<string> negativeSelectionAlgorithm(vector<string> self);
		vector<string> generatingRepertoire(std::vector<string> self);
		vector<string> censoring(std::vector<string> self, std::vector<string> nonself);
		bool matches(string a, string b);
		
		
};

GenericNegativeSelection::GenericNegativeSelection(int r, int detectorSize,int strSize){
	this->r=r;
	this->detectorSize=detectorSize;
	this->strSize=strSize;
	srand(time(NULL));
}
vector<string> GenericNegativeSelection::negativeSelectionAlgorithm(vector<string> self){
        vector<string> nonself,detectors;
		
		detectors = generatingRepertoire(self);
//		cerr<<"detector size: "<<detectors.size()<<endl;
		self=alterate(self);
		nonself = censoring(self,detectors);
		
		return nonself;
}
std::vector<string> GenericNegativeSelection::generatingRepertoire(std::vector<string> self){
	std::vector<string> detectors;
	string rs;
	bool matchUp;
	while(detectors.size()<detectorSize){
		rs=generateRandomElement();
		matchUp=false;
		for (unsigned int i = 0; i < self.size(); i++) {
			if (matches(rs, self[i])) {
				matchUp=true;
//				cerr<<"No match repertorie g\n";
				break;
			}
		}
		if(matchUp==false){
			detectors.push_back(rs);
		}
	}
	return detectors;
}
std::vector<string> GenericNegativeSelection::censoring(std::vector<string> selfStrings, std::vector<string> detectors){
	vector<string> nonSelf;
//	cerr<<"censoring\n";
	for (string s : selfStrings) {
		for (string d : detectors) {
			if (matches(s, d)) {
//				cerr<<"censo no entro\n";
				nonSelf.push_back(s);
				break;
	}}}
	return nonSelf;
}
bool GenericNegativeSelection::matches(string a, string b){
	unsigned int i,j;
	int mem[a.size()][a.size()];
    
    for(i=1;i<=a.size();i++){
        mem[0][i]=i;
    }
    for(i=1;i<=b.size();i++){
        mem[i][0]=i;
    }
    
    for(j=1;j<=b.size();j++){
        for(i=1;i<=a.size();i++){
            if(a[i-1]==b[j-1])
                mem[j][i]=mem[j-1][i-1];
            else{
                mem[j][i]=min3(mem[j-1][i],
                               mem[j][i-1],
                               mem[j-1][i-1])+1;
            }
        }
    }
//	cerr<<mem[b.size()][a.size()]<<"-"<<r<<endl;
    return mem[b.size()][a.size()]<r;
//	return true;
}
// private methods
string GenericNegativeSelection::generateRandomElement(){
	string randstr;
	
	for (unsigned int i = 0; i < strSize; i++) {
		randstr.push_back( (char) (rand()%256));
	}
	return randstr;
}
vector<string> GenericNegativeSelection::alterate(vector<string> self){
	int cant;
	for(string s: self){
		cant = rand()%s.size();
//		cerr<<"("<<s<<") ";
		for (int i = 0; i < cant; i++) {
			s[rand()%s.size()]=(char)(rand()%256);
		}
//		cerr<<"("<<s<<")"<<endl;
	}
	return self;
}
vector<string> GenericNegativeSelection::generateRandomSet(int size){
	vector<string> randset;
	for (int i = 0; i < size; i++) {
		randset.push_back(generateRandomElement());
	}
	return randset;
}

#endif	/* ALGORITHMAIS_H */

