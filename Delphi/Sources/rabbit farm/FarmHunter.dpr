program FarmHunter;

uses
  System.StartUpCopy,
  FMX.Forms,
  uData in 'Data\uData.pas' {Data: TDataModule},
  uScaleForm in 'Forms\uScaleForm.pas' {ScaleForm},
  uGameForm in 'Forms\uGameForm.pas' {GameForm},
  uUtils in 'Data\uUtils.pas',
  uAnimal in 'Data\uAnimal.pas',
  uVegetable in 'Data\uVegetable.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TData, Datas);
  Application.CreateForm(TGameForm, GameForm);
  Application.Run;
end.
