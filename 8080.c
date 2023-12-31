#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
	char const *label;
	uint8_t size;
	bool comma;
} inst_t;

static const inst_t inst[] = {
	[0x00] = {"NOP", 1, 0},
	[0x01] = {"LXI B", 3, 1},
	[0x02] = {"STAX B", 1, 0},
	[0x03] = {"INX B", 1, 0},
	[0x04] = {"INR B", 1, 0},
	[0x05] = {"DCR B", 1, 0},
	[0x06] = {"MVI B", 2, 1},
	[0x07] = {"RLC", 1, 0},
	[0x08] = {"*NOP", 1, 0},
	[0x09] = {"DAD B", 1, 0},
	[0x0a] = {"LDAX B", 1, 0},
	[0x0b] = {"DCX B", 1, 0},
	[0x0c] = {"INR C", 1, 0},
	[0x0d] = {"DCR C", 1, 0},
	[0x0e] = {"MVI C", 2, 1},
	[0x0f] = {"RRC", 1, 0},
	[0x10] = {"*NOP", 1, 0},
	[0x11] = {"LXI D", 3, 1},
	[0x12] = {"STAX D", 1, 0},
	[0x13] = {"INX D", 1, 0},
	[0x14] = {"INR D", 1, 0},
	[0x15] = {"DCR D", 1, 0},
	[0x16] = {"MVI D", 2, 1},
	[0x17] = {"RAL", 1, 0},
	[0x18] = {"*NOP", 1, 0},
	[0x19] = {"DAD D", 1, 0},
	[0x1a] = {"LDAX D", 1, 0},
	[0x1b] = {"DCX D", 1, 0},
	[0x1c] = {"INR E", 1, 0},
	[0x1d] = {"DCR E", 1, 0},
	[0x1e] = {"MVI E", 2, 1},
	[0x1f] = {"RAR", 1, 0},
	[0x20] = {"*NOP", 1, 0},
	[0x21] = {"LXI H", 3, 1},
	[0x22] = {"SHLD", 3, 0},
	[0x23] = {"INX H", 1, 0},
	[0x24] = {"INR H", 1, 0},
	[0x25] = {"DCR H", 1, 0},
	[0x26] = {"MVI H", 2, 1},
	[0x27] = {"DAA", 1, 0},
	[0x28] = {"*NOP", 1, 0},
	[0x29] = {"DAD H", 1, 0},
	[0x2a] = {"LHLD", 3, 0},
	[0x2b] = {"DCX H", 1, 0},
	[0x2c] = {"INR L", 1, 0},
	[0x2d] = {"DCR L", 1, 0},
	[0x2e] = {"MVI L", 2, 1},
	[0x2f] = {"CMA", 1, 0},
	[0x30] = {"*NOP", 1, 0},
	[0x31] = {"LXI SP", 3, 1},
	[0x32] = {"STA", 3, 0},
	[0x33] = {"INX SP", 1, 0},
	[0x34] = {"INR M", 1, 0},
	[0x35] = {"DCR M", 1, 0},
	[0x36] = {"MVI M", 2, 1},
	[0x37] = {"STC", 1, 0},
	[0x38] = {"*NOP", 1, 0},
	[0x39] = {"DAD SP", 1, 0},
	[0x3a] = {"LDA", 3, 0},
	[0x3b] = {"DCX SP", 1, 0},
	[0x3c] = {"INR A", 1, 0},
	[0x3d] = {"DCR A", 1, 0},
	[0x3e] = {"MVI A", 2, 1},
	[0x3f] = {"CMC", 1, 0},
	[0x40] = {"MOV B,B", 1, 0},
	[0x41] = {"MOV B,C", 1, 0},
	[0x42] = {"MOV B,D", 1, 0},
	[0x43] = {"MOV B,E", 1, 0},
	[0x44] = {"MOV B,H", 1, 0},
	[0x45] = {"MOV B,L", 1, 0},
	[0x46] = {"MOV B,M", 1, 0},
	[0x47] = {"MOV B,A", 1, 0},
	[0x48] = {"MOV C,B", 1, 0},
	[0x49] = {"MOV C,C", 1, 0},
	[0x4a] = {"MOV C,D", 1, 0},
	[0x4b] = {"MOV C,E", 1, 0},
	[0x4c] = {"MOV C,H", 1, 0},
	[0x4d] = {"MOV C,L", 1, 0},
	[0x4e] = {"MOV C,M", 1, 0},
	[0x4f] = {"MOV C,A", 1, 0},
	[0x50] = {"MOV D,B", 1, 0},
	[0x51] = {"MOV D,C", 1, 0},
	[0x52] = {"MOV D,D", 1, 0},
	[0x53] = {"MOV D,E", 1, 0},
	[0x54] = {"MOV D,H", 1, 0},
	[0x55] = {"MOV D,L", 1, 0},
	[0x56] = {"MOV D,M", 1, 0},
	[0x57] = {"MOV D,A", 1, 0},
	[0x58] = {"MOV E,B", 1, 0},
	[0x59] = {"MOV E,C", 1, 0},
	[0x5a] = {"MOV E,D", 1, 0},
	[0x5b] = {"MOV E,E", 1, 0},
	[0x5c] = {"MOV E,H", 1, 0},
	[0x5d] = {"MOV E,L", 1, 0},
	[0x5e] = {"MOV E,M", 1, 0},
	[0x5f] = {"MOV E,A", 1, 0},
	[0x60] = {"MOV H,B", 1, 0},
	[0x61] = {"MOV H,C", 1, 0},
	[0x62] = {"MOV H,D", 1, 0},
	[0x63] = {"MOV H,E", 1, 0},
	[0x64] = {"MOV H,H", 1, 0},
	[0x65] = {"MOV H,L", 1, 0},
	[0x66] = {"MOV H,M", 1, 0},
	[0x67] = {"MOV H,A", 1, 0},
	[0x68] = {"MOV L,B", 1, 0},
	[0x69] = {"MOV L,C", 1, 0},
	[0x6a] = {"MOV L,D", 1, 0},
	[0x6b] = {"MOV L,E", 1, 0},
	[0x6c] = {"MOV L,H", 1, 0},
	[0x6d] = {"MOV L,L", 1, 0},
	[0x6e] = {"MOV L,M", 1, 0},
	[0x6f] = {"MOV L,A", 1, 0},
	[0x70] = {"MOV M,B", 1, 0},
	[0x71] = {"MOV M,C", 1, 0},
	[0x72] = {"MOV M,D", 1, 0},
	[0x73] = {"MOV M,E", 1, 0},
	[0x74] = {"MOV M,H", 1, 0},
	[0x75] = {"MOV M,L", 1, 0},
	[0x76] = {"HLT", 1, 0},
	[0x77] = {"MOV M,A", 1, 0},
	[0x78] = {"MOV A,B", 1, 0},
	[0x79] = {"MOV A,C", 1, 0},
	[0x7a] = {"MOV A,D", 1, 0},
	[0x7b] = {"MOV A,E", 1, 0},
	[0x7c] = {"MOV A,H", 1, 0},
	[0x7d] = {"MOV A,L", 1, 0},
	[0x7e] = {"MOV A,M", 1, 0},
	[0x7f] = {"MOV A,A", 1, 0},
	[0x80] = {"ADD B", 1, 0},
	[0x81] = {"ADD C", 1, 0},
	[0x82] = {"ADD D", 1, 0},
	[0x83] = {"ADD E", 1, 0},
	[0x84] = {"ADD H", 1, 0},
	[0x85] = {"ADD L", 1, 0},
	[0x86] = {"ADD M", 1, 0},
	[0x87] = {"ADD A", 1, 0},
	[0x88] = {"ADC B", 1, 0},
	[0x89] = {"ADC C", 1, 0},
	[0x8a] = {"ADC D", 1, 0},
	[0x8b] = {"ADC E", 1, 0},
	[0x8c] = {"ADC H", 1, 0},
	[0x8d] = {"ADC L", 1, 0},
	[0x8e] = {"ADC M", 1, 0},
	[0x8f] = {"ADC A", 1, 0},
	[0x90] = {"SUB B", 1, 0},
	[0x91] = {"SUB C", 1, 0},
	[0x92] = {"SUB D", 1, 0},
	[0x93] = {"SUB E", 1, 0},
	[0x94] = {"SUB H", 1, 0},
	[0x95] = {"SUB L", 1, 0},
	[0x96] = {"SUB M", 1, 0},
	[0x97] = {"SUB A", 1, 0},
	[0x98] = {"SBB B", 1, 0},
	[0x99] = {"SBB C", 1, 0},
	[0x9a] = {"SBB D", 1, 0},
	[0x9b] = {"SBB E", 1, 0},
	[0x9c] = {"SBB H", 1, 0},
	[0x9d] = {"SBB L", 1, 0},
	[0x9e] = {"SBB M", 1, 0},
	[0x9f] = {"SBB A", 1, 0},
	[0xa0] = {"ANA B", 1, 0},
	[0xa1] = {"ANA C", 1, 0},
	[0xa2] = {"ANA D", 1, 0},
	[0xa3] = {"ANA E", 1, 0},
	[0xa4] = {"ANA H", 1, 0},
	[0xa5] = {"ANA L", 1, 0},
	[0xa6] = {"ANA M", 1, 0},
	[0xa7] = {"ANA A", 1, 0},
	[0xa8] = {"XRA B", 1, 0},
	[0xa9] = {"XRA C", 1, 0},
	[0xaa] = {"XRA D", 1, 0},
	[0xab] = {"XRA E", 1, 0},
	[0xac] = {"XRA H", 1, 0},
	[0xad] = {"XRA L", 1, 0},
	[0xae] = {"XRA M", 1, 0},
	[0xaf] = {"XRA A", 1, 0},
	[0xb0] = {"ORA B", 1, 0},
	[0xb1] = {"ORA C", 1, 0},
	[0xb2] = {"ORA D", 1, 0},
	[0xb3] = {"ORA E", 1, 0},
	[0xb4] = {"ORA H", 1, 0},
	[0xb5] = {"ORA L", 1, 0},
	[0xb6] = {"ORA M", 1, 0},
	[0xb7] = {"ORA A", 1, 0},
	[0xb8] = {"CMP B", 1, 0},
	[0xb9] = {"CMP C", 1, 0},
	[0xba] = {"CMP D", 1, 0},
	[0xbb] = {"CMP E", 1, 0},
	[0xbc] = {"CMP H", 1, 0},
	[0xbd] = {"CMP L", 1, 0},
	[0xbe] = {"CMP M", 1, 0},
	[0xbf] = {"CMP A", 1, 0},
	[0xc0] = {"RNZ", 1, 0},
	[0xc1] = {"POP B", 1, 0},
	[0xc2] = {"JNZ", 3, 0},
	[0xc3] = {"JMP", 3, 0},
	[0xc4] = {"CNZ", 3, 0},
	[0xc5] = {"PUSH B", 1, 0},
	[0xc6] = {"ADI", 2, 0},
	[0xc7] = {"RST 0", 1, 0},
	[0xc8] = {"RZ", 1, 0},
	[0xc9] = {"RET", 1, 0},
	[0xca] = {"JZ", 3, 0},
	[0xcb] = {"*JMP", 3, 0},
	[0xcc] = {"CZ", 3, 0},
	[0xcd] = {"CALL", 3, 0},
	[0xce] = {"ACI", 2, 0},
	[0xcf] = {"RST 1", 1, 0},
	[0xd0] = {"RNC", 1, 0},
	[0xd1] = {"POP D", 1, 0},
	[0xd2] = {"JNC", 3, 0},
	[0xd3] = {"OUT", 2, 0},
	[0xd4] = {"CNC", 3, 0},
	[0xd5] = {"PUSH D", 1, 0},
	[0xd6] = {"SUI", 2, 0},
	[0xd7] = {"RST 2", 1, 0},
	[0xd8] = {"RC", 1, 0},
	[0xd9] = {"*RET", 1, 0},
	[0xda] = {"JC", 3, 0},
	[0xdb] = {"IN", 2, 0},
	[0xdc] = {"CC", 3, 0},
	[0xdd] = {"*CALL", 3, 0},
	[0xde] = {"SBI", 2, 0},
	[0xdf] = {"RST 3", 1, 0},
	[0xe0] = {"RPO", 1, 0},
	[0xe1] = {"POP H", 1, 0},
	[0xe2] = {"JPO", 3, 0},
	[0xe3] = {"XTHL", 1, 0},
	[0xe4] = {"CPO", 3, 0},
	[0xe5] = {"PUSH H", 1, 0},
	[0xe6] = {"ANI", 2, 0},
	[0xe7] = {"RST 4", 1, 0},
	[0xe8] = {"RPE", 1, 0},
	[0xe9] = {"PCHL", 1, 0},
	[0xea] = {"JPE", 3, 0},
	[0xeb] = {"XCHG", 1, 0},
	[0xec] = {"CPE", 3, 0},
	[0xed] = {"*CALL", 3, 0},
	[0xee] = {"XRI", 2, 0},
	[0xef] = {"RST 5", 1, 0},
	[0xf0] = {"RP", 1, 0},
	[0xf1] = {"POP PSW", 1, 0},
	[0xf2] = {"JP", 3, 0},
	[0xf3] = {"DI", 1, 0},
	[0xf4] = {"CP", 3, 0},
	[0xf5] = {"PUSH PSW", 1, 0},
	[0xf6] = {"ORI", 2, 0},
	[0xf7] = {"RST 6", 1, 0},
	[0xf8] = {"RM", 1, 0},
	[0xf9] = {"SPHL", 1, 0},
	[0xfa] = {"JM", 3, 0},
	[0xfb] = {"EI", 1, 0},
	[0xfc] = {"CM", 3, 0},
	[0xfd] = {"*CALL", 3, 0},
	[0xfe] = {"CPI", 2, 0},
	[0xff] = {"RST 7", 1, 0}
};

static void disassemble(uint8_t const *buf, size_t size) {

	size_t off = 0;

	while (off < size) {
		inst_t const *it = inst + buf[off];

		if (it->size > size - off)
			return;

		printf("%04zx: ", off);

		for (size_t i = 0; i < 3; i++)
			if (i < it->size)
				printf("%02x ", buf[off + i]);
			else
				printf("   ");

		printf(": %s", it->label);

		if (it->size > 1) {
			int d = buf[off + 1];

			if (it->size > 2)
				d |= buf[off + 2] << 8;

			if (it->comma)
				putchar(',');

			printf(" %#x", d);
		}

		putchar(0xa);

		off += it->size;
	}

}

int main(int argc, char *argv[]) {

	if (argc == 1) {
		fputs("Missing filename\n", stderr);
		return 1;
	}

	FILE *fp = fopen(argv[1], "rb");

	if (!fp) {
		perror(argv[1]);
		return 1;
	}

#define CHUNK 512

	uint8_t *buf = malloc(CHUNK);
	size_t red = 0, chunks = 1;

	for (;;) {
		for (size_t i = CHUNK; i--; ) {
			int ch;

			if ((ch = fgetc(fp)) == EOF)
				break;

			buf[red++] = ch;
		}

		if (ferror(fp)) {
			perror("read error");
			free(buf);
			return 1;
		}

		if (feof(fp))
			break;

		buf = realloc(buf, CHUNK * ++chunks);
	}

	printf("%s: %zu bytes (%#zx)\n", argv[1], red, red);

	disassemble(buf, red);

	free(buf);

	fclose(fp);

	return 0;
}
