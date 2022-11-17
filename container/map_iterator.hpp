	template <bool CONST, T>
	class map_iterator : public std::iterator<
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T>
	{
		public :
			typedef typename choose_type<CONST, reference, const_reference>::type reference;
			typedef typename choose_type<CONST, pointer, const_pointer>::type pointer;
			typedef typename choose_type<CONST, iterator, const_iterator>::type	iterator;
			typedef typename choose_type<CONST, const_iterator, iterator>::type	conversion;
		
			template <bool B>
			vector_iterator(const vector_iterator<B> &src):
				_ptr(src.base()) {}
				

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