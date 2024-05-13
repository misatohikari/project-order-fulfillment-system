#include <fstream>
#include <algorithm>
#include "LineManager.h"


using namespace std;
namespace seneca {
	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
		ifstream input(file);
		if (!input.is_open()) {
			cerr << "Unable to read or open file: " << file;
			return;
		}

		vector<string> firstStations;
		vector<string> lastStations;

		string line;
		while (getline(input, line)) {
			string currentStation, nextStation;

			size_t deliminator = line.find('|');
			if (deliminator != string::npos) {

				currentStation = line.substr(0, deliminator);
				nextStation = line.substr(deliminator + 1);
			}
			else {
				//deal with the case where no delimiter and set nextStation as empty string!!
				currentStation = line;
				nextStation = "";
			}
			firstStations.push_back(currentStation);
			lastStations.push_back(nextStation);

				//find current station
				auto currStationIt = find_if(stations.begin(), stations.end(), [&](Workstation* station) {
					return station->getItemName() == currentStation;
					});
				// push current station to m_activeLine
				if (currStationIt != stations.end()) {
					m_activeLine.push_back(*currStationIt);
					//find next station
					if (nextStation.length() > 0) {
						auto nextStationIt = find_if(stations.begin(), stations.end(), [&](Workstation* station) {
							return station->getItemName() == nextStation;
							});
						//set the next station of currentStation.
						(*currStationIt)->setNextStation(*nextStationIt);
					}
					else {
						(*currStationIt)->setNextStation(nullptr);
						// include this case unless Bookcase -> End of line never printed.
					}
				}		
		}

		// check for the first station
		auto firstStationIt = find_if(firstStations.begin(), firstStations.end(), [&](const string& firstStation) {
			return count(lastStations.begin(), lastStations.end(), firstStation) == 0;
			});

		// if first station is found, then set to m_firstStation
		if (firstStationIt != firstStations.end()) {
			const string& checkForFirstStation = *firstStationIt;
			auto firstStation = find_if(stations.begin(), stations.end(), [&](Workstation* station) {
				return station->getItemName() == checkForFirstStation;
				});
			if (firstStation != stations.end()) {
				m_firstStation = *firstStation;
			}
		}

		m_cntCustomerOrder = g_pending.size();
	}
	
	void LineManager::reorderStations()
	{
		vector<Workstation*> reorderLine{};
		Workstation* currentStation = m_firstStation;

		while (currentStation != nullptr) {
			/*reorderLine.insert(reorderLine.begin(), currentStation);*/
			reorderLine.push_back(currentStation);
			currentStation = currentStation->getNextStation();
		}

		m_activeLine = reorderLine;
	}
	bool LineManager::run(ostream& os)
	{
		static size_t cnt = 1;

		os << "Line Manager Iteration: " << cnt++ << endl;
		if (!g_pending.empty()) {
			*m_firstStation += move(g_pending.front());
			g_pending.pop_front();
		}

		//bool allOrdersProcessed = true;
		for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&os](Workstation* ws) {
			ws->fill(os);
			});


		for_each(this->m_activeLine.begin(), this->m_activeLine.end(), [&](Workstation* ws) {
			ws->attemptToMoveOrder();
		});
		// check if all the customer ordered processed.
		return m_cntCustomerOrder == (g_completed.size() + g_incomplete.size());
	}

	void LineManager::display(std::ostream& os) const
	{
		for (auto station : m_activeLine) {
			station->display(os);
		}
	}
}

