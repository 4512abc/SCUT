
#include <iostream>
#include <fstream>
using namespace std;
 
int main(){
	ofstream fileOut;
	ifstream fileIn;
 
	fileOut.open("testFile");
	for(int i = 0; i < 5; i++)
		fileOut.write((char*)(&i),sizeof(i));
	fileOut.close();
 
	fileIn.open("testFile");
	while(!fileIn.eof()){
		int i;
		fileIn.read((char*)(&i), sizeof(i));
		cout<<i<<"\t";
	}
	cout<<endl;
	fileIn.close();
}

/* eof()返回true的条件是“读到文件结束符”，而不是文件内容的最后一个字符。“文件结束符”不是指文件最后的字符，而是文件最后的字符的下一位。

     对于上面一段代码，i是以文本形式输入文件也是以文本形式读取文件，每一个int在输进去文件是是以char或是char[ ]形式输入的，读入时则是以char形式读入，文件以迭代方式读入char并输入屏幕显示，其实到最后文件也有读入最后所谓的“文件结束符”，“文件结束符”是一个不可显示字符，因为“文件结束符”实际上的值为-1。 我们知道在ASCII代码值的范围是0~255，不可能出现-1。。

    而对于下一段代码，i是以二进制形式输入文件的也是以二进制形式读取文件的，每一个int在输入文件时是以int形式输入，在读取时也是以int形式读入。知道int所占字节是4，而char所占字节是1。当读完文件中所有的int时，读到最后的“文件结束符”时，只剩下1字节，和

fileIn.read((char*)(&i), sizeof(i));
    中的sizeof(i)不符，这时编译器会重复上一个sizeof(i)的数据并输出。所以最后输出会重复最后一个int。
*/