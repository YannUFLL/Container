/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:15:04 by ydumaine          #+#    #+#             */
/*   Updated: 2022/11/30 16:40:19 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft{

template<class T, class Container = ft::vector<T> >
class stack 
{
	private : 
		 Container c;
	public :
	typedef Container container_type;
	typedef typename Container::value_type value_type;
	typedef typename Container::size_type size_type;
	typedef typename Container::reference reference;
	typedef typename Container::const_reference const_reference;

	explicit stack(Container c = Container()):c(c) {}
	stack(const stack &other):c(other.c) {}
	~stack() {}
	stack& operator=(const stack& other) {c = other.c;}
	reference top() {return (c.back());}
	const_reference top() const {return (c.back());};
	size_type size() const {return (c.size());}
	void push(const value_type& value) {c.push_back(value);} 
	void pop() {c.pop_back();} 
	bool	empty() {return c.empty();}
friend bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c == rhs.c);
}
friend bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c != rhs.c);
}
friend bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c < rhs.c);
}
friend bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c <= rhs.c);
}
friend bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c > rhs.c);
}
friend bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
	return (lhs.c >= rhs.c);
}
};



template<class T, class Container >
void swap(ft::stack<T,Container>& lhs,
					ft::stack<T,Container>& rhs)
{
	lhs.swap(rhs);
}

}

#endif