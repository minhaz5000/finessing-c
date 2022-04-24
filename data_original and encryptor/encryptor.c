
/*	Encryptor for encrypting the data files
	Run encryptor encrpyt <file> to encrypt
	and encryptor decrpyt <file> to decrypt
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char *buffer, size_t size)
{
    unsigned flag = size % 2;
    for (size_t i = 0; i < size; ++i)
    {
        buffer[i] ^= 'y';
        buffer[i] ^= flag;
    }
}

void decrypt(char *buffer, size_t size)
{
    unsigned flag = size % 2;
    for (size_t i = 0; i < size; ++i)
    {
        buffer[i] ^= flag;
        buffer[i] ^= 'y';
    }
}

int main(int argc, char *argv[])
{
	char *buffer = NULL;
	size_t buffer_length;
	FILE *fp = fopen(argv[2], "r+");
	if (!fp)
	{
		fprintf(stderr, "Failed to load file %s\n", argv[2]);
		return -1;
	}
	if (fseek(fp, 0L, SEEK_END) == 0)
	{
		buffer_length = ftell(fp);
	}
	else
	{
		return -1;
	}
	buffer = malloc(sizeof(char) * (buffer_length + 1));
	rewind(fp);
	fread(buffer, sizeof(char), buffer_length, fp);
	rewind(fp);
	if (strcmp(argv[1], "decrypt") == 0)
	{
		decrypt(buffer, buffer_length);
		fwrite(buffer, sizeof(char), buffer_length, fp);
		printf("Decrypted %zu characters in %s\n", buffer_length, argv[2]);
	}
	if (strcmp(argv[1], "encrypt") == 0)
	{
		encrypt(buffer, buffer_length);
		fwrite(buffer, sizeof(char), buffer_length, fp);
		printf("Encrypted %zu characters in %s\n", buffer_length, argv[2]);
	}
	free(buffer);
	fclose(fp);
	return 0;
}