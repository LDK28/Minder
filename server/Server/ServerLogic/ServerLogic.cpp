#include "ServerLogic.hpp"

int ServerLogic::getConfID(){}
void ServerLogic::setConfID(int confID){}
nlohmann::json ServerLogic::getDataFromDB(char &request){}
void ServerLogic::sendDataToDB(nlohmann::json){}

nlohmann::json ServerLogic::router(char &request, nlohmann::json){}