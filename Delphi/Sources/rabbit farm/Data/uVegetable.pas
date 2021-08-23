unit uVegetable;

interface

const
    // TimeState in milliseconds
    tsStart = 0;
    tsStop = 0;
    tsStole = 0;
    tsNextLevel = 10000;

type
  TState = (
    asStart,
    asStop,
    asStole,
    asNextLevel);

type

  TAliveObject = class
  private
  const
    MinLevel = 0;
    MaxLevel = 6;
  var
    FTimeSetState: Cardinal;
    FState: TState;
    Level: Integer;
    TimeState: Cardinal;
    procedure setState(Value: TState);
    function getTimeInState: Cardinal;
    property TimeInState: Cardinal read getTimeInState;
    property State: TState read FState write setState;
  public
    Row, Col, Index: Integer;
    OnGrownUp: procedure (Row, Col, Level: Integer) of object;
    OnStart, OnStop, OnStole: procedure (Row, Col: Integer) of object;
    constructor Create;
    procedure Think;
    procedure Stole;
  end;

implementation

uses
  System.SysUtils, System.DateUtils;

{ TAliveObject }

constructor TAliveObject.Create;
begin
  State := asStart;
  Row := -1;
  Col := -1;
  Level := MinLevel;
end;

function TAliveObject.getTimeInState: Cardinal;
begin
  Result := MilliSecondOfTheMonth(Now) - FTimeSetState;
end;

procedure TAliveObject.setState(Value: TState);
begin
  FState := Value;
  case Value of
    asStart: TimeState := tsStart;
    asStop: TimeState := tsStop;
    asStole: TimeState := tsStole;
    asNextLevel: TimeState := tsNextLevel;
  end;
  TimeState := TimeState + Random(200) - 100;
  case Value of
    asStart: if Assigned(OnStart) then OnStart(row, col);
    asStop: if Assigned(OnStop) then OnStop(row, col);
    asStole: if Assigned(OnStole) then OnStole(row, col);
    asNextLevel: if Assigned(OnGrownUp) then OnGrownUp(Row, Col, Level);
  end;
  FTimeSetState := MilliSecondOfTheMonth(Now);
end;

procedure TAliveObject.Stole;
begin
  State := asStop;
end;

procedure TAliveObject.Think;
begin
  if FState = asStop then Exit;
  if TimeInState < Integer(TimeState) then Exit;
  case State of
    asStart: State := asNextLevel;
    asNextLevel:
      if Level < MaxLevel then
      begin
        Inc(Level);
        State := asNextLevel;
      end else
        State := asStop;
  end;
end;

end.
