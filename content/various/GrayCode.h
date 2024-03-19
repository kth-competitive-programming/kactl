/**
 * Author: Eu-Shaun Leong
 * Date: 2024-03-18
 * License: CC0
 * Source: -
 * Description: Successive gray codes vary by exactly 1 bit.
 */
#pragma once

int gray(int b){ return b^(b>>1); }
int bin(int g){
    for (int mask=g>>1;mask;mask>>=1)g^=mask;
    return g;
}