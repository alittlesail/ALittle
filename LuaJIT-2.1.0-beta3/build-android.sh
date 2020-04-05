NDK=D:/android-ndk-r20
NDKABI=29
NDKVER=$NDK/toolchains/llvm
NDKP=$NDKVER/prebuilt/windows-x86_64/bin/aarch64-linux-android29-
NDKF="--sysroot $NDK/toolchains/llvm/prebuilt/windows-x86_64/sysroot"
make HOST_CC="gcc -m64" CROSS=$NDKP TARGET_FLAGS="$NDKF" TARGET_SYS=Linux