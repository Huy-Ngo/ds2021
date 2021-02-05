#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

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

	char buffer[100];
	while (1) {
		printf("client>");
		scanf("%s", buffer);
		send(sockfd, buffer, strlen(buffer), 0);

		recv(sockfd, buffer, sizeof(buffer), 0);
		printf("server says: %s\n", buffer);
	}

	freeaddrinfo(res);
	return 0;
}
