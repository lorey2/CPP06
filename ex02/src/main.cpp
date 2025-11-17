/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:03:16 by lorey             #+#    #+#             */
/*   Updated: 2025/07/03 15:18:50 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
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
