/**
 * Author: chilli
 * License: CC0
 * Source:
 * Description: Reads in arbitrary amounts of integral values.
 * Status: tested on SPOJ INTEST
 * Time: About 5x as fast as cin.
 * Usage: int a, b[5]; ll c;
 * read_int(a, b[0], c);
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
void read_int() {}
template <class T, class... S>
inline void read_int(T &a, S &... b) {
	char c, s = 1;
	while (isspace(c = gc()));
	if (c == '-') s = -1, c = gc();
	for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
	a *= s;
	read_int(b...);
}
