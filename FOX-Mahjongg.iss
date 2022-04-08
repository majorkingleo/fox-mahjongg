; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "FOX-Mahjongg"
#define MyAppVersion "0.3"
#define MyAppPublisher "Martin Oberzalek"
#define MyAppURL "https://github.com/majorkingleo/fox-mahjongg"
#define MyAppExeName "fox-mahjongg.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{E5ED5547-4FD3-4FC5-83E5-8BC71AE4CDC6}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\{#MyAppName}
DisableProgramGroupPage=yes
LicenseFile=z:\home\martin\workspace\fox-mahjongg-win32\LICENSE.txt
; Remove the following line to run in administrative install mode (install for all users.)
PrivilegesRequired=lowest
PrivilegesRequiredOverridesAllowed=dialog
OutputDir=z:\home\martin\workspace\fox-mahjongg-win32
OutputBaseFilename=FOX-Mahjongg-installer-{#MyAppVersion}
Compression=bzip
SolidCompression=no
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libbz2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libcairo-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libcroco-0.6-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libdjvulibre-21.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libffi-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libfftw3-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libfftw3f-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libfontconfig-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libFOX-1.7-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libfreetype-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgdk_pixbuf-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgio-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libglib-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgmodule-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgobject-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libgomp-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libharfbuzz-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libintl-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libjasper-4.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libjpeg-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\liblcms2-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\liblzma-5.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libMagick++-Q16-7.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libMagickCore-Q16-7.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libMagickWand-Q16-7.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpango-1.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpangocairo-1.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpangoft2-1.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpangowin32-1.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpixman-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\librsvg-2-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libssp-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libtiff-5.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libxml2-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libz.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\dist\libpcre-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\images\xmahjongg.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "z:\home\martin\workspace\fox-mahjongg-win32\po\de.gmo"; DestDir: "{app}/de/LC_MESSAGES"; DestName: fox-mahjongg.mo; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}" ; IconFilename: "{app}\xmahjongg.ico"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; IconFilename: "{app}\xmahjongg.ico"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

