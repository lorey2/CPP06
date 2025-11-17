/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   A.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:50:04 by lorey             #+#    #+#             */
/*   Updated: 2025/07/03 15:08:03 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Base.hpp"

class A : public Base {
	public:
		A(){std::cout << "A constructor" << std::endl;}
};
