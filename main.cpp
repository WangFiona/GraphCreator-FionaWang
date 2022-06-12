#include <iostream>
#include <cstring>

using namespace std;

/*
 * Author: Fiona Wang
 * Date: June 7th 2022
 * This is the main class for the graph creater program
 * The user can add or remove vertices and edges, and use Dijkstra's algorithms
 */

int main(){
  int graph[20][20]; //[column][row]
  char vertices[20];
  int vertexCount = 0;
  
  for(int i=0; i<20; i++){
    vertices[i] = '\0';
    for(int j=0; j<20; j++){
      graph[i][j] = 0;
    }
  }

  char command[15];
  bool running = true;

  cout << "Enter a command" << endl;
  cout << "'addV' (to add a vertex) or 'addE' (to add an edge)" << endl;
  cout << "'removeV' (to remove a vertex) or 'removeE' (to remove an edge)" << endl;
  cout << "'print' (to print the matrix), 'find' (to find the shortest path), or 'quit')" << endl;
  while(running){
    cin >> command;

    for(int i=0; i < strlen(command); i++) {
      command[i] = toupper(command[i]);
    }

    if(strcmp(command, "ADDV") == false){
      cout << "Enter a character label for the new vertex:" << endl;
      char label;
      cin >> label;
      bool used = false;
      for(int i=0; i<20; i++){
	if(vertices[i] == label){
	  cout << "This label has already been used" << endl;
	  used = true;
	}
      }

      if(!used){
	vertexCount++;
	vertices[vertexCount] = label;
      }
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "ADDE") == false){
      cout << "Enter the two vertices you want to connect (eg. A E)" << endl;
      char v1;
      char v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;
      int weight = 0;
      
      for(int i=0; i<20; i++){
	if(vertices[i] == v1){
	  v1Index = i;
	}
	else if(vertices[i] == v2){
	  v2Index = i;
	}
      }

      if(v1Index != -1 && v2Index != -1){
	cout << "Enter the weight of the edge" << endl;
	cin >> weight;

	graph[v2Index][v1Index] = weight;
      }
      else{
	cout << "One of those vertices were not found!" << endl;
      }
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "PRINT") == false){
      for(int i=0; i<20; i++){
	if(vertices[i]){
	  cout << "\t" << vertices[i];
	}
      }
      cout << endl;
      for(int i=1; i<=vertexCount; i++){
	if(vertices[i]){
	  cout << vertices[i] << "\t";
	}
	for(int j=1; j<20; j++){
	  if(j <= vertexCount)
	    cout << graph[j][i] << "\t";
	}
	cout << endl;
      }
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "REMOVEV") == false){
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "REMOVEE") == false){
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "FIND") == false){
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
