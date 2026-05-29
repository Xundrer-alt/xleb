#![no_std]

use core::panic::PanicInfo;
pub mod arch;
use crate::arch::Arch;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[unsafe(no_mangle)]
pub extern "C" fn halt() -> ! {
    arch::CurrentArch::halt()
}