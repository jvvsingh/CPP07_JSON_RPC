
// ecs36b WR client

#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "wrclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

// for sleep()
#include <unistd.h>

using namespace jsonrpc;
using namespace std;

int
main(void)
{
  // HttpClient httpclient("http://169.237.6.102:8300");
  HttpClient httpclient("http://localhost:8300");
  wrClient myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value my_json;
  Json::Value result;

  my_json["content"] = "This is a test message!";

  try {
    result = myClient.remote_print("remote print", (my_json.toStyledString()).c_str());
    cout << result.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
