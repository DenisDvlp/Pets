unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms, ToolWin,
  Dialogs, Grids, StdCtrls, ComCtrls, ExtCtrls;

type
  TForm1 = class(TForm)
    PanelDobav1: TPanel;
    DateZay1: TDateTimePicker;
    ComboBoxZay: TComboBox;
    EditZay: TEdit;
    Button1: TButton;
    Button2: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    PanelUdal1: TPanel;
    Label4: TLabel;
    Button3: TButton;
    Button4: TButton;
    LabelZay: TLabel;
    sgZay1: TStringGrid;
    BD1: TButton;
    BI1: TButton;
    BU1: TButton;
    PanelSearch: TPanel;
    Button8: TButton;
    Panel1: TPanel;
    Panel2: TPanel;
    sgZay2: TStringGrid;
    BU2: TButton;
    BI2: TButton;
    BD2: TButton;
    PanelDobav2: TPanel;
    Label5: TLabel;
    Label7: TLabel;
    DateZay2: TDateTimePicker;
    Edit1: TEdit;
    Button12: TButton;
    Button13: TButton;
    PanelUdal2: TPanel;
    Label6: TLabel;
    Label8: TLabel;
    Button14: TButton;
    Button15: TButton;
    BZ1: TButton;
    BU3: TButton;
    BI3: TButton;
    BD3: TButton;
    PanelUdal3: TPanel;
    Label9: TLabel;
    Label10: TLabel;
    Button5: TButton;
    Button6: TButton;
    PanelDobav3: TPanel;
    Label11: TLabel;
    Label12: TLabel;
    Edit2: TEdit;
    Button7: TButton;
    Button9: TButton;
    Edit3: TEdit;
    Edit4: TEdit;
    Edit5: TEdit;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Edit6: TEdit;
    Panel3: TPanel;
    Panel4: TPanel;
    editsearch: TEdit;
    sgTerm: TStringGrid;
    M: TMemo;
    Button10: TButton;
    Panel5: TPanel;
    procedure Panel2Click(Sender: TObject);
    procedure Panel1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BD1Click(Sender: TObject);
    procedure BI1Click(Sender: TObject);
    procedure BU1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure BD2Click(Sender: TObject);
    procedure BI2Click(Sender: TObject);
    procedure BU2Click(Sender: TObject);
    procedure Button13Click(Sender: TObject);
    procedure Button15Click(Sender: TObject);
    procedure BD3Click(Sender: TObject);
    procedure BI3Click(Sender: TObject);
    procedure BU3Click(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure sgZay1SelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure sgZay2SelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure sgTermSelectCell(Sender: TObject; ACol, ARow: Integer;
      var CanSelect: Boolean);
    procedure BZ1Click(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button12Click(Sender: TObject);
    procedure Button14Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure editsearchKeyPress(Sender: TObject; var Key: Char);
    procedure Button8Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
    procedure SGMouseMove(Sender: TObject; Shift: TShiftState;
      X, Y: Integer);
    procedure sgZay1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure sgZay2MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure sgTermMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
const
      N=2000;
var
  Form1: TForm1;
  path,username: string;
  ZayDate,ZayTSP,ZayProb,ZaySdel,ZayZakr,ZayOper,
  TermInv,TermSN,TermModel,TermType,TermTSP,
  TSP: array [1..N] of string;
  LastZay,LastTerm,SelectedZay1,SelectedZay2,SelectedTerm,LastTSP,posx,posy: integer;
implementation

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

procedure init;
var i: integer;
begin
  with form1 do
  begin
    for i:=1 to N do
    begin
      sgZay1.Cells[0,i]:=inttostr(i);
      sgZay2.Cells[0,i]:=inttostr(i);
      sgTerm.Cells[0,i]:=inttostr(i);
    end;

    sgZay1.Cells[0,0]:='№ п/п';
    sgZay1.Cells[1,0]:='Дата';
    sgZay1.Cells[2,0]:='ТСП, Адрес';
    sgZay1.Cells[3,0]:='Проблема';
    sgZay1.Cells[4,0]:='Статус';
    sgZay1.Cells[5,0]:='Оператор';

    sgZay2.Cells[0,0]:='№ п/п';
    sgZay2.Cells[1,0]:='Дата';
    sgZay2.Cells[2,0]:='Сделано';

    sgTerm.Cells[0,0]:='№ п/п';
    sgTerm.Cells[1,0]:='Инв. №';
    sgTerm.Cells[2,0]:='Серийный номер';
    sgTerm.Cells[3,0]:='Модель';
    sgTerm.Cells[4,0]:='Тип';
    sgTerm.Cells[5,0]:='ТСП, Адрес';

    username:=GetUserFromWindows;
    path:=ExtractFilePath(Application.ExeName);
    M.Lines.LoadFromFile(path+'Synchronize.file');
    if (M.Text<>'')and(LowString(M.Text)<>LowString(username)) then
    begin
      Panel5.Enabled:=true;
      Panel5.Caption:='Пользователь '+M.Text+' уже работает с программой';
    end else
    begin
      M.Text:=username;
      M.Lines.SaveToFile(path+'Synchronize.file');
      Panel5.Visible:=false;
    end;

    panel2.BorderStyle:=bsSingle;
    panel1.BorderStyle:=bsNone;
    Panel3.Visible:=true;
    Panel4.Visible:=false;

    DateZay1.Date:=date;
    DateZay2.Date:=date;
    SelectedZay1:=1;
    SelectedZay2:=1;
    SelectedTerm:=1;
  end;
end;

////////загрузка Zay//////
procedure LoadZay;
var i,j,len: integer;
    s: string;
begin
  with form1 do
  begin
    for i:=1 to N do
    begin
      ZayDate[i]:='';
      ZayTSP[i]:='';
      ZayProb[i]:='';
      ZayZakr[i]:='';
      ZaySdel[i]:='';
      ZayOper[i]:='';
    end;
    M.Text:='';
    M.Lines.LoadFromFile(path+'Zay.base');
    s:=M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#9 do begin ZayDate[j]:=ZayDate[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin ZayTSP[j]:=ZayTSP[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin ZayProb[j]:=ZayProb[j]+s[i]; i:=i+1; end;i:=i+1;
      ZayZakr[j]:=s[i];i:=i+1;
      while s[i]<>#9 do begin ZayOper[j]:=ZayOper[j]+s[i]; i:=i+1; end;i:=i+1;
      while (s[i]<>#17)or(s[i+1]<>#13)or(s[i+2]<>#10) do begin ZaySdel[j]:=ZaySdel[j]+s[i]; i:=i+1; end;i:=i+3;
      j:=j+1;
    end;
    LastZay:=j-1;
  end;
end;

////////загрузка Term//////
procedure LoadTerm;
var i,j,len: integer;
    s: string;
begin
  with form1 do
  begin
    for i:=1 to N do
    begin
      TermInv[i]:='';
      TermSN[i]:='';
      TermModel[i]:='';
      TermType[i]:='';
      TermTSP[i]:='';
    end;
    M.Text:='';
    M.Lines.LoadFromFile(path+'Term.base');
    s:=M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#9 do begin TermInv[j]:=TermInv[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin TermSN[j]:=TermSN[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin TermModel[j]:=TermModel[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin TermType[j]:=TermType[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#13 do begin TermTSP[j]:=TermTSP[j]+s[i]; i:=i+1; end;i:=i+2;
      j:=j+1;
    end;
    LastTerm:=j-1;
  end;
end;

////////загрузка TSP//////
procedure LoadTSP;
var i,j,len: integer;
    s: string;
begin
  with form1 do
  begin
    for i:=1 to N do
    begin
      TSP[i]:='';
    end;
    M.Text:='';
    M.Lines.LoadFromFile(path+'TSP.base');
    s:=M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#13 do begin TSP[j]:=TSP[j]+s[i]; i:=i+1; end;i:=i+2;
      j:=j+1;
    end;
    LastTSP:=j-1;
  end;
end;

/////////сохранение Zay//////////
procedure SaveZay;
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to LastZay do
    begin
      form1.M.Lines.Add(ZayDate[i]+#9+ZayTSP[i]+#9+ZayProb[i]+#9+ZayZakr[i]+#9+ZayOper[i]);
      form1.M.Lines.Add(ZaySdel[i]+#17);
    end;
    form1.M.Lines.SaveToFile(path+'Zay.base');
end;

/////////сохранение Term//////////
procedure SaveTerm;
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to LastTerm do
    begin
      form1.M.Lines.Add(TermInv[i]+#9+TermSN[i]+#9+TermModel[i]+#9+TermType[i]+#9+TermTSP[i]);
    end;
    form1.M.Lines.SaveToFile(path+'Term.base');
end;

/////////сохранение TSP//////////
procedure SaveTSP;
var i: integer;
begin
    form1.M.Text:='';
    for i:=1 to LastTSP do
    begin
      form1.M.Lines.Add(TSP[i]);
    end;
    form1.M.Lines.SaveToFile(path+'TSP.base');
end;

////////заполнение таблицы Zay1/////////
procedure FillZay1;
var i: integer;
begin
  with form1 do
  begin
    sgZay1.RowCount:=2;
    for i:=1 to LastZay do
    begin
      sgZay1.Cells[1,i]:=ZayDate[i];
      sgZay1.Cells[2,i]:=ZayTSP[i];
      sgZay1.Cells[3,i]:=ZayProb[i];
      sgZay1.Cells[4,i]:=ZayZakr[i];
      sgZay1.Cells[5,i]:=ZayOper[i];
      sgZay1.Cells[6,i]:=inttostr(i);
    end;
    if LastZay>1 then sgZay1.RowCount:=i;
  end;
end;

////////заполнение таблицы Zay2/////////
procedure FillZay2(num:integer);
var i,j,len: integer;
    s: string;
begin
  with form1 do
  begin
    if sgZay1.Cells[6,num]<>'' then
    begin
      num:=strtoint(sgZay1.Cells[6,num]);
      if ZaySdel[num]<>'' then
      begin
        s:=ZaySdel[num];
        len:=length(s);
        j:=1; i:=1;
        sgZay2.RowCount:=2;
        while i<=len do
        begin
          sgZay2.Cells[1,j]:='';
          sgZay2.Cells[2,j]:='';
          while s[i]<>#9 do begin sgZay2.Cells[1,j]:=sgZay2.Cells[1,j]+s[i]; i:=i+1; end;i:=i+1;
          while (s[i]<>#13)and(i<=len) do begin sgZay2.Cells[2,j]:=sgZay2.Cells[2,j]+s[i]; i:=i+1; end;i:=i+2;
          j:=j+1;
        end;
        if j>1 then sgZay2.RowCount:=j;
      end else
      begin
        sgZay2.Cells[1,1]:='';
        sgZay2.Cells[2,1]:='';
        sgZay2.RowCount:=2;
      end;
    end else
    begin
      sgZay2.Cells[1,1]:='';
      sgZay2.Cells[2,1]:='';
      sgZay2.RowCount:=2;
    end;
  end;
end;

////////заполнение таблицы Term/////////
procedure FillTerm;
var i: integer;
begin
  with form1 do
  begin
    sgTerm.RowCount:=2;
    for i:=1 to LastTerm do
    begin
      sgTerm.Cells[1,i]:=TermInv[i];
      sgTerm.Cells[2,i]:=TermSN[i];
      sgTerm.Cells[3,i]:=TermModel[i];
      sgTerm.Cells[4,i]:=TermType[i];
      sgTerm.Cells[5,i]:=TermTSP[i];
      sgTerm.Cells[6,i]:=inttostr(i);
    end;
    if LastTerm>1 then sgTerm.RowCount:=i;
  end;
end;

////////заполнение комбобоксов "ТСП, Адрес"/////////
procedure FillTSP;
var i: integer;
begin
  with form1 do
  begin
    ComboBoxZay.Items.Clear;
    for i:=1 to LastTSP do
    ComboBoxZay.Items.Add(TSP[i]);
    ComboBoxZay.Text:=ComboBoxZay.Items.Strings[1];
    if LastTSP>25 then ComboBoxZay.DropDownCount:=25 else ComboBoxZay.DropDownCount:=LastTSP;
  end;
end;

////////допустимость активности кнопок добавить изменить удалить и т.д.//////////
procedure enablebuttons;
begin
  with form1 do
  begin
    if (sgZay2.Cells[1,SelectedZay2]='')and(sgZay2.Cells[2,SelectedZay2]='') then
    begin
      BU2.Enabled:=false;
      BI2.Enabled:=false;
    end else
    begin
      BU2.Enabled:=true;
      BI2.Enabled:=true;
    end;

    if sgZay1.Cells[6,SelectedZay1]<>'' then
    begin
      BU1.Enabled:=true;
      BI1.Enabled:=true;
      BZ1.Enabled:=true;
      BD2.Enabled:=true;
      if sgZay1.Cells[4,SelectedZay1]='-' then BZ1.Caption:='Закрыть заявку' else BZ1.Caption:='Открыть заявку';
    end else
    begin
      BU1.Enabled:=false;
      BI1.Enabled:=false;
      BZ1.Enabled:=false;
      BD2.Enabled:=false;
    end;

    if sgTerm.Cells[6,SelectedTerm]<>'' then
    begin
      BU3.Enabled:=true;
      BI3.Enabled:=true;
    end else
    begin
      BU3.Enabled:=false;
      BI3.Enabled:=false;
    end;
  end;
end;

////////////поиск по ключевым словам
procedure search(s: string);
var i,j,max,max1,max2,count: integer;
    searchindex: array [1..N] of integer;
    bl: boolean;
    keys: array [1..100] of string;
begin
  for i:=1 to N do searchindex[i]:=0;
  for i:=1 to 100 do keys[i]:='';
  with form1 do
  begin

    i:=1;
    if panel3.Visible then
    begin
      while i<sgZay1.RowCount do
      begin
        sgZay1.Cells[1,i]:='';
        sgZay1.Cells[2,i]:='';
        sgZay1.Cells[3,i]:='';
        sgZay1.Cells[4,i]:='';
        sgZay1.Cells[5,i]:='';
        sgZay1.Cells[6,i]:='';
        i:=i+1;
      end;
      sgZay1.RowCount:=2;
    end else
    if panel4.Visible then
    begin
      while i<sgTerm.RowCount do
      begin
        sgTerm.Cells[1,i]:='';
        sgTerm.Cells[2,i]:='';
        sgTerm.Cells[3,i]:='';
        sgTerm.Cells[4,i]:='';
        sgTerm.Cells[5,i]:='';
        sgTerm.Cells[6,i]:='';
        i:=i+1;
      end;
      sgTerm.RowCount:=2;
    end;

    if s<>'' then //begin if s<>''
    begin

      bl:=true;
      max:=0;
      max1:=0;
      max2:=0;
      count:=1;
      s:=LowString(s);

      for i:=1 to length(s) do
      begin
        if (s[i]=' ') then
        begin
          if bl then
          begin
            count:=count+1;
            bl:=false;
          end;
        end else bl:=true;
        if bl then keys[count]:= keys[count] + s[i];
      end;

    if panel3.Visible then
    begin
      for i:=1 to LastZay do
      for j:=1 to count do
      begin
        if (strpos(pchar(LowString(ZayDate[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(ZayTSP[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(ZayProb[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(ZaySdel[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;

        if searchindex[i]>=max then max:=searchindex[i] else
        if searchindex[i]>=max1 then max1:=searchindex[i] else
        if searchindex[i]>=max2 then max2:=searchindex[i];
      end;
    end else
    if panel4.Visible then
    begin
      for i:=1 to LastTerm do
      for j:=1 to count do
      begin
        if (strpos(pchar(LowString(TermInv[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(TermSN[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(TermModel[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(TermType[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;
        if (strpos(pchar(LowString(TermTSP[i])),pchar(keys[j]))<>nil) then
        searchindex[i]:=searchindex[i]+1;

        if searchindex[i]>=max then max:=searchindex[i] else
        if searchindex[i]>=max1 then max1:=searchindex[i] else
        if searchindex[i]>=max2 then max2:=searchindex[i];
      end;
    end;

  bl:=false;
  if max<>0 then
  begin
    bl:=true;
    if panel3.Visible then
    begin
      for i:=1 to LastZay do
      if searchindex[i]=max then
        begin
          sgZay1.Cells[1,sgZay1.RowCount-1]:=ZayDate[i];
          sgZay1.Cells[2,sgZay1.RowCount-1]:=ZayTSP[i];
          sgZay1.Cells[3,sgZay1.RowCount-1]:=ZayProb[i];
          sgZay1.Cells[4,sgZay1.RowCount-1]:=ZayZakr[i];
          sgZay1.Cells[5,sgZay1.RowCount-1]:=ZayOper[i];
          sgZay1.Cells[6,sgZay1.RowCount-1]:=inttostr(i);
          sgZay1.RowCount:=sgZay1.RowCount+1;
        end;
    end else
    if panel4.Visible then
    begin
      for i:=1 to LastTerm do
      if searchindex[i]=max then
        begin
          sgTerm.Cells[1,sgTerm.RowCount-1]:=TermInv[i];
          sgTerm.Cells[2,sgTerm.RowCount-1]:=TermSN[i];
          sgTerm.Cells[3,sgTerm.RowCount-1]:=TermModel[i];
          sgTerm.Cells[4,sgTerm.RowCount-1]:=TermType[i];
          sgTerm.Cells[5,sgTerm.RowCount-1]:=TermTSP[i];
          sgTerm.Cells[6,sgTerm.RowCount-1]:=inttostr(i);
          sgTerm.RowCount:=sgTerm.RowCount+1;
        end;
    end;
    if max1<>0 then
    begin
      if panel3.Visible then
      begin
        for i:=1 to LastZay do
          if searchindex[i]=max1 then
          begin
            sgZay1.Cells[1,sgZay1.RowCount-1]:=ZayDate[i];
            sgZay1.Cells[2,sgZay1.RowCount-1]:=ZayTSP[i];
            sgZay1.Cells[3,sgZay1.RowCount-1]:=ZayProb[i];
            sgZay1.Cells[4,sgZay1.RowCount-1]:=ZayZakr[i];
            sgZay1.Cells[5,sgZay1.RowCount-1]:=ZayOper[i];
            sgZay1.Cells[6,sgZay1.RowCount-1]:=inttostr(i);
            sgZay1.RowCount:=sgZay1.RowCount+1;
          end;
      end else
      if panel4.Visible then
      begin
        for i:=1 to LastTerm do
          if searchindex[i]=max1 then
          begin
            sgTerm.Cells[1,sgTerm.RowCount-1]:=TermInv[i];
            sgTerm.Cells[2,sgTerm.RowCount-1]:=TermSN[i];
            sgTerm.Cells[3,sgTerm.RowCount-1]:=TermModel[i];
            sgTerm.Cells[4,sgTerm.RowCount-1]:=TermType[i];
            sgTerm.Cells[5,sgTerm.RowCount-1]:=TermTSP[i];
            sgTerm.Cells[6,sgTerm.RowCount-1]:=inttostr(i);
            sgTerm.RowCount:=sgTerm.RowCount+1;
          end;
      end;

      if max2<>0 then
      begin
        if panel3.Visible then
        begin
          for i:=1 to LastZay do
            if searchindex[i]=max2 then
            begin
              sgZay1.Cells[1,sgZay1.RowCount-1]:=ZayDate[i];
              sgZay1.Cells[2,sgZay1.RowCount-1]:=ZayTSP[i];
              sgZay1.Cells[3,sgZay1.RowCount-1]:=ZayProb[i];
              sgZay1.Cells[4,sgZay1.RowCount-1]:=ZayZakr[i];
              sgZay1.Cells[5,sgZay1.RowCount-1]:=ZayOper[i];
              sgZay1.Cells[6,sgZay1.RowCount-1]:=inttostr(i);
              sgZay1.RowCount:=sgZay1.RowCount+1;
            end;
        end else
        if panel4.Visible then
        begin
          for i:=1 to LastTerm do
            if searchindex[i]=max2 then
            begin
              sgTerm.Cells[1,sgTerm.RowCount-1]:=TermInv[i];
              sgTerm.Cells[2,sgTerm.RowCount-1]:=TermSN[i];
              sgTerm.Cells[3,sgTerm.RowCount-1]:=TermModel[i];
              sgTerm.Cells[4,sgTerm.RowCount-1]:=TermType[i];
              sgTerm.Cells[5,sgTerm.RowCount-1]:=TermTSP[i];
              sgTerm.Cells[6,sgTerm.RowCount-1]:=inttostr(i);
              sgTerm.RowCount:=sgTerm.RowCount+1;
            end;
        end;
      end;
    end;//end if max1<>0
    if (panel3.Visible)and(sgZay1.RowCount>2) then
    sgZay1.RowCount:=sgZay1.RowCount-1
    else
    if (panel4.Visible)and(sgTerm.RowCount>2) then
    sgTerm.RowCount:=sgTerm.RowCount-1;
  end;//end if max<>0
  end; //end if s<>''
  if panel3.Visible then
  begin
    SelectedZay1:=1;
    FillZay2(1);
  end;
  enablebuttons;
  end; // end with form1 do
end;

////////всё неактивно//////////
procedure allfalse(bl: boolean);
begin
  with form1 do
  begin
    editsearch.Enabled:=bl;
    Button8.Enabled:=bl;
    panel2.Enabled:=bl;
    panel1.Enabled:=bl;
    sgZay1.Enabled:=bl;
    sgZay2.Enabled:=bl;
    sgTerm.Enabled:=bl;
    BD1.Enabled:=bl;
    BI1.Enabled:=bl;
    BU1.Enabled:=bl;
    BZ1.Enabled:=bl;
    BD2.Enabled:=bl;
    BI2.Enabled:=bl;
    BU2.Enabled:=bl;
    BD3.Enabled:=bl;
    BI3.Enabled:=bl;
    BU3.Enabled:=bl;
    if bl then enablebuttons;
  end;
end;

////////переключение между таблицами/////////
procedure TForm1.Panel2Click(Sender: TObject);
begin
  if panel2.BorderStyle=bsNone then
  begin
    panel2.BorderStyle:=bsSingle;
    panel1.BorderStyle:=bsNone;
    Panel3.Visible:=true;
    Panel4.Visible:=false;
  end;
end;
procedure TForm1.Panel1Click(Sender: TObject);
begin
  if panel1.BorderStyle=bsNone then
  begin
    panel1.BorderStyle:=bsSingle;
    panel2.BorderStyle:=bsNone;
    Panel4.Visible:=true;
    Panel3.Visible:=false;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
 init;
 LoadZay;
 LoadTerm;
 LoadTSP;
 FillZay1;
 FillTerm;
 FillTSP; M.Text:=ComboBoxZay.Items.CommaText;
end;
/////////кнопки добавления удаления изменения 1/////////
procedure TForm1.BD1Click(Sender: TObject);
begin
  DateZay1.Date:=date;
  ComboBoxZay.Text:=sgZay1.cells[2,SelectedZay1];
  EditZay.Text:=sgZay1.cells[3,SelectedZay1];

  PanelDobav1.Visible:=true;
  Button1.Caption:=BD1.Caption;
  allfalse(false);
end;
procedure TForm1.BI1Click(Sender: TObject);
begin
  DateZay1.Date:=strtodate(sgZay1.cells[1,SelectedZay1]);
  ComboBoxZay.Text:=sgZay1.cells[2,SelectedZay1];
  EditZay.Text:=sgZay1.cells[3,SelectedZay1];

  PanelDobav1.Visible:=true;
  Button1.Caption:=BI1.Caption;  
  allfalse(false);
end;
procedure TForm1.BU1Click(Sender: TObject);
begin
  LabelZay.Caption:=sgZay1.cells[1,SelectedZay1]+#10+#13+
  sgZay1.cells[2,SelectedZay1]+#10+#13+sgZay1.cells[3,SelectedZay1];

  PanelUdal1.Visible:=true;  
  allfalse(false);
end;
procedure TForm1.Button2Click(Sender: TObject);
begin
  PanelDobav1.Visible:=false;  
  allfalse(true);
end;
procedure TForm1.Button4Click(Sender: TObject);
begin
  PanelUdal1.Visible:=false; 
  allfalse(true);
end;
/////////кнопки добавления удаления изменения 2/////////
procedure TForm1.BD2Click(Sender: TObject);
begin  
  DateZay2.Date:=date;
  Edit1.Text:='';

  PanelDobav2.Visible:=true;
  Button12.Caption:=BD2.Caption;   
  allfalse(false);
end;
procedure TForm1.BI2Click(Sender: TObject);
begin
  DateZay2.Date:=strtodate(sgZay2.cells[1,SelectedZay2]);
  Edit1.Text:=sgZay2.cells[2,SelectedZay2];

  PanelDobav2.Visible:=true;
  Button12.Caption:=BI2.Caption;    
  allfalse(false);
end;
procedure TForm1.BU2Click(Sender: TObject);
begin
  Label8.Caption:=sgZay2.cells[1,SelectedZay2]+#10+#13+
  sgZay2.cells[2,SelectedZay2];

  PanelUdal2.Visible:=true; 
  allfalse(false);
end;
procedure TForm1.Button13Click(Sender: TObject);
begin
  PanelDobav2.Visible:=false;  
  allfalse(true);
end;
procedure TForm1.Button15Click(Sender: TObject);
begin
  PanelUdal2.Visible:=false;
  allfalse(true);
end;
/////////кнопки добавления удаления изменения 3/////////
procedure TForm1.BD3Click(Sender: TObject);
begin
  Edit2.Text:=sgTerm.Cells[1,SelectedTerm];
  Edit3.Text:=sgTerm.Cells[2,SelectedTerm];
  Edit4.Text:=sgTerm.Cells[3,SelectedTerm];
  Edit5.Text:=sgTerm.Cells[4,SelectedTerm];
  Edit6.Text:=sgTerm.Cells[5,SelectedTerm];

  PanelDobav3.Visible:=true;
  Button7.Caption:=BD3.Caption;  
  allfalse(false);
end;
procedure TForm1.BI3Click(Sender: TObject);
begin
  Edit2.Text:=sgTerm.Cells[1,SelectedTerm];
  Edit3.Text:=sgTerm.Cells[2,SelectedTerm];
  Edit4.Text:=sgTerm.Cells[3,SelectedTerm];
  Edit5.Text:=sgTerm.Cells[4,SelectedTerm];
  Edit6.Text:=sgTerm.Cells[5,SelectedTerm];

  PanelDobav3.Visible:=true;
  Button7.Caption:=BI3.Caption;  
  allfalse(false);
end;
procedure TForm1.BU3Click(Sender: TObject);
begin
  Label10.Caption:=sgTerm.cells[1,SelectedTerm]+#9+sgTerm.cells[2,SelectedTerm]+#9+
  sgTerm.cells[3,SelectedTerm]+#9+sgTerm.cells[4,SelectedTerm]+#10+#13+
  sgTerm.cells[5,SelectedTerm];

  PanelUdal3.Visible:=true;  
  allfalse(false);
end;
procedure TForm1.Button9Click(Sender: TObject);
begin
  PanelDobav3.Visible:=false; 
  allfalse(true);
end;
procedure TForm1.Button6Click(Sender: TObject);
begin
  PanelUdal3.Visible:=false; 
  allfalse(true);
end;

procedure TForm1.sgZay1SelectCell(Sender: TObject; ACol, ARow: Integer;
  var CanSelect: Boolean);
begin
  SelectedZay1:=ARow;
  if sgZay1.Cells[5,ARow]<>'' then
  begin
    BU1.Enabled:=true;
    BI1.Enabled:=true;
    BZ1.Enabled:=true;
    BD2.Enabled:=true;
    if sgZay1.Cells[4,ARow]='-' then BZ1.Caption:='Закрыть заявку' else BZ1.Caption:='Открыть заявку';
  end else
  begin
    BU1.Enabled:=false;
    BI1.Enabled:=false;
    BZ1.Enabled:=false;
    BD2.Enabled:=false;
  end;
  FillZay2(ARow);
  BU2.Enabled:=false;
  BI2.Enabled:=false;
end;

procedure TForm1.sgZay2SelectCell(Sender: TObject; ACol, ARow: Integer;
  var CanSelect: Boolean);
begin
  if (sgZay2.Cells[1,ARow]='')and(sgZay2.Cells[2,ARow]='') then
  begin
    BU2.Enabled:=false;
    BI2.Enabled:=false;
  end else
  begin
    SelectedZay2:=ARow;
    BU2.Enabled:=true;
    BI2.Enabled:=true;
  end;
end;

procedure TForm1.sgTermSelectCell(Sender: TObject; ACol, ARow: Integer;
  var CanSelect: Boolean);
begin
  if sgTerm.Cells[6,ARow]<>'' then
  begin
    SelectedTerm:=ARow;
    BU3.Enabled:=true;
    BI3.Enabled:=true;
  end else
  begin
    BU3.Enabled:=false;
    BI3.Enabled:=false;
  end;
end;

procedure TForm1.BZ1Click(Sender: TObject);
var n: integer;
begin
  n:=strtoint(sgZay1.cells[5,SelectedZay1]);
  if BZ1.Caption='Закрыть заявку' then
  begin
    sgZay1.cells[4,SelectedZay1]:='+';
    ZayZakr[n]:='+';
    BZ1.Caption:='Открыть заявку';
  end else
  begin
    sgZay1.cells[4,SelectedZay1]:='-';
    ZayZakr[n]:='-';
    BZ1.Caption:='Закрыть заявку';
  end;
  SaveZay;
end;

procedure TForm1.Button1Click(Sender: TObject);
var n: integer;
begin
  if Button1.Caption='Добавить' then
  begin
    if LastZay<>0 then sgZay1.RowCount:=sgZay1.RowCount+1;
    LastZay:=LastZay+1;
    sgZay1.cells[1,sgZay1.RowCount-1]:=datetostr(DateZay1.Date);
    sgZay1.cells[2,sgZay1.RowCount-1]:=ComboBoxZay.Text;
    sgZay1.cells[3,sgZay1.RowCount-1]:=EditZay.Text;
    sgZay1.cells[4,sgZay1.RowCount-1]:='-';
    sgZay1.cells[5,sgZay1.RowCount-1]:=inttostr(LastZay);
    ZayDate[LastZay]:=datetostr(DateZay1.Date);
    ZayTSP[LastZay] :=ComboBoxZay.Text;
    ZayProb[LastZay]:=EditZay.Text;
    ZayZakr[LastZay]:='-';
    ZaySdel[LastZay]:='';
  end else
  if Button1.Caption='Изменить' then
  begin
    n:=strtoint(sgZay1.cells[5,SelectedZay1]);
    sgZay1.cells[1,SelectedZay1]:=datetostr(DateZay1.Date);
    sgZay1.cells[2,SelectedZay1]:=ComboBoxZay.Text;
    sgZay1.cells[3,SelectedZay1]:=EditZay.Text;
    ZayDate[n]:=datetostr(DateZay1.Date);
    ZayTSP[n]:=ComboBoxZay.Text;
    ZayProb[n]:=EditZay.Text;
  end;
  SaveZay;
  PanelDobav1.Visible:=false;
  allfalse(true);
end;

procedure TForm1.Button3Click(Sender: TObject);
var i,n: integer;
begin
    n:=strtoint(sgZay1.cells[5,SelectedZay1]);
    for i:=SelectedZay1 to sgZay1.RowCount-2 do
    begin
      sgZay1.cells[1,i]:=sgZay1.cells[1,i+1];
      sgZay1.cells[2,i]:=sgZay1.cells[2,i+1];
      sgZay1.cells[3,i]:=sgZay1.cells[3,i+1];
      sgZay1.cells[4,i]:=sgZay1.cells[4,i+1];
      if strtoint(sgZay1.cells[5,i+1])>n then
      sgZay1.cells[5,i]:=inttostr(strtoint(sgZay1.cells[5,i+1])-1)
      else
      sgZay1.cells[5,i]:=sgZay1.cells[5,i+1];
    end;
    sgZay1.cells[1,sgZay1.RowCount-1]:='';
    sgZay1.cells[2,sgZay1.RowCount-1]:='';
    sgZay1.cells[3,sgZay1.RowCount-1]:='';
    sgZay1.cells[4,sgZay1.RowCount-1]:='';
    sgZay1.cells[5,sgZay1.RowCount-1]:='';

    if sgZay1.RowCount>2 then sgZay1.RowCount:=sgZay1.RowCount-1;

    for i:=n to LastZay-1 do
    begin
      ZayDate[i]:=ZayDate[i+1];
      ZayTSP[i] :=ZayTSP[i+1];
      ZayProb[i]:=ZayProb[i+1];
      ZayZakr[i]:=ZayZakr[i+1];
      ZaySdel[i]:=ZaySdel[i+1];
    end;
    ZayDate[LastZay]:='';
    ZayTSP[LastZay] :='';
    ZayProb[LastZay]:='';
    ZayZakr[LastZay]:='';
    ZaySdel[LastZay]:='';

    LastZay:=LastZay-1;

    SaveZay;
    FillZay2(SelectedZay1);
    PanelUdal1.Visible:=false;
  allfalse(true);
end;

procedure TForm1.Button12Click(Sender: TObject);
var i,n: integer;
begin
  n:=strtoint(sgZay1.cells[5,SelectedZay1]);
  if Button12.Caption='Добавить' then
  begin
    if ZaySdel[n]<>'' then sgZay2.RowCount:=sgZay2.RowCount+1;
    sgZay2.cells[1,sgZay2.RowCount-1]:=datetostr(DateZay2.Date);
    sgZay2.cells[2,sgZay2.RowCount-1]:=Edit1.Text;
    if ZaySdel[n]<>'' then
    ZaySdel[n]:=ZaySdel[n]+#13+#10+datetostr(DateZay2.Date)+#9+Edit1.Text
    else
    ZaySdel[n]:=datetostr(DateZay2.Date)+#9+Edit1.Text;
  end else
  if Button12.Caption='Изменить' then
  begin
    sgZay2.cells[1,SelectedZay2]:=datetostr(DateZay2.Date);
    sgZay2.cells[2,SelectedZay2]:=Edit1.Text;
    for i:=1 to sgZay2.RowCount-1 do
    if i=1 then
    ZaySdel[n]:=sgZay2.cells[1,i]+#9+sgZay2.cells[2,i]
    else
    ZaySdel[n]:=ZaySdel[n]+#13+#10+sgZay2.cells[1,i]+#9+sgZay2.cells[2,i];
  end;
  SaveZay;
  PanelDobav2.Visible:=false;
  allfalse(true);
end;

procedure TForm1.Button14Click(Sender: TObject);
var i,n: integer;
begin
    n:=strtoint(sgZay1.cells[5,SelectedZay1]);
    sgZay2.cells[1,SelectedZay2]:='';
    sgZay2.cells[2,SelectedZay2]:='';
    for i:=SelectedZay2 to sgZay2.RowCount-2 do
    begin
      sgZay2.cells[1,i]:=sgZay2.cells[1,i+1];
      sgZay2.cells[2,i]:=sgZay2.cells[2,i+1];
    end;
    if sgZay2.RowCount>2 then sgZay2.RowCount:=sgZay2.RowCount-1;
    if (sgZay2.cells[1,i]<>'')and(sgZay2.cells[2,i]<>'') then
      for i:=1 to sgZay2.RowCount-1 do
      if i=1 then
      ZaySdel[n]:=sgZay2.cells[1,i]+#9+sgZay2.cells[2,i]
      else
      ZaySdel[n]:=ZaySdel[n]+#13+#10+sgZay2.cells[1,i]+#9+sgZay2.cells[2,i]
    else ZaySdel[n]:='';

    SaveZay;
    PanelUdal2.Visible:=false;
  allfalse(true);
end;

procedure TForm1.Button7Click(Sender: TObject);
var n: integer;
begin
  if Button7.Caption='Добавить' then
  begin
    if LastTerm<>0 then sgTerm.RowCount:=sgTerm.RowCount+1;
    LastTerm:=LastTerm+1;
    sgTerm.cells[1,sgTerm.RowCount-1]:=Edit2.Text;
    sgTerm.cells[2,sgTerm.RowCount-1]:=Edit3.Text;
    sgTerm.cells[3,sgTerm.RowCount-1]:=Edit4.Text;
    sgTerm.cells[4,sgTerm.RowCount-1]:=Edit5.Text;
    sgTerm.cells[5,sgTerm.RowCount-1]:=Edit6.Text;
    sgTerm.cells[6,sgTerm.RowCount-1]:=inttostr(LastTerm);
    TermInv[LastTerm]:=Edit2.Text;
    TermSN[LastTerm] :=Edit3.Text;
    TermModel[LastTerm]:=Edit4.Text;
    TermType[LastTerm]:=Edit5.Text;
    TermTSP[LastTerm]:=Edit6.Text;

  end else
  if Button7.Caption='Изменить' then
  begin
    n:=strtoint(sgTerm.cells[6,SelectedTerm]);
    sgTerm.cells[1,SelectedTerm]:=Edit2.Text;
    sgTerm.cells[2,SelectedTerm]:=Edit3.Text;
    sgTerm.cells[3,SelectedTerm]:=Edit4.Text;
    sgTerm.cells[4,SelectedTerm]:=Edit5.Text;
    sgTerm.cells[5,SelectedTerm]:=Edit6.Text;
    TermInv[n]:=Edit2.Text;
    TermSN[n] :=Edit3.Text;
    TermModel[n]:=Edit4.Text;
    TermType[n]:=Edit5.Text;
    TermTSP[n]:=Edit6.Text;
  end;

  M.Text:=ComboBoxZay.Items.CommaText;
  if (strpos(pchar(LowString(M.Text)),pchar(LowString(Edit6.Text)))=nil) then
  begin
    LastTSP:=LastTSP+1;
    TSP[LastTSP]:=Edit6.Text;
    FillTSP;
    SaveTSP;
  end;

  SaveTerm;
  PanelDobav3.Visible:=false;
  allfalse(true);
end;

procedure TForm1.Button5Click(Sender: TObject);
var i,n: integer;
    tmptsp: string;
    bl: boolean;
begin
    n:=strtoint(sgTerm.cells[6,SelectedTerm]);
    for i:=SelectedTerm to sgTerm.RowCount-2 do
    begin
      sgTerm.cells[1,i]:=sgTerm.cells[1,i+1];
      sgTerm.cells[2,i]:=sgTerm.cells[2,i+1];
      sgTerm.cells[3,i]:=sgTerm.cells[3,i+1];
      sgTerm.cells[4,i]:=sgTerm.cells[4,i+1];
      sgTerm.cells[5,i]:=sgTerm.cells[5,i+1];
      if strtoint(sgTerm.cells[6,i+1])>n then
      sgTerm.cells[6,i]:=inttostr(strtoint(sgTerm.cells[6,i+1])-1)
      else
      sgTerm.cells[6,i]:=sgTerm.cells[6,i+1];
    end;
    sgTerm.cells[1,sgTerm.RowCount-1]:='';
    sgTerm.cells[2,sgTerm.RowCount-1]:='';
    sgTerm.cells[3,sgTerm.RowCount-1]:='';
    sgTerm.cells[4,sgTerm.RowCount-1]:='';
    sgTerm.cells[5,sgTerm.RowCount-1]:='';
    sgTerm.cells[6,sgTerm.RowCount-1]:='';

    if sgTerm.RowCount>2 then sgTerm.RowCount:=sgTerm.RowCount-1;

    tmptsp:=TermTSP[n];

    for i:=n to LastTerm-1 do
    begin
      TermInv[i]:=TermInv[i+1];
      TermSN[i] :=TermSN[i+1];
      TermModel[i]:=TermModel[i+1];
      TermType[i]:=TermType[i+1];
      TermTSP[i]:=TermTSP[i+1];
    end;
    TermInv[LastTerm]:='';
    TermSN[LastTerm] :='';
    TermModel[LastTerm]:='';
    TermType[LastTerm]:='';
    TermTSP[LastTerm]:='';

    LastTerm:=LastTerm-1;

    bl:=true;
    for i:=1 to LastTerm do
    begin
      if tmptsp=TermTSP[i] then bl:=false;
      break;
    end;
    if bl then
    begin
      for i:=1 to LastTSP do
      if TSP[i]=tmptsp then break;
      for i:=i to LastTSP-1 do TSP[i]:=TSP[i+1];
      TSP[LastTSP]:='';
      LastTSP:=LastTSP-1;
      FillTSP;
      SaveTSP;
    end;

    SaveTerm;
    PanelUdal3.Visible:=false;
  allfalse(true);
end;

procedure TForm1.editsearchKeyPress(Sender: TObject; var Key: Char);
begin
  if key=#13 then
  search(editsearch.Text);
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  search(editsearch.Text);
end;

procedure TForm1.Button10Click(Sender: TObject);
begin
  if panel3.Visible then
  FillZay1
  else
  FillTerm;
end;

//сортировка//
procedure TForm1.SGMouseMove(Sender: TObject; Shift: TShiftState;
  X, Y: Integer);
begin
  posx:=x;
  posy:=y;
end;

procedure TForm1.sgZay1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var temp,i,j,k: integer;
    bl: boolean;
    p: string;
begin
        if (posy<sgZay1.RowHeights[0]) then
        begin
          i:=0;
          temp:=sgZay1.ColWidths[0];
          while (i<sgZay1.ColCount)and not((posx>temp-sgZay1.ColWidths[i])and(posx<=temp)) do
          begin
            i:=i+1;
            temp:=temp+sgZay1.ColWidths[i];
          end;
        end;
        if (i>0)and(i<sgZay1.ColCount) then
        begin
          bl:=true;
          while bl do
          begin
            bl:=false;
            for j:=1 to sgZay1.RowCount-2 do
            if i=1 then
            begin
              if strtodate(sgZay1.Cells[i,j])>strtodate(sgZay1.Cells[i,j+1]) then
              begin
                bl:=true;
                for k:=1 to sgZay1.ColCount do
                begin
                  p:=sgZay1.Cells[k,j];sgZay1.Cells[k,j]:=sgZay1.Cells[k,j+1];sgZay1.Cells[k,j+1]:=p;
                end;
              end;
            end else
            begin
              if ((sgZay1.Cells[i,j]='')and(sgZay1.Cells[i,j+1]<>''))or
              ((sgZay1.Cells[i,j]<>'')and(sgZay1.Cells[i,j+1]<>'')and(sgZay1.Cells[i,j]>sgZay1.Cells[i,j+1])) then
              begin
                bl:=true;
                for k:=1 to sgZay1.ColCount do
                begin
                  p:=sgZay1.Cells[k,j];sgZay1.Cells[k,j]:=sgZay1.Cells[k,j+1];sgZay1.Cells[k,j+1]:=p;
                end;
              end;
            end;
          end;
        end;
end;

procedure TForm1.sgZay2MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var temp,i,j,k: integer;
    bl: boolean;
    p: string;
begin
        if (posy<sgZay2.RowHeights[0]) then
        begin
          i:=0;
          temp:=sgZay2.ColWidths[0];
          while (i<sgZay2.ColCount)and not((posx>temp-sgZay2.ColWidths[i])and(posx<=temp)) do
          begin
            i:=i+1;
            temp:=temp+sgZay2.ColWidths[i];
          end;
        end;
        if (i>0)and(i<sgZay2.ColCount) then
        begin
          bl:=true;
          while bl do
          begin
            bl:=false;
            for j:=1 to sgZay2.RowCount-2 do
            if i=1 then
            begin
              if strtodate(sgZay2.Cells[i,j])>strtodate(sgZay2.Cells[i,j+1]) then
               begin
                bl:=true;
                for k:=1 to sgZay2.ColCount-1 do
                begin
                  p:=sgZay2.Cells[k,j];sgZay2.Cells[k,j]:=sgZay2.Cells[k,j+1];sgZay2.Cells[k,j+1]:=p;
                end;
              end;
            end else
            begin
              if ((sgZay2.Cells[i,j]='')and(sgZay2.Cells[i,j+1]<>''))or
              ((sgZay2.Cells[i,j]<>'')and(sgZay2.Cells[i,j+1]<>'')and(sgZay2.Cells[i,j]>sgZay2.Cells[i,j+1])) then
              begin
                bl:=true;
                for k:=1 to sgZay2.ColCount-1 do
                begin
                  p:=sgZay2.Cells[k,j];sgZay2.Cells[k,j]:=sgZay2.Cells[k,j+1];sgZay2.Cells[k,j+1]:=p;
                end;
              end;
            end;
          end;
        end;
end;

procedure TForm1.sgTermMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
var temp,i,j,k: integer;
    bl: boolean;
    p: string;
begin
        if (posy<sgTerm.RowHeights[0]) then
        begin
          i:=0;
          temp:=sgTerm.ColWidths[0];
          while (i<sgTerm.ColCount)and not((posx>temp-sgTerm.ColWidths[i])and(posx<=temp)) do
          begin
            i:=i+1;
            temp:=temp+sgTerm.ColWidths[i];
          end;
        end;
        if (i>0)and(i<sgTerm.ColCount) then
        begin
          bl:=true;
          while bl do
          begin
            bl:=false;
            for j:=1 to sgTerm.RowCount-2 do
            if ((sgTerm.Cells[i,j]='')and(sgTerm.Cells[i,j+1]<>''))or
            ((sgTerm.Cells[i,j]<>'')and(sgTerm.Cells[i,j+1]<>'')and(sgTerm.Cells[i,j]>sgTerm.Cells[i,j+1])) then
            begin
              bl:=true;
              for k:=1 to sgTerm.ColCount-1 do
              begin
                p:=sgTerm.Cells[k,j];sgTerm.Cells[k,j]:=sgTerm.Cells[k,j+1];sgTerm.Cells[k,j+1]:=p;
              end;
            end;
          end;
        end;
end;

end.
