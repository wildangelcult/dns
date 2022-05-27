#ifndef __DNS_H
#define __DNS_H
//https://datatracker.ietf.org/doc/html/rfc1035

#include <stdint.h>

#define DNS_MAX_DOMAIN 256

typedef enum dns_qtype_e {
	DNS_QT_A		=	1,
	DNS_QT_NS		=	2,
	DNS_QT_MD		=	3,
	DNS_QT_MF		=	4,
	DNS_QT_CNAME		=	5,
	DNS_QT_SOA		=	6,
	DNS_QT_MB		=	7,
	DNS_QT_MG		=	8,
	DNS_QT_MR		=	9,
	DNS_QT_NULL		=	10,
	DNS_QT_WKS		=	11,
	DNS_QT_PTR		=	12,
	DNS_QT_HINFO		=	13,
	DNS_QT_MINFO		=	14,
	DNS_QT_MX		=	15,
	DNS_QT_TXT		=	16,
	DNS_QT_RP		=	17,
	DNS_QT_AFSDB		=	18,
	DNS_QT_X25		=	19,
	DNS_QT_ISDN		=	20,
	DNS_QT_RT		=	21,
	DNS_QT_NSAP		=	22,
	DNS_QT_NSAP_PTR		=	23,
	DNS_QT_SIG		=	24,
	DNS_QT_KEY		=	25,
	DNS_QT_PX		=	26,
	DNS_QT_GPOS		=	27,
	DNS_QT_AAAA		=	28,
	DNS_QT_LOC		=	29,
	DNS_QT_NXT		=	30,
	DNS_QT_EID		=	31,
	DNS_QT_NIMLOC		=	32,
	DNS_QT_SRV		=	33,
	DNS_QT_ATMA		=	34,
	DNS_QT_NAPTR		=	35,
	DNS_QT_KX		=	36,
	DNS_QT_CERT		=	37,
	DNS_QT_A6		=	38,
	DNS_QT_DNAME		=	39,
	DNS_QT_SINK		=	40,
	DNS_QT_OPT		=	41,
	DNS_QT_APL		=	42,
	DNS_QT_DS		=	43,
	DNS_QT_SSHFP		=	44,
	DNS_QT_ISECKEY		=	45,
	DNS_QT_RRSIG		=	46,
	DNS_QT_NSEC		=	47,
	DNS_QT_DNSKEY		=	48,
	DNS_QT_DHCID		=	49,
	DNS_QT_NSEC3		=	50,
	DNS_QT_NSEC3PARAM	=	51,
	DNS_QT_TLSA		=	52,
	DNS_QT_SMIMEA		=	53,
	DNS_QT_HIP		=	55,
	DNS_QT_NINFO		=	56,
	DNS_QT_RKEY		=	57,
	DNS_QT_TALINK		=	58,
	DNS_QT_CDS		=	59,
	DNS_QT_CDNSKEY		=	60,
	DNS_QT_OPENPGPKEY	=	61,
	DNS_QT_CSYNC		=	62,
	DNS_QT_ZONEMD		=	63,
	DNS_QT_SVCB		=	64,
	DNS_QT_HTTPS		=	65,
	DNS_QT_SPF		=	99,
	DNS_QT_UINFO		=	100,
	DNS_QT_UID		=	101,
	DNS_QT_GID		=	102,
	DNS_QT_UNSPEC		=	103,
	DNS_QT_NID		=	104,
	DNS_QT_L32		=	105,
	DNS_QT_L64		=	106,
	DNS_QT_LP		=	107,
	DNS_QT_EUI48		=	108,
	DNS_QT_EUI64		=	109,

	DNS_QT_TKEY		=	249,
	DNS_QT_TSIG		=	250,
	DNS_QT_IXFR		=	251,
	DNS_QT_AXFR		=	252,
	DNS_QT_MAILB		=	253,
	DNS_QT_MAILA		=	254,
	DNS_QT_ANY		=	255,
	DNS_QT_URI		=	256,
	DNS_QT_CAA		=	257,
	DNS_QT_AVC		=	258,
	DNS_QT_DOA		=	259,
	DNS_QT_AMTRELAY		=	260,

	DNS_QT_TA		=	32768,
	DNS_QT_DLV		=	32769,

	DNS_QT_PRIVATE		=	65280,
	DNS_QT_UNKNOWN		=	65535,
} dns_qtype_t;

typedef enum dns_qclass_e {
	DNS_QC_IN	=	1,
	DNS_QC_CS	=	2,
	DNS_QC_CH	=	3,
	DNS_QC_HS	=	4,
	DNS_QC_NONE	=	254,
	DNS_QC_ANY	=	255,
	DNS_QC_PRIVATE	=	65280,
	DNS_QC_UNKNOWN	=	65535,
} dns_qclass_t;

typedef enum dns_opcode_e {
	DNS_OP_QUERY	=	0,
	DNS_OP_IQUERY	=	1,
	DNS_OP_STATUS	=	2,
	DNS_OP_NOTIFY	=	4,
	DNS_OP_UPDATE	=	5,
} dns_opcode_t;

typedef enum dns_rcode_e {
	DNS_RC_OKAY		=	0,
	DNS_RC_FORMAT_ERROR	=	1,
	DNS_RC_SERVER_FAILURE	=	2,
	DNS_RC_NAME_ERROR	=	3,
	DNS_RC_NOT_IMPLEMENTED	=	4,
	DNS_RC_REFUSED		=	5,
	DNS_RC_YXDOMAIN		=	6,
	DNS_RC_YXRRSET		=	7,
	DNS_RC_NXRRSET		=	8,
	DNS_RC_NOTAUTH		=	9,
	DNS_RC_NOTZONE		=	10,
} dns_rcode_t;

typedef struct dns_qd_s {
	char		*qname;
	uint16_t	qtype;
	uint16_t	qclass;
} dns_qd_t;

typedef struct dns_rr_s {
	char		*name;
	uint16_t	type;
	uint16_t	klass;
	uint32_t	ttl;
	uint16_t	rdlength;
	union {
		char *s;
		struct in_addr	ipv4;
		struct in6_addr	ipv6;
	} rdata;
} dns_rr_t;

typedef struct dns_msg_s {
	uint16_t	id;
	uint8_t		qr;
	uint8_t		opcode;
	uint8_t		aa;
	uint8_t		tc;
	uint8_t		rd;
	uint8_t		ra;
	uint8_t		z;
	uint8_t		rcode;
	uint16_t	qdcount;
	uint16_t	ancount;
	uint16_t	nscount;
	uint16_t	arcount;
	dns_qd_t	*qd;
	dns_rr_t	*an;
	dns_rr_t	*ns;
	dns_rr_t	*ar;
} dns_msg_t;

#endif //__DNS_H
