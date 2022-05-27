#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "dns.h"


static char* dns_readName(dns_msg_t* msg, uint8_t *buf, uint8_t **origcurr) {
	size_t i, len;
	uint8_t *curr, n, j;
	char *name, *pname;
	int jumped = 0;

	name = malloc(DNS_MAX_DOMAIN);
	pname = name;
	curr = *origcurr;
	name[0] = 0;

	while (*curr) {
		if (*curr & 0xc0 == 0xc0) {
			curr = buf + ntohs(*((uint16_t*)curr)++) - 1;
			jumped = 1;
		} else {
			*pname++ = *curr;
		}

		++curr;

		if (!jumped) {
			++*origcurr;
		}
	}

	*pname = 0;

	if (jumped) {
		*origcurr += 2
	}

	len = strlen(name);
	for (i = 0; i < len; ++i) {
		n = name[i];
		for (j = 0; j < n; ++i, ++j) {
			name[i] = name[i+1];
		}
		name[i] = '.';
	}
	name[i-1] = 0;

	return name;
}

dns_msg_t* dns_decode(uint8_t *buf, size_t size) {
	uint16_t	i;
	uint8_t		*curr, n;
	dns_msg_t	*msg = malloc(sizeof(dns_msg_t));

	msg->intern = NULL;

	msg->id = ntohs(*((uint16_t*)curr)++);

	n = *curr++;
	msg->qr = (n & 0x80) >> 7;
	msg->opcode = (n & 0x78) >> 3;
	msg->aa = (n & 0x4) >> 2;
	msg->tc = (n & 0x2) >> 1;
	msg->rd = (n & 0x1);

	n = *curr++;
	msg->ra = (n & 0x80) >> 7;
	msg->z = (n & 0x70) >> 4;
	msg->rcode = (n & 0xf);

	msg->qdcount = ntohs(*((uint16_t*)curr)++);
	msg->ancount = ntohs(*((uint16_t*)curr)++);
	msg->nscount = ntohs(*((uint16_t*)curr)++);
	msg->arcount = ntohs(*((uint16_t*)curr)++);

	msg->qd = malloc(sizeof(dns_qd_t) * msg->qdcount);
	msg->an = malloc(sizeof(dns_rr_t) * msg->ancount);
	msg->ns = malloc(sizeof(dns_rr_t) * msg->nscount);
	msg->ar = malloc(sizeof(dns_rr_t) * msg->arcount);

	for (i = 0; i < msg->qdcount; ++i) {

	}

	return msg;
}
