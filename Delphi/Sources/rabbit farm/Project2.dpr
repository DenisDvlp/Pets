program Project2;

uses
  System.StartUpCopy,
  FMX.Forms,
  uData in 'Data\uData.pas' {Data: TDataModule},
  uScaleForm in 'Forms\uScaleForm.pas' {ScaleForm},
  uGameForm in 'Forms\uGameForm.pas' {GameForm};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TData, Datas);
  Application.CreateForm(TGameForm, GameForm);
  Application.Run;
end.
