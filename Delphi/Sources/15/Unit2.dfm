object Form1: TForm1
  Left = 228
  Top = 118
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 
    '                                     "Multicalculator" by Petrov' +
    ' D. (c)'
  ClientHeight = 73
  ClientWidth = 569
  Color = cl3DLight
  Ctl3D = False
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Microsoft Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object E1: TEdit
    Left = 80
    Top = 8
    Width = 409
    Height = 22
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxLength = 256
    ParentFont = False
    TabOrder = 0
  end
  object E2: TEdit
    Left = 80
    Top = 40
    Width = 409
    Height = 22
    TabStop = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    MaxLength = 256
    ParentFont = False
    ReadOnly = True
    TabOrder = 3
  end
  object B: TButton
    Left = 496
    Top = 8
    Width = 65
    Height = 60
    Caption = '='
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'Century Gothic'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = BClick
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 65
    Height = 60
    Caption = 'C'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'DejaVu Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    OnClick = BClic
  end
end
