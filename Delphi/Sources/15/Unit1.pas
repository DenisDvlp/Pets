unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    e1: TEdit;
    b1: TButton;
    b2: TButton;
    b3: TButton;
    b4: TButton;
    b5: TButton;
    b6: TButton;
    b7: TButton;
    b8: TButton;
    b9: TButton;
    bt: TButton;
    b0: TButton;
    bpm: TButton;
    bdel: TButton;
    bum: TButton;
    bmin: TButton;
    bpl: TButton;
    bsqrt: TButton;
    brav: TButton;
    C: TButton;
    e2: TEdit;
    procedure b7Click(Sender: TObject);
    procedure FormKeyPress(Sender: TObject; var Key: char);
    procedure b8Click(Sender: TObject);
    procedure b9Click(Sender: TObject);
    procedure b4Click(Sender: TObject);
    procedure b5Click(Sender: TObject);
    procedure b6Click(Sender: TObject);
    procedure b1Click(Sender: TObject);
    procedure b2Click(Sender: TObject);
    procedure b3Click(Sender: TObject);
    procedure btClick(Sender: TObject);
    procedure b0Click(Sender: TObject);
    procedure bdelClick(Sender: TObject);
    procedure bumClick(Sender: TObject);
    procedure bminClick(Sender: TObject);
    procedure bplClick(Sender: TObject);
    procedure CClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure bravClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
var buf1: Extended;
var buf2: Extended;
var num1: Extended;
var num2: Extended;
var bl: Boolean;
var bl1: Boolean;
var bl2: Boolean;
var bl3: Boolean;
var bl4: Boolean;

implementation

{$R *.dfm}

procedure TForm1.FormKeyPress(Sender: TObject; var Key: char);
begin
 case Key of
 '1': e1.text:=e1.text+'1';
 '2': e1.text:=e1.text+'2';
 '3': e1.text:=e1.text+'3';
 '4': e1.text:=e1.text+'4';
 '5': e1.text:=e1.text+'5';
 '6': e1.text:=e1.text+'6';
 '7': e1.text:=e1.text+'7';
 '8': e1.text:=e1.text+'8';
 '9': e1.text:=e1.text+'9';
 '0': e1.text:=e1.text+'0';
 '/': e1.text:=e1.text+'/';
 '*': e1.text:=e1.text+'*';
 '-': e1.text:=e1.text+'-';
 '+': e1.text:=e1.text+'+';
 '.': e1.text:=e1.text+'.';
 end;
end;

procedure TForm1.b1Click(Sender: TObject);
begin
e1.text:=e1.text+'1';
if bl=false then
buf1 := buf1 * 10 + 1
else
buf2 := buf2 * 10 + 1;
end;

procedure TForm1.b2Click(Sender: TObject);
begin
e1.text:=e1.text+'2';
if bl=false then
buf1 := buf1 * 10 + 2
else
buf2 := buf2 * 10 + 2;
end;

procedure TForm1.b3Click(Sender: TObject);
begin
e1.text:=e1.text+'3';
if bl=false then
buf1 := buf1 * 10 + 3
else
buf2 := buf2 * 10 + 3;
end;
     
procedure TForm1.b4Click(Sender: TObject);
begin
e1.text:=e1.text+'4';
if bl=false then
buf1 := buf1 * 10 + 4
else
buf2 := buf2 * 10 + 4;
end;

procedure TForm1.b5Click(Sender: TObject);
begin
e1.text:=e1.text+'5';
if bl=false then
buf1 := buf1 * 10 + 5
else
buf2 := buf2 * 10 + 5;
end;

procedure TForm1.b6Click(Sender: TObject);
begin
e1.text:=e1.text+'6';
if bl=false then
buf1 := buf1 * 10 + 6
else
buf2 := buf2 * 10 + 6;
end;

procedure TForm1.b7Click(Sender: TObject);
begin
e1.text:=e1.text+'7';
if bl=false then
buf1 := buf1 * 10 + 7
else
buf2 := buf2 * 10 + 7;
end;

procedure TForm1.b8Click(Sender: TObject);
begin
e1.text:=e1.text+'8';
if bl=false then
buf1 := buf1 * 10 + 8
else
buf2 := buf2 * 10 + 8;
end;

procedure TForm1.b9Click(Sender: TObject);
begin
e1.text:=e1.text+'9';
if bl=false then
buf1 := buf1 * 10 + 9
else
buf2 := buf2 * 10 + 9;
end;
    
procedure TForm1.b0Click(Sender: TObject);
begin
e1.text:=e1.text+'0';
if bl=false then
buf1 := buf1 * 10 + 0
else
buf2 := buf2 * 10 + 0;
end;

procedure TForm1.btClick(Sender: TObject);
begin
e1.text:=e1.text+'.';
end;

procedure TForm1.bdelClick(Sender: TObject);
begin
if bl=false then bl:=true else
begin
if bl1=true then num1:=buf1/buf2 else
if bl2=true then num1:=buf1*buf2 else
if bl3=true then num1:=buf1-buf2 else
if bl4=true then num1:=buf1+buf2;
e2.Text := floattostr(num1);
buf1:=num1;
buf2:=0;
end;
bl1:=true;
bl2:=false;
bl3:=false;
bl4:=false;
e1.text:=e1.text+'/';
end;

procedure TForm1.bumClick(Sender: TObject);
begin
if bl=false then bl:=true else
begin
if bl1=true then num1:=buf1/buf2 else
if bl2=true then num1:=buf1*buf2 else
if bl3=true then num1:=buf1-buf2 else
if bl4=true then num1:=buf1+buf2;
e2.Text := floattostr(num1);
buf1:=num1;
buf2:=0;
end;
bl2:=true;
bl1:=false;
bl3:=false;
bl4:=false;
e1.text:=e1.text+'*';
end;

procedure TForm1.bminClick(Sender: TObject);
begin
if bl=false then bl:=true else
begin
if bl1=true then num1:=buf1/buf2 else
if bl2=true then num1:=buf1*buf2 else
if bl3=true then num1:=buf1-buf2 else
if bl4=true then num1:=buf1+buf2;
e2.Text := floattostr(num1);
buf1:=num1;
buf2:=0;
end;
bl3:=true;
bl2:=false;
bl1:=false;
bl4:=false;
e1.text:=e1.text+'-';
end;

procedure TForm1.bplClick(Sender: TObject);
begin
if bl=false then bl:=true else
begin
if bl1=true then num1:=buf1/buf2 else
if bl2=true then num1:=buf1*buf2 else
if bl3=true then num1:=buf1-buf2 else
if bl4=true then num1:=buf1+buf2;
e2.Text := floattostr(num1);
buf1:=num1;
buf2:=0;
end;
bl4:=true;
bl2:=false;
bl3:=false;
bl1:=false;
e1.text:=e1.text+'+';
end;

procedure TForm1.bravClick(Sender: TObject);
begin
if bl1=true then num1:=buf1/buf2 else
if bl2=true then num1:=buf1*buf2 else
if bl3=true then num1:=buf1-buf2 else
if bl4=true then num1:=buf1+buf2;
e2.Text := floattostr(num1);
buf1:=num1;
buf2:=0;
bl1:=false;
bl2:=false;
bl3:=false;
bl4:=false;
end;

procedure TForm1.CClick(Sender: TObject);
begin
e1.Text:='';
e2.Text:='';
buf1:=0;
buf2:=0;
num1:=0;
num2:=0;
bl:=false;
bl1:=false;
bl2:=false;
bl3:=false;
bl4:=false;
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
buf1:=0;
buf2:=0;
num1:=0;
num2:=0;
bl:=false;
bl1:=false;
bl2:=false;
bl3:=false;
bl4:=false;
end;

end.
