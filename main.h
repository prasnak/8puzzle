#include <iostream>
#include <queue>
#include <vector>

using namespace std; 

const int ROWS=3; 
const int COLS=3;

void printState(int state[3][3])
{
	cout<<"_______"<<endl;
	for(int i=0; i<ROWS; i++)
	{
		cout<<"|";
		for (int j=0; j<COLS;j++)
		{
			cout<<state[i][j]<<"|";
		}
		cout<<endl<<"-------"<<endl;     
	} 
}