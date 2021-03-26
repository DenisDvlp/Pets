#pragma once
#include <vector>
#include <algorithm>

class State
{
    friend class StateManager;

    State *m_parent = nullptr;
    std::vector<int> m_IDs;
    bool m_entered = false;
    bool m_activated = false;
    int m_id = 0;

private:
    void enter(State *parent);
    void activate();
    void deactivate();
    void exit();
    bool isRegistered(int id);

protected:
    void registerID(int id);

public:
    virtual void onCreate() {};
    virtual void onEnter() {};
    virtual void onActivate() {};
    virtual void onDeactivate() {};
    virtual void onExit() {};
};