#pragma once
#include <iostream>
#include <string>
#include <deque>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

namespace seneca {
	extern std::deque<CustomerOrder> g_pending;
	extern std::deque<CustomerOrder> g_completed;
	extern std::deque<CustomerOrder> g_incomplete;

	class Workstation: public Station {
		std::deque<CustomerOrder> m_orders{}; // std::deque - double ended queue
		Workstation* m_pNextStation{};

	public:
		Workstation(const std::string& arg) : Station(arg){};
		Workstation(const Workstation&) = delete;
		Workstation& operator=(const Workstation&) = delete;
		Workstation(Workstation&&) = delete;
		Workstation& operator=(Workstation&&) = delete;
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);

	};
}

#endif
