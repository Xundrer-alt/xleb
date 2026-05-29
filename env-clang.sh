export PS1="\n\[\033[1;32m\][kernel] \[\033[0m\]\u@\h:\w\n\$ "
set_target() {
    case "$1" in
        i386)
            export TARGET="i386-unknown-none"
            export ARCH_FLAGS="--target=$TARGET -march=i386 -mno-sse -mno-mmx"
            ;;
        *)
            echo "Unknown target. Supported: i386"
            return 1
            ;;
    esac
    export ARCH="$1"
    export CFLAGS="$ARCH_FLAGS -ffreestanding -nostdlib -Wno-unused-command-line-argument"
    export LDFLAGS="-fuse-ld=lld $ARCH_FLAGS -nostdlib"
}

b() {
    if [ -z "$TARGET" ]; then
        echo "Error: target not set. Use 'set_target <arch>' first."
        return 1
    fi
    mkdir -p build
    cd build
    cmake .. \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_C_FLAGS="$CFLAGS" \
        -DCMAKE_ASM_COMPILER=clang \
        -DCMAKE_ASM_FLAGS="$CFLAGS" \
        -DCMAKE_EXE_LINKER_FLAGS="$LDFLAGS" \
        -DCMAKE_SYSTEM_NAME="Generic" \
        -DARCH="$ARCH"
    make -j$(nproc)
    cd ..
}
br() {
    b
    qemu-system-$ARCH -kernel build/kernel -serial stdio
}
bt() {
    if [ -z "$TARGET" ]; then
        echo "Error: target not set. Use 'set_target <arch>' first."
        return 1
    fi
    mkdir -p build
    cd build
    cmake .. \
        -DCMAKE_C_COMPILER=clang \
        -DCMAKE_C_FLAGS="$CFLAGS" \
        -DCMAKE_ASM_COMPILER=clang \
        -DCMAKE_ASM_FLAGS="$CFLAGS" \
        -DCMAKE_EXE_LINKER_FLAGS="$LDFLAGS" \
        -DCMAKE_SYSTEM_NAME="Generic" \
        -DARCH="$ARCH" \
        -DENABLE_TESTS=ON
    make -j$(nproc)
    cd ..
}
btr() {
    bt
    qemu-system-$ARCH -kernel build/kernel -serial stdio
}
bd() {
    b
    qemu-system-$ARCH -kernel build/kernel -serial stdio -s -S
}
cl() {
    rm -rf build* rust/target
    echo "Removed all build directories"
}
cbr() {
    cl
    br
}
cbtr() {
    cl
    btr
}
d() {
    lldb build/kernel -o "gdb-remote localhost:1234"
}
set_target i386
echo "Available commands:"
echo "  set_target i386"
echo "  b - build kernel for current target"
echo "  br - build kernel + run with qemu"
echo "  bt - build tests for current target"
echo "  btr - build tests + run with qemu"
echo "  bd - build kernel + run with qemu (with options -s -S)"
echo "  cl - delete all build directories"
echo "  cbr - delete all build + build kernel + run with qemu"
echo "  cbtr - delete all build + build tests + run with qemu"
echo "  d - start lldb + connect to localhost:1234"