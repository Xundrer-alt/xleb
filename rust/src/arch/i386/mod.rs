use core::arch::asm;
use super::Arch;

pub struct I386Arch;
impl Arch for I386Arch {
    fn halt() -> ! {
        unsafe {
            loop {
                asm!("hlt", options(nomem, nostack, preserves_flags));
            }
        }
    }
}