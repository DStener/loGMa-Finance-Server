#ifndef ISCE_DATABASE_H_
#define ISCE_DATABASE_H_
#include <libpq-fe.h>



namespace isce {
	class DataBase {
		PGconn* conn;
	public:
		DataBase() {
			// connect
			conn = PQconnectdb("host=localhost dbname=logma user=postgres password=2207");

			if (PQstatus(conn) != CONNECTION_OK) {
				std::cerr << "Connected error" << PQerrorMessage(conn) << std::endl;
			}
			else {
				std::cout << "Connected" << std::endl;
			}

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

		void Select(const std::string& column, const std::string& table) {
			std::string query = "SELECT " + column + " FROM " + table + ";";
			PGresult* res = PQexec(conn, query.c_str());

			if (!conn || PQresultStatus(res) != PGRES_TUPLES_OK) {
				std::cerr << "Select failed" << PQerrorMessage(conn) << std::endl;
			}
			else {
				int rows = PQntuples(res); // строки
				int cols = PQnfields(res); // столбцы

				for (int i = 0; i < rows; ++i) {
					for (int j = 0; j < cols; ++j) {
						std::cout << PQgetvalue(res, i, j) << ' ';
					}
					std::cout << std::endl;
				}

			}

			PQclear(res);

		}

		
		void Delete(const std::string& table, const std::string condition) {
			std::string query = "DELETE FROM " + table + " WHERE " + condition + ';';
			PGresult* res = PQexec(conn, query.c_str());

			if (!conn || PQresultStatus(res) != PGRES_COMMAND_OK) {
				std::cerr << "deleted failed: " << PQerrorMessage(conn) << std::endl;
			}
			else {
				std::cout << "deleted successfully" << std::endl;
			}

			PQclear(res);

		}
		
		
		void Insert(const std::string& table, const std::string& parameters, const std::string& values) {
			std::string query = "INSERT INTO " + table + " " + '(' + parameters + ')' + "VALUES" + '(' + values + ')' + ";";
			PGresult* res = PQexec(conn, query.c_str());

			if (!conn || PQresultStatus(res) != PGRES_COMMAND_OK) {
				std::cerr << "Insert failed: " << PQerrorMessage(conn) << std::endl;
			}

			PQclear(res);
		}

		
		void Update(const std::string& table, const std::string& parameters, const std::string& condition) {
			std::string query = "UPDATE " + table + " SET " + parameters + " WHERE " + condition;
			PGresult* res = PQexec(conn, query.c_str());
			if (!conn || PQresultStatus(res) != PGRES_COMMAND_OK) {
				std::cerr << "Updated failed" << PQerrorMessage(conn) << std::endl;
			}
			else {
				std::cout << "Updated successfully" << std::endl;
			}

			PQclear(res);
		}
	};
using DB = DataBase;
} // namespace isce
#endif // ISCE_DATABASE_H_