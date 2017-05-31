#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>
#include <common.h>

char* getContent(char* filename);
int isFile(char *location);

int main(int argc, char **argv) {
	int sock, listener;
	struct sockaddr_un local;
	char error[] = "Failure to open non existent file\n";

	char buf[1024];

	listener = socket(AF_UNIX, SOCK_STREAM, 0);
	if (listener == -1) {
		perror("Error create socket");
		exit(1);
	}

	local.sun_family = AF_UNIX;
	strcpy(local.sun_path, SOCK_PATH);
	unlink(local.sun_path);
	int len = strlen(local.sun_path) + sizeof(local.sun_family);

	if (bind(listener, (struct sockaddr *) &local, len) == -1)
	{
		perror("Error bind address");
		exit(2);
	}

	// 5 - value of queue
	listen(listener, 5);

	while (1)
	{
		sock = accept(listener, NULL, NULL);
		if (sock < 0) {
			perror("Error accept");
			exit(3);
		}

		memset(buf, '\0', 1024);
		int bytes_read = recv(sock, buf, 1023, 0);
		if (bytes_read <= 0)
		{
			sleep(1);
			continue;
		}

		if (!isFile(buf)) {
			send(sock, error, strlen(error), 0);
			continue;
		}

		printf("Reading the file: %s\n", buf);
		char* file_content = getContent(buf);

		printf("Sending data to client\n");
		send(sock, file_content, strlen(file_content), 0);
	}

	close(sock);
	return 0;
}
