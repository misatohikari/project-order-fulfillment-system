#pragma once
#include <iostream>
#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

namespace seneca {
	class Utilities {
		size_t m_widthField{ 1 }; //instance variable
		static char m_delimiter; //class variable
	public:
		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter); //PUBLIC class function
		static char getDelimiter(); //PUBLIC class function
		static std::string trim(const std::string& source);
	};
}

#endif