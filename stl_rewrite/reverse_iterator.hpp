/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 09:20:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/11/24 18:32:41 by ydumaine         ###   ########.fr       */
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
	reverse_iterator():current(It()) {};
	explicit reverse_iterator(It itr) : current(itr) {}
	template<class U>
	explicit reverse_iterator(const U& other,std::enable_if<false, std::is_same<U, It> >): current(other.base()) {}

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
	friend bool operator==(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() == rhs.base());
	}
	friend bool operator!=(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() != rhs.base());
	}
	friend bool operator<(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() < rhs.base());
	}
	friend bool operator<=(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() <= rhs.base());
	}
	friend bool operator>(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() > rhs.base());
	}
	friend bool operator>=(reverse_iterator &lhs, reverse_iterator &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
};
}
#endif