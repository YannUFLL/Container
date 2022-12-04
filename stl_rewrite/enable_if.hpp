/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 12:55:57 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/03 18:35:48 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF
#define ENABLE_IF

namespace ft
{
//--------------------------------------------------------------------------------------//
//                                    STL::ENABLE_IF                                    //
//--------------------------------------------------------------------------------------//

	template<bool B, class T = void>
	struct enable_if{};

	template<class T>
	struct enable_if<true, T> {typedef T type;};

//--------------------------------------------------------------------------------------//
//                                   STL::IS_INTEGRAL                                   //
//--------------------------------------------------------------------------------------//

template <typename T>
struct is_integral {static const bool value = false;};

template <>
struct is_integral<bool> {static const bool value = true;};

template <>
struct is_integral<char> {static const bool value = true;};

template <>
struct is_integral<short> {static const bool value = true;};

template <>
struct is_integral<int> {static const bool value = true;};

template <>
struct is_integral<long> {static const bool value = true;};

template <>
struct is_integral<long long> {static const bool value = true;};

template <>
struct is_integral<unsigned char> {static const bool value = true;};

template <>
struct is_integral<unsigned short> {static const bool value = true;};

template <>
struct is_integral<unsigned long> {static const bool value = true;};

template <>
struct is_integral<unsigned long long> {static const bool value = true;};

}


#endif