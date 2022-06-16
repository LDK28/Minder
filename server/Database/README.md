# Database API 

Создать экземпляр клиентов:

Сначала создайте параметры подключения, всего их 4, обязательные - user и dbname.
```c++
std::shared_ptr<PostgreSQLConnectParams> conParams =
    std::make_shared<PostgreSQLConnectParams>("p1xel", "db_minder");

std::shared_ptr<PostgreDatabaseClient> pg =
    std::make_shared<PostgreDatabaseClient>(conParams); // затем экземпляр postgre клиента

DatabaseUsersClient cl(pg); // создание user клиента
```

В случае ошибки будет поле "msg"
```json
{
  "msg": "ERROR:  duplicate key value violates unique constraint \"users_username_key\"\nDETAIL:  Key (username)=(vika) already exists.\n",
  "status": "error"
}
```

Иначе ```json["status"] = "ok";``` + какие-то поля, в зависимости от функции

## DatabaseUsersClient

### Поля
```{"username", "password", "session_id"}```

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

Формат запроса(возможно упускать каждое из полей): 
```    
json user = {
    {"id", 2}, {"username", "valera12312341"}, {"password", "1234"}};
json resp = cl.updateUser(user);
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
```cpp
bool checkUser(std::string name) const;
```

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

### validateUser
```cpp
bool validateUser(const std::string &name,const std::string &password) const;
```

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


## DatabaseSessionClient

### getSessionInfo

```cpp
json createSession(json data) const;
```

Формат запроса: 
```cpp
json req = {{"name", "sess_to"}, {"password", "1234"}};
json resp = cl.createSession(req);
```

Формат ответа:
```
{
  "id": "6",
  "status": "ok"
}
```

или ошибка

### checkSession
```cpp
bool checkSession(const std::string &name) const;
```
Формат ответа:
`true` - если сессия с таким именем существует

`false` - иначе



### getSessionInfo
```json getSessionInfo(int id) const;```

Формат запроса: 
```cpp
  int id = 1;
  json session = cl.getSessionInfo(id);
```

Формат ответа(Поле users, но user там один):
```json
{
  "sessions": [
    {
      "id": "1",
      "name": "sess1",
      "password": "123"
    }
  ],
  "status": "ok"
}
```

### checkConnectionToSession
```cpp
json checkConnectionToSession(int id, const std::string &password);
```
Формат запроса:

```cpp
json resp = cl.checkConnectionToSession(1, "123");
```

Формат ответа(Поле users, но user там один):

```json
{
  "sessions": [
    {
      "id": "1",
      "name": "sess1",
      "password": "123"
    }
  ],
  "status": "ok"
```

ВНИМАТЕЛЬНО. Возвращается массив sessions, сделано с возможностью расширения.


### updateSession
```cpp
json updateSession(json) const;
```

Формат запроса(возможно упускать каждое из полей): 
```cpp
  json session = {{"id", 2}, {"name", "good_sess"}, {"password", "1234"}};
  json resp = cl.updateSession(session);
```
Формат ответа:
```json
{
    "status" : "ok"
}
```

или ошибка

### deleteSession
```json deleteSession(int id) const;```

Формат запроса: 
```    
int sessId = 1;
json resp = cl.deleteSession(sessId);
```
Формат ответа:
```
{
    "status" : "ok"
}
```

или ошибка


## DatabaseDrawDeskClient

### createDesk

```cpp
json createDesk(const json &) const;
```

Формат запроса: 
```cpp
json req = {{"session_id", 3}};
json resp = cl.createDesk(req);
```
Формат ответа:
```json
{
  "id": "6",
  "status": "ok"
}

```

### getDeskInfo

```cpp
json getDeskInfo(int deskId) const;
```

Формат запроса: 
```cpp
int id = 1;
json desk = cl.getDeskInfo(id);
```
Формат ответа:
```json
{
  "desks": [
    {
      "id": 1,
      "session_id": 1
    }
  ],
  "status": "ok"
}

```

Внимательно! Возвращается массив `desks` из одного элемента

### updateDesk

```cpp
json updateDesk(const json &) const;
```

Формат запроса: 
```cpp
json desk = {{"id", 1}, {"session_id", 3}};
json resp = cl.updateDesk(desk);
```
Формат ответа:
```json
{
  "status": "ok"
}

```


### getBlocksInfoFromDesk

```cpp
json getBlocksInfoFromDesk(int deskId) const;
```

Формат запроса: 
```cpp
json blocksResp = cl.getBlocksInfoFromDesk(1);
```
Формат ответа:
```json
{
  "blocks": [
    {
      "color_background": "#69a832",
      "color_border": "#69a832",
      "color_text": "#69a832",
      "desk_id": 1,
      "font": "Arial",
      "id": 1,
      "parent_id": 0,
      "txt": "dima",
      "x": 20,
      "y": 20
    },
    {
      "color_background": "#69a832",
      "color_border": "#69a832",
      "color_text": "#69a832",
      "desk_id": 1,
      "font": "Arial",
      "id": 2,
      "parent_id": 0,
      "txt": "valera",
      "x": 30,
      "y": 30
    }
  ],
  "status": "ok"
}

```

Блоки находятся в массиве `blocks`



### addBlock

```cpp
json addBlock(int deskId, const json &block);
```

Формат запроса: 
```cpp
json block = {
    {"parent_id", 0},
    {"x", 20},
    {"y", 20},
    {"txt", "loool"},
    {"desk_id", 1},
    {"color_text", "#69a832"},
    {"color_background", "#69a832"},
    {"color_border", "#69a832"},
    {"font", "Arial"}
};
int deskId = 1;
json resp = cl.addBlock(deskId, block);
```
Формат ответа:
```json
{
  "id": "6",
  "status": "ok"
}
```

### updateBlock

```cpp
json updateBlock(const json &block);
```

Формат запроса: 
```cpp
json block = {
    {"id", 5},
    {"parent_id", 0},
    {"x", 20},
    {"y", 20},
    {"txt", "polinochka"},
    {"desk_id", 1},
    {"color_text", "#69a832"},
    {"color_background", "#69a832"},
    {"color_border", "#69a832"},
    {"font", "Arial"}
};

json resp = cl.updateBlock(block);
```
Формат ответа:
```json
{
  "status": "ok"
}

```

### deleteBlock

```cpp
json deleteBlock(int blockId);;
```

Формат запроса: 
```cpp
int blockId = 3;
json resp = cl.deleteBlock(blockId);
```
Формат ответа:
```json
{
  "status": "ok"
}

```