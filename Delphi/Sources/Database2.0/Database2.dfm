object Form1: TForm1
  Left = 168
  Top = 123
  BorderStyle = bsSingle
  Caption = 'Database 2.1.4 '#1086#1090' 31 '#1084#1072#1103' 2013'
  ClientHeight = 581
  ClientWidth = 1016
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    1016
    581)
  PixelsPerInch = 96
  TextHeight = 13
  object M: TMemo
    Left = 0
    Top = 168
    Width = 25
    Height = 25
    TabOrder = 12
    Visible = False
  end
  object StringGridHISTORY: TStringGrid
    Left = -1
    Top = 56
    Width = 837
    Height = 415
    Anchors = [akLeft, akTop, akRight, akBottom]
    BorderStyle = bsNone
    ColCount = 7
    Ctl3D = True
    DefaultRowHeight = 18
    FixedColor = clActiveBorder
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goThumbTracking]
    ParentCtl3D = False
    TabOrder = 4
    Visible = False
    OnMouseDown = SGMouseDown
    OnMouseMove = SGMouseMove
    OnSelectCell = StringGridHISTORYSelectCell
    ColWidths = (
      33
      94
      67
      307
      64
      62
      187)
  end
  object StringGridINV: TStringGrid
    Left = -1
    Top = 56
    Width = 837
    Height = 415
    Anchors = [akLeft, akTop, akRight, akBottom]
    BorderStyle = bsNone
    ColCount = 8
    Ctl3D = True
    DefaultRowHeight = 18
    FixedColor = clActiveBorder
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect, goThumbTracking]
    ParentCtl3D = False
    TabOrder = 2
    OnMouseDown = SGMouseDown
    OnMouseMove = SGMouseMove
    OnSelectCell = StringGridINVSelectCell
    ColWidths = (
      33
      64
      64
      243
      52
      75
      150
      132)
  end
  object PanelMENU: TPanel
    Left = 836
    Top = 0
    Width = 180
    Height = 581
    Anchors = [akTop, akRight, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 8
      Top = 328
      Width = 169
      Height = 209
      BiDiMode = bdLeftToRight
      Caption = #1060#1048#1051#1068#1058#1056#1067
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 2
      object Label10: TLabel
        Left = 9
        Top = 16
        Width = 33
        Height = 15
        Caption = #1058#1054#1041#1054
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object filtr3: TButton
        Left = 8
        Top = 104
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = filtr3Click
      end
      object filtr4: TButton
        Left = 8
        Top = 128
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = filtr4Click
      end
      object filtr5: TButton
        Left = 8
        Top = 152
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = filtr5Click
      end
      object filtr6: TButton
        Left = 8
        Top = 176
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = filtr6Click
      end
      object ComboBoxTOBO1: TComboBox
        Left = 8
        Top = 32
        Width = 153
        Height = 23
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ItemHeight = 15
        ParentFont = False
        TabOrder = 0
        OnChange = ComboBoxTOBO1Change
      end
      object filtr2: TButton
        Left = 8
        Top = 80
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = filtr2Click
      end
      object filtr1: TButton
        Left = 8
        Top = 56
        Width = 153
        Height = 23
        Caption = #1092#1080#1083#1100#1090#1088
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = filtr1Click
      end
      object redak: TButton
        Left = 88
        Top = 0
        Width = 73
        Height = 25
        Hint = #1056#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1077' '#1092#1080#1083#1100#1090#1088#1086#1074' '#1076#1083#1103' '#1074#1099#1073#1086#1088#1082#1080' '#1087#1086' '#1090#1080#1087#1072#1084
        Caption = #1056#1077#1076#1072#1082#1090#1080#1088'.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        OnClick = redakClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 0
      Width = 169
      Height = 177
      BiDiMode = bdLeftToRight
      Caption = #1055#1045#1056#1045#1052#1045#1065#1045#1053#1048#1045
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 0
      object Label7: TLabel
        Left = 9
        Top = 16
        Width = 75
        Height = 15
        Caption = #1044#1072#1090#1072' ('#1082#1086#1075#1076#1072')'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 9
        Top = 56
        Width = 66
        Height = 15
        Caption = #1050#1086#1076' ('#1082#1091#1076#1072')'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label17: TLabel
        Left = 9
        Top = 100
        Width = 4
        Height = 15
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object ComboBoxKUDA1: TComboBox
        Left = 8
        Top = 72
        Width = 153
        Height = 23
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ItemHeight = 15
        ParentFont = False
        TabOrder = 1
        OnChange = ComboBoxKUDA1Change
      end
      object Move1: TButton
        Left = 8
        Top = 136
        Width = 153
        Height = 33
        Hint = #1042#1099#1073#1077#1088#1080#1090#1077' '#1084#1077#1089#1090#1086' '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1103' '#1074' '#1087#1086#1083#1077' '#1074#1099#1096#1077
        Caption = #1055#1077#1088#1077#1084#1077#1089#1090#1080#1090#1100
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = Move1Click
      end
      object DateTimePicker1: TDateTimePicker
        Left = 8
        Top = 32
        Width = 153
        Height = 23
        Date = 41180.693150127310000000
        Time = 41180.693150127310000000
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
    end
    object GroupBox5: TGroupBox
      Left = 8
      Top = 176
      Width = 169
      Height = 153
      BiDiMode = bdLeftToRight
      Caption = #1048#1057#1058#1054#1056#1048#1071
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentFont = False
      TabOrder = 1
      object Label13: TLabel
        Left = 9
        Top = 16
        Width = 9
        Height = 15
        Caption = #1057
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label14: TLabel
        Left = 9
        Top = 56
        Width = 15
        Height = 15
        Caption = #1055#1086
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object History2: TButton
        Left = 8
        Top = 120
        Width = 153
        Height = 23
        Hint = #1042#1089#1077' '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1103' '#1074#1099#1073#1088#1072#1085#1086#1075#1086' '#1080#1085#1074#1077#1085#1090#1072#1088#1085#1086#1075#1086' '#1085#1086#1084#1077#1088#1072
        Caption = #1055#1086' '#1080#1085#1074'. '#1085#1086#1084#1077#1088#1091
        Enabled = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = History2Click
      end
      object History1: TButton
        Left = 8
        Top = 96
        Width = 153
        Height = 23
        Hint = #1047#1072#1076#1072#1081#1090#1077' '#1076#1080#1072#1087#1072#1079#1086#1085' '#1076#1072#1090#1099' '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1081' '#1090#1077#1093#1085#1080#1082#1080
        Caption = #1055#1086' '#1076#1072#1090#1077
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = History1Click
      end
      object DateTimePicker2: TDateTimePicker
        Left = 8
        Top = 32
        Width = 153
        Height = 23
        Date = 41180.693150127310000000
        Time = 41180.693150127310000000
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
      end
      object DateTimePicker3: TDateTimePicker
        Left = 8
        Top = 72
        Width = 153
        Height = 23
        Date = 41180.693150127310000000
        Time = 41180.693150127310000000
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
    object Move2: TButton
      Left = 16
      Top = 544
      Width = 153
      Height = 31
      Hint = 
        #1055#1086#1089#1083#1077' '#1089#1087#1080#1089#1072#1085#1080#1103' '#1080#1085#1074#1077#1085#1090#1072#1088#1085#1099#1081' '#1085#1086#1084#1077#1088' '#1084#1086#1078#1085#1086' '#1074#1086#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1080#1079#1084#1077#1085#1080#1074' '#1087#1086#1083#1077' ' +
        #1082#1086#1076#1072
      Caption = #1057#1087#1080#1089#1072#1090#1100
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = Move2Click
    end
  end
  object PanelINV: TPanel
    Left = -1
    Top = 471
    Width = 814
    Height = 112
    Anchors = [akLeft, akRight, akBottom]
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 3
    DesignSize = (
      814
      112)
    object Label6: TLabel
      Left = 452
      Top = 0
      Width = 81
      Height = 13
      Anchors = [akRight, akBottom]
      AutoSize = False
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
    end
    object Label2: TLabel
      Left = 8
      Top = 0
      Width = 78
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1048#1085#1074#1077#1085#1090#1072#1088#1085#1099#1081
    end
    object Label3: TLabel
      Left = 8
      Top = 40
      Width = 21
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1058#1080#1087
    end
    object Label4: TLabel
      Left = 120
      Top = 0
      Width = 45
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1052#1086#1076#1077#1083#1100
    end
    object Label5: TLabel
      Left = 120
      Top = 40
      Width = 23
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1050#1086#1076
    end
    object LabelDIVISION: TLabel
      Left = 120
      Top = 80
      Width = 321
      Height = 15
      Anchors = [akLeft, akRight, akBottom]
      AutoSize = False
    end
    object Dobav1: TButton
      Left = 732
      Top = 7
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = Dobav1Click
    end
    object EditNUMBER: TEdit
      Left = 8
      Top = 16
      Width = 105
      Height = 23
      Anchors = [akLeft, akBottom]
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      OnChange = EditNUMBERChange
    end
    object EditMODEL: TEdit
      Left = 120
      Top = 16
      Width = 321
      Height = 23
      Anchors = [akLeft, akRight, akBottom]
      TabOrder = 1
      OnChange = EditMODELChange
    end
    object MemoCOMMENT1: TMemo
      Left = 448
      Top = 16
      Width = 277
      Height = 90
      Anchors = [akRight, akBottom]
      TabOrder = 4
      OnChange = MemoCOMMENT1Change
    end
    object ComboBoxTYPE: TComboBox
      Left = 8
      Top = 56
      Width = 105
      Height = 23
      Anchors = [akLeft, akBottom]
      ItemHeight = 15
      TabOrder = 2
      OnChange = ComboBoxTYPEChange
    end
    object ComboBoxKOD: TComboBox
      Left = 120
      Top = 56
      Width = 217
      Height = 23
      Anchors = [akLeft, akBottom]
      ItemHeight = 15
      TabOrder = 3
      OnChange = ComboBoxKODChange
    end
    object Izmen1: TButton
      Left = 732
      Top = 39
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = Izmen1Click
    end
    object Udal1: TButton
      Left = 732
      Top = 71
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
      Visible = False
      OnClick = Udal1Click
    end
  end
  object PanelSEARCH: TPanel
    Left = -1
    Top = 0
    Width = 838
    Height = 57
    Anchors = [akLeft, akTop, akRight]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      838
      57)
    object Label1: TLabel
      Left = 136
      Top = 35
      Width = 56
      Height = 15
      Caption = #1048#1089#1082#1072#1090#1100' '#1074':'
    end
    object EditSEARCH: TEdit
      Left = 136
      Top = 8
      Width = 617
      Height = 25
      Hint = #1074#1074#1086#1076#1080#1090#1077' '#1082#1083#1102#1095#1077#1074#1099#1077' '#1089#1083#1086#1074#1072' '#1095#1077#1088#1077#1079' '#1087#1088#1086#1073#1077#1083' '#1080#1083#1080' '#1079#1072#1087#1103#1090#1091#1102
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnKeyPress = EditSEARCHKeyPress
    end
    object ButtonSEARCH: TButton
      Left = 757
      Top = 8
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1053#1072#1081#1090#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = ButtonSEARCHClick
    end
    object CheckBox1: TCheckBox
      Left = 200
      Top = 35
      Width = 65
      Height = 17
      Caption = #1048#1085#1074' '#8470
      Checked = True
      State = cbChecked
      TabOrder = 2
    end
    object CheckBox2: TCheckBox
      Left = 272
      Top = 35
      Width = 49
      Height = 17
      Caption = #1058#1080#1087
      Checked = True
      State = cbChecked
      TabOrder = 3
    end
    object CheckBox3: TCheckBox
      Left = 328
      Top = 35
      Width = 65
      Height = 17
      Caption = #1052#1086#1076#1077#1083#1100
      Checked = True
      State = cbChecked
      TabOrder = 4
    end
    object CheckBox4: TCheckBox
      Left = 400
      Top = 35
      Width = 65
      Height = 17
      Caption = #1060#1080#1083#1080#1072#1083
      Checked = True
      State = cbChecked
      TabOrder = 5
    end
    object CheckBox5: TCheckBox
      Left = 472
      Top = 35
      Width = 49
      Height = 17
      Caption = #1050#1086#1076
      Checked = True
      State = cbChecked
      TabOrder = 6
    end
    object CheckBox6: TCheckBox
      Left = 528
      Top = 35
      Width = 113
      Height = 17
      Caption = #1055#1086#1076#1088#1072#1079#1076#1077#1083#1077#1085#1080#1077
      Checked = True
      State = cbChecked
      TabOrder = 7
    end
    object CheckBox7: TCheckBox
      Left = 648
      Top = 35
      Width = 97
      Height = 17
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
      Checked = True
      State = cbChecked
      TabOrder = 8
    end
    object VEXCEL: TButton
      Left = 8
      Top = 8
      Width = 65
      Height = 25
      Hint = #1080#1084#1087#1086#1088#1090' '#1090#1077#1082#1091#1097#1077#1081' '#1090#1072#1073#1083#1080#1094#1099' '#1074' Excel-'#1092#1072#1081#1083
      Caption = #1042' Excel'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnClick = VEXCELClick
    end
    object bprev: TButton
      Left = 80
      Top = 8
      Width = 25
      Height = 25
      Hint = #1087#1077#1088#1077#1076#1099#1076#1091#1097#1080#1081' '#1087#1086#1080#1089#1082
      Caption = '<'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Terminal'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 10
      OnClick = bprevClick
    end
    object bnext: TButton
      Left = 104
      Top = 8
      Width = 25
      Height = 25
      Hint = #1089#1083#1077#1076#1091#1102#1097#1080#1081' '#1087#1086#1080#1089#1082
      Caption = '>'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -20
      Font.Name = 'Terminal'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 11
      OnClick = bnextClick
    end
    object Panel1: TPanel
      Left = 2
      Top = 40
      Width = 63
      Height = 20
      BorderStyle = bsSingle
      Caption = #1087#1086#1080#1089#1082
      Color = clActiveBorder
      TabOrder = 12
      OnClick = Panel1Click
    end
    object Panel2: TPanel
      Left = 65
      Top = 40
      Width = 62
      Height = 20
      Caption = #1080#1089#1090#1086#1088#1080#1103
      Color = clActiveBorder
      TabOrder = 13
      OnClick = Panel2Click
    end
  end
  object PanelKOD: TPanel
    Left = -1
    Top = 471
    Width = 814
    Height = 112
    Anchors = [akLeft, akRight, akBottom]
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 6
    DesignSize = (
      814
      112)
    object Label11: TLabel
      Left = 8
      Top = 0
      Width = 23
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1050#1086#1076
    end
    object Label15: TLabel
      Left = 8
      Top = 40
      Width = 152
      Height = 15
      Anchors = [akLeft, akBottom]
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1087#1086#1076#1088#1072#1079#1076#1077#1083#1077#1085#1080#1103
    end
    object Label9: TLabel
      Left = 396
      Top = 40
      Width = 85
      Height = 15
      Anchors = [akRight, akBottom]
      Caption = #1056#1072#1089#1087#1086#1083#1086#1078#1077#1085#1080#1077
    end
    object Dobav2: TButton
      Left = 732
      Top = 7
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = Dobav2Click
    end
    object EditKOD: TEdit
      Left = 8
      Top = 16
      Width = 105
      Height = 23
      Anchors = [akLeft, akBottom]
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      OnChange = EditKODChange
    end
    object EditDIVISION: TEdit
      Left = 8
      Top = 56
      Width = 381
      Height = 23
      Anchors = [akLeft, akRight, akBottom]
      TabOrder = 1
      OnChange = EditDIVISIONChange
    end
    object Izmen2: TButton
      Left = 732
      Top = 39
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = Izmen2Click
    end
    object Udal2: TButton
      Left = 732
      Top = 71
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Visible = False
      OnClick = Udal2Click
    end
    object ComboBoxTOBO2: TComboBox
      Left = 396
      Top = 56
      Width = 129
      Height = 23
      Anchors = [akRight, akBottom]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ItemHeight = 15
      ParentFont = False
      TabOrder = 2
      OnChange = ComboBoxTOBO2Change
    end
  end
  object PanelTOBO: TPanel
    Left = -1
    Top = 471
    Width = 814
    Height = 112
    Anchors = [akLeft, akRight, akBottom]
    Ctl3D = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Reference Sans Serif'
    Font.Style = []
    ParentCtl3D = False
    ParentFont = False
    TabOrder = 7
    DesignSize = (
      814
      112)
    object Label12: TLabel
      Left = 152
      Top = 0
      Width = 81
      Height = 13
      AutoSize = False
      Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
    end
    object Label16: TLabel
      Left = 8
      Top = 0
      Width = 73
      Height = 15
      Caption = #1053#1086#1084#1077#1088' '#1058#1054#1041#1054
    end
    object Dobav3: TButton
      Left = 732
      Top = 7
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = Dobav3Click
    end
    object EditTOBO: TEdit
      Left = 8
      Top = 16
      Width = 137
      Height = 23
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      OnChange = EditTOBOChange
    end
    object MemoCOMMENT2: TMemo
      Left = 152
      Top = 16
      Width = 317
      Height = 89
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 1
      OnChange = MemoCOMMENT2Change
    end
    object Izmen3: TButton
      Left = 732
      Top = 39
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = Izmen3Click
    end
    object Udal3: TButton
      Left = 732
      Top = 71
      Width = 73
      Height = 33
      Anchors = [akTop, akRight]
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      Visible = False
      OnClick = Udal3Click
    end
  end
  object UpDown1: TUpDown
    Left = 814
    Top = 471
    Width = 22
    Height = 110
    Anchors = [akRight, akBottom]
    Min = 1
    Max = 3
    Position = 1
    TabOrder = 5
    OnChangingEx = UpDown1ChangingEx
  end
  object PanelVexcel11: TPanel
    Left = 327
    Top = 108
    Width = 353
    Height = 129
    Anchors = []
    Color = clBlue
    TabOrder = 8
    Visible = False
    object PanelVexcel12: TPanel
      Left = 8
      Top = 8
      Width = 337
      Height = 113
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label18: TLabel
        Left = 8
        Top = 3
        Width = 90
        Height = 15
        Caption = #1048#1084#1087#1086#1088#1090' '#1087#1086#1083#1103':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object CB11: TCheckBox
        Left = 8
        Top = 27
        Width = 57
        Height = 17
        Caption = #1048#1085#1074' '#8470
        Checked = True
        State = cbChecked
        TabOrder = 0
      end
      object CB12: TCheckBox
        Left = 88
        Top = 27
        Width = 49
        Height = 17
        Caption = #1058#1080#1087
        Checked = True
        State = cbChecked
        TabOrder = 1
      end
      object CB13: TCheckBox
        Left = 160
        Top = 27
        Width = 65
        Height = 17
        Caption = #1052#1086#1076#1077#1083#1100
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object CB14: TCheckBox
        Left = 232
        Top = 27
        Width = 73
        Height = 17
        Caption = #1060#1080#1083#1080#1072#1083
        Checked = True
        State = cbChecked
        TabOrder = 3
      end
      object CB15: TCheckBox
        Left = 8
        Top = 51
        Width = 65
        Height = 17
        Caption = #1050#1086#1076
        Checked = True
        State = cbChecked
        TabOrder = 4
      end
      object CB16: TCheckBox
        Left = 88
        Top = 51
        Width = 121
        Height = 17
        Caption = #1055#1086#1076#1088#1072#1079#1076#1077#1083#1077#1085#1080#1077
        Checked = True
        State = cbChecked
        TabOrder = 5
      end
      object CB17: TCheckBox
        Left = 232
        Top = 51
        Width = 97
        Height = 17
        Caption = #1050#1086#1084#1084#1077#1085#1090#1072#1088#1080#1081
        Checked = True
        State = cbChecked
        TabOrder = 6
      end
      object B1Nazad: TButton
        Left = 8
        Top = 72
        Width = 153
        Height = 33
        Caption = #1053#1072#1079#1072#1076
        TabOrder = 7
        OnClick = B1NazadClick
      end
      object B1Sohr: TButton
        Left = 176
        Top = 72
        Width = 153
        Height = 33
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074'...'
        TabOrder = 8
        OnClick = B1SohrClick
      end
    end
  end
  object PanelVexcel21: TPanel
    Left = 327
    Top = 111
    Width = 353
    Height = 81
    Anchors = []
    Color = clBlue
    TabOrder = 9
    Visible = False
    object PanelVexcel22: TPanel
      Left = 8
      Top = 8
      Width = 337
      Height = 65
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label19: TLabel
        Left = 8
        Top = 3
        Width = 238
        Height = 15
        Caption = #1048#1084#1087#1086#1088#1090' '#1087#1086#1083#1103' '#1080#1089#1090#1086#1088#1080#1080' '#1087#1077#1088#1077#1084#1077#1097#1077#1085#1080#1081
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object B2Nazad: TButton
        Left = 8
        Top = 24
        Width = 153
        Height = 33
        Caption = #1053#1072#1079#1072#1076
        TabOrder = 0
        OnClick = B2NazadClick
      end
      object B2Sohr: TButton
        Left = 176
        Top = 24
        Width = 153
        Height = 33
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074'...'
        TabOrder = 1
        OnClick = B2SohrClick
      end
    end
  end
  object PanelSync1: TPanel
    Left = -1
    Top = 471
    Width = 838
    Height = 112
    Anchors = [akLeft, akRight, akBottom]
    Color = clRed
    TabOrder = 14
    Visible = False
    DesignSize = (
      838
      112)
    object PanelSync2: TPanel
      Left = 8
      Top = 8
      Width = 823
      Height = 97
      Anchors = [akLeft, akRight]
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      DesignSize = (
        823
        97)
      object LabelSync: TLabel
        Left = 8
        Top = 3
        Width = 520
        Height = 15
        Caption = 
          #1056#1077#1078#1080#1084' '#1088#1077#1076#1072#1082#1090#1080#1088#1086#1074#1072#1085#1080#1103' '#1085#1077#1076#1086#1089#1090#1091#1087#1077#1085'. '#1055#1086#1083#1100#1079#1086#1074#1072#1090#1077#1083#1100' "" '#1091#1078#1077' '#1088#1072#1073#1086#1090#1072#1077#1090' '#1089' ' +
          #1073#1072#1079#1086#1081':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object ListBoxSync: TListBox
        Left = 8
        Top = 16
        Width = 807
        Height = 73
        Anchors = [akLeft, akRight]
        ItemHeight = 15
        TabOrder = 1
      end
      object ButtonSync: TButton
        Left = 526
        Top = 56
        Width = 265
        Height = 33
        Anchors = [akTop, akRight]
        Caption = #1055#1077#1088#1077#1081#1090#1080' '#1074' '#1087#1086#1083#1085#1086#1092#1091#1085#1082#1094#1080#1086#1085#1072#1083#1100#1085#1099#1081' '#1088#1077#1078#1080#1084
        TabOrder = 0
        Visible = False
        OnClick = ButtonSyncClick
      end
    end
  end
  object PanelFiltr1: TPanel
    Left = 129
    Top = 90
    Width = 753
    Height = 281
    Anchors = []
    Color = clBlue
    TabOrder = 10
    Visible = False
    object PanelFiltr2: TPanel
      Left = 8
      Top = 8
      Width = 737
      Height = 265
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label20: TLabel
        Left = 8
        Top = 3
        Width = 78
        Height = 15
        Caption = #1048#1084#1103' '#1082#1085#1086#1087#1082#1080
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label21: TLabel
        Left = 136
        Top = 3
        Width = 114
        Height = 15
        Caption = #1050#1083#1102#1095#1077#1074#1072#1103' '#1092#1088#1072#1079#1072
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label22: TLabel
        Left = 8
        Top = 163
        Width = 193
        Height = 15
        Caption = #1042#1077#1089#1100' '#1089#1087#1080#1089#1086#1082' '#1082#1083#1102#1095#1077#1074#1099#1093' '#1089#1083#1086#1074
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object B3Nazad: TButton
        Left = 8
        Top = 224
        Width = 153
        Height = 33
        Caption = #1053#1072#1079#1072#1076
        TabOrder = 0
        OnClick = B3NazadClick
      end
      object B3Sohr: TButton
        Left = 576
        Top = 224
        Width = 153
        Height = 33
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        TabOrder = 1
        OnClick = B3SohrClick
      end
      object bf1: TEdit
        Left = 8
        Top = 16
        Width = 121
        Height = 23
        TabOrder = 2
      end
      object bf2: TEdit
        Left = 8
        Top = 40
        Width = 121
        Height = 23
        TabOrder = 3
      end
      object bf3: TEdit
        Left = 8
        Top = 64
        Width = 121
        Height = 23
        TabOrder = 4
      end
      object bf4: TEdit
        Left = 8
        Top = 88
        Width = 121
        Height = 23
        TabOrder = 5
      end
      object bf5: TEdit
        Left = 8
        Top = 112
        Width = 121
        Height = 23
        TabOrder = 6
      end
      object bf6: TEdit
        Left = 8
        Top = 136
        Width = 121
        Height = 23
        TabOrder = 7
      end
      object kf1: TEdit
        Left = 136
        Top = 16
        Width = 593
        Height = 23
        TabOrder = 8
      end
      object kf2: TEdit
        Left = 136
        Top = 40
        Width = 593
        Height = 23
        TabOrder = 9
      end
      object kf3: TEdit
        Left = 136
        Top = 64
        Width = 593
        Height = 23
        TabOrder = 10
      end
      object kf4: TEdit
        Left = 136
        Top = 88
        Width = 593
        Height = 23
        TabOrder = 11
      end
      object kf5: TEdit
        Left = 136
        Top = 112
        Width = 593
        Height = 23
        TabOrder = 12
      end
      object kf6: TEdit
        Left = 136
        Top = 136
        Width = 593
        Height = 23
        TabOrder = 13
      end
      object MemoSpisok: TMemo
        Left = 8
        Top = 176
        Width = 721
        Height = 41
        Ctl3D = False
        ParentCtl3D = False
        ReadOnly = True
        TabOrder = 14
      end
    end
  end
  object PanelRedaktor1: TPanel
    Left = 311
    Top = 93
    Width = 383
    Height = 273
    Anchors = []
    Color = clRed
    TabOrder = 13
    Visible = False
    object LabelRedaktor: TLabel
      Left = 1
      Top = 11
      Width = 381
      Height = 15
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object PanelRedaktor2: TPanel
      Left = 8
      Top = 40
      Width = 369
      Height = 225
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object B7Nazad: TButton
        Left = 8
        Top = 184
        Width = 153
        Height = 33
        Caption = #1053#1072#1079#1072#1076
        TabOrder = 1
        OnClick = B7NazadClick
      end
      object B7Dobav: TButton
        Left = 208
        Top = 184
        Width = 153
        Height = 33
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100
        TabOrder = 0
        OnClick = B7DobavClick
      end
      object MemoRedaktor: TMemo
        Left = 8
        Top = 8
        Width = 353
        Height = 169
        Ctl3D = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentCtl3D = False
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
    end
  end
  object PanelPeremestit1: TPanel
    Left = 325
    Top = 100
    Width = 353
    Height = 209
    Anchors = []
    Color = clBlue
    TabOrder = 11
    Visible = False
    object LabelPeremestit: TLabel
      Left = 1
      Top = 8
      Width = 349
      Height = 15
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object PanelPeremestit2: TPanel
      Left = 8
      Top = 32
      Width = 337
      Height = 169
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Reference Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      object Label23: TLabel
        Left = 8
        Top = 3
        Width = 257
        Height = 15
        Caption = #1044#1086#1073#1072#1074#1083#1077#1085#1080#1077' '#1082#1086#1084#1084#1077#1085#1090#1072#1088#1080#1103' ('#1085#1077#1086#1073#1103#1079#1072#1090#1077#1083#1100#1085#1086'):'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Reference Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object B4Nazad: TButton
        Left = 8
        Top = 128
        Width = 153
        Height = 33
        Caption = #1053#1072#1079#1072#1076
        TabOrder = 0
        OnClick = B4NazadClick
      end
      object B4Peremestit: TButton
        Left = 176
        Top = 128
        Width = 153
        Height = 33
        Caption = #1055#1077#1088#1077#1084#1077#1089#1090#1080#1090#1100
        TabOrder = 1
        OnClick = B4PeremestitClick
      end
      object MemoPeremestit: TMemo
        Left = 8
        Top = 24
        Width = 321
        Height = 97
        TabOrder = 2
      end
    end
  end
  object Timer1: TTimer
    Interval = 1
    OnTimer = Timer1Timer
    Top = 96
  end
  object SaveDialog1: TSaveDialog
    Filter = #1042#1089#1077' '#1092#1072#1081#1083#1099' (*.*)|*.*'
    Title = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1074'...'
    Top = 128
  end
end
