/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:03:16 by lorey             #+#    #+#             */
/*   Updated: 2025/07/01 12:22:00 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <cassert>
#include <iostream>
#include <ostream>

// Main function to test the Serializer.
int main() {
	// 1. Create a Data object on the heap.
	Data* original_data = new Data();
	original_data->test = "Hello, World!";

	std::cout << "--- Step 1: Original Data ---" << std::endl;
	std::cout << "Original pointer address: " << original_data << std::endl;
	std::cout << "Original data content: \"" << original_data->test << "\"" << std::endl;
	std::cout << std::endl;

	// 2. Serialize the pointer.
	std::cout << "--- Step 2: Serialization ---" << std::endl;
	uintptr_t serialized_ptr = Serializer::serialize(original_data);
	std::cout << "Serialized value (as integer): " << serialized_ptr << std::endl;
	std::cout << std::endl;


	// 3. Deserialize the integer back into a pointer.
	std::cout << "--- Step 3: Deserialization ---" << std::endl;
	Data* deserialized_data = Serializer::deserialize(serialized_ptr);
	std::cout << "Deserialized pointer address: " << deserialized_data << std::endl;
	std::cout << "Content from deserialized pointer: \"" << deserialized_data->test << "\"" << std::endl;
	std::cout << std::endl;


	// 4. Verification.
	std::cout << "--- Step 4: Verification ---" << std::endl;
	// Check if the pointers match.
	assert(original_data == deserialized_data);
	std::cout << "Assertion passed: Original and deserialized pointers are the same." << std::endl;

	// Check if the data is intact.
	assert(original_data->test == "Hello, World!");
	std::cout << "Assertion passed: Data content is intact after deserialization." << std::endl;
	std::cout << std::endl;

	std::cout << "✅ Test successful!" << std::endl;

	// 5. Clean up the allocated memory.
	delete original_data;
	// No need to delete deserialized_data as it points to the same memory.
	original_data = NULL;
	deserialized_data = NULL;

	return 0;
}
