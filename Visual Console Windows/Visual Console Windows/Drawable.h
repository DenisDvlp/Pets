//Drawable.h
#pragma once
#include "IDraw.h"
#include "DVector.h"
#include "Signal.h"
#include "Sizable.h"
#include "Positionable.h"

class Drawable
    : public Sizable16
    , public Positionable16
{
public:
    explicit Drawable(Drawable* = nullptr);
    virtual ~Drawable();
    Drawable* parent() const;
    void setParent(Drawable*);
    void bringToFront();
    void sendToBack();
    void draw(IDraw*);
    bool mouseUp(Key);
    bool mouseDown(Key);
    bool mouseMove(Point16);
    Signal<Sender, Key> onMouseUp;
    Signal<Sender, Key> onMouseDown;
    Signal<Sender, Point16> onMouseMove;
    Signal<Sender> onMouseEnter;
    Signal<Sender> onMouseLeave;
    Signal<Sender, Key> onClick;
protected:
    Rect16 m_rect;
private:
    void resize(Size16&) override;
    void reposition(Point16&) override;
    virtual void onDraw(IDraw*);
private:
    DVector<Drawable*> m_children;
    Drawable* m_parent = nullptr;
    Point16 m_mousePosition;
    char m_clicked = 0;
    bool m_isEntered = false;
};

