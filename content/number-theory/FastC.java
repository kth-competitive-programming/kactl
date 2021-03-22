/**
 * Author: EgorKulikov -> Musin
 * Date: 2019-11-26
 * Description: Linear c(n,k).
 */
int fast_c(int n, int k) {
  double res = 1;
  for (int i = 1; i <= k; i++)
    res = res * (n - k + i) / i;
  return (int) (res + 0.01);
}
