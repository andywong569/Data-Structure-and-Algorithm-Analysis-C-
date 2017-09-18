/**
 *  \brief 最大子序列和的问题
 */
 
/**
 *  \brief 算法1 穷举法求最大子序列和
 *  
 *  \param [in] p 求解的数组
 *  \param [in] cnt 数组的大小
 *  \param [out] start 返回最大子序列和的开始索引
 *  \param [out] end 返回最大子序列和的结束索引
 *  \return 最大子序列的和
 *  
 *  \details 时间复杂度为O(N3)
 */
int maxSubSum1(int* p, int cnt, int& start, int& end)
{
	int max = 0;
	
	for(int i = 0; i < cnt; ++i)
        for(int j = i; j < cnt; ++j)
        {
            int sum = 0;
            for(int k = i; k <= j; ++k)
            {
                sum += p[k];
            }
			
			if(max < sum)
			{
				max = sum;
				start = i; 
				end = j;
			}
        }
		
	return max;
}


/**
 *  \brief 算法2 去掉算法1中的第三个循环求解
 *  
 *  \param [in] a 整形数组
 *  \return 最大子序列的和
 *  
 *  \details 时间复杂度为O(N2)
 */
int maxSubSum2( const vector<int>& a )
{
	int max = 0;
	for(int i = 0; i < a.size(); ++i)
	{
		int sum = 0;
		for(int j = i; j < a.size(); ++j)
		{
			sum += a[j];
			
			if(sum > max)
				max = sum;
		}
	}
}

/**
 *  \brief 算法3 采用分治策略
 *  
 *  \param [in] a 数组
 *  \param [in] left 数组左边界
 *  \param [in] right 数组右边界
 *  \return 最大子序列的和
 *  
 *  \details 时间复杂度为O(NlogN)；体现递归威力的极好的范例
 *  		 最大子序列和可能出现在三处地方：
 *  			1、输入数据的左半部；
 *  			2、输入数据的右半部；
 *  			3、跨越输入数据的中部从而占据左右两半部分；
 *  			前两种情况可以递归求解；
 *  第三种情况的最大和可以通过求出前半部分的最大和（包含前半部分的最后一个元素）
 *  以及后半部分的最大和（包含后半部分的第一个元素）而得到。然后将这两个和加在一起。
 */
int maxSubSum3(const vector<int>& a, int left, int right)
{
	if(left == right)
		if(a[left] > 0)
			return a[left];
		else
			return 0;
	
	int center = (left + right) / 2;
	int maxLeftSum = maxSubSum3(a, left, center);
	int maxRightSum = maxSubSum3(a, center + 1, right);
	
	int maxLeftBorderSum = 0, leftBorderSum = 0;
	for(int i = center; i >= left; --i)
	{
		leftBorderSum += a[i];
		if(leftBorderSum > maxLeftBorderSum)
			maxLeftBorderSum = leftBorderSum;
	}
	
	int maxRightBorderSum = 0, rightBorderSum = 0;
	for(int j = center + 1; j <= right; ++j)
	{
		rightBorderSum += a[j];
		if(rightBorderSum > maxRightBorderSum)
			maxRightBorderSum = rightBorderSum;
	}
	
	auto max3 = [](int a, int b, int c)
	{
		return max(max(a, b), c);
	};
	
	return max3(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}


/**
 *  \brief 算法4 聪明算法
 *  
 *  \param [in] a 整形数组
 *  \return 最大子序列的和
 *  
 *  \details 时间复杂度为O(N)
 *  运行时间是明显的，但正确性则不明显；
 *  如果a[i]是负的，那么它不可能代表最优序列的起点，因为任何包含a[i]
 *  的作为起点的子序列都可以通过用a[i+1]作起点而得到改进。
 *  类似的，任何负的子序列不可能是最优子序列的前缀(原理相同)。
 *  如果在内循环中我们检测到从a[i]到a[j]的子序列是负的，那么我们可以推进i。
 *  关键的结论是，我们不仅能够把i推进到i+1，而且我们实际上还可以把它一直推进到j+1。
 *  为了看清楚这一点，令p为i+1和j之间的任一下标。
 *  开始于下标p的任意子序列都不大于在下标i开始并包含a[i]到a[p-1]的子序列的对应子序列，
 *  因为后面这个子序列不是负的(j是使得从下标i开始成为负值的第一个下标)。
 *  因此，把i推进到j+1是安全：我们不会错过最优解。
 *  
 *  该算法的一个附带优点是，它只对数据进行一次扫描，一旦a[i]被读入并被处理，
 *  它就不再需要被记忆。因此，如果数组在磁盘或磁带上，它就可以被顺序读入，
 *  在主存中不必存储数组的任何部分。不仅如此，在任何时刻，算法都能对它已经读入的
 *  数据给出子序列问题的正确答案(其他算法不具有这个特性)。具有这种特性的算法叫作
 *  联机算法(on-line algorithm)。仅需要常量空间并以线性时间运行的联机算法
 *  几乎总是完美的算法。
 */
int maxSubSum4(const vector<int>& a)
{
	int max = 0, sum = 0;
	for(int i = 0; i < a.size(); ++i)
	{
		sum += a[i];
		
		if(sum > max)
			max = sum;
		else if(sum < 0)
			sum = 0;
	}
	
	return max;
}