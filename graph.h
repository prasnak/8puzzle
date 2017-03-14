#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
using namespace std;

//A vertex that holds the tile state and other information used by the main program. 
struct vertex {

  int index; //substitute for a name
  int tileState[3][3]; //hold configuration of tiles
  int posOfEmptyTile[2];  //used for moves and duplicates detection 
  int heuristic; 
  int numOfChildren;  
  int parentIndex; 
  char moveToMakeMe; 
  std::vector<char> movesToGenerateChildren; 
  int depth; 
  bool discovered; 

  void setTileState(int state[3][3])
  {
    for (int i=0; i<3; i++) //initialize node with dummy values
      for (int j=0; j<3; j++)
      {
         if (state[i][j] == 0) //save position of empty tile
         {
           posOfEmptyTile[0] = i;
           posOfEmptyTile[1] = j;
         }
         tileState[i][j] = state[i][j]; 
       }
     } 
};


#endif 

//Note to self: You tried --struct vertex* parent;-- since it's the correct way. But the address changes before path is found.