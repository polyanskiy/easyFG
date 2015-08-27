;
; Windows Installer for easyFG
;
; Author: Mikhail N Polyanskiy (polyanskiy@bnl.gov)
;
; Brookhaven National Laboratory, USA


!include "MUI.nsh"
;!include FileAssociation.nsh

;General
SetCompressor lzma
Name "easyFG"
OutFile "easyFG_20120320.exe"

;Default install path
InstallDir "$PROGRAMFILES\easyFG"          ;default
InstallDirRegKey HKLM "Software\easyFG" "" ;if previous installation exists (overrides default)


;-------------------------Interface Settings---------------------------

!define MUI_ABORTWARNING
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\win.bmp"
!define EASYFG_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\easyFG"
!define EASYFG_ROOT_KEY "Applications\easyFG.exe"

;Installer pages
!insertmacro MUI_PAGE_WELCOME
;!insertmacro MUI_PAGE_LICENSE "copying.txt"
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
  File "C:\QtSDK\mingw\bin\libgcc_s_dw2-1.dll"
  File "C:\QtSDK\mingw\bin\libstdc++-6.dll"
  File "C:\QtSDK\mingw\bin\mingwm10.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtCore4.dll"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\bin\QtGui4.dll"
  ;libtiff
  File "C:\Program Files (x86)\GnuWin32\bin\jpeg62.dll"
  File "C:\Program Files (x86)\GnuWin32\bin\libtiff3.dll"
  File "C:\Program Files (x86)\GnuWin32\bin\zlib1.dll"
  
  SetOutPath "$INSTDIR\imageformats"
  File "C:\QtSDK\Desktop\Qt\4.8.0\mingw\plugins\imageformats\qjpeg4.dll"
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
  WriteRegStr HKLM "Software\easyFG" "" $INSTDIR
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\SupportedTypes" ".asc" ""
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\SupportedTypes" ".sif" ""
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\SupportedTypes" ".tif" ""
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\SupportedTypes" ".tiff" ""
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\SupportedTypes" ".raw" ""
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\DefaultIcon" "" "$INSTDIR\easyFG.exe"
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\shell\open" "FriendlyAppName" "easyFG"
  WriteRegStr HKCR "${EASYFG_ROOT_KEY}\shell\open\command" "" "$INSTDIR\easyFG.exe %1"
  
  ;${registerExtension} "$INSTDIR\easyFG.exe" ".sif" "Andor sif file"


  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "${EASYFG_UNINST_KEY}" "UninstallString" "$INSTDIR\uninstall.exe"
  WriteRegStr HKLM "${EASYFG_UNINST_KEY}" "DisplayName" "easyFG"
  WriteRegStr HKLM "${EASYFG_UNINST_KEY}" "DisplayIcon" "$INSTDIR\easyFG.exe"

SectionEnd


;-------------------------Uninstaller Section---------------------------

Section "Uninstall"

  SetShellVarContext all
  RMDir /r "$SMPROGRAMS\easyFG"
  Delete "$DESKTOP\easyFG.lnk"

  Delete "$INSTDIR\uninstall.exe"
  RMDir /r "$INSTDIR"

  DeleteRegKey HKLM "Software\easyFG"
  DeleteRegKey HKLM "${EASYFG_UNINST_KEY}"
  DeleteRegKey HKCR "${EASYFG_ROOT_KEY}"

SectionEnd
