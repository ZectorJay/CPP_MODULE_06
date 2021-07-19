/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmickey <hmickey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 16:06:08 by hmickey           #+#    #+#             */
/*   Updated: 2021/07/19 22:30:09 by hmickey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.hpp"

/*
int literal values: 0, -42, 42
float literal values: 0.0f, -4.2f, 4.2f... -inff, +inff and nanf.
double literal values: 0.0, -4.2, 4.2... -inf, +inf and nan.
*/

Converter::Converter() {}

Converter::~Converter(){}

Converter::Converter( Converter const & src){ operator=(src); }

Converter	&	Converter::operator=( Converter const & src){
	if (this != &src) 
		_pseudoValue = src.getPseudoValue();
	return (*this);
}

Converter::failConvertion::failConvertion(){}

std::string		Converter::getPseudoValue() const{ return (_pseudoValue); }

char const* Converter::failConvertion::what() const throw(){
	return ("Error during convertion");
}

int		Converter::checkNumeric(char *num) const {
	int k = 1;
	int i = 0;

	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i] >= '0' && num[i] <= '9')
		i++;
	if (num[i] == '.')
	{
		k = 2;
		i++;
	}
	if (num[i] >= '0' && num[i] <= '9'){
		while (num[i] >= '0' && num[i] <= '9')
			i++;
	}
	else if (k == 2)
		k = 0;
	if (num[i] == 'f' && k == 2)
	{
		k = 3;
		i++;
	}
	if (num[i] != '\0')
		k = 0;
	return (k);
}

int		Converter::findPseudoValue(char *num, std::string valueToFind){
	if (strlen(num) != valueToFind.length())
		return (0);
	if (strnstr(num, valueToFind.c_str(), strlen(num))){
		_pseudoValue = valueToFind;
		return (1);
	}
	return (0);
}	

template <typename T>
void	Converter::displayValue(std::string type, T value, int flag) const {
	std::cout<<type<<": "<<value;
	if (!strchr(typeid(value).name(), 'i') && !strchr(typeid(value).name(), 'c') && flag == 1){
		std::cout<<".0";
	}
	if (strchr(typeid(value).name(), 'f'))
		std::cout<<"f";
	std::cout<<std::endl;
}

template <typename T>
void	Converter::convertValue(T value) const {
	int flag = 0;
	if (strstr("ic", typeid(value).name()))
		flag = 1;
	if (isprint(static_cast<int>(value)))
		displayValue("char", static_cast<char>(value), flag);
	else
		displayValue("char", "Non displayable", flag);
	displayValue("int", static_cast<int>(value), flag);
	displayValue("float", static_cast<float>(value), flag);
	displayValue("double", static_cast<double>(value), flag);
}

void	Converter::convertFunValue(std::string fun) const{
	displayValue("char", "impossible", 0);
	displayValue("int", "impossible", 0);
	displayValue("float", fun + "f", 0);
	displayValue("double", fun, 0);
}

void	Converter::checkAlpha(char *num){
	int len = strlen(num);

	if (len > 1 && len <= 5){
		if (findPseudoValue(num, "nanf") || findPseudoValue(num, "nan"))
			convertFunValue("nan");
		else if (findPseudoValue(num, "-inff") || findPseudoValue(num, "-inf"))
			convertFunValue("-inf");
		else if (findPseudoValue(num, "+inff") || findPseudoValue(num, "+inf"))
			convertFunValue("+inf");
	}
	else if (len == 1)
		convertValue(static_cast<char>(num[0]));
	if (len != 1 && _pseudoValue.length() == 0)
		throw failConvertion();
}

void	Converter::convert(char *num){
	int i = checkNumeric(num);
	
	if (i == 1)
		convertValue(atoi(num));
	else if (i == 2)
		convertValue(atof(num));
	else if (i == 3)
		convertValue(static_cast<float>(atof(num)));
	else if (i == 0)
		checkAlpha(num);
}