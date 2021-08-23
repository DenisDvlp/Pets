unit Unit1;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, FMX.Objects,
  System.ImageList, FMX.ImgList, FMX.Ani, FMX.Controls.Presentation,
  FMX.StdCtrls, FMX.Platform, FMX.Layouts;

type
  TForm1 = class(TForm)
    ImageList1: TImageList;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Image5: TImage;
    Image6: TImage;
    Image7: TImage;
    Image8: TImage;
    Image9: TImage;
    FloatAnimation1: TFloatAnimation;
    FloatAnimation2: TFloatAnimation;
    FloatAnimation3: TFloatAnimation;
    FloatAnimation4: TFloatAnimation;
    FloatAnimation5: TFloatAnimation;
    FloatAnimation6: TFloatAnimation;
    FloatAnimation7: TFloatAnimation;
    FloatAnimation8: TFloatAnimation;
    FloatAnimation9: TFloatAnimation;
    Label1: TLabel;
    Label2: TLabel;
    Image10: TImage;
    Image11: TImage;
    Label4: TLabel;
    Label5: TLabel;
    Label6: TLabel;
    Label7: TLabel;
    Label8: TLabel;
    Image12: TImage;
    Image13: TImage;
    Image14: TImage;
    Rectangle1: TRectangle;
    Image15: TImage;
    Layout1: TLayout;
    Layout2: TLayout;
    Layout3: TLayout;
    Layout4: TLayout;
    Layout5: TLayout;
    Layout6: TLayout;
    Layout7: TLayout;
    Layout8: TLayout;
    Layout9: TLayout;
    procedure FormCreate(Sender: TObject);
    procedure FloatAnimation1Finish(Sender: TObject);
    procedure Layout1MouseEnter(Sender: TObject);
  private
    ScreenScale: Single;

    function  GetImage(Index: Integer): TImage;
    function  GetAnimation(Index: Integer): TFloatAnimation;
    function  GetLayout(Index: Integer): TLayout;

    property image [Index: Integer] : TImage read GetImage;
    property animation [Index: Integer] : TFloatAnimation read GetAnimation;
    property layout [Index: Integer] : TLayout read GetLayout;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.fmx}

{ TForm1 }


procedure TForm1.FloatAnimation1Finish(Sender: TObject);
var
  i, j: Integer;
begin
  j :=(Sender as TFmxObject).Parent.Tag;
  if animation[j].Tag = 0 then
  begin
    if image[j].Tag = 1 then
    Label5.Text := IntToStr(StrToInt(Label5.Text) + 1) else
    Label7.Text := IntToStr(StrToInt(Label7.Text) + 1);
    Label4.Text := IntToStr(
    Round(100 * StrToInt(Label2.Text)/
    (StrToInt(Label1.Text) + StrToInt(Label7.Text)))) + ' %';
    animation[j].Tag := 1;
    animation[j].StopValue := layout[j].Position.Y + image[j].Height;
    animation[j].Delay := Random(80) / 100 + 0.8;
    animation[j].Start;
  end else
  begin
    i := Random(2);
    image[j].Bitmap.Assign(ImageList1.Bitmap(
    TSizeF.Create(image[j].Width * ScreenScale, image[j].Height * ScreenScale), i));
    image[j].Tag := i;
    animation[j].Tag := 0;
    animation[j].StopValue := layout[j].Position.Y - image[j].Height;
    animation[j].Delay := Random(80) / 100 + 0.4;
    animation[j].Start;
  end;
end;

procedure TForm1.FormCreate(Sender: TObject);
var
  i: Integer;   var
  Screen: IFMXScreenService;
begin
  if TPlatformServices.Current.SupportsPlatformService(IFMXScreenService, IInterface(Screen)) then
    ScreenScale := Screen.GetScreenScale;

  for i := 0 to 8 do
  begin
    image[i].Bitmap.Assign(ImageList1.Bitmap(
    TSizeF.Create(image[i].Width, image[i].Height),0));
    animation[i].StopValue := layout[i].Position.Y - image[i].Height;
    animation[i].Start;
  end;
  image10.Bitmap.Assign(ImageList1.Bitmap(
  TSizeF.Create(image10.Width * ScreenScale, image10.Height * ScreenScale),0));
  image11.Bitmap.Assign(ImageList1.Bitmap(
  TSizeF.Create(image10.Width * ScreenScale, image10.Height * ScreenScale),1));
end;

function TForm1.GetAnimation(Index: Integer): TFloatAnimation;
begin
  Result := nil;
  case Index of
    0: Result := FloatAnimation1;
    1: Result := FloatAnimation2;
    2: Result := FloatAnimation3;
    3: Result := FloatAnimation4;
    4: Result := FloatAnimation5;
    5: Result := FloatAnimation6;
    6: Result := FloatAnimation7;
    7: Result := FloatAnimation8;
    8: Result := FloatAnimation9;
  end;
end;

function TForm1.GetImage(Index: Integer): TImage;
begin
  Result := nil;
  case Index of
    0: Result := Image1;
    1: Result := Image2;
    2: Result := Image3;
    3: Result := Image4;
    4: Result := Image5;
    5: Result := Image6;
    6: Result := Image7;
    7: Result := Image8;
    8: Result := Image9;
  end;
end;

function TForm1.GetLayout(Index: Integer): TLayout;
begin
  Result := nil;
  case Index of
    0: Result := Layout1;
    1: Result := Layout2;
    2: Result := Layout3;
    3: Result := Layout4;
    4: Result := Layout5;
    5: Result := Layout6;
    6: Result := Layout7;
    7: Result := Layout8;
    8: Result := Layout9;
  end;
end;

procedure TForm1.Layout1MouseEnter(Sender: TObject);
var
  i: Integer;
begin
  i :=(Sender as TFmxObject).Tag;
  if animation[i].Tag = 0 then Exit;
  layout[i].Position.Y := animation[i].StartValue;
  if image[i].Tag = 0 then
    Label1.Text := IntToStr(StrToInt(Label1.Text) + 1)
  else
    Label2.Text := IntToStr(StrToInt(Label2.Text) + 1);
  Label4.Text := IntToStr(
  Round(100 * StrToInt(Label2.Text)/
  (StrToInt(Label1.Text) + StrToInt(Label7.Text)))) + ' %';
end;

end.
