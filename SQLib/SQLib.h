#pragma once

#include <string>
#include <memory>
#include <vector>
#include <variant>

namespace sql {

	using value_t = std::variant<
		std::int64_t, 
		double, 
		std::string, 
		std::nullptr_t>;
	using name_value_t = std::pair<std::string, value_t>;
	using row_t = std::vector<name_value_t>;
	using table_t = std::vector<row_t>;

	class SQLib 
	{
	public:
		// Execute an SQL string to the database.
		//	return bool		- true is ok
		//					- false is error
		virtual bool ExecuteString(const std::string& string) = 0;
		// Get an error from the previously called ExecuteString (in case there
		// is a return false).
		virtual const std::string& GetError() const = 0;
		// Get the return values from the last execute string.
		virtual const table_t& GetReturnValues() const = 0;
	};

	std::shared_ptr<SQLib> CreateSQLiteDB(const std::string& file);

} // End namespace sql.
