/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:57:22 by lorey             #+#    #+#             */
/*   Updated: 2025/11/17 18:57:26 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cerrno>

//lit is just for literal
//
//if not isprint: non displayable
//if nan if <0 >127: impossible
static void printChar(double lit, bool isNaN, bool isInf) {
	std::cout << "char: ";
	if (isNaN || isInf || lit < 0 || lit > 127) {
		std::cout << "impossible";
	} else if (!std::isprint(static_cast<int>(lit))) {
		std::cout << "Non displayable";
	} else {
		std::cout << "'" << static_cast<char>(lit) << "'";
	}
	std::cout << std::endl;
}

// impossible if not in max-minint range
// or nan, inf
static void printInt(double lit, bool isNaN, bool isInf) {
	std::cout << "int: ";
	if (isNaN || isInf || lit < static_cast<double>(INT_MIN) || lit > static_cast<double>(INT_MAX)) {
		std::cout << "impossible";
	} else {
		std::cout << static_cast<int>(lit);
	}
	std::cout << std::endl;
}

//fixed is to force decimal notation
//setprecision is the num of digit after the point.
static void printFloat(double lit) {
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(lit) << "f" << std::endl;
}

static void printDouble(double lit) {
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(lit) << std::endl;
}


void ScalarConverter::convert(const std::string& input) {
	double  val = 0.0;
	char	*end = NULL;
	
	//check for specific input
	if (input == "nan" || input == "nanf")
		val = std::numeric_limits<double>::quiet_NaN();
	else if (input == "+inf" || input == "+inff")
		val = std::numeric_limits<double>::infinity();
	else if (input == "-inf" || input == "-inff")
		val = -std::numeric_limits<double>::infinity();
	// if it is a one char number we just static cast it in double
	else if (input.length() == 1 && !std::isdigit(input[0])) {
		val = static_cast<double>(input[0]);
	}
	// if it is a multichar we strtod it
	else {
		val = std::strtod(input.c_str(), &end);
		std::string remainder = end;
		if (input.empty() || (remainder.length() > 1) || (remainder.length() == 1 && remainder[0] != 'f')) {
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
	}
	//those function exist, why not use them?
	bool isNaN = std::isnan(val);
	bool isInf = std::isinf(val);

	//now that we have the val as a double we just have to print it
	printChar(val, isNaN, isInf);
	printInt(val, isNaN, isInf);
	printFloat(val);
	printDouble(val);
}
