# Libbpf-bootstrap for android
upstream: 
- https://github.com/libbpf/libbpf-bootstrap
- https://github.com/SeeFlowerX/BTFHubForAndroid

## prerare
- Android NDK

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
adb push examples/c/btf_file/* example/c/your_executable_file /data/local/tmp
```


# feature
- libelf,libz on aarcj64 embedded.
- x86 -> android13(aarch64) cross-compile you can directly write ebpf both kernel-program and user-program on x86 machine.
- FlameGraph embedded to monitor performance.
- For None BTF/vmlinux android-kernel(CONFIG_DEBUG_INFO_BTF not set) support.
- adb debug (after compiling&linking, directly push into android-phone) embedded.



