/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorey <lorey@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:49:57 by lorey             #+#    #+#             */
/*   Updated: 2025/07/01 12:16:39 by lorey            ###   LAUSANNE.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string>

struct Data {
	std::string test;
};

class Serializer{
	private:
		Serializer(){};
		~Serializer(){};
		Serializer(const Serializer &serializer){ (void)serializer; };
		Serializer& operator=(const Serializer &serializer){ (void)serializer; return  (*this);};
	public:
		static uintptr_t serialize(Data* ptr);
		static Data* deserialize(uintptr_t raw);
};
