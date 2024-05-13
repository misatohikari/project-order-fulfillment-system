#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
#include"CustomerOrder.h"
#include"Utilities.h"

using namespace std;

namespace seneca {
	size_t CustomerOrder::m_widthField = 0;
	CustomerOrder::CustomerOrder(const string& line)
	{
		Utilities ut;
		bool more = true;
		size_t pos = 0;

		m_name = ut.extractToken(line, pos, more);
		m_product = ut.extractToken(line, pos, more);

		while (more) {
			string itemName = ut.extractToken(line, pos, more);
			try {
				Item** temp = new Item * [m_cntItem + 1];

				for (size_t i = 0; i < m_cntItem; ++i) {
					temp[i] = m_lstItem[i];
				}

				delete[] m_lstItem;
				m_lstItem = temp;

				m_lstItem[m_cntItem] = new Item(itemName);
				m_cntItem++;

				if (ut.getFieldWidth() > m_widthField) {
					m_widthField = ut.getFieldWidth();
				}
			}
			catch (const char* msg) {
				cout << "Error: " << msg << endl;
			}
		}
	}
	CustomerOrder::CustomerOrder(const CustomerOrder& RO)
	{
		throw invalid_argument("Can not allow copy constructor.");
	}
	CustomerOrder::CustomerOrder(CustomerOrder&& RO) noexcept
	{
		*this = move(RO);
	}
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& RO) noexcept
	{
		if (this != &RO) {
			for (size_t i = 0; i < m_cntItem; ++i) {
				delete m_lstItem[i];
			}
			delete[] m_lstItem;
			m_name = RO.m_name;
			m_product = RO.m_product;
			m_cntItem = RO.m_cntItem;
			//m_widthField = RO.m_widthField;
			m_lstItem = RO.m_lstItem;

			RO.m_name = "";
			RO.m_product = "";
			RO.m_cntItem = 0;
			//RO.m_widthField = 0;
			RO.m_lstItem = nullptr;
		}
		return *this;
	}
	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			delete this->m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	bool CustomerOrder::isOrderFilled() const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (!m_lstItem[i]->m_isFilled) return false;
			// m_lstItem is a pointer to a Item pointers Item** so can't use begin()
			// which need to be used for a container of vector list, array.
		}
		return true;
	}
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_cntItem; ++i) {
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled) return false;
		}
		return true;
	
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
		bool itemFound = false;
		for (size_t i = 0; i < m_cntItem && !itemFound; ++i) {
			if (station.getItemName() == m_lstItem[i]->m_itemName){
				if (!m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {

					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					station.updateQuantity();
					itemFound = true;

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
				else if (station.getQuantity() == 0) {
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
				}
			}
		}
		return;

	}

	void CustomerOrder::display(std::ostream& os) const
	{
		os << m_name << " - " << m_product << endl;

		for (size_t i = 0; i < m_cntItem; ++i) {
			os << "[" << setw(6) << right<< setfill('0') << m_lstItem[i]->m_serialNumber << "] " << setfill(' ') << left << setw(m_widthField) << m_lstItem[i]->m_itemName
				<< " - ";
			if (m_lstItem[i]->m_isFilled) os << "FILLED" << endl;
			else os << "TO BE FILLED" << endl;
		};
	}
}