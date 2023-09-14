<<<<<<< HEAD
---
layout: post
title: libbpf-bootstrap-android
date: 2023-9-14 16:18
category: Framework
author: JiaHuann
tags: [Android, ebpf-framework, cross-compile]
summary: For amd64 aarch machine to directly using libbpf-bootstrap framwork to write ebpf programs both kernel and user space.And you don't need to have `CONFIG_BTF_DEBUG_INFO` support by using externel BTF file in BTFhubForAndroid instead.For this goal,I did some changes on libbpf-bootstrap,and have done some embedded features.Wish this can help you sth.Best regards. 
---

# Libbpf-bootstrap for android
> For amd64 aarch machine to directly using libbpf-bootstrap framwork to write ebpf programs both kernel and user space.And you don't need to have `CONFIG_BTF_DEBUG_INFO` support by using externel BTF file in BTFhubForAndroid instead.For this goal,I did some changes on libbpf-bootstrap,and have done some embedded features.Wish this can help you sth.Best regards. 
## upstream: 
- https://github.com/libbpf/libbpf-bootstrap
- https://github.com/SeeFlowerX/BTFHubForAndroid

## prerare
- Android NDK
- gcc-aarch64-linux-gnu
- Android phone with root and unlock BL

## usage
- deps
```shell
https://github.com/JiaHuann/libbpf-bootstrap-android
cd libbpf-bootstrap-android
sudo apt install gcc-aarch64-linux-gnu llvm clang 
wget https://dl.google.com/android/repository/android-ndk-r25c-linux.zip?hl=zh-cn android-ndk-r25c-linux.zip
unzip android-ndk-r25c-linux
```
- set NDK env to `$PATH`
```shell
vim ~/.bashrc
export your android-ndk-r25c/toolchains/llvm/prebuilt/linux-x86_64/bin to PATH
```

- compile and push to phone 
```
cd examples/c && make

adb devices
adb remount     # may fail, you can leave with issure.
adb push examples/c/btf_file/* example/c/your_executable_file /data/local/tmp
adb shell    #into android kernel shell
```
- in android shell
```shell
cd /data/local/tmp && chmod +x your_excutable_file
./run
Congratulations!
```


# feature
- libelf,libz on aarcj64 embedded.
- x86 -> android13(aarch64) cross-compile you can directly write ebpf both kernel-program and user-program on x86 machine.
- FlameGraph embedded to monitor performance.
- For None BTF/vmlinux android-kernel(CONFIG_DEBUG_INFO_BTF not set) support.
- adb debug (after compiling&linking, directly push into android-phone) embedded.

# RoadMap:
- change the static link to ShareLib.
- Measure the eBPF program's overhead by FlameGraph.
- Add more Android features into support.
- Test for lower Android version.



=======
# libbpf-bootstrap-android
>>>>>>> b0d37de (Initial commit)
