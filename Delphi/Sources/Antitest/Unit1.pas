unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Button1: TButton;
    Button2: TButton;
    Memo1: TMemo;
    Memo2: TMemo;
    Edit1: TEdit;
    OpenDialog1: TOpenDialog;
    GroupBox1: TGroupBox;
    Button5: TButton;
    Button6: TButton;
    m: TMemo;
    SaveDialog1: TSaveDialog;
    Button3: TButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  number,alfabet: array [1..256] of string;
  sdvig: integer;
implementation

{$R *.dfm}

procedure loadalfabet();
var s: string;
i,j: integer;
begin
  form1.m.Lines.LoadFromFile('alfabet.txt');
  s:=form1.m.Text;
  i:=1;
  for j:=1 to 256 do
  begin
    number[j]:=s[i]+s[i+1]+s[i+2]; i:=i+4;
    if s[i]<>#13 then begin alfabet[j]:=s[i]; i:=i+3; end else i:=i+2;
  end;
end;

procedure uncrypt(shift: integer);
var s,s1,s2: string;
      i,j: integer;
      bl: boolean;
begin
 bl:=true;
   s:=form1.memo1.text;
   i:=shift;
   form1.Memo2.Text:='';
   while i<length(s) do
   begin
     case s[i] of
     '0':begin if (s[i+1]<>'0')or(s[i+2]<>'0') then bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '1':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '2':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '3':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '4':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '5':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '6':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '7':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '8':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     '9':begin bl:=true; s1:=s[i]+s[i+1]+s[i+2]; i:=i+3; for j:=1 to 256 do if s1=number[j] then s1:=alfabet[j]; end;
     else begin s1:=s[i]; i:=i+1; end; end;
     if bl then
     begin
       if s1=' ' then bl:=false;
       if s1='1  ' then begin s2:=s2+#13+#10; i:=i+12 end else
       if s1<>'90 ' then s2:=s2+s1;
     end;
   end;
   form1.Memo2.Text:=s2;
end;

procedure TForm1.Button1Click(Sender: TObject);
var s,s1: string;
i: integer;
begin
    edit1.Text:='';
    memo1.Lines.Text:='';
    opendialog1.Execute;
    s:=opendialog1.Files.Text;
    for i:=1 to (length(s)-2) do
    edit1.Text:=edit1.Text+s[i];
    if edit1.Text<>'' then memo1.Lines.LoadFromFile(edit1.Text);

    {i:=1;
    while s[i]<>'.' do
    begin s1:=s1+s[i]; i:=i+1; end;

    m.Text:='';
    m.Lines.Add('copy '+edit1.Text+' '+s1+'.txt');
    m.Lines.Add('del bat.bat');
    m.Lines.SaveToFile('bat.bat');
    WinExec('bat.bat', SW_HIDE);
    sleep(1000);
    memo1.Lines.LoadFromFile(s1+'.txt');
    sleep(1000);
    m.Text:='';
    m.Lines.Add('del '+s1+'.txt');
    m.Lines.Add('del bat.bat');
    m.Lines.SaveToFile('bat.bat');
    WinExec('bat.bat', SW_HIDE); }
end;

procedure TForm1.FormCreate(Sender: TObject);
var j: integer;
begin
sdvig:=1;
loadalfabet();
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
uncrypt(sdvig);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
if sdvig>1 then sdvig:=sdvig-1;
uncrypt(sdvig);
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
if sdvig<6 then sdvig:=sdvig+1;
uncrypt(sdvig);
end;

procedure TForm1.Button3Click(Sender: TObject);
var s,s1: string;
i: integer;
begin
    savedialog1.Execute;
    s:=savedialog1.Files.Text;
    for i:=1 to (length(s)-2) do
    s1:=s1+s[i];
    if s1<>'' then memo2.Lines.SaveToFile(s1+'.txt');
end;

end.