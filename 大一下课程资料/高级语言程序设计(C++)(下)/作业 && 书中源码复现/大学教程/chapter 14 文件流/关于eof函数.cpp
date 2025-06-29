#include <iostream>
#include <fstream>
using namespace std;
 
int main(){
	ofstream fileOut;
	ifstream fileIn;
 
	fileOut.open("testFile");
	for(int i = 0; i < 5; i++)
		fileOut<<i;
	fileOut.close();
 
	fileIn.open("testFile");
	while(!fileIn.eof()){
		int i;
		fileIn>>i;
		cout<<i<<"\t";
	}
	cout<<endl;
	fileIn.close();	
}