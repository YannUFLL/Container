	template <bool CONST, typename T>
	class map_iterator : public std::iterator<
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T>
	{
		public :
				

			pointer		base() const { return _ptr; }

			vector_iterator(): _ptr(NULL) {}
			vector_iterator(pointer ptr):_ptr(ptr) {}
    		reference operator*() const {return *_ptr;}
    		pointer operator->() {return _ptr;}
			iterator& operator++() {_ptr++; return(*this);} 
			iterator operator++(int) {iterator temp = *this; ++(*this); return(temp);} 
			iterator& operator--() {_ptr--; return(*this);} 
			iterator operator--(int) {iterator temp = *this; --(*this); return(temp);} 
			iterator& operator+=(value_type n){this->_ptr += n;return(*this);}
			iterator& operator-=(value_type n){this->_ptr -= n;return(*this);}
			iterator friend operator+(iterator a, size_type n) {iterator it(a._ptr); it += n ; return (it);}
			iterator friend operator-(iterator a, size_type n) {iterator it(a._ptr); it -= n ; return (it);}
			friend size_type operator-(const iterator &a, const iterator &b) 
			{
				return (a._ptr - b._ptr);
			}
			bool operator==(const iterator &a) const 	
			{
				return (a._ptr == this->_ptr);
			}
			bool operator!=(const iterator &a) const 	
			{
				return (a._ptr != this->_ptr);
			}
			bool friend operator>(iterator const &a, iterator const &b) 
			{
				return (a._ptr > b._ptr);
			}
			bool friend operator<(iterator const &a, iterator const &b) 
			{
				return (a._ptr < b._ptr);
			}
			bool friend operator>=(iterator const &a, iterator const &b) 
			{
				return (a._ptr >= b._ptr);
			}
			bool friend operator<=(iterator const &a, iterator const &b) 
			{
				return (a._ptr <= b._ptr);
			}
			void friend iter_swap(iterator &a, iterator &b)
			{
				iterator c(a); 
				a._ptr = b._ptr;
				b._ptr = c._ptr;
			}
		private : 
			pointer _ptr;
	};