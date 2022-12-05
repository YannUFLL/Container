/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:10 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/05 11:12:10 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../stl_rewrite/alloc.hpp"
#include "../utils/choose_if_const.hpp"
#include "../stl_rewrite/iterator_trait.hpp"
#include "../stl_rewrite/lexicographical_compare.hpp"
#include "../stl_rewrite/stl_iterator.hpp"
#include "../stl_rewrite/enable_if.hpp"

namespace ft{

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
	vector_base(const allocator_type& a, size_type n): _alloc(a) {
		if (n != 0)
			_v = _alloc.allocate(n); // warning trap. allocating with n = 0 still requests memory.
		else
			_v = NULL;
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
class vector : private vector_base<T, Alloc>
{
	public :
	typedef T value_type;
	typedef T* pointer;
	typedef Alloc allocator_type;
	typedef typename allocator_type::reference reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::const_pointer const_pointer;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	template<bool> class vector_iterator;
	template<bool> class vector_reverse_iterator;
	typedef typename vector<T, Alloc>:: template vector_iterator<true> const_iterator;
	typedef typename vector<T, Alloc>:: template vector_iterator<false> iterator;
	typedef typename ft::reverse_iterator<iterator> reverse_iterator;
	typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

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
			typedef typename choose_type<CONST, pointer, const_pointer>::type pointer;
			typedef typename choose_type<CONST, iterator, const_iterator>::type	iterator;
			typedef typename choose_type<CONST, const_iterator, iterator>::type	conversion;

		
			vector_iterator(const vector_iterator<false> &src):
				_ptr(src.base()) {

				}

			pointer		base() const { return _ptr; }

			vector_iterator(): _ptr(NULL) {}
			vector_iterator(pointer ptr):_ptr(ptr) {}
			reference operator*() const {return *_ptr;}
			pointer operator->() {return _ptr;}
			iterator& operator++() {_ptr++; return(*this);} 
			iterator operator++(int) {iterator temp = *this; ++(*this); return(temp);} 
			iterator& operator--() {_ptr--; return(*this);} 
			iterator operator--(int) {iterator temp = *this; --(*this); return(temp);} 
			iterator& operator+=(size_type n){this->_ptr += n;return(*this);}
			iterator& operator-=(size_type n){this->_ptr -= n;return(*this);}
			iterator operator+(size_type n) {iterator it(_ptr); it += n ; return (it);}
			iterator operator-(size_type n) {iterator it(_ptr); it -= n ; return (it);}
			reference operator[](size_type n) {return (*(_ptr + n));}
			vector_iterator& operator=(const vector_iterator &assign)
			{
				if (this != &assign)
					_ptr = assign._ptr;
				return (*this);
			}
			friend difference_type operator+(const iterator &a, const iterator &b) 
			{
				return (a._ptr + b._ptr);
			}
			friend iterator operator+(const size_type n, const iterator &b) 
			{
				iterator it(b._ptr); 
				it += n ;
				return (it);
			}
			friend difference_type operator-(const iterator &a, const iterator &b) 
			{
				return (a._ptr - b._ptr);
			}
			friend iterator operator-(const size_type n, const iterator &b) 
			{
				iterator it(b._ptr); 
				it -= n ;
				return (it);
			}
			bool operator==(const const_iterator &a) const 	
			{
				return (a.base() == this->_ptr);
			}
			bool operator!=(const const_iterator &a) const 	
			{
				return (a.base() != this->_ptr);
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
	iterator begin() {return(iterator(this->_v)); }
	iterator end() {return(iterator(this->_space));} // return a invalid memorty address, is just to determin when the boundary was reach
	const_iterator begin() const {return(const_iterator(this->_v)); }
	const_iterator end() const {return(const_iterator(this->_space));} // return a invalid memorty address, is just to determin when the boundary was reach
	reverse_iterator rbegin() {return(reverse_iterator(this->_space)); }
	reverse_iterator rend() {return(reverse_iterator(this->_v));} // return a invalid memorty address, is just to determin when the boundary was reach
	const_reverse_iterator rbegin() const {return(const_reverse_iterator(this->_space)); }
	const_reverse_iterator rend() const {return(const_reverse_iterator(this->_v));} // return a invalid memorty address, is just to determin when the boundary was reach

	explicit vector(const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, 0) {}

	explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()): vector_base<T,Alloc>(alloc, n )
	{
		uninitialized_fill<T*,T,Alloc>(this->_v, this->_space, val, this->_alloc);
	}


	template <typename InputIterator>
	vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0): vector_base<T,Alloc>(alloc, 0)
	{
		size_type n = 0;
		for (InputIterator ptr = first; ptr != last; ptr++)
			n++;
		this->_v = this->_alloc.allocate(n);
		this->_space = this->_v + n;
		this->_last = this->_v + n;
		uninitialized_copy(this->_v, this->_last, first, this->_alloc );
	}


	vector(const vector& x): vector_base<T,Alloc>(x._alloc, x.size()) 
	{
		const_iterator it = x.begin();
		uninitialized_copy(this->begin(), this->end(), it, this->_alloc);
	}

	vector& operator=(const vector& other)
	{
		if (this != &other)
		{
			vector tmp(other);
			swap(tmp);
		}
		return (*this);
	}

	~vector()	{destroy_all_elements();this->~vector_base<T>();}	
	
	void destroy_all_elements()
	{
		for (pointer p = this->_v; p != this->_space; p++)
		{
			this->_alloc.destroy(p);
		}
		this->_space = this->_v;
	}
	/* CAPACITY */
	size_type size() const {return size_type(end() - begin());}
	size_type max_size() const {return (std::min((size_type) std::numeric_limits<difference_type>::max(), this->_alloc.max_size()));}
	size_type capacity() const {return (this->_last - this->_v);}
	void	resize(size_type n, value_type val = value_type())
	{
		reallocate(n,val);
	}
	void	reserve(size_type n) 
	{
		if (n > this->max_size())
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
	bool empty() const {return(this->_v == this->_space);}
	private : 

	void	reallocate(size_type n)
	{
		size_type nbr_elements = this->size();
		pointer ptr = this->_alloc.allocate(n);
		uninitialized_copy(ptr, ptr + std::min(nbr_elements, n), this->_v, this->_alloc);
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
		if (n > this->size() || n < 0)
			throw(std::out_of_range("vector"));
		else 
			return (*(this->_v + n));
	}
	const_reference at(size_type n) const 
	{
		if (n > this->size() || n < 0)
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
	void assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
	{
		size_type n = 0;	
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
			this->destroy_all_elements();
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
			this->destroy_all_elements();
			uninitialized_fill(this->_v, this->_v + n, val, this->_alloc);
			this->_space = this->_v + n;
		}
	}
	void	push_back(const value_type& val)
	{
		if (this->_space == this->_last)
		{
			if (this->size() == 0)  
				reallocate(1);
			else
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
	void destroy_element(pointer start, pointer end)
	{
		for(;start != end; ++start)
			this->_alloc.destroy(start);
	}
	void insert (iterator position, size_type n, const value_type& val)  
	{
		size_type pos; 
		size_type nbr_elements;
		if (this->size() + n > this->capacity())
		{
			nbr_elements = this->size();
			pos = return_pos(position);
			size_type size_allocate = 0;
			if ((n + nbr_elements) < (nbr_elements * 2))
				size_allocate = nbr_elements * 2;
			else
				size_allocate = nbr_elements + n;
			pointer ptr = this->_alloc.allocate(n + nbr_elements);
			try 
			{
				uninitialized_copy(ptr,  ptr + pos, this->_v, this->_alloc);
			}
			catch (...)
			{
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			try 
			{
				uninitialized_fill(ptr + pos, ptr + pos + n, val, this->_alloc);
			}
			catch (...)
			{
				destroy_element(ptr, (ptr + pos));
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			try 
			{
				uninitialized_copy(ptr + pos + n,  ptr + n + nbr_elements, position, this->_alloc);
			}
			catch (...)
			{
				destroy_element(ptr, ptr + (pos + n));
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n + nbr_elements; 
			this->_last = ptr + size_allocate; 
		}
		else 
		{ 
			reverse_iterator start(this->end() + n); 
			reverse_iterator end(position); 
			reverse_iterator value(this->rbegin()); 
			uninitialized_copy_and_destroy(start, end, value, this->_alloc);
			end = end - n;
			uninitialized_fill(end, end + n, val, this->_alloc);
			this->_space = this->_space + n;
		}
	}

	iterator insert(iterator position, const value_type& val)
	{
		size_type pos;
		pos = return_pos(position); 
		insert(position, 1, val);
		iterator new_pos(this->begin() + pos);
		return(new_pos);
	}
	template <class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last,typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
	{
		size_type pos; 
		size_type nbr_elements;
		size_type n = 0;
		for (InputIterator ptr = first; ptr != last; ptr++)
			++n;
		if (this->size() + n > this->capacity())
		{
			nbr_elements = this->size();
			pos = return_pos(position);
			size_type size_allocate = 0;
			if ((n + nbr_elements) < (nbr_elements * 2))
				size_allocate = nbr_elements * 2;
			else
				size_allocate = nbr_elements + n;
			pointer ptr = this->_alloc.allocate(n + nbr_elements);
			try 
			{
				uninitialized_copy(ptr,  ptr + pos, this->_v, this->_alloc);
			}
			catch (...)
			{
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			try
			{
				uninitialized_copy(ptr + pos, ptr + pos + n, first, this->_alloc);
			}
			catch (...)
			{
				destroy_element(ptr, ptr + pos);
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			try 
			{
				uninitialized_copy(ptr + pos + n,  ptr + n + nbr_elements, position, this->_alloc);
			}
			catch (...)
			{
				destroy_element(ptr, ptr + (pos + n));
				this->_alloc.deallocate(ptr, size_allocate);
				throw;
			}
			this->~vector();
			this->_v = ptr; 
			this->_space = ptr + n + nbr_elements; 
			this->_last = ptr + size_allocate; 
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
			uninitialized_copy(position, position + n, first, this->_alloc);
			this->_space = ptr; 
		}
	}
	iterator erase( iterator first, iterator last )
	{
		if (first == last)
			return (last);
		size_type n = 0;
		for (iterator ptr = first; ptr != last; ptr++)
			n++;	
		for (iterator ptr = first; ptr != last; ptr++)
			this->_alloc.destroy(&*ptr);
		if (&*last != this->_last)
		{
			uninitialized_copy_and_destroy(first, (this->end() - n), last, this->_alloc);
			this->_space = this->_space - n;
			return (first);
		}
		this->_space = this->_space - n;
		return (this->end());
	}
	iterator erase (iterator position)
	{
		if (position == this->end())
			return (this->end());
		this->_alloc.destroy(&*position);
		iterator copy(&*(position + 1));
		if (*&position != this->_last)
			uninitialized_copy_and_destroy(position, this->end() - 1, copy, this->_alloc);
		this->_space = this->_space - 1;
		return (position);
	}
	void clear()
	{
		this->destroy_all_elements();
	}
	void swap(vector &other)
	{
		std::swap(this->_alloc, other._alloc);
		std::swap(this->_v, other._v);
		std::swap(this->_last, other._last);
		std::swap(this->_space, other._space);
	}
	friend void swap(vector &a, vector &b) {a.swap(b);}
};


template <class T, class Alloc>
bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename vector<T, Alloc>::const_iterator start = lhs.begin();
	typename vector<T, Alloc>::const_iterator end = lhs.end();
	typename vector<T, Alloc>::const_iterator start_rhs = rhs.begin();
	for (; start != end;)
	{
		if (*start != *start_rhs)
			return (false);
		++start;
		++start_rhs;
	}
	return (true);
}

template <class T, class Alloc>
bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	if (lhs == rhs)
		return (false);
	return (true);
}

template <class T, class Alloc>
bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
{
	return (!(lhs < rhs));
}

template<typename T> void swap(vector_base<T>& a, vector_base<T> &b)
{
	swap(a._alloc, b._alloc);swap(a._v, b._v);swap(a._space,b._space);swap(a._last,b._last);
}

}

#endif