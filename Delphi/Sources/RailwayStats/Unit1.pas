unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Grids, StdCtrls, ExtCtrls, jpeg;

type
  TForm1 = class(TForm)
    M: TMemo;
    GroupBox3: TGroupBox;
    StringGrid1: TStringGrid;
    GroupBox1: TGroupBox;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Edit1: TEdit;
    Edit2: TEdit;
    Edit3: TEdit;
    Edit4: TEdit;
    GroupBox2: TGroupBox;
    StringGrid2: TStringGrid;
    GroupBox4: TGroupBox;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Edit5: TEdit;
    Edit6: TEdit;
    Edit7: TEdit;
    Edit8: TEdit;
    Button1: TButton;
    Timer1: TTimer;
    Edit9: TEdit;
    Edit10: TEdit;
    Label9: TLabel;
    Label10: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    ComboBox1: TComboBox;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Button8: TButton;
    Label13: TLabel;
    imp: TImage;
    imo: TImage;
    Panel1: TPanel;
    yello: TImage;
    Timer2: TTimer;
    re: TImage;
    gree: TImage;
    blu: TImage;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Image5: TImage;
    Image6: TImage;
    Image7: TImage;
    Image8: TImage;
    Image9: TImage;
    Image10: TImage;
    Image11: TImage;
    Image12: TImage;
    Image13: TImage;
    Image14: TImage;
    Image15: TImage;
    Image16: TImage;
    Image17: TImage;
    Image18: TImage;
    Image19: TImage;
    Image20: TImage;
    Image21: TImage;
    Image22: TImage;
    Image23: TImage;
    Image24: TImage;
    Image25: TImage;
    Image26: TImage;
    Image27: TImage;
    Image28: TImage;
    Image29: TImage;
    Image30: TImage;
    Image31: TImage;
    Image32: TImage;
    Image33: TImage;
    Image34: TImage;
    Image35: TImage;
    Image36: TImage;
    Image37: TImage;
    Image38: TImage;
    Image39: TImage;
    Image40: TImage;
    Image41: TImage;
    Image42: TImage;
    Image43: TImage;
    Image44: TImage;
    Image45: TImage;
    Image46: TImage;
    Image47: TImage;
    Image48: TImage;
    Image49: TImage;
    Image50: TImage;
    Image51: TImage;
    Image52: TImage;
    Image53: TImage;
    Image54: TImage;
    Image55: TImage;
    Image56: TImage;
    Image57: TImage;
    Image58: TImage;
    Image59: TImage;
    Image60: TImage;
    Image61: TImage;
    Image62: TImage;
    Image63: TImage;
    Image64: TImage;
    Image65: TImage;
    Image66: TImage;
    Image67: TImage;
    Image68: TImage;
    Image69: TImage;
    Image70: TImage;
    Image71: TImage;
    Image72: TImage;
    Image73: TImage;
    Image74: TImage;
    Image75: TImage;
    Image76: TImage;
    Image77: TImage;
    Image78: TImage;
    Image79: TImage;
    Image80: TImage;
    Image81: TImage;
    Image82: TImage;
    Image83: TImage;
    Image84: TImage;
    Image85: TImage;
    Image86: TImage;
    Image87: TImage;
    Image88: TImage;
    Image89: TImage;
    Image90: TImage;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    GroupBox5: TGroupBox;
    Image91: TImage;
    Image92: TImage;
    Image93: TImage;
    Image94: TImage;
    Panel2: TPanel;
    Image95: TImage;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

  const
       N = 5000;
var
  Form1: TForm1;
  pvp,kvp,cvp,dvp,pvo,kvo,cvo,dvo: array [1..N] of string;
  pathapp: string;
  Number1,Number2,curp,curo,count1,count2,delta: integer;
  bl1,bl2,b1,b2: boolean;
implementation

{$R *.dfm}
function im(i: integer): timage;
begin
  with form1 do
  begin
    case i of
    1:result:=image1;
    2:result:=image2;
    3:result:=image3;
    4:result:=image4;
    5:result:=image5;
    6:result:=image6;
    7:result:=image7;
    8:result:=image8;
    9:result:=image9;
    10:result:=image10;
    11:result:=image11;
    12:result:=image12;
    13:result:=image13;
    14:result:=image14;
    15:result:=image15;
    16:result:=image16;
    17:result:=image17;
    18:result:=image18;
    19:result:=image19; 
    20:result:=image20;
    21:result:=image21;
    22:result:=image22;
    23:result:=image23;
    24:result:=image24;
    25:result:=image25;
    26:result:=image26;
    27:result:=image27;
    28:result:=image28;
    29:result:=image29;
    30:result:=image30;
    31:result:=image31;
    32:result:=image32;
    33:result:=image33;
    34:result:=image34;
    35:result:=image35;
    36:result:=image36;
    37:result:=image37;
    38:result:=image38;
    39:result:=image39; 
    40:result:=image40;
    41:result:=image41;
    42:result:=image42;
    43:result:=image43;
    44:result:=image44;
    45:result:=image45;
    46:result:=image46;
    47:result:=image47;
    48:result:=image48;
    49:result:=image49;   
    50:result:=image50;
    51:result:=image51;
    52:result:=image52;
    53:result:=image53;
    54:result:=image54;
    55:result:=image55;
    56:result:=image56;
    57:result:=image57;
    58:result:=image58;
    59:result:=image59;  
    60:result:=image60;
    61:result:=image61;
    62:result:=image62;
    63:result:=image63;
    64:result:=image64;
    65:result:=image65;
    66:result:=image66;
    67:result:=image67;
    68:result:=image68;
    69:result:=image69;
    70:result:=image70;
    71:result:=image71;
    72:result:=image72;
    73:result:=image73;
    74:result:=image74;
    75:result:=image75;
    76:result:=image76;
    77:result:=image77;
    78:result:=image78;
    79:result:=image79;
    80:result:=image80;
    81:result:=image81;
    82:result:=image82;
    83:result:=image83;
    84:result:=image84;
    85:result:=image85;
    86:result:=image86;
    87:result:=image87;
    88:result:=image88;
    89:result:=image89;
    90:result:=image90;
    end;
  end;
end;
procedure start(x: integer);
var i: integer;
    num1,num2: integer;
begin
with form1 do
  case x of
  1: begin
    num1:=random(11)+30;
    count1:=random(600)+50;
    bl1:=true;
    b1:=true;
    for i:=1 to 45 do
    begin
      im(i).Top:=imp.top;
      im(i).left:=imp.Width+imp.left+(i-1)*im(1).Width;
      case random(4) of
      0:im(i).Picture:=yello.Picture;
      1:im(i).Picture:=re.Picture;
      2:im(i).Picture:=gree.Picture;
      3:im(i).Picture:=blu.Picture;
      end;
      if i>num1 then im(i).Visible:=false else im(i).Visible:=true;
    end;
  end;
  2: begin
    num2:=random(11)+75; 
    count2:=random(600)+50;
    bl2:=true;
    b2:=true;
    for i:=46 to 90 do
    begin
      im(i).Top:=imo.top;
      im(i).left:=imo.left-(i-45)*im(1).Width;
      case random(4) of
      0:im(i).Picture:=yello.Picture;
      1:im(i).Picture:=re.Picture;
      2:im(i).Picture:=gree.Picture;
      3:im(i).Picture:=blu.Picture;
      end;
      if i>num2 then im(i).Visible:=false else im(i).Visible:=true;
    end;
  end;
end;
end;

{////////////инициализация////////////}
procedure init();
var i: integer;
begin
    curp:=1;
    curo:=1;
    for i:=1 to Number1 do
    begin
      pvp[i]:='';
      kvp[i]:='';
      cvp[i]:='';
      dvp[i]:='';
    end;
    for i:=1 to Number2 do
    begin
      pvo[i]:='';
      kvo[i]:='';
      cvo[i]:='';
      dvo[i]:='';
    end;
      form1.StringGrid1.Cells[0,0]:='день';
      form1.StringGrid1.Cells[1,0]:='К';
      form1.StringGrid1.Cells[2,0]:='НВ';
      form1.StringGrid1.Cells[3,0]:='Ц';
      form1.StringGrid1.Cells[4,0]:='Ін';
      form1.StringGrid2.Cells[0,0]:='день';
      form1.StringGrid2.Cells[1,0]:='К';
      form1.StringGrid2.Cells[2,0]:='НВ';
      form1.StringGrid2.Cells[3,0]:='Ц';
      form1.StringGrid2.Cells[4,0]:='Ін';
    form1.StringGrid1.RowCount:=2;
    form1.StringGrid2.RowCount:=2;
end;
{////////////load.XLS"////////////}
procedure loading();
var s: string;
    i,j,len: integer;
begin 
    init();
    form1.M.Lines.LoadFromFile(pathapp+'prib.xls');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#9 do begin pvp[j]:=pvp[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin kvp[j]:=kvp[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin cvp[j]:=cvp[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#13 do begin dvp[j]:=dvp[j]+s[i]; i:=i+1; end;i:=i+2;
      j:=j+1;
    end;
    Number1:=j-1;
    form1.M.Lines.LoadFromFile(pathapp+'otprav.xls');
    s:=form1.M.Text;
    len:=length(s);
    i:=1; j:=1;
    while i<=len do
    begin
      while s[i]<>#9 do begin pvo[j]:=pvo[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin kvo[j]:=kvo[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#9 do begin cvo[j]:=cvo[j]+s[i]; i:=i+1; end;i:=i+1;
      while s[i]<>#13 do begin dvo[j]:=dvo[j]+s[i]; i:=i+1; end;i:=i+2;
      j:=j+1;
    end;
    Number2:=j-1;
end;
{////////////заполнение таблицы////////////}
procedure filling();
var i: integer;
begin
    form1.Edit1.Text:=pvp[1];
    form1.Edit2.Text:=kvp[1];
    form1.Edit3.Text:=cvp[1];
    form1.Edit4.Text:=dvp[1];
    form1.Edit5.Text:=pvo[1];
    form1.Edit6.Text:=kvo[1];
    form1.Edit7.Text:=cvo[1];
    form1.Edit8.Text:=dvo[1];
    for i:=2 to Number1 do
    begin
      form1.StringGrid1.Cells[0,i-1]:=inttostr(i-1);
      form1.StringGrid1.Cells[1,i-1]:=pvp[i];
      form1.StringGrid1.Cells[2,i-1]:=kvp[i];
      form1.StringGrid1.Cells[3,i-1]:=cvp[i];
      form1.StringGrid1.Cells[4,i-1]:=dvp[i];
      form1.ComboBox1.Items.Add(inttostr(i-1));
    end;
    form1.ComboBox1.Text:='1';
    form1.StringGrid1.RowCount:=Number1;
    for i:=2 to Number2 do
    begin
      form1.StringGrid2.Cells[0,i-1]:=inttostr(i-1);
      form1.StringGrid2.Cells[1,i-1]:=pvo[i];
      form1.StringGrid2.Cells[2,i-1]:=kvo[i];
      form1.StringGrid2.Cells[3,i-1]:=cvo[i];
      form1.StringGrid2.Cells[4,i-1]:=dvo[i];
    end;
    form1.StringGrid2.RowCount:=Number2;
end;
{////////////y1////////////}
function y1(x1,x2,x3,x4: string):string;
var h,m: integer;
begin
  h:=round(strtofloat(form1.edit1.text)*strtofloat(x3)+
      strtofloat(form1.edit2.text)*strtofloat(x4)+
      strtofloat(form1.edit3.text)*strtofloat(x2)+
      strtofloat(form1.edit4.text)*strtofloat(x1)) div 60;
  m:=round(strtofloat(form1.edit1.text)*strtofloat(x3)+
      strtofloat(form1.edit2.text)*strtofloat(x4)+
      strtofloat(form1.edit3.text)*strtofloat(x2)+
      strtofloat(form1.edit4.text)*strtofloat(x1)) mod 60;  
  result:=inttostr(h)+':'+inttostr(m);
end;
{////////////y2////////////}
function y2(x1,x2,x3,x4: string):string;
var h,m: integer;
begin
  h:=round(strtofloat(form1.edit5.text)*strtofloat(x2)+
      strtofloat(form1.edit6.text)*strtofloat(x3)+
      strtofloat(form1.edit7.text)*strtofloat(x4)+
      strtofloat(form1.edit8.text)*strtofloat(x1)) div 60;
  m:=round(strtofloat(form1.edit5.text)*strtofloat(x2)+
      strtofloat(form1.edit6.text)*strtofloat(x3)+
      strtofloat(form1.edit7.text)*strtofloat(x4)+
      strtofloat(form1.edit8.text)*strtofloat(x1)) mod 60;
  result:=inttostr(h)+':'+inttostr(m);
end;


procedure TForm1.FormCreate(Sender: TObject);
begin
  pathapp:=ExtractFilePath(Application.ExeName);
  Randomize;
  delta:=16;
  start(1);
  start(2);
  bl1:=true;
  bl2:=true;
  loading();
  filling();
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  loading();
  filling();
end;

procedure TForm1.Timer1Timer(Sender: TObject);
var scl: integer;
begin
  if curp<Number1 then
  begin
    Label12.Caption:=inttostr(curp);
    edit9.Text:=y1(StringGrid1.Cells[1,curp],StringGrid1.Cells[2,curp],StringGrid1.Cells[3,curp],StringGrid1.Cells[4,curp]);
    scl:=Image93.Height-round((strtofloat(edit1.text)*strtofloat(StringGrid1.Cells[3,curp])+
      strtofloat(edit2.text)*strtofloat(StringGrid1.Cells[4,curp])+
      strtofloat(edit3.text)*strtofloat(StringGrid1.Cells[2,curp])+
      strtofloat(edit4.text)*strtofloat(StringGrid1.Cells[1,curp]))/3000*Image93.Height);
    image93.canvas.LineTo((Image93.Width div Number1)*curp,scl);
  end;
  if curo<Number2 then
  begin
    Label12.Caption:=inttostr(curo);
    edit10.Text:=y2(StringGrid2.Cells[1,curo],StringGrid2.Cells[2,curo],StringGrid2.Cells[3,curo],StringGrid2.Cells[4,curo]);
    scl:=Image94.Height-round((strtofloat(edit5.text)*strtofloat(StringGrid2.Cells[2,curo])+
      strtofloat(edit6.text)*strtofloat(StringGrid2.Cells[3,curo])+
      strtofloat(edit7.text)*strtofloat(StringGrid2.Cells[4,curo])+
      strtofloat(edit8.text)*strtofloat(StringGrid2.Cells[1,curo]))/3000*Image94.Height);
    image94.canvas.LineTo((Image94.Width div Number2)*curo,scl);
  end;
  if (curp>Number1)and(curo>Number2) then
  begin start(1); start(2); timer2.Enabled:=false; end
  else
  begin curp:=curp+1; curo:=curo+1; end;
end;

procedure TForm1.Button2Click(Sender: TObject);
var scl: integer;
begin
  curp:=strtoint(ComboBox1.text);
  curo:=strtoint(ComboBox1.text);
  image93.Picture:=image95.Picture;
  image94.Picture:=image95.Picture;
  image93.Canvas.MoveTo(0,image93.Height);
  image94.Canvas.MoveTo(0,image94.Height);
  if curp<Number1 then
  begin
    Label12.Caption:=inttostr(curp);
    edit9.Text:=y1(StringGrid1.Cells[1,curp],StringGrid1.Cells[2,curp],StringGrid1.Cells[3,curp],StringGrid1.Cells[4,curp]);
    scl:=Image93.Height-round((strtofloat(edit1.text)*strtofloat(StringGrid1.Cells[3,curp])+
      strtofloat(edit2.text)*strtofloat(StringGrid1.Cells[4,curp])+
      strtofloat(edit3.text)*strtofloat(StringGrid1.Cells[2,curp])+
      strtofloat(edit4.text)*strtofloat(StringGrid1.Cells[1,curp]))/3000*Image93.Height);
    image93.canvas.LineTo((Image93.Width div Number1)*curp,scl);
    curp:=curp+1;
  end;
  if curo<Number2 then
  begin
    Label12.Caption:=inttostr(curo);
    edit10.Text:=y2(StringGrid1.Cells[1,curo],StringGrid1.Cells[2,curo],StringGrid1.Cells[3,curo],StringGrid1.Cells[4,curo]);
    scl:=Image94.Height-round((strtofloat(edit5.text)*strtofloat(StringGrid2.Cells[2,curo])+
      strtofloat(edit6.text)*strtofloat(StringGrid2.Cells[3,curo])+
      strtofloat(edit7.text)*strtofloat(StringGrid2.Cells[4,curo])+
      strtofloat(edit8.text)*strtofloat(StringGrid2.Cells[1,curo]))/3000*Image94.Height);
    image94.canvas.LineTo((Image94.Width div Number2)*curo,scl);
    curo:=curo+1;
  end;

  label12.Caption:=ComboBox1.text;
  timer1.Enabled:=true;
  timer2.Enabled:=true;
  start(1);
  start(2);
  button3.Enabled:=true;
  button3.Caption:='Пауза';
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  if button3.Caption='Пауза' then
  begin
    button3.Caption:='Продовжити';
    timer1.Enabled:=false;
    timer2.Enabled:=false;
  end else
  begin
    button3.Caption:='Пауза';
    timer1.Enabled:=true;
    timer2.Enabled:=true;
  end;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  timer1.Enabled:=false;
  timer2.Enabled:=false;
  image93.Picture:=image95.Picture;
  image94.Picture:=image95.Picture;
  start(1);
  start(2);
  button3.Enabled:=false;
  edit9.Text:='';
  edit10.Text:='';
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  timer1.Interval:=12000;
  delta:=16;
  Button5.Font.Style:=[fsBold];
  Button6.Font.Style:=[];
  Button7.Font.Style:=[];
  Button8.Font.Style:=[];
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  timer1.Interval:=6000;
  delta:=32;
  Button6.Font.Style:=[fsBold]; 
  Button5.Font.Style:=[];
  Button7.Font.Style:=[];
  Button8.Font.Style:=[];
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  timer1.Interval:=3000;
  delta:=64;
  Button7.Font.Style:=[fsBold];
  Button6.Font.Style:=[];
  Button5.Font.Style:=[];
  Button8.Font.Style:=[];
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  timer1.Interval:=1500;
  delta:=128;
  Button8.Font.Style:=[fsBold];
  Button6.Font.Style:=[];
  Button7.Font.Style:=[];
  Button5.Font.Style:=[];
end;

procedure TForm1.Timer2Timer(Sender: TObject);
var i: integer;
begin
  if count1>0 then
  count1:=count1-delta else
  begin
    if bl1 then
    begin
      if im(1).left>(-1)*45*im(1).width then
      for i:=1 to 45 do
      begin
        im(i).Left:=im(i).Left-delta
      end else bl1:=false;
      if b1 and (im(1).left<(imp.Width div 2)-im(1).Width*18) then begin b1:=false; count1:=18000 div delta; end;
    end else start(1);
  end;
  if count2>0 then
  count2:=count2-delta else
  begin
    if bl2 then
    begin
      if im(90).left<imo.Width+imo.Left then
      for i:=46 to 90 do
      begin
        im(i).Left:=im(i).Left+delta
      end else bl2:=false;    
      if b2 and (im(46).left>(imp.Width div 2)+im(1).Width*18) then begin b2:=false; count2:=12000 div delta; end;
    end else start(2);
  end;
end;

end.
