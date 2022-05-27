# HttClient API 

Создание экземпляра класса:

Сначала создайте параметры подключения к серверу - **ip (std::string)** и **port (int)**.
```c++
std::string ip = "192.168.77.50";
int port = 80;

// 1
std::shared_ptr<HttpClient> httpClient = std::make_shared<HttpClient>(ip, port);
// 2
HttpClient httpClient(ip, port);
```

### Методы

#### updateSettings

Обновление настроек подключения к серверу(ip, port).

```c++
// Прототип
HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &settings);

// Успешный вызов
HttpClientData::returnCode rc;
HttpClientData::SettingsData settings = {"192.168.23.23", 80}; // {ip, port}
rc = httpClient.updateSettings(); // rc => HttpClientData::returnCode::SUCCESS

// Неуспешный вызов
HttpClientData::SettingsData settings = {"", 80}; // {ip, port} // empty string ip
rc = httpClient.updateSettings(ip, port); // rc => HttpClientData::returnCode::FAILED
```

#### checkConnectionToSession

Проверка сессии и верификация пароля, если есть и пароль совпадает: name сесcии, если нет - empty string

```c++
// Прототип
std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &scData);

// Вызов
std::string name;
HttpClientData::SessionConnectionData scData = {182, "Qwerty"}; // {id, password}
name = httpClient.checkConnectionToSession(scData); // name => "Your session name"

```

#### createSession

Создание сессии: id сесcии

```c++
// Прототип
size_t createSession(const HttpClientData::SessionCreationData &scData);

// Вызов
size_t id;
HttpClientData::SessionCreationData scData = {"name", "Qwerty"}; // {name, password}
id = httpClient.createSession(scData); // id => 182

```

#### getUsers*

Получение активных пользователей сессии

```c++
// Прототип
std::string getUsers(const HttpClientData::SessionConnectionData &scData);

// Вызов
std::string names;
HttpClientData::SessionConnectionData scData = {182, "Qwerty"}; // {id, password}
id = httpClient.scData(scData); // names => {"name1", "name2"}

```

#### getUsers

Добавление блока в сессию

```c++
// Прототип
void addBlock(const HttpClientData::Block &block, const HttpClientData::SessionConnectionData &scData);

```

​    // удалить блок по id

​    void deleteBlock(const size_t BlockId, const HttpClientData::SessionConnectionData &) override;



​    // получить все блоки по id сессии

#### changeBlock

```c++
// Прототип
void changeBlock(const HttpClientData::Block &block, const HttpClientData::SessionConnectionData &scData);

```

#### 

#### deleteBlock

Удаление блока из сессии по id

```c++
// Прототип
void deleteBlock(const size_t &blockId, const HttpClientData::SessionConnectionData &scData);

```

#### getCurrentStateDesk

Получить все блоки по id сессии

```c++
// Прототип
HttpClientData::MindMapData getCurrentStateDesk(const HttpClientData::SessionConnectionData &scData);

```

#### 
