; Windows Installer for easyFG
; Author: Mikhail N Polyanskiy (polyanskiy@bnl.gov)
; Brookhaven National Laboratory, USA

!include "MUI.nsh"

;General
SetCompressor lzma
Name "easyFG"
OutFile "easyFG_20150827.exe"

;Default install path
InstallDir "$PROGRAMFILES\easyFG"          ;default
InstallDirRegKey HKLM "Software\easyFG" "" ;if previous installation exists (overrides default)


;-------------------------Interface Settings---------------------------

!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\win.bmp"
;!define EASYFG_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\easyFG"
;!define EASYFG_ROOT_KEY "Applications\easyFG.exe"

;Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
  
;Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES
!insertmacro MUI_UNPAGE_FINISH

;Languages
!insertmacro MUI_LANGUAGE "English"


;-------------------------Installer Sections---------------------------

Section "Section_01" Sec01

  ;Read previous installation path from registry
  ReadRegDWORD $0 HKLM "Software\easyFG" ""

  ;Remove previous installation
  SetShellVarContext all
  RMDir /r $0                                   
  RMDir /r "$SMPROGRAMS\easyFG"
  RMDir /r "$INSTDIR"

  ;Write files to installation directory
  SetOutPath "$INSTDIR"
  File "release\easyFG.exe"
  File "C:\Qt\5.5\mingw492_32\bin\icudt54.dll"
  File "C:\Qt\5.5\mingw492_32\bin\icuin54.dll"
  File "C:\Qt\5.5\mingw492_32\bin\icuuc54.dll"
  File "C:\Qt\5.5\mingw492_32\bin\libgcc_s_dw2-1.dll"
  File "C:\Qt\Tools\mingw492_32\bin\libgomp-1.dll"
  File "C:\Qt\5.5\mingw492_32\bin\libstdc++-6.dll"
  File "C:\Qt\5.5\mingw492_32\bin\libwinpthread-1.dll"
  File "C:\Qt\5.5\mingw492_32\bin\Qt5Core.dll"
  File "C:\Qt\5.5\mingw492_32\bin\Qt5Gui.dll"
  File "C:\Qt\5.5\mingw492_32\bin\Qt5Widgets.dll"
  ;libtiff
  File "C:\Program Files (x86)\GnuWin32\bin\jpeg62.dll"
  File "C:\Program Files (x86)\GnuWin32\bin\libtiff3.dll"
  File "C:\Program Files (x86)\GnuWin32\bin\zlib1.dll"
  
  SetOutPath "$INSTDIR\platforms"
  File "C:\Qt\5.5\mingw492_32\plugins\platforms\qwindows.dll"  
  
  SetOutPath "$INSTDIR\imageformats"
  File "C:\Qt\5.5\mingw492_32\plugins\imageformats\qjpeg.dll"
  
  SetOutPath "$INSTDIR\src"
  File "easyfg.h"
  File "analysis.cpp"
  File "buttons.cpp"
  File "colormap.cpp"
  File "load.cpp"
  File "main.cpp"
  File "mainwindow.cpp"
  File "memory.cpp"
  File "reference.cpp"
  File "scale.cpp"
  File "scene.cpp"
  File "settings.cpp"
  File "shortcuts.cpp"
  File "update.cpp"
  File "mainwindow.ui"
  File "icon.rc"
  File "icon.qrc"
  File "easyFG.pro"
  File "installer.nsi"
  
  SetOutPath "$INSTDIR\src\icon"
  File "icon\*.*"
  SetOutPath "$INSTDIR\src\icon\valenky"
  File "icon\valenky\*.*"
  SetOutPath "$INSTDIR\examples"
  File "examples\*.*"
  
  ;Write Start menu entries
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\easyFG"
  CreateShortCut "$SMPROGRAMS\easyFG\easyFG.lnk" "$INSTDIR\easyFG.exe"
  ;SetOutPath "$SMPROGRAMS\easyFG"
  ;SetOverwrite on
  ;File "easyFG homepage.url"
  CreateShortCut "$SMPROGRAMS\easyFG\Uninstall easyFG.lnk" "$INSTDIR\uninstall.exe" "" ""
  
  ;Create desktope shortcut
  CreateShortCut "$DESKTOP\easyFG.lnk" "$INSTDIR\easyFG.exe"

  ;Registry
  ;WriteRegStr HKLM "Software\easyFG" "" $INSTDIR
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\easyFG.exe" "" "$INSTDIR\easyFG.exe"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\easyFG.exe" "Path" "$INSTDIR\"
  WriteRegStr HKCR "Applications\easyFG.exe\shell\open" "FriendlyAppName" "easyFG"
  WriteRegStr HKCR "Applications\easyFG.exe\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\"" ; "%1" without quotes: 8.3 name format
  
  ;Register extensions
  WriteRegStr HKCR ".asc\OpenWithProgIds" "easyFG.asc" ""
  WriteRegStr HKCR ".sif\OpenWithProgIds" "easyFG.sif" ""
  WriteRegStr HKCR ".tif\OpenWithProgIds" "easyFG.tif" ""
  WriteRegStr HKCR ".tiff\OpenWithProgIds" "easyFG.tiff" ""
  WriteRegStr HKCR ".raw\OpenWithProgIds" "easyFGraw" ""
  WriteRegStr HKCR "easyFG.asc\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\""
  WriteRegStr HKCR "easyFG.sif\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\""
  WriteRegStr HKCR "easyFG.tif\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\""
  WriteRegStr HKCR "easyFG.tiff\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\""
  WriteRegStr HKCR "easyFG.raw\shell\open\command" "" "$\"$INSTDIR\easyFG.exe$\" $\"%1$\""

  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\easyFG" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\easyFG" "DisplayName" "easyFG"
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\easyFG" "DisplayIcon" "$INSTDIR\easyFG.exe"

SectionEnd


;-------------------------Uninstaller Section---------------------------

Section "Uninstall"

  SetShellVarContext all
  RMDir /r "$SMPROGRAMS\easyFG"
  Delete "$DESKTOP\easyFG.lnk"

  Delete "$INSTDIR\uninstall.exe"
  RMDir /r "$INSTDIR"

  ;DeleteRegKey HKLM "Software\easyFG"
  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\easyFG.exe"
  DeleteRegKey HKCR "Applications\easyFG.exe" 
  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\easyFG"
  
  ;unregister extensions
  DeleteRegKey HKCR ".asc\OpenWithProgIds\easyFG.asc"
  DeleteRegKey HKCR ".sif\OpenWithProgIds\easyFG.sif"
  DeleteRegKey HKCR ".tif\OpenWithProgIds\easyFG.tif"
  DeleteRegKey HKCR ".tiff\OpenWithProgIds\easyFG.tiff"
  DeleteRegKey HKCR ".raw\OpenWithProgIds\easyFG.raw"

SectionEnd
