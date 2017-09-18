/**
 *  \brief 如果N是奇数，那么它等于N/2的二进制表示中1的个数加1
 */

/**
 *  my code
 */
static int sum = 0;
void numOne(int n)
{
	if(n == 1)
	{
		++sum;
		return;
	}
	if(n%2)
	{
		sum += 1;
		numOne(n/2);
	}
	else
		numOne(n/2);
}


/**
 *  other's code
 */
int ones(int n)
{
	if(n < 2)
		return n;
	return (n%2 +ones(n/2)); 
}