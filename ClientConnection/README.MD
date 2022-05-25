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

