/**
 *  \brief 欧几里得算法计算最大公约数(greatest common divisor)
 *  
 *  \param [in] m Parameter_Description
 *  \param [in] n Parameter_Description
 *  \return Return_Description
 *  
 *  \details 迭代次数至多是2logN=O(logN)(M和N是两个相邻的斐波那契数列)
 *  假设m>=n。如果n>m，则循环的第一次迭代将它们互相交换。
 *  早在公元前300年左右，欧几里得就在他的著作《几何原本》中给出了高效的解法——辗转相除法。
 *  假设用f（x, y）表示x，y的最大公约数，取k = x/y，b = x%y，则x = ky + b，
 *  如果一个数能够同时整除x和y，则必能同时整除b和y；而能够同时整除b和y的数也必能同时整除x和y，
 *  即x和y的公约数与b和y的公约数是相同的，其最大公约数也是相同的，
 *  则有f（x, y）= f（y, x % y）（y > 0），
 *  如此便可把原问题转化为求两个更小数的最大公约数，直到其中一个数为0，
 *  剩下的另外一个数就是两者最大的公约数。
 */
long gcd(long m, long n)
{
	while(n != 0)
	{
		int rem = m % n;
		m = n;
		n = rem;
	}
	
	return m;
}

//	使用递归
long gcd(long m, long n)
{
	return (n > 0) ? gcd(n, m%n) : m;
}