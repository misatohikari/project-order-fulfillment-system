#pragma once
#include <iostream>
#include <string>
#ifndef SENECA_STATION_H
#define SENECA_STATION_H

namespace seneca {
	class Station {
		int m_id;
		std::string m_item;
		std::string m_description;
		size_t m_serialNum;
		size_t m_stock;

		static size_t m_widthField;
		static size_t id_generator;

	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};

}

#endif
