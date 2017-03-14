/*
Prasuna Kunasani
200285299
CS421 Assignment 2
Assumptions: That the state being entered is in the correct format as prompted. This means, a blank (0) is expected
To run program: make run
 */

#include "main.h"

void printState(int [3][3]); 
void depthFirstSearch(vertex&, int);
void breadthFirstSearch(vertex&);
void bestFirstSearch(char,vertex&);
bool isGoalState(vertex);
void printPath(vertex, vector<vertex>);
void initializeChild(vertex, vertex&,int,int); 
void generateMoves(vertex&); 
vector<vertex> generateChildren(vertex&);
int inClosedList(vertex&, vector<vertex>);
int inOpenList(vertex& , vector<vertex>); 
bool isSameNode(vertex , vertex );
int manhattanDistance(int compareState[3][3]);
int heuristicH(int compareState[3][3]);
int tilesOutOfPlace(int compareState[3][3]); 
bool isDuplicateNode (vertex , vector<vertex>, vector<vertex>); 

int main()
{

	int counter =1;
	char input[9]; 
	int choice;

 	int initState[ROWS][COLS] = {{1,2,3},{4,5,6},{7,8,9}}; //correct code. uncomment when the next line is commented. 
 	
 	//int initState[ROWS][COLS] = {{1,3,4},{8,6,2},{7,5,0}}; //for testing purposes - else, the user enters. 
	//int initState[ROWS][COLS] = {{1,2,3},{8,0,4},{7,6,5}}; //Note: same as goal state
    //int initState[ROWS][COLS] = {{2,8,1},{4,3,0},{7,6,5}}; //Note:  testing - med
    //int initState[ROWS][COLS] = {{2,8,1},{4,6,3},{7,5,0}}; //Note:  testing - hard
    //int initState[ROWS][COLS] = {{5,6,7},{4,8,0},{3,2,1}}; //Note: testing - very hard
    //int initState[ROWS][COLS] = {{1,3,0},{8,2,4},{7,6,5}}; //Note:  testing - very easy (expect for DFS)

 	cout<<"The positions of states are layed out as follows---------->"<<endl;
 	printState(initState);

//  TESTING - COMMENT SO YOU DON'T HAVE TO TYPE EACH TIME
 	cout<<"Please enter the initial state using numbers 1-8 and 0 for space:"<<endl;
 	do
 	{
 		cout<<"Position "<<counter<<":";
 		cin>>input[counter-1]; 

 		while (!cin)
 		{
 			cout<<"You did not enter a proper value. Try again:";
 			cin>>input;
 		}
 		counter++;

 	}
 	while (counter<10); 

 	counter = 0; //reset counter

     //place char that the user entered into the state array
 	for(int i=0; i<ROWS;i++)
 	{
 		for(int j=0; j<COLS;j++)
 		{
 			initState[i][j] = input[counter]-'0'; 
 			counter++;
 		}

 	}

 	cout<<"You entered: "<<endl;
 	printState(initState);

//TESTING - Comment till here so you don't have to try the state each time. 

 	vertex initialVertex = {}; //will zero all fields
	initialVertex.setTileState(initState);  

 	cout<<"Which search method would you like to use to find the solution?"<<endl;
 	cout<<"1 - Depth First Search"<<endl;
 	cout<<"2 - Breadth First Search"<<endl;
 	cout<<"3 - BestFS - Tiles out of space heuristic"<<endl;
 	cout<<"4 - BestFS - Moves to get to goal state heuristic"<<endl;
 	cout<<"5 - BestFS - Manhattan distance + Sequence Score heuristic"<<endl;
 	cout<<"Your choice: "; 
 	cin>>choice; 

 	while (!cin || choice>5)
 	{
 		cout<<"You didn't enter a proper value. Try again:"; 
 		cin>>choice;
 	}

 	if (choice == 1)
 	{
 		int maxLevel = 0; 
 		cout<<"What is the maximum level you want the program to run for?"<<endl;
 		cin>>maxLevel; 
 		depthFirstSearch(initialVertex, maxLevel); 
 	}
 	else if (choice == 2)
 	{
 		breadthFirstSearch(initialVertex);
 	}
 	else if (choice ==3)
 	{
 		bestFirstSearch('t',initialVertex);
 	}
 	else if (choice ==4)
 	{
 		bestFirstSearch('m',initialVertex);
 	}
 	else if (choice ==5)
 	{
 		bestFirstSearch('h',initialVertex);
 	}


 	return 0; 	
 }