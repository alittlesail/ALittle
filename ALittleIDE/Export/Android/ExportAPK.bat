@echo off

set last_path=%cd%
chdir %~dp0

if [%1]==[] echo error:not found package name
if [%1]==[] goto :EOF

set package_path=%1
echo %package_path%
set base_path=../../../../Export/Android

set path=%base_path%\build-tools\jdk\bin
echo %path%

mkdir bin
mkdir bin\classes
mkdir gen

echo begin R.java
"%base_path%\build-tools\build-tools\29.0.2\aapt.exe" package -f -m -J gen -S res -I %base_path%\build-tools\platforms\android-29\android.jar -M AndroidManifest.xml
echo end R.java

echo begin javac
"%base_path%\build-tools\jdk\bin\javac"  -Xlint:unchecked -encoding UTF-8 -source 1.7 -target 1.7 -bootclasspath %base_path%\build-tools\platforms\android-29\android.jar -d bin\classes gen\%package_path%\R.java @src_list.txt
echo end javac

echo begin classes.dex
call "%base_path%\build-tools\build-tools\29.0.2\dx.bat" --dex --output=bin\classes.dex bin\classes %base_path%\libs\*.jar
echo end classes.dex

echo begin resource.ap_
"%base_path%\build-tools\build-tools\29.0.2\aapt.exe" package -f -S res -I %base_path%\build-tools\platforms\android-29\android.jar -A assets -M AndroidManifest.xml -F bin\resources.ap_
echo end resource.ap_

echo begin apk
"%base_path%\build-tools\jdk\bin\java" -cp %base_path%\build-tools\tools\lib\sdklib.jar com.android.sdklib.build.ApkBuilderMain bin\ALittleClient_unsigned.apk -v -u -z bin\resources.ap_ -f bin\classes.dex -rf %base_path%\src -nf %base_path%\libs -rj %base_path%\libs
echo end apk

echo begin Install.apk
"%base_path%\build-tools\jdk\bin\jarsigner" -verbose -storepass alittle -keystore %base_path%\build-tools\alittle.keystore -digestalg SHA1 -sigalg MD5withRSA -signedjar bin\Install.apk bin\ALittleClient_unsigned.apk alittle
echo end Install.apk

chdir %last_path%