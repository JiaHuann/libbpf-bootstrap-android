# Libbpf-bootstrap for android
upstream: 
- https://github.com/libbpf/libbpf-bootstrap
- https://github.com/SeeFlowerX/BTFHubForAndroid

## prerare
- Android NDK

## usage
cd examples/c && make
adb push examples/c/btf_file/* /data/local/tmp

# feature
- libelf,libz on aarcj64 embedded.
- x86 -> android13(aarch64) cross-compile you can directly write ebpf both kernel-program and user-program on x86 machine.
- FlameGraph embedded.
- For None BTF/vmlinux android-kernel(CONFIG_DEBUG_INFO_BTF not set) support.
- adb debug (after compiling&linking, directly push into android-phone) embedded.



