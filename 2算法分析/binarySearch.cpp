/**
 *  \brief 二分搜索
 *  
 *  \param [in] a 已排序原数组
 *  \param [in] value 要查找的值
 *  \return 若找到，返回下标的索引；否则返回-1
 *  
 *  \details 时间复杂度为O(logN)
 */
template<typename Comparable>
int binarySearch(const vector<Comparable>& a, const Comparable& value)
{
	int low = 0;
	int high = a.size() - 1;
	if(a[low] <= value && a[high] >= value)		// value处于最小值和最大值之间才做循环
		while(low <= high)
		{
			int mid = (low + high) / 2;
			if(a[mid] > value)
				high = mid - 1;
			else if(a[mid] < value)
				low = mid + 1;
			else
				return mid;
		}
	
	return -1;
}