unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls, ComCtrls;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Panel2: TPanel;
    Panel3: TPanel;
    Panel4: TPanel;
    Panel5: TPanel;
    Panel6: TPanel;
    Panel7: TPanel;
    Panel8: TPanel;
    Panel9: TPanel;
    Panel10: TPanel;
    Panel11: TPanel;
    Panel12: TPanel;
    Panel13: TPanel;
    Panel14: TPanel;
    Panel15: TPanel;
    Panel16: TPanel;
    Panel17: TPanel;
    Panel18: TPanel;
    Panel19: TPanel;
    Panel20: TPanel;
    Panel21: TPanel;
    Panel22: TPanel;
    Panel23: TPanel;
    Panel24: TPanel;
    Panel25: TPanel;
    Panel26: TPanel;
    Panel27: TPanel;
    Panel28: TPanel;
    Panel29: TPanel;
    Panel30: TPanel;
    Panel31: TPanel;
    Panel32: TPanel;
    Panel33: TPanel;
    Panel34: TPanel;
    Panel35: TPanel;
    Panel36: TPanel;
    Panel37: TPanel;
    Panel38: TPanel;
    Panel39: TPanel;
    Panel40: TPanel;
    Panel41: TPanel;
    Panel42: TPanel;
    Panel43: TPanel;
    Panel44: TPanel;
    Panel45: TPanel;
    Panel46: TPanel;
    Panel47: TPanel;
    Panel48: TPanel;
    Panel49: TPanel;
    Panel50: TPanel;
    Panel51: TPanel;
    Panel52: TPanel;
    Panel53: TPanel;
    Panel54: TPanel;
    Panel55: TPanel;
    Panel56: TPanel;
    Panel57: TPanel;
    Panel58: TPanel;
    Panel59: TPanel;
    Panel60: TPanel;
    Panel61: TPanel;
    Panel62: TPanel;
    Panel63: TPanel;
    Panel64: TPanel;
    Panel65: TPanel;
    Panel66: TPanel;
    Panel67: TPanel;
    Panel68: TPanel;
    Panel69: TPanel;
    Panel70: TPanel;
    Panel71: TPanel;
    Panel72: TPanel;
    Panel73: TPanel;
    Panel74: TPanel;
    Panel75: TPanel;
    Panel76: TPanel;
    Panel77: TPanel;
    Panel78: TPanel;
    Panel79: TPanel;
    Panel80: TPanel;
    Panel81: TPanel;
    Panel86: TPanel;
    GroupBox1: TGroupBox;
    ComboBox1: TComboBox;
    Button3: TButton;
    Button2: TButton;
    GroupBox2: TGroupBox;
    Button1: TButton;
    Button4: TButton;
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
{const
       N = 6;  //не может быть меньше 1 }
var
  Form1: TForm1;
  bl: array [1..729] of boolean;
  nextseqgeneration: boolean;
  blfield,blcounted: array [1..81] of boolean;
  field,seq: array [1..81] of integer;
  numberofindependentcells,numberofconnectedcells,N,M,variants: integer;
implementation

{$R *.dfm}

function cel(x,y: integer):tpanel;
begin
with form1 do
begin
  case x of
    1:case y of
        1: result:=panel1;
        2: result:=panel2;
        3: result:=panel3;
        4: result:=panel4;
        5: result:=panel5;
        6: result:=panel6;
        7: result:=panel7;
        8: result:=panel8;
        9: result:=panel9;
      end;
    2:case y of
        1: result:=panel10;
        2: result:=panel11;
        3: result:=panel12;
        4: result:=panel13;
        5: result:=panel14;
        6: result:=panel15;
        7: result:=panel16;
        8: result:=panel17;
        9: result:=panel18;
      end;
    3:case y of
        1: result:=panel19;
        2: result:=panel20;
        3: result:=panel21;
        4: result:=panel22;
        5: result:=panel23;
        6: result:=panel24;
        7: result:=panel25;
        8: result:=panel26;
        9: result:=panel27;
      end;
    4:case y of
        1: result:=panel28;
        2: result:=panel29;
        3: result:=panel30;
        4: result:=panel31;
        5: result:=panel32;
        6: result:=panel33;
        7: result:=panel34;
        8: result:=panel35;
        9: result:=panel36;
      end;
    5:case y of
        1: result:=panel37;
        2: result:=panel38;
        3: result:=panel39;
        4: result:=panel40;
        5: result:=panel41;
        6: result:=panel42;
        7: result:=panel43;
        8: result:=panel44;
        9: result:=panel45;
      end;
    6:case y of
        1: result:=panel46;
        2: result:=panel47;
        3: result:=panel48;
        4: result:=panel49;
        5: result:=panel50;
        6: result:=panel51;
        7: result:=panel52;
        8: result:=panel53;
        9: result:=panel54;
      end;
    7:case y of
        1: result:=panel55;
        2: result:=panel56;
        3: result:=panel57;
        4: result:=panel58;
        5: result:=panel59;
        6: result:=panel60;
        7: result:=panel61;
        8: result:=panel62;
        9: result:=panel63;
      end;
    8:case y of
        1: result:=panel64;
        2: result:=panel65;
        3: result:=panel66;
        4: result:=panel67;
        5: result:=panel68;
        6: result:=panel69;
        7: result:=panel70;
        8: result:=panel71;
        9: result:=panel72;
      end;
    9:case y of
        1: result:=panel73;
        2: result:=panel74;
        3: result:=panel75;
        4: result:=panel76;
        5: result:=panel77;
        6: result:=panel78;
        7: result:=panel79;
        8: result:=panel80;
        9: result:=panel81;
      end;
  end;
end;
end;

function blcntd(x,y: integer): boolean;
begin
result:=blcounted[(x-1)*N+y];
end;

procedure blcntdinit(x,y: integer; b: boolean);
begin
blcounted[(x-1)*N+y]:=b;
end;

function blfld(x,y: integer): boolean;
begin
result:=blfield[(x-1)*N+y];
end;

procedure blfldinit(x,y: integer; b: boolean);
begin
blfield[(x-1)*N+y]:=b;
end;

function fld(x,y: integer): integer;
begin
result:=field[(x-1)*N+y];
end;

procedure fldinit(x,y,f: integer);
begin
field[(x-1)*N+y]:=f;
end;

function sq(x,y: integer): integer;
begin
result:=seq[(x-1)*N+y];
end;

procedure sqinit(x,y,s: integer);
begin
seq[(x-1)*N+y]:=s;
end;

function bln(x,y,num: integer): boolean;
begin
result:=bl[x*N*N+y*N-N*(N+1)+num];
end;

procedure blninit(x,y,num: integer; b: boolean);
begin
bl[x*N*N+y*N-N*(N+1)+num]:=b;
end;

procedure defaultfld();
var i,j: integer;
begin
  N:=9;
  for i:=1 to 9 do
  for j:=1 to 9 do begin cel(i,j).Caption:=''; cel(i,j).Color:=clbtnface; end;
  for i:=1 to N*N do field[i]:=0;

  fldinit(1,1,1);
  fldinit(2,1,1);
  fldinit(3,1,1);
  fldinit(1,2,1);
  fldinit(2,2,1);
  fldinit(3,2,1);
  fldinit(1,3,1);
  fldinit(2,3,1);
  fldinit(3,3,1);

  fldinit(4,1,2);
  fldinit(5,1,2);
  fldinit(6,1,2);
  fldinit(4,2,2);
  fldinit(5,2,2);
  fldinit(6,2,2);
  fldinit(4,3,2);
  fldinit(5,3,2);
  fldinit(6,3,2);

  fldinit(7,1,3);
  fldinit(8,1,3);
  fldinit(9,1,3);
  fldinit(7,2,3);
  fldinit(8,2,3);
  fldinit(9,2,3);
  fldinit(7,3,3);
  fldinit(8,3,3);
  fldinit(9,3,3);

  fldinit(1,4,4);
  fldinit(2,4,4);
  fldinit(3,4,4);
  fldinit(1,5,4);
  fldinit(2,5,4);
  fldinit(3,5,4);
  fldinit(1,6,4);
  fldinit(2,6,4);
  fldinit(3,6,4);

  fldinit(4,4,5);
  fldinit(5,4,5);
  fldinit(6,4,5);
  fldinit(4,5,5);
  fldinit(5,5,5);
  fldinit(6,5,5);
  fldinit(4,6,5);
  fldinit(5,6,5);
  fldinit(6,6,5);

  fldinit(7,4,6);
  fldinit(8,4,6);
  fldinit(9,4,6);
  fldinit(7,5,6);
  fldinit(8,5,6);
  fldinit(9,5,6);
  fldinit(7,6,6);
  fldinit(8,6,6);
  fldinit(9,6,6);

  fldinit(1,7,7);
  fldinit(2,7,7);
  fldinit(3,7,7);
  fldinit(1,8,7);
  fldinit(2,8,7);
  fldinit(3,8,7);
  fldinit(1,9,7);
  fldinit(2,9,7);
  fldinit(3,9,7);

  fldinit(4,7,8);
  fldinit(5,7,8);
  fldinit(6,7,8);
  fldinit(4,8,8);
  fldinit(5,8,8);
  fldinit(6,8,8);
  fldinit(4,9,8);
  fldinit(5,9,8);
  fldinit(6,9,8);

  fldinit(7,7,9);
  fldinit(8,7,9);
  fldinit(9,7,9);
  fldinit(7,8,9);
  fldinit(8,8,9);
  fldinit(9,8,9);
  fldinit(7,9,9);
  fldinit(8,9,9);
  fldinit(9,9,9);


  for i:=1 to N do
  for j:=1 to N do
  case fld(i,j) of
  1:cel(i,j).Color:=clred;
  2:cel(i,j).Color:=claqua;
  3:cel(i,j).Color:=clMoneyGreen;
  4:cel(i,j).Color:=clgreen;
  5:cel(i,j).Color:=clfuchsia;
  6:cel(i,j).Color:=clyellow;
  7:cel(i,j).Color:=clskyblue;
  8:cel(i,j).Color:=clolive;
  9:cel(i,j).Color:=clteal;
  end;

end;

procedure sequentialgenerator();
var i,j,k,l,nexti,nextj: integer;
    b,b1: boolean;
begin
  form1.Caption:='Поиск ...';
  //инициализация таблицы последовательности цифр
  if nextseqgeneration then
  begin
    for i:=1 to N*N do seq[i]:=1;
    nextseqgeneration:=false;
  end;
  //переменная вгоняющая в цикл последовательного перебора
  //до тех пор пока не найдёт подходящую или не пройдёт все возможные варианты таблиц
  b:=true;
while b do
begin
  //инициализация таблицы разрешений установки цифр
  for i:=1 to N*N*N do bl[i]:=true;
  //переменная позволяющая прекратить выполнение цикла заполнения таблицы цифр
  //если будет найдена невозможность создать судоку
  b1:=true;
  for i:=1 to N do
  if b1 then
  for j:=1 to N do
  begin
    if (i=1)and(j=1) then
    begin
      if seq[1]=N then begin seq[1]:=1; seq[2]:=seq[2]+1; end else seq[1]:=seq[1]+1;
      //cel(1,1).Caption:=inttostr(seq[1]);
      for k:=1 to N do blninit(k,1,seq[1],false);
      for k:=1 to N do blninit(1,k,seq[1],false);
      for k:=1 to N do
      for l:=1 to N do if fld(k,l)=fld(i,j) then blninit(k,l,seq[1],false);
    end else
    if (i=N)and(j=N) then
    begin
      if sq(N,N)>N then
      begin
        seq[N*N]:=N;
        b:=false;
        b1:=false;
        nextseqgeneration:=true;
        break;
      end else
      if bln(N,N,sq(N,N)) then
      begin
        //cel(N,N).Caption:=inttostr(sq(N,N));
        variants:=variants+1;
        b:=false;
      end else
      begin
        b1:=false;
        break;
      end;
    end else
    begin
      if j=N then begin nexti:=i+1; nextj:=1; end else begin nexti:=i; nextj:=j+1; end;
      if sq(i,j)>N then begin sqinit(i,j,1); sqinit(nexti,nextj,sq(nexti,nextj)+1); end;
      if bln(i,j,sq(i,j)) then
      begin
        //cel(i,j).Caption:=inttostr(sq(i,j));
        for k:=i to N do blninit(k,j,sq(i,j),false);
        for k:=j to N do blninit(i,k,sq(i,j),false);
        for k:=1 to N do
        for l:=1 to N do if fld(k,l)=fld(i,j) then blninit(k,l,sq(i,j),false);
      end else
      begin
        b1:=false;
        break;
      end;
    end;
  end else break;
  form1.Caption:='Поиск '+inttostr(round(((seq[N*N]-1)*N*N*N+(seq[N*N-1]-1)*N*N+(seq[N*N-2]-1)*N+seq[N*N-3])*100/(N*N*N*N)))+' %';
end;
  form1.Caption:='Поиск завершён на '+inttostr(round(((seq[N*N]-1)*N*N*N+(seq[N*N-1]-1)*N*N+(seq[N*N-2]-1)*N+seq[N*N-3])*100/(N*N*N*N)))+' %';
  if variants>0 then
  for i:=1 to N do
  for j:=1 to N do cel(i,j).Caption:=inttostr(sq(i,j));
  if nextseqgeneration then
  if variants>0 then
  begin
    ShowMessage('Для текущих областей варианты судоку исчерпаны.'+#13+#10+'Всего найдено '+inttostr(variants)+ ' вариантов.');
    variants:=0;
  end else ShowMessage('Для текущих областей не существует вариантов судоку.'+#13+#10+'Попробуйте сгенерировать другие области.');
end;

procedure randomgenerate();
var temp,i,j,k,l: integer;
    b,b1,b2: boolean;
begin
//переменные для отображения процентов генераций
M:=1;
form1.Caption:='Поиск 0 %';
//переменная вгоняющая в цикл генераций
//до тех пор пока не найдёт подходящую или не пройдёт 100000 таблиц
b:=true;
while b do
begin
  //инициализация таблицы разрешений установки цифр
  for i:=1 to N*N*N do bl[i]:=true;
  //переменная позволяющая прекратить выполнение цикла заполнения таблицы цифр
  //если будет найдена невозможность создать судоку
  b1:=true;
  for i:=1 to N do
  if b1 then
  for j:=1 to N do
  begin
    //переменная прекращающая выполнение цикла если не найдёт разрешённых цифр
    b1:=false;
    for k:=1 to N do if bln(i,j,k) then begin b1:=true; break; end;
    //условие если есть разрешённые цифры
    if b1 then
    begin
      //случайный поиск разрешённой цифры
      temp:=random(N)+1;
      while bln(i,j,temp)=false do
      begin
        temp:=random(N)+1;
      end;
      //после удачного выбора цифры запись её в ячейку
      cel(i,j).Caption:=inttostr(temp);
      //циклы запрещающие ставить установленную цифру
      //в других ячейках следуя правилам судоку
      for k:=i to N do blninit(k,j,temp,false);
      for k:=j to N do blninit(i,k,temp,false);
      for k:=1 to N do
      for l:=1 to N do if fld(k,l)=fld(i,j) then blninit(k,l,temp,false);
      //условие выхода из общего цикла, если была выбрана последняя цифра в таблице.
      if (i=N)and(j=N) then b:=false;
    end
    //условие если нет разрешённых цифр, выходит из цикла и начинает заново
    else break;
  end else break;
  M:=M+1;
  form1.Caption:='Поиск '+inttostr(round(M/1000))+' %';
  if M>100000 then
  begin
    b:=false;
    ShowMessage('Не удалось составить судоку для текущих областей.'+#13+#10+'Попробуйте сгенерировать другие области или попробуйте ещё раз.');
  end;
end;
form1.Caption:='Поиск завершён на '+inttostr(round(M/1000))+' %';
end;

procedure freecells(x,y: integer);
begin
  if (x>0)and(x<N+1)and(y>0)and(y<N+1)and(fld(x,y)=0)and(blcntd(x,y)=false) then
  begin
    numberofconnectedcells:=numberofconnectedcells+1;
    blcntdinit(x,y,true);
    freecells(x-1,y);
    freecells(x+1,y);
    freecells(x,y-1);
    freecells(x,y+1);
  end;
end;

function integrity(): boolean;
var b: boolean;
    x,y,i,j: integer;
begin
  b:=false;
  numberofindependentcells:=0;
  numberofconnectedcells:=0;
  for i:=1 to N*N do blcounted[i]:=false;

  for i:=1 to N*N do if field[i]=0 then numberofindependentcells:=numberofindependentcells+1;
  for i:=1 to N do
  for j:=1 to N do
  if (fld(i,j)=0) then begin x:=i; y:=j; b:=true; break; end;

  if b then freecells(x,y);

  if numberofindependentcells=numberofconnectedcells then result:=true else result:=false;
end;

function defineborders(f: integer): boolean;
var i,j: integer;
    b: boolean;
begin
  for i:=1 to N*N do blfield[i]:=false;
  for i:=1 to N do
  for j:=1 to N do if cel(i,j).Color=clsilver then cel(i,j).Color:=clBtnFace;

  for i:=1 to N do
  for j:=1 to N do
  if (fld(i,j)=0) then
  begin
    b:=false;
    if ((i+1<N+1)and(fld(i+1,j)=f))or
       ((i-1>0)  and(fld(i-1,j)=f))or
       ((j+1<N+1)and(fld(i,j+1)=f))or
       ((j-1>0)  and(fld(i,j-1)=f))then b:=true;
    if b then
    begin
      fldinit(i,j,-1);
      if integrity then begin blfldinit(i,j,true); end;
      fldinit(i,j,0);
    end;
  end;
end;

procedure generatefields();
var x,y,i,j,k: integer;
    b,b1: boolean;
begin
  for i:=1 to 9 do
  for j:=1 to 9 do begin cel(i,j).Color:=clblack; cel(i,j).Caption:=''; end;
b1:=true;
while b1 do
begin
  for i:=1 to N*N do
  begin
    blfield[i]:=false;
    field[i]:=0;
  end;

  for i:=1 to N do
  begin
    for j:=1 to N do
    begin
      if j=1 then for k:=1 to N*N do if field[k]=0 then begin blfield[k]:=true; break; end;
      b:=false;
      for k:=1 to N*N do if blfield[k]=true then begin b:=true; break; end;
      if b then
      begin
        x:=random(N)+1;
        y:=random(N)+1;
        while blfld(x,y)=false do
        begin
          x:=random(N)+1;
          y:=random(N)+1;
        end;
        fldinit(x,y,i);
        case i of
        1:cel(x,y).Color:=clred;
        2:cel(x,y).Color:=claqua;
        3:cel(x,y).Color:=clMoneyGreen;
        4:cel(x,y).Color:=clgreen;
        5:cel(x,y).Color:=clfuchsia;
        6:cel(x,y).Color:=clyellow;
        7:cel(x,y).Color:=clskyblue;
        8:cel(x,y).Color:=clolive;
        9:cel(x,y).Color:=clteal;
        end;
        defineborders(i);
      end;
    end;
  end;
  b1:=false;
  for k:=1 to N*N do if field[k]=0 then begin b1:=true; break; end;
end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var i,j: integer;
begin
  Randomize;
  nextseqgeneration:=true;
  variants:=0;
  defaultfld;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  nextseqgeneration:=true;
  randomgenerate;
end;
procedure TForm1.Button3Click(Sender: TObject);
var s: string;
begin
  s:=ComboBox1.Text;
  if length(s)=1 then
  begin
    if (s[1]='2')or(s[1]='3')or(s[1]='4')or(s[1]='5')or
      (s[1]='6')or(s[1]='7')or(s[1]='8')or(s[1]='9')then
    begin
      N:=strtoint(s[1]);
    end;
  end;
  nextseqgeneration:=true;
  generatefields;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  defaultfld;
  nextseqgeneration:=true;
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
sequentialgenerator;
end;

end.
