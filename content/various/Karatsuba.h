/**
 * Author: Simon Lindholm
 * Date: 2015-04-22
 * License: CC0
 * Source: me
 * Description: Faster-than-naive convolution of two sequences: $c[x] = \sum a[i]b[x-i]$.
   Uses the identity $(aX+b)(cX+d) = acX^2 + bd + ((a+c)(b+d)-ac-bd)X$.
   Doesn't handle sequences of very different length well.
   See also FFT, under the Numerical chapter.
 * Time: O(N^{1.6})
 * Status: tested
 */
