//Drawable.h
#pragma once
#include "Linkable.h"
#include "DDrawable.h"
#include "DShapeable.h"
#include "Signal.h"
#include "Key.h"

class Drawable
    : Linkable
    , public DDrawable
    , public DShapeable
{
public:
    explicit Drawable(Drawable* = nullptr);
    virtual ~Drawable();
    Drawable* parent() const;
    void setParent(Drawable*);
    void bringToFront();
    void sendToBack();
    bool mouseUp(Key);
    bool mouseDown(Key);
    bool mouseMove(DPoint);
    Signal<Sender, Key> onMouseUp;
    Signal<Sender, Key> onMouseDown;
    Signal<Sender, DPoint> onMouseMove;
    Signal<Sender> onMouseEnter;
    Signal<Sender> onMouseLeave;
    Signal<Sender, Key> onClick;
protected:
    DRect m_rect;
private:
    void reshape(DRect& rect) override;
    void draw() const override;
private:
    DVector<Drawable*> m_children;
    Drawable* m_parent = nullptr;
    DPoint m_mousePosition;
    char m_clicked = 0;
    bool m_isEntered = false;
};

