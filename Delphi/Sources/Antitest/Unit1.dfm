object Form1: TForm1
  Left = 234
  Top = 145
  Width = 1041
  Height = 539
  Caption = 'Uncryptor [by Petrov D.]'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    1033
    505)
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 360
    Top = 8
    Width = 153
    Height = 41
    Caption = #1086#1090#1082#1088#1099#1090#1100' '#1096#1080#1092#1088#1086#1074#1072#1085#1099#1081' '#1092#1072#1081#1083
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 520
    Top = 8
    Width = 121
    Height = 41
    Caption = #1088#1072#1089#1096#1080#1092#1088#1086#1074#1072#1090#1100
    TabOrder = 1
    OnClick = Button2Click
  end
  object Memo1: TMemo
    Left = 8
    Top = 56
    Width = 505
    Height = 441
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 2
  end
  object Memo2: TMemo
    Left = 520
    Top = 56
    Width = 505
    Height = 441
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = MAC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 345
    Height = 41
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMaroon
    Font.Height = -16
    Font.Name = 'Comic Sans MS'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object GroupBox1: TGroupBox
    Left = 656
    Top = 8
    Width = 209
    Height = 41
    BiDiMode = bdLeftToRight
    Caption = #1050#1086#1088#1088#1077#1082#1090#1080#1088#1086#1074#1082#1072' '#1088#1072#1089#1096#1080#1092#1088#1086#1074#1082#1080
    ParentBiDiMode = False
    TabOrder = 5
    object Button5: TButton
      Left = 16
      Top = 16
      Width = 89
      Height = 17
      Caption = #1089#1076#1074#1080#1075' '#1074#1083#1077#1074#1086
      TabOrder = 0
      OnClick = Button5Click
    end
    object Button6: TButton
      Left = 112
      Top = 16
      Width = 81
      Height = 17
      Caption = #1089#1076#1074#1080#1075' '#1074#1087#1088#1072#1074#1086
      TabOrder = 1
      OnClick = Button6Click
    end
  end
  object m: TMemo
    Left = 952
    Top = 8
    Width = 17
    Height = 25
    TabOrder = 6
    Visible = False
  end
  object Button3: TButton
    Left = 872
    Top = 8
    Width = 65
    Height = 41
    Caption = #1089#1086#1093#1088#1072#1085#1080#1090#1100
    TabOrder = 7
    OnClick = Button3Click
  end
  object OpenDialog1: TOpenDialog
    Left = 992
    Top = 16
  end
  object SaveDialog1: TSaveDialog
    Filter = '*.txt'
    Left = 960
    Top = 24
  end
end
