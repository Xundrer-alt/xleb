{
  description = "Kernel Builder (unnamed yet)";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      system = "x86_64-linux";
      pkgs = nixpkgs.legacyPackages.${system};
      clang = pkgs.llvmPackages_20.clang-unwrapped;
      lld = pkgs.llvmPackages_20.lld;
      clang-tools = pkgs.llvmPackages_20.clang-tools;
    in {
      devShells.${system}.default = pkgs.mkShell {
        name = "rboxmgr-shell";
        buildInputs = [
          clang
          clang-tools
          lld
          pkgs.cmake
          pkgs.lldb
          pkgs.qemu
        ];

        shellHook = ''
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
                  -DCMAKE_C_FLAGS="$ARCH_FLAGS" \
                  -DCMAKE_ASM_COMPILER=clang \
                  -DCMAKE_ASM_FLAGS="$ARCH_FLAGS" \
                  -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld $ARCH_FLAGS" \
                  -DCMAKE_SYSTEM_NAME="Generic" \
                  -DCMAKE_SYSTEM_PROCESSOR="$1" \
                  -DARCH="$ARCH"
              make -j$(nproc)
              cd ..
          }
          bt() {
            b
            qemu-system-$ARCH -kernel build/kernel -serial stdio
          }
          bd() {
            b
            qemu-system-$ARCH -kernel build/kernel -serial stdio -s -S
          }
          cl() {
              rm -rf build*
              echo "Removed all build directories"
          }
          cbt() {
            cl
            bt
          }
          d() {
            lldb build/kernel -o "gdb-remote localhost:1234"
          }
          set_target i386
          echo "Available commands:"
          echo "  set_target i386"
          echo "  b - build kernel for current target"
          echo "  bt - build kernel + test with qemu"
          echo "  bd - build kernel + test with qemu (with options -s -S)"
          echo "  cl - delete all build directories"
          echo "  cbt - delete all build + build kernel + test with qemu"
          echo "  d - start lldb + connect to localhost:1234"
        '';
      };
    };
}
