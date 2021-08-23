unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, jpeg, ExtCtrls, StdCtrls, ComCtrls, Menus;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Image1: TImage;
    Button3: TButton;
    Button4: TButton;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Label9: TLabel;
    Label10: TLabel;
    Label33: TLabel;
    Label11: TLabel;
    Label12: TLabel;
    Label13: TLabel;
    Label14: TLabel;
    Label15: TLabel;
    Label16: TLabel;
    Label17: TLabel;
    Label18: TLabel;
    Label19: TLabel;
    Label20: TLabel;
    Label21: TLabel;
    Label22: TLabel;
    Label23: TLabel;
    Label24: TLabel;
    Label25: TLabel;
    Label26: TLabel;
    Label27: TLabel;
    Label28: TLabel;
    Label29: TLabel;
    Label30: TLabel;
    Label31: TLabel;
    Label32: TLabel;
    M: TMemo;
    Panel3: TPanel;
    lqnum: TLabel;
    lqadres: TLabel;
    lqtel: TLabel;
    lqnum1: TLabel;
    lqadres1: TLabel;
    lqtel1: TLabel;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Image5: TImage;
    Image6: TImage;
    Image7: TImage;
    Image8: TImage;
    PopupMenu1: TPopupMenu;
    N521211: TMenuItem;
    Label34: TLabel;
    Label35: TLabel;
    Label36: TLabel;
    Label37: TLabel;
    Label38: TLabel;
    Label39: TLabel;
    Label40: TLabel;
    Label41: TLabel;
    Label42: TLabel;
    Label43: TLabel;
    Label44: TLabel;
    Label45: TLabel;
    Label46: TLabel;
    Label47: TLabel;
    Label48: TLabel;
    Label49: TLabel;
    Label50: TLabel;
    Label51: TLabel;
    PopupMenu2: TPopupMenu;
    N1: TMenuItem;
    N2: TMenuItem;
    Label52: TLabel;
    PopupMenu3: TPopupMenu;
    MenuItem1: TMenuItem;
    MenuItem2: TMenuItem;
    procedure Image1MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure FormCreate(Sender: TObject);
    procedure Image1MouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Image1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Button4MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Button3MouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure Label20MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label1MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label10MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label11MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label12MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label13MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label14MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label15MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label16MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label17MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label18MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label19MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label2MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label21MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label22MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label23MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label24MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label25MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label26MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label27MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label28MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label29MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label3MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label30MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label31MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label32MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label33MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label4MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label5MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label6MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label7MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label8MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label9MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure FormMouseWheelUp(Sender: TObject; Shift: TShiftState;
      MousePos: TPoint; var Handled: Boolean);
    procedure FormMouseWheelDown(Sender: TObject; Shift: TShiftState;
      MousePos: TPoint; var Handled: Boolean);
    procedure N521211Click(Sender: TObject);
    procedure FormResize(Sender: TObject);
    procedure N1Click(Sender: TObject);
    procedure N2Click(Sender: TObject);
    procedure Label34MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label35MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label36MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label37MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label38MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label39MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label40MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label41MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label42MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label43MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label44MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label45MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label46MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label47MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label48MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label49MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label50MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label51MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure Label52MouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure MenuItem1Click(Sender: TObject);
    procedure MenuItem2Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  drag,blup,bldown: boolean;
  xx,yy,imagenumber,xsc,ysc,pingnum,selectedpingnum: integer;
  defaultposx,defaultposy,posx,posy: array[1..100] of integer;
  infonumber,infoadres,infotel,inforouter,infopc: array [1..100] of string;
  procedure buttonpos();
  procedure buttonrepos();
  procedure buttonposinit();
  procedure tobovisible(vis: boolean);
  procedure quickinfo(num: integer);
  procedure panelshow(num: integer);
  function imag(i: integer):timage;
  function labl(i: integer):tlabel;
implementation

{$R *.dfm}
procedure loadinfo();
var s: string;
    i,j,len: integer;
begin
    form1.M.Lines.LoadFromFile('shortinfo.xls');
    s:=form1.M.Text;
    len:=length(s);
    j:=1; i:=1;
    while i<=len do begin
    while s[i]<>#9 do begin infonumber[j]:=infonumber[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#9 do begin infoadres[j]:=infoadres[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#9 do begin infotel[j]:=infotel[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#9 do begin inforouter[j]:=inforouter[j]+s[i]; i:=i+1; end;i:=i+1;
    while s[i]<>#13 do begin infopc[j]:=infopc[j]+s[i]; i:=i+1; end;i:=i+2;
    j:=j+1; end;
end;

procedure LongPing(c: string);
var s: string;
begin
  if c='router' then s:=inforouter[pingnum];
  if c='mainpc' then s:=infopc[pingnum];

  if s<>'' then
  begin
    form1.M.Text:='';
    form1.M.Text:='ping -t '+s;
    form1.M.Lines.SaveToFile('pingpong.bat');
    winexec('pingpong.bat',SW_SHOW);
  end;
end;

procedure panelshow(num: integer);
begin
  pingnum:=num;
  with form1 do
  if Panel3.Visible=false then
  begin
    if labl(num).Left<panel3.Width then
    panel3.Left:=labl(num).Left+labl(num).Width
    else
    panel3.Left:=labl(num).Left-panel3.Width;
    if labl(num).top<panel3.Height then
    panel3.top:=labl(num).top+labl(num).Height
    else
    panel3.top:=labl(num).top-panel3.Height;
    if panel3.Height+panel3.Top>ClientHeight then panel3.Top:=ClientHeight-panel3.Height;
    Panel3.Visible:=true;
  end;
end;

procedure quickinfo(num: integer);
begin
  form1.lqnum1.caption:=infonumber[num];
  form1.lqadres1.caption:=infoadres[num];
  if num<34 then
  begin
    form1.lqtel.caption:='òåë.';
    form1.lqtel1.caption:=infotel[num];
  end else begin
    form1.lqtel.caption:='ìîäåëü';
    form1.lqtel1.caption:=infotel[num];
  end;
  form1.Canvas.FillRect(form1.Canvas.ClipRect);
end;

procedure tobovisible(vis: boolean);
var i: integer;
begin for i:=1 to 33 do labl(i).Visible:=vis;end;

procedure atmvisible(vis: boolean);
var i: integer;
begin for i:=34 to 52 do labl(i).Visible:=vis;end;

procedure buttonposinit();
var i:integer;
begin
  for i:=1 to 52 do
  begin
   defaultposx[i]:=labl(i).Left;
   defaultposy[i]:=labl(i).Top;
  end;
end;

function imag(i: integer):timage;
begin
  with form1 do
  case i of
  1:result:=image1;
  2:result:=image2;
  3:result:=image3;
  4:result:=image4;
  5:result:=image5;
  6:result:=image6;
  7:result:=image7;
  8:result:=image8;
  end;
end;

function labl(i: integer):tlabel;
begin
  with form1 do
  case i of
  1:result:=label1;
  2:result:=label2;
  3:result:=label3;
  4:result:=label4;
  5:result:=label5;
  6:result:=label6;
  7:result:=label7;
  8:result:=label8;
  9:result:=label9;
  10:result:=label10;
  11:result:=label11;
  12:result:=label12;
  13:result:=label13;
  14:result:=label14;
  15:result:=label15;
  16:result:=label16;
  17:result:=label17;
  18:result:=label18;
  19:result:=label19;
  20:result:=label20;
  21:result:=label21;
  22:result:=label22;
  23:result:=label23;
  24:result:=label24;
  25:result:=label25;
  26:result:=label26;
  27:result:=label27;
  28:result:=label28;
  29:result:=label29;
  30:result:=label30;
  31:result:=label31;
  32:result:=label32;
  33:result:=label33;
  34:result:=label34;
  35:result:=label35;
  36:result:=label36;
  37:result:=label37;
  38:result:=label38;
  39:result:=label39;
  40:result:=label40;
  41:result:=label41;
  42:result:=label42;
  43:result:=label43;
  44:result:=label44;
  45:result:=label45;
  46:result:=label46;
  47:result:=label47;
  48:result:=label48;
  49:result:=label49;
  50:result:=label50;
  51:result:=label51;
  52:result:=label52;
  end;
end;

procedure buttonrepos();
var scale: real;
    i: integer;
begin
  with form1 do
  begin
  case imagenumber of
  1:begin Caption:='Êàðòà ÒÎÁÎ 100%';scale:=1; end;
  2:begin Caption:='Êàðòà ÒÎÁÎ 90%';scale:=0.9; end;
  3:begin Caption:='Êàðòà ÒÎÁÎ 80%';scale:=0.8; end;
  4:begin Caption:='Êàðòà ÒÎÁÎ 70%';scale:=0.7; end;
  5:begin Caption:='Êàðòà ÒÎÁÎ 60%';scale:=0.6; end;
  6:begin Caption:='Êàðòà ÒÎÁÎ 50%';scale:=0.5; end;
  7:begin Caption:='Êàðòà ÒÎÁÎ 40%';scale:=0.4; end;
  8:begin Caption:='Êàðòà ÒÎÁÎ 30%';scale:=0.3; end; end;
  end;
  for i:=1 to 52 do
  begin
	  posx[i]:=round(defaultposx[i]*scale);
	  posy[i]:=round(defaultposy[i]*scale);
  end;
end;

procedure buttonpos();
var i: integer;
begin
  for i:=1 to 52 do
  begin
    labl(i).Left:=imag(imagenumber).Left+posx[i];
    labl(i).Top:=imag(imagenumber).Top+posy[i];
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var i: integer;
begin
  form1.M.Lines.LoadFromFile('shortinfo.xls');
  loadinfo();
  panel1.Width:=ClientWidth;
  panel1.Height:=ClientHeight;
  drag:=false;
  blup:=false;
  bldown:=false;
  imagenumber:=8;
  for i:=1 to 7 do imag(i).Visible:=false;
  buttonposinit();
  buttonrepos();
  buttonpos();
end;

procedure TForm1.Image1MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin drag:=true; xx:=x;yy:=y; end;

procedure TForm1.Image1MouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin drag:=false; buttonpos(); end;

procedure TForm1.Image1MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  Panel3.Visible:=false;
  xsc:=x;
  ysc:=y;
  if drag then
  begin
    imag(imagenumber).left:=imag(imagenumber).left+x-xx;imag(imagenumber).Top:=imag(imagenumber).Top+y-yy;
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
    //buttonpos();
  end;
end;

procedure TForm1.Button3MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if imagenumber>1 then
  begin
    imag(imagenumber-1).Left:=round(clientwidth/2+imag(imagenumber-1).width/imag(imagenumber).width*(imag(imagenumber).Left-clientwidth/2));
    imag(imagenumber-1).Top:=round(clientheight/2+imag(imagenumber-1).height/imag(imagenumber).height*(imag(imagenumber).Top-clientheight/2));
    imag(imagenumber).Visible:=false;
    imag(imagenumber-1).Visible:=true;
    imagenumber:=imagenumber-1;
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
  end;
  buttonrepos();
  buttonpos();
end;

procedure TForm1.Button4MouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if imagenumber<8 then
  begin
    imag(imagenumber+1).Left:=round(clientwidth/2+imag(imagenumber+1).width/imag(imagenumber).width*(imag(imagenumber).Left-clientwidth/2));
    imag(imagenumber+1).Top:=round(clientheight/2+imag(imagenumber+1).height/imag(imagenumber).height*(imag(imagenumber).Top-clientheight/2));
    imag(imagenumber).Visible:=false;
    imag(imagenumber+1).Visible:=true;
    imagenumber:=imagenumber+1;
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
  end;
  buttonrepos();
  buttonpos();
end;

procedure TForm1.FormMouseWheelUp(Sender: TObject; Shift: TShiftState;
  MousePos: TPoint; var Handled: Boolean);
begin
  if blup then blup:=false else blup:=true;
  if blup and (imagenumber>1) then
  begin
    imag(imagenumber-1).Left:=round(xsc+imag(imagenumber).Left-imag(imagenumber-1).Width/imag(imagenumber).Width*xsc);
    imag(imagenumber-1).Top:=round(ysc+imag(imagenumber).Top-imag(imagenumber-1).Height/imag(imagenumber).Height*ysc);
    xsc:=xsc+imag(imagenumber).Left-imag(imagenumber-1).Left;
    ysc:=ysc+imag(imagenumber).Top-imag(imagenumber-1).Top;
    imag(imagenumber).Visible:=false;
    imag(imagenumber-1).Visible:=true;
    imagenumber:=imagenumber-1;
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
  end;
  buttonrepos();
  buttonpos();
end;

procedure TForm1.FormMouseWheelDown(Sender: TObject; Shift: TShiftState;
  MousePos: TPoint; var Handled: Boolean);
begin
  if bldown then bldown:=false else bldown:=true;
  if bldown and (imagenumber<8) then
  begin
    imag(imagenumber+1).Left:=round(xsc+imag(imagenumber).Left-imag(imagenumber+1).Width/imag(imagenumber).Width*xsc);
    imag(imagenumber+1).Top:=round(ysc+imag(imagenumber).Top-imag(imagenumber+1).Height/imag(imagenumber).Height*ysc);
    xsc:=xsc+imag(imagenumber).Left-imag(imagenumber+1).Left;
    ysc:=ysc+imag(imagenumber).Top-imag(imagenumber+1).Top;
    imag(imagenumber).Visible:=false;
    imag(imagenumber+1).Visible:=true;
    imagenumber:=imagenumber+1;
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
  end;
  buttonrepos();
  buttonpos();
end;

procedure TForm1.Label1MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(1); quickinfo(1);end;
procedure TForm1.Label2MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(2); quickinfo(2);end;
procedure TForm1.Label3MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(3); quickinfo(3);end;
procedure TForm1.Label4MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(4); quickinfo(4);end;
procedure TForm1.Label5MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(5); quickinfo(5);end;
procedure TForm1.Label6MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(6); quickinfo(6);end;
procedure TForm1.Label7MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(7); quickinfo(7);end;
procedure TForm1.Label8MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(8); quickinfo(8);end;
procedure TForm1.Label9MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(9); quickinfo(9);end;
procedure TForm1.Label10MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(10); quickinfo(10);end;
procedure TForm1.Label11MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(11); quickinfo(11);end;
procedure TForm1.Label12MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(12); quickinfo(12);end;
procedure TForm1.Label13MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(13); quickinfo(13);end;
procedure TForm1.Label14MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(14); quickinfo(14);end;
procedure TForm1.Label15MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(15); quickinfo(15);end;
procedure TForm1.Label16MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(16); quickinfo(16);end;
procedure TForm1.Label17MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(17); quickinfo(17);end;
procedure TForm1.Label18MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(18); quickinfo(18);end;
procedure TForm1.Label19MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(19); quickinfo(19);end;
procedure TForm1.Label20MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(20); quickinfo(20);end;
procedure TForm1.Label21MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(21); quickinfo(21);end;
procedure TForm1.Label22MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(22); quickinfo(22);end;
procedure TForm1.Label23MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(23); quickinfo(23);end;

procedure TForm1.Label24MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(24); quickinfo(24);end;
procedure TForm1.Label25MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(25); quickinfo(25);end;
procedure TForm1.Label26MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(26); quickinfo(26);end;
procedure TForm1.Label27MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(27); quickinfo(27);end;
procedure TForm1.Label28MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(28); quickinfo(28);end;
procedure TForm1.Label29MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(29); quickinfo(29);end;
procedure TForm1.Label30MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(30); quickinfo(30);end;
procedure TForm1.Label31MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(31); quickinfo(31);end;
procedure TForm1.Label32MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(32); quickinfo(32);end;
procedure TForm1.Label33MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(33); quickinfo(33);end;

procedure TForm1.N521211Click(Sender: TObject);
begin
  LongPing('router');
end;

procedure TForm1.FormResize(Sender: TObject);
begin
    if imag(imagenumber).left<(clientwidth-imag(imagenumber).Width) then imag(imagenumber).left:=clientwidth-imag(imagenumber).Width;
    if imag(imagenumber).top<(clientheight-imag(imagenumber).height) then imag(imagenumber).top:=clientheight-imag(imagenumber).height;
    if imag(imagenumber).left>0 then imag(imagenumber).left:=0;
    if imag(imagenumber).top>0 then imag(imagenumber).top:=0;
    buttonpos();
end;

procedure TForm1.N1Click(Sender: TObject);
begin
  if N1.Checked then
  begin
    N1.Checked:=false;
    atmvisible(false);
  end else begin
    N1.Checked:=true;
    atmvisible(true);
  end;
end;

procedure TForm1.N2Click(Sender: TObject);
begin
  if N2.Checked then
  begin
    N2.Checked:=false;
    tobovisible(false);
  end else begin
    N2.Checked:=true;
    tobovisible(true);
  end;
end;

procedure TForm1.Label34MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(34); quickinfo(34);end;
procedure TForm1.Label35MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(35); quickinfo(35);end;
procedure TForm1.Label36MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(36); quickinfo(36);end;
procedure TForm1.Label37MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(37); quickinfo(37);end;
procedure TForm1.Label38MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(38); quickinfo(38);end;
procedure TForm1.Label39MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(39); quickinfo(39);end;
procedure TForm1.Label40MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(40); quickinfo(40);end;
procedure TForm1.Label41MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(41); quickinfo(41);end;
procedure TForm1.Label42MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(42); quickinfo(42);end;
procedure TForm1.Label43MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(43); quickinfo(43);end;
procedure TForm1.Label44MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(44); quickinfo(44);end;
procedure TForm1.Label45MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(45); quickinfo(45);end;
procedure TForm1.Label46MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(46); quickinfo(46);end;
procedure TForm1.Label47MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(47); quickinfo(47);end;
procedure TForm1.Label48MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(48); quickinfo(48);end;
procedure TForm1.Label49MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(49); quickinfo(49);end;
procedure TForm1.Label50MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(50); quickinfo(50);end;
procedure TForm1.Label51MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(51); quickinfo(51);end;
procedure TForm1.Label52MouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin panelshow(52); quickinfo(52);end;

procedure TForm1.MenuItem1Click(Sender: TObject);
begin
  LongPing('mainpc');
end;
procedure TForm1.MenuItem2Click(Sender: TObject);
begin
  LongPing('router');
end;

end.
