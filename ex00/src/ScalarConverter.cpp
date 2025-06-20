/* ************************************************************************** */
/*																			*/
/*														:::		::::::::	 */
/*	 ScalarConverter.cpp								:+:		:+:	:+:	 */
/*													+:+ +:+		 +:+	 */
/*	 By: lorey <lorey@student.42lausanne.ch>		+#+	+:+		 +#+		*/
/*												+#+#+#+#+#+	 +#+			 */
/*	 Created: 2025/06/11 21:09:11 by lorey			 #+#	#+#			 */
/*	 Updated: 2025/06/12 01:09:42 by lorey			###	 LAUSANNE.ch		 */
/*																			*/
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <climits>
#include <iostream>
#include <cstdlib>
#include <cerrno>

void	ScalarConverter::convert(const std::string& input){
	if (isChar(input))
		std::cout << "char" << std::endl;
	else if (isInt(input))
		std::cout << "int" << std::endl;
	else if (isFloat(input))
		std::cout << "float" << std::endl;
	else if (isDouble(input))
		std::cout << "double" << std::endl;
}

bool ScalarConverter::isChar(const std::string& input){
	return(input.size() == 1 || (input.size() == 3 && (input[0] == '\'' && input[2] == '\'')));
}

bool ScalarConverter::isInt(const std::string& input) {
    if (input.empty() || input.find_first_not_of(" \t\n\v\f\r+-0123456789") != std::string::npos) {
        return false;
    }

    char* endptr = NULL;
    errno = 0;

    long value = std::strtol(input.c_str(), &endptr, 10);
    if (errno == ERANGE) {
        return false;
    }
    if (*endptr != '\0') {
        return false;
    }
    return (value >= INT_MIN && value <= INT_MAX);
}

/* bool ScalarConverter::isFloat(const std::string& input){
	std::size_t	i = 0;
	bool isBfComa = false;
	bool isAfComa = false;

	while (i < input.size() && std::isspace(input[i]))
		i++;
	if (i == input.size())
		return false;
	if (input[i] == '+' || input[i] == '-')
		i++;
	if (i == input.size())
		return false;
	for (; i < input.size() && std::isdigit(input[i]); i++)
		isBfComa = true;
	if (i == input.size() && isBfComa)
		return true;
	if (input[i] == '.')
		i++;
	if (i == input.size() && isBfComa)
		return true;
	for (; i < input.size() && std::isdigit(input[i]); i++){
		isAfComa = true;
	}
	if (i == input.size() && (isBfComa || isAfComa))
		return true;
	if (i == input.size() - 1 && (input[input.size() - 1] == 'F' || input[input.size() - 1] == 'f'))
		if (isBfComa || isAfComa)
			return true;
	return false;
} */

bool ScalarConverter::isFloat(const std::string& input) {
    // A simple check to quickly discard clearly invalid strings
    if (input.empty() || input.find_first_not_of(" \t\n\v\f\r+-0123456789.eEfFinfa") != std::string::npos) {
        // This check is a bit loose but can quickly filter out bad inputs.
        // A more precise check is done by strtod.
    }
    if (input == "nanf" || input == "+inff" || input == "-inff") return true;

    char* endptr = NULL;
    errno = 0; // Reset errno

    // Use strtod, as there is no strtof in C++98
    std::strtof(input.c_str(), &endptr);

    if (errno == ERANGE) { // Value was out of range for a double
        // For floats, infinity is often a valid state, so we don't return false here.
        // We let the logic below handle it.
    }

    // If nothing was converted, it's invalid.
    if (endptr == input.c_str()) {
        return false;
    }

    // Skip trailing whitespace
    while (*endptr != '\0' && std::isspace(static_cast<unsigned char>(*endptr))) {
        endptr++;
    }

    // Valid if we are at the end...
    if (*endptr == '\0') {
        return true;
    }
    // ... or if the only thing left is a valid 'f' suffix
    if ((*endptr == 'f' || *endptr == 'F') && *(endptr + 1) == '\0') {
        return true;
    }

    return false;
}

// isDouble is even simpler, as it doesn't need to check for the 'f'
bool ScalarConverter::isDouble(const std::string& input) {
    if (input.empty()) return false;
    if (input == "nan" || input == "+inf" || input == "-inf") return true;

    char* endptr = NULL;
    errno = 0;
    std::strtod(input.c_str(), &endptr);
    
    if (errno == ERANGE) {} // inf/-inf is a valid double
    if (endptr == input.c_str()) return false;
    
    while (*endptr != '\0' && std::isspace(static_cast<unsigned char>(*endptr))) {
        endptr++;
    }
    
    return (*endptr == '\0');
}
