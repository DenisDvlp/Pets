unit AI;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls;

type
  TForm1 = class(TForm)
    Edit1: TEdit;
    Memo1: TMemo;
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  str: string;
  procedure AI();
implementation

{$R *.dfm}


procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
if (key=#13)and(edit1.Text<>'') then
begin
  memo1.Lines.Add(edit1.Text);
  str:=edit1.Text;
  edit1.Text:='';
  AI();
end;

end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  memo1.Text:='';
  setlength(str,256);
end;

procedure AI();
var i: integer;
begin
  for i:=1 to 252 do
  begin
    if (str[i]='п')and(str[i+1]='л')and(str[i+2]='а')and(str[i+3]='н')then
    form1.memo1.lines.add('ПЛАН НА ДЕНЬ ещё не составлен');
  end;
end;

end.
