/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   C.hpp                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:50:04 by lorey             #+#    #+#             */
/*   Updated: 2025/07/03 15:10:14 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Base.hpp"

class C : public Base {
	public:
		C(){std::cout << "B constructor" << std::endl;}
};
