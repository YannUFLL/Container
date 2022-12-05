/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 19:14:54 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/05 09:37:10 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_HPP
#define MAP_HPP

#include <iterator>
#include "map_iterator.hpp"
#include <functional>
#include <memory>
#include "../stl_rewrite/ft_pair.hpp"
#include "../stl_rewrite/stl_iterator.hpp"
#include "../stl_rewrite/enable_if.hpp"


namespace ft {

template <typename Key, typename T, typename Compare = std::less<Key>,
typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	struct node;
	enum color_t {red, black, double_black};
	public :
	typedef Key key_type;
	typedef T   mapped_type; 
	typedef ft::pair<const Key, T> value_type; 
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator:: template rebind<node>::other node_allocator;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename std::allocator_traits<Allocator>::pointer pointer;
	typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
	typedef typename ft::Wrapper_it<ft::map_iterator<T, node, const value_type> > const_iterator;
	typedef typename ft::Wrapper_it<ft::map_iterator<T, node, value_type> > iterator;
	typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef typename ft::reverse_iterator<iterator> reverse_iterator;

	private : 
	struct node 
	{
		node& operator=(node& other) {left = other.left; right = other.right; parent = other.parent; color = other.color; return(*this);}
		node(): left(), right(), parent(), color(red), content() {}
		struct node *left;
		struct node *right;
		struct node *parent; 
		color_t color;
		value_type  content;
		~node() {}
	};
	public :
		class value_compare
		{
			protected:
				key_compare _comp;
			public : 
				value_compare(key_compare c): _comp(c) {}	
				bool operator()(const value_type& lhs, const value_type& rhs)
				{
					return (_comp(lhs.first, rhs.first));
				}
		};
//--------------------------------------------------------------------------------------//
//                                     Constructors                                     //
//--------------------------------------------------------------------------------------//

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
		_root(NULL), _alloc_node(node_allocator()), _alloc_pair(alloc), _comp(comp) {}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator& alloc = Allocator()):
		_root(NULL), _alloc_node(node_allocator()), _alloc_pair(alloc), _comp(comp)
		{
			for(;first != last; first++)
				insert(*first);
		}

		map(const map& other): _root(NULL), _alloc_node(other._alloc_node), _alloc_pair(other._alloc_pair), _comp(other._comp)
		{
			map::const_iterator first = other.begin();	
			map::const_iterator last = other.end();	
			for(;first != last; first++)
				insert(*first);
		}

		~map()
		{
			this->clear();
		}
	
//--------------------------------------------------------------------------------------//
//                                    Red Black Tree                                    //
//--------------------------------------------------------------------------------------//

	private :
		node *_root;
		node_allocator _alloc_node;
		allocator_type _alloc_pair;
		key_compare _comp;

		node* parent(node *n) {return (n->parent);}
		node* grandparent(node *n) 
		{
			node *p = parent(n);
			if (p == NULL)
				return (NULL);
			return (parent(p));
		}
		node* brother(node *n) 
		{
			node *p = parent(n);
			if (p == NULL)
				return (NULL);
			if (n == p->left)
				return(p->right);
			else
				return (p->left);
		}
		node* uncle(node* enfant)
		{
			node *p = parent(enfant);
			node *g = grandparent(enfant);
			if (g == NULL)
				return (NULL);
			return (brother(p));
		}
		void left_rotation(node *x)
		{
			struct node *y = x->right; 
			x->right = y->left; 
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else 
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		  void right_rotation(node *x)
		{
			struct node *y = x->left; 
			x->left = y->right; 
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else 
				x->parent->left = y;
			
			y->right = x;
			x->parent = y;
		}
		node*  search_element(key_type const &key) const
		{
			if (_root == NULL)
				return (NULL);
			node* pos = _root;
			while (1)
			{
				if (pos == NULL)
					return (NULL);
				if (!_comp(key, pos->content.first) && !_comp(pos->content.first, key)) 
					return (pos); 
				if (_comp(key, pos->content.first))
				{
						pos = pos->left;
				}
				else 
				{
						pos = pos->right;
				}
			}
		}
		void recursive_insert(node *root, node *n)
		{
			if (root != NULL && _comp(n->content.first, root->content.first)) 
			{
				if (root->left != NULL)
				{
					recursive_insert(root->left, n);
					return ;
				}
				else 
					root->left = n;
			}
			else if (root != NULL)
			{
				if (root->right != NULL)
				{
					recursive_insert(root->right, n);
					return ;
				}
				else 
					root->right = n;
			}
			n->parent = root;
			n->color = red;
		}
		void insert_case1(node *n)
		{
			if (parent(n) == NULL)
			{
				n->color = black;
				_root = n;
			}
		}
		void insert_case2(node *n)
		{
			(void)n;
			return ;
		}
		void insert_case3(node *n)
		{
			parent(n)->color = black;
			uncle(n)->color = black;
			node *g = grandparent(n);
			g->color = red;
			repair_tree_insert(g);
			return ;
		}
		void insert_case4(node *n)
		{
			node *p = parent(n);
			node *g = grandparent(n);
			if (g->left && n == g->left->right)
			{
				left_rotation(p);
				n = n->left;
			}
			else if (g->right && n == g->right->left)
			{
				right_rotation(p);
				n = n->right;
			}
			insert_case5(n);
		}
		void	insert_case5(node *n)
		{
			node *p = parent(n);
			node *g = grandparent(n);
			if (n == p->left)
				right_rotation(g);
			else 
				left_rotation(g);
			p->color = black;
			g->color = red;
		}
		void repair_tree_insert(node* n)
		{
			if (parent(n) == NULL)
				insert_case1(n);
			else if (parent(n)->color == black)
				insert_case2(n);
			else if (uncle(n) != NULL && uncle(n)->color == red)
				insert_case3(n);
			else 
				insert_case4(n);
		}
		void	insert(node* n)
		{
			recursive_insert(_root, n);
			repair_tree_insert(n);
		}
		//void	insert(iterator position, node );
		node* if_one_child_rt(node *n)
		{
			if (n == NULL)
				return (NULL);
			if (n->left != NULL && n->right != NULL)
				return (NULL);
			if (n->left != NULL)
				return(n->left);
			if (n->right != NULL)
				return(n->right);
			return(NULL);
		}
		void	erase_case_1or0_child(node *n)
		{
			node *child = if_one_child_rt(n);
			if (n->color == red && !child)
			{
				if (n->parent && n->parent->left == n)
					n->parent->left = NULL;
				else if (n->parent) 
					n->parent->right = NULL;
				delete_node(n);
			}
			else if (child && child->color == red)
			{
				child->parent = n->parent;
				child->color = black;
				if (n->parent == NULL)
					_root = child;
				if (n->parent && n->parent->left == n)
					n->parent->left = child;
				else if (n->parent) 
					n->parent->right = child;
				delete_node(n);
			}
			else if (n == _root && n->left == NULL && n->right == NULL)
			{
				delete_node(n);
				_root = NULL;
			}
			else if (n->color == black)
			{
				n->color = double_black;
				erase_rebalancing_tree(n, 0);
			}
		}
		node *search_inorder(node *n)
		{
			n = n->left;
			while (n->right != NULL)
				n = n->right;
			return(n);
		}
		void swap_env(node *a, node *b)
		{
			if (a->parent && a == a->parent->left) //SKIP car le root n'a pas de parents
				a->parent->left = b; 
			else if (a->parent) // SKIP car le route n'a pas de parents 
				a->parent->right = b; 
			if (a->left && a->left != b)		
				a->left->parent = b; // set le parent du fils fauche sur b
			if (a->right && a->right != b)
				a->right->parent = b;// set le parent du fils droit sur b
		}
		void swap(node *a, node *b)
		{
			if (a == _root)
				_root = b;
			else if (b == _root)
				_root = a;
			swap_env(a, b);
			swap_env(b, a);
			node *a_parent = a->parent;
			node *a_left = a->left;
			node *a_right = a->right;
			color_t a_color = a->color; 
			if (b->parent == a)
				a->parent = b;
			else
				a->parent = b->parent;
			a->left = b->left;
			a->right = b->right;
			a->color = b->color;
			if (a_parent == b)
				b->parent = a;
			else   
				b->parent = a_parent;
			b->left = a_left;
			b->right = a_right;
			b->color = a_color;
		}
		void erase_case_2_child(node *n)
		{
			node *inorder = NULL;
			inorder = search_inorder(n);
			swap(n, inorder);
			erase_case_1or0_child(n);
		}
			node* rt_red_child(node *n)
		{
			if (n == NULL)
				return (NULL);
			if (n->right != NULL && n->right->color == red)
				return(n->right);
			if (n->left != NULL && n->left->color == red)
				return(n->left);
			return(NULL);
		}
		void erase_rebalancing_tree(node *n, bool already_delete)
		{
			node *b = brother(n);
			node *p = parent(n);
			node *child_brother = rt_red_child(b);
			
			if (b->color == black && ((b->left && b->left->color == red) || (b->right && b->right->color == red))) // CASE ONE
			{
				color_t old_color = p->color;
				if (n == p->right && child_brother == b->right)
				{
					left_rotation(b);
					b->color = red;
					b->parent->color = black;
					child_brother = b;
				}
				if (n == p->left && child_brother == b->left)
				{
					right_rotation(b);
					b->color = red;
					b->parent->color = black;
					child_brother = b;
				}
				if (n == p->left)
				{
					left_rotation(p);
					p->parent->right->color = black;
					p->parent->left->color = black;
				}
				else	
				{
					right_rotation(p);
					p->parent->right->color = black;
					p->parent->left->color = black;
				}
				if (already_delete != 1)
				{
				if (n->parent && n->parent->left == n)
					n->parent->left = NULL;
				else if (n->parent)
					n->parent->right = NULL;
					delete_node(n);
				}
				if (already_delete == 1 && n->color == double_black)
					n->color = black;
				p->parent->color = old_color;
			}
			else if (b->color == black)
			{  
				b->color = red;
				if (already_delete != 1)
				{
					if (n->parent && n->parent->left == n)
						n->parent->left = NULL;
					else if (n->parent)
						n->parent->right = NULL;
					delete_node(n);
				}	
				if (p->color == red)
				{
					p->color = black;
					if (already_delete == 1 && n->color == double_black)
					n->color = black;
				}
				else if (p != _root)
				{
					if (already_delete == 1  && n->color == double_black)
						n->color = black;
					p->color = double_black;
					erase_rebalancing_tree(p, 1);
				}
			}
			else if (b->color == red)
			{
				if (b == p->left)
					right_rotation(p);
				else   
					left_rotation(p);
				p->color = red;
				b->color = black;
				erase_rebalancing_tree(n, already_delete);
			}
		}
	node* new_node(value_type content = value_type())
	{
		node *ptr = _alloc_node.allocate(1);
			_alloc_node.construct(ptr);
		try
		{
			_alloc_pair.construct(&ptr->content, content);
		}
		catch (...)
		{
			_alloc_node.deallocate(ptr, 1);
			throw;
		}
		return (ptr);
	}
	void	delete_node(node *n)
	{
		//_alloc_pair.destroy(&n->content);
		_alloc_node.destroy(n);
		_alloc_node.deallocate(n, 1);
	}
	void	erase_element(node *element)
	{
		if (element == NULL)
			return ;
		if (element->right == NULL || element->left == NULL)
			erase_case_1or0_child(element);
		else 
			erase_case_2_child(element);
	}
//--------------------------------------------------------------------------------------//
//                                                                                      //
//                                    Public Members                                    //
//                                                                                      //
//--------------------------------------------------------------------------------------//

	 public :

	map& operator=(const map& other)
	{
		if (this != &other)
		{
			map tmp(other);
			swap(tmp);
		}
		return (*this);
	}
//--------------------------------------------------------------------------------------//
//                                      Iterators                                       //
//--------------------------------------------------------------------------------------//

	iterator begin() 
	{
		node *beg;
		beg = _root;
		if (_root == NULL)
		{
			typename ft::map_iterator<T, node,value_type> begin(_root, 1);
			return (begin);
		}
		while (beg->left != NULL)
		{
			beg = beg->left;
		}
		iterator begin(beg);
		return (begin);
	}
	iterator end()
	{
		node *beg;
		beg = _root;
		if (_root == NULL)
		{
			typename ft::map_iterator<T, node,value_type> it(_root, 1);
			return (it);
		}
		while (beg->right != NULL)
		{
			beg = beg->right;
		}
		typename ft::map_iterator<T, node,value_type> it(beg, 1);
		return (it);
	}
	reverse_iterator rbegin()
	{
		reverse_iterator it(this->end());
		return (it);
	}
		reverse_iterator rend() 
	{
		reverse_iterator it(this->begin());	
		return (it);
	}
	const_iterator begin() const 
	{
		node *beg;
		beg = _root;
		if (_root == NULL)
		{
			typename ft::map_iterator<T, node, const value_type> begin(_root, 1);
			return (begin);
		}
		while (beg->left != NULL)
		{
			beg = beg->left;
		}
		const_iterator begin(beg);
		return (begin);
	}
	const_iterator end() const
	{
		node *beg;
		beg = _root;
		if (_root == NULL)
		{
			typename ft::map_iterator<T, node, const value_type> it(_root, 1);
			return (it);
		}
		while (beg->right != NULL)
		{
			beg = beg->right;
		}
		typename ft::map_iterator<T, node, const value_type> it(beg, 1);
		return (it);
	}
	const_reverse_iterator rbegin() const
	{
		const_reverse_iterator it(this->cend());
		return (it);
	}
	const_reverse_iterator rend() const 
	{
		const_reverse_iterator it(this->cbegin());
		return (it);
	}



//--------------------------------------------------------------------------------------//
//                                       Capacity                                       //
//--------------------------------------------------------------------------------------//

	bool empty() const {return (!_root);}
	size_type size() const 
	{
		const_iterator start = this->begin();
		const_iterator end = this->end();
		int i = 0;
		for (;start != end; start++, i++);
		return (i);
	}
	size_type max_size() const
	{
		return (_alloc_node.max_size());
	}
//--------------------------------------------------------------------------------------//
//                                   Element Access                                     //
//--------------------------------------------------------------------------------------//

	mapped_type& operator[](const key_type& k) 
	{
		node *element = search_element(k);
		if (element == NULL)
		{
			element = new_node(value_type(k, mapped_type()));
			insert(element);
		} 
		return (element->content.second);
	}
	mapped_type& at(const Key& key)
	{
		node *element = search_element(key);
		if (!element)
			throw std::out_of_range("map::at: key not found map");
		else
			return (element->content.second);
	}
	const mapped_type& at(const Key& key) const
	{
		node *element = search_element(key);
		if (!element)
			throw std::out_of_range("map::at: key not found map");
		else
			return (element->content.second);
	}
//--------------------------------------------------------------------------------------//
//                                       Modifier                                       //
//--------------------------------------------------------------------------------------//

	ft::pair<iterator, bool> insert(const ft::pair<const Key, mapped_type> &value) 
	{
		node *element = search_element(value.first);
		if (element == NULL)
		{
			element = new_node(value);
			iterator it(element); 
			insert(element);
			ft::pair<iterator, bool> pair;
			pair.first = it;
			pair.second = true;
			return (pair);
		}
		iterator it(element); 
		ft::pair<iterator, bool> pair;
		pair.first = it;
		pair.second = false;
		return (pair);
	}
	iterator insert(iterator pos, const value_type& value) 
	{
		(void)pos;
		return(insert(value).first);
	}
	template<class InputIt>
	void insert(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0)
	{
		while (first != last)
			insert(*first++);
	}
	size_type	erase(const key_type &k)
	{
		node *element = search_element(k);
		if (element == NULL)
			return (0);
		erase_element(element);
		return(1);
	}
	void erase(iterator first, iterator last)
	{
		for (;first != last;)
		{
			node *element = search_element(first->first); 
			++first;
			erase_element(element);
		}
	}
	void erase(iterator position)
	{
			node *element = search_element(position->first); 
			erase_element(element);
	}
	void swap(map& x)
	{
		std::swap(_root, x._root);
		std::swap(_alloc_node, x._alloc_node);
		std::swap(_alloc_pair, x._alloc_pair);
		std::swap(_comp, x._comp);
	}

	void clear()
	{
		erase(this->begin(), this->end());
	}
//--------------------------------------------------------------------------------------//
//                                      Observer                                       //
//--------------------------------------------------------------------------------------//
key_compare key_comp() const
{
	return (_comp);
}

value_compare value_comp() const
{ 
	return value_compare(_comp);
}
//--------------------------------------------------------------------------------------//
//                                      Operations                                      //
//--------------------------------------------------------------------------------------//
	size_type count (const key_type& k) const	
	{
		node *element = search_element(k); 
		return (element ? true: false);
	}
	iterator find(const Key& key)
	{
		node *element = search_element(key); 
		if (!element)
		{
			iterator tmp(this->end());
			return (tmp);
		}
		else
		{
			iterator tmp(element);
			return (tmp);
		}
	}
	const_iterator find(const Key& key) const
	{
		node *element = search_element(key); 
		if (!element)
		{
			const_iterator tmp(this->end());
			return (tmp);
		}
		else
		{
			const_iterator tmp(element);
			return (tmp);
		}
	}
	iterator lower_bound(const Key& key)
	{
		iterator it = this->begin();
		while (_comp(it->first, key) && it != this->end())
			++it;
		return (it);
	}
	const_iterator lower_bound(const Key& key) const
	{
		const_iterator it = this->begin();
		while (_comp(it->first, key) && it != this->end())
			++it;
		return (it);
	}
		iterator upper_bound(const Key& key)
	{
		iterator it = this->begin();
		while (_comp(it->first, key) && it != this->end())
			++it;
		if (it->first == key)
			++it;
		return (it);
	}
	const_iterator upper_bound(const Key& key) const
	{
		const_iterator it = this->begin();
		while (_comp(it->first, key) && it != this->end())
			++it;
		if (it->first == key)
			++it;
		return (it);
	}
	
	ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const
	{
		const_iterator lower = lower_bound(key);
		const_iterator upper = upper_bound(key);
		ft::pair<const_iterator, const_iterator> pair;
		pair.first = lower;
		pair.second = upper;
		return (pair);
	}

		ft::pair<iterator,iterator> equal_range(const Key& key)
	{
		iterator lower = lower_bound(key);
		iterator upper = upper_bound(key);
		ft::pair<iterator, iterator> pair;
		pair.first = lower;
		pair.second = upper;
		return (pair);
	}


//--------------------------------------------------------------------------------------//
//                                       Operator                                       //
//--------------------------------------------------------------------------------------//
};

template<class Key, class T, class Compare, class Alloc>
bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs,
								const ft::map<Key,T,Compare,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	else
	{
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator ite = lhs.end();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();
		while (it != ite)
		{
			if (it->first != it2->first || it->second != it2->second)
				return (false);
			++it;
			++it2;
		}
		return (true);
	}
}
template<class Key, class T, class Compare, class Alloc>
bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs,
								const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs,
							 const ft::map<Key,T,Compare,Alloc>& rhs)
{
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator ite = lhs.end();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it2 = rhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator it2e = rhs.end();
	while (it != ite)
	{
		if (it2 == it2e)
			return (false);
		if (it->first < it2->first)
			return (true);
		if (it->first > it2->first)
			return (false);
		if (it->second < it2->second)
			return (true);
		if (it->second > it2->second)
			return (false);
		++it;
		++it2;
	}
	return (it2!=it2e);
}

template<class Key, class T, class Compare, class Alloc>
bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs,
							 const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (rhs < lhs);
}

template<class Key, class T, class Compare, class Alloc>
bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs,
								const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs > rhs));
}

template<class Key, class T, class Compare, class Alloc>
bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs,
								const ft::map<Key,T,Compare,Alloc>& rhs)
{
	return (!(lhs < rhs));
}

}


//--------------------------------------------------------------------------------------//
//                                      Allocator                                       //
//--------------------------------------------------------------------------------------//





#endif