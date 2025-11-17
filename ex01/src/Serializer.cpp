/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:11:04 by lorey             #+#    #+#             */
/*   Updated: 2025/11/17 18:32:49 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"


//ok so as you know, a pointer is just a memory adress
//in some unlikely cases, for arithmetic
//	or send it to smth that only can store int
//	we might cast it into uniptr_t
//		this is just an unsigned int that will be big enough
//		to store a memory adress
Data* Serializer::deserialize(uintptr_t raw) {
	return (reinterpret_cast<Data*>(raw));
}

uintptr_t Serializer::serialize(Data *ptr) {
	return (reinterpret_cast<uintptr_t>(ptr));
}
