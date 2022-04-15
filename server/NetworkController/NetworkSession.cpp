class NetworkSession
{
private:
    int getSocket();
public:
    NetworkSession(/* args */);
    ~NetworkSession();

    int getRequest();
    int sendResponse();

};

NetworkSession::NetworkSession(/* args */)
{
}

NetworkSession::~NetworkSession()
{
}
