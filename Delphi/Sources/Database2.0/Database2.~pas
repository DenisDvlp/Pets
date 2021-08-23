unit Database2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, dbcgrids, Grids, ValEdit, ToolWin, ActnMan, ActnCtrls, ActnMenus,
  ExtCtrls, StdCtrls, ComCtrls;

type
  TForm1 = class(TForm)
    StringGridINV: TStringGrid;
    EditSEARCH: TEdit;
    ButtonSEARCH: TButton;
    PanelSEARCH: TPanel;
    CheckBox1: TCheckBox;
    CheckBox2: TCheckBox;
    CheckBox3: TCheckBox;
    CheckBox4: TCheckBox;
    CheckBox5: TCheckBox;
    CheckBox6: TCheckBox;
    CheckBox7: TCheckBox;
    Label1: TLabel;
    PanelINV: TPanel;
    EditNUMBER: TEdit;
    EditMODEL: TEdit;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    MemoCOMMENT1: TMemo;
    ComboBoxTYPE: TComboBox;
    ComboBoxKOD: TComboBox;
    Izmen1: TButton;
    Udal1: TButton;
    LabelDIVISION: TLabel;
    filtr1: TButton;
    PanelMENU: TPanel;
    filtr2: TButton;
    filtr3: TButton;
    ComboBoxTOBO1: TComboBox;
    filtr4: TButton;
    filtr5: TButton;
    filtr6: TButton;
    Label10: TLabel;
    GroupBox1: TGroupBox;
    GroupBox2: TGroupBox;
    Label7: TLabel;
    ComboBoxKUDA1: TComboBox;
    Move2: TButton;
    Move1: TButton;
    DateTimePicker1: TDateTimePicker;
    Label8: TLabel;
    GroupBox5: TGroupBox;
    Label13: TLabel;
    Label14: TLabel;
    History2: TButton;
    History1: TButton;
    DateTimePicker2: TDateTimePicker;
    DateTimePicker3: TDateTimePicker;
    Label17: TLabel;
    StringGridHISTORY: TStringGrid;
    VEXCEL: TButton;
    UpDown1: TUpDown;
    PanelKOD: TPanel;
    Label11: TLabel;
    Label15: TLabel;
    EditKOD: TEdit;
    EditDIVISION: TEdit;
    Izmen2: TButton;
    Udal2: TButton;
    ComboBoxTOBO2: TComboBox;
    Label9: TLabel;
    PanelTOBO: TPanel;
    Label12: TLabel;
    Label16: TLabel;
    EditTOBO: TEdit;
    MemoCOMMENT2: TMemo;
    Izmen3: TButton;
    Udal3: TButton;
    Timer1: TTimer;
    redak: TButton;
    PanelVexcel11: TPanel;
    PanelVexcel12: TPanel;
    Label18: TLabel;
    CB11: TCheckBox;
    CB12: TCheckBox;
    CB13: TCheckBox;
    CB14: TCheckBox;
    CB15: TCheckBox;
    CB16: TCheckBox;
    CB17: TCheckBox;
    B1Nazad: TButton;
    B1Sohr: TButton;
    PanelVexcel21: TPanel;
    PanelVexcel22: TPanel;
    Label19: TLabel;
    B2Nazad: TButton;
    B2Sohr: TButton;
    PanelFiltr1: TPanel;
    PanelFiltr2: TPanel;
    Label20: TLabel;
    B3Nazad: TButton;
    B3Sohr: TButton;
    Label21: TLabel;
    bf1: TEdit;
    bf2: TEdit;
    bf3: TEdit;
    bf4: TEdit;
    bf5: TEdit;
    bf6: TEdit;
    kf1: TEdit;
    kf2: TEdit;
    kf3: TEdit;
    kf4: TEdit;
    kf5: TEdit;
    kf6: TEdit;
    MemoSpisok: TMemo;
    Label22: TLabel;
    PanelPeremestit1: TPanel;
    PanelPeremestit2: TPanel;
    Label23: TLabel;
    B4Nazad: TButton;
    B4Peremestit: TButton;
    MemoPeremestit: TMemo;
    SaveDialog1: TSaveDialog;
    M: TMemo;
    PanelRedaktor1: TPanel;
    PanelRedaktor2: TPanel;
    LabelRedaktor: TLabel;
    B7Nazad: TButton;
    B7Dobav: TButton;
    MemoRedaktor: TMemo;
    LabelPeremestit: TLabel;
    PanelSync1: TPanel;
    PanelSync2: TPanel;
    LabelSync: TLabel;
    ButtonSync: TButton;
    ListBoxSync: TListBox;
    bprev: TButton;
    bnext: TButton;
    Dobav1: TButton;
    Dobav2: TButton;
    Dobav3: TButton;
    Panel1: TPanel;
    Panel2: TPanel;
    procedure FormCreate(Sender: TObject);
    procedure UpDown1ChangingEx(Sender: TObject; var AllowChange: Boolean;
      NewValue: Smallint; Direction: TUpDownDirection);
    procedure Timer1Timer(Sender: TObject);
    procedure VEXCELClick(Sender: TObject);
    procedure B1NazadClick(Sender: TObject);
    procedure B1SohrClick(Sender: TObject);
    procedure B2NazadClick(Sender: TObject);
    procedure B2SohrClick(Sender: TObject);
    procedure Move1Click(Sender: TObject);
    procedure Move2Click(Sender: TObject);
    procedure B4NazadClick(Sender: TObject);
    procedure B4PeremestitClick(Sender: TObject);
    procedure redakClick(Sender: TObject);
    procedure B3NazadClick(Sender: TObject);
    procedure B3SohrClick(Sender: TObject);
    procedure ButtonSEARCHClick(Sender: TObject);
    procedure EditSEARCHKeyPress(Sender: TObject; var Key: Char);
    procedure ComboBoxKUDA1Change(Sender: TObject);
    procedure EditNUMBERChange(Sender: TObject);
    procedure EditKODChange(Sender: TObject);
    procedure EditTOBOChange(Sender: TObject);
    procedure Izmen1Click(Sender: TObject);
    procedure B7DobavClick(Sender: TObject);
    procedure B7NazadClick(Sender: TObject);
    procedure Izmen2Click(Sender: TObject);
    procedure Izmen3Click(Sender: TObject);
    procedure Udal1Click(Sender: TObject);
    procedure Udal2Click(Sender: TObject);
    procedure Udal3Click(Sender: TObject);
    procedure StringGridINVSelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure ComboBoxTOBO1Change(Sender: TObject);
    procedure filtr1Click(Sender: TObject);
    procedure filtr2Click(Sender: TObject);
    procedure filtr3Click(Sender: TObject);
    procedure filtr4Click(Sender: TObject);
    procedure filtr5Click(Sender: TObject);
    procedure filtr6Click(Sender: TObject);
    procedure History1Click(Sender: TObject);
    procedure StringGridHISTORYSelectCell(Sender: TObject; ACol,
      ARow: Integer; var CanSelect: Boolean);
    procedure History2Click(Sender: TObject);
    procedure FormDestroy(Sender: TObject);
    procedure ButtonSyncClick(Sender: TObject);
    procedure bprevClick(Sender: TObject);
    procedure bnextClick(Sender: TObject);
    procedure Dobav2Click(Sender: TObject);
    procedure Dobav3Click(Sender: TObject);
    procedure Dobav1Click(Sender: TObject);
    procedure ComboBoxKODChange(Sender: TObject);
    procedure Panel1Click(Sender: TObject);
    procedure Panel2Click(Sender: TObject);
    procedure EditMODELChange(Sender: TObject);
    procedure ComboBoxTYPEChange(Sender: TObject);
    procedure MemoCOMMENT1Change(Sender: TObject);
    procedure EditDIVISIONChange(Sender: TObject);
    procedure ComboBoxTOBO2Change(Sender: TObject);
    procedure MemoCOMMENT2Change(Sender: TObject); 
    procedure SGMouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure SGMouseDown(Sender: TObject;
      Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
const
       N = 5000; //должно быть не меньше 1
       N2 = 200;//должно быть не меньше 2.
  color1 = $FFE4C1;
  colorred = $A8A8FF;
  coloryellow = $FFFFA8;
  colorgreen = $A8FFA8;

var
  Form1: TForm1;
  bl1, bl2, bl3, bl4, blSync: boolean;
  invspisan: array [1..N] of boolean;
  invinv,invtype,invmodel,invkod,invdivision,invtobo,invcomment,invmovement,invtoboadres: array [1..N] of string;
  movementinv,movementmovement: array [1..N] of string;
  commentinv,commentcomment: array [1..N] of string;
  kodkod,koddivision,kodtobo: array [1..N2] of string;
  infonumber,infoadres: array [1..N2] of string;
  models: array [1..N] of string;
  types,searchstring: array [1..N2] of string;
  chooseninv, choosenkod, choosentobo, choosenkuda, syncname, username, pathapp: string;
  choosenpanel, currentsearch, Lastinvnumber,posx,posy: integer;
implementation

uses Math;

{$R *.dfm}
/////////////имя компьютера//////////
Function GetUserFromWindows: string;
Var 
  UserName    : string; 
  UserNameLen : Dword;
Begin 
  UserNameLen := 255; 
  SetLength(userName, UserNameLen);
  If GetUserName(PChar(UserName), UserNameLen) Then
    Result := Copy(UserName,1,UserNameLen - 1)
  Else
    Result := 'unnamed';
End;

//ПРОВЕРКА НА НЕПУСТОЕ ПОЛЕ //
function IsNotEmpty(s: string):boolean;
var i,len: integer;
    bl: boolean;
begin
    len:=length(s);
    bl:=false;
    for i:=1 to len do
    begin
      if s[i]<>' ' then bl:=true;
    end;
    result:=bl;
end;

//ПРОВЕРКА НА КОРРЕКТНО ВВЕДЁННОЕ ТОБО //
function checktobo():boolean;
var i: integer;
    bl: boolean;
begin
    i:=1;
    bl:=false;
    while infonumber[i]<>'' do
    begin
      if infonumber[i]=form1.ComboBoxTOBO1.text then bl:=true;
      i:=i+1;
    end;
    result:=bl;
end;

//ОБНОВЛЕНИЕ ИНФОРМАЦИИ В ТАБЛИЦАХ//
procedure RefreshTables();
var i,j, index, numofstringgridinv, numofstringgridhistory: integer;
    s: string;
begin
  with form1 do
  begin
    numofstringgridinv:=StringGridINV.RowCount-1;
    numofstringgridhistory:=StringGridHISTORY.RowCount-1;

    for i:=1 to numofstringgridinv do
      if StringGridINV.Cells[8,i]<>'' then
      begin
        index:=strtoint(StringGridINV.Cells[8,i]);
        StringGridINV.Cells[1,i]:=invinv[index];
        StringGridINV.Cells[2,i]:=invtype[index];
        StringGridINV.Cells[3,i]:=invmodel[index];
        StringGridINV.Cells[4,i]:=invtobo[index];
        StringGridINV.Cells[5,i]:=invkod[index];
        StringGridINV.Cells[6,i]:=invdivision[index];
        StringGridINV.Cells[7,i]:=invcomment[index];
      end else
      begin
          StringGridINV.Cells[1,i]:='';
          StringGridINV.Cells[2,i]:='';
          StringGridINV.Cells[3,i]:='';
          StringGridINV.Cells[4,i]:='';
          StringGridINV.Cells[5,i]:='';
          StringGridINV.Cells[6,i]:='';
          StringGridINV.Cells[7,i]:='';
      end;

    for i:=1 to numofstringgridhistory do
    begin
        StringGridHISTORY.Cells[1,i]:='';
        StringGridHISTORY.Cells[2,i]:='';
        StringGridHISTORY.Cells[3,i]:='';
        StringGridHISTORY.Cells[4,i]:='';
        StringGridHISTORY.Cells[5,i]:='';
        StringGridHISTORY.Cells[6,i]:='';
    end;
  end;  //end with
end;

//ДАННЫЕ НА ПАНЕЛЬ ДОБАВЛЕНИЯ/ИЗМЕНЕНИЯ/УДАЛЕНИЯ //
procedure DataToPanel(buttonname: string);
var i: integer;
    captioninv, captionkod,captiontobo: string;
    bl: boolean;
begin
  with form1 do begin //with form1

  b7dobav.Caption:=buttonname;
  PanelRedaktor1.Visible:=true;

  if buttonname='Добавить' then begin PanelRedaktor1.Color:=clgreen; LabelRedaktor.Caption:='Добавление нового '; end;
  if buttonname='Изменить' then begin PanelRedaktor1.Color:=clblue; LabelRedaktor.Caption:='Изменение '; end;
  if buttonname='Удалить'  then begin PanelRedaktor1.Color:=clred; LabelRedaktor.Caption:='Удаление '; end;
  MemoRedaktor.Text:='';

  case choosenpanel of
  1:begin
      if buttonname='Добавить' then captioninv:=EditNUMBER.Text else captioninv:=invinv[strtoint(chooseninv)];
      LabelRedaktor.Caption:=LabelRedaktor.Caption+'инвентарного номера '+captioninv;
      bl:=false;
      i:=1;
      while kodkod[i]<>'' do
      begin
        if (kodkod[i]+' '+koddivision[i]=ComboBoxKOD.Text)or(kodkod[i]=ComboBoxKOD.Text) then begin bl:=true; break; end;
        i:=i+1;
      end;
      MemoRedaktor.Lines.Add('Инв. №:'+#9+#9+EditNUMBER.Text);
      MemoRedaktor.Lines.Add('Тип:'+#9+#9+ComboBoxTYPE.Text);
      MemoRedaktor.Lines.Add('Модель:'+#9+#9+EditMODEL.Text);
      if bl then
      begin
        MemoRedaktor.Lines.Add('Код:'+#9+#9+kodkod[i]);
        MemoRedaktor.Lines.Add('Подразделение:'+#9+koddivision[i]);
        MemoRedaktor.Lines.Add('Тобо:'+#9+#9+kodtobo[i]);
      end else
      begin
        MemoRedaktor.Lines.Add('Код:'+#9+#9+ComboBoxKOD.Text);
        MemoRedaktor.Lines.Add('Подразделение:'+#9);
        MemoRedaktor.Lines.Add('Тобо:'+#9+#9);
      end;
      MemoRedaktor.Lines.Add('Комментарий:'+#9+MemoCOMMENT1.Text);
    end;
  2:begin
      if buttonname='Добавить' then captionkod:=EditKOD.Text else captionkod:=choosenkod;
      LabelRedaktor.Caption:=LabelRedaktor.Caption+'кода подразделения '+captionkod;
      MemoRedaktor.Lines.Add('Код:'+#9+#9+EditKOD.Text);
      MemoRedaktor.Lines.Add('Подразделение:'+#9+EditDIVISION.Text);
      MemoRedaktor.Lines.Add('ТОБО:'+#9+#9+ComboBoxTOBO2.Text);
    end;
  3:begin
      if buttonname='Добавить' then captiontobo:=EditTOBO.Text else captiontobo:=choosentobo;
      LabelRedaktor.Caption:=LabelRedaktor.Caption+'номера филиала '+captiontobo;
      MemoRedaktor.Lines.Add('ТОБО:'+#9+#9+EditTOBO.Text);
      MemoRedaktor.Lines.Add('Комментарий:'+#9+MemoCOMMENT2.Text);
    end;
  end;

  end;//with form1
end;
//ПРОВЕРКА НА ДОПУСТИМОСТЬ ДОБАВЛЕНИЯ/ИЗМЕНЕНИЯ//
procedure IfAllowAdding();
var i: integer;
    bl,bl1: boolean;
begin
  with form1 do
  begin
      bl:=false;                           //1 панель
      for i:=1 to Lastinvnumber do
      if EditNUMBER.Text=invinv[i] then
      begin
        bl:=true;
        break;
      end;
  if IsNotEmpty(EditNUMBER.Text) then
    begin
      Izmen1.Enabled:=false;
      if bl then
      begin
        Dobav1.Visible:=false;
        if chooseninv<>'' then
        begin
          Udal1.Visible:=true;
          if invinv[strtoint(chooseninv)]=EditNUMBER.Text then
          begin
            EditNUMBER.Color:=colorgreen;
            Izmen1.Visible:=true;
          end else
          begin
            EditNUMBER.Color:=coloryellow;
            Izmen1.Visible:=false;
          end;
        end else
        begin
          EditNUMBER.Color:=coloryellow;
          Izmen1.Visible:=false;
          Udal1.Visible:=false;
        end;
      end else
      begin
        EditNUMBER.Color:=colorgreen;
        Dobav1.Visible:=true;
        if chooseninv<>'' then
        begin
          Izmen1.Visible:=true;
          Udal1.Visible:=true;
        end else
        begin
          Izmen1.Visible:=false;
          Udal1.Visible:=false;
        end;
      end;
    end else
    begin
      EditNUMBER.Color:=colorred;
      Dobav1.Visible:=false;
      Izmen1.Visible:=false;
      if chooseninv<>'' then
        Udal1.Visible:=true
      else
        Udal1.Visible:=false;
    end;
      bl:=false;                             //2 панель
      bl1:=false;
      i:=1;
      while kodkod[i]<>'' do
      begin
        if choosenkod=kodkod[i] then bl1:=true;
        if EditKOD.Text=kodkod[i] then bl:=true;
        i:=i+1;
      end;
  if IsNotEmpty(EditKOD.Text) then
    begin
      Izmen2.Enabled:=false;
      if bl then
      begin
        Dobav2.Visible:=false;
        if choosenkod<>'' then
        begin
          if bl1 then Udal2.Visible:=true else Udal2.Visible:=false;
          if choosenkod=EditKOD.Text then
          begin
            EditKOD.Color:=colorgreen;
            if bl1 then Izmen2.Visible:=true else Izmen2.Visible:=false;
          end else
          begin
            EditKOD.Color:=coloryellow;
            Izmen2.Visible:=false;
          end;
        end else
        begin
          EditKOD.Color:=coloryellow;
          Izmen2.Visible:=false;
          Udal2.Visible:=false;
        end;
      end else
      begin
        EditKOD.Color:=colorgreen;
        if EditKOD.Text<>'Списан' then Dobav2.Visible:=true else Dobav2.Visible:=false; 
        if choosenkod<>'' then
        begin
          if bl1 then Izmen2.Visible:=true else Izmen2.Visible:=false;
          if bl1 then Udal2.Visible:=true else Udal2.Visible:=false;
        end else
        begin
          Izmen2.Visible:=false;
          Udal2.Visible:=false;
        end;
      end;
    end else
    begin
      EditKOD.Color:=colorred;
      Dobav2.Visible:=false;
      Izmen2.Visible:=false;
      if choosenkod<>'' then
      begin if bl1 then Udal2.Visible:=true else Udal2.Visible:=false end
      else
      begin Udal2.Visible:=false; end;
    end;

      bl:=false;                          //3 панель
      bl1:=false;
      i:=1;
      while infonumber[i]<>'' do
      begin
        if choosentobo=infonumber[i] then bl1:=true;
        if EditTOBO.Text=infonumber[i] then bl:=true;
        i:=i+1;
      end;
    if IsNotEmpty(EditTOBO.Text) then
    begin
      Izmen3.Enabled:=false;
      if bl then
      begin
        Dobav3.Visible:=false;
        if choosentobo<>'' then
        begin
          if bl1 then Udal3.Visible:=true else Udal3.Visible:=false;
          if choosentobo=EditTOBO.Text then
          begin
            EditTOBO.Color:=colorgreen;
            if bl1 then Izmen3.Visible:=true else Izmen3.Visible:=false;
          end else
          begin
            EditTOBO.Color:=coloryellow;
            Izmen3.Visible:=false;
          end;
        end else
        begin
          EditTOBO.Color:=coloryellow;
          Izmen3.Visible:=false;
          Udal3.Visible:=false;
        end;
      end else
      begin
        EditTOBO.Color:=colorgreen;
        Dobav3.Visible:=true;
        if choosentobo<>'' then
        begin
          if bl1 then Izmen3.Visible:=true else Izmen3.Visible:=false;
          if bl1 then Udal3.Visible:=true else Udal3.Visible:=false;
        end else
        begin
          Izmen3.Visible:=false;
          Udal3.Visible:=false;
        end;
      end;
    end else
    begin
      EditTOBO.Color:=colorred;
      Dobav3.Visible:=false;
      Izmen3.Visible:=false;
      if choosentobo<>'' then
        if bl1 then Udal3.Visible:=true else Udal3.Visible:=false
      else
        Udal3.Visible:=false;
    end;
  end;
end;

//ВЫБОР ИНВЕНТАРНОГО НОМЕРА ИЗ ТАБЛИЦЫ//
procedure InvFromTable(num: string);
var i:integer;
begin
  with form1 do
  if num<>'' then
  begin
    i:=strtoint(num);
    chooseninv:=num;
    if invspisan[i] then
    begin
      choosenkod:='';
      choosentobo:='';
      move1.Enabled:=false;
      move2.Enabled:=false;
    end else
    begin
      choosenkod:= invkod[i];
      choosentobo:=invtobo[i];
      if (choosenkuda<>'')and(invkod[i]<>choosenkuda) then move1.Enabled:=true else move1.Enabled:=false;
      move2.Enabled:=true;
    end;
    if invmovement[i]<>'' then History2.Enabled:=true else History2.Enabled:=false;
    
    EditNUMBER.Text:=invinv[i];
    EditMODEL.Text:=invmodel[i];
    ComboBoxTYPE.Text:=invtype[i];
    MemoCOMMENT1.Text:=invcomment[i];
    if invspisan[i] then
    begin
      ComboBoxKOD.Text:='Списан';
      LabelDIVISION.Caption:='';
      EditKOD.Text:='';
      EditDIVISION.Text:='';
      ComboBoxTOBO2.Text:='';
      EditTOBO.Text:='';
      MemoCOMMENT2.Text:='';
    end else
    begin
      ComboBoxKOD.Text:=invkod[i]+' '+invdivision[i];
      LabelDIVISION.Caption:=invdivision[i];
      EditKOD.Text:=invkod[i];
      EditDIVISION.Text:=invdivision[i];
      ComboBoxTOBO2.Text:=invtobo[i];
      EditTOBO.Text:=invtobo[i];
      MemoCOMMENT2.Text:=invtoboadres[i];
    end;
  end else
  begin
    chooseninv:='';
    choosenkod:='';
    choosentobo:='';
    move1.Enabled:=false;
    move2.Enabled:=false;
    History2.Enabled:=false;

    EditNUMBER.Text:='';
    EditMODEL.Text:='';
    ComboBoxTYPE.Text:='';
    ComboBoxKOD.Text:='';
    LabelDIVISION.Caption:='';
    MemoCOMMENT1.Text:='';
    EditKOD.Text:='';
    EditDIVISION.Text:='';
    ComboBoxTOBO2.Text:='';
    EditTOBO.Text:='';
    MemoCOMMENT2.Text:='';
  end;
  IfAllowAdding();
end;

{////////////приведение к нижнему регистру////////////}
function LowString(s: string): string ;
var i,len: integer;
begin
    len:=length(s);
    for i:=1 to len do
    begin
      case s[i] of
      'А':s[i]:='а';
      'Б':s[i]:='б';
      'В':s[i]:='в';
      'Г':s[i]:='г';
      'Д':s[i]:='д';
      'Е':s[i]:='е';
      'Ё':s[i]:='ё';
      'Ж':s[i]:='ж';
      'З':s[i]:='з';
      'И':s[i]:='и';
      'Й':s[i]:='й';
      'К':s[i]:='к';
      'Л':s[i]:='л';
      'М':s[i]:='м';
      'Н':s[i]:='н';
      'О':s[i]:='о';
      'П':s[i]:='п';
      'Р':s[i]:='р';
      'С':s[i]:='с';
      'Т':s[i]:='т';
      'У':s[i]:='у';
      'Ф':s[i]:='ф';
      'Х':s[i]:='х';
      'Ц':s[i]:='ц';
      'Ч':s[i]:='ч';
      'Ш':s[i]:='ш';
      'Щ':s[i]:='щ';
      'Ъ':s[i]:='ъ';
      'Ы':s[i]:='ы';
      'Ь':s[i]:='ь';
      'Э':s[i]:='э';
      'Ю':s[i]:='ю';
      'Я':s[i]:='я';

      'A':s[i]:='a';
      'B':s[i]:='b';
      'C':s[i]:='c';
      'D':s[i]:='d';
      'E':s[i]:='e';
      'F':s[i]:='f';
      'G':s[i]:='g';
      'H':s[i]:='h';
      'I':s[i]:='i';
      'J':s[i]:='j';
      'K':s[i]:='k';
      'L':s[i]:='l';
      'M':s[i]:='m';
      'N':s[i]:='n';
      'O':s[i]:='o';
      'P':s[i]:='p';
      'Q':s[i]:='q';
      'R':s[i]:='r';
      'S':s[i]:='s';
      'T':s[i]:='t';
      'U':s[i]:='u';
      'V':s[i]:='v';
      'W':s[i]:='w';
      'X':s[i]:='x';
      'Y':s[i]:='y';
      'Z':s[i]:='z'; end;
    end;
    result:=s;
end;

{////////////поиск по ключевым словам (c)////////////}
procedure search(s: string; blfiltr,bl1,bl2,bl3,bl4,bl5,bl6,bl7: boolean);
var i,j,max,max1,max2,count: integer;
    searchindex: array [1..N] of integer;
    bl: boolean;
    keys: array [1..N2] of string;
begin
  with form1 do begin
    StringGridINV.Visible:=true;
    StringGridHISTORY.Visible:=false;
    panel1.BorderStyle:=bsSingle;
    panel2.BorderStyle:=bsNone;

    StringGridINV.RowCount:=2;
    for i:=0 to 8 do StringGridINV.Cells[i,1]:='';
    if s<>'' then //begin if s<>''
    begin
      //инициализация
      bl:=true;
      max:=0;
      max1:=0;
      max2:=0;
      count:=1;
      s:=LowString(s);
      //определение ключевых фраз
      for i:=1 to length(s) do
      begin
        if (s[i]=' ')or(s[i]=',') then
        begin
          if bl then
          begin
            count:=count+1;
            bl:=false;
          end;
        end else bl:=true;
        if bl then keys[count]:= keys[count] + s[i];
      end;
    //индексация
    for i:=1 to Lastinvnumber do
    for j:=1 to count do
    begin
      //поиск совпадений
      if bl1 and (strpos(pchar(LowString(invinv[i])),pchar(keys[j]))<>nil) then
      searchindex[i]:=searchindex[i]+1;
      if blfiltr then
      begin
        if bl2 and (LowString(invtype[i])=keys[j]) then
        searchindex[i]:=searchindex[i]+1;
      end else begin
        if bl2 and (strpos(pchar(LowString(invtype[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
      end;
      if bl3 and (strpos(pchar(LowString(invmodel[i])),pchar(keys[j]))<>nil) then
      searchindex[i]:=searchindex[i]+1;
      if bl4 and (strpos(pchar(LowString(invtobo[i])),pchar(keys[j]))<>nil) then
      searchindex[i]:=searchindex[i]+1;
      if bl5 and (LowString(invkod[i])=keys[j]) then
      searchindex[i]:=searchindex[i]+1;
      if bl6 and (strpos(pchar(LowString(invdivision[i])),pchar(keys[j]))<>nil) then
      searchindex[i]:=searchindex[i]+1;
      if bl7 and (strpos(pchar(LowString(invcomment[i])),pchar(keys[j]))<>nil) then
      searchindex[i]:=searchindex[i]+1;
      //определение максимальных индексов
      if searchindex[i]>=max then max:=searchindex[i] else
      if blfiltr=false then
      if searchindex[i]>=max1 then max1:=searchindex[i] else
      if searchindex[i]>=max2 then max2:=searchindex[i];
    end;

  //вывод в таблицу
  if ((max<>0)and(blfiltr=false))or((bl2)and(bl4=false)and(blfiltr)and(max<>0))or((blfiltr)and(max>1)and(bl4)and(bl2))or((bl2=false)and(bl4)and(blfiltr)and(max<>0)) then
  begin
    for i:=1 to Lastinvnumber do
    if searchindex[i]=max then
      begin
        StringGridINV.Cells[0,StringGridINV.RowCount-1]:=inttostr(StringGridINV.RowCount-1);
        StringGridINV.Cells[1,StringGridINV.RowCount-1]:=invinv[i];
        StringGridINV.Cells[2,StringGridINV.RowCount-1]:=invtype[i];
        StringGridINV.Cells[3,StringGridINV.RowCount-1]:=invmodel[i];
        StringGridINV.Cells[4,StringGridINV.RowCount-1]:=invtobo[i];
        StringGridINV.Cells[5,StringGridINV.RowCount-1]:=invkod[i];
        StringGridINV.Cells[6,StringGridINV.RowCount-1]:=invdivision[i];
        StringGridINV.Cells[7,StringGridINV.RowCount-1]:=invcomment[i];
        StringGridINV.Cells[8,StringGridINV.RowCount-1]:=inttostr(i);
        StringGridINV.RowCount:=StringGridINV.RowCount+1;
      end;
    for i:=0 to 8 do StringGridINV.Cells[i,StringGridINV.RowCount-1]:='';
  if blfiltr=false then
  begin
    if max1<>0 then
    begin
      StringGridINV.RowCount:=StringGridINV.RowCount+1;
      for i:=1 to Lastinvnumber do
        if searchindex[i]=max1 then
        begin
          StringGridINV.Cells[0,StringGridINV.RowCount-1]:=inttostr(StringGridINV.RowCount-2);
          StringGridINV.Cells[1,StringGridINV.RowCount-1]:=invinv[i];
          StringGridINV.Cells[2,StringGridINV.RowCount-1]:=invtype[i];
          StringGridINV.Cells[3,StringGridINV.RowCount-1]:=invmodel[i];
          StringGridINV.Cells[4,StringGridINV.RowCount-1]:=invtobo[i];
          StringGridINV.Cells[5,StringGridINV.RowCount-1]:=invkod[i];
          StringGridINV.Cells[6,StringGridINV.RowCount-1]:=invdivision[i];
          StringGridINV.Cells[7,StringGridINV.RowCount-1]:=invcomment[i]; 
          StringGridINV.Cells[8,StringGridINV.RowCount-1]:=inttostr(i);
          StringGridINV.RowCount:=StringGridINV.RowCount+1;
        end;
      for i:=0 to 8 do StringGridINV.Cells[i,StringGridINV.RowCount-1]:='';
      if max2<>0 then
      begin
        StringGridINV.RowCount:=StringGridINV.RowCount+1;
        for i:=1 to Lastinvnumber do
          if searchindex[i]=max2 then
          begin
            StringGridINV.Cells[0,StringGridINV.RowCount-1]:=inttostr(StringGridINV.RowCount-3);
            StringGridINV.Cells[1,StringGridINV.RowCount-1]:=invinv[i];
            StringGridINV.Cells[2,StringGridINV.RowCount-1]:=invtype[i];
            StringGridINV.Cells[3,StringGridINV.RowCount-1]:=invmodel[i];
            StringGridINV.Cells[4,StringGridINV.RowCount-1]:=invtobo[i];
            StringGridINV.Cells[5,StringGridINV.RowCount-1]:=invkod[i];
            StringGridINV.Cells[6,StringGridINV.RowCount-1]:=invdivision[i];
            StringGridINV.Cells[7,StringGridINV.RowCount-1]:=invcomment[i]; 
            StringGridINV.Cells[8,StringGridINV.RowCount-1]:=inttostr(i);
            StringGridINV.RowCount:=StringGridINV.RowCount+1;
          end;
        for i:=0 to 8 do StringGridINV.Cells[i,StringGridINV.RowCount-1]:='';
      end;
    end;//end if max1<>0
  end;//end if blfiltr=false
  end;//end if max<>0
  end; //end if s<>''
  end; // end with form1 do
  chooseninv:=form1.StringGridINV.Cells[8,1];
  if (blSync=false) then InvFromTable(chooseninv);
end;
{////////////сортировка инвентарных номеров////////////}
procedure SortInv();
var bl,tempbl: boolean;
    i: integer;
    p: string;
begin
  //сортируем инвентарные номера по возрастанию
  bl:=true;
  while bl do
  begin
    bl:=false;
    for i:=1 to Lastinvnumber-1 do
      if invinv[i]>invinv[i+1] then
      begin
        bl:=true;
        p:=invinv[i];invinv[i]:=invinv[i+1];invinv[i+1]:=p;
        p:=invtype[i];invtype[i]:=invtype[i+1];invtype[i+1]:=p;
        p:=invmodel[i];invmodel[i]:=invmodel[i+1];invmodel[i+1]:=p;
        p:=invkod[i];invkod[i]:=invkod[i+1];invkod[i+1]:=p;
        p:=invdivision[i];invdivision[i]:=invdivision[i+1];invdivision[i+1]:=p;
        p:=invtobo[i];invtobo[i]:=invtobo[i+1];invtobo[i+1]:=p;
        p:=invcomment[i];invcomment[i]:=invcomment[i+1];invcomment[i+1]:=p;
        p:=invmovement[i];invmovement[i]:=invmovement[i+1];invmovement[i+1]:=p;
        p:=invtoboadres[i];invtoboadres[i]:=invtoboadres[i+1];invtoboadres[i+1]:=p;
        tempbl:=invspisan[i];invspisan[i]:=invspisan[i+1];invspisan[i+1]:=tempbl;
      end;
  end;
end;
{////////////сортировка типов////////////}
procedure SortType();
var bl: boolean;
    i,j: integer;
    p: string;
begin
  //находим все уникальные типы техники
  for i:=1 to N2 do types[i]:='';
  form1.M.Text:='';
  j:=1;
  for i:=1 to Lastinvnumber do
    if (invtype[i]<>'')and(strpos(pchar(form1.M.Text),pchar(invtype[i]+'#'))=nil) then
    begin
      types[j]:=invtype[i];
      j:=j+1;
      form1.M.Text:=form1.M.Text+invtype[i]+'#';
    end;
  //сортируем типы по возрастанию
  bl:=true;
  while bl do
  begin
    i:=1;
    bl:=false;
    while types[i+1]<>'' do
    begin
      if types[i]>types[i+1] then
      begin
        bl:=true;
        p:=types[i];types[i]:=types[i+1];types[i+1]:=p;
      end;
      i:=i+1;
    end;
  end;
  // заполняем комбобоксы
  i:=1;
  form1.ComboBoxTYPE.Items.Clear;
  while types[i]<>'' do
  begin
    form1.ComboBoxTYPE.Items.Add(types[i]);
    i:=i+1;
  end;
  form1.MemoSpisok.text:=form1.ComboBoxTYPE.Items.CommaText;
  form1.ComboBoxTYPE.DropDownCount:=34;
end;
{////////////сортировка ТОБО////////////}
procedure SortTOBO();
var bl: boolean;
    i: integer;
    p: string;
begin
  //сортируем ТОБО по возрастанию
  bl:=true;
  while bl do
  begin
    i:=1;
    bl:=false;
    while infonumber[i+1]<>'' do
    begin
      if infonumber[i]>infonumber[i+1] then
      begin
        bl:=true;
        p:=infonumber[i];infonumber[i]:=infonumber[i+1];infonumber[i+1]:=p;
        p:=infoadres[i];infoadres[i]:=infoadres[i+1];infoadres[i+1]:=p;
      end;
      i:=i+1;
    end;
  end;
  //заполняем комбобоксы
  form1.ComboBoxTOBO1.Items.Clear;
  form1.ComboBoxTOBO2.Items.Clear;
  form1.ComboBoxTOBO1.Items.Add('ВСЕ');
  i:=1;
  while infonumber[i]<>'' do
  begin
    form1.ComboBoxTOBO1.Items.Add(infonumber[i]);
    form1.ComboBoxTOBO2.Items.Add(infonumber[i]);
    i:=i+1;
  end;
  form1.ComboBoxTOBO1.DropDownCount:=23;
  form1.ComboBoxTOBO2.DropDownCount:=34;
end;
{////////////сортировка кодов подразделений////////////}
procedure SortKod();
var bl: boolean;
    i: integer;
    p: string;
begin
  //сортируем коды подразделений по возрастанию
  bl:=true;
  while bl do
  begin
    i:=1;
    bl:=false;
    while kodkod[i+1]<>'' do
    begin
      if kodkod[i]>kodkod[i+1] then
      begin
        bl:=true;
        p:=kodkod[i];kodkod[i]:=kodkod[i+1];kodkod[i+1]:=p;
        p:=koddivision[i];koddivision[i]:=koddivision[i+1];koddivision[i+1]:=p;
        p:=kodtobo[i];kodtobo[i]:=kodtobo[i+1];kodtobo[i+1]:=p;
      end;
      i:=i+1;
    end;
  end;                                                    
  //заполняем комбобоксы и лейблы
    i:=1;
    form1.ComboBoxKOD.Items.Clear;
    form1.ComboBoxKUDA1.Items.Clear;
    choosenkuda:=kodkod[i];
    form1.Label17.Caption:=koddivision[i];
    form1.LabelDIVISION.Caption:=koddivision[i];
    while kodkod[i]<>'' do
    begin
      form1.ComboBoxKOD.Items.Add(kodkod[i]+' '+koddivision[i]);
      form1.ComboBoxKUDA1.Items.Add(kodkod[i]+' '+koddivision[i]);
      i:=i+1;
    end;
    form1.ComboBoxKOD.DropDownCount:=30;
    form1.ComboBoxKUDA1.DropDownCount:=30;
end;
{////////////заполнить подразделения инвентарников////////////}
procedure FillCommentMovementDivisionToboadres(bl1,bl2,bl3,bl4: boolean);
var i,j: integer;
begin
    for i:=1 to Lastinvnumber do
    begin
      if bl1 then
      begin
        j:=1;
        while commentinv[j]<>'' do
        begin
          if invinv[i]=commentinv[j] then
          begin
            invcomment[i]:=commentcomment[j];
            break;
          end;
          j:=j+1;
        end;
      end;
      if bl2 then
      begin
        j:=1;
        while movementinv[j]<>'' do
        begin
          if invinv[i]=movementinv[j] then
          begin
            invmovement[i]:=movementmovement[j];
            break;
          end;
          j:=j+1;
        end;
      end;
      if bl3 then
      begin
        j:=1;
        while kodkod[j]<>'' do
        begin
          if invkod[i]=kodkod[j] then
          begin
            invdivision[i]:=koddivision[j];
            invtobo[i]:=kodtobo[j];
            break;
          end;
          j:=j+1;
        end;
      end;
      if bl4 then
      begin
        j:=1;
        while infonumber[j]<>'' do
        begin
          if invtobo[i]=infonumber[j] then
          begin
            invtoboadres[i]:=infoadres[j];
            break;
          end;
          j:=j+1;
        end;
      end;
    end;
end;
{//////////// загрузить из файла "INFO.BASE"////////////}
procedure loadinginfo();
var s,num,com: string;
    i,j,len: integer;
begin
    for i:=1 to N2 do begin infonumber[i]:=''; infoadres[i]:=''; end;
    form1.M.Lines.LoadFromFile(pathapp+'info.base');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      if s[i]='&' then
      begin
        num:='';com:='';i:=i+1;
        while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
        while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
        infonumber[j]:=num;infoadres[j]:=com;j:=j+1;
      end;
      i:=i+1;
    end;
end;
{//////////// загрузить из файла "INV.XLS"////////////}
procedure loadinginv();
var s: string;
    i,j,len: integer;
begin
    for i:=1 to N do
    begin
      invinv[i]:=''; invtype[i]:='';
      invmodel[i]:=''; invkod[i]:='';
      invtobo[i]:=''; invtoboadres[i]:='';
      invdivision[i]:=''; invmovement[i]:='';
      invcomment[i]:=''; invspisan[i]:=false;
    end;
    form1.M.Lines.LoadFromFile(pathapp+'inv.xls');
    s:=form1.M.Text;
    len:=length(s);
    j:=1; i:=1;
    while i<=len do begin
    while s[i]<>#9 do begin invinv[j]:=invinv[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#9 do begin invtype[j]:=invtype[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#9 do begin invmodel[j]:=invmodel[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#13 do begin invkod[j]:=invkod[j]+s[i]; i:=i+1; end;i:=i+2;
    if invkod[j]='Списан' then invspisan[j]:=true;
    j:=j+1; end;
    Lastinvnumber:=j-1;
end; 
{//////////// загрузить из файла "KOD.XLS"////////////}
procedure loadingkod();
var s: string;
    i,j,len: integer;
begin
    for i:=1 to N2 do begin kodkod[i]:=''; koddivision[i]:=''; kodtobo[i]:=''; end;
    form1.M.Lines.LoadFromFile(pathapp+'kod.xls');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#9 do begin kodkod[j]:=kodkod[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin koddivision[j]:=koddivision[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#13 do begin kodtobo[j]:=kodtobo[j]+s[i]; i:=i+1; end;i:=i+2;
      j:=j+1;
    end;
end;
{//////////// загрузить из файла "COMMENT.BASE"////////////}
procedure loadingcomment();
var s,num,com: string;
    i,j,len: integer;
begin
    for i:=1 to N do begin commentinv[i]:=''; commentcomment[i]:=''; end;
    form1.M.Lines.LoadFromFile(pathapp+'comment.base');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      if s[i]='&' then
      begin
        num:='';com:='';i:=i+1;
        while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
        while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
        commentinv[j]:=num; commentcomment[j]:=com;j:=j+1;
      end;
      i:=i+1;
    end;
end; 
{//////////// загрузить из файла "MOVEMENT.BASE"////////////}
procedure loadingmovement();
var s,num,mov: string;
    i,j,len: integer;
begin 
    for i:=1 to N do begin movementinv[i]:=''; movementmovement[i]:=''; end;
    form1.M.Lines.LoadFromFile(pathapp+'movement.base');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      if s[i]='&' then
      begin
        num:='';mov:='';i:=i+1;
        while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
        while s[i]<>'}' do begin mov:=mov+s[i]; i:=i+1; end;
        movementinv[j]:=num; movementmovement[j]:=mov;j:=j+1;
      end;
      i:=i+1;
    end;
end;
{//////////// загрузить из файла "settings.file"////////////}
procedure loadingsettings();
var s,num,com: string;
    i: integer;
begin
  with form1 do begin //with
    M.Lines.LoadFromFile(pathapp+'settings.file');
    s:=M.Text;
    i:=1;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf1.text:=num;kf1.text:=com;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf2.text:=num;kf2.text:=com;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf3.text:=num;kf3.text:=com;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf4.text:=num;kf4.text:=com;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf5.text:=num;kf5.text:=com;
    num:='';com:='';
    while s[i]<>'&' do i:=i+1; i:=i+1;
    while s[i]<>'{' do begin num:=num+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>'}' do begin com:=com+s[i]; i:=i+1; end;
    bf6.text:=num;kf6.text:=com;
    filtr1.Caption:=bf1.text;
    filtr2.Caption:=bf2.text;
    filtr3.Caption:=bf3.text;
    filtr4.Caption:=bf4.text;
    filtr5.Caption:=bf5.text;
    filtr6.Caption:=bf6.text;
  end; //with
end;
{//////////// сохранить в файл "INFO.BASE"////////////}
procedure savinginfo();
var i: integer;
begin
    form1.M.Text:='';
    i:=1;
    while infonumber[i]<>'' do
    begin
      form1.M.Lines.Add('&'+infonumber[i]+'{'+infoadres[i]+'}');
      i:=i+1;
    end;
    form1.M.Lines.SaveToFile(pathapp+'info.base');
end;
{//////////// сохранить в файл "INV.XLS"////////////}
procedure savinginv();
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to Lastinvnumber do
    form1.M.Lines.Add(invinv[i]+#9+invtype[i]+#9+invmodel[i]+#9+invkod[i]);
    form1.M.Lines.SaveToFile(pathapp+'inv.xls');
end; 
{//////////// сохранить в файл "KOD.XLS"////////////}
procedure savingkod();
var i: integer;
begin
    form1.M.Text:='';
    i:=1;
    while kodkod[i]<>'' do
    begin
      form1.M.Lines.Add(kodkod[i]+#9+koddivision[i]+#9+kodtobo[i]);
      i:=i+1;
    end;
    form1.M.Lines.SaveToFile(pathapp+'kod.xls');
end;
{//////////// сохранить в файл "COMMENT.BASE"////////////}
procedure savingcomment();
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to Lastinvnumber do
    form1.M.Lines.Add('&'+invinv[i]+'{'+invcomment[i]+'}');
    form1.M.Lines.SaveToFile(pathapp+'comment.base');
end;
{//////////// сохранить в файл "MOVEMENT.BASE"////////////}
procedure savingmovement();
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to Lastinvnumber do
    form1.M.Lines.Add('&'+invinv[i]+'{'+invmovement[i]+'}');
    form1.M.Lines.SaveToFile(pathapp+'movement.base');
end;
{//////////// сохранить в файл "settings.file"////////////}
procedure savingsettings();
begin
  with form1 do begin //with
    M.Text:='';
    M.Lines.Add('&'+bf1.text+'{'+kf1.text+'}');
    M.Lines.Add('&'+bf2.text+'{'+kf2.text+'}');
    M.Lines.Add('&'+bf3.text+'{'+kf3.text+'}');
    M.Lines.Add('&'+bf4.text+'{'+kf4.text+'}');
    M.Lines.Add('&'+bf5.text+'{'+kf5.text+'}');
    M.Lines.Add('&'+bf6.text+'{'+kf6.text+'}');
    M.Lines.SaveToFile(pathapp+'settings.file');
  end; //with
end;
//ВСЕ FALSE ИЛИ TRUE//
procedure all(bl: boolean);
begin
  with form1 do
  begin
  //кнопки
    if bl and (chooseninv<>'') then
    begin
      if invspisan[strtoint(chooseninv)]=false then
      begin
        if choosenkuda<>'' then Move1.Enabled:=true;
        Move2.Enabled:=true;
      end;
      if (invmovement[strtoint(chooseninv)]<>'') then History2.Enabled:=true;
    end else begin
      Move1.Enabled:=false;
      Move2.Enabled:=false;
      History2.Enabled:=false;
    end;
    VEXCEL.Enabled:=bl;
    ButtonSEARCH.Enabled:=bl;
    History1.Enabled:=bl;
    redak.Enabled:=bl;
    filtr1.Enabled:=bl;
    filtr2.Enabled:=bl;
    filtr3.Enabled:=bl;
    filtr4.Enabled:=bl;
    filtr5.Enabled:=bl;
    filtr6.Enabled:=bl;
    Dobav1.Enabled:=bl;
    Izmen1.Enabled:=bl;
    Udal1.Enabled:=bl;
    Dobav2.Enabled:=bl;
    Izmen2.Enabled:=bl;
    Udal2.Enabled:=bl;
    Dobav3.Enabled:=bl;
    Izmen3.Enabled:=bl;
    Udal3.Enabled:=bl;
    UpDown1.Enabled:=bl;
  // < >
    if bl then
    begin
      if currentsearch>1 then bprev.Enabled:=true else bprev.Enabled:=false;
      if (currentsearch<N2)and(searchstring[currentsearch+1]<>'') then bnext.Enabled:=true else bnext.Enabled:=false;
    end else begin
      bprev.Enabled:=false;
      bnext.Enabled:=false;
    end;
  //галочки
    CheckBox1.Enabled:=bl;
    CheckBox2.Enabled:=bl;
    CheckBox3.Enabled:=bl;
    CheckBox4.Enabled:=bl;
    CheckBox5.Enabled:=bl;
    CheckBox6.Enabled:=bl;
    CheckBox7.Enabled:=bl;
  //поля
    DateTimePicker1.Enabled:=bl;
    DateTimePicker2.Enabled:=bl;
    DateTimePicker3.Enabled:=bl;
    ComboBoxKUDA1.Enabled:=bl;
    ComboBoxTOBO1.Enabled:=bl;
    ComboBoxTOBO2.Enabled:=bl;
    ComboBoxTYPE.Enabled:=bl;
    ComboBoxKOD.Enabled:=bl;
  //эдиты                   
    EditSEARCH.Enabled:=bl;
    EditNUMBER.Enabled:=bl;
    EditMODEL.Enabled:=bl;
    EditKOD.Enabled:=bl;
    EditDIVISION.Enabled:=bl;
    EditTOBO.Enabled:=bl;
  //мемо
    MemoCOMMENT1.Enabled:=bl;
    MemoCOMMENT2.Enabled:=bl;
  //stringgrid
    StringGridINV.Enabled:=bl;
    StringGridHISTORY.Enabled:=bl;
  end;
end;
//НАЗВАНИЕ ПОЛЕЙ ТАБЛИЦ//
procedure NameGrids();
begin
  with form1 do
  begin
    StringGridINV.Cells[0,0]:='№п/п';
    StringGridINV.Cells[1,0]:='Инв. №';
    StringGridINV.Cells[2,0]:='Тип';
    StringGridINV.Cells[3,0]:='Модель';
    StringGridINV.Cells[4,0]:='Филиал';
    StringGridINV.Cells[5,0]:='Код';
    StringGridINV.Cells[6,0]:='Подразделение';
    StringGridINV.Cells[7,0]:='Комментарий';

    StringGridHISTORY.Cells[0,0]:='№п/п';
    StringGridHISTORY.Cells[1,0]:='Дата';
    StringGridHISTORY.Cells[2,0]:='Инв. №';
    StringGridHISTORY.Cells[3,0]:='Модель';
    StringGridHISTORY.Cells[4,0]:='Откуда';
    StringGridHISTORY.Cells[5,0]:='Куда';
    StringGridHISTORY.Cells[6,0]:='В подразделение';
  end;
end;
//ЗАКРАШИВАНИЕ ФОРМЫ//
procedure colorbackground(col: tcolor);
begin
  with form1 do
  begin
    panelSEARCH.Color:=col;
    panelMENU.Color:=col;
    panelINV.Color:=col;
    panelKOD.Color:=col;
    panelTOBO.Color:=col;
    PanelVexcel12.Color:=col;
    PanelVexcel22.Color:=col;
    PanelFiltr2.Color:=col;
    PanelPeremestit2.Color:=col;
    PanelRedaktor2.Color:=col;
    MemoRedaktor.Color:=col;
  end;
end;
//И Н И Ц А Л И З А Ц И Я//
procedure TForm1.FormCreate(Sender: TObject);
var i: integer;
begin
  username:=GetUserFromWindows;
  pathapp:=ExtractFilePath(Application.ExeName);
  M.Lines.LoadFromFile(pathapp+'Synchronize.file');
  if (M.Text<>'')and(M.Text<>username) then
  begin
    blSync:=true;
    PanelSync1.Visible:=true;
    syncname:=M.Text;
    LabelSync.Caption:='Режим редактирования недоступен. Пользователь "'+syncname+'" уже работает с базой:';
    Timer1.Interval:=10000;
    all(false);
    VEXCEL.Enabled:=true;
    ButtonSEARCH.Enabled:=true;
    EditSEARCH.Enabled:=true;
    CheckBox1.Enabled:=true;
    CheckBox2.Enabled:=true;
    CheckBox3.Enabled:=true;
    CheckBox4.Enabled:=true;
    CheckBox5.Enabled:=true;
    CheckBox6.Enabled:=true;
    CheckBox7.Enabled:=true;
    DateTimePicker2.Enabled:=true;
    DateTimePicker3.Enabled:=true;
    History1.Enabled:=true;
    ComboBoxTOBO1.Enabled:=true;
    filtr1.Enabled:=true;
    filtr2.Enabled:=true;
    filtr3.Enabled:=true;
    filtr4.Enabled:=true;
    filtr5.Enabled:=true;
    filtr6.Enabled:=true;
    StringGridINV.Enabled:=true;
    StringGridHISTORY.Enabled:=true;
  end else
  begin
    blSync:=false;
    M.Text:=username;
    M.Lines.SaveToFile(pathapp+'Synchronize.file');
    M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
    M.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--OPENED');
    M.Lines.SaveToFile(pathapp+'UserActivity.txt');
  end;
  ///////1 этап//////////
  loadinginv();
  loadingcomment();
  loadingmovement();
  loadingkod();
  loadinginfo();
  loadingsettings();
  ///////2 этап//////////
  FillCommentMovementDivisionToboadres(true,true,true,true);
  ///////3 этап//////////
  SortKod();
  SortTOBO();
  SortInv();
  SortType();
  ///////4 этап//////////
  NameGrids();
  colorbackground(rgb(255,228,193));
  //инициализация мелкой хрени//
  currentsearch:=1;
  PanelKOD.top:=PanelKOD.top+PanelKOD.Height;
  PanelTOBO.top:=PanelTOBO.top+PanelTOBO.Height;
  DateTimePicker1.Date:=Date;
  DateTimePicker2.Date:=Date-30;
  DateTimePicker3.Date:=Date;
  form1.ComboBoxTOBO1.ItemIndex:=0;
  form1.ComboBoxKUDA1.ItemIndex:=0;
  savedialog1.InitialDir:=pathapp;
  for i:=1 to Lastinvnumber do
  begin
      StringGridINV.Cells[0,StringGridINV.RowCount-1]:=inttostr(StringGridINV.RowCount-1);
      StringGridINV.Cells[1,StringGridINV.RowCount-1]:=invinv[i];
      StringGridINV.Cells[2,StringGridINV.RowCount-1]:=invtype[i];
      StringGridINV.Cells[3,StringGridINV.RowCount-1]:=invmodel[i];
      StringGridINV.Cells[4,StringGridINV.RowCount-1]:=invtobo[i];
      StringGridINV.Cells[5,StringGridINV.RowCount-1]:=invkod[i];
      StringGridINV.Cells[6,StringGridINV.RowCount-1]:=invdivision[i];
      StringGridINV.Cells[7,StringGridINV.RowCount-1]:=invcomment[i];
      StringGridINV.Cells[8,StringGridINV.RowCount-1]:=inttostr(i);
      StringGridINV.RowCount:=StringGridINV.RowCount+1;
  end;
    chooseninv:=StringGridINV.Cells[8,1];
    if (blSync=false) then begin M.Lines.LoadFromFile(pathapp+'UserActivity.txt'); InvFromTable(chooseninv); end;
end;
//ЗАКРЫТИЕ ПРОГРАММЫ//
procedure TForm1.FormDestroy(Sender: TObject);
begin
  if blSync=false then
  begin
  M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
  m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--CLOSED');
  m.Lines.SaveToFile(pathapp+'UserActivity.txt');
  M.Text:='';
  M.Lines.SaveToFile(pathapp+'Synchronize.file');
  end;
end;
//КНОПКА"Вверх-вниз"//
procedure TForm1.UpDown1ChangingEx(Sender: TObject;
  var AllowChange: Boolean; NewValue: Smallint;
  Direction: TUpDownDirection);
begin
  UpDown1.Enabled:=false;
  case NewValue of
  1: begin bl1:=true; end;
  2: begin
      if UpDown1.Position<NewValue then begin  bl2:=true; end;
      if UpDown1.Position>NewValue then begin  bl3:=true; end;
     end;
  3:begin  bl4:=true; end;
  else UpDown1.Enabled:=true;
  end;
end;
//ТАЙМЕР//
procedure TForm1.Timer1Timer(Sender: TObject);
var delta, maximum: integer;
begin
  delta:=16;
  maximum:=112;
  if bl1 then
  begin
    panelINV.Height:=panelINV.Height+delta;
    panelKOD.Top:=panelKOD.Top+delta;
    if panelINV.Height=maximum then begin  bl1:=false; UpDown1.Enabled:=true; end;
  end;
  if bl2 then
  begin
    panelINV.Height:=panelINV.Height-delta;
    panelKOD.Top:=panelKOD.Top-delta;
    if panelINV.Height=0 then begin  bl2:=false; UpDown1.Enabled:=true; end;
  end;
  if bl3 then
  begin
    panelKOD.Height:=panelKOD.Height+delta;
    panelTOBO.Top:=panelTOBO.Top+delta;
    if panelKOD.Height=maximum then begin  bl3:=false; UpDown1.Enabled:=true; end;
  end;
  if bl4 then
  begin
    panelKOD.Height:=panelKOD.Height-delta;
    panelTOBO.Top:=panelTOBO.Top-delta;
    if panelKOD.Height=0 then begin  bl4:=false; UpDown1.Enabled:=true; end;
  end;
  if blSync then
  begin
    M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
    if M.Text<>ListBoxSync.Items.Text then
    begin
      ListBoxSync.Items.Text:=M.Text;
      if (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-7]='C')and
         (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-6]='L')and
         (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-5]='O')and
         (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-4]='S')and
         (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-3]='E')and
         (ListBoxSync.Items.Text[length(ListBoxSync.Items.Text)-2]='D') then
      begin
      ButtonSync.Visible:=true;
      LabelSync.Caption:='Пользователь "'+syncname+'" вышел из программы. Режим редактирования доступен.';
      end else begin
      ButtonSync.Visible:=false;
      LabelSync.Caption:='Режим редактирования недоступен. Пользователь "'+syncname+'" уже работает с базой:';
      ///////1 этап//////////
      loadinginv();
      loadingcomment();
      loadingmovement();
      loadingkod();
      loadinginfo();
      loadingsettings();
      ///////2 этап//////////
      FillCommentMovementDivisionToboadres(true,true,true,true);
      ///////3 этап//////////
      SortKod();
      SortTOBO();
      SortInv();
      SortType();
      end;
    end;
  end;

end;
//КНОПКА "В Excel"//
procedure TForm1.VEXCELClick(Sender: TObject);
begin
  all(false);
  if StringGridINV.Visible=true then
  PanelVexcel11.Visible:=true
  else
  PanelVexcel21.Visible:=true;
end;
//В EXCEL ИНВЕНТАРНИКИ//
procedure TForm1.B1NazadClick(Sender: TObject);
begin
  all(true);
  PanelVexcel11.Visible:=false;
end;
procedure TForm1.B1SohrClick(Sender: TObject);
var s,s1: string;
    i,j,len: integer;
begin
    M.Text:='';
    i:=0;
    while StringGridINV.Cells[1,i]<>'' do
    begin
      s:='';
      if CB11.Checked=true then s:=s+StringGridINV.Cells[1,i]+#9;
      if CB12.Checked=true then s:=s+StringGridINV.Cells[2,i]+#9;
      if CB13.Checked=true then s:=s+StringGridINV.Cells[3,i]+#9;
      if CB14.Checked=true then s:=s+StringGridINV.Cells[4,i]+#9;
      if CB15.Checked=true then s:=s+StringGridINV.Cells[5,i]+#9;
      if CB16.Checked=true then s:=s+StringGridINV.Cells[6,i]+#9;
      if CB17.Checked=true then
      begin
        j:=1;
        s1:=StringGridINV.Cells[7,i];
        len:=length(StringGridINV.Cells[7,i]);
        while j<=len do
        begin
          if s1[j]<>#10 then
          if s1[j]= #13 then
          s:=s+' ' else s:=s+s1[j];
          j:=j+1;
        end;
      end; 
      M.Lines.Add(s);
      i:=i+1;
    end;
    //сохранение//
    savedialog1.Execute;
    s:=savedialog1.Files.Text;
    s1:='';
    for i:=1 to (length(s)-2) do
    s1:=s1+s[i];
    if s1<>'' then M.Lines.SaveToFile(s1+'.xls');

    all(true);
    PanelVexcel11.Visible:=false;
    ShowMessage('Импорт в Excel успешно завершён!');
end;
//В EXCEL ИСТОРИЮ//
procedure TForm1.B2NazadClick(Sender: TObject);
begin
  all(true);
  PanelVexcel21.Visible:=false;
end;
procedure TForm1.B2SohrClick(Sender: TObject);
var s,s1: string;
    i,j: integer;
begin
    s:=s+'Дата перемещения'+#9+'Тип'+#9+'Модель'+#9
    +'Наименование объекта'+#9+'Инвентарный номер'+#9+'Наименование отдела, код места эксплуатации, передающего объект'+#9
    +'Наименование отдела, код места эксплуатации, принимающего  объект';
    M.Text:='';
    M.Lines.Add(s);
    i:=1;
    while StringGridHISTORY.Cells[1,i]<>'' do
    begin
      s:='';
      s:=s+StringGridHISTORY.Cells[1,i]+#9;
      j:=1;
      while StringGridHISTORY.Cells[2,i]<>invinv[j] do j:=j+1;
      s:=s+invtype[j]+#9;
      s:=s+StringGridHISTORY.Cells[3,i]+#9+#9;
      s:=s+StringGridHISTORY.Cells[2,i]+#9;
      s:=s+StringGridHISTORY.Cells[4,i]+#9;
      s:=s+StringGridHISTORY.Cells[5,i];
      M.Lines.Add(s);
      i:=i+1;
    end;
    //сохранение//
    savedialog1.Execute;
    s:=savedialog1.Files.Text;
    for i:=1 to (length(s)-2) do
    s1:=s1+s[i];
    if s1<>'' then M.Lines.SaveToFile(s1+'.xls');

    all(true);
    PanelVexcel21.Visible:=false;
    ShowMessage('Импорт в Excel успешно завершён!');
end;
//КНОПКА "Переместить"//
procedure TForm1.Move1Click(Sender: TObject);
begin
  all(false);
  B4Peremestit.Caption:='Переместить';
  LabelPeremestit.Caption:='Перемещение инвентарного номера '+invinv[strtoint(chooseninv)];
  MemoPeremestit.Text:=invcomment[strtoint(chooseninv)];
  PanelPeremestit1.Visible:=true;
end;
//КНОПКА "Списать"//
procedure TForm1.Move2Click(Sender: TObject);
begin
  all(false);
  B4Peremestit.Caption:='Списать';
  LabelPeremestit.Caption:='Списание инвентарного номера '+invinv[strtoint(chooseninv)];
  MemoPeremestit.Text:=invcomment[strtoint(chooseninv)];
  PanelPeremestit1.Visible:=true;
end;
//ПАНЕЛЬ ПЕРЕМЕЩЕНИЯ/СПИСАНИЯ //
procedure TForm1.B4NazadClick(Sender: TObject);
begin
  all(true);
  PanelPeremestit1.Visible:=false;
end;
procedure TForm1.B4PeremestitClick(Sender: TObject);
var i,j: integer;
    bl: boolean;
begin
  bl:=false;
  i:=strtoint(chooseninv);
  if B4Peremestit.Caption='Переместить' then
  begin
    M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
    m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Перемещение '+invinv[i]+' '+invtype[i]+' '+invmodel[i]+' '+invkod[i]+' -> '+choosenkuda);
    m.Lines.SaveToFile(pathapp+'UserActivity.txt');

    j:=1;
    while kodkod[j]<>choosenkuda do j:=j+1;


    invmovement[i]:=invmovement[i]+datetostr(DateTimePicker1.Date)+#9+invkod[i]+#9+kodkod[j]+#9;
    invdivision[i]:=koddivision[j];
    invcomment[i]:=MemoPeremestit.Text;
    invkod[i]:=kodkod[j];
    invtobo[i]:=kodtobo[j];
    invtoboadres[i]:='';
    j:=1;
    while (infonumber[j]<>'') do
    begin
      if infonumber[j]=invtobo[i] then begin invtoboadres[i]:=infoadres[j]; break; end;
      j:=j+1;
    end;
  end else
  if B4Peremestit.Caption='Списать' then
  begin
    M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
    m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Списание '+invinv[i]+' '+invtype[i]+' '+invmodel[i]+' '+invkod[i]);
    m.Lines.SaveToFile(pathapp+'UserActivity.txt');

    invmovement[i]:=invmovement[i]+datetostr(DateTimePicker1.Date)+#9+invkod[i]+#9+'Списан'+#9;
    invcomment[i]:=MemoPeremestit.Text;
    invspisan[i]:=true;
    invkod[i]:='Списан';
    invdivision[i]:='';
    invtobo[i]:='';
    invtoboadres[i]:='';
  end;
  savinginv();
  savingcomment();
  savingmovement();

  RefreshTables();
  InvFromTable(chooseninv);
  all(true);
  PanelPeremestit1.Visible:=false;
end;
//КНОПКА "Редак."//
procedure TForm1.redakClick(Sender: TObject);
begin
  all(false);
  loadingsettings();
  PanelFiltr1.Visible:=true;
end;
//ПАНЕЛЬ РЕДАКТИРОВАНИЯ ФИЛЬТРОВ//
procedure TForm1.B3NazadClick(Sender: TObject);
begin
  all(true);
  PanelFiltr1.Visible:=false;
end;
procedure TForm1.B3SohrClick(Sender: TObject);
var s1,s2: string;
    i: integer;
begin
  M.Text:='';
  s1:=kf1.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf1.text+'{'+s2+'}');
  s1:=kf2.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf2.text+'{'+kf2.text+'}');
  s1:=kf3.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf3.text+'{'+kf3.text+'}'); 
  s1:=kf4.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf4.text+'{'+kf4.text+'}'); 
  s1:=kf5.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf5.text+'{'+kf5.text+'}'); 
  s1:=kf6.text; s2:=''; for i:=1 to length(s1) do
  if (s1[i]<>'&')and(s1[i]<>'{')and(s1[i]<>'}') then s2:=s2+s1[i];
  M.Lines.Add('&'+bf6.text+'{'+s2+'}');
  M.Lines.SaveToFile('settings.file');
  filtr1.Caption:=bf1.Text;
  filtr2.Caption:=bf2.Text;
  filtr3.Caption:=bf3.Text;
  filtr4.Caption:=bf4.Text;
  filtr5.Caption:=bf5.Text;
  filtr6.Caption:=bf6.Text;
  all(true);
  PanelFiltr1.Visible:=false;
end;
// ПАНЕЛЬ ДОБАВЛЕНИЯ/УДАЛЕНИЯ/ИЗМЕНЕНИЯ //
procedure TForm1.B7NazadClick(Sender: TObject);
begin
  all(true);
  PanelRedaktor1.Visible:=false;
end;

procedure TForm1.B7DobavClick(Sender: TObject);
var i,j,k,temp: integer;
    temps,s: string;
begin
  if b7dobav.Caption='Добавить' then
  case choosenpanel of
  1:begin
      Lastinvnumber:=Lastinvnumber+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Добавление ИНВ.№ '+EditNUMBER.Text+' '+ComboBoxTYPE.Text+' '+EditMODEL.Text+' '+ComboBoxKOD.Text);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      invinv[Lastinvnumber]:=EditNUMBER.Text;
      invtype[Lastinvnumber]:=ComboBoxTYPE.Text;
      invmodel[Lastinvnumber]:=EditMODEL.Text;
      invcomment[Lastinvnumber]:=MemoCOMMENT1.Text;
      invkod[Lastinvnumber]:=ComboBoxKOD.Text;
      if invkod[Lastinvnumber]='Списан' then invspisan[Lastinvnumber]:=true else invspisan[Lastinvnumber]:=false; 
      invdivision[Lastinvnumber]:='';
      invtobo[Lastinvnumber]:='';
      i:=1;while(kodkod[i]<>'') do
      begin
        if (kodkod[i]+' '+koddivision[i]=ComboBoxKOD.Text)or(kodkod[i]=ComboBoxKOD.Text) then
        begin
          invkod[Lastinvnumber]:=kodkod[i];
          invdivision[Lastinvnumber]:=koddivision[i];
          invtobo[Lastinvnumber]:=kodtobo[i];
          break;
        end;
        i:=i+1;
      end;
      invtoboadres[Lastinvnumber]:='';
      i:=1;
      while infonumber[i]<>'' do
      begin
        if infonumber[i]=invtobo[Lastinvnumber] then begin invtoboadres[Lastinvnumber]:=infoadres[i]; break; end;
        i:=i+1;
      end;

      SortType();
      savinginv();
      savingcomment();
      savingmovement();
    end;
  2:begin
      i:=1;while kodkod[i]<>'' do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Добавление КОДА '+EditKOD.Text+' '+EditDIVISION.Text+' '+ComboBoxTOBO2.Text);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      kodkod[i]:=EditKOD.Text;
      koddivision[i]:=EditDIVISION.Text;
      kodtobo[i]:=ComboBoxTOBO2.Text;
      for i:=1 to Lastinvnumber do
      begin
        if invkod[i]=EditKOD.Text then
        begin
          invdivision[i]:=EditDIVISION.Text;
          invtobo[i]:=ComboBoxTOBO2.Text;
          invtoboadres[i]:='';
          j:=1;
          while infonumber[j]<>'' do
          begin
            if infonumber[j]=invtobo[i] then begin invtoboadres[i]:=infoadres[j]; break; end;
            j:=j+1;
          end;
        end;
      end;

      SortKod();
      savingkod();
    end;
  3:begin
      i:=1;while infonumber[i]<>'' do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Добавление ТОБО '+EditTOBO.Text);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      infonumber[i]:=EditTOBO.Text;
      infoadres[i]:=MemoCOMMENT2.Text;
      for i:=1 to Lastinvnumber do
      if invtobo[i]=EditTOBO.Text then invtoboadres[i]:=MemoCOMMENT2.Text;

      SortTOBO();
      savinginfo();
    end;
  end else
  if b7dobav.Caption='Изменить' then
  case choosenpanel of
  1:begin
      i:=strtoint(chooseninv);

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Изменение ИНВ.№ '+invinv[i]+' '+invtype[i]+' '+invmodel[i]+' '+invkod[i]+' -> '+invinv[i]+' '+ComboBoxTYPE.Text+' '+EditMODEL.Text+' '+ComboBoxKOD.Text);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      invinv[i]:=EditNUMBER.Text;
      invtype[i]:=ComboBoxTYPE.Text;
      invmodel[i]:=EditMODEL.Text;
      if (invspisan[i])and(invkod[i]<>ComboBoxTYPE.Text) then invspisan[i]:=false;
      invkod[i]:=ComboBoxKOD.Text;
      invdivision[i]:='';
      invtobo[i]:='';
      j:=1;while (kodkod[j]<>'') do
      begin
        if (kodkod[j]+' '+koddivision[j]=ComboBoxKOD.Text)or(kodkod[j]=ComboBoxKOD.Text) then
        begin
          invkod[i]:=kodkod[j];
          invdivision[i]:=koddivision[j];
          invtobo[i]:=kodtobo[j];
          break;
        end;
        j:=j+1;
      end;
      invtoboadres[i]:='';
      j:=1;
      while infonumber[j]<>'' do
      begin
        if infonumber[j]=invtobo[i] then begin invtoboadres[i]:=infoadres[j]; break; end;
        j:=j+1;
      end;

      SortType();
      savinginv();
      if invcomment[i]<>MemoCOMMENT1.Text then
      begin
        invcomment[i]:=MemoCOMMENT1.Text;
        savingcomment();
      end;
      if invinv[i]<>EditNUMBER.Text then
      begin
        savingmovement();
        savingcomment();
      end;
    end;
  2:begin
      i:=1;while kodkod[i]<>choosenkod do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Изменение КОДА '+kodkod[i]+' '+koddivision[i]+' '+kodtobo[i]+' -> '+kodkod[i]+' '+EditDIVISION.Text+' '+ComboBoxTOBO2.Text);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      kodkod[i]:=EditKOD.Text;
      koddivision[i]:=EditDIVISION.Text;
      kodtobo[i]:=ComboBoxTOBO2.Text;
      for i:=1 to Lastinvnumber do
      begin
        if invkod[i]=choosenkod then
        begin
          invkod[i]:=EditKOD.Text;
          invdivision[i]:=EditDIVISION.Text;
          invtobo[i]:=ComboBoxTOBO2.Text;
          invtoboadres[i]:='';
          j:=1;
          while infonumber[j]<>'' do
          begin
            if infonumber[j]=invtobo[i] then begin invtoboadres[i]:=infoadres[j]; break; end;
            j:=j+1;
          end;
        end;
        //////находит вхождение строки для замены
        if (strpos(pchar(LowString(invmovement[i])),pchar(#9+choosenkod+#9))<>nil) then
        begin
          ////первичная инициализация
          s:=invmovement[i];
          invmovement[i]:='';
          temp:=length(s);
          ////цикл прохода по выбранной строке
          j:=1;
          while j<=temp do
          begin
            /////переписывает дату
            while s[j]<>#9 do
            begin
              invmovement[i]:=invmovement[i]+s[j];
              j:=j+1;
            end;
            invmovement[i]:=invmovement[i]+#9;j:=j+1;
            ///переписывает первый код и сравнивает его с изменённым
            temps:='';
            while s[j]<>#9 do
            begin
              temps:=temps+s[j];
              j:=j+1;
            end;
            if temps=choosenkod then
              invmovement[i]:=invmovement[i]+EditKOD.Text
            else
              invmovement[i]:=invmovement[i]+temps;
            invmovement[i]:=invmovement[i]+#9;j:=j+1;
            ///переписывает второй код и сравнивает его с изменённым
            temps:='';
            while s[j]<>#9 do
            begin
              temps:=temps+s[j];
              j:=j+1;
            end;
            if temps=choosenkod then
              invmovement[i]:=invmovement[i]+EditKOD.Text
            else
              invmovement[i]:=invmovement[i]+temps;
            invmovement[i]:=invmovement[i]+#9;j:=j+1;
          end;
        end;
      end;

      SortKod();
      savingkod();
      savinginv();
    end;
  3:begin
      i:=1;while infonumber[i]<>choosentobo do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Изменение ТОБО '+infonumber[i]);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      infonumber[i]:=EditTOBO.Text;
      infoadres[i]:=MemoCOMMENT2.Text;
      for i:=1 to Lastinvnumber do
      if invtobo[i]=choosentobo then
      begin
        invtobo[i]:=EditTOBO.Text;
        invtoboadres[i]:=MemoCOMMENT2.Text;
      end;
      i:=1;while kodkod[i]<>'' do
      begin
        if kodtobo[i]=choosentobo then kodtobo[i]:=EditTOBO.Text;
        i:=i+1;
      end;

      SortTOBO();
      savingkod();
      savinginfo();
    end;
  end else
  if b7dobav.Caption='Удалить' then
  case choosenpanel of
  1:begin
      i:=strtoint(chooseninv);
      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Удаление ИНВ.№ '+invinv[i]+' '+invtype[i]+' '+invmodel[i]+' '+invkod[i]);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      for i:=i to Lastinvnumber-1 do
      begin
        invinv[i]:=invinv[i+1];
        invtype[i]:=invtype[i+1];
        invmodel[i]:=invmodel[i+1];
        invkod[i]:=invkod[i+1];
        invdivision[i]:=invdivision[i+1];
        invtobo[i]:=invtobo[i+1];
        invtoboadres[i]:=invtoboadres[i+1];
        invcomment[i]:=invcomment[i+1];
        invmovement[i]:=invmovement[i+1];
        invspisan[i]:=invspisan[i+1];
      end;
        invinv[i+1]:='';
        invtype[i+1]:='';
        invmodel[i+1]:='';
        invkod[i+1]:='';
        invdivision[i+1]:='';
        invtobo[i+1]:='';
        invtoboadres[i+1]:='';
        invcomment[i+1]:='';
        invmovement[i+1]:='';
        invspisan[i+1]:=false;
      Lastinvnumber:=Lastinvnumber-1;
      chooseninv:='';
      SortType();
      savinginv();
      savingcomment();
      savingmovement();
    end;
  2:begin
      i:=1; while kodkod[i]<>choosenkod do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Удаление КОДА '+kodkod[i]+' '+koddivision[i]+' '+kodtobo[i]);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      while kodkod[i+1]<>'' do
      begin
        kodkod[i]:=kodkod[i+1];
        koddivision[i]:=koddivision[i+1];
        kodtobo[i]:=kodtobo[i+1];
        i:=i+1;
      end;
        kodkod[i+1]:='';
        koddivision[i+1]:='';
        kodtobo[i+1]:='';

      for i:=1 to Lastinvnumber do
      begin
        if invkod[i]=choosenkod then
        begin
          invdivision[i]:='';
          invtobo[i]:='';
          invtoboadres[i]:='';
        end;
      end;
      choosenkod:='';
      SortKod();
      savingkod();
    end;
  3:begin
      i:=1; while infonumber[i]<>choosentobo do i:=i+1;

      M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
      m.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--Удаление ТОБО '+infonumber[i]);
      m.Lines.SaveToFile(pathapp+'UserActivity.txt');

      while infonumber[i+1]<>'' do
      begin
        infonumber[i]:=infonumber[i+1];
        infoadres[i]:=infoadres[i+1];
        i:=i+1;
      end;
        infonumber[i+1]:='';
        infoadres[i+1]:='';

      for i:=1 to Lastinvnumber do
      if invtobo[i]=choosentobo then
      begin
        invtoboadres[i]:='';
      end;
      choosentobo:='';
      SortTOBO();
      savinginfo();
    end;
  end;
  RefreshTables();
  IfAllowAdding();
  all(true);
  PanelRedaktor1.Visible:=false;
end;
//КНОПКА "GO!"//
procedure TForm1.ButtonSEARCHClick(Sender: TObject);
var i: integer;
begin
  if EditSEARCH.Text<>'' then
  begin
    if currentsearch=1 then
    begin
      searchstring[1]:=EditSEARCH.Text;
      currentsearch:=currentsearch+1;
      for i:=currentsearch to N2 do searchstring[i]:='';
      bprev.Enabled:=false;
      bnext.Enabled:=false;
    end else
    begin
      if (currentsearch=N2)and(EditSEARCH.Text<>searchstring[N2]) then
      begin
        for i:=1 to N2-1 do searchstring[i]:=searchstring[i+1];
        searchstring[N2]:=EditSEARCH.Text;
        bprev.Enabled:=true;
        bnext.Enabled:=false;
      end else
      if EditSEARCH.Text<>searchstring[currentsearch-1] then
      begin
        searchstring[currentsearch]:=EditSEARCH.Text;
        currentsearch:=currentsearch+1;
        for i:=currentsearch to N2 do searchstring[i]:='';
        bprev.Enabled:=true;
        bnext.Enabled:=false;
      end;
    end;
    search(EditSEARCH.Text,false,CheckBox1.Checked,CheckBox2.Checked
    ,CheckBox3.Checked,CheckBox4.Checked,CheckBox5.Checked
    ,CheckBox6.Checked,CheckBox7.Checked);
  end;
end;
//НАЖАТИЕ "Enter" В ПОИСКОВОЙ СТРОКЕ//
procedure TForm1.EditSEARCHKeyPress(Sender: TObject; var Key: Char);
var i: integer;
begin
  if (Key=#13)and(EditSEARCH.Text<>'') then
  begin
    if currentsearch=1 then
    begin
      searchstring[1]:=EditSEARCH.Text;
      currentsearch:=currentsearch+1;
      for i:=currentsearch to N2 do searchstring[i]:='';
      bprev.Enabled:=false;
      bnext.Enabled:=false;
    end else
    begin
      if (currentsearch=N2)and(EditSEARCH.Text<>searchstring[N2]) then
      begin
        for i:=1 to N2-1 do searchstring[i]:=searchstring[i+1];
        searchstring[N2]:=EditSEARCH.Text;
        bprev.Enabled:=true;
        bnext.Enabled:=false;
      end else
      if EditSEARCH.Text<>searchstring[currentsearch-1] then
      begin
        searchstring[currentsearch]:=EditSEARCH.Text;
        currentsearch:=currentsearch+1;
        for i:=currentsearch to N2 do searchstring[i]:='';
        bprev.Enabled:=true;
        bnext.Enabled:=false;
      end;
    end;
    search(EditSEARCH.Text,false,CheckBox1.Checked,CheckBox2.Checked
    ,CheckBox3.Checked,CheckBox4.Checked,CheckBox5.Checked
    ,CheckBox6.Checked,CheckBox7.Checked);
  end;
end;
//ИЗМЕНЕНИЕ ПОЛЯ "Код (куда)"//
procedure TForm1.ComboBoxKUDA1Change(Sender: TObject);
var i: integer;
begin
  i:=1;
  choosenkuda:='';
  label17.Caption:='';
  Move1.Enabled:=false;
  while kodkod[i]<>'' do
  begin
    if (kodkod[i]+' '+koddivision[i]=ComboBoxKUDA1.text)or(kodkod[i]=ComboBoxKUDA1.text) then
    begin
      choosenkuda:=kodkod[i];
      label17.Caption:=koddivision[i];
      if (chooseninv<>'')and(invspisan[strtoint(chooseninv)]=false)and(invkod[strtoint(chooseninv)]<>choosenkuda) then Move1.Enabled:=true;
      break;
    end;
    i:=i+1;
  end;
end;
//ИЗМЕНЕНИЕ ПОЛЕЙ РЕДАКТОРА №1//
procedure TForm1.ComboBoxKODChange(Sender: TObject);
var i: integer;
    bl: boolean;
begin
  bl:=false;
  i:=1;
  while kodkod[i]<>'' do
  begin
    if (kodkod[i]+' '+koddivision[i]=ComboBoxKOD.Text)or(kodkod[i]=ComboBoxKOD.Text) then begin bl:=true; break; end;
    i:=i+1;
  end;
  if bl then LabelDIVISION.Caption:=koddivision[i] else LabelDIVISION.Caption:='';
  Izmen1.Enabled:=true;
end;

procedure TForm1.EditNUMBERChange(Sender: TObject);
begin
  IfAllowAdding();
  Izmen1.Enabled:=true;
end;

procedure TForm1.EditMODELChange(Sender: TObject);
begin
  Izmen1.Enabled:=true;
end;

procedure TForm1.ComboBoxTYPEChange(Sender: TObject);
begin
  Izmen1.Enabled:=true;
end;

procedure TForm1.MemoCOMMENT1Change(Sender: TObject);
begin
  Izmen1.Enabled:=true;
end;
//ИЗМЕНЕНИЕ ПОЛЕЙ РЕДАКТОРА №2//
procedure TForm1.EditKODChange(Sender: TObject);
begin
  IfAllowAdding();
  Izmen2.Enabled:=true;
end;
 
procedure TForm1.EditDIVISIONChange(Sender: TObject);
begin
  Izmen2.Enabled:=true;
end;

procedure TForm1.ComboBoxTOBO2Change(Sender: TObject);
begin
  Izmen2.Enabled:=true;
end;
//ИЗМЕНЕНИЕ ПОЛЕЙ РЕДАКТОРА №3//
procedure TForm1.EditTOBOChange(Sender: TObject);
begin
  IfAllowAdding();
  Izmen3.Enabled:=true;
end;

procedure TForm1.MemoCOMMENT2Change(Sender: TObject);
begin
  Izmen3.Enabled:=true;
end;
//КНОПКА "Добавить" РЕДАКТОРА №1//
procedure TForm1.Dobav1Click(Sender: TObject);
begin
  all(false);
  choosenpanel:=1;
  DataToPanel(Dobav1.Caption);
end;
//КНОПКА "Добавить" РЕДАКТОРА №2//
procedure TForm1.Dobav2Click(Sender: TObject);
begin
  all(false);
  choosenpanel:=2;
  DataToPanel(Dobav2.Caption);
end;
//КНОПКА "Добавить" РЕДАКТОРА №3//
procedure TForm1.Dobav3Click(Sender: TObject);
begin
  all(false);
  choosenpanel:=3;
  DataToPanel(Dobav3.Caption);
end;
//КНОПКА "Изменить" РЕДАКТОРА №1//
procedure TForm1.Izmen1Click(Sender: TObject);
begin
  all(false); 
  choosenpanel:=1;
  DataToPanel(izmen1.Caption);
end;
//КНОПКА "Изменить" РЕДАКТОРА №2//
procedure TForm1.Izmen2Click(Sender: TObject);
begin
  all(false); 
  choosenpanel:=2;
  DataToPanel(izmen2.Caption);
end;
//КНОПКА "Изменить" РЕДАКТОРА №3//
procedure TForm1.Izmen3Click(Sender: TObject);
begin
  all(false);
  choosenpanel:=3;
  DataToPanel(izmen3.Caption);
end;
//КНОПКА "Удалить" РЕДАКТОРА №1//
procedure TForm1.Udal1Click(Sender: TObject);
begin
  all(false);  
  choosenpanel:=1;
  DataToPanel(Udal1.Caption);
end;
//КНОПКА "Удалить" РЕДАКТОРА №2//
procedure TForm1.Udal2Click(Sender: TObject);
begin
  all(false);  
  choosenpanel:=2;
  DataToPanel(Udal2.Caption);
end;
//КНОПКА "Удалить" РЕДАКТОРА №3//
procedure TForm1.Udal3Click(Sender: TObject);
begin
  all(false);  
  choosenpanel:=3;
  DataToPanel(Udal3.Caption);
end;

procedure TForm1.StringGridINVSelectCell(Sender: TObject; ACol,
  ARow: Integer; var CanSelect: Boolean);
var i: integer;
begin
  chooseninv:=StringGridINV.Cells[8,ARow];
  if (arow>0)and(blSync=false) then InvFromTable(chooseninv);
end;

procedure TForm1.ComboBoxTOBO1Change(Sender: TObject);
var i: integer;
begin
  if ComboBoxTOBO1.Text='ВСЕ' then
  begin
    StringGridINV.Visible:=true;
    StringGridHISTORY.Visible:=false;
    panel1.BorderStyle:=bsSingle;
    panel2.BorderStyle:=bsNone;

    StringGridINV.RowCount:=2;
    for i:=0 to 8 do StringGridINV.Cells[i,1]:='';
    for i:=1 to Lastinvnumber do
    begin
      StringGridINV.Cells[0,StringGridINV.RowCount-1]:=inttostr(StringGridINV.RowCount-1);
      StringGridINV.Cells[1,StringGridINV.RowCount-1]:=invinv[i];
      StringGridINV.Cells[2,StringGridINV.RowCount-1]:=invtype[i];
      StringGridINV.Cells[3,StringGridINV.RowCount-1]:=invmodel[i];
      StringGridINV.Cells[4,StringGridINV.RowCount-1]:=invtobo[i];
      StringGridINV.Cells[5,StringGridINV.RowCount-1]:=invkod[i];
      StringGridINV.Cells[6,StringGridINV.RowCount-1]:=invdivision[i];
      StringGridINV.Cells[7,StringGridINV.RowCount-1]:=invcomment[i];
      StringGridINV.Cells[8,StringGridINV.RowCount-1]:=inttostr(i);
      StringGridINV.RowCount:=StringGridINV.RowCount+1;
    end;
    for i:=0 to 8 do StringGridINV.Cells[i,StringGridINV.RowCount-1]:='';
    chooseninv:=StringGridINV.Cells[8,1];
    if (blSync=false) then InvFromTable(chooseninv);
  end else
  begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text,true,false,false
      ,false,true,false,false,false);
    end;
  end;
end;

procedure TForm1.filtr1Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf1.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf1.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.filtr2Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf2.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf2.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.filtr3Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf3.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf3.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.filtr4Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf4.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf4.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.filtr5Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf5.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf5.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.filtr6Click(Sender: TObject);
begin
    if checktobo() then
    begin
      search(ComboBoxTOBO1.Text+','+kf6.Text,true,false,true
      ,false,true,false,false,false);
    end else
    if ComboBoxTOBO1.Text='ВСЕ' then
    begin
      search(kf6.Text,true,false,true
      ,false,false,false,false,false);
    end;
end;

procedure TForm1.History1Click(Sender: TObject);
var s: string;
    i,j,k: integer;
    dt: tdate;
begin
  StringGridHISTORY.Visible:=true;
  StringGridINV.Visible:=false;
  panel1.BorderStyle:=bsNone;
  panel2.BorderStyle:=bsSingle;

  StringGridHISTORY.RowCount:=2;
  for i:=0 to 7 do StringGridHISTORY.Cells[i,1]:='';
  dt:=DateTimePicker2.date;
  while dt<=DateTimePicker3.date do
  begin
    for i:=1 to Lastinvnumber do
    if strpos(pchar(invmovement[i]),pchar(datetostr(dt)))<>nil then
    begin
        s:=invmovement[i];
        j:=1;
        while j<=length(s) do
        begin
          if (s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]+s[j+7]+s[j+8]+s[j+9])=datetostr(dt) then
          begin
            StringGridHISTORY.Cells[0,StringGridHISTORY.RowCount-1]:=inttostr(StringGridHISTORY.RowCount-1);
            StringGridHISTORY.Cells[1,StringGridHISTORY.RowCount-1]:=datetostr(dt);
            StringGridHISTORY.Cells[2,StringGridHISTORY.RowCount-1]:=invinv[i];
            StringGridHISTORY.Cells[3,StringGridHISTORY.RowCount-1]:=invmodel[i];
            StringGridHISTORY.Cells[7,StringGridHISTORY.RowCount-1]:=inttostr(i);
            j:=j+11;
            StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]:='';
            StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]:='';
            while s[j]<>#9 do begin StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]:=StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]+s[j]; j:=j+1; end; j:=j+1;
            while s[j]<>#9 do begin StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]:=StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]+s[j]; j:=j+1; end; j:=j+1;
            k:=1;
            while kodkod[k]<>'' do
            begin
              if kodkod[k]=StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1] then
              begin StringGridHISTORY.Cells[6,StringGridHISTORY.RowCount-1]:=koddivision[k]; break; end;
              k:=k+1;
            end;
            StringGridHISTORY.RowCount:=StringGridHISTORY.RowCount+1;
          end else
          begin
            j:=j+11;
            while s[j]<>#9 do j:=j+1; j:=j+1;
            while s[j]<>#9 do j:=j+1; j:=j+1;
          end;
        end;
    end;
    dt:=dt+1;
  end;
  for i:=0 to 7 do StringGridHISTORY.Cells[i,StringGridHISTORY.RowCount-1]:='';
  chooseninv:=StringGridHISTORY.Cells[7,1];
  if (blSync=false) then InvFromTable(chooseninv);
end;

procedure TForm1.StringGridHISTORYSelectCell(Sender: TObject; ACol,
  ARow: Integer; var CanSelect: Boolean);
var i: integer;
begin
  chooseninv:=StringGridHISTORY.Cells[7,ARow];
  if (arow>0)and(blSync=false) then InvFromTable(chooseninv);
end;

procedure TForm1.History2Click(Sender: TObject);
var i,j,k: integer;
    s: string;
begin
  StringGridHISTORY.Visible:=true;
  StringGridINV.Visible:=false;
  panel1.BorderStyle:=bsNone;
  panel2.BorderStyle:=bsSingle;

  for i:=0 to 7 do StringGridHISTORY.Cells[i,1]:='';
  i:=strtoint(chooseninv);
  StringGridHISTORY.RowCount:=2;
  j:=1;
  s:=invmovement[i];
  while j<=length(s) do
  begin
      StringGridHISTORY.Cells[0,StringGridHISTORY.RowCount-1]:=inttostr(StringGridHISTORY.RowCount-1);
      StringGridHISTORY.Cells[1,StringGridHISTORY.RowCount-1]:=s[j]+s[j+1]+s[j+2]+s[j+3]+s[j+4]+s[j+5]+s[j+6]+s[j+7]+s[j+8]+s[j+9];
      StringGridHISTORY.Cells[2,StringGridHISTORY.RowCount-1]:=invinv[i];
      StringGridHISTORY.Cells[3,StringGridHISTORY.RowCount-1]:=invmodel[i];
      StringGridHISTORY.Cells[7,StringGridHISTORY.RowCount-1]:=inttostr(i);
      j:=j+11;
      StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]:='';
      StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]:='';
      while s[j]<>#9 do begin StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]:=StringGridHISTORY.Cells[4,StringGridHISTORY.RowCount-1]+s[j]; j:=j+1; end; j:=j+1;
      while s[j]<>#9 do begin StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]:=StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1]+s[j]; j:=j+1; end; j:=j+1;
      k:=1;
      while kodkod[k]<>'' do
      begin
        if kodkod[k]=StringGridHISTORY.Cells[5,StringGridHISTORY.RowCount-1] then
        begin StringGridHISTORY.Cells[6,StringGridHISTORY.RowCount-1]:=koddivision[k]; break; end;
        k:=k+1;
      end;
      StringGridHISTORY.RowCount:=StringGridHISTORY.RowCount+1;
  end;
  for i:=0 to 7 do StringGridHISTORY.Cells[i,StringGridHISTORY.RowCount-1]:='';
  chooseninv:=StringGridHISTORY.Cells[7,1];
  if (blSync=false) then InvFromTable(chooseninv);
end;

procedure TForm1.ButtonSyncClick(Sender: TObject);
var i: integer;
begin
  M.Lines.LoadFromFile(pathapp+'Synchronize.file');
  if (M.Text<>'')and(M.Text<>username) then
  begin
    ButtonSync.Visible:=false;
    syncname:='';
    for i:=1 to (length(m.Text)-2) do syncname:=syncname+m.Text[i];
    LabelSync.Caption:='Режим редактирования недоступен. Пользователь "'+syncname+'" уже работает с базой:';
  end else
  begin
    PanelSync1.Visible:=false;
    blSync:=false;
    Timer1.Interval:=1;
    M.Text:=username;
    M.Lines.SaveToFile(pathapp+'Synchronize.file');
    M.Lines.LoadFromFile(pathapp+'UserActivity.txt');
    M.Lines.Add('['+datetostr(date)+' '+timetostr(time)+']['+username+']--OPENED');
    M.Lines.SaveToFile(pathapp+'UserActivity.txt');
    all(true);
  ///////1 этап//////////
  loadinginv();
  loadingcomment();
  loadingmovement();
  loadingkod();
  loadinginfo();
  loadingsettings();
  ///////2 этап//////////
  FillCommentMovementDivisionToboadres(true,true,true,true);
  ///////3 этап//////////
  SortKod();
  SortTOBO();
  SortInv();
  SortType();
  end;
end;
// кнопка "<"//
procedure TForm1.bprevClick(Sender: TObject);
begin
  while searchstring[currentsearch]='' do currentsearch:=currentsearch-1;
  currentsearch:=currentsearch-1;
  bnext.Enabled:=true;
  if currentsearch=1 then bprev.Enabled:=false;
  EditSEARCH.Text:=searchstring[currentsearch];
  search(searchstring[currentsearch],false,CheckBox1.Checked,CheckBox2.Checked
  ,CheckBox3.Checked,CheckBox4.Checked,CheckBox5.Checked
  ,CheckBox6.Checked,CheckBox7.Checked);
end;
// кнопка ">"//
procedure TForm1.bnextClick(Sender: TObject);
begin
  currentsearch:=currentsearch+1;
  bprev.Enabled:=true;
  if (currentsearch=N2)or(searchstring[currentsearch+1]='') then bnext.Enabled:=false;
  EditSEARCH.Text:=searchstring[currentsearch];
  search(searchstring[currentsearch],false,CheckBox1.Checked,CheckBox2.Checked
  ,CheckBox3.Checked,CheckBox4.Checked,CheckBox5.Checked
  ,CheckBox6.Checked,CheckBox7.Checked);
  if (bnext.Enabled=false)and(currentsearch<N2) then currentsearch:=currentsearch+1;
end;

procedure TForm1.Panel1Click(Sender: TObject);
begin
  if panel1.BorderStyle=bsNone then
  begin
    panel1.BorderStyle:=bsSingle;
    panel2.BorderStyle:=bsNone;
    StringGridINV.Visible:=true;
    StringGridHISTORY.Visible:=false;
  end;
end;

procedure TForm1.Panel2Click(Sender: TObject);
begin
  if panel2.BorderStyle=bsNone then
  begin
    panel1.BorderStyle:=bsNone;
    panel2.BorderStyle:=bsSingle;
    StringGridINV.Visible:=false;
    StringGridHISTORY.Visible:=true;
  end;
end;

//сортировка//
procedure TForm1.SGMouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  posx:=x;
  posy:=y;
end;

procedure TForm1.SGMouseDown(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var temp,i,j,k: integer;
    bl: boolean;
    p: string;
begin
    if StringGridINV.Visible then
    begin
        if (posy<StringGridINV.RowHeights[0]) then
        begin
          i:=0;
          temp:=StringGridINV.ColWidths[0];
          while (i<StringGridINV.ColCount)and not((posx>temp-StringGridINV.ColWidths[i])and(posx<=temp)) do
          begin
            i:=i+1;
            temp:=temp+StringGridINV.ColWidths[i];
          end;
        end;
        if (i>0)and(i<StringGridINV.ColCount) then
        begin
          bl:=true;
          while bl do
          begin
            bl:=false;
            for j:=1 to StringGridINV.RowCount-3 do
            if (StringGridINV.Cells[i,j]='')or(StringGridINV.Cells[i,j]>StringGridINV.Cells[i,j+1]) then
            begin
              bl:=true;
              for k:=1 to StringGridINV.ColCount do
              begin
                p:=StringGridINV.Cells[k,j];StringGridINV.Cells[k,j]:=StringGridINV.Cells[k,j+1];StringGridINV.Cells[k,j+1]:=p;
              end;
            end;
          end;
        end;
    end else
    if StringGridHISTORY.Visible then
    begin
        if (posy<StringGridHISTORY.RowHeights[0]) then
        begin
          i:=0;
          temp:=StringGridHISTORY.ColWidths[0];
          while (i<StringGridHISTORY.ColCount)and not((posx>temp-StringGridHISTORY.ColWidths[i])and(posx<=temp)) do
          begin
            i:=i+1;
            temp:=temp+StringGridHISTORY.ColWidths[i];
          end;
        end;
        if (i>0)and(i<StringGridHISTORY.ColCount) then
        begin
          bl:=true;
          while bl do
          begin
            bl:=false;
            for j:=1 to StringGridHISTORY.RowCount-3 do
            if (StringGridHISTORY.Cells[i,j]='')or(StringGridHISTORY.Cells[i,j]>StringGridHISTORY.Cells[i,j+1]) then
            begin
              bl:=true;
              for k:=1 to StringGridHISTORY.ColCount do
              begin
                p:=StringGridHISTORY.Cells[k,j];StringGridHISTORY.Cells[k,j]:=StringGridHISTORY.Cells[k,j+1];StringGridHISTORY.Cells[k,j+1]:=p;
              end;
            end;
          end;
        end;
    end;
end;


end.
