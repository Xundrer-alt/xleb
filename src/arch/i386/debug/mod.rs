// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2026 Xundrer-alt
use core::fmt;
mod uart;
use self::uart::uart_putc;

pub(crate) struct UartWriter;
impl fmt::Write for UartWriter {
    fn write_str(&mut self, s: &str) -> fmt::Result {
        for &b in s.as_bytes() {
            uart_putc(b);
        }
        Ok(())
    }
}
pub(crate) fn print(args: fmt::Arguments) {
    use core::fmt::Write;
    let _ = UartWriter.write_fmt(args);
}

#[macro_export]
macro_rules! print {
    ($($arg:tt)*) => {{
        $crate::arch::i386::debug::print(format_args!($($arg)*));
    }};
}
#[macro_export]
macro_rules! println {
    () => {
        $crate::print!("\n");
    };
    ($($arg:tt)*) => {
        $crate::print!($($arg)*);
        $crate::print!("\n");
    };
}

#[macro_export]
macro_rules! debug {
    ($($arg:tt)*) => {
        $crate::print!("\x1b[36m[DEBUG] ({}:{}) \x1b[0m", file!(), line!());
        $crate::println!($($arg)*);
    };
}
#[macro_export]
macro_rules! info {
    ($($arg:tt)*) => {
        $crate::print!("\x1b[32m[INFO ] \x1b[0m");
        $crate::println!($($arg)*);
    };
}
#[macro_export]
macro_rules! warn {
    ($($arg:tt)*) => {
        $crate::print!("\x1b[33m[WARN ] \x1b[0m");
        $crate::println!($($arg)*);
    };
}
#[macro_export]
macro_rules! error {
    ($($arg:tt)*) => {
        $crate::print!("\x1b[31m[ERROR] \x1b[0m");
        $crate::println!($($arg)*);
    };
}
