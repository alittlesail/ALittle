
mkdir ios

ISDKP=$(xcrun --sdk iphoneos --show-sdk-path)
ICC=$(xcrun --sdk iphoneos --find clang)

make clean

ISDKF="-arch arm64 -isysroot $ISDKP"
make DEFAULT_CC=clang HOST_CC="clang " CROSS="$(dirname $ICC)/" TARGET_FLAGS="$ISDKF" TARGET_SYS=iOS

mv "src/libluajit.a" "ios/libluajit.a"