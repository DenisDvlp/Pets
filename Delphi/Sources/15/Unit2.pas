unit Unit2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    E1: TEdit;
    E2: TEdit;
    B: TButton;
    Button1: TButton;
    procedure BClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure BClic(Sender: TObject);

  private
    { Private declarations }
  public
    { Public declarations }
  end;
    function Rules(): integer;
    function Go(first: integer): real;
    function Skobki(): integer;
    function Begining(): integer;
    function Number(first: integer): integer;
    function Sign(first: integer): integer;
    function Skob1(first: integer): integer;
    function Skob2(first: integer): integer;
var
  Form1: TForm1;
  str: string;
implementation

{$R *.dfm}
////////////////////////////////////////////////////////////////////////////////
function Skobki(): integer;
  var
    i,count1,count2,kod: integer;
begin
  count1:=0;
  count2:=0;
  for i:=1 to length(str) do
    begin
      if str[i]='(' then count1:=count1+1;
      if str[i]=')' then count2:=count2+1;
      if count1<count2 then kod:=1;
    end;
      if count1<>count2 then kod:=2 else if kod<>1 then kod:=0;
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Begining(): integer;
  var kod: integer;
begin
    kod:=3;
    case str[1] of
    '1': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '2': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '3': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '4': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '5': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '6': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '7': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '8': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '9': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '0': begin if length(str)=1 then kod:=0 else kod:=Number(2); end;
    '+': begin if length(str)=1 then kod:=3 else kod:=Sign(2); end;
    '-': begin if length(str)=1 then kod:=3 else kod:=Sign(2); end;
    '(': begin if length(str)=1 then kod:=3 else kod:=Skob1(2); end;
    end;
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Number(first: integer): integer;
  var kod: integer;
begin
    kod:=4;
    case str[first] of
    '1': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '2': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '3': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '4': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '5': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '6': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '7': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '8': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '9': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '0': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '+': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '-': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '*': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '/': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    ')': begin if length(str)=first then kod:=0 else kod:=Skob2(first+1); end;
    end;
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Sign(first: integer): integer;
  var kod: integer;
begin
    kod:=5;
    case str[first] of
    '1': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '2': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '3': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '4': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '5': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '6': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '7': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '8': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '9': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '0': begin if length(str)=first then kod:=0 else kod:=Number(first+1); end;
    '(': begin kod:=Skob1(first+1); end;
    end; 
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Skob1(first: integer): integer;
  var kod: integer;
begin
    kod:=6;
    case str[first] of
    '1': begin kod:=Number(first+1); end;
    '2': begin kod:=Number(first+1); end;
    '3': begin kod:=Number(first+1); end;
    '4': begin kod:=Number(first+1); end;
    '5': begin kod:=Number(first+1); end;
    '6': begin kod:=Number(first+1); end;
    '7': begin kod:=Number(first+1); end;
    '8': begin kod:=Number(first+1); end;
    '9': begin kod:=Number(first+1); end;
    '0': begin kod:=Number(first+1); end;
    '+': begin kod:=Sign(first+1); end;
    '-': begin kod:=Sign(first+1); end;
    '(': begin kod:=Skob1(first+1); end;
    ')': begin kod:=9 end;
    end;
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Skob2(first: integer): integer;
  var kod: integer;
begin
    kod:=7;
    case str[first] of
    '+': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '-': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '*': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    '/': begin if length(str)=first then kod:=8 else kod:=Sign(first+1); end;
    ')': begin if length(str)=first then kod:=0 else kod:=Skob2(first+1); end;
    end; 
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Rules(): integer;
  var kod: integer;
begin
    if Skobki()=0 then
    kod:=Begining()
    else
    kod:=Skobki();
    result:=kod;
end;
////////////////////////////////////////////////////////////////////////////////
function Go(first: integer): real;
   label label1;
   var
   sum: real;
   buf1: real;
   buf2: real;
   i, count: integer;
   blf,b1,b2,b3,b4: boolean;
begin
      count:=0;
      buf1:=0;
      buf2:=0;
      sum:=0;
      blf:=true;
      b1:=false;
      b2:=false;
      b3:=false;
      b4:=false;
      i:=first;
  while  i<=length(str) do
  begin
    if blf=true then
    begin
     case str[i] of
     '1': begin buf1:=buf1*10+1; end;
     '2': begin buf1:=buf1*10+2; end;
     '3': begin buf1:=buf1*10+3; end;
     '4': begin buf1:=buf1*10+4; end;
     '5': begin buf1:=buf1*10+5; end;
     '6': begin buf1:=buf1*10+6; end;
     '7': begin buf1:=buf1*10+7; end;
     '8': begin buf1:=buf1*10+8; end;
     '9': begin buf1:=buf1*10+9; end;
     '0': begin buf1:=buf1*10+0; end;
     end;
   end else
   begin
     case str[i] of
     '1': begin buf2:=buf2*10+1;  end;
     '2': begin buf2:=buf2*10+2;  end;
     '3': begin buf2:=buf2*10+3;  end;
     '4': begin buf2:=buf2*10+4;  end;
     '5': begin buf2:=buf2*10+5;  end;
     '6': begin buf2:=buf2*10+6;  end;
     '7': begin buf2:=buf2*10+7;  end;
     '8': begin buf2:=buf2*10+8;  end;
     '9': begin buf2:=buf2*10+9;  end;
     '0': begin buf2:=buf2*10+0;  end;
     end;
   end;
////////////////////////////////
  if (i=length(str)) or (str[i+1]=')') then
  begin
      if b1=true then begin buf1:=buf1/buf2; end else
      if b2=true then begin buf1:=buf1*buf2; end;
      if b3=true then sum:=sum-buf1 else
      if b4=true then sum:=sum+buf1 else
                      sum:=buf1;
  result:=sum;
  goto label1;
  end;
////////////////////////////////
  if str[i]='(' then
  begin
      if blf=true then
      buf1:=Go(i+1) else
      buf2:=Go(i+1);
      count:=1;
      while count<>0 do
      begin
          i:=i+1;
          if(str[i]='(') then count:=count+1;
          if(str[i]=')') then count:=count-1;
      end;
      if i=length(str) then
      begin
        if b1=true then begin buf1:=buf1/buf2; end else
        if b2=true then begin buf1:=buf1*buf2; end;
        if b3=true then sum:=sum-buf1 else
        if b4=true then sum:=sum+buf1 else
                        sum:=buf1;
      result:=sum;
      goto label1;
      end;
  end;
////////////////////////////////
  if str[i]='/' then
  begin
      if blf=true then
      begin blf:=false; b1:=true; end
      else
      begin
         if b1=true then begin buf1:=buf1/buf2; end else
         if b2=true then begin buf1:=buf1*buf2; end;
         b1:=true; b2:=false; buf2:=0;
      end;
  end else
////////////////////////////////
  if str[i]='*' then
  begin
      if blf=true then
      begin blf:=false; b2:=true; end
      else
      begin
         if b1=true then begin buf1:=buf1/buf2; end else
         if b2=true then begin buf1:=buf1*buf2; end;
         b1:=false; b2:=true; buf2:=0;
      end;
  end else
////////////////////////////////
  if str[i]='-' then
  begin
      if b1=true then begin buf1:=buf1/buf2; end else
      if b2=true then begin buf1:=buf1*buf2; end;
      if b3=true then sum:=sum-buf1 else
      if b4=true then sum:=sum+buf1 else
                      sum:=buf1;
       b1:=false; b2:=false; b3:=true; b4:=false; buf1:=0; buf2:=0; blf:=true;
  end else
////////////////////////////////
  if str[i]='+' then
  begin
      if b1=true then begin buf1:=buf1/buf2; end else
      if b2=true then begin buf1:=buf1*buf2; end;
      if b3=true then sum:=sum-buf1 else
      if b4=true then sum:=sum+buf1 else
                      sum:=buf1;
       b1:=false; b2:=false; b3:=false; b4:=true; buf1:=0; buf2:=0; blf:=true;
  end;
///////////////////////////////
  i:=i+1;
  end;
   label1:
end;
////////////////////////////////////////////////////////////////////////////////
procedure TForm1.BClick(Sender: TObject);
begin
str:=e1.text;
if str <> '' then
  begin
    e2.Color:=TColor($A0C0FF);
    case Rules() of
    1: e2.text:='ERROR: Нарушена логика скобок!';
    2: e2.text:='ERROR: Пропущены скобки!';
    3: e2.text:='ERROR: Выражение начинается неверно!';
    4: e2.text:='ERROR: После цифры обнаружен неверный символ!';
    5: e2.text:='ERROR: После знака обнаружен неверный символ!';
    6: e2.text:='ERROR: Неверный символ после открытой скобки!';
    7: e2.text:='ERROR: Неверный символ после закрытой скобки!';
    8: e2.text:='ERROR: Незаконченное выражение!';
    9: e2.text:='ERROR: Пустые скобки!';
    0:
      begin
        e2.Color:=clWindow;
        e2.text:=floattostr(Go(1));
      end;
    end;
  end;
end;

procedure TForm1.BClic(Sender: TObject);
begin
  e2.Color:=clWindow;
  e1.Text:='';
  e2.Text:='';
  str:='';
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
setlength(str,256);
e1.SelLength:=256;
e2.SelLength:=256;
  e2.Color:=clWindow;
  e1.Text:='';
  e2.Text:='';
  str:='';
end;

end.
