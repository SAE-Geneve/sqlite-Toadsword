#include "SQLiteImpl.h"
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

namespace sql {

	static int Callback(void* ptr, int ac, char** av, char** column_name) 
	{
		SQLiteImpl* myDb = reinterpret_cast<SQLiteImpl*>(ptr);

		row_t newRow;
		int i;
        for( i = 0; i < ac; i++) {
			newRow.push_back(std::pair<std::string, value_t>(column_name[i], av[i]));
        }
		myDb->table_.push_back(newRow);
		return 0;
	}

	SQLiteImpl::SQLiteImpl(const std::string& file)
	{
		table_ = {};
		int res = sqlite3_open(file.c_str(), &db_);
        if(res) {
			fprintf(stderr, "Can't open database : %s\n", sqlite3_errmsg(db_));
			sqlite3_close(db_);
			throw std::runtime_error("");
        }
	}

	SQLiteImpl::~SQLiteImpl()
	{
		sqlite3_close(db_);
	}

	bool SQLiteImpl::ExecuteString(const std::string& cmd)
	{
		table_ = {};
		char* errorMsg;
        int res = sqlite3_exec(db_, cmd.c_str(), Callback, this, &errorMsg);
        if(res != SQLITE_OK) {
			fprintf(stderr, "SQL error : %s\n", errorMsg);
			error_ = errorMsg;
			return false;
        }
		
		return true;
	}

	sql::value_t SQLiteImpl::GetValue(const std::string& str) const
	{
#pragma message ("You have to complete this code!")
		return str;
	}

} // End namespace sql.
