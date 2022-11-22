
#ifndef MAP_HPP
#define MAP_HPP

#include "../stl_rewrite/ft_pair.hpp"
#include "map_iterator.hpp"
#include <cstring>
#include <functional>
#include <memory>
#include <initializer_list>

namespace ft {
template <typename Key, typename T, typename Compare = std::less<Key>,
typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map
{
	struct node;
	typedef Key key_type;
	typedef T   mapped_type; 
	typedef ft::pair<const Key, T> value_type; 
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef std::allocator<node> node_allocator;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef typename std::allocator_traits<Allocator>::pointer pointer;
	typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;

	public :
	typedef typename ft::map_iterator<T, node, const value_type> const_iterator;
	typedef typename ft::map_iterator<T, node, value_type> iterator;

	private : 
	enum color_t {red, black, double_black};
	struct node 
	{
		node(): left(), right(), parent(), color(red), content() {}
		struct node *left;
		struct node *right;
		struct node *parent; 
		color_t color;
		value_type  content;
	};
	public :
		/********* CONSTRUCTOR *********/
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
		_root(NULL), _alloc_node(node_allocator()), _alloc_pair(alloc), _comp(comp), _dummy(){}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare &comp = Compare(), const Allocator& alloc = Allocator()):
		_alloc_node(node_allocator()), _alloc_pair(alloc), _comp(comp), _dummy()
		{
			for(;first != last; first++)
				insert(*first);
		}

		map(const map& other, const Allocator &alloc): 
		_alloc_node(node_allocator()), _alloc_pair(alloc), _comp(other._comp), _dummy()
		{

		}
	
		/*  
		map(std::initializer_list<value_type> init, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()):
		_alloc_node(node_allocator()), _alloc_pair(alloc), _comp(comp) {}
		*/


	private :
		node *_root;
		node_allocator _alloc_node;
		allocator_type _alloc_pair;
		key_compare _comp;
		node _dummy;

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
		node*  search_element(key_type const &key)
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
		void insert_from_position(node *position, node *n)
		{
			bool superior = 0;
			if (_comp(n->content.first, position->content.first))
				superior = 1;
			if (superior == 1)
			{
				while (_comp(n->content.first, position->content.first) && position != _root)
				{
					position = position->parent;
				}
			}
			else 
			{
				while (!_comp(n->content.first, position->content.first) && position != _root)
				{
					position = position->parent;
				}
			}
			recursive_insert(position, n);
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
		void erase_rebalancing_tree(node *n, bool already_delete)
		{
			node *b = brother(n);
			node *p = parent(n);
			node *child_brother = if_one_child_rt(b);
			
			if (b->color == black && ((b->left && b->left->color == red) || (b->right && b->right->color == red))) // CASE ONE
			{
				color_t old_color = p->color;
				if (n == p->right && child_brother == b->right)
				{
					left_rotation(b);
					b->color = red;
					child_brother->color = black;
					child_brother = b;
				}
				if (n == p->left && child_brother == b->left)
				{
					right_rotation(b);
					b->color = red;
					child_brother->color = black;
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
				p->parent->color = old_color;
			}
			else if (b->color == black) 
			{  
				b->color = red;
				if (p->color == red)
					p->color = black;
				if (already_delete != 1)
				{
					if (n->parent && n->parent->left == n)
						n->parent->left = NULL;
					else if (n->parent)
						n->parent->right = NULL;
					delete_node(n);
				}
				else if (p != _root)
				{
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
				erase_rebalancing_tree(p, 0);
			}
		}
	node* new_node(value_type content = value_type())
	{
		node *ptr = _alloc_node.allocate(1);
		_alloc_node.construct(ptr);
		_alloc_pair.construct(&ptr->content, content);
		return (ptr);
	}
	void	delete_node(node *n)
	{
		_alloc_pair.destroy(&n->content);
		_alloc_node.destroy(n);
		_alloc_node.deallocate(n, 1);
	}
	 public :
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
	map& operator=(const map& other)
	{
		if (this != &other)
		{
			map tmp(other);
			swap(tmp);
		}
		return (*this);
	}
	iterator begin()  
	{
		node *beg;
		beg = _root;
		if (_root == NULL)
		{
			iterator begin(_root);
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
			iterator it(_root);
			return (it);
		}
		while (beg->right != NULL)
		{
			beg = beg->right;
		}
		iterator it(beg, 1);
		return (it);
	}

	ft::pair<iterator, bool> insert(const ft::pair<const int, int> &value)
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
	ft::pair<iterator, bool> insert(iterator pos, const value_type& value) 
	{
		node *element = search_element(value.first);
		if (element == NULL)
		{
			element = new_node(value);
			iterator it(element); 
			insert_from_positon(pos, value);
		}
		return (element);
	}
	template<class InputIt>
	void insert(InputIt first, InputIt last, typename std::enable_if<!std::is_integral<InputIt>::value>::type* = 0)
	{
		while (first != last)
			insert(*first++);
	}

	size_type	erase(const key_type &k)
	{
		node *element = search_element(k);
		if (element == NULL)
			return (0);
		if (element->right == NULL || element->left == NULL)
			erase_case_1or0_child(element);
		else 
			erase_case_2_child(element);
		return(1);
	}
};
}

#endif