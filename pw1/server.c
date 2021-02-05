#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define CHUNK_SIZE 8192

const char ACK[1] = {69};

int main()
{
	int ss;
	struct sockaddr_in ad;
	socklen_t ad_length = sizeof(ad);

	// create the socket
	ss = socket(AF_INET, SOCK_STREAM, 0);

	// bind the socket to port 12345
	memset(&ad, 0, sizeof(ad));
	ad.sin_family = AF_INET;
	ad.sin_addr.s_addr = INADDR_ANY;
	ad.sin_port = htons(12345);
	bind(ss, (struct sockaddr *)&ad, ad_length);

	// then listen
	listen(ss, 0);

	char chunk[CHUNK_SIZE];
	while (1) {
		int cli = accept(ss, (struct sockaddr *)&ad, &ad_length);
		if (fork())
			continue;

		char fsize[10];
		recv(cli, fsize, 10, 0);
		int size;
		sscanf(fsize, "%d", &size);

		char fname[16];
		recv(cli, fname, 16, 0);
		puts(fname);
		FILE *f = fopen(fname, "w");

		int len;
		while (len = recv(cli, chunk, CHUNK_SIZE, 0)) {
			fwrite(chunk, 1, len, f);
			send(cli, ACK, 1, 0);
		}

		fclose(f);
		close(cli);
		return 0;
	}
}
