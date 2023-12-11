# zephyr_rust

Пример приложения использующего код на языке Rust.

* Для запуска приложения необходимо установить и настроить cmake модуль (corrosion)[https://github.com/corrosion-rs/corrosion]
* Для генирации зголовочного файла используется [cbindgen](https://github.com/eqrion/cbindgen)
* в rustc должна быть установлен соответствующий target (cortex m4/m7 - *thumbv7m-none-eabi* или *thumbv7em-none-eabihf*)

## Как работает

* Код на языке Rust компилируется в статическую библиотеку и подключается к основной программе Zephyr
* Компиляцией rust занимается компилятор rustc для соответствующей target
* Для генерации заголовков требуется вызвать команду

```bash
cbindgen --config cbindgen.toml --crate rlib --output rust_header.h --lang c
```

* Далее требуется подключить заголовочный файл в код на Си 

```C
#include "rust_header.h"
```

* Дальнейшая сборка происходит через

```bash
west build -- -DRust_CARGO_TARGET=thumbv7m-none-eabi
```

## Проблемы

* Недоступна stdlib языка rust, т.к. thumbv7m-none-eabi её не поддерживает. Соответственно, остается только core lib с малым функционалом

## TODO

* сделать установку target для corrison, чтобы избавиться от -- -DRust_CARGO_TARGET=thumbv7m-none-eabi