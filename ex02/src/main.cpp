/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lorey <lorey@student.42lausanne.ch>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/06/11 21:03:16 by lorey			 #+#	#+#			 */
/*   Updated: 2025/11/17 18:55:43 by lorey            ###   LAUSANNE.ch       */
/*																			*/
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include <exception>



Base * generate(void){
	int randomNumber = std::rand() % 3;
	if (randomNumber == 0) {
		return (new A);
	} else if (randomNumber == 1) {
		return (new B);
	} else if (randomNumber == 2) {
		return (new C);
	}
	return (NULL);
}

void identify(Base* p) {
	std::cout	<< "\n\n~~~~~~~~~~~~~~~~~~\n"
				<< "Identify pointer:)\n" 
				<< "~~~~~~~~~~~~~~~~~~"
				<< std::endl;
	// so we use there the function dynamic_cast that return the adress
	// or NULL (0)
	if (dynamic_cast<A*>(p)) {
		std::cout << "pointer: A" << std::endl;
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "pointer: B" << std::endl;
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "pointer: C" << std::endl;
	} else {
		std::cout << "pointer: Unknown or NULL" << std::endl;
	}
}


//the problem with ref is that they cannot be NULL
//so we cannot return a null ref
//so we have to use try catch to catch the std::bad_cast
//if the cast could occur we print
void identify(Base& p) {
	std::cout	<< "\n\n~~~~~~~~~~~~~~~~~~\n"
				<< "Identify reference\n" 
				<< "~~~~~~~~~~~~~~~~~~"
				<< std::endl;
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "reference: A" << std::endl;
		return;
	} catch (const std::exception& e) {
	}

	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "reference: B" << std::endl;
		return;
	} catch (const std::exception& e) {
	}

	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "reference: C" << std::endl;
	} catch (const std::exception& e) {
		std::cout << "reference: Unknown type" << std::endl;
	}
}

int main(void) {
	std::srand(static_cast<unsigned int>(std::time(0)));
	Base* ptr = generate();
	Base& ref = *ptr;
	identify(ptr);
	identify(ref);
	delete(ptr);
	return(0);
}
