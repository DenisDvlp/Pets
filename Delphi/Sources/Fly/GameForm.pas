unit GameForm;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Controls, FMX.Forms, FMX.Graphics, FMX.Dialogs, FMX.Ani,
  FMX.Objects, FMX.Layouts, FMX.Media;

type
  TForm1 = class(TForm)
    animUpDown: TFloatAnimation;
    animRotate: TFloatAnimation;
    imBoat: TImage;
    imSea: TImage;
    MainTimer: TTimer;
    imPlane: TImage;
    imSky: TImage;
    imStar1: TImage;
    animOpacity1: TFloatAnimation;
    rectOption: TRectangle;
    Text2: TText;
    Layout1: TLayout;
    Rectangle2: TRectangle;
    Text1: TText;
    imStar2: TImage;
    animOpacity2: TFloatAnimation;
    imStar3: TImage;
    animOpacity3: TFloatAnimation;
    imStar4: TImage;
    animOpacity4: TFloatAnimation;
    animDamage: TFloatAnimation;
    textScore: TText;
    Image1: TImage;
    FloatAnimation1: TFloatAnimation;
    LayoutSky: TLayout;
    Text3: TText;
    procedure MainTimerTimer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Single);
    procedure FormMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Single);
    procedure FormResize(Sender: TObject);
    procedure Rectangle2Click(Sender: TObject);
  private
    g, moving: Single;
    touching, damaged: Boolean;
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.fmx}

procedure TForm1.FormCreate(Sender: TObject);
begin
  g := -4;
  moving := 4;
  touching := False;
  damaged := False;
  rectOption.Visible := True;
  animDamage.Enabled := False;
  imPlane.Position.Y := ClientWidth * 0.25;
  imBoat.Position.X := ClientWidth;
end;

procedure TForm1.FormMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Single);
begin
  touching := True;
end;

procedure TForm1.FormMouseUp(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Single);
begin
  touching := False;
end;

procedure TForm1.FormResize(Sender: TObject);
begin
  imBoat.Height := 0.5 * ClientHeight;
  imBoat.Width := 1.06 * imBoat.Height;
  imBoat.Position.Y := imSea.Position.Y - (imBoat.RotationCenter.Y) * imBoat.Height;
  animUpDown.StartValue := imBoat.Position.Y;
  animUpDown.StopValue := imBoat.Position.Y - 10;
  imBoat.Position.X := ClientWidth;
  imStar1.Position.X := ClientWidth * 0.25;
  imStar2.Position.X := ClientWidth * 0.5;
  imStar3.Position.X := ClientWidth * 0.75;
  imStar4.Position.X := ClientWidth * 1;
end;

procedure TForm1.MainTimerTimer(Sender: TObject);
const
  maxg = 6;
  procedure StarProc(imStar: TImage);
  begin
    imStar.Position.X := imStar.Position.X - moving;
    if imStar.Position.X + imStar.Width <= 0 then
    begin
      imStar.Position.X := ClientWidth;
      imStar.Position.Y := Random(Round(
        ClientHeight - imStar.Height - imSea.Height - 20)) + 10;
      imStar.Opacity := 1;
      (imStar.Children[0] as TFloatAnimation).Enabled := False;
    end;
    if imPlane.AbsoluteRect.CenterPoint.Distance(
       imStar.AbsoluteRect.CenterPoint) <= imStar.Width then
    begin
       (imStar.Children[0] as TFloatAnimation).Enabled := True;
       textScore.Text := IntToStr(StrToInt(textScore.Text) + 1);
    end;
  end;
begin
  //plane
  imPlane.Position.Y := imPlane.Position.Y + g;
  if not damaged then
    imPlane.RotationAngle := 30 * g / maxg;
  if touching and not damaged then
    g := g - imPlane.Position.Y / ClientHeight * 1;
  g := g + 0.1;
  if g < -maxg then g := -maxg;

  //boat
  imBoat.Position.X := imBoat.Position.X - moving;
  if imBoat.Position.X + imBoat.Width <= 0 then
    imBoat.Position.X := ClientWidth;

  //star 1
  StarProc(imStar1);
  //star 2
  StarProc(imStar2);
  //star 3
  StarProc(imStar3);
  //star 4
  StarProc(imStar4);

  //plane and boat
  if imPlane.AbsoluteRect.CenterPoint.Distance(
     imBoat.AbsoluteRect.CenterPoint) <= imBoat.Width / 2 then
  begin
    damaged := True;
    animDamage.Enabled := True;
  end;

  //plane and sea
  if imPlane.Position.Y + imPlane.Height * 0.8 > imSea.Position.Y then
  begin
    MainTimer.Enabled := False;
    rectOption.Visible := True;
    if text3.Text.Equals('') or (StrToInt(textScore.Text) > StrToInt(text3.Text)) then
      text3.Text := textScore.Text;
    text2.Text := 'BEST SCORE';
  end;

end;

procedure TForm1.Rectangle2Click(Sender: TObject);
begin
  FormCreate(nil);
  MainTimer.Enabled := True;
  rectOption.Visible := False;
end;

end.
