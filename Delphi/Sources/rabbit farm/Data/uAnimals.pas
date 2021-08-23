unit uAnimal;

interface

uses
  System.Types, uUtils, FMX.Dialogs;

const
    // TimeState in milliseconds
    tsNoInterest = 0;
    tsDead = 0;
    tsStole = 0;
    tsBeforeStole = 200;
    tsDistracted = 500;
    tsHiden = 500;
    tsShowed = 1000;
    tsIn = 200;
    tsOut = 200;
type
  TState = (
    asNoInterest,
    asDead,
    asStole,
    asBeforeStole,
    asDistracted,
    asHiden,
    asShowed,
    asIn,
    asOut);


  TAnimal = class
  private
    FTimeSetState: Cardinal;
    FState: TState;
    TimeState: Cardinal;
    procedure setState(Value: TState);
    function getTimeInState: Cardinal;
    property TimeInState: Cardinal read getTimeInState;
    property State: TState read FState write setState;
  public
    Row, Col, Index: Integer;
    OnDead, OnShowed, OnIn, OnOut: procedure (Row, Col: Integer) of object;
    OnStole :procedure of object;
    constructor Create;
    procedure Think(var MeadowPositions: TImageExArray; VegetableCount: Integer);
    procedure Kill;
  end;

implementation

uses
  System.SysUtils, System.DateUtils;

{ TAnimal }

constructor TAnimal.Create;
begin
  State := asHiden;
  Row := -1;
  Col := -1;
end;

function TAnimal.getTimeInState: Cardinal;
begin
  Result := MilliSecondOfTheMonth(Now) - FTimeSetState;
end;

procedure TAnimal.Kill;
begin
  State := asDead;
end;

procedure TAnimal.setState(Value: TState);
begin
  FState := Value;
  case Value of
    asNoInterest: TimeState := tsNoInterest;
    asDead: TimeState := tsDead;
    asStole: TimeState := tsStole;
    asBeforeStole: TimeState := tsBeforeStole;
    asDistracted: TimeState := tsDistracted;
    asHiden: TimeState := tsHiden;
    asShowed: TimeState := tsShowed;
    asIn: TimeState := tsIn;
    asOut: TimeState := tsOut;
  end;
  TimeState := TimeState + Random(200) - 100;
  case Value of
    asStole: if Assigned(OnStole) then OnStole;
    asDead: if Assigned(OnDead) then OnDead(row, col);
    asShowed: if Assigned(OnShowed) then OnShowed(row, col);
    asIn: if Assigned(OnIn) then OnIn(row, col);
    asOut: if Assigned(OnOut) then OnOut(row, col);
  end;
  FTimeSetState := MilliSecondOfTheMonth(Now);
end;

procedure TAnimal.Think(var MeadowPositions: TImageExArray; VegetableCount: Integer);
  procedure GetNextPlace;
  var
    i, j, rand, _row: Integer;
  begin
    if row = -1 then
    _row := 1 else
    _row := Random(Length(MeadowPositions) - row - 1) mod 1 + 1;
    col := -1;
    for i := 0 to Length(MeadowPositions[row + _row]) - 1 do
      if MeadowPositions[row + _row, i].Animal = -1 then
      begin
        col := i;
        break;
      end;
    if col <> -1 then
    begin
      row := row + _row;
      i := 0;
      j := 0;
      rand := Random(Length(MeadowPositions[row]) - 1);
      while i < rand do
      begin
        if MeadowPositions[row, j].Animal = -1 then
        begin
          i := i + 1;
          col := j;
        end;
        j := j + 1;
        if j = Length(MeadowPositions[row]) then j := 0;
      end;
      MeadowPositions[row, col].Animal := Index;
    end;
  end;

begin

  // 1. зайцу не интересно или он мёртв
  if (FState = asNoInterest) or (FState = asDead) then Exit;

  // 2. время на пребывание в статусе не истекло
  if TimeInState < Integer(TimeState) then Exit;

  // 3. в какой статус желает перейти заяц
  case State of
    asStole: State := asNoInterest;
    asBeforeStole:
      if VegetableCount = 0 then
        State := asNoInterest
      else
        State := asStole;
    asHiden, asDistracted:
      if VegetableCount = 0 then
        State := asNoInterest
      else
      begin
        GetNextPlace;
        if col = -1 then
          State := asDistracted
        else
          State := asIn;
      end;
    asShowed: State := asOut;
    asIn:
      if VegetableCount = 0 then
        State := asOut
      else
        State := asShowed;
    asOut:
    begin
      if VegetableCount = 0 then
        State := asNoInterest
      else
      if row = Length(MeadowPositions) - 1 then
        State := asBeforeStole
      else
        State := asHiden;
      MeadowPositions[row, col].Animal := -1;
    end;
  end;
end;

end.
