#pragma once

//typedef int ScreenID;

enum ScreenID {
	SCR_ROOT,
	SCR_RADIO,
	SCR_MEDIA,
	SCR_PHONE,
	SCR_MEDIA_ERROR,
	SCR_MEDIA_STANDART,
	SCR_RADIO_ERROR,
	SCR_RADIO_STANDART,
	SCR_PHONE_ERROR,
	SCR_PHONE_STANDART,
	SCR_AES,
	SCR_AT,
};

class Screen
{
    friend class ScreenManager;

    ScreenID m_id = static_cast<ScreenID>(0);
    Screen *m_child = nullptr;
    Screen *m_parent = nullptr;
    bool m_isOpen = false;
    bool m_isActive = false;

private:

    void open(Screen *parent);
    void activate();
    void deactivate();
    void close();
    void action();

protected:

    ScreenID id();
    Screen* parent();
    Screen* child();
    bool isActive();

    virtual void onOpen() {};
    virtual void onActivate() {};
    virtual void onDeactivate() {};
    virtual void onClose() {};
    virtual void onAction() {};
};

