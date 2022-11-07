
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "alloc.hpp"
#include "choose_if_const.hpp"

template<typename T, typename Alloc = std::allocator<T> >
class vector_base{
	public : 
	typedef T value_type;
	typedef T* pointer;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::size_t size_type;

		allocator_type _alloc;
		pointer _v;
		pointer _space;
		pointer _last;

	vector_base(const allocator_type &a ): _alloc(a), _v(NULL)  
	{
	}
	vector_base(const allocator_type& a, size_type n): _alloc(a), _v(_alloc.allocate(n)) {

		_space = _v + n; _last = _v + n;
	}
	~vector_base()
	{
		if (_v != NULL)
		{
			_alloc.deallocate(_v, _last - _v);
			_v = NULL;
		}
	}
};

template <typename T, typename Alloc = std::allocator<T> >
class vector : public vector_base<T, Alloc>
{
	typedef T value_type;
	typedef T* pointer;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::size_t size_type;

	public :
	template<bool> class vector_iterator;
	template<bool> class vector_reverse_iterator;
	typedef typename vector<T, Alloc>:: template vector_iterator<true> const_iterator;
	typedef typename vector<T, Alloc>:: template vector_iterator<false> iterator;
	typedef typename vector<T, Alloc>:: template vector_reverse_iterator<true> const_reverse_iterator;
	typedef typename vector<T, Alloc>:: template vector_reverse_iterator<false> reverse_iterator;

	template <bool CONST>
	class vector_iterator : public std::iterator<
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T>
	{
		public :
			typedef typename choose_type<CONST, reference, const_reference>::type reference;
			typedef typename choose_type<CONST, reference, const_pointer>::type pointer;
			vector_iterator(): _ptr(NULL) {}
			vector_iterator(pointer ptr) {this->_ptr = ptr;}
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
		template <bool CONST>
		class vector_reverse_iterator : public std::iterator<
		std::random_access_iterator_tag,
		T,
		T,
		T*,
		T> 
	{
		public :
			typedef typename choose_type<CONST, reference, const_reference>::type reference;
			typedef typename choose_type<CONST, reference, const_pointer>::type pointer;
			vector_reverse_iterator(): _ptr(NULL) {}
			vector_reverse_iterator(pointer ptr) {this->_ptr = ptr;}
    		reference operator*() const {return *_ptr;}
    		pointer operator->() {return _ptr;}
			reverse_iterator& operator++() {_ptr--; return(*this);} 
			reverse_iterator operator++(int) {reverse_iterator temp = *this; --(*this); return(temp);} 
			reverse_iterator& operator--() {_ptr++; return(*this);} 
			reverse_iterator operator--(int) {reverse_iterator temp = *this; ++(*this); return(temp);} 
			reverse_iterator& operator+=(value_type n){this->_ptr -= n;return(*this);}
			reverse_iterator& operator-=(value_type n){this->_ptr += n;return(*this);}
			reverse_iterator friend operator+(reverse_iterator a, size_type n) {reverse_iterator it(a._ptr); it += n ; return (it);}
			reverse_iterator friend operator-(reverse_iterator a, size_type n) {reverse_iterator it(a._ptr); it -= n ; return (it);}
			friend size_type operator-(const reverse_iterator &a, const reverse_iterator &b) 
			{
				return (a._ptr - b._ptr);
			}
			bool operator==(const reverse_iterator &a) const 	
			{
				return (a._ptr == this->_ptr);
			}
			bool operator!=(const reverse_iterator &a) const 	
			{
				return (a._ptr != this->_ptr);
			}
			bool friend operator>(reverse_iterator const &a, reverse_iterator const &b) 
			{
				return (a._ptr < b._ptr);
			}
			bool friend operator<(reverse_iterator const &a, reverse_iterator const &b) 
			{
				return (a._ptr > b._ptr);
			}
			bool friend operator>=(reverse_iterator const &a, reverse_iterator const &b) 
			{
				return (a._ptr <= b._ptr);
			}
			bool friend operator<=(reverse_iterator const &a, reverse_iterator const &b) 
			{
				return (a._ptr >= b._ptr);
			}
			void friend iter_swap(reverse_iterator &a, reverse_iterator &b)
			{
				reverse_iterator c(a); 
				a._ptr = b._ptr;
				b._ptr = c._ptr;
			}
		private : 
			pointer _ptr;
	};
	iterator begin() const {return(iterator(this->_v)); }
	iterator end() const {return(iterator(this->_space));} // return a invalid memorty address, is just to determin when the boundary was reach
	reverse_iterator rbegin() const {return(reverse_iterator(this->_space)); }
	reverse_iterator rend() const {return(reverse_iterator(this->_v));} // return a invalid memorty address, is just to determin when the boundary was reach

	explicit vector(const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, 0) {}

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, n )
	{
		uninitialized_fill<T*,T,Alloc>(this->_v, this->_space, val, this->_alloc);
	}


	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0): vector_base<T,Alloc>(alloc, 0)
	{
		size_type n = 0;
		for (InputIterator ptr = first; ptr != last; ptr++)
			n++;
		this->_alloc.allocate(n);
		uninitialized_copy(this->_v, this->_last, first, this->_alloc );
	}


	vector(const vector& x): vector_base<T,Alloc>(x._alloc, x.size()) 
	{
		uninitialized_copy(x.begin(), x.end(), this->_v, this->_alloc);
	}

	~vector()	{destroy_element();this->~vector_base<T>();}	
	void destroy_element()
	{
		for (pointer p = this->_v; p != this->_space; p++)
		{
			this->_alloc.destroy(p);
		}
	}
	/* CAPACITY */
	size_type size() const {return size_type(end() - begin());}
	size_type maxsize() const {return (static_cast<size_type>(std::numeric_limits<size_type>::max()));}
	size_type capacity() {return (this->_last - this->_v);}
	void	resize(size_type n, value_type val = value_type())
	{
		reallocate(n,val);
	}
	void	reserve(size_type n) 
	{
		if (n > this->maxsize())
			throw (std::length_error("vector::reserve"));
		if (n > this->capacity())
		{
			reallocate(n);
		}
	}
	void shrink_to_fit()
	{
		reallocate(this->size());
	}
	bool empty() {return(this->_v == this->_space - 1);}
	private : 

	void	reallocate(size_type n)
	{
		size_type nbr_elements = this->size();
		pointer ptr = this->_alloc.allocate(n);
		uninitialized_copy(ptr, ptr + n, this->_v, this->_alloc);
		this->~vector();
		this->_v = ptr; 
		this->_space = ptr + nbr_elements; 
		this->_last = ptr + n;
	}
	void	reallocate(size_type n, value_type val)
	{
		pointer ptr = this->_alloc.allocate(n);
		uninitialized_copy(ptr, ptr + std::min(this->size(), n), this->_v, this->_alloc);
		uninitialized_fill(ptr + std::min(this->size(),n), ptr + n, val, this->_alloc);
		this->~vector();
		this->_v = ptr; 
		this->_space = ptr + n; 
		this->_last = ptr + n;
	}
	template <typename Type>
	size_type	return_pos(Type a) const 
	{
		return((&*a) - this->_v);
	}
	public :
	/* ELEMENT ACCESS */
	reference operator[](size_type n) {return (*(this->_v + n));}
	const_reference operator[](size_type n) const {return (*(this->_v + n));}
	reference at(size_type n) 
	{
		if (n > this->size || n < 0)
			throw(std::out_of_range("vector"));
		else 
			return (*(this->_v + n));
	}
	const_reference at(size_type n) const 
	{
		if (n > this->size || n < 0)
			throw(std::out_of_range("vector"));
		else 
				return (*(this->_v + n));
	}
	reference front() { return (*(begin()));}
	const_reference front() const { return (*(begin()));}
	reference back() {return (*(end() - 1));}
	const_reference back() const {return (*(end() - 1));}
	value_type* data()  {return (this->_v);}
	const value_type* data() const  {return (this->_v);}
	/* MODIFIER */
	template <class InputIterator> 
	void assign(InputIterator first, InputIterator last)
	{
		size_type n;	
		for (InputIterator ptr = first; ptr != last; ptr++)
			n++;
		if (n > this->size())
		{
			pointer ptr = this->_alloc.allocate(n);
			uninitialized_copy(ptr, ptr + n, first, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n; 
			this->_last = ptr + n;
		}
		else 
		{
			this->destroy_element();
			uninitialized_copy(this->_v, this->_v + n, first, this->_alloc);
			this->_space = this->_v + n;
		}
	}
	void assign (size_type n, const value_type& val)
	{
		if (n > this->size())
		{
			pointer ptr = this->_alloc.allocate(n);
			uninitialized_fill(ptr, ptr + n, val, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n; 
			this->_last = ptr + n;
		}
		else 
		{
			this->destroy_element();
			uninitialized_fill(this->_v, this->_v + n, val, this->_alloc);
			this->_space = this->_v + n;
		}
	}
	void	push_back(const value_type& val)
	{
		if (this->_space == this->_last)
		{
			reallocate(this->size() * 2);
			this->_alloc.construct((this->_space), val);
			this->_space+= 1;
		}
		else 
		{
			this->_alloc.construct((this->_space), val);
			this->_space+= 1;
		}
	}
	void	pop_back(void)
	{
		if (this->size() > 0)
		{
			this->_alloc.destroy(this->_space -1);
			this->_space+= -1;
		}
	}
	/*
	iterator insert (iterator position, const value_type& val)  
	{

	}*/
	void insert (iterator position, size_type n, const value_type& val)  
	{
		size_type pos; 
		size_type nbr_elements;
		if (this->size() + n > this->capacity())
		{
			nbr_elements = this->size();
			pos = return_pos(position);
			pointer ptr = this->_alloc.allocate(n + nbr_elements);
			uninitialized_copy(ptr,  ptr + pos, this->_v, this->_alloc);
			uninitialized_fill(ptr + pos, ptr + pos + n, val, this->_alloc);
			uninitialized_copy(ptr + pos + n,  ptr + n + nbr_elements, this->_v, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n + nbr_elements; 
			this->_last = ptr + n + nbr_elements; 
		}
		else 
		{
			pointer ptr = this->_v; 
			iterator test(ptr);
			ptr += this->size() + n ;
			reverse_iterator it(ptr);
			reverse_iterator v(this->rbegin());
			nbr_elements = this->size();
			pos = return_pos(position);
			uninitialized_copy_and_destroy(it,  it + (nbr_elements - pos + 1), v, this->_alloc);
			uninitialized_fill(it + (nbr_elements - pos + 1), it + (nbr_elements - pos + 1) + n, val, this->_alloc);
			this->_space = ptr; 
		}
	}

	iterator insert(iterator position, const value_type& val)
	{
		insert(position, 1, val);
		return(position++);
	}
	template <class InputIterator>
	void insert(const_iterator position, InputIterator first, InputIterator last,typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
	{
		size_type pos; 
		size_type nbr_elements;
		size_type n = 0;
		for (InputIterator ptr = first; ptr != last; ptr++)
			n++;
		if (this->size() + n > this->capacity())
		{
			nbr_elements = this->size();
			pos = return_pos(position);
			pointer ptr = this->_alloc.allocate(n + nbr_elements);
			uninitialized_copy(ptr,  ptr + pos, this->_v, this->_alloc);
			uninitialized_copy(ptr + pos, ptr + pos + n, first, this->_alloc);
			uninitialized_copy(ptr + pos + n,  ptr + n + nbr_elements, this->_v, this->_alloc);
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n + nbr_elements; 
			this->_last = ptr + n + nbr_elements; 
		}
		else 
		{
			pointer ptr = this->_v; 
			iterator test(ptr);
			ptr += this->size() + n ;
			reverse_iterator it(ptr);
			reverse_iterator v(this->rbegin());
			nbr_elements = this->size();
			pos = return_pos(position);
			uninitialized_copy_and_destroy(it,  it + (nbr_elements - pos + 1), v, this->_alloc);
			uninitialized_copy(it + (nbr_elements - pos + 1), it + (nbr_elements - pos + 1) + n, first, this->_alloc);
			this->_space = ptr; 
		}
	}
	iterator erase( const_iterator first, const_iterator last )
	{
		size_type n = 0;
		for (const_iterator ptr = first; ptr != last; ptr++)
			n++;	
		for (const_iterator ptr = first; ptr != last; ptr++)
			this->alloc.destroy(&*ptr);
		if (&*last != this->_last)
			uninitialized_copy_and_destroy(first, this->end() - n, last, this->alloc);
	}
	iterator erase (iterator position)
	{
		this->alloc.destroy(&*position);
		iterator copy(&*position);
		if (*&position != this->_last)
			uninitialized_copy_and_destroy(position, this->end() - 1, copy, this->alloc());
	}
};


template<typename T> void swap(vector_base<T>& a, vector_base<T> &b)
{
	swap(a._alloc, b._alloc);swap(a._v, b._v);swap(a._space,b._space);swap(a._last,b._last);
}

#endif