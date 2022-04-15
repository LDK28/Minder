#include "ServerLogic.hpp"

int ServerLogic::getConfID(){};
void ServerLogic::setConfID(int confID){};
json ServerLogic::getDataFromDB(char &request){};
void ServerLogic::sendDataToDB(json data){};

json ServerLogic::router(char &request, json data){};