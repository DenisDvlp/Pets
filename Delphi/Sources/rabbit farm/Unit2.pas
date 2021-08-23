unit uGameForm;

interface

uses
  System.SysUtils, FMX.Controls, FMX.Graphics, FMX.Dialogs, FMX.Objects,
  FMX.Layouts, FMX.StdCtrls, Unit1, System.Classes, FMX.Types, uScaleForm;

type

  PImageArray = array of array of TImage;

  TGameForm = class(TScaleForm)
    Layout1: TLayout;
    imBackground: TImage;
    procedure FormCreate(Sender: TObject);
    procedure imBackgroundClick(Sender: TObject);
  private
    GrassImages: PImageArray;
    procedure GenerateGrass;
    procedure RandomizeGrass;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  GameForm: TGameForm;

implementation

uses
  System.Types;

{$R *.fmx}

procedure TGameForm.FormCreate(Sender: TObject);
begin
  Randomize;
  GenerateGrass;
end;

procedure TGameForm.GenerateGrass;
var
  i, j,
  col, row: Integer;
  LBetween, LHeight, LK: Single;
begin
  col := 23;
  row := 12;
  SetLength(GrassImages, row);
  for i := 0 to row - 1 do
    SetLength(GrassImages[i], col);

  for i := row - 1 downto 0  do
  begin
    LK := i * LBetween * LHeight / sqrt(sqr(i * LBetween) + sqr(LHeight));
    for j := 0 to col - 1 do
    begin
      GrassImages[i, j] := TImage.Create(nil);
      with GrassImages[i, j] do
      begin
        Parent := Form2;
        WrapMode := TImageWrapMode.Stretch;
        Width := (LHeight - LK) / LHeight * 30;
        Height := (LHeight - LK) / LHeight * 85;
        Position.X := Width * j;
        Position.Y := 408 - LK - Height;
      end;
    end;
  end;
  RandomizeGrass;
end;


procedure TGameForm.imBackgroundClick(Sender: TObject);
begin
  RandomizeGrass;
end;

procedure TGameForm.RandomizeGrass;
var
  i, j, imageCount: Integer;
  size: TSizeF;
begin
  imageCount := DataModule1.ImageList1.Destination.Count - 1;
  size := TSizeF.Create(90, 255);
  for i := 0 to Length(GrassImages) - 1 do
  for j := 0 to Length(GrassImages[i]) - 1 do
    GrassImages[i, j].Bitmap.Assign(
    DataModule1.ImageList1.Bitmap(size, Random(imageCount)));
end;

end.
