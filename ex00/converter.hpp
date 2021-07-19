/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:48:13 by hmickey           #+#    #+#             */
/*   Updated: 2021/07/19 22:17:33 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <iostream>
# include <stdexcept>


class Converter {

public:
	
	Converter();
	~Converter();
	Converter(Converter const & src);
	Converter & operator=( Converter const & src);

	void	convert(char *num);

	std::string	getPseudoValue() const;
	class failConvertion : public std::exception {

	public:

		failConvertion();

		char const*		what() const throw();

	};

private:

	int		checkNumeric(char *num) const ;
	void	checkAlpha(char *num);
	int		findPseudoValue(char *num, std::string valueToFind);
	template <typename T>
	void	displayValue(std::string type, T value, int flag) const;
	void	convertFunValue(std::string fun) const;
	template <typename T>
	void	convertValue(T value) const;

	std::string		_pseudoValue;


};

/*
char: Non displayable
int: 0
float: 0.0f
double: 0.0
./convert nan
*/

#endif