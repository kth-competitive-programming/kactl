/**
 * Author: chilli
 * License: CC0
 * Source: Own work
 * Description: Returns an integer. Usage requires your program to pipe in
 * input from file. Can replace calls to gc() with getchar\_unlocked() if extra
 * speed isn't necessary (60\% slowdown).
 * Status: tested on SPOJ INTEST, unit tested
 * Time: About 5x as fast as cin/scanf.
 * Usage: ./a.out < input.txt
 */
#pragma once

struct GC {
	char buf[1 << 16];
	size_t bc = 0, be = 0;
	char operator()() {
		if (bc >= be) {
			buf[0] = 0, bc = 0;
			be = fread(buf, 1, sizeof(buf), stdin);
		}
		return buf[bc++]; // returns 0 on EOF
	}
} gc;
int readInt() {
	int a, c;
	while ((a = gc()) < 40);
	if (a == '-') return -readInt();
	while ((c = gc()) >= 48) a = a * 10 + c - 480;
	return a - 48;
}
