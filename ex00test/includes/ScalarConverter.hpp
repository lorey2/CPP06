/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:32:47 by lorey             #+#    #+#             */
/*   Updated: 2025/07/01 11:49:22 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <string>

class ScalarConverter
{
	public:
		static void convert(const std::string& input);

	private:
		ScalarConverter(){};
		~ScalarConverter(){};
		ScalarConverter(const ScalarConverter &scalar_conv){ (void)scalar_conv; };
		ScalarConverter& operator=(const ScalarConverter &scalar_conv){ (void)scalar_conv; return  (*this);};

		static bool isChar(const std::string& input, char *c);
		static bool isInt(const std::string& input, int *i);
		static bool isFloat(const std::string& input, float *f);
		static bool isDouble(const std::string& input, double *d);
};
