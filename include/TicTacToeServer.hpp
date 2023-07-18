#include <iostream>
#include <net/NetServer.hpp>

enum class TicTacToeMessage : uint32_t
{
    ServerPing,
    MessageAll,
    ServerMessage,
    LoginIn,
    LoginAccept,
    LoginDenied,
    Place
};

class TicTacToeServer : public net::ServerInterface<TicTacToeMessage>
{
public:
    TicTacToeServer(uint16_t nPort) : net::ServerInterface<TicTacToeMessage>(nPort)
    {

    }

protected:
    virtual bool onClientConnect(std::shared_ptr<net::Connection<TicTacToeMessage>> client)
    {
        net::Message<TicTacToeMessage> msg;
        msg.header.id = TicTacToeMessage::LoginAccept;
        client->send(msg);
        return true;
    }

    virtual void onClientDisconnect(std::shared_ptr<net::Connection<TicTacToeMessage>> client)
    {
        std::cout << "Removing client [" << client->getID() << "]\n";
    }

    virtual void onMessage(std::shared_ptr<net::Connection<TicTacToeMessage>> client, net::Message<TicTacToeMessage>& msg)
    {
        std::cout << "Recieve Message with id=" << (int)msg.header.id << " from [" << client->getID() << "]\n";
        switch (msg.header.id)
        {
        case TicTacToeMessage::ServerPing:
            {
                std::cout << "[" << client->getID() << "]: Server Ping\n";
                client->send(msg);
            }
            break;
        case TicTacToeMessage::MessageAll:
            {
                std::cout << "[" << client->getID() << "]: Message All\n";

                net::Message<TicTacToeMessage> msg;
                msg.header.id = TicTacToeMessage::ServerMessage;
                msg << client->getID();
                messageAllClients(msg, client);

            }
            break;
        case TicTacToeMessage::LoginIn:
            {
                std::cout << "[" << client->getID() << "]: Login In\n";

                std::string login, password;
                msg >> password >> login;

                std::cout << "Check credentials... " << std::endl;
                std::cout << "Login: " << login << std::endl;
                std::cout << "Password: " << password << std::endl;

                // net::Message<TicTacToeMessage> msg;
                // msg.header.id = TicTacToeMessage::ServerMessage;
                // msg << "Login In sucessfull";
                // client->send(msg);
            }
            break;
        }
    }
};
