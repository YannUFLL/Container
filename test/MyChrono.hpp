/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyChrono.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydumaine <ydumaine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 23:34:30 by ydumaine          #+#    #+#             */
/*   Updated: 2022/12/04 23:42:19 by ydumaine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHRONO_HPP
# define CHRONO_HPP

# include <iostream>
# include <string>
# include <chrono>
# include <sys/time.h>
# include <iomanip>


class MyChrono
{
	public:
		// Constructors
		MyChrono();
		MyChrono(const MyChrono &copy);
		
		// Destructor
		~MyChrono();
		
		// Operators
		MyChrono & operator=(const MyChrono &assign);
		void	begin();
		void	end();
		void	print_time(std::string const	str)	const;
	private:
		struct timeval _start;
		int _time_spent;
		static	int		time_diff(struct timeval *start, struct timeval *end);

		
};

#endif