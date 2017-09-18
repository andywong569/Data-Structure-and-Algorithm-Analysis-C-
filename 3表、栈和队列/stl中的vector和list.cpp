/**
 *  使用迭代器来间隔删除表中的项（vector或list）
 *  对list是高效的，对vector则不是
 */
template<typename Container>
void removeEveryOtherItem(Container& lst)
{
	typename Container::iterator it = lst.begin();
	it = lst.erase(it);
	if(it != lst.end())
		++it;
}

/**
 *  打印任何容器
 */
template<truename Container>
void printCollection(const Container& c, ostream& out = cout)
{
	if(c.empty())
		out<<"(empty)";
	else
	{
		truename Container::const_iterator it = c.begin();
		out<<"["<<*it++;
		while(it != c.end())
			out<<", "<<*it++;
		out<<"]"<<endl;
	}
}

/**
 *  Vector模板类
 */
template<typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0) : theSize(initSize), 
										theCapacity(init + SPACE_CAPACITY)
	{
		objects = new Object[theCapacity];
	}
	Vector(const Vector& rhs) : objects(nullptr)
	{
		operator=(rhs);
	}
	const Vector& operator=(const Vector& rhs)
	{
		if(this != &rhs)
		{
			delete [] objects;
			theSize = rhs.size();
			theCapacity = rhs.capacity();
			
			objects = new Object[theCapacity];
			memcpy(objects, rhs.objects, theSize*sizeof(Object));
		}
		return *this;
	}
	~Vector()
	{
		delete [] objects;
		objects = nullptr;
	}
	
	void resize(int newSize)
	{
		if(newSize > theCapacity)
			reverse(newSize*2 + 1);
	}
	
	void reverse(int newCapacity)
	{
		if(newCapacity < theSize)
			return;
		
		Object* oldArray = objects;
		objects = new Object[newCapacity];
		memcpy(objects, oldArray, theSize*sizeof(Object));
		theCapacity = newCapacity;
		
		delete [] oldArray;
	}
	
	Object& operator[](int index)
	{
		if(index < 0 || index >= theSize)
			throw OutOfBoundException();
		
		return objects[index];
	}
	const Object& operator[](int index) const
	{
		if(index < 0 || index >= theSize)
			throw OutOfBoundException();
		
		return objects[index];
	}
	
	bool empty() const
	{
		return theSize == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}
	
	void push_back(const Object& x)
	{
		if(theSize == theCapacity)
			reverse(2*theCapacity + 1);
		objects[theSize++] = x;
	}
	
	void pop_back()
	{
		theSize--;
	}
	
	const Object& back() const
	{
		return objects[theSize-1];
	}
	
	typedef Object* iterator;
	typedef const Object* const_iterator;
	
	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[theSize];
	}
	const_iterator end() const
	{
		return &objects[theSize];
	}
	
	enum { SPACE_CAPACITY = 16 };
	
private:
	Object* objects;
	int theSize;
	int theCapacity;
};


/**
 *  List模板类
 */
template<typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node* prev;
		Node* next;
		
		Node(const Object& d = Object(), Node* p = nullptr, Node* n = nullptr) : 
			data(d), prev(p), next(n)
		{}
	};
	
public:
	class const_iterator
	{
	public:
		const_iterator() : current(nullptr)
		{
			
		}
		const Object& operator*() const
		{
			return retrieve();
		}
		const_iterator operator++()
		{
			current = current->next;
			return this;
		}
		const_iterator operator++(int)
		{
			const_iterator tmp = *this;
			++(*this);
			return tmp;
		}
		bool operator==(const const_iterator& rhs) const
		{
			return current == rhs.current;
		}
		bool operator!=(const const_iterator& rhs) const
		{
			return !(this == rhs);
		}
		
	protected:
		/*	为确定传递的迭代器是否属于正确的表	*/
		const List<Object>* theList;
		Node* current;
		
		Object& retrieve() const
		{
			return current->data;
		}
		
		const_iterator(const List<Object>& lst, Node* p) : 
			theList(&lst), current(p)
		{}
		
		void assertIsValid() const
		{
			if(theList == nullptr || current == nullptr || current == theList->head)
				throw IteratorOutOfBoundsException();
		}
		
		friend class List<Object>;
	};
	
	class iterator : public const_iterator
	{
	public:
		iterator()
		{
			
		}
		Object& operator*()
		{
			return retrieve();
		}
		const Object& operator*() const
		{
			return const_iterator::operator*();
		}
		iterator operator++()
		{
			current = current->next;
			return this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		
	protected:		
		iterator(const List<Object>& lst, Node* p) : const_iterator(lst, p)
		{}
		
		friend class List<Object>;
	};
	
public:
	List()
	{
		init();
	}
	List(const List& rhs)
	{
		init();
		*this = rhs;
	}
	~List()
	{
		clear();
		delete head;
		head = nullptr
		delete tail;
		tail = nullptr;
	}
	const List& operator=(const List& rhs)
	{
		if(this != &rhs)
		{
			clear();
			for(const_iterator it = rhs.begin(); it != rhs.end(); ++it)
				push_back(*it);
		}
		return *this;
	}
	
	iterator begin()
	{
		return iterator(*this, head->next);
	}
	const_iterator begin() const
	{
		return const_iterator(*this, head->next);
	}
	iterator end()
	{
		return iterator(*this, tail);
	}
	const_iterator end() const
	{
		return iterator(*this, tail);
	}
	
	int size() const
	{
		return theSize;
	}
	bool empty() const
	{
		return size() == 0;
	}
	
	void clear()
	{
		erase(begin(), end());
	}
	
	Object& front()
	{
		return head->next->data;
	}
	const Object& front() const
	{
		return head->next->data;
	}
	Object& back()
	{
		return tail->prev->data;
	}
	const Object& back() const
	{
		return tail->prev->data;
	}
	void push_front(const Object& x)
	{
		insert(begin(), x);
	}
	void push_back(const Object& x)
	{
		insert(--end(), x);
	}
	void pop_front()
	{
		erase(++begin());
	}
	void pop_back()
	{
		erase(--end());
	}
	
	iterator insert(iterator it, const Object& x)
	{
		it.assertIsValid();
		if(it.theList != this)
			throw IteratorMismatchException();
		
		Node* p = it.current;
		++theSize;
		iterator ins(*this, p->prev = p->prev->next = new Node(x, p->prev, p));
	}
	
	iterator erase(iterator it)
	{
		Node* p = it.current;
		iterator retVal(p->next);
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		p = nullptr;
		--theSize;
		
		return retVal;
	}
	iterator erase(iterator start, iterator end)
	{
		for(iterator it = start; it != end; ++it)
			erase(it);
		return end;
	}

private:
	void init()
	{
		theSize = 0;
		head = new Node;
		tail = new Node;
		head->next = tail;
		tail->next = head;
	}
	
private:
	int theSize;
	Node* head;
	Node* tail;
};