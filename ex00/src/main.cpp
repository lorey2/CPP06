/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 21:03:16 by lorey             #+#    #+#             */
/*   Updated: 2025/06/12 01:17:56 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "ScalarConverter.hpp"

int	main(int argc, char **av){
	if (argc != 2){
		std::cout << "you must provide one and only one arg" << std::endl;
		return (1);
	}
	ScalarConverter::convert(av[1]);
}
