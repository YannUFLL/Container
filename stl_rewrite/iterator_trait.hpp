/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_trait.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:53 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/04 23:36:21 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAIT
#define ITERATOR_TRAIT

// The purpose of these template is to provide type information of the iterator to the algorithms using them
// and if the iterator is a ptr we can't get those type because pointer doesn't have them, so that the reason why we specialize these template

namespace ft
{
template <typename IT>
	struct iterator_trait 
	{
		typedef typename IT::difference_type difference_type;
		typedef typename IT::value_type value_type;
		typedef typename IT::pointer pointer;
		typedef typename IT::reference reference;
		typedef typename IT::iterator_category iterator_category;

	};
	

template <typename IT>
	struct iterator_trait<IT *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef IT value_type;
		typedef IT* pointer;
		typedef IT& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

template <typename IT>
	struct iterator_trait<const IT *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef IT value_type;
		typedef const IT* pointer;
		typedef const IT& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};
}



#endif