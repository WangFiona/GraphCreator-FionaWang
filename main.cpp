#include <iostream>
#include <cstring>

using namespace std;

/*
 * Author: Fiona Wang
 * Date: June 7th 2022
 * This is the main class for the graph creater program
 * The user can add or remove vertices and edges, and use Dijkstra's algorithms
 */

//Struct to hold data for the Dijkstra's Algorithm
struct table {
  char label;
  int shortest;
  char prev;
};

//Initializing functions
bool isEmpty(int count, char unvisited[]);
int findSmallest(table Table[], int count, char unvisited[]);
int locate(char find, char vertices[], int count);

int main(){
  //Initializing the adjacency matrix and other variabls
  int graph[20][20]; //[column][row]
  char vertices[20];
  int vertexCount = 0;

  //Emptying out the arrays
  for(int i=0; i<20; i++){
    vertices[i] = '\0';
    for(int j=0; j<20; j++){
      graph[i][j] = 0;
    }
  }

  //Ask for user input
  char command[15];
  bool running = true;
  cout << "Enter a command:" << endl;
  cout << "'addV' (to add a vertex) or 'addE' (to add an edge)" << endl;
  cout << "'removeV' (to remove a vertex) or 'removeE' (to remove an edge)" << endl;
  cout << "'print' (to print the matrix), 'find' (to find the shortest path), or 'quit'" << endl;
  while(running){
    cin >> command;

    //Allow upper and lower case commands
    for(int i=0; i < strlen(command); i++) {
      command[i] = toupper(command[i]);
    }

    //If adding a vertex
    if(strcmp(command, "ADDV") == false){
      //Ask for a label
      cout << "Enter a character label for the new vertex (eg. A, B, or C)" << endl;
      char label;
      cin >> label;
      bool used = false;
      //Check if the label has already been used
      for(int i=0; i<20; i++){
	if(vertices[i] == label){
	  cout << "This label has already been used" << endl;
	  used = true;
	}
      }

      //If not used, add it to the list of vertices
      if(!used){
	vertexCount++;
	for(int i=0; i<20; i++){
	  if(vertices[i] == '\0'){
	    vertices[i] = label;
	    break;
	  }
	}
      }
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    //If adding an edge
    else if(strcmp(command, "ADDE") == false){
      //Ask for the vertices that the user wants to connect
      cout << "Enter the two vertices you want to connect (eg. A E)" << endl;
      char v1;
      char v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;
      int weight = 0;

      //Check if those vertices exist
      if(v1 != v2){
	for(int i=0; i<20; i++){
	  if(vertices[i] == v1){
	    v1Index = i;
	  }
	  else if(vertices[i] == v2){
	    v2Index = i;
	  }
	}

	//If they both exist, ask for the weight of the edge
	if(v1Index != -1 && v2Index != -1){
	  cout << "Enter the weight of the edge" << endl;
	  cin >> weight;

	  //Add the edge to the matrix
	  graph[v2Index][v1Index] = weight;
	}
	else{ //If the vertices were missing
	  cout << "One of those vertices were not found!" << endl;
	}
      }
      //Two of the vertices were the same
      else
	cout << "You entered two of the same vertices" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    //If printing the matrix
    else if(strcmp(command, "PRINT") == false){
      //Print out the label of the vertices
      if(vertexCount > 0){
	for(int i=0; i<20; i++){
	  if(vertices[i]){
	    cout << "\t" << vertices[i];
	  }
	}
	cout << endl;
	//Print out the label and the corresponding edges
	for(int i=0; i<20; i++){
	  if(vertices[i]){
	    cout << vertices[i] << "\t";
	  }
	  if(vertices[i]){
	    for(int j=0; j<20; j++){
	      if(j < vertexCount)
		cout << graph[j][i] << "\t";
	    }
	    cout << endl;
	  }
	}
      }
      //If there is nothing in the graph
      else
	cout << "The graph is empty!" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    //If removing a vertex
    else if(strcmp(command, "REMOVEV") == false){
      //Ask for the label the user wants to remove
      cout << "Enter the vertex you want to remove (eg. A, B, or C)" << endl;
      char remove;
      cin >> remove;
      bool found = false;
      //Find the corresponding vertex
      for(int i=0; i<20; i++){
	if(vertices[i] == remove){ //Once found
	  found = true;
	  //Delete and shift over the vertex labels
	  for(int j=i; j<20; j++){
	    vertices[j] = vertices[j+1];
	  }
	  //Shifting the rows and columns in the matrix
	  for(int h=i; h<vertexCount; h++){
	    for(int j=0; j<vertexCount; ++j){
	      graph[j][h] = graph[j][h+1]; //Rows
	    }
	    for(int y=0; y<vertexCount; ++y){
	      graph[h][y] = graph[h+1][y]; //Columns
	    }
	  }
	  cout << "Removed!" << endl;
	  vertexCount--;
	}
      }

      //If the vertex does not exist
      if(!found)
	cout << "This vertex was not found" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    //If removing an edge
    else if(strcmp(command, "REMOVEE") == false){
      cout << "Enter the two vertices who's edge you want to remove (eg. A E)" << endl;
      char v1, v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;

      //Check if the vertices exists
      if(v1 != v2){
        for(int i=0; i<20; i++){
          if(vertices[i] == v1){
            v1Index = i;
          }
          else if(vertices[i] == v2){
            v2Index = i;
          }
	}
	//Set the edge to zero
	if(v1Index != -1 && v2Index != -1){
          graph[v2Index][v1Index] = 0;
	  cout << "Removed!" << endl;
	}
	//If the vertices were not found
        else{
          cout << "One of those vertices were not found!" << endl;
        }
      }
      //If both labels are the same
      else
        cout << "You entered two of the same vertices" << endl;
      
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    //Using the Dijkstra's algorithm
    else if(strcmp(command, "FIND") == false){
      //Create the table to keep track of things
      table Table[vertexCount];
      char visited[vertexCount];
      char unvisited[vertexCount];
      //Ask for the two vertex labels
      cout << "Enter the two vertices you want to find the path between (eg. A E)" << endl;

      char v1, v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;
      int visitedCount = 0;

      //Check if the vertices exist and are not the same
      if(v1 != v2){
        for(int i=0; i<20; i++){
          if(vertices[i] == v1){
            v1Index = i;
          }
          else if(vertices[i] == v2){
            v2Index = i;
          }
        }
        if(v1Index != -1 && v2Index != -1){
	  //Empty out the arrays and set the vertex labels in the table
	  for(int i=0; i<20; i++){
	    if(vertices[i]){
	      visited[i] = '\0';
	      unvisited[i] = vertices[i];
	      Table[i].label = vertices[i];
	      if(vertices[i] == v1)
		Table[i].shortest = 0;
	      else
		Table[i].shortest = 100000;
	      Table[i].prev = '\0';
	    }
	  }

	  //Start with the starting vertex and set the table accordingly
	  for(int t=0; t<20; t++){
	    if(graph[t][v1Index] != 0){
	      Table[t].shortest = graph[t][v1Index]; //Set the distance
	      Table[t].prev = vertices[v1Index]; //Set the previous 
	    }
	  }
	  //Update the visited and unvisited tables
	  unvisited[v1Index] = '\0';
	  visited[visitedCount] = vertices[v1Index];
	  visitedCount++;

	  //Go through the rest of the vertices (checking the next smallest)
	  while(visitedCount <= vertexCount && !isEmpty(vertexCount, unvisited)){
	    int index = findSmallest(Table, vertexCount, unvisited); //Find the index of the vertex
	    for(int t=0; t<20; t++){
	      if(graph[t][index] != 0 && unvisited[t]){
		int shortest = Table[index].shortest + graph[t][index]; //Find the new distance
		if(shortest < Table[t].shortest){ //Check if the table should be updated
		  Table[t].shortest = shortest;
		  Table[t].prev = vertices[index];
		}
	      }
	    }
	    //Update the visited and unvisited tables
	    unvisited[index] = '\0';
	    visited[visitedCount] = vertices[index];
	    visitedCount++;
	  }
	  //Print out of there is a path
	  if(Table[v2Index].shortest >= 100000){
	    cout << "There is no path between those vertices!" << endl;
	  }
	  else{
	    //Print out the shortest path
	    cout << "Shortest Path: ";
	    char path[vertexCount];
	    for(int i=0; i<vertexCount; i++){
	      path[i] = '\0';
	    }

	    int pathCount = 0;
	    int index = v2Index;
	    while(Table[index].shortest != 0){
	      path[pathCount] = vertices[index];
	      pathCount++;
	      index = locate(Table[index].prev, vertices, vertexCount);
	    }
	    path[pathCount] = vertices[v1Index];
            pathCount++;

	    //Print out the array
	    for(int i=pathCount-1; i>0; i--){
	      cout << path[i] << " -> ";
	    }
	    cout << vertices[v2Index]  << endl;

	    //Print out the total weight
	    cout << "Total Weight: "  << Table[v2Index].shortest << endl;
	  }
        }
        else{
          cout << "One of those vertices were not found!" << endl;
        }
      }
      else
        cout << "You entered two of the same vertices" << endl;
      
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "QUIT") == false){
      running = false;
    }
    else{
      cout << "Please enter a valid command:" << endl;
    }
  }
  
  return 0;
}

//Function to check if every vertex has been visited
bool isEmpty(int count, char unvisited[]){
  for(int i=0; i<count; i++){
    if(unvisited[i])
      return false;
  }
  return true;
}

//Function to look for the next smallest distance in the table
int findSmallest(table Table[], int count, char unvisited[]){
  int smallest = 10000;
  int index=0;
  for(int i = 0; i<count; i++){
    if(Table[i].shortest < smallest && unvisited[i]){
      smallest = Table[i].shortest;
      index = i;
    }
  }
  return index;
}

//Function to locate the index of a vertex
int locate(char find, char vertices[], int count){
  for(int i=0; i<count; i++){
    if(vertices[i] == find){
      return i;
    }
  }
  return 0;
}
