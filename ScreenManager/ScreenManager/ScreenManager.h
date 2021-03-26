#pragma once
#include "Screen.h"
#include <list>
#include <map>
using std::list;
using std::map;

class ScreenManager
{
    struct Message
    {
        enum MessageType
        {
            MSG_OPEN,
            MSG_CLOSE,
        };
        MessageType type = MSG_OPEN;
        ScreenID id = static_cast<ScreenID> (-1);
        ScreenID parentId = static_cast<ScreenID> (-1);
        Message(MessageType type, ScreenID id, ScreenID parentId) :
            type(type),
            id(id),
            parentId(parentId)
        {}
    };

    list<Message> messages;
    map<ScreenID, Screen*> screens;
    Screen *lastOpened = nullptr;

    void request(Message message);
    void handleMessages();
    void openRequest(ScreenID id, ScreenID parentId);
    void closeRequest(ScreenID id);

    bool has(ScreenID id);
    Screen* get(ScreenID id);

    ScreenManager() {}

public:    
    
    static ScreenManager& instance();

    void add(ScreenID id, Screen * screen);
    void open(ScreenID id);
    void open(int count, ScreenID ids...);
    void close(ScreenID id);


    void print();


};