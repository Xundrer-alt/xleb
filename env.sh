export PS1="\n\[\033[1;32m\][kernel] \[\033[0m\]\u@\h:\w\n\$ "
set_target() {
    case "$1" in
        i386)
            export TARGET="i686-unknown-linux-gnu"
            ;;
        *)
            echo "Unknown target. Supported: i386"
            return 1
            ;;
    esac
    export ARCH="$1"
}

b() {
    if [ -z "$TARGET" ]; then
        echo "Error: target not set. Use 'set_target <arch>' first."
        return 1
    fi
    cargo build --target $TARGET
}
br() {
    b
    qemu-system-$ARCH -kernel target/$TARGET/debug/xleb -serial stdio
}
bt() {
    if [ -z "$TARGET" ]; then
        echo "Error: target not set. Use 'set_target <arch>' first."
        return 1
    fi
    cargo build --target $TARGET
}
btr() {
    bt
    qemu-system-$ARCH -kernel target/$TARGET/debug/xleb -serial stdio
}
bd() {
    b
    qemu-system-$ARCH -kernel target/$TARGET/debug/xleb -serial stdio -s -S
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
release() {
    cl
    if [ -z "$TARGET" ]; then
        echo "Error: target not set. Use 'set_target <arch>' first."
        return 1
    fi
    cargo build --release --target $TARGET
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
echo "  release - build release kernel for current target"
echo "  NOTE: tests is not supported now because kernel is rewrited to Rust"