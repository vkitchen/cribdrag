#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <editline/readline.h>
#include "file.h"

char usage[] = "\
usage:\n\
  %s [cipher] [cipher]\n\
";

size_t clen;
char *cipher, *c1, *c2;

void insert(size_t pos, char *word)
	{
	size_t wordlen = strlen(word);
	for (size_t i = 0; i < wordlen; i++)
		{
		c1[pos+i] = word[i];
		c2[pos+i] = cipher[pos+i] ^ word[i];
		}
	}

void drag(char *word)
	{
	int wordlen = strlen(word);
	for (size_t pos = 0; pos < clen - wordlen; pos++)
		{
		// try insert
		for (int i = 0; i < wordlen; i++)
			{
			char c = cipher[pos+i] ^ word[i];
			if (!(isalpha(c) || c == ' ' || c == '.' || c == ',' || c == '\''))
				goto OUTER;
			}
		insert(pos, word);
		OUTER: ;
		}
	}

void print_result()
	{
	for (size_t i = 0; i < clen; i++)
		printf("%c", c1[i] ? c1[i] : '.');
	printf("\n\n");
	for (size_t i = 0; i < clen; i++) 
		printf("%c", c2[i] ? c2[i] : '.');
	printf("\n");
	}

int main(int argv, char **argc)
	{
	if (argv != 3)
		{
		fprintf(stderr, usage, argc[0]);
		exit(1);
		}

	clen = file_slurp(argc[1], &c1);
	size_t len2 = file_slurp(argc[2], &c2);
	if (len2 < clen)
		clen = len2;

	cipher = (char *)malloc(clen);

	for (size_t i = 0; i < clen; i++)
		cipher[i] = c1[i] ^ c2[i];

	for (;;)
		{
		memset(c1, '\0', clen);
		memset(c2, '\0', clen);

		char *word = readline("> ");
		if (word == NULL)
			break;

		add_history(word);

		drag(word);

		print_result();

		free(word);
		}
	}
