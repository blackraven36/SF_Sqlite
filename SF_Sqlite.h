#ifndef __SF__SQLITE__
#define __SF__SQLITE__

#include <vector>

#include "sqlite3.h"
#include "SF_Sqlite_Structures.h"

#include <assert.h>
#include <vector>
#include <list>

#define DEBUG_SQLITE 1

typedef bool SF_Bool;

class SF_Sqlite
{
private:
	sqlite3* connection;
	std::string databaseName;

public:

	//DOES: Saves the name of the database. Does not automatically open a connection to the database.
	SF_Sqlite( const std::string& dbName );

	//DOES: Connects to the datase. Constructor does not open a connection to the database.
	//ERRORS: ALREADY_CONNECTED 
	const SF_CODES::ERROR connect();

	//DOES: Disconnects the database. Destructor will attempt to disconnect from the database
	//ERRORS: NOT_CONNECTED
	const SF_CODES::ERROR disconnect();

	//DOES: Creates a table based on the SF_Sqlite_Column_Type_Pair data
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: CREATE TABLE Example ( ID PRIMARY KEY AUTOINCREMENT, NAME TEXT )
	const SF_CODES::ERROR createTable(const std::string& name,
									  const std::vector<SF_Sqlite_Column_Type_Pair>& columns) const;

	//DOES: Drops a particular table.
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: DROP TABLE Example
	const SF_CODES::ERROR dropTable(const std::string& name) const;

	//DOES: Executes the query without packaging the result
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: INSERT INTO Example (Name) values ('Serguei Fedorov')
	const SF_CODES::ERROR execute(const std::string& query) const;

	//DOES: Executes a query and adds the results to the list
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//INPUT QUERY: SELECT ID, NAME FROM Example
	const SF_CODES::ERROR execute(const std::string& query, std::list<SF_Sqlite_Row>& result) const;

	//DOES: Processes a query based on the parameters passed in. Executes the resulting query and adds the results to the list
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//INPUT QUERY: SELECT ID, NAME FROM Example WHERE NAME = {0}
	//OUTPUT QUERY: SELECT ID, NAME FROM Example WHERE NAME = 'Serguei Fedorov'
	const SF_CODES::ERROR execute(const std::string& query, const std::vector<SF_Sqlite_Parameter>& params, std::list<SF_Sqlite_Row>& result) const;
	
	//DOES: Executes a scalar query which returns a single int result
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//INPUT QUERY: SELECT count(*) FROM Example
	const SF_CODES::ERROR executeScalar(const std::string& query, int& result) const;

	//DOES: Executes a scalar query which returns a single int result
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//INPUT QUERY: SELECT count(*) FROM Example
	const SF_CODES::ERROR executeScalar(const std::string& query, char& result) const;

	//DOES: Executes a scalar query which returns a single int result
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//INPUT QUERY: SELECT Name FROM Example LIMIT 1
	const SF_CODES::ERROR executeScalar(const std::string& query, char*& result) const;

	//DOES: Executes a query and returns the row count
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: SELECT * FROM Example
	const SF_CODES::ERROR executeCount(const std::string& query, int& result);

	//DOES: Inserts values into table
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: INSERT INTO Example VALUES ( 0, 'Serguei Fedorov')
	const SF_CODES::ERROR insertRecord(const std::string& table, const std::vector<std::string>& values) const;

	//DOES: Inserts values into the table based on the column/data pairs
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: INSERT INTO Example (ID, Name) VALUES ( 0, 'Serguei Fedorov')
	const SF_CODES::ERROR insertRecord(const std::string& table, const std::vector<SF_Sqlite_Column_Data_Pair>& values) const;

	//DOES: Gets all results from table
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: SELECT * FROM Example
	const SF_CODES::ERROR getRecords(const std::string& table,
									 std::list<SF_Sqlite_Row>& result) const;

	//DOES: Gets all results from table for the particular columns
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: SELECT ID, Name FROM Example
	const SF_CODES::ERROR getRecords(const std::string& table,
									const std::vector<std::string>& columns,
									std::list<SF_Sqlite_Row>& result) const;

	//DOES: Gets all results from table for the particular columns and where clause
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: SELECT ID, Name FROM Example where Name = 'Serguei Fedorov'
	const SF_CODES::ERROR getRecords(const std::string& table,
									 const std::vector<std::string>& columns,
									 const std::vector<SF_Sqlite_Column_Data_Pair>& whereValues,
									 std::list<SF_Sqlite_Row>& result) const;

	//DOES: Returns a bool for whether or not a table exists
	//ERRORS: NOT_CONNECTED, QUERY_FAIL
	//OUTPUT QUERY: SELECT count(*) FROM sqlite_master WHERE type='table' AND name='Example'
	const SF_CODES::ERROR tableExists(const std::string& table, SF_Bool& result) const;

	~SF_Sqlite();
};

#endif