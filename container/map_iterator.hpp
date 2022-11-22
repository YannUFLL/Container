	namespace ft 
	{
	
	template <typename T, typename Node, typename Content>
	class map_iterator {
		public :
			typedef	std::bidirectional_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::size_t size_type;
			typedef void difference_type;
			typedef Content* pointer;
			typedef Content& reference;

			pointer		base() const { }

			map_iterator(): _n(NULL) {}
			map_iterator(map_iterator &copy): _last(copy._last) 
			{
				if (copy._n == &copy._dummy)
						_n = &_dummy;
					else
						_n = copy._n;
			}
			map_iterator(Node* ptr):_n(ptr) {}
			map_iterator(Node* ptr, bool end):_n(ptr)
			{
				if (end == true)
				{
					_last = _n;
					_n = &_dummy;
				}
			}
    		reference operator*() const {}
    		pointer operator->() {return (&(_n->content));}
			map_iterator& operator++() 
			{
				Node *child = NULL;
				_last = _n;
				if (_n == &_dummy)
					return (*this);
				if (!_n->right && _n->parent != NULL) 
				{
					do	
					{
						child = _n;
						_n = _n->parent;
						if (child == _n->left)
							return(*this);
						if (_n->parent == NULL && child != _n->left)
						{
							_n = &_dummy;
							return (*this);
						}
					}
					while (child != _n->left);	
				}
				if (_n->right)
				{
					_n = _n->right;
					while (_n->left)
						_n = _n->left;
				}
				return (*this);
			} 
			map_iterator operator++(int) 
			{map_iterator temp = *this; ++(*this); return(temp);} 
			map_iterator& operator--() 
			{
				Node *child = NULL;
				if (_n == &_dummy)
				{
					_n = _last;
					return(*this);
				}
				if (!_n->left && _n->parent != NULL) 
				{
					do				
					{
						child = _n;
						_n = _n->parent;
						if (child == _n->right)
							return(*this);
						if (_n->parent == NULL && child != _n->right)
							return (*this);
					}
					while (child != _n->right);	
				}
				if (_n->left)
				{
					_n = _n->left;
					while (_n->right)
						_n = _n->right;
				}
				return (*this);
			} 
			map_iterator operator--(int) {map_iterator temp = *this; --(*this); return(temp);} 
			bool operator==(const map_iterator &a) const 	
			{
				(void)a;
				return (1);
			}
			bool operator!=(const map_iterator &a) const 	
			{
				(void)a;
				return (1);
			}
			void friend iter_swap(map_iterator &a, map_iterator &b)
			{
				map_iterator c(a); 
				a._ptr = b._ptr;
				b._ptr = c._ptr;
			}
			map_iterator& operator=(const map_iterator &assign) 
            {
                if (this != &assign)
                {
					if (assign._n == &assign._dummy)
						_n = &_dummy;
					else
						_n = assign._n;
					_last = assign._last;
                }
				return *this; 
            }
		private : 
			Node *_n;
			Node *_last;
			Node _dummy;

	};
}