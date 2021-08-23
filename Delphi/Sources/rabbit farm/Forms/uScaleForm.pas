unit uScaleForm;

interface

uses
  FMX.Forms, FMX.Layouts, System.Classes, FMX.Types, FMX.Controls;

type
  TScaleForm = class(TForm)
    MainLayout: TLayout;
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

implementation

{$R *.fmx}

procedure TScaleForm.FormCreate(Sender: TObject);
const
  w = 288;
  h = 480;
begin
  with MainLayout do
  begin
    if ClientWidth / w < ClientHeight / h then
    begin
      Position.X := (ClientWidth - Width * ClientWidth / w) / 2 ;
      Position.Y := (ClientHeight - Height * ClientWidth / w) / 2;
      Scale.X := ClientWidth / w;
      Scale.Y := ClientWidth / w;
    end else begin
      Position.X := (ClientWidth - Width * ClientHeight / h) / 2 ;
      Position.Y := (ClientHeight - Height * ClientHeight / h) / 2;
      Scale.X := ClientHeight / h;
      Scale.Y := ClientHeight / h;
    end;
  end;
end;

end.
