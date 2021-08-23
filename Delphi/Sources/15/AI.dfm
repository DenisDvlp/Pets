object Form1: TForm1
  Left = 185
  Top = 412
  Width = 870
  Height = 640
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Edit1: TEdit
    Left = 88
    Top = 320
    Width = 553
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
    OnKeyPress = Edit1KeyPress
  end
  object Memo1: TMemo
    Left = 88
    Top = 96
    Width = 553
    Height = 209
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
  end
end
