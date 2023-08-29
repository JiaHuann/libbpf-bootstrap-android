# Libbpf-bootstrap for android
upstream: https://github.com/libbpf/libbpf-bootstrap

## prerare
- Android NDK

# feature
- libelf,libz on aarcj64 embedded.
- x86 -> android13(aarch64) cross-compile you can directly write ebpf both kernel-program and user-program on x86 machine.
- FlameGraph embedded.
- For None BTF/vmlinux android-kernel(CONFIG_DEBUG_INFO_BTF not set) support.
- adb debug (after compile&link directly push into android-phone) embedded.



