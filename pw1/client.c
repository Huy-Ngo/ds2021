#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK_SIZE 8192

int main(int argc, char *argv[])
{
	/* TCP/IPv4 */
	struct addrinfo hints = {
		.ai_socktype = SOCK_STREAM,
		.ai_family = AF_INET,
	};
	struct addrinfo *res;

	/* No error checking, sorry!  Use GDB if needed. */
	getaddrinfo(NULL, "12345", &hints, &res);
	int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	connect(sockfd, res->ai_addr, res->ai_addrlen);

	if (argc < 2)
		return 1;

	const char *fname = argv[1];
	char fsize[10];
	struct stat st;
	stat(fname, &st);

	sprintf(fsize, "%ld", st.st_size);
	send(sockfd, fsize, 10, 0);

	char name_trunc[16];
	strncpy(name_trunc, fname, 15);
	name_trunc[15] = 0;
	send(sockfd, name_trunc, 16, 0);

	FILE *f = fopen(fname, "r");
	char chunk[CHUNK_SIZE];
	int len;
	while (len = fread(chunk, 1, CHUNK_SIZE, f)) {
		send(sockfd, chunk, len, 0);
		/* Avoid filling kernel buffer */
		recv(sockfd, chunk, 1, 0);
	}

	fclose(f);
	freeaddrinfo(res);
	return 0;
}
