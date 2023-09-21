#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char* name;
	int index;
}Sommet;

typedef struct{
	int** adjMatrix;
	int ordre;
	Sommet* sommets;
}Graph;

Sommet initSommet(char* nom, int index){
	Sommet sommet;
	sommet.name = (char*)malloc((strlen(nom)+1)*sizeof(char));
	strcpy(sommet.name, nom);
	sommet.index = index;

	return sommet;
}

void initGraph(int ordre, Graph* graph){
	graph->ordre = ordre;
	graph->adjMatrix = (int**)malloc(ordre*sizeof(int*));
	for(int i = 0; i < ordre; i++){
		graph->adjMatrix[i] = (int*)calloc(ordre,sizeof(int));
	}
	graph->sommets = (Sommet*)malloc(ordre*sizeof(Sommet));
}

void fillGraph(Graph* graph, char* filename){
	FILE *file = fopen(filename, "r");
	if(file == NULL){
        printf("Impossible d'ouvrir le fichier\n");
        exit(1);
    }
	char ligne[100];

	int ordre = fgetc(file);
	initGraph(ordre, graph);

	// Sauter une ligne
	fgets(ligne, sizeof(ligne), file);

	// Lire la première ligne
	fgets(ligne, sizeof(ligne), file);

	// récupère les nom des personnes séparées par des virgules
	char *token = strtok(ligne, ",");
	int index = 0;
	while (token != NULL) {
		graph->sommets[index] = initSommet(token, index);
		// Appel suivant pour obtenir le prochain token
		token = strtok(NULL, ",");
		index++;
	}

    while(fgets(ligne, sizeof(ligne), file)!= NULL){
		int x, y;
        if (sscanf(ligne, "(%d,%d)", &x, &y) == 2) {
            graph->adjMatrix[y][x] = 1;
        } else {
            printf("Erreur de format dans la ligne du fichier.\n");
        }
    }

	fclose(file);
}

void printDependance(Graph* graph){
	for(int x = 0; x < graph->ordre; x++){
		for(int y = 0; y < graph->ordre; y++){
			if(graph->adjMatrix[y][x] == 1){
				printf("%s influence %s\n", graph->sommets[x].name, graph->sommets[y].name);
			}
		}
	}
}	

int main(int argc, char const *argv[])
{
	Graph graph;

	char filename[100];

	scanf("%s", &filename);
	fillGraph(&graph, filename);

	printDependance(&graph);

	return 0;
}