pub trait Arch {
    fn halt() -> !;
}

#[cfg(target_arch = "x86")]
pub mod i386;
#[cfg(target_arch = "x86")]
pub use i386::I386Arch as CurrentArch;