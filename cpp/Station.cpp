#include <iostream>
#include <iomanip>
#include"Station.h"
#include"Utilities.h"

using namespace std;
namespace seneca {
	size_t Station::m_widthField = 0;
	size_t Station::id_generator = 0;

	Station::Station(const std::string& record)
	{
		size_t next_pos = 0;
		bool more = true;
		Utilities util;

		m_item = util.extractToken(record, next_pos, more);
		m_serialNum = stoul(util.extractToken(record, next_pos, more)); // record is string but m_serialNum is size_t so stoul
		m_stock = stoul(util.extractToken(record, next_pos, more));

		if (util.getFieldWidth() > m_widthField) {
			m_widthField = util.getFieldWidth();
		}
		m_description = util.extractToken(record, next_pos, more);
		m_id = ++id_generator;
	}

	const std::string& Station::getItemName() const
	{
		return m_item;
	}

	size_t Station::getNextSerialNumber()
	{
		return m_serialNum++;
	}

	size_t Station::getQuantity() const
	{
		return m_stock;
	}

	void Station::updateQuantity()
	{
		if (m_stock > 0)
			m_stock--;
	}

	void Station::display(std::ostream& os, bool full) const
	{
		os << setw(3) << setfill('0') << right << m_id << " | " << left << setw(m_widthField) << setfill(' ') << m_item
			<< " | " << setw(6) << setfill('0') << right << m_serialNum << " | ";

		if (full) {
			os << setw(4) << setfill(' ') << right << m_stock << " | " << m_description << endl;
		}
		else {
			os << endl;
		}
	}

}

