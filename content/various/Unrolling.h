/**
 * Author: Simon Lindholm
 * Date: 2015-03-19
 * License: CC0
 * Source: me
 * Description:
 */
#pragma once

#define F {...; ++i;}
int i = from;
while (i&3 && i < to) F // for alignment, if needed
while (i + 4 <= to) { F F F F }
while (i < to) F
