#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <common.h>

int get_client_local_socket();

int main(int argc, char **argv) {

	//if (argc != 2)
	//{
	//	perror("Please use: client path_to_file\n");
	//	exit(3);
	//}

	int bud_size = 1024*1000;
	char buf[bud_size];
	char message[1024];

	int sock = get_client_local_socket();
	if(sock < 0)
	{
		perror("Error create socket");
		exit(1);
	}

	memset(message,'\0',1024);
	printf("Enter path: ");
	scanf("%s", message);
	printf("Connected to server. Sending filename...\n");
	send(sock, message, strlen(message), 0);

	printf("Server response:\n");
	int num_received_data = recv(sock, buf, bud_size, 0);
	printf("%s", buf);

	if(num_received_data < 0)
	{
		perror("Failure to receive data");
		exit(3);
	}

	close(sock);
	return 0;
}

int get_client_local_socket() {
	int sock;
	struct sockaddr_un remote;

	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sock < 0) {
		return -1;
	}

	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path, SOCK_PATH);
	int len = strlen(remote.sun_path) + sizeof(remote.sun_family);

	if (connect(sock, (struct sockaddr *) &remote, len) == -1) {
		perror("Failure to connect to server");
		return -2;
	}
	return sock;
}

