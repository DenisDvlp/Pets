unit uUtils;

interface

uses
   FMX.Objects, FMX.Ani, FMX.Types;

type
  TImageEx = class(TImage)
  public
    Row, Col, Animal: Integer;
  end;

  TImageExArray = array of array of TImageEx;

  TBitmapListAnimationArray = array of array of TBitmapListAnimation;

  // fuctions
  procedure AddImage(var Image: TImageEx; x, y, w, h: Single);
  procedure CreateImagesPerspective(var images: TImageExArray; bounds: TBounds; GroundH, w, h,
    rowHeight, colWidth: Single);
  procedure CreateImages(var images: TImageExArray; bounds: TBounds; w, h,
    rowHeight, colWidth: Single);

implementation

uses
  uData;

procedure AddImage(var Image: TImageEx; x, y, w, h: Single);
var
  animation: TBitmapListAnimation;
begin
  Image := TImageEx.Create(nil);
  with Image do
  begin
    Width := w;
    Height := h;
    Position.X := x;
    Position.Y := y;
    HitTest := False;
  end;
  animation := TBitmapListAnimation.Create(nil);
  with animation do
  begin
    Parent := Image;
    AnimationCount := 7;
    PropertyName := 'Bitmap';
  end;
end;

procedure CreateImagesPerspective(var images: TImageExArray; bounds: TBounds; GroundH, w, h,
  rowHeight, colWidth: Single);
var
  i, j, row, col: Integer;
  PredH, FactH, k, _x, _y, _w, _h, shiftX: Single;

  function FactHeight(depth: Single): Single;
  begin
    Result :=  GroundH * depth / sqrt(sqr(GroundH) + sqr(depth));
  end;
begin
  i := 0;
  FactH := FactHeight(i * rowHeight);
  i := i + 1;
  repeat
    PredH := FactH;
    FactH := FactHeight(i * rowHeight);
    i := i + 1;
  until (FactH >= bounds.bottom - bounds.top) or (FactH - PredH < 1);
  if i = 0 then Exit;
  row := i;
  SetLength(images, row);
  for i := 0 to row - 1  do
  begin
    FactH := FactHeight((row - 1 - i) * rowHeight);
    k := (GroundH - FactH) / GroundH;
    col := Trunc((bounds.right - bounds.left) / (k * colWidth));
    SetLength(images[i], col);
    shiftX := (col * k * colWidth - (bounds.right - bounds.left)) / 2;
    for j := 0 to col - 1  do
    begin
      _w := k * w;
      _h := k * h;
      _x := bounds.left + k * colWidth * j - shiftX;
      _y := bounds.bottom - FactH - _h;
      addImage(images[i, j], _x, _y, _w, _h);
      images[i, j].Row := i;
      images[i, j].Col := j;
      images[i, j].Animal := -1;
    end;
  end;
end;

procedure CreateImages(var images: TImageExArray; bounds: TBounds; w, h,
  rowHeight, colWidth: Single);
var
  i, j, row, col: Integer;
  FactH, x, y, shiftX: Single;
begin
  col := Trunc((bounds.Right - bounds.Left) / colWidth);
  row := Trunc((bounds.Bottom - bounds.Top) / rowHeight);
  SetLength(images, row);
  for i := 0 to row - 1  do
  begin
    if i mod 2 = 1 then
      col := col - 1;
    SetLength(images[i], col);
    shiftX := (col * colWidth - (bounds.right - bounds.left)) / 2;
    for j := 0 to col - 1  do
    begin
      x := bounds.Left + colWidth * j - shiftX;
      y := bounds.Top + (i + 1) * rowHeight - h;
      addImage(images[i, j], x, y, w, h);
      images[i, j].Row := i;
      images[i, j].Col := j;
      images[i, j].Animal := -1;
    end;
    if i mod 2 = 1 then
      col := col + 1;
  end;
end;


end.
