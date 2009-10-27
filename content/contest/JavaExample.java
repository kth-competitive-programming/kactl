/**
 * Author: Ulf Lundstrom
 * Date: 2005-12-04
 * Source: My solved problems
 * Description: Example of java code using a Scanner for input and BigInteger for calculations. The code prints the number of ways to build binary trees with n nodes for each input value n.
 * Status: tested
 */
import java.util.Scanner;
import java.math.BigInteger;

public class JavaExample {
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		while(true) {
			BigInteger t[] = new BigInteger[301];
			t[1] = t[0] = new BigInteger("1");
			for (int i = 1; i < 300; i++)
				t[i+1] = t[i].multiply(BigInteger.valueOf
						((2*i+1)*(2*i+2))).
					divide(BigInteger.valueOf(i+2));
			while (true) {
				int n = sc.nextInt();
				if (n == 0)
					return;
				System.out.println(t[n]);
			}
		}
	}
}
