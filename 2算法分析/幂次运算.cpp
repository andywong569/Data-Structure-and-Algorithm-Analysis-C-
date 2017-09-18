
/**
 *  \brief 幂运算，用乘法的次数作为运行时间的度量
 *  
 *  \param [in] x Parameter_Description
 *  \param [in] n Parameter_Description
 *  \return Return_Description
 *  
 *  \details 时间复杂度为O(logN)
 *  所需要的乘法次数最多是2logN，因为把问题分半最多需要两次乘法（如果N是奇数）。
 *  N<=1是递归的基准情形。
 *  if N is 偶数，X(N) = X(N/2) * X(N/2)
 *  if N is 奇数，X(N) = X(N/2) * X(N/2) * X
 */
long pow(long x, int n)
{
	if(n == 0)
		return 1;
	
	if(isEven(x))
		return pow(x*x, n/2);	//	不能写成pow(pow(x, 2), n/2) or pow(pow(x, n/2), 2) 死循环 
	else
		return pow(x*x, n/2)*x;
}


/**
 *  还有一种解法为维护一个数组，分别表示x, x^2, x^3, ... ,x^log(n)
 */