object Form1: TForm1
  Left = 286
  Top = 115
  BorderStyle = bsSingle
  Caption = #1047#1072#1103#1074#1082#1080' 2.0'
  ClientHeight = 553
  ClientWidth = 865
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Reference Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  DesignSize = (
    865
    553)
  PixelsPerInch = 96
  TextHeight = 15
  object Panel3: TPanel
    Left = 0
    Top = 56
    Width = 865
    Height = 497
    Anchors = [akLeft, akTop, akRight, akBottom]
    TabOrder = 1
    DesignSize = (
      865
      497)
    object BZ1: TButton
      Left = 744
      Top = 272
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1047#1072#1082#1088#1099#1090#1100' '#1079#1072#1103#1074#1082#1091
      Enabled = False
      TabOrder = 0
      OnClick = BZ1Click
    end
    object BU2: TButton
      Left = 504
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Enabled = False
      TabOrder = 1
      OnClick = BU2Click
    end
    object BU1: TButton
      Left = 384
      Top = 272
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Enabled = False
      TabOrder = 2
      OnClick = BU1Click
    end
    object BI2: TButton
      Left = 624
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      Enabled = False
      TabOrder = 3
      OnClick = BI2Click
    end
    object BI1: TButton
      Left = 504
      Top = 272
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      Enabled = False
      TabOrder = 4
      OnClick = BI1Click
    end
    object BD2: TButton
      Left = 744
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Enabled = False
      TabOrder = 5
      OnClick = BD2Click
    end
    object BD1: TButton
      Left = 624
      Top = 272
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 6
      OnClick = BD1Click
    end
    object sgZay1: TStringGrid
      Left = 8
      Top = 0
      Width = 849
      Height = 265
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = clWhite
      DefaultColWidth = 40
      DefaultRowHeight = 20
      FixedColor = clSilver
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goThumbTracking]
      TabOrder = 7
      OnMouseDown = sgZay1MouseDown
      OnMouseMove = SGMouseMove
      OnSelectCell = sgZay1SelectCell
      ColWidths = (
        40
        89
        288
        380
        27)
    end
    object sgZay2: TStringGrid
      Left = 8
      Top = 304
      Width = 849
      Height = 153
      Anchors = [akLeft, akRight, akBottom]
      Color = clWhite
      ColCount = 3
      DefaultColWidth = 40
      DefaultRowHeight = 20
      FixedColor = clSilver
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect, goThumbTracking]
      TabOrder = 8
      OnMouseDown = sgZay2MouseDown
      OnMouseMove = SGMouseMove
      OnSelectCell = sgZay2SelectCell
      ColWidths = (
        40
        89
        697)
    end
    object PanelDobav1: TPanel
      Left = 0
      Top = 168
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 9
      Visible = False
      DesignSize = (
        849
        97)
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 27
        Height = 15
        Caption = #1044#1072#1090#1072
      end
      object Label2: TLabel
        Left = 112
        Top = 8
        Width = 68
        Height = 15
        Caption = #1058#1057#1055', '#1040#1076#1088#1077#1089
      end
      object Label3: TLabel
        Left = 8
        Top = 48
        Width = 57
        Height = 15
        Caption = #1055#1088#1086#1073#1083#1077#1084#1072
      end
      object DateZay1: TDateTimePicker
        Left = 8
        Top = 24
        Width = 97
        Height = 23
        Date = 41485.000000000000000000
        Time = 41485.000000000000000000
        DateMode = dmUpDown
        TabOrder = 0
      end
      object ComboBoxZay: TComboBox
        Left = 112
        Top = 24
        Width = 633
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        ItemHeight = 15
        TabOrder = 1
      end
      object EditZay: TEdit
        Left = 8
        Top = 64
        Width = 737
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 2
      end
      object Button1: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 3
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 4
        OnClick = Button2Click
      end
    end
    object PanelUdal2: TPanel
      Left = 8
      Top = 392
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 10
      Visible = False
      DesignSize = (
        849
        97)
      object Label6: TLabel
        Left = 8
        Top = 8
        Width = 98
        Height = 15
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100':'
      end
      object Label8: TLabel
        Left = 8
        Top = 24
        Width = 737
        Height = 65
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Button14: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 0
        OnClick = Button14Click
      end
      object Button15: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 1
        OnClick = Button15Click
      end
    end
    object PanelUdal1: TPanel
      Left = 0
      Top = 168
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 11
      Visible = False
      DesignSize = (
        849
        97)
      object Label4: TLabel
        Left = 8
        Top = 8
        Width = 98
        Height = 15
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100':'
      end
      object LabelZay: TLabel
        Left = 8
        Top = 24
        Width = 737
        Height = 65
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Button3: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 0
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 1
        OnClick = Button4Click
      end
    end
    object PanelDobav2: TPanel
      Left = 8
      Top = 392
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 12
      Visible = False
      DesignSize = (
        849
        97)
      object Label5: TLabel
        Left = 8
        Top = 8
        Width = 27
        Height = 15
        Caption = #1044#1072#1090#1072
      end
      object Label7: TLabel
        Left = 8
        Top = 48
        Width = 52
        Height = 15
        Caption = #1057#1076#1077#1083#1072#1085#1086
      end
      object DateZay2: TDateTimePicker
        Left = 8
        Top = 24
        Width = 97
        Height = 23
        Date = 41485.000000000000000000
        Time = 41485.000000000000000000
        DateMode = dmUpDown
        TabOrder = 0
      end
      object Edit1: TEdit
        Left = 8
        Top = 64
        Width = 737
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 1
      end
      object Button12: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 2
        OnClick = Button12Click
      end
      object Button13: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 3
        OnClick = Button13Click
      end
    end
  end
  object Panel4: TPanel
    Left = 0
    Top = 56
    Width = 865
    Height = 497
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Panel4'
    TabOrder = 2
    DesignSize = (
      865
      497)
    object BU3: TButton
      Left = 504
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      TabOrder = 0
      OnClick = BU3Click
    end
    object BI3: TButton
      Left = 624
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      TabOrder = 1
      OnClick = BI3Click
    end
    object BD3: TButton
      Left = 744
      Top = 464
      Width = 113
      Height = 25
      Anchors = [akRight, akBottom]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      TabOrder = 2
      OnClick = BD3Click
    end
    object sgTerm: TStringGrid
      Left = 8
      Top = 0
      Width = 849
      Height = 457
      Anchors = [akLeft, akTop, akRight, akBottom]
      Color = clWhite
      ColCount = 6
      DefaultColWidth = 40
      DefaultRowHeight = 20
      FixedColor = clSilver
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goThumbTracking]
      TabOrder = 3
      OnMouseDown = sgTermMouseDown
      OnMouseMove = SGMouseMove
      OnSelectCell = sgTermSelectCell
      ColWidths = (
        40
        89
        108
        132
        56
        398)
      RowHeights = (
        20
        20
        20
        20
        20)
    end
    object PanelDobav3: TPanel
      Left = 8
      Top = 392
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 4
      Visible = False
      DesignSize = (
        849
        97)
      object Label11: TLabel
        Left = 8
        Top = 8
        Width = 65
        Height = 15
        Caption = #1048#1085#1074'. '#1085#1086#1084#1077#1088
      end
      object Label12: TLabel
        Left = 8
        Top = 48
        Width = 68
        Height = 15
        Caption = #1058#1057#1055', '#1040#1076#1088#1077#1089
      end
      object Label13: TLabel
        Left = 112
        Top = 8
        Width = 99
        Height = 15
        Caption = #1057#1077#1088#1080#1081#1085#1099#1081' '#1085#1086#1084#1077#1088
      end
      object Label14: TLabel
        Left = 272
        Top = 8
        Width = 45
        Height = 15
        Caption = #1052#1086#1076#1077#1083#1100
      end
      object Label15: TLabel
        Left = 472
        Top = 8
        Width = 58
        Height = 15
        Caption = #1058#1080#1087' '#1089#1074#1103#1079#1080
      end
      object Edit2: TEdit
        Left = 8
        Top = 24
        Width = 97
        Height = 23
        TabOrder = 0
      end
      object Button7: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 1
        OnClick = Button7Click
      end
      object Button9: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 2
        OnClick = Button9Click
      end
      object Edit3: TEdit
        Left = 112
        Top = 24
        Width = 153
        Height = 23
        TabOrder = 3
      end
      object Edit4: TEdit
        Left = 272
        Top = 24
        Width = 193
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 4
      end
      object Edit5: TEdit
        Left = 472
        Top = 24
        Width = 57
        Height = 23
        Anchors = [akTop, akRight]
        TabOrder = 5
      end
      object Edit6: TEdit
        Left = 8
        Top = 64
        Width = 737
        Height = 23
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 6
      end
    end
    object PanelUdal3: TPanel
      Left = 8
      Top = 392
      Width = 849
      Height = 97
      Anchors = [akLeft, akRight, akBottom]
      Color = clSilver
      TabOrder = 5
      Visible = False
      DesignSize = (
        849
        97)
      object Label9: TLabel
        Left = 8
        Top = 8
        Width = 98
        Height = 15
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1079#1072#1087#1080#1089#1100':'
      end
      object Label10: TLabel
        Left = 8
        Top = 24
        Width = 737
        Height = 65
        Anchors = [akLeft, akTop, akRight]
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsItalic]
        ParentFont = False
      end
      object Button5: TButton
        Left = 752
        Top = 16
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1059#1076#1072#1083#1080#1090#1100
        TabOrder = 0
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 752
        Top = 56
        Width = 89
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1054#1090#1084#1077#1085#1072
        TabOrder = 1
        OnClick = Button6Click
      end
    end
    object M: TMemo
      Left = 624
      Top = 192
      Width = 113
      Height = 97
      TabOrder = 6
      Visible = False
    end
  end
  object PanelSearch: TPanel
    Left = 0
    Top = 0
    Width = 865
    Height = 59
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
    DesignSize = (
      865
      59)
    object editsearch: TEdit
      Left = 8
      Top = 8
      Width = 689
      Height = 23
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 0
      OnKeyPress = editsearchKeyPress
    end
    object Button8: TButton
      Left = 704
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1055#1086#1080#1089#1082
      TabOrder = 1
      OnClick = Button8Click
    end
    object Panel1: TPanel
      Left = 64
      Top = 40
      Width = 113
      Height = 22
      Caption = #1041#1072#1079#1072' '#1090#1077#1088#1084#1080#1085#1072#1083#1086#1074
      Color = clSilver
      TabOrder = 2
      OnClick = Panel1Click
    end
    object Panel2: TPanel
      Left = 8
      Top = 40
      Width = 57
      Height = 22
      BorderStyle = bsSingle
      Caption = #1047#1072#1103#1074#1082#1080
      Color = clSilver
      TabOrder = 3
      OnClick = Panel2Click
    end
    object Button10: TButton
      Left = 784
      Top = 8
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = #1042#1089#1077
      TabOrder = 4
      OnClick = Button10Click
    end
  end
  object Panel5: TPanel
    Left = 0
    Top = 0
    Width = 865
    Height = 553
    Anchors = [akLeft, akTop, akRight, akBottom]
    BevelOuter = bvNone
    Caption = #1099#1103#1074#1095#1095#1089
    Color = clGray
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -19
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
end