#include <iostream>
#include <cstring>

using namespace std;

/*
 * Author: Fiona Wang
 * Date: June 7th 2022
 * This is the main class for the graph creater program
 * The user can add or remove vertices and edges, and use Dijkstra's algorithms
 */

struct table {
  char label;
  int shortest;
  char prev;
};

bool isEmpty(int count, char unvisited[]);
int findSmallest(table Table[], int count, char unvisited[]);
int printPath(char (&path)[], int count, table Table[], int index, char vertices[]);
int locate(char find, char vertices[], int count);

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
  cout << "Enter a command:" << endl;
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
	for(int i=0; i<20; i++){
	  if(vertices[i] == '\0'){
	    vertices[i] = label;
	    break;
	  }
	}
	//vertices[vertexCount] = label;
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
	  cout << "Enter the weight of the edge" << endl;
	  cin >> weight;
	  
	  graph[v2Index][v1Index] = weight;
	}
	else{
	  cout << "One of those vertices were not found!" << endl;
	}
      }
      else
	cout << "You entered two of the same vertices" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "PRINT") == false){
      if(vertexCount > 0){
	for(int i=0; i<20; i++){
	  if(vertices[i]){
	    cout << "\t" << vertices[i];
	  }
	}
	cout << endl;
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
      else
	cout << "The graph is empty!" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "REMOVEV") == false){
      cout << "Enter the vertex you want to remove" << endl;
      char remove;
      cin >> remove;
      bool found = false;
      for(int i=0; i<20; i++){
	if(vertices[i] == remove){
	  found = true;
	  vertexCount--;
	  vertices[i] = '\0';
	  for(int j=0; j<20; j++){
	    graph[i][j] = 0;
	    graph[j][i] = 0;
	  }
	  cout << "Removed!" << endl;
	}
      }

      if(!found)
	cout << "This vertex was not found" << endl;
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "REMOVEE") == false){
      cout << "Enter the two vertices who's edge you want to remove (eg. A E)" << endl;
      char v1, v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;

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
          graph[v2Index][v1Index] = 0;
	  cout << "Removed!" << endl;
	}
        else{
          cout << "One of those vertices were not found!" << endl;
        }
      }
      else
        cout << "You entered two of the same vertices" << endl;
      
      cout << "Enter another command (addV, addE, removeV, removeE, print, find, or quit)" << endl;
    }
    else if(strcmp(command, "FIND") == false){
      table Table[vertexCount];
      char visited[vertexCount];
      char unvisited[vertexCount];
      cout << "Enter the two vertices you want to find the path between (eg. A E)" << endl;

      char v1, v2;
      cin >> v1;
      cin >> v2;
      int v1Index = -1;
      int v2Index = -1;
      int visitedCount = 0;

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

	  for(int t=0; t<20; t++){
	    if(graph[t][v1Index] != 0){
	      Table[t].shortest = graph[t][v1Index];
	      Table[t].prev = vertices[v1Index];
	    }
	  }
	  unvisited[v1Index] = '\0';
	  visited[visitedCount] = vertices[v1Index];
	  visitedCount++;

	  while(visitedCount <= vertexCount && !isEmpty(vertexCount, unvisited)){
	    int index = findSmallest(Table, vertexCount, unvisited);
	    for(int t=0; t<20; t++){
	      if(graph[t][index] != 0 && unvisited[t]){
		int shortest = Table[index].shortest + graph[t][index];
		if(shortest < Table[t].shortest){
		  Table[t].shortest = shortest;
		  Table[t].prev = vertices[index];
		}
	      }
	    }
	    unvisited[index] = '\0';
	    visited[visitedCount] = vertices[index];
	    visitedCount++;
	  }
	  if(Table[v2Index].shortest >= 100000){
	    cout << "There is no path between those vertices!" << endl;
	  }
	  else{
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
	    
	    for(int i=pathCount-1; i>0; i--){
	      cout << path[i] << " -> ";
	    }
	    cout << vertices[v2Index]  << endl;
	    
	    cout << "Weight: "  << Table[v2Index].shortest << endl;
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

bool isEmpty(int count, char unvisited[]){
  for(int i=0; i<count; i++){
    if(unvisited[i])
      return false;
  }
  return true;
}

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

int printPath(char (&path)[], int count, table Table[], int index, char vertices[]){
  int pathCount = 0;
  while(Table[index].shortest != 0){
    path[pathCount] = Table[index].prev;
    pathCount++;
    index = locate(Table[index].prev, vertices, count);
  }
  return pathCount;
}

int locate(char find, char vertices[], int count){
  for(int i=0; i<count; i++){
    if(vertices[i] == find){
      return i;
    }
  }
  return 0;
}
