/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 10:25:49 by hmickey           #+#    #+#             */
/*   Updated: 2021/07/19 18:39:09 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "converter.hpp"

int main(int argc, char **argv){
	if (argc != 2){
		std::cout<<"Wrong args number"<<std::endl;
		return (0);
	}
	try{
		Converter convert;
		convert.convert(argv[1]);
	} catch (std::exception & e) {
		std::cout<<e.what()<<std::endl;
	}
	return (0);
}