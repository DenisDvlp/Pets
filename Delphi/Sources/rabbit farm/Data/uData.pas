unit uData;

interface

uses
  System.SysUtils, System.Classes, System.ImageList, FMX.ImgList;

type
  TData = class(TDataModule)
    GrassImageList: TImageList;
    GrassImageList2: TImageList;
    GrassImageList3: TImageList;
    BloodAnimationImageList: TImageList;
    AnimalImageList: TImageList;
    GrassAnimationImageList: TImageList;
    AnimalAnimationImageList: TImageList;
    CarrotImageList: TImageList;
    CarrotAnimationList: TImageList;
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Datas: TData;

implementation

{%CLASSGROUP 'FMX.Controls.TControl'}

{$R *.dfm}

end.
