/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stl_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:20:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/03 17:09:16 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STL_ITERATOR_HPP
#define STL_ITERATOR_HPP

#include "iterator_trait.hpp"

namespace ft {
	template<class It>
class Wrapper_it
{
protected : 
	It current;
	typedef iterator_trait<It> traits_type;
public : 
	typedef typename traits_type::pointer pointer;
	typedef typename traits_type::difference_type difference_type;
	typedef typename traits_type::reference reference;
	typedef typename traits_type::iterator_category iterator_category;
	typedef typename traits_type::value_type value_type;
	typedef std::size_t size_type;
	Wrapper_it():current(It()) {};
	Wrapper_it(const It &itr) : current(itr) {}
	template<class U>
	Wrapper_it(const Wrapper_it<U>& other): current(other.base()) {}

	reference operator*() const
	{
		return *(current);
	}
	pointer operator->() const
	{
		return (&(operator*()));
	}
	Wrapper_it& operator++() {++current; return *this;}
	Wrapper_it operator++(int) {Wrapper_it tmp = *this; ++(*this); return tmp;}

	Wrapper_it& operator--() {--current; return *this;}
	Wrapper_it operator--(int) {Wrapper_it tmp = *this; --(*this); return tmp;}
	reference operator[](size_type n) {return (current[n]);}

	Wrapper_it operator+(difference_type n)
	{
		Wrapper_it rt(current + n);
		return (rt);
	}
	Wrapper_it operator-(difference_type n)
	{
		Wrapper_it rt(current - n);
		return (rt);
	}
	Wrapper_it &operator+=(difference_type n)
	{
		current += n;
		return (*this);
	}
	Wrapper_it &operator-=(difference_type n)
	{
		current -= n;
		return (*this);
	}
	It base() const {return current;}
};
template<class Iterator1, class Iterator2>
	bool operator==(const ft::Wrapper_it<Iterator1> &lhs, const ft::Wrapper_it<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator!=(const ft::Wrapper_it<Iterator1> &lhs, const ft::Wrapper_it<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

template<class It>
class reverse_iterator
{
protected : 
	It current;
	typedef iterator_trait<It> traits_type;
public : 
	typedef typename traits_type::pointer pointer;
	typedef typename traits_type::difference_type difference_type;
	typedef typename traits_type::reference reference;
	typedef std::size_t size_type;
	reverse_iterator():current(It()) {};
	explicit reverse_iterator(It itr) : current(itr) {}
	template<class U>
	reverse_iterator(const reverse_iterator<U>& other): current(other.base()) {}

	reference operator*() const
	{
		return *std::prev(current);
	}
	pointer operator->() const
	{
		return (&(operator*()));
	}
	reverse_iterator& operator++() {--current; return *this;}
	reverse_iterator operator++(int) {reverse_iterator tmp = *this; ++(*this); return tmp;}

	reverse_iterator& operator--() {++current; return *this;}
	reverse_iterator operator--(int) {reverse_iterator tmp = *this; --(*this); return tmp;}
	reference operator[](size_type n) {return ((std::prev(current))[-n]);}

	reverse_iterator operator+(difference_type n)
	{
		reverse_iterator rt(current - n);
		return (rt);
	}
	reverse_iterator operator-(difference_type n)
	{
		reverse_iterator rt(current + n);
		return (rt);
	}
	reverse_iterator &operator+=(difference_type n)
	{
		current -= n;
		return (*this);
	}
	reverse_iterator &operator-=(difference_type n)
	{
		current += n;
		return (*this);
	}
	It base() const {return current;}

};
template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() == rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() != rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() < lhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() <= lhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() > lhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() >= lhs.base());
	}
template<class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (rhs.base() - lhs.base());
	}
	template<class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type operator+(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		Iterator1 a = lhs.base();
		Iterator2 b = rhs.base(); 
		return (b + a);
	}
		template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter> &it)
	{
		reverse_iterator<Iter> rt(it.base() - n);
		return (rt);
	}

			template<class Iter>
	reverse_iterator<Iter> operator-(typename reverse_iterator<Iter>::difference_type n, const ft::reverse_iterator<Iter> &it)
	{
		reverse_iterator<Iter> rt(it.base() + n);
		return (rt);
	}


}
#endif