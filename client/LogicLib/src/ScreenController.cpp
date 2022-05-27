#include "ScreenController.h"

void ScreenController::validationLoginDataSuccess() {
    return;
}

void ScreenController::validationRegisterDataSuccess() {
    return;
}

void ScreenController::validationLoginDataFailed(const QString &) {
    return;
}

void ScreenController::validationRegisterDataFailed(const QString &) {
    return;
}

void ScreenController::savingSettingsSuccess() {
    return;
}

void ScreenController::savingSettingsFailed(const QString &) {
    return;
}

void ScreenController::connectionToSessionSuccess(const ViewDataStructures::SessionData &) {
    return;
}

void ScreenController::connectionToSessionFailed(const QString &) {
    return;
}

void ScreenController::creationNewSessionSuccess(const ViewDataStructures::SessionData &) {
    return;
}

void ScreenController::creationNewSessionFailed(const QString &) {
    return;
}

void ScreenController::receiveMindMapDataInSession(const ViewDataStructures::MindMapData &) {
    return;
}

void ScreenController::receiveNewBlockId(const long) {
    return;
}

void ScreenController::receiveBlock(const ViewDataStructures::Block&) {
    return;
}

void ScreenController::receiveDeletedBlockId(size_t) {
    return;
}

void ScreenController::receiveUsersListInSession(const ViewDataStructures::UsersInSessionData &) {
    return;
}

