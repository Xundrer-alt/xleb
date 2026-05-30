use super::interrupt::irq;
use crate::arch::i386::regs::Regs;
use super::interrupt::pic;
use crate::info;
use core::sync::atomic::{AtomicU32, Ordering};

const TIMER_HZ: u32 = 100;
const PIT_BASE: u16 = 0x40;
const PIT_CMD: u16 = 0x43;
const PIT_FREQUENCY: u32 = 1193180;

static TICKS: AtomicU32 = AtomicU32::new(0);

pub fn init() {
    let divisor = PIT_FREQUENCY / TIMER_HZ;
    unsafe {
        pic::outb(PIT_CMD, 0x36);
        pic::outb(PIT_BASE, (divisor & 0xFF) as u8);
        pic::outb(PIT_BASE, ((divisor >> 8) & 0xFF) as u8);
    }
    irq::register_handler(0, timer_handler);
    info!("PIT timer: hello world");
}

pub fn ticks() -> u32 {
    TICKS.load(Ordering::Relaxed)
}

extern "C" fn timer_handler(_regs: &mut Regs) {
    let ticks = TICKS.fetch_add(1, Ordering::Relaxed);
    crate::debug!("Timer tick: {}", ticks);
}