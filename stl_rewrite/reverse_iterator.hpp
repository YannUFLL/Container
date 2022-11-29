/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:20:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/11/29 22:43:19 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_trait.hpp"

namespace ft {
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
		return (lhs.base() < rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() > rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
template<class Iterator1, class Iterator2>
	bool operator-(const ft::reverse_iterator<Iterator1> &lhs, const ft::reverse_iterator<Iterator2> &rhs)
	{
		return (lhs.base() + rhs.base());
	}
	template<class Iterator1, class Iterator2>
	bool operator+(const ft::reverse_iterator<Iterator1> &lhs,const ft::reverse_iterator<Iterator2> &rhs)
	{
		// Iterator 1 = const_iterator 
		// Iterator 2 = Iterator
		Iterator1 a = lhs.base();
		Iterator2 b = rhs.base(); // pourquoi dans cette situation y'a t'il une conversion de type 
		return (a - b);
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