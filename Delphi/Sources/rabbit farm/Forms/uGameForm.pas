unit uGameForm;

interface

uses
  System.SysUtils, System.Types, System.UITypes, System.Classes, System.Variants,
  FMX.Types, FMX.Graphics, FMX.Controls, FMX.Forms, FMX.Dialogs, FMX.StdCtrls,
  uScaleForm, FMX.Objects, FMX.Layouts, FMX.Ani, FMX.ExtCtrls, uUtils,
  FMX.Controls.Presentation, FMX.ScrollBox, FMX.Memo, uAnimal, FMX.Effects;

type
  TGameForm = class(TScaleForm)
    imBackground: TImage;
    InitTimer: TTimer;
    ThinkTimer: TTimer;
    ScoreLayout: TLayout;
    icon: TImage;
    ScoreText: TText;
    ScoreLayoutGlowEffect: TGlowEffect;
    procedure FormCreate(Sender: TObject);
    procedure ThinkTimerTimer(Sender: TObject);
    procedure InitTimerTimer(Sender: TObject);
  private
    FCarrotCount: Cardinal;
    GrassImages,
    MeadowPositions,
    CarrotImages: TImageExArray;
    GrassBitmapListAnimations,
    AnimalBitmapListAnimations: TBitmapListAnimationArray;
    Rabbits: array of TAnimal;
    procedure CreateObjects;
    procedure OrderObjects;

    procedure OnIn(Row, Col: Integer);
    procedure OnOut(Row, Col: Integer);
    procedure OnShowed(Row, Col: Integer);
    procedure OnDead(Row, Col: Integer);
    procedure OnStole;
    procedure Kill(Sender: TObject);
    procedure OnEnter(Sender: TObject);
    procedure setCarrotCount(const Value: Cardinal);

    property CarrotCount: Cardinal read FCarrotCount write setCarrotCount;
  public
    { Public declarations }
  end;

var
  GameForm: TGameForm;

implementation

uses
  uData, System.DateUtils;

{$R *.fmx}

procedure TGameForm.CreateObjects;

const
  groundHight = 600;

  grassLeft = 0;
  grassTop = 180;
  grassRight = 390;
  grassBottom = 410;
  grassRowHeight = 23;
  grassColWidth = 30;
  grassWidth = 30;
  grassHeight = 85;

  positionLeft = 36;
  positionTop = 210;
  positionRight = 324;
  positionBottom = 387;
  positionRowHeight = 69;
  positionColWidth = 70;
  positionWidth = 70;
  positionHeight = 125;

  carrotLeft = 36;
  carrotTop = 420;
  carrotRight = 324;
  carrotBottom = 490;
  carrotRowHeight = 15;
  carrotColWidth = 29;
  carrotWidth = 29;
  carrotHeight = 38;
var
  bounds: TBounds;
  i, j, count: Integer;
  size: TSizeF;
begin
  bounds := TBounds.Create(RectF(grassLeft, grassTop, grassRight, grassBottom));
  CreateImagesPerspective(GrassImages, bounds, groundHight,
    grassWidth, grassHeight, grassRowHeight, grassColWidth);
  size := TSizeF.Create(90, 255);
  count := Datas.GrassImageList.Destination.Count;
  for i := 0 to Length(GrassImages) - 1 do
  for j := 0 to Length(GrassImages[i]) - 1 do
    GrassImages[i, j].Bitmap.Assign(Datas.GrassImageList.Bitmap(size, Random(count)));

  bounds := TBounds.Create(RectF(positionLeft, positionTop, positionRight, positionBottom));
  CreateImagesPerspective(MeadowPositions, bounds, groundHight,
    positionWidth, positionHeight, positionRowHeight, positionColWidth);
  for i := 0 to Length(MeadowPositions) - 1 do
  for j := 0 to Length(MeadowPositions[i]) - 1 do
    MeadowPositions[i, j].OnClick := kill;

  bounds := TBounds.Create(RectF(carrotLeft, carrotTop, carrotRight, carrotBottom));
  CreateImages(CarrotImages, bounds,
    carrotWidth, carrotHeight, carrotRowHeight, carrotColWidth);
  for i := 0 to Length(CarrotImages) - 1 do
  for j := 0 to Length(CarrotImages[i]) - 1 do
  begin
    with (CarrotImages[i, j].Children[0] as TBitmapListAnimation) do
    begin
      AnimationBitmap.Assign(Datas.CarrotAnimationList.Source[0].MultiResBitmap[0].Bitmap);
      Interpolation := TInterpolationType.Quartic;
    end;
    CarrotImages[i, j].OnMouseEnter := OnEnter;
    CarrotImages[i, j].HitTest := True;
  end;
end;

procedure TGameForm.OrderObjects;
var
  i, j, k, l, count, next: Integer;
  min, prevmin: Single;
  orderArray, tmp: TImageExArray;
begin
  count := Length(MeadowPositions) + Length(GrassImages) + Length(CarrotImages);
  SetLength(orderArray, count);
  prevmin := 0;
  next := 0;
  while next < count do
  begin
    min := ClientHeight;
    for j := 0 to 2 do
    begin
      case j of
        0: tmp := MeadowPositions;
        1: tmp := GrassImages;
        2: tmp := CarrotImages;
      end;
      for k := 0 to Length(tmp) - 1 do
      if (tmp[k, 0].AbsoluteRect.Bottom < min) and
         (tmp[k, 0].AbsoluteRect.Bottom > prevmin) then
        min := tmp[k, 0].AbsoluteRect.Bottom;
    end;
    prevmin := min;
    for j := 0 to 2 do
    begin
      case j of
        0: tmp := MeadowPositions;
        1: tmp := CarrotImages;
        2: tmp := GrassImages;
      end;
      for k := 0 to Length(tmp) - 1 do
      if tmp[k, 0].AbsoluteRect.Bottom = min then
      begin
        orderArray[next] := tmp[k];
        Inc(next);
      end;
    end;
  end;
  for i := 0 to Length(orderArray) - 1 do
  for j := 0 to Length(orderArray[i]) - 1 do
    orderArray[i, j].Parent := MainLayout;
end;

procedure TGameForm.setCarrotCount(const Value: Cardinal);
begin
  FCarrotCount := Value;
  ScoreText.Text := IntToStr(Value);
end;

procedure TGameForm.OnEnter(Sender: TObject);
begin
  with Sender as TImageEx do
  begin
    if Animal = 0 then Exit;
    Bitmap.Assign(Datas.CarrotImageList.Source[0].MultiResBitmap[0].Bitmap);
    Animal := 0;
  end;
  CarrotCount := CarrotCount + 1;
  SetLength(Rabbits, Length(Rabbits) + 1);
  Rabbits[Length(Rabbits) - 1] := TAnimal.Create;
  with Rabbits[Length(Rabbits) - 1] do
  begin
    index := Length(Rabbits) - 1;
    OnIn := Self.OnIn;
    OnOut := Self.OnOut;
    OnShowed := Self.OnShowed;
    OnDead := Self.OnDead;
    OnStole := Self.OnStole;
  end;
end;

procedure TGameForm.OnDead(Row, Col: Integer);
begin
  MeadowPositions[Row, Col].Animal := -1;
  with (MeadowPositions[Row, Col].Children[0] as TBitmapListAnimation) do
  begin
    AnimationBitmap.Assign(Datas.AnimalAnimationImageList.Source[1].MultiResBitmap[0].Bitmap);
    Inverse := False;
    Start;
  end;
  MeadowPositions[Row, Col].HitTest := False;
end;

procedure TGameForm.OnIn(Row, Col: Integer);
begin
  with (MeadowPositions[Row, Col].Children[0] as TBitmapListAnimation) do
  begin
    AnimationBitmap.Assign(Datas.AnimalAnimationImageList.Source[0].MultiResBitmap[0].Bitmap);
    Inverse := True;
    Start;
  end;
  MeadowPositions[Row, Col].HitTest := True;
end;

procedure TGameForm.OnOut(Row, Col: Integer);
begin
  with (MeadowPositions[Row, Col].Children[0] as TBitmapListAnimation) do
  begin
    AnimationBitmap.Assign(Datas.AnimalAnimationImageList.Source[0].MultiResBitmap[0].Bitmap);
    Inverse := False;
    Start;
  end;
  MeadowPositions[Row, Col].HitTest := False;
end;

procedure TGameForm.OnShowed(Row, Col: Integer);
begin
  //MeadowPositions[Row, Col].Bitmap.Assign(Datas.AnimalImageList.Source[0].MultiResBitmap[0].Bitmap);
end;

procedure TGameForm.OnStole;
var
  randRow, randCol: Integer;
begin
  if CarrotCount = 0 then Exit;
  repeat
    randRow := Random(Length(CarrotImages));
    randCol := Random(Length(CarrotImages[randRow]));
  until CarrotImages[randRow, randCol].Animal = 0;
  (CarrotImages[randRow, randCol].Children[0] as TBitmapListAnimation).Start;
  //CarrotImages[randRow, randCol].Bitmap.Assign(nil);
  CarrotImages[randRow, randCol].Animal := -1;
  CarrotCount := CarrotCount - 1;
end;

procedure TGameForm.FormCreate(Sender: TObject);
begin
  inherited;
  CarrotCount := 0;
  ThinkTimer.Enabled := True;
end;

procedure TGameForm.InitTimerTimer(Sender: TObject);
begin
  InitTimer.Enabled := False;
  CreateObjects;
  OrderObjects;
end;

procedure TGameForm.Kill(Sender: TObject);
begin
  if (Sender as TImageEx).Animal <> -1 then
    Rabbits[(Sender as TImageEx).Animal].Kill;
end;

procedure TGameForm.ThinkTimerTimer(Sender: TObject);
var
  i: Integer;
begin
  for i := 0 to Length(Rabbits) - 1 do
    Rabbits[i].Think(MeadowPositions, CarrotCount);
end;

end.
