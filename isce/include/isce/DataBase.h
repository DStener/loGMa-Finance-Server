#pragma once 

#include "isce/sqlAttrib.h"
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
#include <iostream>

#include <boost/algorithm/string/case_conv.hpp>
#include <libpq-fe.h>

#include <isce/__DTO.h> 

#define DB_CHECK_ERROR(condition) 																		 \
	if(condition) {																											 \
		std::string error = std::format("{}, func {}(), line {}: {}", 		 \
																		__FILE__, __FUNCTION__, __LINE__,  \
																		PQerrorMessage(conn));      			 \
		throw std::runtime_error(error);																	 \
	}


namespace isce {
class DataBase {
 public:
	DataBase() {
		// Connect to empty/default database
		conn = PQconnectdb(DataBase::get_connect_info(true).c_str());
		DB_CHECK_ERROR(PQstatus(conn) != CONNECTION_OK)
		
		DataBase::create_db_if_not_exist(DataBase::get_name());
		
		// Close connection to empty/default database
		PQfinish(conn);

		// Connect to real database
		conn = PQconnectdb(DataBase::get_connect_info().c_str());
		DB_CHECK_ERROR(PQstatus(conn) != CONNECTION_OK)
	}
	~DataBase() {
		if (conn) {
			PQfinish(conn);
			conn = nullptr;
			std::cout << "Connection closed" << std::endl;
		}
	}

	static std::shared_ptr<DataBase> get() {
		static std::once_flag flag;
		static std::shared_ptr<DataBase> instance;
		std::call_once(flag, [&]() { instance.reset(new DataBase()); });
		return instance;
	}

	template <typename T>
	void Create() {
		std::string query = _DTO::sqlCreateTable<T>();
		PGresult* res = PQexec(conn, query.c_str());

		DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK);

		PQclear(res);
	}

	template <typename T>
	ResponseVec<T> Select(const std::string& condition) {
		std::string query = std::format("SELECT * FROM {0} {2} {1};",
																		_DTO::getName<T>(), condition,
																		((condition.size() > 0)? "WHERE" : ""));

		PGresult* res = PQexec(conn, query.c_str());
		DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

		auto vec = _DTO::fromSQL<T>(res);

		PQclear(res);
		return vec;
	}

	
	void Delete(const std::string& table, const std::string condition) {
		std::string query = "DELETE FROM " + table + " WHERE " + condition + ';';
		PGresult* res = PQexec(conn, query.c_str());

		if (!conn && PQresultStatus(res) != PGRES_COMMAND_OK) {
			std::cerr << "deleted failed: " << PQerrorMessage(conn) << std::endl;
		}
		else {
			std::cout << "deleted successfully" << std::endl;
		}

		PQclear(res);

	}

	template <typename T>
	SQL_SERIAL Insert(T& t) {
		std::string query = _DTO::sqlInsert(t);

		std::cout << query << std::endl;

		PGresult* res = PQexec(conn, query.c_str());
		DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

		SQL_SERIAL id = std::stoi(PQgetvalue(res, 0, 0));

		PQclear(res);
		return id;
	}

	
	void Update(const std::string& table, const std::string& parameters, const std::string& condition) {
		std::string query = "UPDATE " + table + " SET " + parameters + " WHERE " + condition;
		PGresult* res = PQexec(conn, query.c_str());
		if (!conn && PQresultStatus(res) != PGRES_COMMAND_OK) {
			std::cerr << "Updated failed" << PQerrorMessage(conn) << std::endl;
		}
		else {
			std::cout << "Updated successfully" << std::endl;
		}

		PQclear(res);
	}
 private:
	PGconn* conn;

	void create_db_if_not_exist(const std::string& database){
		const std::string check_query = std::format("SELECT * FROM pg_database WHERE datname = '{}';", database);
		const std::string create_query = std::format("CREATE DATABASE {};", database);

		// Check that database is exist
		PGresult* res = PQexec(conn, check_query.c_str());
		DB_CHECK_ERROR(PQresultStatus(res) != PGRES_TUPLES_OK)

		// If database is exist
		if(PQntuples(res) != 0) { return; };

		// Create database if not exist
		res = PQexec(conn, create_query.c_str());
		DB_CHECK_ERROR(PQresultStatus(res) != PGRES_COMMAND_OK)
	}



	static std::string get_name() {
		/*auto conf = config()->getDBConfig();
		if(!conf.has_value()) { return {}; }

		const auto it = conf->find("dbname");
		if(it == conf->end()) { return {}; }

		if(it->value() != "__auto__") { return it->value().as_string().c_str(); }*/

		return "";
		//return std::format("db_{}", boost::to_lower_copy(isce::__service_name__));
	}

	static std::string get_connect_info(bool is_empty_connect = false) {
		//auto conf = config()->getDBConfig();
		//if(!conf.has_value()) { return {}; }

		//std::vector<std::string> conninfo;
		//for(const auto& row : *conf) {
		//	std::string_view key = row.key().data();
		//	std::string_view value = row.value().as_string().c_str();

		//	if(is_empty_connect && key == "dbname") { 
		//		value = "template1";
		//	} else if (key == "dbname" && value == "__auto__") {
		//		//value = std::format("db_{}", boost::to_lower_copy(isce::__service_name__));
		//		value = "";
		//	}
		//	
		//	conninfo.push_back(std::format("{}={}", key, value));
		//}

		//return boost::join(conninfo, " ");
		return "";
	}
};
using DB = DataBase;
} // namespace isce