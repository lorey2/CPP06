/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:03:16 by lorey             #+#    #+#             */
/*   Updated: 2025/11/17 19:01:00 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <cassert>
#include <iostream>
#include <ostream>

int main() {
	Data* original_data = new Data();
	original_data->test = "Hello, World!";

	std::cout << "--- Step 1: Original Data ---" << std::endl;
	std::cout << "Original pointer address: " << original_data << std::endl;
	std::cout << "Original data content: \"" << original_data->test << "\"" << std::endl;
	std::cout << std::endl;

	//Serialize the pointer.
	std::cout << "--- Step 2: Serialization ---" << std::endl;
	uintptr_t serialized_ptr = Serializer::serialize(original_data);
	std::cout << "Serialized value (as integer): " << serialized_ptr << std::endl;
	std::cout << std::endl;


	//Deserialize the integer back into a pointer.
	std::cout << "--- Step 3: Deserialization ---" << std::endl;
	Data* deserialized_data = Serializer::deserialize(serialized_ptr);
	std::cout << "Deserialized pointer address: " << deserialized_data << std::endl;
	std::cout << "Content from deserialized pointer: \"" << deserialized_data->test << "\"" << std::endl;
	std::cout << std::endl;


	//Verification.
	std::cout << "--- Step 4: Verification ---" << std::endl;
	assert(original_data == deserialized_data);
	std::cout << "Assertion passed: Original and deserialized pointers are the same." << std::endl;

	assert(original_data->test == "Hello, World!");
	std::cout << "Assertion passed: Data content is intact after deserialization." << std::endl;
	std::cout << std::endl;


	delete original_data;
	original_data = NULL;
	deserialized_data = NULL;

	return 0;
}
