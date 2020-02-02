//Root.cpp
#include "Root.h"
#include "IDraw.h"
#include "Application.h"
#include "Utils.h"

Root::Root()
{
    for(size_t i = 0; i < 12; i++)
    {
        m_primitives[i].color = Color::BLACK;
        m_primitives[i].textColor = Color::WHITE;
        m_primitives[i].textAlign = Align::LEFT_TOP;
        m_primitives[i].position(i, 0);
        m_primitives[i].size(1, 1);
        m_primitives[i].setParent(this);
        m_primitives[i].onMouseEnter.link(this, &Root::onBoxEnter);
        m_primitives[i].onMouseLeave.link(this, &Root::onBoxLeave);
        m_primitives[i].onMouseDown.link(this, &Root::onBoxClick);
        m_primitives[i].onMouseUp.link(this, &Root::onBoxClickUp);
    }
    m_primitives[0].text = "H";
    m_primitives[1].text = "e";
    m_primitives[2].text = "l";
    m_primitives[3].text = "l";
    m_primitives[4].text = "o";
    m_primitives[5].text = " ";
    m_primitives[6].text = "w";
    m_primitives[7].text = "o";
    m_primitives[8].text = "r";
    m_primitives[9].text = "l";
    m_primitives[10].text = "d";
    m_primitives[11].text = "!";

    for(auto i = 0; i < 5; ++i)
    {
        m_figure[i].size(20, 10);
        m_figure[i].color = Color::BLUE;
        m_figure[i].onMouseEnter.link(this, &Root::onBoxEnter);
        m_figure[i].onMouseLeave.link(this, &Root::onBoxLeave);
        m_figure[i].onMouseDown.link(this, &Root::onBoxClick);
        m_figure[i].onMouseUp.link(this, &Root::onBoxClickUp);
        //m_figure[i].setParent(this);
    }
    Application::events.onMouseMove.link(this, &Root::onMouseMove);

    m_figure[0].position(5, 5);
    m_figure[1].position(10, 10);
    m_figure[2].position(8, 8);
    m_figure[3].position(16, 16);
    m_figure[4].position(15, 15);

    m_figure[2].size(8, 4);
    m_figure[3].size(8, 4);
    m_figure[4].size(8, 4);
    m_figure[2].color = Color::RED;
    m_figure[3].color = Color::RED;
    m_figure[4].color = Color::RED;
}
void Root::onBoxEnter(Sender sender)
{
}

void Root::onBoxLeave(Sender sender)
{
}

void Root::onBoxClick(Sender sender, Key key)
{
    m_f = reinterpret_cast<Drawable*>(sender);
    m_f->bringToFront();
    m_p = m_p - m_f->position();
}

void Root::onBoxClickUp(Sender sender, Key)
{
    m_f = nullptr;
}

void Root::onMouseMove(Point16 p)
{
    if(m_f)
    {
        m_f->position(p - m_p);
    }
    else
    {
        m_p = p;
    }
}

void Root::onDraw(IDraw* draw)
{
    draw->clear(Color::BLACK);
}
