/**
 *  使用Comparable项表示的二叉查找树
 */
template<typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() : root(nullptr)
	{}
	BinarySearchTree(const BinarySearchTree& rhs)
	{
		root = clone(rhs.root);
	}
	~BinarySearchTree()
	{
		makeEmpty();
	}
	
	const BinarySearchTree& operator=(const BinarySearchTree& rhs)
	{
		if(this != rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}
	
	const Comparable& findMin() const
	{
		return findMin(root)->element;
	}
	const Comparable& findMax() const
	{
		return findMax(root)->element;
	}
	/**
	 *  Returns true if x is found in the tree.
	 */
	bool contains(const Comparable& x) const
	{
		return contains(x, root);
	}
	bool isEmpty() const
	{
		return root == nullptr;
	}
	void printTree() const
	{
		printTree(root);
	}
	void makeEmpty()
	{
		makeEmpty(root);
	}
	/**
	 *  Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable& x)
	{
		insert(x, root);
	}
	/**
	 *  Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const Comparable& x)
	{
		remove(x, root);
	}
	
private:
	/**
	 *  对二叉查找树的递归实现
	 */
	BinaryNode* findMin(BinaryNode* t) const
	{
		if(t == nullptr)
			return;
		if(t->left == nullptr)
			return t;
		return findMin(t->left);
	}
	/**
	 *  对二叉查找树的非递归实现
	 */
	BinaryNode* findMax(BinaryNode* t) const
	{
		if(t != nullptr)
			while(t->right != nullptr)
				t = t->right;
		
		return t;
	}
	
	/**
	 *  Internal method to test if an item is in a subtree.
	 *  x is item to research for.
	 *  t is the node that roots the subtree.
	 *  时间复杂度为O(logN)
	 */
	bool contains(const Comparable& x, BinaryNode* t) const
	{
		if(t == nullptr)
			return false;
		else if(x < t->element)
			return contains(x, t->left);
		else if(t->element < x)
			return contains(x, t->right);
		else 
			return true;	// Match
	}
	
	/**
	 *  递归的打印操作
	 */
	void printTree(BinaryNode* t) const
	{
		if(t == nullptr)
			return;
		// print t->element;
		printTree(t->left);
		printTree(t->right);
	}
	
	/**
	 *  递归的删除操作
	 */
	void makeEmpty(BinaryNode* & t)
	{
		if(t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}
	
	/**
	 *  递归的插入函数
	 */
	void insert(const Comparable& x, BinaryNode* & t) const
	{
		if(t == nullptr)
			t = new BinaryNode(x);
		else if(x < t->element)
			insert(x, t->left);
		else if(t->element < x)
			insert(x, t->right);
		else
			;	// Duplicate; do nothing
	}
	
	/**
	 *  最困难的就是删除操作
	 *  1、叶子结点：可以直接删除；
	 *  2、一儿子结点：父节点->儿子结点；
	 *  3、双儿子结点：一般的删除策略是用其右子树的最小的数据代替该结点的数据。
	 */
	void remove(const Comparable& x, BinaryNode* & t) const
	{
		if(t == nullptr)
			return;
		if(x < t->element)
			remove(x, t->left);
		else if(t->element < x)
			remove(x, t->right);
		else if(t->left != nullptr && t->right != nullptr)	//	Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode* oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
			oldNode = nullptr;
		}
	}
	
	/**
	 *  递归的clone函数
	 */
	BinaryNode* clone(BinaryNode* t) const
	{
		if(t == nullptr)
			return;
		
		return new BinaryNode(t->element, clone(t->left), clone(t->right));
	}
	
private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode* left;
		BinaryNode* right;
		
		BinaryNode(const Comparable& x, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
			: element(x), left(lt), right(rt)
		{}
	};
	
	BinaryNode* root;
};




/**
 *  使用函数对象项表示的二叉查找树
 */
template<typename Object, typename Comparator=less<Object>>
class BinarySearchTree
{
public:
	//	Same methods, with Object replacing Comparable
	
private:
	//	...
	
	/**
	 *  Internal method to test if an item is in a subtree.
	 *  x is item to research for.
	 *  t is the node that roots the subtree.
	 *  时间复杂度为O(logN)
	 */
	bool contains(const Comparable& x, BinaryNode* t) const
	{
		if(t == nullptr)
			return false;
		else if(isLessThan(x, t->element))
			return contains(x, t->left);
		else if(isLessThan(t->element, x))
			return contains(x, t->right);
		else 
			return true;	// Match
	}
	
	
private:
	//	...
	BinaryNode* root;
	Comparator isLessThan;
};