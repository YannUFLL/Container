/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:13 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/04 23:34:14 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	#ifndef MAP_ITERATOR_HPP
	#define MAP_ITERATOR_HPP

	#include "../stl_rewrite/enable_if.hpp"
	
	namespace ft 
	{
		template <typename T, typename Node, typename Content>
	class map_iterator {
		public :
			typedef	std::bidirectional_iterator_tag iterator_category;
			typedef T value_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef Content* pointer;
			typedef Content& reference;

			pointer		base() const { }

			map_iterator(): _n(&_dummy), _last(NULL), _dummy(), _same_add(), _same_sub(), _init(){
			}

			template < typename V >
			map_iterator(const map_iterator<T, Node, V> &copy,  typename ft::enable_if<!std::is_const<V>::value>::type* = 0): _last(copy._last), _same_add(copy._same_add), _same_sub(copy._same_sub), _init(copy._init)
			{
				if (copy._n == &copy._dummy)
					_n = &_dummy;
				else
					_n = copy._n;
			}
			
			map_iterator(const map_iterator &copy): _last(copy._last), _same_add(copy._same_add), _same_sub(copy._same_sub), _init(copy._init)
			{
				if (copy._n == &copy._dummy)
					_n = &_dummy;
				else
					_n = copy._n;
			}

			map_iterator(Node* ptr):_n(ptr), _last(NULL), _dummy(), _same_add(), _same_sub(), _init()
			{
			}
			map_iterator(Node* ptr, bool end):_n(ptr), _dummy(), _same_add(), _same_sub(), _init()
			{
				if (end == true)
				{
					_last = _n;
					_n = &_dummy;
				}
			}
			reference operator*() const {return (_n->content);}
			pointer operator->() {return (&(_n->content));}
			map_iterator& operator++() 
			{
				if (_init == 0)
					_init = 1;
				else if (_same_sub == 1)
					_same_sub = 0;
				else 
					_same_add = 1;
				Node *child = NULL;
				if (_n != &_dummy)
					_last = _n;
				if (_n == &_dummy && _last != NULL && _same_add == 0)
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
				if (_init == 0)
					_init = 1;
				else if (_same_add == 1)
					_same_add = 0;
				else 
					_same_sub = 1;
				Node *child = NULL;
				if (_n != &_dummy) //si on est a la fin  
					_last = _n;
				if (_n == &_dummy && _last != NULL && _same_sub == 0) // Si on est sur le noeud de cassos mais qu on change de cote on revient en arriere
				{
					_n = _last;
					return(*this);
				}
				if (_n->parent == NULL && _n->left == NULL) //Si pas de parent et pas a gauche fin de chaine 
				{
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
					if (assign._n == &assign._dummy)
						_n = &_dummy;
					else
						_n = assign._n;
					_last = assign._last;
					_same_add = assign._same_add;
					_same_sub = assign._same_sub;
					_init = assign._init;
				}
				return *this; 
			}
			template<typename T1, typename T2>
			bool friend operator!=(map_iterator <T, Node,T1>& lhs, map_iterator <T, Node,T2>& rhs)
			{
				if (lhs._n == &lhs._dummy && rhs._n == &rhs._dummy)
					return (false);
				return (lhs._n != rhs._n);
			}

			bool operator==(map_iterator& other)
			{
				if (_n == &_dummy && other._n == &other._dummy)
					return (true);
				return (_n == other._n);
			}
		public : 
			Node *_n;
			Node *_last;
			Node _dummy;
			bool _same_add;
			bool _same_sub;
			bool _init;
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