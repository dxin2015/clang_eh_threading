APP_STL := c++_shared
APP_CPPFLAGS := -std=c++14 -fno-rtti -Werror -O2 -DANDROID_ARM_MODE=arm -DANDROID_ARM_NEON=TRUE -DNEON_ENABLED -DNO_ICONV=1 -DLIBCXXABI_USE_LLVM_UNWINDER=YES
APP_PLATFORM := android-28
APP_ABI := armeabi-v7a