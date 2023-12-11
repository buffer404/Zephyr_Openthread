#![no_std]
#![crate_type = "staticlib"]

#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}

#[no_mangle] pub extern fn public_function() -> i32 {
    let tuple = (0, 'c');
    return tuple.1 as i32;
}


#[no_mangle] pub extern fn iterator_example() -> i32 {
    let numbers = 0..;
    let five_numbers = numbers.take(5);
    let mut a = 0;
    for number in five_numbers {
        a = number
    }
    return a
}

#[no_mangle] pub extern fn hello_world() -> *const u8 {
    let s: &'static str = "Hello, World from rust!\0";
    return s.as_ptr()
}