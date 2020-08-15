; http://isskin.codejock.com

[Files]
Source: compiler:IsSkin.dll; DestDir: {tmp}; Flags: dontcopy noencryption

[Code]
procedure LoadSkin(lpszPath: AnsiString; lpszIniFileName: AnsiString);
external 'LoadSkin@files:IsSkin.dll stdcall';

procedure UnloadSkin();
external 'UnloadSkin@files:IsSkin.dll stdcall';
