/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:24:44 by lorey             #+#    #+#             */
/*   Updated: 2025/11/17 14:24:48 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <climits>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cmath>    // Required for floor

#include <iostream>
#include <string>
#include <sstream> // Required for stringstream

bool toChar(const std::string& input, char& out_char) {
    if (input.empty()) {
        return false;
    }

    // Case 1: Input is a single character.
    if (input.length() == 1 && !isdigit(input[0])) {
        out_char = input[0];
        return true;
    }

    // Case 2: Input is a C++ character literal.
    if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') {
        out_char = input[1];
        return true;
    }

    // Case 3: Input is a number (int or float notation).
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    if (ss >> double_val) {
        char remaining_char = 0;
        ss >> remaining_char;
        if (ss.fail() || (remaining_char == 'f' && ss.eof())) {
            if (double_val == floor(double_val)) { // Check for whole number
                int int_val = static_cast<int>(double_val);
                if (int_val >= 0 && int_val <= 127) { // Check ASCII range
                    out_char = static_cast<char>(int_val);
                    return true;
                }
            }
        }
    }
    return false; // All conversion attempts failed.
}

// The printChar function now uses the helper function.
void printChar(const std::string& input) {
    char c = 0;
    if (toChar(input, c)) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            std::cout	<< "char: '"
						<< c << "'"
						<< std::endl;

			std::cout 	<< "int: "
						<< static_cast<int>(c)
						<< std::endl;

			std::cout	<< "float: "
						<< std::fixed
						<< std::setprecision(1)
						<< static_cast<float>(c)
						<< 'f'
						<< std::endl;

			std::cout	<< "double: "
						<< std::setprecision(1)
						<< static_cast<double>(c)
						<< std::endl;
        } else {
            std::cout << "char: Non-printable" << std::endl;

			std::cout 	<< "int: "
						<< static_cast<int>(c)
						<< std::endl;

			std::cout	<< "float: "
						<< std::fixed
						<< std::setprecision(1)
						<< static_cast<float>(c)
						<< 'f'
						<< std::endl;

			std::cout	<< "double: "
						<< std::setprecision(1)
						<< static_cast<double>(c)
						<< std::endl;
		}
    } else {
        std::cout << "char: impossible" << std::endl;
    }
}

void	ScalarConverter::convert(const std::string& input){
	if (isChar(input))
		printChar(input);
	else if (isInt(input))
		std::cout << "int" << std::endl;
	else if (isFloat(input))
		std::cout << "float" << std::endl;
	else if (isDouble(input))
		std::cout << "double" << std::endl;
	else
		std::cout << "nothing" << std::endl;
}


bool ScalarConverter::isChar(const std::string& input) {
    if (input.empty()) {
        return false;
    }

    // Case 1: Input is a single, non-digit character (e.g., "a", "*")
    if (input.length() == 1) {
        return (true);
    }

    // Case 2: Input is a C++ character literal (e.g., "'a'", "'*'")
    if (input.length() == 3 && input[0] == '\'' && input[2] == '\'') {
        return std::isprint(static_cast<unsigned char>(input[1]));
    }

    // --- REVISED NUMERIC LOGIC ---
    // Case 3: Input is a number (int or float notation) representing a printable char.
    std::stringstream ss;
    ss << input;
    double double_val = 0.0;

    // Step 1: Try to parse a double. If this fails, it's not a number.
    if (ss >> double_val) {
        // Step 2: Check what's left in the string. It should be empty or contain just 'f'.
        char remaining_char = 0;
        ss >> remaining_char; // Try to read one more character

        // This condition is true if:
        // - Nothing was left to read (ss.fail() is true), e.g., for "42" or "42.0"
        // - OR a single 'f' was read and then nothing else was left (ss.eof()), e.g., for "42.0f"
        if (ss.fail() || (remaining_char == 'f' && ss.eof())) {
            
            // Step 3: Check if the parsed double is a whole number.
            // We do this by comparing it to its floor.
            if (double_val == floor(double_val)) {

                // Step 4: Check if the whole number is a printable ASCII character.
                int int_val = static_cast<int>(double_val);
                if (int_val >= 0 && int_val <= 127) {
                    return (true);
                }
            }
        }
    }
    // --- END OF REVISED LOGIC ---

    return false;
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
