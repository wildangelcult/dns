#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char dns[256], *host, *p;
	int lock = 0, i;
	size_t len;

	if (argc != 2) {
		return 1;
	}

	len = strlen(argv[1]);
	if (len > 255) {
		return 2;
	}

	host = malloc(len + 2);
	host[0] = 0;

	memcpy(host, argv[1], ++len);
	strcat(host, ".");

	memset(dns, 0, 256);
	p = dns;
	for (i = 0; i < len; ++i) {
		printf("%d %d\n", i, lock);
		if (host[i] == '.') {
			printf("dot\n");
			*p++ = i - lock;
			for (; lock < i; ++lock)
				*p++ = host[lock];
			++lock;
		}
	}
	*p++ = 0;

	printf("%s\n", dns);
	return 0;
}
