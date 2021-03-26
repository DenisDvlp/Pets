#pragma once
#include "State.h"
#include "StateManager.h"


class StateRoot : public State
{
    virtual void onCreate()
    {
        registerID(1);
        registerID(2);
    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};

class State1 : public State
{
    virtual void onCreate()
    {
        registerID(3);
        registerID(4);
    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};

class State2 : public State
{
    virtual void onCreate()
    {
        registerID(5);
        registerID(6);
    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};

class State3 : public State
{
    virtual void onCreate()
    {
        registerID(7);
        registerID(8);
    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};

class State4 : public State
{
    virtual void onCreate()
    {
        registerID(4);
        registerID(7);
        registerID(8);
    }
    virtual void onEnter()
    {
        StateManager::instance().open(4);

    }
    virtual void onExit()
    {
    }
};

class State5 : public State
{
    virtual void onCreate()
    {
        registerID(7);
        registerID(8);
    }
    virtual void onEnter()
    {
    }
    virtual void onExit()
    {

    }
};

class State6 : public State
{
    virtual void onCreate()
    {
        registerID(7);
        registerID(8);
    }
    virtual void onEnter()
    {
    }
    virtual void onExit()
    {

    }
};

class State7 : public State
{
    virtual void onCreate()
    {

    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};

class State8 : public State
{
    virtual void onCreate()
    {

    }
    virtual void onEnter()
    {

    }
    virtual void onExit()
    {

    }
};