#include "Workstation.h"

using namespace std;
namespace seneca {
	std::deque<CustomerOrder> g_pending{};
	std::deque<CustomerOrder> g_completed{};
	std::deque<CustomerOrder> g_incomplete{};


	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty()) {
			m_orders.front().fillItem(*this, os); // .front() get the front value stored without deleting. 
		}
	}
	bool Workstation::attemptToMoveOrder() {
		if (!m_orders.empty()) {
			if (getQuantity() == 0 || m_orders.front().isItemFilled(getItemName())) {
	
				if (m_pNextStation != nullptr) {
					*m_pNextStation += move(m_orders.front());
					m_orders.pop_front();
					return true;
				}
				else {
					// no next station
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(move(m_orders.front())); // move to completed queue
					else
						g_incomplete.push_back(move(m_orders.front())); // move to incomplete queue
					m_orders.pop_front();
					return true;
				}
			}
			else {
				return false;
			}
		}
		return false; 
	}
	
	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}
	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{
		os << getItemName() << " --> ";
		if (m_pNextStation) os << m_pNextStation->getItemName();
		else os << "End of Line";
		os << endl;
		
	}
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}
}