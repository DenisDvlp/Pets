#pragma once
#include "DView.h"
#include "DPoint.h"

class DButton : public DView
{
  enum StatusType : byte {
    Main,
    Click,
    Disable,
    Hover,
  };
public:
    DButton(Key);
    using DView::DView;
    void setMainColor(DColor);
    void setClickColor(DColor);
    void setDisableColor(DColor);
    void setHoverColor(DColor);
    void draw(IDDraw&) const override;
    void onSystemMouseMove(const DMouseMessage&) override;
    void onSystemMouseUp(const DMouseMessage&) override;
    void onSystemMouseDown(const DMouseMessage&) override;
    void onSystemKeyUp(Key) override;
    void onSystemKeyDown(Key) override;
private:
    StatusType m_status = StatusType::Main;
    DColor m_colors[4] = {
      DColors::WHITE,
      DColors::WHITE,
      DColors::WHITE,
      DColors::WHITE
    };
    Key m_key = Key::NONE;
};

