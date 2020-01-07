/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Returns an integer. Usage requires your program to pipe in
 * input from file. Can replace calls to gc() with getchar_unlocked() if extra
 * speed isn't necessary (60% slowdown).
 * Status: tested on SPOJ INTEST
 * Time: About 5x as fast as cin/scanf.
 * Usage: ./a.out < input.txt
 */
#pragma once

struct GC {
	char buf[1 << 16];
	int bc = 0, be = 0;
	char operator()() {
		if (bc >= be) {
			buf[0] = bc = 0;
			be = fread(buf, 1, sizeof(buf), stdin);
		}
		return buf[bc++]; // returns 0 on EOF
	}
} gc;
int read_int() {
	char c;
	while ((c = gc()) < 40);
	if (c == '-') return -read_int();
	int a = c - '0';
	while (isdigit(c = gc())) a = a * 10 + c -'0';
	return a;
}
