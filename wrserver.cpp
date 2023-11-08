
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "wrserver.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include <stdio.h>

// popular ones
#include <strings.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception> 
#include <time.h>

using namespace jsonrpc;
using namespace std;

class mywrServer : public wrServer
{
public:
  mywrServer(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);
  virtual Json::Value remote_print(const std::string& action, const std::string& your_json);
};

mywrServer::mywrServer(AbstractServerConnector &connector, serverVersion_t type)
  : wrServer(connector, type)
{
  std::cout << "mywrServer Object created" << std::endl;
}

// member functions

Json::Value
mywrServer::remote_print
(const std::string& action, const std::string& your_json)
{
  Json::Value result;
  std::cout << action << " " << your_json;
  std::string strJson;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  strJson += "{\"status\" : \"successful\"}";

  Json::CharReaderBuilder builder;
  Json::CharReader* reader = builder.newCharReader();
  std::string errors;
  bool parsingSuccessful = reader->parse
    (strJson.c_str(), strJson.c_str() + strJson.size(), &result, &errors);
  delete reader;

  if (!parsingSuccessful) {
    std::cout << "Failed to parse the JSON, errors:" << std::endl;
    std::cout << errors << std::endl;
  }

  return result;
}

int
main
(void)
{
  HttpServer httpserver(8300);
  mywrServer s(httpserver,
	       JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
