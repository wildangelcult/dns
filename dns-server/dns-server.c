#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
	int sv, px;
	int len;
	socklen_t socklen;
	struct sockaddr_in svaddr, pxaddr, claddr;
	char buf[65535];
	FILE *fw;


	sv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	px = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	svaddr.sin_family = AF_INET;
	svaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	svaddr.sin_port = htons(53);

	pxaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "1.1.1.1", &pxaddr.sin_addr.s_addr);
	pxaddr.sin_port = htons(53);

	bind(sv, (struct sockaddr*)&svaddr, sizeof(svaddr));

	fw = fopen("dns.log", "wb");

	for (;;) {
		socklen = sizeof(claddr);
		if ((len = recvfrom(sv, buf, sizeof(buf), 0, (struct sockaddr*)&claddr, &socklen)) == -1) {
			perror("recvfrom()");
			return 1;
		}

		if (sendto(px, buf, len, 0, (struct sockaddr*)&pxaddr, sizeof(pxaddr)) == -1) {
			perror("sendto()");
			return 1;
		}

		socklen = sizeof(pxaddr);
		if ((len = recvfrom(px, buf, sizeof(buf), 0, (struct sockaddr*)&pxaddr, &socklen)) == -1) {
			perror("recvfrom()");
			return 1;
		}

		fwrite(buf, 1, len, fw);
		fflush(fw);

		if (sendto(sv, buf, len, 0, (struct sockaddr*)&claddr, sizeof(claddr)) == -1) {
			perror("sendto()");
			return 1;
		}
	}

	close(sv);
	fclose(fw);
	return 0;
}
