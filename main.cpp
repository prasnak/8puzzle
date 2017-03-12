#include "main.h"

void printState(int [3][3]); 

int main()
{

//int initState[rows][cols]; //correct code. uncomment when the next line is commented. 
int initState[ROWS][COLS] = {{1,3,4},{8,6,2},{7,5,0}}; //for testing purposes - else, the user enters. 

printState(initState);


return 0; 	
}