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
    DButton();
    using DView::DView;
    void setMainColor(DColor);
    void setClickColor(DColor);
    void setDisableColor(DColor);
    void setHoverColor(DColor);
    void draw(IDDraw&) const override;
    void onSystemMouseMove(const DPoint&) override;
private:
    StatusType m_status = StatusType::Main;
    DColor m_colors[4] = {
      DColors::WHITE,
      DColors::WHITE,
      DColors::WHITE,
      DColors::WHITE
    };
};

