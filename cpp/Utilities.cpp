#include "Utilities.h"

using namespace std;
namespace seneca {

	char Utilities::m_delimiter = getDelimiter();

	std::string Utilities::trim(const std::string& source)
	{
		size_t first = source.find_first_not_of(' ');
		if (std::string::npos == first)
			return source;
		size_t last = source.find_last_not_of(' ');
		return source.substr(first, (last - first + 1));
	}

	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}
	size_t Utilities::getFieldWidth() const
	{
		return m_widthField;
	}
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string token;
		// Find the position of the next delimiter
		size_t delimPos = str.find(m_delimiter, next_pos);

		if (delimPos != string::npos) { // delimiter is found case
			token = str.substr(next_pos, delimPos - next_pos); //extract token
			next_pos = delimPos + 1;
			more = true;
		}
		else {
			// delimiter is not found - extract the last token
			token = str.substr(next_pos);
			more = false;
		}

		token = trim(token);
		if (token.length() > m_widthField) {
			m_widthField = token.length();
		}
		if (token.empty()) {
			more = false;
			throw "ERROR: Token is empty!";
		}
		return token;

	}
	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}
	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}