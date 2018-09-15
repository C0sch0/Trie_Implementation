#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


// Esta linea permite usar MAX_LENGTH como una constante en el programa
// Uso 101 para considerar el caracter que indica el fin de un string


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Modo de uso: ./autocomplete [database.txt] [queries.txt] [output.txt]\n");
		return 0;
	}
	FILE *database = fopen(argv[1], "r");
	FILE *queries  = fopen(argv[2], "r");
	FILE *output   = fopen(argv[3], "w");
	if (!database || !queries || !output)
	{
		printf("¡Error abriendo los archivos!");
		return 2;
	}

	// Create root
	Trie* root = trie_init();
	int n;
	fscanf(database, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		int freq, length;
		fscanf(database, "%d %d ", &freq, &length);
		//printf("freq = %d, length = %d\n", freq, length);
		char chars[MAX_LENGTH];
		fgets(chars, MAX_LENGTH, database);
		size_t largo = strlen(chars);
		chars[largo-1] = '\0';
		//printf("%s\n", chars);
		insert(root, chars, freq, length);

	}
	int n_queries;
	fscanf(queries, "%d", &n_queries);
	for (int i = 0; i < n_queries; i++)
	{
		int length;
		char content[MAX_LENGTH];
		fscanf(queries, "%d ", &length);
		if (length == 0) {
			strcpy(content, "");
		}
		else {
			fgets(content, MAX_LENGTH, queries);
			size_t size = strlen(content);
			content[size - 1] = '\0';
		}
		//printf("%d \n", length);
		//printf("%s \n", content);

		char resultado_busqueda[MAX_LENGTH];
		strcpy(resultado_busqueda, suggest(root, content, length));
		fprintf(output, "%s\n", resultado_busqueda);
	}

	destroy_all(root);
	fclose(database);
	fclose(queries);
	fclose(output);
	return 0;
}
