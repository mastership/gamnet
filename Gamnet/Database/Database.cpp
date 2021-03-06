/*
 * Database.cpp
 *
 *  Created on: Jul 24, 2013
 *      Author: kukuta
 */

#include "Database.h"
#include "../Library/ThreadPool.h"
#include "../Library/Singleton.h"
#include "../Library/Exception.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/exception/diagnostic_information.hpp>

namespace Gamnet { namespace Database {

//static ThreadPool	  threadPool_(16);

void ReadXml(const char* xml_path)
{
	boost::property_tree::ptree ptree_;
	boost::property_tree::xml_parser::read_xml(xml_path, ptree_);

	auto database_ = ptree_.get_child("server");
	for(auto elmt : database_)
	{
		if("database" != elmt.first)
		{
			continue;
		}
		int id = elmt.second.get<int>("<xmlattr>.id");
		int port = elmt.second.get<int>("<xmlattr>.port");
		const std::string host = elmt.second.get<std::string>("<xmlattr>.host");
		const std::string user = elmt.second.get<std::string>("<xmlattr>.user");
		const std::string passwd = elmt.second.get<std::string>("<xmlattr>.passwd");
		const std::string db = elmt.second.get<std::string>("<xmlattr>.db");
		if(false == Connect(id, host.c_str(), port, user.c_str(), passwd.c_str(), db.c_str()))
		{
#ifdef _WIN32
			throw Exception(GAMNET_ERROR_DB_CONNECT_FAIL, "[", __FILE__, ":", __FUNCTION__, "@", __LINE__, "] database connect fail");
#else
			throw Exception(GAMNET_ERROR_DB_CONNECT_FAIL, "[", __FILE__, ":", __func__, "@" , __LINE__, "] database connect fail");
#endif
		}
	}
}

bool Connect(int db_type, const char* host, int port, const char* id, const char* passwd, const char* db)
{
	return Singleton<DatabaseImpl>::GetInstance().Connect(db_type, host, port, id, passwd, db);
}

ResultSet Execute(int db_type, const std::string& query)
{
	return Singleton<DatabaseImpl>::GetInstance().Execute(db_type, query);
}
/*
void AExecute(int db_type, const std::string& query, std::function<void(ResultSet)> callback)
{
	threadPool_.PostTask(std::bind(&DatabaseImpl::Execute, &Singleton<DatabaseImpl>::GetInstance(), db_type, query, callback));
}
*/
}}


