# Database API 

Создать экземпляр клиентов TODO

В случае ошибки будет поле "msg"
```
{
  "msg": "ERROR:  duplicate key value violates unique constraint \"users_username_key\"\nDETAIL:  Key (username)=(vika) already exists.\n",
  "status": "error"
}
```

Иначе ```json["status"] = "ok";``` + какие-то поля, в зависимости от функции

## DatabaseUsersClient

### createUser
```json createUser(json) const;```

Формат запроса: 
```json req = {{"username", "aaaaaaaaaaaaabcdc"}, {"password", "12341234"}};```

Формат ответа:
```
{
  "id": "6",
  "status": "ok"
}
```

### getUserInfo
```json getUserInfo(int id) const;```

Формат запроса: 
```    
int id = 1;
json usr = cl.getUserInfo(id);
```

Формат ответа(Поле users, но user там один):
```
{
    "status" : "ok",
    "users" : [ {
        "id" : 1,
        "password" : "dima_pass",
        "session_id" : "1",
        "username" : "dima"
    } ]
}
```

### getAllUsersInfo
```json getAllUsersInfo() const;```

Формат запроса: 
```    
json usrs = cl.getAllUsersInfo();
```

Формат ответа(Поле users):
```
{
  "status": "ok",
  "users": [
    {
      "id": 1,
      "password": "dima_pass",
      "session_id": "1",
      "username": "dima"
    },
    {
      "id": 2,
      "password": "valera_pass",
      "session_id": "1",
      "username": "valera"
    },
    {
      "id": 3,
      "password": "vika_pass",
      "session_id": "2",
      "username": "vika"
    }
  ]
}
```

### getAllUsersInfo

Формат запроса: 
```    
int sessionId = 1;
json usrs = cl.getUsersInSession(sessionId);
```

Ответ идентичен вышенаписанному примеру `getAllUsersInfo`

### addUsersInSession
```json addUsersInSession(std::vector<int> userId, int sessionId) const;```

Формат запроса: 
```    
std::vector<int> usersIds = {1, 2, 3};
int sessionId = 3;
json usrs = cl.addUsersInSession(usersIds, sessionId);
```

Формат ответа:
```
{
    "status" : "ok"
}
```

### updateUser
```json DatabaseUsersClient::updateUser(json sessData) const```

Формат запроса: 
```    
std::vector<int> usersIds = {1, 2, 3};
int sessionId = 3;
json usrs = cl.addUsersInSession(usersIds, sessionId);
```
Формат ответа:
```
{
    "status" : "ok"
}
```

или ошибка

### deleteUsersById
```json deleteUsersById(int id) const;```

Формат запроса: 
```    
int userId = 2;
json resp = cl.deleteUsersById(userId);
```
Формат ответа:
```
{
    "status" : "ok"
}
```

или ошибка

### checkUser
```bool checkUser(std::string name) const;```

Формат запроса: 
```    
json resp = cl.checkUser("username");
```
Формат ответа:
```
{
    "status" : "ok"
}
```

или ошибка

### getUserByName
```json getUserByName(std::string name) const;```

Формат запроса: 
```    
std::string name = "dima";
json usr = cl.getUserByName(name);
```

Формат ответа(Поле users, но user там один):
```
{
    "status" : "ok",
    "users" : [ {
        "id" : 1,
        "password" : "dima_pass",
        "session_id" : "1",
        "username" : "dima"
    } ]
}
```