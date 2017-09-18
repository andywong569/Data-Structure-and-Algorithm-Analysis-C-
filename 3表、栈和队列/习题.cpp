/**
 *  排序后的两表L和P，打印L中那些由P所指定的位置上的元素
 */
template<typename Object>
void printLots(const list<Object>& L, const list<int>& P)
{
	int pos = 0;
	typename list<Object>::const_iterator lIter = L.cbegin();
	for(typename list<int>::const_iterator pIter = P.cbegin(); pIter != P.cend() && lIter != L.cend(); ++pIter)
	{
		while(pos < *pIter && lIter != L.cend())
		{
			++pos;
			++lIter;
		}
		
		if(lIter != L.cend())
			cout << *lIter << endl;
	}
}

/**
 *  STL的find函数
 */
template<typename Iterator, typename Object>
Iterator find(Iterator start, Iterator end, const Object& x)
{
	while(start != end && *start != x)
	{
		++start;
	}
	return start;
}

/**
 *  求解排序后的两个表的交集
 */
template<typename Object>
list<Object> intersection(const list<Object>& L1, const list<Object>& L2)
{
	typename list<Object>::const_iterator l1Iter = L1.cbegin();
	typename list<Object>::const_iterator l2Iter = L2.cbegin();
	list<Object> retList;
	while(l1Iter != L1.cend() && l2Iter != L2.cend())
	{
		if(*l1Iter < *l2Iter)
		{
			++l1Iter;
		}
		else if(*l1Iter > *l2Iter)
		{
			++l2Iter;
		}
		else
		{
			retList.push_back(*l1Iter);
			++l1Iter;
			++l2Iter;
		}
	}
	
	return retList;
}

/**
 *  求解排序后的两个表的并集
 */
template<typename Object>
list<Object> listUnion(const list<Object>& L1, const list<Object>& L2)
{
	typename list<Object>::const_iterator l1Iter = L1.cbegin();
	typename list<Object>::const_iterator l2Iter = L2.cbegin();
	list<Object> retList;
	while(l1Iter != L1.cend() || l2Iter != L2.cend())
	{
		if(l1Iter == L1.cend() || l2Iter == L2.cend())
		{
			if(l1Iter == L1.cend())
			{
				while(l2Iter != L2.cend())
					retList.push_back(*l2Iter++);
			}
			else
				while(l1Iter != L1.cend())
					retList.push_back(*l1Iter++);
		}
		else if(*l1Iter < *l2Iter)
		{
			retList.push_back(*l1Iter++);
		}
		else if(*l1Iter > *l2Iter)
		{
			retList.push_back(*l2Iter++);
		}
		else
		{
			retList.push_back(*l1Iter++);
			++l2Iter;
		}
	}
	
	return retList;
}

/**
 *  Josephus问题 V1
 */
int Josephus(int M, list<int>& N)
{
	int start = 0;
	typedef list<int>::iterator it = N.begin();
	while(N.size() > 1)
	{
		if(it == N.end())
			it = N.begin();
		
		while(it != N.end() && start < M)
		{
			++it;
			++start;
		}
		if(start == M)
		{
			if(it != N.end())
			{
				it = N.erase(it);
				if(it == N.end())
					it = N.begin();
			}
			else
			{
				it = N.begin();
				it = N.erase(it);
			}
			start = 0;
		}
	}
}

/**
 *  Josephus问题 V2
 */
int Josephus(int M, list<int>& N)
{
	typename list<int>::iterator it = N.begin();
	int mPrime = M%(N.size());	//	求模，表示移动几个位置
	//	pass the potato
	while(N.size() > 1)
	{
		mPrime = M%(N.size());
		if(mPrime <= (N.size())/2)	// pass forward
		{
			for(int j = 0; j < mPrime; ++j)
			{
				++it;
				if(it == N.end())
					it = N.begin();
			}
		}
		else						//	pass backward
		{
			for(int j = 0; j < (N.size()-mPrime); ++j)
			{
				if(it == N.begin())
					it = --N.end();
				else
					--it;
			}
		}
		cout << *it << " ";
		it = N.erase(it);
		if(it == N.end())
			it = N.begin();
	}
}


/**
 *  逆向打印单链表
 *  可以使用stack实现，但是需要O(N)的额外空间
 *  反转结点的next指向
 */
Node* reverseList(Node* first)
{
	Node* prevPos = nullptr;
	Node* currPos = first;
	Node* nextPos = first->next;
	while(nextPos != nullptr)
	{
		currPos->next = prevPos;
		prevPos = currPos;
		currPos = nextPos;
		nextPos = nextPos->next;
	}
	currPos->next = prevPos;
	return currPos;
}


/**
 *  删除单链表的一个结点，不需要任何其他的结点的指针
 *  时间复杂度为O(1)
 */
void delSigLinkNode(Node* curr)
{
	Node* next = curr->next;
	curr->data = next->data;
	curr->next = next->next;
	delete next;
	next = nullptr;
}