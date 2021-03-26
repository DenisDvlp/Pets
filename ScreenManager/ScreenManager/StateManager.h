#pragma once
#include "State.h"
#include <map>

class StateManager
{
    std::map<int, State*> states;
    State *m_activatedState = nullptr;

    bool has(int id)
    {
        return states.find(id) != states.end();
    }

    void activate(int id)
    {
        if (m_activatedState != nullptr && m_activatedState->m_id != id)
        {
            m_activatedState->deactivate();
        }
        State *state = get(id);
        if (state != nullptr)
        {
            state->activate();
            m_activatedState = state;
        }
        else
        {
            m_activatedState = nullptr;
        }
    }

    void closeRegistered(int id)
    {
        closeRegistered(get(id));
    }

    void closeRegistered(State *state)
    {
        if (state != nullptr)
        {
            for (auto _id : state->m_IDs)
            {
                State *s = get(_id);
                if (s != nullptr && s->m_entered)
                {
                    s->exit();
                    closeRegistered(s);
                }
            }
        }
    }

    void openRegistered(State *state, int id)
    {
        if (state != nullptr)
        {
            for (auto _id : state->m_IDs)
            {
                State *s = get(_id);
                if (s != nullptr)
                {
                    if (_id == id)
                    {
                        s->enter(state);
                    }
                    else
                    {
                        if (s->m_entered)
                        {
                            s->exit();
                            closeRegistered(s);
                        }
                    }
                }
            }
        }
    }

public:

    static StateManager& instance()
    {
        static StateManager ss;
        return ss;
    }

    State* get(int id)
    {
        return has(id) ? states[id] : nullptr;
    }

    void add(int id, State *state)
    {
        if (state != nullptr && !has(id))
        {
            state->m_id = id;
            state->onCreate();
            states[id] = state;
        }
    }

    void open(int id)
    {
        open(1, id);
    }

    void open(int count, int ids...)
    {
        int *id = &ids;
        State *state = nullptr;
        if (count > 0 && has(id[0]))
        {
            states[id[0]]->enter(nullptr);
            state = states[id[0]];
        }
        for (int i = 1; i < count && has(id[i]) && state != nullptr && state->isRegistered(id[i]); i++)
        {
            openRegistered(state, id[i]);
            state = states[id[i]];
        }
        if (state != nullptr)
        {
            activate(state->m_id);
        }
    }

    void close(int id)
    {
        bool needActivateParent = false;
        State *parent = m_activatedState;
        while (parent != nullptr && !needActivateParent)
        {
            needActivateParent = parent->m_id == id;
            parent = parent->m_parent;
        }
        State *state = get(id);
        if (state != nullptr && state->m_entered)
        {
            state->exit();
            closeRegistered(state);
        }
        if (parent != nullptr && needActivateParent)
        {
            activate(parent->m_id);
        }
    }
};