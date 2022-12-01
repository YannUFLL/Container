	#ifndef MAP_ITERATOR_HPP
	#define MAP_ITERATOR_HPP
	
	namespace ft 
	{
	template <typename T, typename Node, typename Content, typename NotConstContent, typename color_t>
	class map_iterator {
		public :
			typedef	std::bidirectional_iterator_tag iterator_category;
			typedef Content value_type;
			typedef T mapped_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Content* pointer;
			typedef Content& reference;
		private : 
			Node *_n;
			Node _dummy;
		public :
			map_iterator(): _n(&_dummy), _dummy()
			{
				_dummy.color = static_cast<color_t>(3);
			}
			map_iterator(map_iterator const &copy): _dummy()
			{
				_dummy.color = static_cast<color_t>(3);
				if (copy.base()->color == static_cast<color_t>(3))
				{
					_dummy = *(copy.base());
					_n = &_dummy;
				}
			}
			map_iterator(Node* ptr):_n(ptr), _dummy()
			{
				_dummy.color = static_cast<color_t>(3);
				if (ptr == NULL)
				{
					_n = &_dummy;
				}
			}
			map_iterator(Node* ptr, bool end):_n(ptr), _dummy()
			{
				_dummy.color = static_cast<color_t>(3) ;
				if (end == true)
				{
					_dummy.left = _n;
					_n = &_dummy;
				}
			}
			Node*		base() const {return(_n); }
			reference operator*() const {return (_n->content);}
			pointer operator->() const {return (&(_n->content));}
			map_iterator& operator++() 
			{
				Node *child = NULL;
				if (_n != &_dummy) //si on est a la fin  
					_dummy.left = _n;
				if (_n == &_dummy)
				{
					if (_dummy.left != NULL)
						_n = _dummy.left;
					return(*this);
				}
				if (_n->parent == NULL && _n->right == NULL)
				{
					_dummy.left = _n;
					_n = &_dummy;
					return (*this);
				}
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
			map_iterator operator++(int) {map_iterator temp = *this; ++(*this); return(temp);} 
			map_iterator& operator--() 
			{
				Node *child = NULL;
				if (_n != &_dummy) //si on est a la fin  
					_dummy.left = _n;
				if (_n == &_dummy) // Si on est sur le noeud de cassos mais qu on change de cote on revient en arriere
				{
					if (_dummy.left != NULL)
						_n = _dummy.left;
					return(*this);
				}
				if (_n->parent == NULL && _n->left == NULL) 
				{
					_dummy.left = _n;
					_n = &_dummy;
					return (*this);
				}
				if (!_n->left && _n->parent != NULL)  // Si un parent et pas de fils a gauche 
				{
					do				
					{
						child = _n;
						_n = _n->parent;
						if (child == _n->right) // si on est un fils droit c est qu on a atteint le fils inferieur 
							return(*this);
						if (_n->parent == NULL && child != _n->right) // si aucun element trouve
						{
							_n = &_dummy;
							return (*this);
						}
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
				if ((&a._dummy == a._n) && (&_dummy == _n))
				{
					return (1);
				}
				if (_n == a._n)
					return (1);
				else 
					return (0);
			}
			bool operator!=(const map_iterator &a) const 	
			{
				return (!(operator==(a)));
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
					_dummy.color = static_cast<color_t>(3);
					if (assign.base()->color == static_cast<color_t>(3))
					{
						_dummy = *(assign.base());
						_n = &_dummy;
					}
				}
				return *this; 
			}
			bool operator!=(map_iterator& other)
			{
				if (_n == &_dummy && other._n == &other._dummy)
					return (false);
				return (_n != other._n);
			}
			bool operator==(map_iterator& other)
			{
				if (_n == &_dummy && other._n == &other._dummy)
					return (true);
				return (_n == other._n);
			}


	};
//--------------------------------------------------------------------------------------//
//                                   Reverse iterator                                   //
//--------------------------------------------------------------------------------------//

/*
template <typename T, typename Node, typename Content>
	class reverse_map_iterator {
		public :
			typedef	std::bidirectional_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::size_t size_type;
			typedef void difference_type;
			typedef Content* pointer;
			typedef Content& reference;

			pointer		base() const { }

			reverse_map_iterator(): _n(NULL) {}
			reverse_map_iterator(reverse_map_iterator const &copy): _last(copy._last) 
			{
				if (copy._n == &copy._dummy)
						_n = &_dummy;
					else
						_n = copy._n;
			}
			reverse_map_iterator(Node* ptr):_n(ptr) {}
			reverse_map_iterator(Node* ptr, bool end):_n(ptr)
			{
				if (end == true)
				{
					_last = _n;
					_n = &_dummy;
				}
			}
			reference operator*() const {return (_n->content);}
			pointer operator->() {return (&(_n->content));}
			reverse_map_iterator& operator--() 
			{
				Node *child = NULL;
				if (_n == &_dummy && _last != NULL)
				{
					_n = _last;
					return(*this);
				}
				if (_n->parent == NULL && _n->right == NULL)
				{
					_n = &_dummy;
					return (*this);
				}
				if (!_n->right && _n->parent != NULL) 
				{
					do				
					{
						child = _n;
						_n = _n->parent;
						if (child == _n->left)
							return(*this);
						if (_n->parent == NULL && child != _n->left)
							return (*this);
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
			reverse_map_iterator operator++(int) {reverse_map_iterator temp = *this; ++(*this); return(temp);} 
			reverse_map_iterator& operator++() 
			{
				Node *child = NULL;
				_last = _n;
				if (_n == &_dummy)
					return (*this);
				if (_n->parent == NULL && _n->left == NULL)
				{
					_n = &_dummy;
					return (*this);
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
						{
							_n = &_dummy;
							return (*this);
						}
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
			reverse_map_iterator operator--(int) {reverse_map_iterator temp = *this; --(*this); return(temp);} 
			bool operator==(const reverse_map_iterator &a) const 	
			{
				(void)a;
				return (1);
			}
			bool operator!=(const reverse_map_iterator &a) const 	
			{
				(void)a;
				return (1);
			}
			void friend iter_swap(reverse_map_iterator &a, reverse_map_iterator &b)
			{
				reverse_map_iterator c(a); 
				a._ptr = b._ptr;
				b._ptr = c._ptr;
			}
			reverse_map_iterator& operator=(const reverse_map_iterator &assign) 
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
			bool operator!=(reverse_map_iterator& other)
			{
				if (_n == &_dummy && other._n == &other._dummy)
					return (false);
				return (_n != other._n);
			}
			bool operator==(reverse_map_iterator& other)
			{
				if (_n == &_dummy && other._n == &other._dummy)
					return (true);
				return (_n == other._n);
			}
		private : 
			Node *_n;
			Node *_last;
			Node _dummy;
	};
	*/

}

#endif