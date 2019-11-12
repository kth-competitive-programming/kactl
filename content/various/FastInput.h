/**
 * Author: chilli
 * License: CC0
 * Source:
 * Description: Returns an integer. Usage requires your program to pipe in input from file.
 * Status: tested on SPOJ INTEST
 * Time: About 5x as fast as cin/scanf.
 * Usage: ./a.out < input.txt
 */
#pragma once

struct GC {
	char buf[1 << 16 | 1];
	int bc = 0, be = 0;
	char operator()() {
		if (bc >= be) {
			be = fread(buf, 1, sizeof(buf) - 1, stdin);
			buf[be] = bc = 0;
		}
		return buf[bc++];
	}
} gc;
inline int read_int() {
	static char c;
	while ((c = gc()) < 40);
	if (c == '-') return -read_int();
	int a = c - '0';
	for (; isdigit(c = gc()); a = a * 10 + c - '0');
	return a;
}
