/**
 * Author: Musin
 * Date: 2019-11-26
 * Description: FFT on real and imag double arrays.
 */
static class FFTArrays {
  void fft(double[] real, double[] imag, boolean inv) {
    int n = real.length;
    int m = 0;
    while (1 << m < n) m++;

    int[] rev = new int[n];
    for (int i = 1, j = -1; i < n; i++) {
      if ((i & (i - 1)) == 0) j++;
      rev[i] = rev[i ^ (1 << j)] | (1 << (m - 1 - j));
    }
    for (int i = 0; i < n; i++) {
      if (i < rev[i]) {
        swap(real, i, rev[i]);
        swap(imag, i, rev[i]);
      }
    }

    for (int len = 1; len < n; len <<= 1) {
      double root = Math.PI / len;
      if (inv) root = -root;
      double rootReal = Math.cos(root);
      double rootImag = Math.sin(root);
      for (int i = 0; i < n; i += len * 2) {
        double wReal = 1;
        double wImag = 0;
        for (int j = 0; j < len; j++) {
          double real1 = real[i + j];
          double imag1 = imag[i + j];
          double real2 = real[i + j + len];
          double imag2 = imag[i + j + len];
          double real3 = real2 * wReal - imag2 * wImag;
          double imag3 = real2 * wImag + imag2 * wReal;
          real[i + j] = real1 + real3;
          imag[i + j] = imag1 + imag3;
          real[i + j + len] = real1 - real3;
          imag[i + j + len] = imag1 - imag3;
          double nextwr = wReal * rootReal - wImag * rootImag;
          double nextwi = wReal * rootImag + wImag * rootReal;
          wReal = nextwr;
          wImag = nextwi;
        }
      }
    }

    if (inv) {
      for (int i = 0; i < n; i++) {
        real[i] /= n;
        imag[i] /= n;
      }
    }
  }

  void swap(double[] a, int i, int j) {
      double t = a[i];
      a[i] = a[j];
      a[j] = t;
  }

  double[] copy(int[] a, int n) {
      double[] b = new double[n];
      for (int i = 0; i < a.length; i++) b[i] = a[i];
      return b;
  }

  long[] multiply(int[] a, int[] b) {
    int n = Math.max(1,
      highestOneBit(max(a.length, b.length) - 1) << 2);
    double[] aReal = copy(a, n);
    double[] aImag = new double[n];
    double[] bReal = copy(b, n);
    double[] bImag = new double[n];
    fft(aReal, aImag, false);
    fft(bReal, bImag, false);
    for (int i = 0; i < n; i++) {
      double real = aReal[i] * bReal[i] - aImag[i] * bImag[i];
      double imag = aReal[i] * bImag[i] + aImag[i] * bReal[i];
      aReal[i] = real;
      aImag[i] = imag;
    }
    fft(aReal, aImag, true);
    long[] res = new long[n];
    for (int i = 0; i < n; i++) res[i] = round(aReal[i]);
    return res;
  }
}
