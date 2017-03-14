#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "graph.h"
#include <queue>
#include <stack>
#include <stdlib.h>


const int ROWS = 3;
const int COLS = 3;
const int goalState[ROWS][COLS] = { { 1, 2, 3 }, { 8, 0, 4 }, { 7, 6, 5 } };

/* Function: Overrides the default comparator for a priority Queue. B
By default, c++ library's priority queue is a max heap. This function helps it become a min heap
inspired from: http://www.technical-recipes.com/2011/priority-queues-and-min-priority-queues-in-c/
*/
struct myComparator {
    bool operator()(const vertex& v1, const vertex& v2)
    {
        return v1.heuristic > v2.heuristic;
    }
};

//Function: Takes is a 2d array and iterates the array print a 8 puzzle box for readability purposes.
void printState(int state[3][3])
{
    cout << "_______" << endl;
    for (int i = 0; i < ROWS; i++) {
        cout << "|";
        for (int j = 0; j < COLS; j++) {
            cout << state[i][j] << "|";
        }
        cout << endl
             << "-------" << endl;
    }
}

/*Function: Takes a vertex structure, iterates through the 2d array state 
and compares it to the goal state. If at any point there is a difference, it exits. */
bool isGoalState(vertex stateToCheck)
{
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (goalState[i][j] != stateToCheck.tileState[i][j])
                return false;
        }
    }
    return true;
}

/*Function: Take a vertex object a vertex list to recursively print it's state and it's parent state until
the initial state is found*/
void printPath(vertex foundState, vector<vertex> fullList)
{
    if (foundState.index == 0) {
        cout << "Child#:" << foundState.index << " at level:" << foundState.depth << endl;
        printState(foundState.tileState);
        return;
    }

    cout << "Child#:" << foundState.index << " at level:" << foundState.depth << endl;
    printState(foundState.tileState);
    cout << "^" << endl;
    cout << "|" << endl;
    //  cout << "|" << endl;

    //the next three lines are needed because the address of the parent kept changing and a roundabout way had to be
    //used to find the parent's tile state.
    int i = 0;
    while (fullList[i].index != foundState.parentIndex)
        i++;

    printPath(fullList[i], fullList);
    return;
}

//Function: Called when a new child is created to initialize the tile state and the position of the empty tile.
void initializeChild(vertex parent, vertex& child, int a, int b)
{
    for (int i = 0; i < ROWS; i++) //straight up copying parent state to child
        for (int j = 0; j < COLS; j++) {
            child.tileState[i][j] = parent.tileState[i][j];
        }
    //updating child's empty tile place using calculations that can be made from parent's empty space
    //added all the variables to make it easier to read and understand what I'm doing
    int parentI = parent.posOfEmptyTile[0];
    int parentJ = parent.posOfEmptyTile[1];

    child.posOfEmptyTile[0] = parentI + a; //old empty tile pos + row value
    child.posOfEmptyTile[1] = parentJ + b; //old empty tile pos + col value

    int childI = child.posOfEmptyTile[0];
    int childJ = child.posOfEmptyTile[1];

    //this is the number that will move in the direction that it was intended to
    //In the parent, it's where the child's empty tile is going to be
    int temp = parent.tileState[childI][childJ];

    //It will go where the parent's empty space would've been
    child.tileState[parentI][parentJ] = temp;

    //Update empty tile of child
    child.tileState[childI][childJ] = 0;
}

//Function: Will generate moves while making sure to not go back up the state and create loops
void generateMoves(vertex& parentState)
{
    if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 0 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
    }
    else if (parentState.posOfEmptyTile[0] == 1 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'd')
            parentState.movesToGenerateChildren.push_back('u');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 0) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 1) {
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'r')
            parentState.movesToGenerateChildren.push_back('l');
    }
    else if (parentState.posOfEmptyTile[0] == 2 && parentState.posOfEmptyTile[1] == 2) {
        if (parentState.moveToMakeMe != 'u')
            parentState.movesToGenerateChildren.push_back('d');
        if (parentState.moveToMakeMe != 'l')
            parentState.movesToGenerateChildren.push_back('r');
    }
}

//Function: Generates children of a vertex and returns the generated children as a vector.
vector<vertex> generateChildren(vertex& parentState)
{
    generateMoves(parentState);
    parentState.numOfChildren = parentState.movesToGenerateChildren.size();

    int count = 0;
    vector<vertex> children;

    while (count != parentState.numOfChildren) {
        vertex tempChild; //create temp child

        /*To initialize tile state, the follow formula was used to see the values:   
  //For Down, take position of empty tile(eg 11) and subtract 10. Eg, 11-10 = 00. And the value from 00 swap with 11 . 
  //For Up, add 10 to the position of the empty tile
  //For right, subtract 01 to the position of empty tile
  //For left, add 01 to the position of empty tile  */

        if (parentState.movesToGenerateChildren[count] == 'l') //left
        {
            tempChild.moveToMakeMe = 'l';
            initializeChild(parentState, tempChild, 0, 1);
        }
        else if (parentState.movesToGenerateChildren[count] == 'r') //right
        {
            tempChild.moveToMakeMe = 'r';
            initializeChild(parentState, tempChild, -0, -1);
        }
        else if (parentState.movesToGenerateChildren[count] == 'u') //up
        {
            tempChild.moveToMakeMe = 'u';
            initializeChild(parentState, tempChild, 1, 0);
        }
        else if (parentState.movesToGenerateChildren[count] == 'd') //down
        {
            tempChild.moveToMakeMe = 'd';
            initializeChild(parentState, tempChild, -1, -0);
        }

        tempChild.depth = parentState.depth + 1;
        tempChild.numOfChildren = 0;

        count++;

        children.push_back(tempChild);
    }

    return children;
}

//Function: Simply compares two vertex objects to see if they are the same.
bool isSameNode(vertex node1, vertex node2)
{
    //first, checking if the space is in the same position else no need to compare each tile
    if (node1.posOfEmptyTile[0] == node2.posOfEmptyTile[0] && node1.posOfEmptyTile[1] == node2.posOfEmptyTile[1])

    {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (node1.tileState[i][j] != node2.tileState[i][j])
                    return false;
            }
        }
    }
    else
        return false;

    return true;
}

//Function: Checks to see if a vertex(state) is in the openList (where discovered = true)
int inOpenList(vertex& checkState, vector<vertex> nodeList)
{
    for (int i = 0; i < nodeList.size(); i++) {
        if (nodeList[i].discovered == true) //means it was in the open list
        {
            if (isSameNode(nodeList[i], checkState)) {
                return nodeList[i].index;
            }
        }
    }
    return -1;
}

//Function: checks to see if a vertex (state) is in the closedList
int inClosedList(vertex& checkState, vector<vertex> closedList)
{
    for (int i = 0; i < closedList.size(); i++) {
        if (isSameNode(closedList[i], checkState)) {
            return closedList[i].index;
        }
    }
    return -1;
}

//Function: Checks to see if a vertex (state) is in both the open and closed lists. 
bool isDuplicateNode(vertex nodeToCheck, vector<vertex> nodeList, vector<vertex> closedList)
{
    if (inOpenList(nodeToCheck, nodeList) > -1 && inClosedList(nodeToCheck, nodeList) > -1)
        return true;
    else
        return false;
}

/*Function: Calculates the manhattan Distance. "The "Manhattan distance" between 2 squares S1 and S2 is the distance between S1 
and S2 in the horizontal direction plus the distance between S1 and S2 in the vertical direction. We want to minimize
the length of solutions."*/
int manhattanDistance(int compareState[3][3])
{
    int manhattanDist = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            int tile = compareState[i][j];

            if (tile != goalState[i][j]) {
                int row = 0;
                int col = 0;
                do {
                    do {
                        col++;
                    } while (tile == goalState[row][col] || col > 3);

                    row++;

                } while (tile == goalState[row][col] || row > 3);
                manhattanDist = manhattanDist + abs(row - i) + abs(col - j);
            }
        }
    }
    return manhattanDist;
}


/*Function calculates H = totdist + 3*seq where totdist is the manhattan distance.The "sequence score" that measures the
 degree to which the tiles are already ordered in the current position with respect to the order required in the goal 
 configuration. seq is computed as the sum of scores for each tileaccording to the following rules:
A tile in the centre scores 1, A tile on a non-central square scores 0 if the tile is, in the clockwise direction, 
followed by its proper successor. Such a tile scores 2 if it is not followed by its proper successor.*/
int heuristicH(int compareState[3][3])
{

    int seqScore = 0; 

    //Hard coded method to find sequence score

    for (int i=0; i<ROWS; i++)
    {
        for (int j=0; j<COLS; j++)
        {
            if ((i==0 && j==0) && (compareState[0][1] != goalState[0][1]))
                seqScore =  seqScore + 2; 
            else if ((i==0 && j==1) && (compareState[0][2] != goalState[0][2]))
                  seqScore =  seqScore + 2; 
            else if ((i==0 && j==2) && (compareState[1][2] != goalState[1][2]))
                  seqScore =  seqScore + 2; 
           else if ((i==1 && j==0) && (compareState[0][0] != goalState[0][0]))
                 seqScore =  seqScore + 2; 
           else if (i==1 && j==1) 
                 seqScore =  seqScore + 1; 
           else if ((i==1 && j==2) && (compareState[2][2] != goalState[2][2]))
                  seqScore =  seqScore + 2; 
           else if ((i==2 && j==0) && (compareState[1][0] != goalState[1][0]))
                 seqScore =  seqScore + 2; 
           else if ((i==2 && j==1) && (compareState[2][0] != goalState[2][0]))
                  seqScore =  seqScore + 2; 
           else if ((i==2 && j==2) && (compareState[2][1] != goalState[2][1]))
                 seqScore =  seqScore + 2; 
        }
    }

    int totdist = manhattanDistance(compareState); 
    int H = totdist + 3*seqScore;

    return H;
}

/*Function: Calculates the tilesOutOfPlace heuristic where it simply counts how many tiles in the comparing state are out of 
place from those in the goal state*/
int tilesOutOfPlace(int compareState[3][3])
{
    int outOfPlaceCount = 0;
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            if (goalState[i][j] != compareState[i][j])
                outOfPlaceCount++;
    return outOfPlaceCount - 1; //to account for the middle tile
}

//The algorithm is based on pseudocode from pg 134 of Artificial Intelligence 6th edition
void bestFirstSearch(char heurChoice, vertex& initialVertex)
{
    cout << "Best First Search will be performed" << endl;

    priority_queue<vertex, vector<vertex>, myComparator> openBestFSList;

    vector<vertex> nodeList; //holds all nodes- needed for depth

    vector<vertex> closedList; //Algo - closed:= []
    vector<vertex> childList; //holds children once generated



 cout << "Number of states/nodes generated: " << initialVertex.index << ", ";
    initialVertex.discovered = true;
   

    openBestFSList.push(initialVertex); //Algo - open:= [Start]
    nodeList.push_back(initialVertex);

    while (!openBestFSList.empty()) //Algo- while open != [] do
    { 
        //Algo - remove the leftmost state from open, call it X
        vertex topVertex = openBestFSList.top();
        openBestFSList.pop(); 

        // Algo = if X = goal, then return the path from Start to X

        if (isGoalState(topVertex)) {
            cout << "GOAL STATE FOUND! Here is the path to the goal state:" << endl;
            printPath(topVertex, nodeList);
            return;
        }
        else //Algo - else, generate Children of X
        {
            int parentIndex = topVertex.index;

            childList = generateChildren(topVertex);

            int numberOfChildren = topVertex.numOfChildren;

            vertex currentChild;

            int duplicateOpenIndex = -1; //saves the return value from open list duplicate checks
            int duplicateClosedIndex = -1;

            //Algo - for each child of X, do 
            while (numberOfChildren > 0) {

                currentChild = childList[numberOfChildren - 1];
                currentChild.index = nodeList.size();
                currentChild.parentIndex = parentIndex;

                duplicateOpenIndex = inOpenList(currentChild, nodeList);
                duplicateClosedIndex = inClosedList(currentChild, closedList);

                int heurValue = 0;

                //Algo - If the child is not on open or closed lists
                if (duplicateOpenIndex == -1 && duplicateClosedIndex == -1) {

                    //Algo - assign the child a heuristic value
                    if (heurChoice == 't')
                        heurValue = currentChild.depth + tilesOutOfPlace(currentChild.tileState);
                    else if (heurChoice == 'm')
                        heurValue = currentChild.depth + manhattanDistance(currentChild.tileState);
                    else
                        heurValue = currentChild.depth + heuristicH(currentChild.tileState);

                    currentChild.heuristic = heurValue;

                     cout << currentChild.index << ", ";

                     //Algo - add the child to open 
                    currentChild.discovered = true;
                    openBestFSList.push(currentChild);
                    nodeList.push_back(currentChild);
                }

                if (duplicateOpenIndex > -1) //Algo - If child is already on open 
                { 

                    //Algo - if new child was reached by a shorter path
                    if (currentChild.heuristic < nodeList[duplicateOpenIndex].heuristic) { 

                        //Algo - Then give the state on open the shorter path
                        //Note to self: The reason you pushed the child instead of adjusting the path is because, it's too complex
                        //to try to pop and push the pq until the duplicate child is found. Instead, adding the same child with a 
                        //dif heuristic and index will be adjusted accordingly in the heap just as though the original heuristics
                        //was updated. 
                        openBestFSList.push(currentChild);
                        nodeList[duplicateOpenIndex].heuristic = currentChild.heuristic;
                    }
                }

                if (duplicateClosedIndex > -1)  //Algo - If the child is already on closed
                { 
                    //Algo if new child was reached by a shorter path
                    if (currentChild.heuristic < closedList[duplicateClosedIndex].heuristic) {
                        //DEV - Algo - REMOVE STATE FROM CLOSED LIST - 
                        //Algo - add the child to open
                        openBestFSList.push(currentChild);
                    }
                }

                numberOfChildren--; //to iterate through children generated
            }

            //Algo - put X on closed
            closedList.push_back(topVertex);
        } //else - not goal state

        //Algo - re-order states on open by heuristic merit (leftmost) - done automatically by min heap

    }// while - open list is not empty
        //Algo - return FAIL
        cout << "Couldn't find the goal state using Best First Search. Exiting program." << endl;
}

//The algorithm is based on pseudocode from pg 102 of Artificial Intelligence 6th edition
void depthFirstSearch(vertex& initialVertex, int maxLevel)
{
    cout << "Depth First Search will be performed" << endl;

    stack<vertex> openDFSList;
    vector<vertex> nodeList;
    vector<vertex> closedList; //Algo - closed:= []


cout << "Number of states/nodes generated: " << initialVertex.index << ", ";
    initialVertex.discovered = true;

    
    nodeList.push_back(initialVertex);
    openDFSList.push(initialVertex); //Algo - open := [Start]

    //Algo - while open != [] do
    while (!openDFSList.empty()) {

        //Algo - remove leftmost state from open, call it X
        vertex topVertex = openDFSList.top();
        openDFSList.pop();

        //Algo - If X is a goal, then return SUCCESS
        if (isGoalState(topVertex)) {
            cout << "GOAL STATE FOUND! Here is the path to the goal state:" << endl;
            printPath(topVertex, nodeList);
            return;
        }
        else //Algo - else, generate children of X
        {

            if (topVertex.depth < maxLevel) {

                int parentIndex = topVertex.index;

                //Algo - generate children of X;
                vector<vertex> childList = generateChildren(topVertex);

                int numberOfChildren = topVertex.numOfChildren;
                //Algo - put X on closed
                closedList.push_back(topVertex);
                vertex currentChild;

                while (numberOfChildren > 0) {

                    currentChild = childList[numberOfChildren - 1];
                    currentChild.index = nodeList.size();
                    //    currentChild.depth = topVertex.depth + 1;
                    currentChild.parentIndex = parentIndex;

                    //Algo - discard children of X if already in open or closed
                    //Algo - put remaining children on left end of open
                    if (!isDuplicateNode(currentChild, nodeList, closedList)) {

                        cout << currentChild.index << ", ";
                        currentChild.discovered = true;
                        nodeList.push_back(currentChild);
                        openDFSList.push(currentChild);
                    }

                    numberOfChildren--;
                }
            }
            else {
                //Algo - return FAIL
                cout << "Couldn't find the goal state within this level. Exiting program." << endl;
                return;
            }
        }
    }
}

//The algorithm is based on pseudocode from pg 100 of Artificial Intelligence 6th edition
void breadthFirstSearch(vertex& initialVertex)
{
    cout << "Breadth First Search will be performed" << endl;
    queue<vertex> openBFSList;
    vector<vertex> nodeList;
    vector<vertex> closedList; //closed:= []


cout << "Number of states/nodes generated: " << initialVertex.index << ", ";


    initialVertex.discovered = true;

    
    nodeList.push_back(initialVertex);
    openBFSList.push(initialVertex);

    while (!openBFSList.empty()) {

        vertex topVertex = openBFSList.front();
        openBFSList.pop();

        if (isGoalState(topVertex)) {
            cout << "GOAL STATE FOUND! Here is the path to the goal state:" << endl;
            printPath(topVertex, nodeList);
            return;
        }
        else {

            int parentIndex = topVertex.index;

            // generate children of X;
            vector<vertex> childList = generateChildren(topVertex);

            int numberOfChildren = topVertex.numOfChildren;

            closedList.push_back(topVertex);
            vertex currentChild;

            while (numberOfChildren > 0) {

                currentChild = childList[numberOfChildren - 1];
                currentChild.index = nodeList.size();
                //  currentChild.depth = topVertex.depth + 1;
                currentChild.parentIndex = parentIndex;

                if (!isDuplicateNode(currentChild, nodeList, closedList)) {

                    cout << currentChild.index << ", ";
                    currentChild.discovered = true;
                    nodeList.push_back(currentChild);
                    openBFSList.push(currentChild);
                }

                numberOfChildren--;
            }
        }
    }
    cout << "Couldn't find the goal state using Bread First Search. Exiting program." << endl;
}

#endif
