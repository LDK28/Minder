#include "HttpClient.hpp"

int main(void)
{
    HttpClient httpClient("127.0.0.1", 1025);

    std::string menu = "\n \
    МЕНЮ: \n \
    1. Создать сессию\n \
    2. Подключиться к сессии\n \
    3. Обновить настройки подключения\n \
    4. Получить всех юзеров сессии \n \
    5. Добавление блока в сессию\n \
    6. Удаление блока\n \
    7. Получить все блоки доски\n \
    8. Выйти из сессии\n \
    0. Выход\n\n \
    Выберети пункт: ";

    std::string loginMenu = "\n \
    МЕНЮ: \n \
    1. Вход\n \
    2. Регистрация\n \
    0. Выход\n\n \
    Выберети пункт: ";

    size_t userId = 0;
    size_t desk_id = 0;

    while (true)
    {
        if (userId > 0)
        {
            std::string command;

            std::cout << menu;
            std::cin >> command;
            if (command == "1")
            {
                HttpClientData::SessionCreationData scData;
                std::cout << "Введите имя сессии:\n";
                std::cin >> scData.name;
                std::cout << "Введите пароль дdeleteBlockля сессии:\n";
                std::cin >> scData.password;
                desk_id = httpClient.createSession(scData, userId);
                std::cout << "ID вашей сессии: " << desk_id << "\n";
            }
            else if (command == "2")
            {
                HttpClientData::SessionConnectionData scData;
                std::cout << "Введите ID сессии:\n";
                std::cin >> scData.id;
                std::cout << "Введите пароль для сессии:\n";
                std::cin >> scData.password;
                std::string name = httpClient.checkConnectionToSession(scData, userId);
                if (name.empty())
                    std::cout << "Не удалось подключиться к сессии\n";
                else
                {
                    std::cout << "Имя вашей сессии: " << name << "\n";
                    desk_id = scData.id;
                }
            }
            else if (command == "3")
            {
                HttpClientData::SettingsData settings;
                std::cout << "Введите ip:\n";
                std::cin >> settings.ip;
                std::cout << "Введите порт:\n";
                std::cin >> settings.port;
                if (httpClient.updateSettings(settings) == HttpClientData::returnCode::SUCCESS)
                    std::cout << "Настройки успешно изменены\n";
                else
                    std::cout << "Неверно введены данные\n";
            }
            else if (command == "4")
            {
                if (desk_id > 0)
                {
                    HttpClientData::UsersInSessionData users = httpClient.getUsersInSession(desk_id);
                    std::cout << "Пользователи в сессии:\n";
                    for (auto user : users.users)
                        std::cout << user.nickname << "\n";
                }
                else
                    std::cout << "Вы не подключены к сессии\n";
            }
            else if (command == "5")
            {
                if (desk_id > 0)
                {
                    HttpClientData::Block block;
                    std::cout << "Введите текст блока:\n";
                    std::cin >> block.text;

                    block.posY = 20;
                    block.posX = 20;
                    block.parentId = 0;
                    block.fontColor.name = "#69a832";
                    block.bgColor.name = "#69a832";
                    block.borderColor.name = "#69a832";
                    block.font.name = "Arial";

                    std::cout << "ID созданного блока: " << httpClient.addBlock(block, desk_id) << "\n";
                }
                else
                    std::cout << "Вы не подключены к сессии\n";
            }
            else if (command == "6")
            {
                if (desk_id > 0)
                {
                    size_t blockId;
                    std::cout << "Введите ID блока для удаления:\n";
                    std::cin >> blockId;
                    httpClient.deleteBlock(blockId);
                }
                else
                    std::cout << "Вы не подключены к сессии\n";
            }
            else if (command == "7")
            {
                if (desk_id > 0)
                {
                    HttpClientData::MindMapData map = httpClient.getCurrentStateDesk(desk_id);
                    std::cout << "Блоки сессии:\n";
                    for (auto block : map.blocks)
                        std::cout << "block ID: " << block.id << " Text: " << block.text << "\n";
                }
                else
                    std::cout << "Вы не подключены к сессии\n";
            }
            else if (command == "8")
            {
                if (desk_id > 0)
                {
                    httpClient.disconnectSession(userId, desk_id);
                    desk_id = 0;
                }
                else
                    std::cout << "Вы не подключены к сессии\n";
            }
            else if (command == "0")
                break;
        }
        else
        {
            std::string command;

            std::cout << loginMenu;
            std::cin >> command;

            if (command == "1")
            {
                HttpClientData::UserData user;
                std::cout << "Введите никнейм:\n";
                std::cin >> user.nickname;
                std::cout << "Введите пароль:\n";
                std::cin >> user.password;
                userId = httpClient.loginUser(user);
                if (userId == 0)
                    std::cout << "Неверные данные! Повторите попытку.\n";
                else
                    std::cout << "Авторизация прошла успешно!\nВаш ID: " << userId << "\n";
            }
            else if (command == "2")
            {
                HttpClientData::UserData user;
                std::cout << "Введите никнейм:\n";
                std::cin >> user.nickname;
                std::cout << "Введите пароль:\n";
                std::cin >> user.password;
                userId = httpClient.registerUser(user);
                if (userId == 0)
                    std::cout << "Неверные данные! Повторите попытку.\n";
                else
                    std::cout << "Рагистрация прошла успешно!\nВаш ID: " << userId << "\n";
            }
            else if (command == "0")
                break;
        }
    }

    return 0;
}