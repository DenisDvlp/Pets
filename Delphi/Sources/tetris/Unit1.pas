unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, StdCtrls;

type
  TForm1 = class(TForm)
    Shape1: TShape;
    Timer1: TTimer;
    Shape2: TShape;
    Shape3: TShape;
    Shape4: TShape;
    Shape5: TShape;
    Shape6: TShape;
    Shape7: TShape;
    Shape8: TShape;
    Shape9: TShape;
    Shape10: TShape;
    Shape11: TShape;
    Shape12: TShape;
    Shape13: TShape;
    Shape14: TShape;
    Shape15: TShape;
    Shape16: TShape;
    Shape17: TShape;
    Shape18: TShape;
    Shape19: TShape;
    Shape20: TShape;
    Shape21: TShape;
    Shape22: TShape;
    Shape23: TShape;
    Shape24: TShape;
    Shape25: TShape;
    Shape26: TShape;
    Shape27: TShape;
    Shape28: TShape;
    Shape29: TShape;
    Shape30: TShape;
    Shape31: TShape;
    Shape32: TShape;
    Shape33: TShape;
    Shape34: TShape;
    Shape35: TShape;
    Shape36: TShape;
    Shape37: TShape;
    Shape38: TShape;
    Shape39: TShape;
    Shape40: TShape;
    Shape41: TShape;
    Shape42: TShape;
    Shape43: TShape;
    Shape44: TShape;
    Shape45: TShape;
    Shape46: TShape;
    Shape47: TShape;
    Shape48: TShape;
    Shape49: TShape;
    Shape50: TShape;
    Shape51: TShape;
    Shape52: TShape;
    Shape53: TShape;
    Shape54: TShape;
    Shape55: TShape;
    Shape56: TShape;
    Shape57: TShape;
    Shape58: TShape;
    Shape59: TShape;
    Shape60: TShape;
    Shape61: TShape;
    Shape62: TShape;
    Shape63: TShape;
    Shape64: TShape;
    Shape65: TShape;
    Shape66: TShape;
    Shape67: TShape;
    Shape68: TShape;
    Shape69: TShape;
    Shape70: TShape;
    Shape71: TShape;
    Shape72: TShape;
    Shape73: TShape;
    Shape74: TShape;
    Shape75: TShape;
    Shape76: TShape;
    Shape77: TShape;
    Shape78: TShape;
    Shape79: TShape;
    Shape80: TShape;
    Shape81: TShape;
    Shape82: TShape;
    Shape83: TShape;
    Shape84: TShape;
    Shape85: TShape;
    Shape86: TShape;
    Shape87: TShape;
    Shape88: TShape;
    Shape89: TShape;
    Shape90: TShape;
    Shape91: TShape;
    Shape92: TShape;
    Shape93: TShape;
    Shape94: TShape;
    Shape95: TShape;
    Shape96: TShape;
    Shape97: TShape;
    Shape98: TShape;
    Shape99: TShape;
    Shape100: TShape;
    Shape101: TShape;
    Shape102: TShape;
    Shape103: TShape;
    Shape104: TShape;
    Shape105: TShape;
    Shape106: TShape;
    Shape107: TShape;
    Shape108: TShape;
    Shape109: TShape;
    Shape110: TShape;
    Shape111: TShape;
    Shape112: TShape;
    Shape113: TShape;
    Shape114: TShape;
    Shape115: TShape;
    Shape116: TShape;
    Shape117: TShape;
    Shape118: TShape;
    Shape119: TShape;
    Shape120: TShape;
    Shape121: TShape;
    Shape122: TShape;
    Shape123: TShape;
    Shape124: TShape;
    Shape125: TShape;
    Shape126: TShape;
    Shape127: TShape;
    Shape128: TShape;
    Shape129: TShape;
    Shape130: TShape;
    Shape131: TShape;
    Shape132: TShape;
    Shape133: TShape;
    Shape134: TShape;
    Shape135: TShape;
    Shape136: TShape;
    Shape137: TShape;
    Shape138: TShape;
    Shape139: TShape;
    Shape140: TShape;
    Shape141: TShape;
    Shape142: TShape;
    Shape143: TShape;
    Shape144: TShape;
    Shape145: TShape;
    Shape146: TShape;
    Shape147: TShape;
    Shape148: TShape;
    Shape149: TShape;
    Shape150: TShape;
    Shape151: TShape;
    Shape152: TShape;
    Shape153: TShape;
    Shape154: TShape;
    Shape155: TShape;
    Shape156: TShape;
    Shape157: TShape;
    Shape158: TShape;
    Shape159: TShape;
    Shape160: TShape;
    Shape161: TShape;
    Shape162: TShape;
    Shape163: TShape;
    Shape164: TShape;
    Shape165: TShape;
    Shape166: TShape;
    Shape167: TShape;
    Shape168: TShape;
    Shape169: TShape;
    Shape170: TShape;
    Shape171: TShape;
    Shape172: TShape;
    Shape173: TShape;
    Shape174: TShape;
    Shape175: TShape;
    Shape176: TShape;
    Shape177: TShape;
    Shape178: TShape;
    Shape179: TShape;
    Shape180: TShape;
    Shape181: TShape;
    Shape182: TShape;
    Shape183: TShape;
    Shape184: TShape;
    Shape185: TShape;
    Shape186: TShape;
    Shape187: TShape;
    Shape188: TShape;
    Shape189: TShape;
    Shape190: TShape;
    Shape191: TShape;
    Shape192: TShape;
    Shape193: TShape;
    Shape194: TShape;
    Shape195: TShape;
    Shape196: TShape;
    Shape197: TShape;
    Shape198: TShape;
    Shape199: TShape;
    Shape200: TShape;
    Shape201: TShape;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    Label5: TLabel;
    Shape202: TShape;
    Shape203: TShape;
    Shape204: TShape;
    Shape205: TShape;
    Shape206: TShape;
    Shape207: TShape;
    Shape208: TShape;
    Shape209: TShape;
    Shape210: TShape;
    Shape211: TShape;
    Shape212: TShape;
    Shape213: TShape;
    Shape214: TShape;
    Shape215: TShape;
    Shape216: TShape;
    Shape217: TShape;
    Shape218: TShape;
    Shape219: TShape;
    Shape220: TShape;
    Shape221: TShape;
    Shape222: TShape;
    Shape223: TShape;
    Shape224: TShape;
    Shape225: TShape;
    Shape226: TShape;
    Shape227: TShape;
    Shape228: TShape;
    Shape229: TShape;
    Shape230: TShape;
    Shape231: TShape;
    Shape232: TShape;
    Shape233: TShape;
    Shape234: TShape;
    Shape235: TShape;
    Shape236: TShape;
    Shape237: TShape;
    Shape238: TShape;
    Shape239: TShape;
    Shape240: TShape;
    Shape241: TShape;
    Shape242: TShape;
    Shape243: TShape;
    Shape244: TShape;
    Shape245: TShape;
    Shape246: TShape;
    Shape247: TShape;
    Shape248: TShape;
    Shape249: TShape;
    Shape250: TShape;
    Shape251: TShape;
    Shape252: TShape;
    Shape253: TShape;
    Shape254: TShape;
    Shape255: TShape;
    Shape256: TShape;
    Shape257: TShape;
    Shape258: TShape;
    Shape259: TShape;
    Panel1: TPanel;
    Panel2: TPanel;
    Panel4: TPanel;
    Label1: TLabel;
    Label6: TLabel;
    Shape260: TShape;
    Shape261: TShape;
    Shape262: TShape;
    Shape263: TShape;
    Shape264: TShape;
    Shape265: TShape;
    Shape266: TShape;
    Shape267: TShape;
    Shape268: TShape;
    Shape269: TShape;
    Shape270: TShape;
    Shape271: TShape;
    Shape272: TShape;
    Shape273: TShape;
    Shape274: TShape;
    Shape275: TShape;
    Shape276: TShape;
    Shape277: TShape;
    Shape278: TShape;
    Shape279: TShape;
    Shape280: TShape;
    Shape281: TShape;
    Shape282: TShape;
    Shape283: TShape;
    Shape284: TShape;
    Shape285: TShape;
    Shape286: TShape;
    Shape287: TShape;
    Shape288: TShape;
    Shape289: TShape;
    Shape290: TShape;
    Shape291: TShape;
    Shape292: TShape;
    Shape293: TShape;
    Shape294: TShape;
    Shape295: TShape;
    Shape296: TShape;
    Shape297: TShape;
    Shape298: TShape;
    Shape299: TShape;
    Shape300: TShape;
    Shape301: TShape;
    Shape302: TShape;
    Shape303: TShape;
    Shape304: TShape;
    Shape305: TShape;
    Shape306: TShape;
    Shape307: TShape;
    Shape308: TShape;
    Shape309: TShape;
    Shape310: TShape;
    Shape311: TShape;
    Shape312: TShape;
    Shape313: TShape;
    Shape314: TShape;
    Shape315: TShape;
    Shape316: TShape;
    Shape317: TShape;
    Shape318: TShape;
    Shape319: TShape;
    Shape320: TShape;
    Shape321: TShape;
    Shape322: TShape;
    Shape323: TShape;
    Shape324: TShape;
    Shape325: TShape;
    Shape326: TShape;
    Shape327: TShape;
    Shape328: TShape;
    Shape329: TShape;
    Shape330: TShape;
    Shape331: TShape;
    Shape332: TShape;
    Shape333: TShape;
    Shape334: TShape;
    Shape335: TShape;
    Shape336: TShape;
    Shape337: TShape;
    Shape338: TShape;
    Shape339: TShape;
    Shape340: TShape;
    Shape341: TShape;
    Shape342: TShape;
    Shape343: TShape;
    Shape344: TShape;
    Shape345: TShape;
    Shape346: TShape;
    Shape347: TShape;
    Shape348: TShape;
    Shape349: TShape;
    Shape350: TShape;
    Shape351: TShape;
    Shape352: TShape;
    Shape353: TShape;
    Shape354: TShape;
    Shape355: TShape;
    Shape356: TShape;
    Shape357: TShape;
    Shape358: TShape;
    Shape359: TShape;
    Shape360: TShape;
    Shape361: TShape;
    Shape362: TShape;
    Shape363: TShape;
    Shape364: TShape;
    Shape365: TShape;
    Shape366: TShape;
    Shape367: TShape;
    Shape368: TShape;
    Shape369: TShape;
    Shape370: TShape;
    Shape371: TShape;
    Shape372: TShape;
    Shape373: TShape;
    Shape374: TShape;
    Shape375: TShape;
    Shape376: TShape;
    Shape377: TShape;
    Shape378: TShape;
    Shape379: TShape;
    Shape380: TShape;
    Shape381: TShape;
    Shape382: TShape;
    Shape383: TShape;
    Shape384: TShape;
    Shape385: TShape;
    Shape386: TShape;
    Shape387: TShape;
    Shape388: TShape;
    Shape389: TShape;
    Shape390: TShape;
    Shape391: TShape;
    Shape392: TShape;
    Shape393: TShape;
    Shape394: TShape;
    Shape395: TShape;
    Shape396: TShape;
    Shape397: TShape;
    Shape398: TShape;
    Shape399: TShape;
    Shape400: TShape;
    Shape401: TShape;
    Shape402: TShape;
    Shape403: TShape;
    Shape404: TShape;
    Shape405: TShape;
    Shape406: TShape;
    Shape407: TShape;
    Shape408: TShape;
    Shape409: TShape;
    Shape410: TShape;
    Shape411: TShape;
    Shape412: TShape;
    Shape413: TShape;
    Shape414: TShape;
    Shape415: TShape;
    Shape416: TShape;
    Shape417: TShape;
    Shape418: TShape;
    Shape419: TShape;
    Shape420: TShape;
    Shape421: TShape;
    Shape422: TShape;
    Shape423: TShape;
    Shape424: TShape;
    Shape425: TShape;
    Shape426: TShape;
    Shape427: TShape;
    Shape428: TShape;
    Shape429: TShape;
    Shape430: TShape;
    Shape431: TShape;
    Shape432: TShape;
    Shape433: TShape;
    Shape434: TShape;
    Shape435: TShape;
    Shape436: TShape;
    Shape437: TShape;
    Shape438: TShape;
    Shape439: TShape;
    Shape440: TShape;
    Shape441: TShape;
    Shape442: TShape;
    Shape443: TShape;
    Shape444: TShape;
    Shape445: TShape;
    Shape446: TShape;
    Shape447: TShape;
    Shape448: TShape;
    Shape449: TShape;
    Shape450: TShape;
    Shape451: TShape;
    Shape452: TShape;
    Shape453: TShape;
    Shape454: TShape;
    Shape455: TShape;
    Shape456: TShape;
    Shape457: TShape;
    Shape458: TShape;
    Shape459: TShape;
    Shape460: TShape;
    Shape461: TShape;
    Shape462: TShape;
    Shape463: TShape;
    Shape464: TShape;
    Shape465: TShape;
    Shape466: TShape;
    Shape467: TShape;
    Shape468: TShape;
    Shape469: TShape;
    Shape470: TShape;
    Shape471: TShape;
    Shape472: TShape;
    Shape473: TShape;
    Shape474: TShape;
    Shape475: TShape;
    Shape476: TShape;
    Shape477: TShape;
    Shape478: TShape;
    Shape479: TShape;
    Shape480: TShape;
    Shape481: TShape;
    Shape482: TShape;
    Shape483: TShape;
    Shape484: TShape;
    Shape485: TShape;
    Shape486: TShape;
    Shape487: TShape;
    Shape488: TShape;
    Shape489: TShape;
    Shape490: TShape;
    Shape491: TShape;
    Shape492: TShape;
    Shape493: TShape;
    Shape494: TShape;
    Shape495: TShape;
    Shape496: TShape;
    Shape497: TShape;
    Shape498: TShape;
    Shape499: TShape;
    Shape500: TShape;
    Shape501: TShape;
    Shape502: TShape;
    Shape503: TShape;
    Shape504: TShape;
    Shape505: TShape;
    Shape506: TShape;
    Shape507: TShape;
    Shape508: TShape;
    Shape509: TShape;
    Shape510: TShape;
    Shape511: TShape;
    Shape512: TShape;
    Shape513: TShape;
    Shape514: TShape;
    Shape515: TShape;
    Shape516: TShape;
    Shape517: TShape;
    Shape518: TShape;
    Shape519: TShape;
    Shape520: TShape;
    Shape521: TShape;
    Shape522: TShape;
    Shape523: TShape;
    Shape524: TShape;
    Shape525: TShape;
    Shape526: TShape;
    Shape527: TShape;
    Shape528: TShape;
    Shape529: TShape;
    Shape530: TShape;
    Shape531: TShape;
    Shape532: TShape;
    Shape533: TShape;
    Shape534: TShape;
    Shape535: TShape;
    Shape536: TShape;
    Shape537: TShape;
    Shape538: TShape;
    Shape539: TShape;
    Shape540: TShape;
    Shape541: TShape;
    Shape542: TShape;
    Shape543: TShape;
    Shape544: TShape;
    Shape545: TShape;
    Shape546: TShape;
    Shape547: TShape;
    Shape548: TShape;
    Shape549: TShape;
    Shape550: TShape;
    Shape551: TShape;
    Shape552: TShape;
    Shape553: TShape;
    Shape554: TShape;
    Shape555: TShape;
    Shape556: TShape;
    Shape557: TShape;
    Shape558: TShape;
    Shape559: TShape;
    Shape560: TShape;
    Shape561: TShape;
    Shape562: TShape;
    Shape563: TShape;
    Shape564: TShape;
    Shape565: TShape;
    Shape566: TShape;
    Shape567: TShape;
    Shape568: TShape;
    Shape569: TShape;
    Shape570: TShape;
    Shape571: TShape;
    Shape572: TShape;
    Shape573: TShape;
    Shape574: TShape;
    Shape575: TShape;
    Shape576: TShape;
    Shape577: TShape;
    Shape578: TShape;
    Shape579: TShape;
    Shape580: TShape;
    Shape581: TShape;
    Shape582: TShape;
    Shape583: TShape;
    Shape584: TShape;
    Shape585: TShape;
    Shape586: TShape;
    Shape587: TShape;
    Shape588: TShape;
    Shape589: TShape;
    Shape590: TShape;
    Shape591: TShape;
    Shape592: TShape;
    Shape593: TShape;
    Shape594: TShape;
    Shape595: TShape;
    Shape596: TShape;
    Shape597: TShape;
    Shape598: TShape;
    Shape599: TShape;
    Shape600: TShape;
    Shape601: TShape;
    Shape602: TShape;
    Shape603: TShape;
    Shape604: TShape;
    Shape605: TShape;
    Shape606: TShape;
    Shape607: TShape;
    Shape608: TShape;
    Shape609: TShape;
    Shape610: TShape;
    Shape611: TShape;
    Shape612: TShape;
    Shape613: TShape;
    Shape614: TShape;
    Shape615: TShape;
    Shape616: TShape;
    Shape617: TShape;
    Shape618: TShape;
    Shape619: TShape;
    Shape620: TShape;
    Shape621: TShape;
    Shape622: TShape;
    Shape623: TShape;
    Shape624: TShape;
    Shape625: TShape;
    Shape626: TShape;
    Shape627: TShape;
    Shape628: TShape;
    Shape629: TShape;
    Shape630: TShape;
    Shape631: TShape;
    Shape632: TShape;
    Shape633: TShape;
    Shape634: TShape;
    Shape635: TShape;
    Shape636: TShape;
    Shape637: TShape;
    Shape638: TShape;
    Shape639: TShape;
    Shape640: TShape;
    Shape641: TShape;
    Shape642: TShape;
    Shape643: TShape;
    Shape644: TShape;
    Shape645: TShape;
    Shape646: TShape;
    Shape647: TShape;
    Shape648: TShape;
    Shape649: TShape;
    Shape650: TShape;
    Shape651: TShape;
    Shape652: TShape;
    Shape653: TShape;
    Shape654: TShape;
    Shape655: TShape;
    Shape656: TShape;
    Shape657: TShape;
    Shape658: TShape;
    Shape659: TShape;
    Shape660: TShape;
    Shape661: TShape;
    Shape662: TShape;
    Shape663: TShape;
    Shape664: TShape;
    Shape665: TShape;
    Shape666: TShape;
    Shape667: TShape;
    Shape668: TShape;
    Shape669: TShape;
    Shape670: TShape;
    Shape671: TShape;
    Shape672: TShape;
    Shape673: TShape;
    Shape674: TShape;
    Shape675: TShape;
    Shape676: TShape;
    Shape677: TShape;
    Shape678: TShape;
    Shape679: TShape;
    Shape680: TShape;
    Shape681: TShape;
    Shape682: TShape;
    Shape683: TShape;
    Shape684: TShape;
    Shape685: TShape;
    Shape686: TShape;
    Shape687: TShape;
    Shape688: TShape;
    Shape689: TShape;
    Shape690: TShape;
    Shape691: TShape;
    Shape692: TShape;
    Shape693: TShape;
    Shape694: TShape;
    Shape695: TShape;
    Shape696: TShape;
    Shape697: TShape;
    Shape698: TShape;
    Shape699: TShape;
    Shape700: TShape;
    Shape701: TShape;
    Shape702: TShape;
    Shape703: TShape;
    Shape704: TShape;
    Shape705: TShape;
    Shape706: TShape;
    Shape707: TShape;
    Shape708: TShape;
    Shape709: TShape;
    Shape710: TShape;
    Shape711: TShape;
    Shape712: TShape;
    Shape713: TShape;
    Shape714: TShape;
    Shape715: TShape;
    Shape716: TShape;
    Shape717: TShape;
    Shape718: TShape;
    Shape719: TShape;
    Shape720: TShape;
    Shape721: TShape;
    Shape722: TShape;
    Shape723: TShape;
    Shape724: TShape;
    Shape725: TShape;
    Shape726: TShape;
    Shape727: TShape;
    Shape728: TShape;
    Label7: TLabel;
    Panel3: TPanel;
    Panel5: TPanel;
    Timer2: TTimer;
    Timer3: TTimer;
    procedure Timer1Timer(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormKeyDown(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure FormKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure Panel2Click(Sender: TObject);
    procedure Timer2Timer(Sender: TObject);
    procedure Timer3Timer(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;
////////////////////////////����������////////////////////////////////////////
var
  Form1: TForm1;
  x,y, xprev,yprev,Speed,shnum,level,destroycell,destroyrow: integer;
  shnumhelp: array [1..4] of integer;
  fullrow: array [1..20] of boolean;
  colory: array [1..7] of Tcolor = (clgreen,clnavy,clpurple,clblue,clred,clfuchsia,clmaroon);
////////////////////////////�������///////////////////////////////////////////
procedure cell(x,y: integer; colr: Tcolor);
function iscolcell(x,y: integer; colr: Tcolor): boolean;
procedure cellhelp(num,x,y: integer; colr: Tcolor);
function Randomshape(int: integer): integer;
procedure changetimer(i: integer);
procedure findfullrows();
procedure shadow(i,y: integer);
procedure shadowdelete();
implementation

{$R *.dfm}

procedure sh1(x,y: integer; colr: Tcolor);
begin
   cell(x,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y,colr);
   cell(x-2,y,colr);
end;
procedure sh2(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y+2,colr);
end;
procedure sh3(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-2,y,colr);
   cell(x-2,y+1,colr);
end;
procedure sh4(x,y: integer; colr: Tcolor);
begin
   cell(x-1,y,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y+2,colr);
   cell(x,y+2,colr);
end;
procedure sh5(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x-2,y+1,colr);
end;
procedure sh6(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x,y+1,colr);
   cell(x,y+2,colr);
end;
procedure sh7(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-2,y,colr);
   cell(x-3,y,colr);
end;
procedure sh8(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x,y+2,colr);
   cell(x,y+3,colr);
end;
procedure sh9(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-1,y+1,colr);
   cell(x-2,y+1,colr);
end;
procedure sh10(x,y: integer; colr: Tcolor);
begin
   cell(x-1,y,colr);
   cell(x-1,y+1,colr);
   cell(x,y+1,colr);
   cell(x,y+2,colr);
end;
procedure sh11(x,y: integer; colr: Tcolor);
begin
   cell(x-2,y,colr);
   cell(x-2,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x,y+1,colr);
end;
procedure sh12(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x,y+2,colr);
   cell(x-1,y+2,colr);
end;
procedure sh13(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-2,y,colr);
   cell(x,y+1,colr);
end;
procedure sh14(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y+2,colr);
end;
procedure sh15(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x,y+2,colr);
   cell(x-1,y+1,colr);
end;
procedure sh16(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x-1,y,colr);
   cell(x-2,y,colr);
   cell(x-1,y+1,colr);
end;
procedure sh17(x,y: integer; colr: Tcolor);
begin
   cell(x-1,y,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y+2,colr);
   cell(x,y+1,colr);
end;
procedure sh18(x,y: integer; colr: Tcolor);
begin
   cell(x-1,y,colr);
   cell(x,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x-2,y+1,colr);
end;
procedure sh19(x,y: integer; colr: Tcolor);
begin
   cell(x,y,colr);
   cell(x,y+1,colr);
   cell(x-1,y+1,colr);
   cell(x-1,y,colr);
end;

procedure helpsh1(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-2,y,colr);
end;
procedure helpsh2(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y+2,colr);
end;
procedure helpsh3(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-2,y,colr);
   cellhelp(num,x-2,y+1,colr);
end;
procedure helpsh4(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y+2,colr);
   cellhelp(num,x,y+2,colr);
end;
procedure helpsh5(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-2,y+1,colr);
end;
procedure helpsh6(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x,y+2,colr);
end;
procedure helpsh7(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-2,y,colr);
   cellhelp(num,x-3,y,colr);
end;
procedure helpsh8(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x,y+2,colr);
   cellhelp(num,x,y+3,colr);
end;
procedure helpsh9(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-2,y+1,colr);
end;
procedure helpsh10(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x,y+2,colr);
end;
procedure helpsh11(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x-2,y,colr);
   cellhelp(num,x-2,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x,y+1,colr);
end;
procedure helpsh12(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x,y+2,colr);
   cellhelp(num,x-1,y+2,colr);
end;
procedure helpsh13(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-2,y,colr);
   cellhelp(num,x,y+1,colr);
end;
procedure helpsh14(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y+2,colr);
end;
procedure helpsh15(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x,y+2,colr);
   cellhelp(num,x-1,y+1,colr);
end;
procedure helpsh16(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-2,y,colr);
   cellhelp(num,x-1,y+1,colr);
end;
procedure helpsh17(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y+2,colr);
   cellhelp(num,x,y+1,colr);
end;
procedure helpsh18(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x-1,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-2,y+1,colr);
end;
procedure helpsh19(num,x,y: integer; colr: Tcolor);
begin
   cellhelp(num,x,y,colr);
   cellhelp(num,x,y+1,colr);
   cellhelp(num,x-1,y+1,colr);
   cellhelp(num,x-1,y,colr);
end;

function iscolsh1(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))then result:=true else result:=false;
end;
function iscolsh2(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y+2,colr)or iscolcell(x-1,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh3(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))and
   (iscolcell(x-2,y+1,colr)or iscolcell(x-2,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh4(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y+2,colr)or iscolcell(x-1,y+2,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh5(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-2,y+1,colr)or iscolcell(x-2,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh6(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh7(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))and
   (iscolcell(x-3,y,colr)or iscolcell(x-3,y,colr2))then result:=true else result:=false;
end;
function iscolsh8(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))and
   (iscolcell(x,y+3,colr)or iscolcell(x,y+3,colr2))then result:=true else result:=false;
end;
function iscolsh9(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-2,y+1,colr)or iscolcell(x-2,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh10(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh11(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))and
   (iscolcell(x-2,y+1,colr)or iscolcell(x-2,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh12(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))and
   (iscolcell(x-1,y+2,colr)or iscolcell(x-1,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh13(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh14(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y+2,colr)or iscolcell(x-1,y+2,colr2))then result:=true else result:=false;
end;
function iscolsh15(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x,y+2,colr)or iscolcell(x,y+2,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh16(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-2,y,colr)or iscolcell(x-2,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh17(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y+2,colr)or iscolcell(x-1,y+2,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh18(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-2,y+1,colr)or iscolcell(x-2,y+1,colr2))then result:=true else result:=false;
end;
function iscolsh19(x,y: integer; colr,colr2: Tcolor):boolean;
begin if
   (iscolcell(x,y,colr)or iscolcell(x,y,colr2))and
   (iscolcell(x,y+1,colr)or iscolcell(x,y+1,colr2))and
   (iscolcell(x-1,y+1,colr)or iscolcell(x-1,y+1,colr2))and
   (iscolcell(x-1,y,colr)or iscolcell(x-1,y,colr2))then result:=true else result:=false;
end;

function iscolcell(x,y: integer; colr: Tcolor): boolean;
var bl: boolean;
begin
  bl:=true;
  with form1 do
  begin
    if (y<1)or(y>10) then bl:=false else
    case x of
    1: case y of
      1: if Shape1.Brush.Color<>colr then bl:=false;
      2: if Shape2.Brush.Color<>colr then bl:=false;
      3: if Shape3.Brush.Color<>colr then bl:=false;
      4: if Shape4.Brush.Color<>colr then bl:=false;
      5: if Shape5.Brush.Color<>colr then bl:=false;
      6: if Shape6.Brush.Color<>colr then bl:=false;
      7: if Shape7.Brush.Color<>colr then bl:=false;
      8: if Shape8.Brush.Color<>colr then bl:=false;
      9: if Shape9.Brush.Color<>colr then bl:=false;
      10: if Shape10.Brush.Color<>colr then bl:=false; end;
    2: case y of
      1: if Shape11.Brush.Color<>colr then bl:=false;
      2: if Shape12.Brush.Color<>colr then bl:=false;
      3: if Shape13.Brush.Color<>colr then bl:=false;
      4: if Shape14.Brush.Color<>colr then bl:=false;
      5: if Shape15.Brush.Color<>colr then bl:=false;
      6: if Shape16.Brush.Color<>colr then bl:=false;
      7: if Shape17.Brush.Color<>colr then bl:=false;
      8: if Shape18.Brush.Color<>colr then bl:=false;
      9: if Shape19.Brush.Color<>colr then bl:=false;
      10: if Shape20.Brush.Color<>colr then bl:=false; end;
    3: case y of
      1: if Shape21.Brush.Color<>colr then bl:=false;
      2: if Shape22.Brush.Color<>colr then bl:=false;
      3: if Shape23.Brush.Color<>colr then bl:=false;
      4: if Shape24.Brush.Color<>colr then bl:=false;
      5: if Shape25.Brush.Color<>colr then bl:=false;
      6: if Shape26.Brush.Color<>colr then bl:=false;
      7: if Shape27.Brush.Color<>colr then bl:=false;
      8: if Shape28.Brush.Color<>colr then bl:=false;
      9: if Shape29.Brush.Color<>colr then bl:=false;
      10: if Shape30.Brush.Color<>colr then bl:=false; end;
    4: case y of
      1: if Shape31.Brush.Color<>colr then bl:=false;
      2: if Shape32.Brush.Color<>colr then bl:=false;
      3: if Shape33.Brush.Color<>colr then bl:=false;
      4: if Shape34.Brush.Color<>colr then bl:=false;
      5: if Shape35.Brush.Color<>colr then bl:=false;
      6: if Shape36.Brush.Color<>colr then bl:=false;
      7: if Shape37.Brush.Color<>colr then bl:=false;
      8: if Shape38.Brush.Color<>colr then bl:=false;
      9: if Shape39.Brush.Color<>colr then bl:=false;
      10: if Shape40.Brush.Color<>colr then bl:=false; end;
    5: case y of
      1: if Shape41.Brush.Color<>colr then bl:=false;
      2: if Shape42.Brush.Color<>colr then bl:=false;
      3: if Shape43.Brush.Color<>colr then bl:=false;
      4: if Shape44.Brush.Color<>colr then bl:=false;
      5: if Shape45.Brush.Color<>colr then bl:=false;
      6: if Shape46.Brush.Color<>colr then bl:=false;
      7: if Shape47.Brush.Color<>colr then bl:=false;
      8: if Shape48.Brush.Color<>colr then bl:=false;
      9: if Shape49.Brush.Color<>colr then bl:=false;
      10: if Shape50.Brush.Color<>colr then bl:=false; end;
    6: case y of
      1: if Shape51.Brush.Color<>colr then bl:=false;
      2: if Shape52.Brush.Color<>colr then bl:=false;
      3: if Shape53.Brush.Color<>colr then bl:=false;
      4: if Shape54.Brush.Color<>colr then bl:=false;
      5: if Shape55.Brush.Color<>colr then bl:=false;
      6: if Shape56.Brush.Color<>colr then bl:=false;
      7: if Shape57.Brush.Color<>colr then bl:=false;
      8: if Shape58.Brush.Color<>colr then bl:=false;
      9: if Shape59.Brush.Color<>colr then bl:=false;
      10: if Shape60.Brush.Color<>colr then bl:=false; end;
    7: case y of
      1: if Shape61.Brush.Color<>colr then bl:=false;
      2: if Shape62.Brush.Color<>colr then bl:=false;
      3: if Shape63.Brush.Color<>colr then bl:=false;
      4: if Shape64.Brush.Color<>colr then bl:=false;
      5: if Shape65.Brush.Color<>colr then bl:=false;
      6: if Shape66.Brush.Color<>colr then bl:=false;
      7: if Shape67.Brush.Color<>colr then bl:=false;
      8: if Shape68.Brush.Color<>colr then bl:=false;
      9: if Shape69.Brush.Color<>colr then bl:=false;
      10: if Shape70.Brush.Color<>colr then bl:=false; end;
    8: case y of
      1: if Shape71.Brush.Color<>colr then bl:=false;
      2: if Shape72.Brush.Color<>colr then bl:=false;
      3: if Shape73.Brush.Color<>colr then bl:=false;
      4: if Shape74.Brush.Color<>colr then bl:=false;
      5: if Shape75.Brush.Color<>colr then bl:=false;
      6: if Shape76.Brush.Color<>colr then bl:=false;
      7: if Shape77.Brush.Color<>colr then bl:=false;
      8: if Shape78.Brush.Color<>colr then bl:=false;
      9: if Shape79.Brush.Color<>colr then bl:=false;
      10: if Shape80.Brush.Color<>colr then bl:=false; end;
    9: case y of
      1: if Shape81.Brush.Color<>colr then bl:=false;
      2: if Shape82.Brush.Color<>colr then bl:=false;
      3: if Shape83.Brush.Color<>colr then bl:=false;
      4: if Shape84.Brush.Color<>colr then bl:=false;
      5: if Shape85.Brush.Color<>colr then bl:=false;
      6: if Shape86.Brush.Color<>colr then bl:=false;
      7: if Shape87.Brush.Color<>colr then bl:=false;
      8: if Shape88.Brush.Color<>colr then bl:=false;
      9: if Shape89.Brush.Color<>colr then bl:=false;
      10: if Shape90.Brush.Color<>colr then bl:=false; end;
    10: case y of
      1: if Shape91.Brush.Color<>colr then bl:=false;
      2: if Shape92.Brush.Color<>colr then bl:=false;
      3: if Shape93.Brush.Color<>colr then bl:=false;
      4: if Shape94.Brush.Color<>colr then bl:=false;
      5: if Shape95.Brush.Color<>colr then bl:=false;
      6: if Shape96.Brush.Color<>colr then bl:=false;
      7: if Shape97.Brush.Color<>colr then bl:=false;
      8: if Shape98.Brush.Color<>colr then bl:=false;
      9: if Shape99.Brush.Color<>colr then bl:=false;
      10: if Shape100.Brush.Color<>colr then bl:=false; end;
    11: case y of
      1: if Shape101.Brush.Color<>colr then bl:=false;
      2: if Shape102.Brush.Color<>colr then bl:=false;
      3: if Shape103.Brush.Color<>colr then bl:=false;
      4: if Shape104.Brush.Color<>colr then bl:=false;
      5: if Shape105.Brush.Color<>colr then bl:=false;
      6: if Shape106.Brush.Color<>colr then bl:=false;
      7: if Shape107.Brush.Color<>colr then bl:=false;
      8: if Shape108.Brush.Color<>colr then bl:=false;
      9: if Shape109.Brush.Color<>colr then bl:=false;
      10: if Shape110.Brush.Color<>colr then bl:=false; end;
    12: case y of
      1: if Shape111.Brush.Color<>colr then bl:=false;
      2: if Shape112.Brush.Color<>colr then bl:=false;
      3: if Shape113.Brush.Color<>colr then bl:=false;
      4: if Shape114.Brush.Color<>colr then bl:=false;
      5: if Shape115.Brush.Color<>colr then bl:=false;
      6: if Shape116.Brush.Color<>colr then bl:=false;
      7: if Shape117.Brush.Color<>colr then bl:=false;
      8: if Shape118.Brush.Color<>colr then bl:=false;
      9: if Shape119.Brush.Color<>colr then bl:=false;
      10: if Shape120.Brush.Color<>colr then bl:=false; end;
    13: case y of
      1: if Shape121.Brush.Color<>colr then bl:=false;
      2: if Shape122.Brush.Color<>colr then bl:=false;
      3: if Shape123.Brush.Color<>colr then bl:=false;
      4: if Shape124.Brush.Color<>colr then bl:=false;
      5: if Shape125.Brush.Color<>colr then bl:=false;
      6: if Shape126.Brush.Color<>colr then bl:=false;
      7: if Shape127.Brush.Color<>colr then bl:=false;
      8: if Shape128.Brush.Color<>colr then bl:=false;
      9: if Shape129.Brush.Color<>colr then bl:=false;
      10: if Shape130.Brush.Color<>colr then bl:=false; end;
    14: case y of
      1: if Shape131.Brush.Color<>colr then bl:=false;
      2: if Shape132.Brush.Color<>colr then bl:=false;
      3: if Shape133.Brush.Color<>colr then bl:=false;
      4: if Shape134.Brush.Color<>colr then bl:=false;
      5: if Shape135.Brush.Color<>colr then bl:=false;
      6: if Shape136.Brush.Color<>colr then bl:=false;
      7: if Shape137.Brush.Color<>colr then bl:=false;
      8: if Shape138.Brush.Color<>colr then bl:=false;
      9: if Shape139.Brush.Color<>colr then bl:=false;
      10: if Shape140.Brush.Color<>colr then bl:=false; end;
    15: case y of
      1: if Shape141.Brush.Color<>colr then bl:=false;
      2: if Shape142.Brush.Color<>colr then bl:=false;
      3: if Shape143.Brush.Color<>colr then bl:=false;
      4: if Shape144.Brush.Color<>colr then bl:=false;
      5: if Shape145.Brush.Color<>colr then bl:=false;
      6: if Shape146.Brush.Color<>colr then bl:=false;
      7: if Shape147.Brush.Color<>colr then bl:=false;
      8: if Shape148.Brush.Color<>colr then bl:=false;
      9: if Shape149.Brush.Color<>colr then bl:=false;
      10: if Shape150.Brush.Color<>colr then bl:=false; end;
    16: case y of
      1: if Shape151.Brush.Color<>colr then bl:=false;
      2: if Shape152.Brush.Color<>colr then bl:=false;
      3: if Shape153.Brush.Color<>colr then bl:=false;
      4: if Shape154.Brush.Color<>colr then bl:=false;
      5: if Shape155.Brush.Color<>colr then bl:=false;
      6: if Shape156.Brush.Color<>colr then bl:=false;
      7: if Shape157.Brush.Color<>colr then bl:=false;
      8: if Shape158.Brush.Color<>colr then bl:=false;
      9: if Shape159.Brush.Color<>colr then bl:=false;
      10: if Shape160.Brush.Color<>colr then bl:=false; end;
    17: case y of
      1: if Shape161.Brush.Color<>colr then bl:=false;
      2: if Shape162.Brush.Color<>colr then bl:=false;
      3: if Shape163.Brush.Color<>colr then bl:=false;
      4: if Shape164.Brush.Color<>colr then bl:=false;
      5: if Shape165.Brush.Color<>colr then bl:=false;
      6: if Shape166.Brush.Color<>colr then bl:=false;
      7: if Shape167.Brush.Color<>colr then bl:=false;
      8: if Shape168.Brush.Color<>colr then bl:=false;
      9: if Shape169.Brush.Color<>colr then bl:=false;
      10: if Shape170.Brush.Color<>colr then bl:=false; end;
    18: case y of
      1: if Shape171.Brush.Color<>colr then bl:=false;
      2: if Shape172.Brush.Color<>colr then bl:=false;
      3: if Shape173.Brush.Color<>colr then bl:=false;
      4: if Shape174.Brush.Color<>colr then bl:=false;
      5: if Shape175.Brush.Color<>colr then bl:=false;
      6: if Shape176.Brush.Color<>colr then bl:=false;
      7: if Shape177.Brush.Color<>colr then bl:=false;
      8: if Shape178.Brush.Color<>colr then bl:=false;
      9: if Shape179.Brush.Color<>colr then bl:=false;
      10: if Shape180.Brush.Color<>colr then bl:=false; end;
    19: case y of
      1: if Shape181.Brush.Color<>colr then bl:=false;
      2: if Shape182.Brush.Color<>colr then bl:=false;
      3: if Shape183.Brush.Color<>colr then bl:=false;
      4: if Shape184.Brush.Color<>colr then bl:=false;
      5: if Shape185.Brush.Color<>colr then bl:=false;
      6: if Shape186.Brush.Color<>colr then bl:=false;
      7: if Shape187.Brush.Color<>colr then bl:=false;
      8: if Shape188.Brush.Color<>colr then bl:=false;
      9: if Shape189.Brush.Color<>colr then bl:=false;
      10: if Shape190.Brush.Color<>colr then bl:=false; end;
    20: case y of
      1: if Shape191.Brush.Color<>colr then bl:=false;
      2: if Shape192.Brush.Color<>colr then bl:=false;
      3: if Shape193.Brush.Color<>colr then bl:=false;
      4: if Shape194.Brush.Color<>colr then bl:=false;
      5: if Shape195.Brush.Color<>colr then bl:=false;
      6: if Shape196.Brush.Color<>colr then bl:=false;
      7: if Shape197.Brush.Color<>colr then bl:=false;
      8: if Shape198.Brush.Color<>colr then bl:=false;
      9: if Shape199.Brush.Color<>colr then bl:=false;
      10: if Shape200.Brush.Color<>colr then bl:=false; end; end;
  end;
  result:=bl;
end;

procedure cell(x,y: integer; colr: Tcolor);
begin
  with form1 do
  begin
    case x of
    1: case y of
      1: Shape1.Brush.Color:=colr;
      2: Shape2.Brush.Color:=colr;
      3: Shape3.Brush.Color:=colr;
      4: Shape4.Brush.Color:=colr;
      5: Shape5.Brush.Color:=colr;
      6: Shape6.Brush.Color:=colr;
      7: Shape7.Brush.Color:=colr;
      8: Shape8.Brush.Color:=colr;
      9: Shape9.Brush.Color:=colr;
      10: Shape10.Brush.Color:=colr; end;
    2: case y of
      1: Shape11.Brush.Color:=colr;
      2: Shape12.Brush.Color:=colr;
      3: Shape13.Brush.Color:=colr;
      4: Shape14.Brush.Color:=colr;
      5: Shape15.Brush.Color:=colr;
      6: Shape16.Brush.Color:=colr;
      7: Shape17.Brush.Color:=colr;
      8: Shape18.Brush.Color:=colr;
      9: Shape19.Brush.Color:=colr;
      10: Shape20.Brush.Color:=colr; end;
    3: case y of
      1: Shape21.Brush.Color:=colr;
      2: Shape22.Brush.Color:=colr;
      3: Shape23.Brush.Color:=colr;
      4: Shape24.Brush.Color:=colr;
      5: Shape25.Brush.Color:=colr;
      6: Shape26.Brush.Color:=colr;
      7: Shape27.Brush.Color:=colr;
      8: Shape28.Brush.Color:=colr;
      9: Shape29.Brush.Color:=colr;
      10: Shape30.Brush.Color:=colr; end;
    4: case y of
      1: Shape31.Brush.Color:=colr;
      2: Shape32.Brush.Color:=colr;
      3: Shape33.Brush.Color:=colr;
      4: Shape34.Brush.Color:=colr;
      5: Shape35.Brush.Color:=colr;
      6: Shape36.Brush.Color:=colr;
      7: Shape37.Brush.Color:=colr;
      8: Shape38.Brush.Color:=colr;
      9: Shape39.Brush.Color:=colr;
      10: Shape40.Brush.Color:=colr; end;
    5: case y of
      1: Shape41.Brush.Color:=colr;
      2: Shape42.Brush.Color:=colr;
      3: Shape43.Brush.Color:=colr;
      4: Shape44.Brush.Color:=colr;
      5: Shape45.Brush.Color:=colr;
      6: Shape46.Brush.Color:=colr;
      7: Shape47.Brush.Color:=colr;
      8: Shape48.Brush.Color:=colr;
      9: Shape49.Brush.Color:=colr;
      10: Shape50.Brush.Color:=colr; end;
    6: case y of
      1: Shape51.Brush.Color:=colr;
      2: Shape52.Brush.Color:=colr;
      3: Shape53.Brush.Color:=colr;
      4: Shape54.Brush.Color:=colr;
      5: Shape55.Brush.Color:=colr;
      6: Shape56.Brush.Color:=colr;
      7: Shape57.Brush.Color:=colr;
      8: Shape58.Brush.Color:=colr;
      9: Shape59.Brush.Color:=colr;
      10: Shape60.Brush.Color:=colr; end;
    7: case y of
      1: Shape61.Brush.Color:=colr;
      2: Shape62.Brush.Color:=colr;
      3: Shape63.Brush.Color:=colr;
      4: Shape64.Brush.Color:=colr;
      5: Shape65.Brush.Color:=colr;
      6: Shape66.Brush.Color:=colr;
      7: Shape67.Brush.Color:=colr;
      8: Shape68.Brush.Color:=colr;
      9: Shape69.Brush.Color:=colr;
      10: Shape70.Brush.Color:=colr; end;
    8: case y of
      1: Shape71.Brush.Color:=colr;
      2: Shape72.Brush.Color:=colr;
      3: Shape73.Brush.Color:=colr;
      4: Shape74.Brush.Color:=colr;
      5: Shape75.Brush.Color:=colr;
      6: Shape76.Brush.Color:=colr;
      7: Shape77.Brush.Color:=colr;
      8: Shape78.Brush.Color:=colr;
      9: Shape79.Brush.Color:=colr;
      10: Shape80.Brush.Color:=colr; end;
    9: case y of
      1: Shape81.Brush.Color:=colr;
      2: Shape82.Brush.Color:=colr;
      3: Shape83.Brush.Color:=colr;
      4: Shape84.Brush.Color:=colr;
      5: Shape85.Brush.Color:=colr;
      6: Shape86.Brush.Color:=colr;
      7: Shape87.Brush.Color:=colr;
      8: Shape88.Brush.Color:=colr;
      9: Shape89.Brush.Color:=colr;
      10: Shape90.Brush.Color:=colr; end;
    10: case y of
      1: Shape91.Brush.Color:=colr;
      2: Shape92.Brush.Color:=colr;
      3: Shape93.Brush.Color:=colr;
      4: Shape94.Brush.Color:=colr;
      5: Shape95.Brush.Color:=colr;
      6: Shape96.Brush.Color:=colr;
      7: Shape97.Brush.Color:=colr;
      8: Shape98.Brush.Color:=colr;
      9: Shape99.Brush.Color:=colr;
      10: Shape100.Brush.Color:=colr; end;
    11: case y of
      1: Shape101.Brush.Color:=colr;
      2: Shape102.Brush.Color:=colr;
      3: Shape103.Brush.Color:=colr;
      4: Shape104.Brush.Color:=colr;
      5: Shape105.Brush.Color:=colr;
      6: Shape106.Brush.Color:=colr;
      7: Shape107.Brush.Color:=colr;
      8: Shape108.Brush.Color:=colr;
      9: Shape109.Brush.Color:=colr;
      10: Shape110.Brush.Color:=colr; end;
    12: case y of
      1: Shape111.Brush.Color:=colr;
      2: Shape112.Brush.Color:=colr;
      3: Shape113.Brush.Color:=colr;
      4: Shape114.Brush.Color:=colr;
      5: Shape115.Brush.Color:=colr;
      6: Shape116.Brush.Color:=colr;
      7: Shape117.Brush.Color:=colr;
      8: Shape118.Brush.Color:=colr;
      9: Shape119.Brush.Color:=colr;
      10: Shape120.Brush.Color:=colr; end;
    13: case y of
      1: Shape121.Brush.Color:=colr;
      2: Shape122.Brush.Color:=colr;
      3: Shape123.Brush.Color:=colr;
      4: Shape124.Brush.Color:=colr;
      5: Shape125.Brush.Color:=colr;
      6: Shape126.Brush.Color:=colr;
      7: Shape127.Brush.Color:=colr;
      8: Shape128.Brush.Color:=colr;
      9: Shape129.Brush.Color:=colr;
      10: Shape130.Brush.Color:=colr; end;
    14: case y of
      1: Shape131.Brush.Color:=colr;
      2: Shape132.Brush.Color:=colr;
      3: Shape133.Brush.Color:=colr;
      4: Shape134.Brush.Color:=colr;
      5: Shape135.Brush.Color:=colr;
      6: Shape136.Brush.Color:=colr;
      7: Shape137.Brush.Color:=colr;
      8: Shape138.Brush.Color:=colr;
      9: Shape139.Brush.Color:=colr;
      10: Shape140.Brush.Color:=colr; end;
    15: case y of
      1: Shape141.Brush.Color:=colr;
      2: Shape142.Brush.Color:=colr;
      3: Shape143.Brush.Color:=colr;
      4: Shape144.Brush.Color:=colr;
      5: Shape145.Brush.Color:=colr;
      6: Shape146.Brush.Color:=colr;
      7: Shape147.Brush.Color:=colr;
      8: Shape148.Brush.Color:=colr;
      9: Shape149.Brush.Color:=colr;
      10: Shape150.Brush.Color:=colr; end;
    16: case y of
      1: Shape151.Brush.Color:=colr;
      2: Shape152.Brush.Color:=colr;
      3: Shape153.Brush.Color:=colr;
      4: Shape154.Brush.Color:=colr;
      5: Shape155.Brush.Color:=colr;
      6: Shape156.Brush.Color:=colr;
      7: Shape157.Brush.Color:=colr;
      8: Shape158.Brush.Color:=colr;
      9: Shape159.Brush.Color:=colr;
      10: Shape160.Brush.Color:=colr; end;
    17: case y of
      1: Shape161.Brush.Color:=colr;
      2: Shape162.Brush.Color:=colr;
      3: Shape163.Brush.Color:=colr;
      4: Shape164.Brush.Color:=colr;
      5: Shape165.Brush.Color:=colr;
      6: Shape166.Brush.Color:=colr;
      7: Shape167.Brush.Color:=colr;
      8: Shape168.Brush.Color:=colr;
      9: Shape169.Brush.Color:=colr;
      10: Shape170.Brush.Color:=colr; end;
    18: case y of
      1: Shape171.Brush.Color:=colr;
      2: Shape172.Brush.Color:=colr;
      3: Shape173.Brush.Color:=colr;
      4: Shape174.Brush.Color:=colr;
      5: Shape175.Brush.Color:=colr;
      6: Shape176.Brush.Color:=colr;
      7: Shape177.Brush.Color:=colr;
      8: Shape178.Brush.Color:=colr;
      9: Shape179.Brush.Color:=colr;
      10: Shape180.Brush.Color:=colr; end;
    19: case y of
      1: Shape181.Brush.Color:=colr;
      2: Shape182.Brush.Color:=colr;
      3: Shape183.Brush.Color:=colr;
      4: Shape184.Brush.Color:=colr;
      5: Shape185.Brush.Color:=colr;
      6: Shape186.Brush.Color:=colr;
      7: Shape187.Brush.Color:=colr;
      8: Shape188.Brush.Color:=colr;
      9: Shape189.Brush.Color:=colr;
      10: Shape190.Brush.Color:=colr; end;
    20: case y of
      1: Shape191.Brush.Color:=colr;
      2: Shape192.Brush.Color:=colr;
      3: Shape193.Brush.Color:=colr;
      4: Shape194.Brush.Color:=colr;
      5: Shape195.Brush.Color:=colr;
      6: Shape196.Brush.Color:=colr;
      7: Shape197.Brush.Color:=colr;
      8: Shape198.Brush.Color:=colr;
      9: Shape199.Brush.Color:=colr;
      10: Shape200.Brush.Color:=colr; end; end;
  end;
end;

function getcolorcell(x,y: integer): Tcolor;
var colr: Tcolor;
begin
  colr:=clwhite;
  with form1 do
  begin
    case x of
    1: case y of
      1: colr:=Shape1.Brush.Color;
      2: colr:=Shape2.Brush.Color;
      3: colr:=Shape3.Brush.Color;
      4: colr:=Shape4.Brush.Color;
      5: colr:=Shape5.Brush.Color;
      6: colr:=Shape6.Brush.Color;
      7: colr:=Shape7.Brush.Color;
      8: colr:=Shape8.Brush.Color;
      9: colr:=Shape9.Brush.Color;
      10: colr:=Shape10.Brush.Color; end;
    2: case y of
      1: colr:=Shape11.Brush.Color;
      2: colr:=Shape12.Brush.Color;
      3: colr:=Shape13.Brush.Color;
      4: colr:=Shape14.Brush.Color;
      5: colr:=Shape15.Brush.Color;
      6: colr:=Shape16.Brush.Color;
      7: colr:=Shape17.Brush.Color;
      8: colr:=Shape18.Brush.Color;
      9: colr:=Shape19.Brush.Color;
      10: colr:=Shape20.Brush.Color; end;
    3: case y of
      1: colr:=Shape21.Brush.Color;
      2: colr:=Shape22.Brush.Color;
      3: colr:=Shape23.Brush.Color;
      4: colr:=Shape24.Brush.Color;
      5: colr:=Shape25.Brush.Color;
      6: colr:=Shape26.Brush.Color;
      7: colr:=Shape27.Brush.Color;
      8: colr:=Shape28.Brush.Color;
      9: colr:=Shape29.Brush.Color;
      10: colr:=Shape30.Brush.Color; end;
    4: case y of
      1: colr:=Shape31.Brush.Color;
      2: colr:=Shape32.Brush.Color;
      3: colr:=Shape33.Brush.Color;
      4: colr:=Shape34.Brush.Color;
      5: colr:=Shape35.Brush.Color;
      6: colr:=Shape36.Brush.Color;
      7: colr:=Shape37.Brush.Color;
      8: colr:=Shape38.Brush.Color;
      9: colr:=Shape39.Brush.Color;
      10: colr:=Shape40.Brush.Color; end;
    5: case y of
      1: colr:=Shape41.Brush.Color;
      2: colr:=Shape42.Brush.Color;
      3: colr:=Shape43.Brush.Color;
      4: colr:=Shape44.Brush.Color;
      5: colr:=Shape45.Brush.Color;
      6: colr:=Shape46.Brush.Color;
      7: colr:=Shape47.Brush.Color;
      8: colr:=Shape48.Brush.Color;
      9: colr:=Shape49.Brush.Color;
      10: colr:=Shape50.Brush.Color; end;
    6: case y of
      1: colr:=Shape51.Brush.Color;
      2: colr:=Shape52.Brush.Color;
      3: colr:=Shape53.Brush.Color;
      4: colr:=Shape54.Brush.Color;
      5: colr:=Shape55.Brush.Color;
      6: colr:=Shape56.Brush.Color;
      7: colr:=Shape57.Brush.Color;
      8: colr:=Shape58.Brush.Color;
      9: colr:=Shape59.Brush.Color;
      10: colr:=Shape60.Brush.Color; end;
    7: case y of
      1: colr:=Shape61.Brush.Color;
      2: colr:=Shape62.Brush.Color;
      3: colr:=Shape63.Brush.Color;
      4: colr:=Shape64.Brush.Color;
      5: colr:=Shape65.Brush.Color;
      6: colr:=Shape66.Brush.Color;
      7: colr:=Shape67.Brush.Color;
      8: colr:=Shape68.Brush.Color;
      9: colr:=Shape69.Brush.Color;
      10: colr:=Shape70.Brush.Color; end;
    8: case y of
      1: colr:=Shape71.Brush.Color;
      2: colr:=Shape72.Brush.Color;
      3: colr:=Shape73.Brush.Color;
      4: colr:=Shape74.Brush.Color;
      5: colr:=Shape75.Brush.Color;
      6: colr:=Shape76.Brush.Color;
      7: colr:=Shape77.Brush.Color;
      8: colr:=Shape78.Brush.Color;
      9: colr:=Shape79.Brush.Color;
      10: colr:=Shape80.Brush.Color; end;
    9: case y of
      1: colr:=Shape81.Brush.Color;
      2: colr:=Shape82.Brush.Color;
      3: colr:=Shape83.Brush.Color;
      4: colr:=Shape84.Brush.Color;
      5: colr:=Shape85.Brush.Color;
      6: colr:=Shape86.Brush.Color;
      7: colr:=Shape87.Brush.Color;
      8: colr:=Shape88.Brush.Color;
      9: colr:=Shape89.Brush.Color;
      10: colr:=Shape90.Brush.Color; end;
    10: case y of
      1: colr:=Shape91.Brush.Color;
      2: colr:=Shape92.Brush.Color;
      3: colr:=Shape93.Brush.Color;
      4: colr:=Shape94.Brush.Color;
      5: colr:=Shape95.Brush.Color;
      6: colr:=Shape96.Brush.Color;
      7: colr:=Shape97.Brush.Color;
      8: colr:=Shape98.Brush.Color;
      9: colr:=Shape99.Brush.Color;
      10: colr:=Shape100.Brush.Color; end;
    11: case y of
      1: colr:=Shape101.Brush.Color;
      2: colr:=Shape102.Brush.Color;
      3: colr:=Shape103.Brush.Color;
      4: colr:=Shape104.Brush.Color;
      5: colr:=Shape105.Brush.Color;
      6: colr:=Shape106.Brush.Color;
      7: colr:=Shape107.Brush.Color;
      8: colr:=Shape108.Brush.Color;
      9: colr:=Shape109.Brush.Color;
      10: colr:=Shape110.Brush.Color; end;
    12: case y of
      1: colr:=Shape111.Brush.Color;
      2: colr:=Shape112.Brush.Color;
      3: colr:=Shape113.Brush.Color;
      4: colr:=Shape114.Brush.Color;
      5: colr:=Shape115.Brush.Color;
      6: colr:=Shape116.Brush.Color;
      7: colr:=Shape117.Brush.Color;
      8: colr:=Shape118.Brush.Color;
      9: colr:=Shape119.Brush.Color;
      10: colr:=Shape120.Brush.Color; end;
    13: case y of
      1: colr:=Shape121.Brush.Color;
      2: colr:=Shape122.Brush.Color;
      3: colr:=Shape123.Brush.Color;
      4: colr:=Shape124.Brush.Color;
      5: colr:=Shape125.Brush.Color;
      6: colr:=Shape126.Brush.Color;
      7: colr:=Shape127.Brush.Color;
      8: colr:=Shape128.Brush.Color;
      9: colr:=Shape129.Brush.Color;
      10: colr:=Shape130.Brush.Color; end;
    14: case y of
      1: colr:=Shape131.Brush.Color;
      2: colr:=Shape132.Brush.Color;
      3: colr:=Shape133.Brush.Color;
      4: colr:=Shape134.Brush.Color;
      5: colr:=Shape135.Brush.Color;
      6: colr:=Shape136.Brush.Color;
      7: colr:=Shape137.Brush.Color;
      8: colr:=Shape138.Brush.Color;
      9: colr:=Shape139.Brush.Color;
      10: colr:=Shape140.Brush.Color; end;
    15: case y of
      1: colr:=Shape141.Brush.Color;
      2: colr:=Shape142.Brush.Color;
      3: colr:=Shape143.Brush.Color;
      4: colr:=Shape144.Brush.Color;
      5: colr:=Shape145.Brush.Color;
      6: colr:=Shape146.Brush.Color;
      7: colr:=Shape147.Brush.Color;
      8: colr:=Shape148.Brush.Color;
      9: colr:=Shape149.Brush.Color;
      10: colr:=Shape150.Brush.Color; end;
    16: case y of
      1: colr:=Shape151.Brush.Color;
      2: colr:=Shape152.Brush.Color;
      3: colr:=Shape153.Brush.Color;
      4: colr:=Shape154.Brush.Color;
      5: colr:=Shape155.Brush.Color;
      6: colr:=Shape156.Brush.Color;
      7: colr:=Shape157.Brush.Color;
      8: colr:=Shape158.Brush.Color;
      9: colr:=Shape159.Brush.Color;
      10: colr:=Shape160.Brush.Color; end;
    17: case y of
      1: colr:=Shape161.Brush.Color;
      2: colr:=Shape162.Brush.Color;
      3: colr:=Shape163.Brush.Color;
      4: colr:=Shape164.Brush.Color;
      5: colr:=Shape165.Brush.Color;
      6: colr:=Shape166.Brush.Color;
      7: colr:=Shape167.Brush.Color;
      8: colr:=Shape168.Brush.Color;
      9: colr:=Shape169.Brush.Color;
      10: colr:=Shape170.Brush.Color; end;
    18: case y of
      1: colr:=Shape171.Brush.Color;
      2: colr:=Shape172.Brush.Color;
      3: colr:=Shape173.Brush.Color;
      4: colr:=Shape174.Brush.Color;
      5: colr:=Shape175.Brush.Color;
      6: colr:=Shape176.Brush.Color;
      7: colr:=Shape177.Brush.Color;
      8: colr:=Shape178.Brush.Color;
      9: colr:=Shape179.Brush.Color;
      10: colr:=Shape180.Brush.Color; end;
    19: case y of
      1: colr:=Shape181.Brush.Color;
      2: colr:=Shape182.Brush.Color;
      3: colr:=Shape183.Brush.Color;
      4: colr:=Shape184.Brush.Color;
      5: colr:=Shape185.Brush.Color;
      6: colr:=Shape186.Brush.Color;
      7: colr:=Shape187.Brush.Color;
      8: colr:=Shape188.Brush.Color;
      9: colr:=Shape189.Brush.Color;
      10: colr:=Shape190.Brush.Color; end;
    20: case y of
      1: colr:=Shape191.Brush.Color;
      2: colr:=Shape192.Brush.Color;
      3: colr:=Shape193.Brush.Color;
      4: colr:=Shape194.Brush.Color;
      5: colr:=Shape195.Brush.Color;
      6: colr:=Shape196.Brush.Color;
      7: colr:=Shape197.Brush.Color;
      8: colr:=Shape198.Brush.Color;
      9: colr:=Shape199.Brush.Color;
      10: colr:=Shape200.Brush.Color; end; end;
   result:=colr;
  end;
end;

procedure cellhelp(num,x,y: integer; colr: Tcolor);
begin
  with form1 do
  begin //begin with
  case num of
  1:case x of
    1: case y of
      1: Shape201.Brush.Color:=colr;
      2: Shape202.Brush.Color:=colr;
      3: Shape203.Brush.Color:=colr;
      4: Shape204.Brush.Color:=colr; end;
    2: case y of
      1: Shape205.Brush.Color:=colr;
      2: Shape206.Brush.Color:=colr;
      3: Shape207.Brush.Color:=colr;
      4: Shape208.Brush.Color:=colr; end;
    3: case y of
      1: Shape209.Brush.Color:=colr;
      2: Shape210.Brush.Color:=colr;
      3: Shape211.Brush.Color:=colr;
      4: Shape212.Brush.Color:=colr;end;
    4: case y of
      1: Shape213.Brush.Color:=colr;
      2: Shape214.Brush.Color:=colr;
      3: Shape215.Brush.Color:=colr;
      4: Shape216.Brush.Color:=colr; end; end;
  2:case x of
    1: case y of
      1: Shape217.Brush.Color:=colr;
      2: Shape218.Brush.Color:=colr;
      3: Shape219.Brush.Color:=colr;
      4: Shape220.Brush.Color:=colr; end;
    2: case y of
      1: Shape221.Brush.Color:=colr;
      2: Shape222.Brush.Color:=colr;
      3: Shape223.Brush.Color:=colr;
      4: Shape224.Brush.Color:=colr; end;
    3: case y of
      1: Shape225.Brush.Color:=colr;
      2: Shape226.Brush.Color:=colr;
      3: Shape227.Brush.Color:=colr;
      4: Shape228.Brush.Color:=colr;end;
    4: case y of
      1: Shape229.Brush.Color:=colr;
      2: Shape230.Brush.Color:=colr;
      3: Shape231.Brush.Color:=colr;
      4: Shape232.Brush.Color:=colr; end; end;
  3:case x of
    1: case y of
      1: Shape233.Brush.Color:=colr;
      2: Shape234.Brush.Color:=colr;
      3: Shape235.Brush.Color:=colr;
      4: Shape236.Brush.Color:=colr; end;
    2: case y of
      1: Shape237.Brush.Color:=colr;
      2: Shape238.Brush.Color:=colr;
      3: Shape239.Brush.Color:=colr;
      4: Shape240.Brush.Color:=colr; end;
    3: case y of
      1: Shape241.Brush.Color:=colr;
      2: Shape242.Brush.Color:=colr;
      3: Shape243.Brush.Color:=colr;
      4: Shape244.Brush.Color:=colr;end;
    4: case y of
      1: Shape245.Brush.Color:=colr;
      2: Shape246.Brush.Color:=colr;
      3: Shape247.Brush.Color:=colr;
      4: Shape248.Brush.Color:=colr; end; end;
  4:case x of
    1: case y of
      1: Shape249.Brush.Color:=colr;
      2: Shape250.Brush.Color:=colr;
      3: Shape251.Brush.Color:=colr;
      4: Shape252.Brush.Color:=colr; end;
    2: case y of
      1: Shape253.Brush.Color:=colr;
      2: Shape254.Brush.Color:=colr;
      3: Shape255.Brush.Color:=colr;
      4: Shape256.Brush.Color:=colr; end;
    3: case y of
      1: Shape257.Brush.Color:=colr;
      2: Shape258.Brush.Color:=colr;
      3: Shape259.Brush.Color:=colr;
      4: Shape260.Brush.Color:=colr;end;
    4: case y of
      1: Shape261.Brush.Color:=colr;
      2: Shape262.Brush.Color:=colr;
      3: Shape263.Brush.Color:=colr;
      4: Shape264.Brush.Color:=colr; end; end; end;
  end; //end with
end;

procedure TForm1.FormCreate(Sender: TObject);
begin
  x:=0;y:=5;
  xprev:=1;yprev:=5;
  Speed:=1000;
  level:=1;
  Timer1.Interval:=Speed;
  panel3.Caption:=inttostr(level);
  panel4.Caption:=inttostr(0);
  panel5.Caption:=inttostr(0);
  Randomize;
  while shnumhelp[1]=0 do shnumhelp[1]:=Random(20);
  while shnumhelp[2]=0 do shnumhelp[2]:=Random(20);
  while shnumhelp[3]=0 do shnumhelp[3]:=Random(20);
  while shnumhelp[4]=0 do shnumhelp[4]:=Random(20);
  while shnum=0 do shnum:=Random(20);
  Randomshape(20);
  shadowdelete();
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  case shnum of
    1:begin sh1(x,y,clwhite); if iscolsh1(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(1,y); sh1(x,y,colory[1]);end else begin shadowdelete(); sh1(x,y,colory[1]); findfullrows(); end; end;
    2:begin sh2(x,y,clwhite); if iscolsh2(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(2,y); sh2(x,y,colory[1]);end else begin shadowdelete(); sh2(x,y,colory[1]); findfullrows(); end; end;
    3:begin sh3(x,y,clwhite); if iscolsh3(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(3,y); sh3(x,y,colory[2]);end else begin shadowdelete(); sh3(x,y,colory[2]); findfullrows(); end; end;
    4:begin sh4(x,y,clwhite); if iscolsh4(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(4,y); sh4(x,y,colory[2]);end else begin shadowdelete(); sh4(x,y,colory[2]); findfullrows(); end; end;
    5:begin sh5(x,y,clwhite); if iscolsh5(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(5,y); sh5(x,y,colory[2]);end else begin shadowdelete(); sh5(x,y,colory[2]); findfullrows(); end; end;
    6:begin sh6(x,y,clwhite); if iscolsh6(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(6,y); sh6(x,y,colory[2]);end else begin shadowdelete(); sh6(x,y,colory[2]); findfullrows(); end; end;
    7:begin sh7(x,y,clwhite); if iscolsh7(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(7,y); sh7(x,y,colory[3]);end else begin shadowdelete(); sh7(x,y,colory[3]); findfullrows(); end; end;
    8:begin sh8(x,y,clwhite); if iscolsh8(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(8,y); sh8(x,y,colory[3]);end else begin shadowdelete(); sh8(x,y,colory[3]); findfullrows(); end; end;
    9:begin sh9(x,y,clwhite); if iscolsh9(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(9,y); sh9(x,y,colory[4]);end else begin shadowdelete(); sh9(x,y,colory[4]); findfullrows(); end; end;
    10:begin sh10(x,y,clwhite); if iscolsh10(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(10,y); sh10(x,y,colory[4]);end else begin shadowdelete(); sh10(x,y,colory[4]); findfullrows(); end; end;
    11:begin sh11(x,y,clwhite); if iscolsh11(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(11,y); sh11(x,y,colory[5]);end else begin shadowdelete(); sh11(x,y,colory[5]); findfullrows(); end; end;
    12:begin sh12(x,y,clwhite); if iscolsh12(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(12,y); sh12(x,y,colory[5]);end else begin shadowdelete(); sh12(x,y,colory[5]); findfullrows(); end; end;
    13:begin sh13(x,y,clwhite); if iscolsh13(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(13,y); sh13(x,y,colory[5]);end else begin shadowdelete(); sh13(x,y,colory[5]); findfullrows(); end; end;
    14:begin sh14(x,y,clwhite); if iscolsh14(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(14,y); sh14(x,y,colory[5]);end else begin shadowdelete(); sh14(x,y,colory[5]); findfullrows(); end; end;
    15:begin sh15(x,y,clwhite); if iscolsh15(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(15,y); sh15(x,y,colory[6]);end else begin shadowdelete(); sh15(x,y,colory[6]); findfullrows(); end; end;
    16:begin sh16(x,y,clwhite); if iscolsh16(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(16,y); sh16(x,y,colory[6]);end else begin shadowdelete(); sh16(x,y,colory[6]); findfullrows(); end; end;
    17:begin sh17(x,y,clwhite); if iscolsh17(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(17,y); sh17(x,y,colory[6]);end else begin shadowdelete(); sh17(x,y,colory[6]); findfullrows(); end; end;
    18:begin sh18(x,y,clwhite); if iscolsh18(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(18,y); sh18(x,y,colory[6]);end else begin shadowdelete(); sh18(x,y,colory[6]); findfullrows(); end; end;
    19:begin sh19(x,y,clwhite); if iscolsh19(x+1,y,clWhite,clSilver)and(x<20) then begin  x:=x+1;shadow(19,y); sh19(x,y,colory[7]);end else begin shadowdelete(); sh19(x,y,colory[7]); findfullrows(); end; end; end;
end;

procedure TForm1.FormKeyDown(Sender: TObject; var Key: Word;
  Shift: TShiftState);
var i,j: integer;
begin
  if (Key=vk_Left) and (y>1) then
  begin
    shadowdelete();
    case shnum of
    1: begin sh1(x,y,clwhite); if iscolsh1(x,y-1,clWhite,clSilver) then y:=y-1; shadow(1,y); sh1(x,y,colory[1]);end;
    2: begin sh2(x,y,clwhite); if iscolsh2(x,y-1,clWhite,clSilver) then y:=y-1; shadow(2,y); sh2(x,y,colory[1]);end;
    3: begin sh3(x,y,clwhite); if iscolsh3(x,y-1,clWhite,clSilver) then y:=y-1; shadow(3,y); sh3(x,y,colory[2]);end;
    4: begin sh4(x,y,clwhite); if iscolsh4(x,y-1,clWhite,clSilver) then y:=y-1; shadow(4,y); sh4(x,y,colory[2]);end;
    5: begin sh5(x,y,clwhite); if iscolsh5(x,y-1,clWhite,clSilver) then y:=y-1; shadow(5,y); sh5(x,y,colory[2]);end;
    6: begin sh6(x,y,clwhite); if iscolsh6(x,y-1,clWhite,clSilver) then y:=y-1; shadow(6,y); sh6(x,y,colory[2]);end;
    7: begin sh7(x,y,clwhite); if iscolsh7(x,y-1,clWhite,clSilver) then y:=y-1; shadow(7,y); sh7(x,y,colory[3]);end;
    8: begin sh8(x,y,clwhite); if iscolsh8(x,y-1,clWhite,clSilver) then y:=y-1; shadow(8,y); sh8(x,y,colory[3]);end;
    9: begin sh9(x,y,clwhite); if iscolsh9(x,y-1,clWhite,clSilver) then y:=y-1; shadow(9,y); sh9(x,y,colory[4]);end;
    10: begin sh10(x,y,clwhite); if iscolsh10(x,y-1,clWhite,clSilver) then y:=y-1; shadow(10,y); sh10(x,y,colory[4]);end;
    11: begin sh11(x,y,clwhite); if iscolsh11(x,y-1,clWhite,clSilver) then y:=y-1; shadow(11,y); sh11(x,y,colory[5]);end;
    12: begin sh12(x,y,clwhite); if iscolsh12(x,y-1,clWhite,clSilver) then y:=y-1; shadow(12,y); sh12(x,y,colory[5]);end;
    13: begin sh13(x,y,clwhite); if iscolsh13(x,y-1,clWhite,clSilver) then y:=y-1; shadow(13,y); sh13(x,y,colory[5]);end;
    14: begin sh14(x,y,clwhite); if iscolsh14(x,y-1,clWhite,clSilver) then y:=y-1; shadow(14,y); sh14(x,y,colory[5]);end;
    15: begin sh15(x,y,clwhite); if iscolsh15(x,y-1,clWhite,clSilver) then y:=y-1; shadow(15,y); sh15(x,y,colory[6]);end;
    16: begin sh16(x,y,clwhite); if iscolsh16(x,y-1,clWhite,clSilver) then y:=y-1; shadow(16,y); sh16(x,y,colory[6]);end;
    17: begin sh17(x,y,clwhite); if iscolsh17(x,y-1,clWhite,clSilver) then y:=y-1; shadow(17,y); sh17(x,y,colory[6]);end;
    18: begin sh18(x,y,clwhite); if iscolsh18(x,y-1,clWhite,clSilver) then y:=y-1; shadow(18,y); sh18(x,y,colory[6]);end;
    19: begin sh19(x,y,clwhite); if iscolsh19(x,y-1,clWhite,clSilver) then y:=y-1; shadow(19,y); sh19(x,y,colory[7]);end;
    end;
  end;
  if Key=vk_Right then
  begin
    shadowdelete();
    case shnum of
    1:begin sh1(x,y,clwhite); if iscolsh1(x,y+1,clWhite,clSilver) then y:=y+1; shadow(1,y); sh1(x,y,colory[1]);end;
    2:begin sh2(x,y,clwhite); if iscolsh2(x,y+1,clWhite,clSilver) then y:=y+1; shadow(2,y); sh2(x,y,colory[1]);end;
    3:begin sh3(x,y,clwhite); if iscolsh3(x,y+1,clWhite,clSilver) then y:=y+1; shadow(3,y); sh3(x,y,colory[2]);end;
    4:begin sh4(x,y,clwhite); if iscolsh4(x,y+1,clWhite,clSilver) then y:=y+1; shadow(4,y); sh4(x,y,colory[2]);end;
    5:begin sh5(x,y,clwhite); if iscolsh5(x,y+1,clWhite,clSilver) then y:=y+1; shadow(5,y); sh5(x,y,colory[2]);end;
    6:begin sh6(x,y,clwhite); if iscolsh6(x,y+1,clWhite,clSilver) then y:=y+1; shadow(6,y); sh6(x,y,colory[2]);end;
    7:begin sh7(x,y,clwhite); if iscolsh7(x,y+1,clWhite,clSilver) then y:=y+1; shadow(7,y); sh7(x,y,colory[3]);end;
    8:begin sh8(x,y,clwhite); if iscolsh8(x,y+1,clWhite,clSilver) then y:=y+1; shadow(8,y); sh8(x,y,colory[3]);end;
    9:begin sh9(x,y,clwhite); if iscolsh9(x,y+1,clWhite,clSilver) then y:=y+1; shadow(9,y); sh9(x,y,colory[4]);end;
    10:begin sh10(x,y,clwhite); if iscolsh10(x,y+1,clWhite,clSilver) then y:=y+1; shadow(10,y); sh10(x,y,colory[4]);end;
    11:begin sh11(x,y,clwhite); if iscolsh11(x,y+1,clWhite,clSilver) then y:=y+1; shadow(11,y); sh11(x,y,colory[5]);end;
    12:begin sh12(x,y,clwhite); if iscolsh12(x,y+1,clWhite,clSilver) then y:=y+1; shadow(12,y); sh12(x,y,colory[5]);end;
    13:begin sh13(x,y,clwhite); if iscolsh13(x,y+1,clWhite,clSilver) then y:=y+1; shadow(13,y); sh13(x,y,colory[5]);end;
    14:begin sh14(x,y,clwhite); if iscolsh14(x,y+1,clWhite,clSilver) then y:=y+1; shadow(14,y); sh14(x,y,colory[5]);end;
    15:begin sh15(x,y,clwhite); if iscolsh15(x,y+1,clWhite,clSilver) then y:=y+1; shadow(15,y); sh15(x,y,colory[6]);end;
    16:begin sh16(x,y,clwhite); if iscolsh16(x,y+1,clWhite,clSilver) then y:=y+1; shadow(16,y); sh16(x,y,colory[6]);end;
    17:begin sh17(x,y,clwhite); if iscolsh17(x,y+1,clWhite,clSilver) then y:=y+1; shadow(17,y); sh17(x,y,colory[6]);end;
    18:begin sh18(x,y,clwhite); if iscolsh18(x,y+1,clWhite,clSilver) then y:=y+1; shadow(18,y); sh18(x,y,colory[6]);end;
    19:begin sh19(x,y,clwhite); if iscolsh19(x,y+1,clWhite,clSilver) then y:=y+1; shadow(19,y); sh19(x,y,colory[7]);end;
    end;
  end;
  if Key=vk_up then
  begin
    case shnum of
    1:begin sh1(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[1]);findfullrows();end;
    2:begin sh2(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[1]);findfullrows();end;
    3:begin sh3(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[2]);findfullrows();end;
    4:begin sh4(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[2]);findfullrows();end;
    5:begin sh5(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[2]);findfullrows();end;
    6:begin sh6(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[2]);findfullrows();end;
    7:begin sh7(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[3]);findfullrows();end;
    8:begin sh8(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[3]);findfullrows();end;
    9:begin sh9(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[4]);findfullrows();end;
    10:begin sh10(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[4]);findfullrows();end;
    11:begin sh11(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[5]);findfullrows();end;
    12:begin sh12(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[5]);findfullrows();end;
    13:begin sh13(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[5]);findfullrows();end;
    14:begin sh14(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[5]);findfullrows();end;
    15:begin sh15(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[6]);findfullrows();end;
    16:begin sh16(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[6]);findfullrows();end;
    17:begin sh17(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[6]);findfullrows();end;
    18:begin sh18(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[6]);findfullrows();end;
    19:begin sh19(x,y,clwhite); for i:=1 to 20 do for j:=1 to 10 do if iscolcell(i,j,clSilver)then cell(i,j,colory[7]);findfullrows();end;
    end;
  end;
  if Key=vk_down then
  begin
    if level*10<100 then
    changetimer(200);
  end;
  if key=VK_SPACE then
  begin
    shadowdelete();
    case shnum of
    1: begin
          sh1(x,y,clwhite);
          if iscolsh2(x,y,clWhite,clSilver) then begin shnum:=2; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(2,y); sh2(x,y,colory[1]); end else
          if iscolsh2(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(2,y); sh2(x,y,colory[1]); shnum:=2; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh2(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(2,y); sh2(x,y,colory[1]); shnum:=2; timer1.enabled:=false; timer1.enabled:=true; end else sh1(x,y,colory[1]);
        end;
    2: begin
          sh2(x,y,clwhite);
          if iscolsh1(x,y,clWhite,clSilver) then begin shnum:=1; if (iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(1,y); sh1(x,y,colory[1]); end else
          if iscolsh1(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(1,y); sh1(x,y,colory[1]); shnum:=1; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh1(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(1,y); sh1(x,y,colory[1]); shnum:=1; timer1.enabled:=false; timer1.enabled:=true; end else sh2(x,y,colory[1]);
        end;
    3: begin
          sh3(x,y,clwhite);
          if iscolsh4(x,y,clWhite,clSilver) then begin shnum:=4; if (iscolcell(x+1,y+2,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(4,y); sh4(x,y,colory[2]); end else
          if iscolsh4(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(4,y);  sh4(x,y,colory[2]); shnum:=4; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh4(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(4,y);  sh4(x,y,colory[2]); shnum:=4; timer1.enabled:=false; timer1.enabled:=true; end else sh3(x,y,colory[2]);
        end;
    4: begin
          sh4(x,y,clwhite);
          if iscolsh5(x,y,clWhite,clSilver) then begin shnum:=5; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(5,y); sh5(x,y,colory[2]); end else
          if iscolsh5(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(5,y);  sh5(x,y,colory[2]); shnum:=5; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh5(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(5,y);  sh5(x,y,colory[2]); shnum:=5; timer1.enabled:=false; timer1.enabled:=true; end else sh4(x,y,colory[2]);
        end;
    5: begin
          sh5(x,y,clwhite); 
          if iscolsh6(x,y,clWhite,clSilver) then begin shnum:=6; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false)or(iscolcell(x+1,y+2,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(6,y); sh6(x,y,colory[2]); end else
          if iscolsh6(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(6,y);  sh6(x,y,colory[2]); shnum:=6; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh6(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(6,y);  sh6(x,y,colory[2]); shnum:=6; timer1.enabled:=false; timer1.enabled:=true; end else sh5(x,y,colory[2]); 
        end;
    6: begin
          sh6(x,y,clwhite); 
          if iscolsh3(x,y,clWhite,clSilver) then begin shnum:=3; if (iscolcell(x+1,y,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(3,y); sh3(x,y,colory[2]); end else
          if iscolsh3(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(3,y);  sh3(x,y,colory[2]); shnum:=3; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh3(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(3,y);  sh3(x,y,colory[2]); shnum:=3; timer1.enabled:=false; timer1.enabled:=true; end else sh6(x,y,colory[2]); 
        end;
    7: begin
          sh7(x,y,clwhite); 
          if iscolsh8(x,y,clWhite,clSilver) then begin shnum:=8; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false)or(iscolcell(x+1,y+2,clwhite)=false)or(iscolcell(x+1,y+3,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(8,y); sh8(x,y,colory[3]); end else
          if iscolsh8(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(8,y); sh8(x,y,colory[3]); shnum:=8; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh8(x,y-2,clWhite,clSilver) then begin y:=y-2; shadow(8,y); sh8(x,y,colory[3]); shnum:=8; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh8(x,y-3,clWhite,clSilver) then begin y:=y-3; shadow(8,y); sh8(x,y,colory[3]); shnum:=8; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh8(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(8,y); sh8(x,y,colory[3]); shnum:=8; timer1.enabled:=false; timer1.enabled:=true; end else sh7(x,y,colory[3]); 
        end;
    8: begin 
          sh8(x,y,clwhite);
          if iscolsh7(x,y,clWhite,clSilver) then begin shnum:=7; if (iscolcell(x+1,y,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(7,y); sh7(x,y,colory[3]); end else
          if iscolsh7(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(7,y);  sh7(x,y,colory[3]); shnum:=7; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh7(x,y+2,clWhite,clSilver) then begin y:=y+2; shadow(7,y); sh7(x,y,colory[3]); shnum:=7; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh7(x,y+3,clWhite,clSilver) then begin y:=y+3; shadow(7,y); sh7(x,y,colory[3]); shnum:=7; timer1.enabled:=false; timer1.enabled:=true; end else sh8(x,y,colory[3]); 
        end;
    9: begin 
          sh9(x,y,clwhite); 
          if iscolsh10(x,y,clWhite,clSilver) then begin shnum:=10; if (iscolcell(x+1,y+1,clwhite)=false)or(iscolcell(x+1,y+2,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(10,y); sh10(x,y,colory[4]); end else
          if iscolsh10(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(10,y);  sh10(x,y,colory[4]); shnum:=10; timer1.enabled:=false; timer1.enabled:=true; end else
          if iscolsh10(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(10,y);  sh10(x,y,colory[4]); shnum:=10; timer1.enabled:=false; timer1.enabled:=true; end else sh9(x,y,colory[4]);
        end;
    10: begin 
            sh10(x,y,clwhite);
            if iscolsh9(x,y,clWhite,clSilver) then begin shnum:=9; if (iscolcell(x+1,y,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(9,y); sh9(x,y,colory[4]); end else
            if iscolsh9(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(9,y);  sh9(x,y,colory[4]); shnum:=9; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh9(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(9,y);  sh9(x,y,colory[4]); shnum:=9; timer1.enabled:=false; timer1.enabled:=true; end else sh10(x,y,colory[4]);
          end;
    11: begin
            sh11(x,y,clwhite);
            if iscolsh12(x,y,clWhite,clSilver) then begin shnum:=12; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false)or(iscolcell(x+1,y+2,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(12,y); sh12(x,y,colory[5]); end else
            if iscolsh12(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(12,y);  sh12(x,y,colory[5]); shnum:=12; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh12(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(12,y);  sh12(x,y,colory[5]); shnum:=12; timer1.enabled:=false; timer1.enabled:=true; end else sh11(x,y,colory[5]);
          end;
    12: begin
            sh12(x,y,clwhite); 
            if iscolsh13(x,y,clWhite,clSilver) then begin shnum:=13; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(13,y); sh13(x,y,colory[5]); end else
            if iscolsh13(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(13,y);  sh13(x,y,colory[5]); shnum:=13; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh13(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(13,y);  sh13(x,y,colory[5]); shnum:=13; timer1.enabled:=false; timer1.enabled:=true; end else sh12(x,y,colory[5]);
          end;
    13: begin 
            sh13(x,y,clwhite); 
            if iscolsh14(x,y,clWhite,clSilver) then begin shnum:=14; if (iscolcell(x+1,y,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(14,y); sh14(x,y,colory[5]); end else
            if iscolsh14(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(14,y);  sh14(x,y,colory[5]); shnum:=14; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh14(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(14,y);  sh14(x,y,colory[5]); shnum:=14; timer1.enabled:=false; timer1.enabled:=true; end else sh13(x,y,colory[2]); 
          end;
    14: begin
            sh14(x,y,clwhite); 
            if iscolsh11(x,y,clWhite,clSilver) then begin shnum:=11; if (iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(11,y); sh11(x,y,colory[5]); end else
            if iscolsh11(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(11,y);  sh11(x,y,colory[5]); shnum:=11; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh11(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(11,y);  sh11(x,y,colory[5]); shnum:=11; timer1.enabled:=false; timer1.enabled:=true; end else sh14(x,y,colory[5]); 
          end;
    15: begin
            sh15(x,y,clwhite);
            if iscolsh16(x,y,clWhite,clSilver) then begin shnum:=16; if (iscolcell(x+1,y,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(16,y); sh16(x,y,colory[6]); end else
            if iscolsh16(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(16,y);  sh16(x,y,colory[6]); shnum:=16; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh16(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(16,y);  sh16(x,y,colory[6]); shnum:=16; timer1.enabled:=false; timer1.enabled:=true; end else sh15(x,y,colory[6]); 
          end;
    16: begin
            sh16(x,y,clwhite);
            if iscolsh17(x,y,clWhite,clSilver) then begin shnum:=17; if (iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(17,y); sh17(x,y,colory[6]); end else
            if iscolsh17(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(17,y);  sh17(x,y,colory[6]); shnum:=17; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh17(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(17,y);  sh17(x,y,colory[6]); shnum:=17; timer1.enabled:=false; timer1.enabled:=true; end else sh16(x,y,colory[6]); 
          end;
    17: begin
            sh17(x,y,clwhite);
            if iscolsh18(x,y,clWhite,clSilver) then begin shnum:=18; if  (iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(18,y); sh18(x,y,colory[6]);  end else
            if iscolsh18(x,y+1,clWhite,clSilver) then begin y:=y+1; shadow(18,y);  sh18(x,y,colory[6]); shnum:=18; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh18(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(18,y);  sh18(x,y,colory[6]); shnum:=18; timer1.enabled:=false; timer1.enabled:=true; end else sh17(x,y,colory[6]); 
          end;
    18: begin 
            sh18(x,y,clwhite); 
            if iscolsh15(x,y,clWhite,clSilver) then begin shnum:=15; if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false)or(iscolcell(x+1,y+2,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; shadow(15,y); sh15(x,y,colory[6]); end else
            if iscolsh15(x,y-1,clWhite,clSilver) then begin y:=y-1; shadow(15,y);  sh15(x,y,colory[6]); shnum:=15; timer1.enabled:=false; timer1.enabled:=true; end else
            if iscolsh15(x-1,y,clWhite,clSilver) then begin x:=x-1; shadow(15,y);  sh15(x,y,colory[6]); shnum:=15; timer1.enabled:=false; timer1.enabled:=true; end else sh18(x,y,colory[6]);
          end;
    19: begin  if (iscolcell(x+1,y,clwhite)=false)or(iscolcell(x+1,y+1,clwhite)=false) then begin timer1.enabled:=false; timer1.enabled:=true; end; end;
    end;
  end;

end;

procedure TForm1.FormKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if Key=vk_Down then
  begin
  changetimer(level);
  end;
end;

procedure TForm1.Panel2Click(Sender: TObject);
begin
if timer1.Enabled then
begin Panel2.Color:=clblack; timer1.Enabled:=false; end
else
begin Panel2.Color:=clmaroon; timer1.Enabled:=true; end;
end;

function Randomshape(int: integer): integer;
var i,j,k: integer;
begin
  form1.Timer1.Interval:=Speed;
  result:=shnumhelp[1];
  shnumhelp[1]:=shnumhelp[2];
  shnumhelp[2]:=shnumhelp[3];
  shnumhelp[3]:=shnumhelp[4];
  shnumhelp[4]:=Random(int);
  while shnumhelp[4]=0 do shnumhelp[4]:=Random(int);
  for i:=1 to 4 do
  for j:=1 to 4 do
  for k:=1 to 4 do cellhelp(i,j,k,clwhite);
  for i:=1 to 4 do
  case shnumhelp[i] of
    1:helpsh1(i,4,2,colory[1]);
    2:helpsh2(i,4,2,colory[1]);
    3:helpsh3(i,4,2,colory[2]);
    4:helpsh4(i,4,1,colory[2]);
    5:helpsh5(i,4,2,colory[2]);
    6:helpsh6(i,4,2,colory[2]);
    7:helpsh7(i,4,2,colory[3]);
    8:helpsh8(i,3,1,colory[3]);
    9:helpsh9(i,4,2,colory[4]);
    10:helpsh10(i,4,2,colory[4]);
    11:helpsh11(i,4,2,colory[5]);
    12:helpsh12(i,4,1,colory[5]);
    13:helpsh13(i,4,2,colory[5]);
    14:helpsh14(i,4,2,colory[5]);
    15:helpsh15(i,4,2,colory[6]);
    16:helpsh16(i,4,2,colory[6]);
    17:helpsh17(i,4,2,colory[6]);
    18:helpsh18(i,4,2,colory[6]);
    19:helpsh19(i,4,2,colory[7]);
  end;
end;

procedure changetimer(i: integer);
begin
  Form1.Timer1.Interval:=round(Speed/sqrt(i)-50);
end;

procedure findfullrows();
var i,j: integer;
    bl: boolean;
begin
  form1.Timer1.enabled:=false;
  x:=0; y:=5;
  shnum:=randomshape(20);
  if strtoint(Form1.Panel5.Caption)>(50*level+(sqr(level)+level)/2*10) then level:=level+1;
  Form1.Panel3.Caption:=inttostr(level);
  changetimer(level);
  destroycell:=1;
  destroyrow:=0;
  for i:=1 to 20 do
  begin
    bl:=true;
    for j:=1 to 10 do
    begin
      if iscolcell(i,j,clwhite) then bl:=false;
    end;
    if bl then begin fullrow[i]:=true; destroyrow:=destroyrow+1; end;
  end;

  Form1.Panel4.caption:=inttostr(destroyrow);
  if fullrow[14] then begin Form1.Panel4.caption:=Form1.Panel4.caption+' x2'; destroyrow:=destroyrow*2;end;
  if fullrow[8] then begin Form1.Panel4.caption:=Form1.Panel4.caption+' x3'; destroyrow:=destroyrow*3;end;
  if fullrow[5] then begin Form1.Panel4.caption:=Form1.Panel4.caption+' x4'; destroyrow:=destroyrow*4;end;
  if fullrow[3] then begin Form1.Panel4.caption:=Form1.Panel4.caption+' x5'; destroyrow:=destroyrow*5;end;
  Form1.Panel5.caption:=inttostr(strtoint(Form1.Panel5.caption)+destroyrow);

  form1.Timer2.enabled:=true;
end;

procedure TForm1.Timer2Timer(Sender: TObject);
var i: integer;
begin
  for i:=1 to 20 do if fullrow[i] then cell(i,destroycell,clwhite);
  if fullrow[14] then begin if Form1.Label5.font.Color=clyellow then Form1.Label5.font.Color:=clred else Form1.Label5.font.Color:=clyellow; end;
  if fullrow[8] then begin if Form1.Label4.font.Color=clyellow then Form1.Label4.font.Color:=clred else Form1.Label4.font.Color:=clyellow; end;
  if fullrow[5] then begin if Form1.Label3.font.Color=clyellow then Form1.Label3.font.Color:=clred else Form1.Label3.font.Color:=clyellow; end;
  if fullrow[3] then begin if Form1.Label2.font.Color=clyellow then Form1.Label2.font.Color:=clred else Form1.Label2.font.Color:=clyellow; end;
  destroycell:=destroycell+1;
  if destroycell>10 then begin Timer2.enabled:=false; Timer3.enabled:=true; end;
end;

procedure TForm1.Timer3Timer(Sender: TObject);
var i,j: integer;
    bl: boolean;
begin
  if destroyrow>0 then
  begin
    destroyrow:=destroyrow-1;
    i:=20;
    while i>0 do
    begin
      if fullrow[i] then
      begin
        bl:=fullrow[i];
        if i-1>0 then
        begin
          fullrow[i]:=fullrow[i-1];
          fullrow[i-1]:=bl;
        end;
        for j:=0 to 10 do cell(i,j,getcolorcell(i-1,j));
      end;
      i:=i-1;
    end;
  end else
  begin Timer3.enabled:=false; Timer1.enabled:=true; for i:=1 to 20 do fullrow[i]:=false; end;
end;

procedure shadow(i,y: integer);
var j: integer;
    w: TColor;
begin
  j:=x;
  w:=clSilver;
  shadowdelete();
  case i of
  1:begin while j<21 do if iscolsh1(j,y,clwhite,clwhite) then j:=j+1 else break; sh1(j-1,y,w); end;
  2:begin while j<21 do if iscolsh2(j,y,clwhite,clwhite) then j:=j+1 else break; sh2(j-1,y,w); end;
  3:begin while j<21 do if iscolsh3(j,y,clwhite,clwhite) then j:=j+1 else break; sh3(j-1,y,w); end;
  4:begin while j<21 do if iscolsh4(j,y,clwhite,clwhite) then j:=j+1 else break; sh4(j-1,y,w); end;
  5:begin while j<21 do if iscolsh5(j,y,clwhite,clwhite) then j:=j+1 else break; sh5(j-1,y,w); end;
  6:begin while j<21 do if iscolsh6(j,y,clwhite,clwhite) then j:=j+1 else break; sh6(j-1,y,w); end;
  7:begin while j<21 do if iscolsh7(j,y,clwhite,clwhite) then j:=j+1 else break; sh7(j-1,y,w); end;
  8:begin while j<21 do if iscolsh8(j,y,clwhite,clwhite) then j:=j+1 else break; sh8(j-1,y,w); end;
  9:begin while j<21 do if iscolsh9(j,y,clwhite,clwhite) then j:=j+1 else break; sh9(j-1,y,w); end;
  10:begin while j<21 do if iscolsh10(j,y,clwhite,clwhite) then j:=j+1 else break; sh10(j-1,y,w); end;
  11:begin while j<21 do if iscolsh11(j,y,clwhite,clwhite) then j:=j+1 else break; sh11(j-1,y,w); end;
  12:begin while j<21 do if iscolsh12(j,y,clwhite,clwhite) then j:=j+1 else break; sh12(j-1,y,w); end;
  13:begin while j<21 do if iscolsh13(j,y,clwhite,clwhite) then j:=j+1 else break; sh13(j-1,y,w); end;
  14:begin while j<21 do if iscolsh14(j,y,clwhite,clwhite) then j:=j+1 else break; sh14(j-1,y,w); end;
  15:begin while j<21 do if iscolsh15(j,y,clwhite,clwhite) then j:=j+1 else break; sh15(j-1,y,w); end;
  16:begin while j<21 do if iscolsh16(j,y,clwhite,clwhite) then j:=j+1 else break; sh16(j-1,y,w); end;
  17:begin while j<21 do if iscolsh17(j,y,clwhite,clwhite) then j:=j+1 else break; sh17(j-1,y,w); end;
  18:begin while j<21 do if iscolsh18(j,y,clwhite,clwhite) then j:=j+1 else break; sh18(j-1,y,w); end;
  19:begin while j<21 do if iscolsh19(j,y,clwhite,clwhite) then j:=j+1 else break; sh19(j-1,y,w); end; end;
end;

procedure shadowdelete();
var i,j: integer;
begin
  for i:=1 to 20 do
  for j:=1 to 10 do
  if iscolcell(i,j,clSilver) then cell(i,j,clwhite);
end;

end.