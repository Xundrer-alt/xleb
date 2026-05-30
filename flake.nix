{
  description = "Xleb Kernel Builder";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
    rust-overlay.url = "github:oxalica/rust-overlay";
  };

  outputs = { self, nixpkgs, flake-utils, rust-overlay }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        overlays = [ (import rust-overlay) ];
        pkgs = import nixpkgs {
          inherit system overlays;
        };
        clang = pkgs.llvmPackages_20.clang-unwrapped;
        lld = pkgs.llvmPackages_20.lld;
        clang-tools = pkgs.llvmPackages_20.clang-tools;
        rust-nightly = pkgs.rust-bin.selectLatestNightlyWith (toolchain: toolchain.minimal.override {
                extensions = [ "rust-src" "rust-analyzer" ];
                targets = [ "i686-unknown-linux-gnu" ];
              });
      in {
        devShells.default = pkgs.mkShell {
          name = "xleb-shell";
          buildInputs = with pkgs; [
            qemu
            rust-nightly
            cargo
          ];

          shellHook = ''
            export PS1="\n\[\033[1;32m\][xleb] \[\033[0m\]\u@\h:\w\n\$ "
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
                cargo build
            }
            br() {
              b
              qemu-system-$ARCH -kernel target/i686-unknown-linux-gnu/debug/xleb -serial stdio
            }
            bt() {
                if [ -z "$TARGET" ]; then
                    echo "Error: target not set. Use 'set_target <arch>' first."
                    return 1
                fi
                cargo build
            }
            btr() {
              bt
              qemu-system-$ARCH -kernel target/i686-unknown-linux-gnu/debug/xleb -serial stdio
            }
            bd() {
              b
              qemu-system-$ARCH -kernel target/i686-unknown-linux-gnu/debug/xleb -serial stdio -s -S
            }
            cl() {
              rm -rf target
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
            echo "  NOTE: tests is not supported now because kernel is rewrited to Rust"
          '';
        };
      }
    );
}