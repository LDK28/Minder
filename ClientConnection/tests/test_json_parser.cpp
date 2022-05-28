#include "env_settings.hpp"

TEST(session_connection_to_json, simpletest) {
    
    json result = JsonParser::SessionConnectionDataToJson(SESSION_CONNECTION_DATA_STRUCT);

    ASSERT_EQ(result["id"], SESSION_CONNECTION_DATA_JSON["id"]);
    ASSERT_EQ(result["password"], SESSION_CONNECTION_DATA_JSON["password"]);
}

TEST(session_creation_to_json, simpletest) {
    
    json result = JsonParser::SessionCreationDataToJson(SESSION_CREATION_DATA_STRUCT );

    ASSERT_EQ(result["name"], SESSION_CREATION_DATA_JSON["name"]);
    ASSERT_EQ(result["password"], SESSION_CREATION_DATA_JSON["password"]);
}
