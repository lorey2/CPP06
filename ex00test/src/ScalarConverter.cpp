/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:55:48 by lorey             #+#    #+#             */
/*   Updated: 2025/06/30 20:52:09 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <climits>
#include <limits>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <float.h>

void handleDouble(const std::string input) {
	if (input == "nan" || input == "nanf") {
		std::cout	<< "double: "
					<< "nan"
					<< std::endl;
		return ;
	}
	if (input == "+inff" || input == "+inf") {
		std::cout	<< "double: "
					<< "+inf"
					<< std::endl;
		return ;
	}
	if (input == "-inff" || input == "-inf") {
		std::cout	<< "float: "
					<< "-inf"
					<< std::endl;
		return ;
	}
	if (input.length() == 1 && !isdigit(input[0])) {
		std::cout	<< "double: "
					<< std::fixed
					<< std::setprecision(1)
					<< static_cast<double>(input[0])
					<< std::endl;
		return ;
    }
	if (input.length() == 3 && (input[0] == '\'' && input[2] == '\'')){
		std::cout	<< "double: "
					<< std::fixed
					<< std::setprecision(1)
					<< static_cast<double>(input[1])
					<< std::endl;
		return ;
	}
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.peek() == EOF)) {
			            float float_val = static_cast<float>(double_val);
			std::cout	<< "double: "
						<< std::fixed
						<< std::setprecision(1)
						<< float_val
						<< std::endl;
			return ;

        } else {
			//42a / 42.0x
			std::cout	<< "double: "
						<< "impossible (not a valid double notation)"
						<< std::endl;
			return ;
		}
	} else {
		//abc
		std::cout	<< "double: "
					<< "impossible (not a valid double notation)"
					<< std::endl;
		return ;
	}


}


bool ScalarConverter::isChar(const std::string &input, char *c) {
	if (input.size() == 1 && !std::isdigit(input[0])){
		*c = input[0];
		return true;
	}
	if (input.size() == 3 && input[0] == '\'' && input[2] == '\'' && !std::isdigit(input[0])) {
		*c = input[1];
		return true;
	}
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;
    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.peek() == EOF)) {
            if (double_val == floor(double_val)) {
                int int_val = static_cast<int>(double_val);
                if (int_val >= 0 && int_val <= 127) {
					if (isprint(static_cast<unsigned char>(int_val))) {
						*c = static_cast<unsigned char>(int_val);
						return true;
					} else {
						//for ex \0 non displayable
						*c = 'n';
						return false;

					}
				} else {
					//too big or negetive numbers
					*c = 'r';
					return false;
				}
            } else {
				//42.58
				*c = 'a';
				return false;
			}
        } else {
			//42a / 42.0x
			*c = '0';
			return false;
		}
	} else {
		//abc
		*c = '0';
		return false;
	}
}

void castChar(char c) {
	std::cout << "char: '" << c << "'" << std::endl;
	std::cout << "int: " << static_cast<int>(c) << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(c) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(c) << std::endl;
}

bool ScalarConverter::isInt(const std::string& input, int *i) {
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.peek() == EOF)) {
			if (double_val < static_cast<double>(INT_MIN) || double_val > static_cast<double>(INT_MAX)){
				//overflow
				*i = 1;
				return false;
			}
            if (double_val == floor(double_val)) {
                int int_val = static_cast<int>(double_val);
				*i = int_val;
				return true;
            } else {
				//42.58
				*i = 2;
				return false;
			}
        } else {
			//42a / 42.0x
			*i = 0;
			return false;
		}
	} else {
		//abc
		*i = 0;
		return false;
	}
}

void castInt(int i, char c) {
	if (c == 'n') {
		std::cout << "char: " << "not displayable" << std::endl;
	} else if(c == 'r'){
		std::cout << "char: " << "impossible (too big or negative)" << std::endl;
	} else {
		std::cout << "impossible (idk why xD)" << std::endl;
	}
	std::cout << "int: " << i << std::endl;
	std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(i) << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(i) << std::endl;

}

bool ScalarConverter::isFloat(const std::string& input, float *f) {
	if (input == "nanf") {
		//*f = 0.0f / 0.0f;
		*f = std::numeric_limits<float>::quiet_NaN();
		return true;
	}
	if (input == "+inff") {
		*f = std::numeric_limits<float>::infinity();
		return true;
	}
	if (input == "-inff" || input == "-inf") {
		*f = -std::numeric_limits<float>::infinity();
		return true;
	}
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.peek() == EOF)) {
			if (double_val < static_cast<float>(FLT_MIN) || double_val > static_cast<float>(FLT_MAX)){
				*f = 1;
				return false;
			}
            float float_val = static_cast<float>(double_val);
			*f = float_val;
			return true;

        } else {
			//42a / 42.0x
			*f = 0;
			return false;
		}
	} else {
		//abc
		*f = 0;
		return false;
	}
}

void castFloat(int i, char c, float f) {
	if(c == 'r'){
		std::cout << "char: " << "impossible (too big or negative)" << std::endl;
	}
	else if (c == 'a'){
		std::cout << "char: " << "impossible (coma number)" << std::endl;
	} else if (c == '0'){
		std::cout << "char: " << "impossible (no sense)" << std::endl;
	} else {
		std::cout << "char: " << "impossible (idk why xD)" << std::endl;
	}
	if (i == 1) {
		std::cout << "int: " <<  "impossible (overflow)" << std::endl;
	} else if (i == 2) {
		std::cout << "int: " <<  "impossible (coma number)" << std::endl;
	} else if (i == 0){
		std::cout << "int: " << "impossible (no sense)" << std::endl;
	} else {
		std::cout << "int" << "impossible (idk why xD)" << std::endl;
	}

	std::cout << "float: " << std::fixed << std::setprecision(1) << f << "f" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << static_cast<double>(f) << std::endl;

}

bool ScalarConverter::isDouble(const std::string& input, double *d) {
	if (input == "nan") {
		*d = std::numeric_limits<double>::quiet_NaN();
		return true;
	}
	if (input == "+inf") {
		*d = std::numeric_limits<double>::quiet_NaN();
		return true;
	}
	if (input == "-inf") {
		return true;
	}
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.peek() == EOF)) {
			*d = double_val;
			return true;

        } else {
			//42a / 42.0x
			return false;
		}
	} else {
		//abc
		return false;
	}

}

void castDouble(int i, char c, float f, double d) {
	if(c == 'r'){
		std::cout << "char: " << "impossible (too big or negative)" << std::endl;
	}
	else if (c == 'a'){
		std::cout << "char: " << "impossible (coma number)" << std::endl;
	} else if (c == '0'){
		std::cout << "char: " << "impossible (no sense)" << std::endl;
	} else {
		std::cout << "char: " << "impossible (idk why xD)" << std::endl;
	}
	if (i == 1) {
		std::cout << "int: " <<  "impossible (overflow)" << std::endl;
	} else if (i == 2) {
		std::cout << "int: " <<  "impossible (coma number)" << std::endl;
	} else if (i == 0) {
		std::cout << "int: " << "impossible (no sense)" << std::endl;
	} else {
		std::cout << "int" << "impossible (idk why xD)" << std::endl;
	}
	if (f == 1) {
		std::cout << "float: overflow" << std::endl;
	}
	std::cout << "float: " << "impossible (double number)" << std::endl;
	std::cout << "double: " << std::fixed << std::setprecision(1) << d << std::endl;
}

void ScalarConverter::convert(const std::string &input) {
	char c = 0;
	int i = 0;
	float f = 0;
	double d = 0;

	if (isChar(input, &c)) {
		castChar(c);
	} else if (isInt(input, &i)) {
		castInt(i, c);
	} else if (isFloat(input, &f)) {
		castFloat(i, c, f);
	} else if (isDouble(input, &d)) {
		castDouble(i, c, f, d);
	} else {
		std::cout << "no cast are disponible with your (bad) input" << std::endl;
	}

//	handleChar(input);
//	handleInt(input);
//	handleFloat(input);
//	handleDouble(input);
}
