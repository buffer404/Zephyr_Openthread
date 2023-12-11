list(APPEND ZEPHYR_EXTRA_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/../../lmtlib_light)
cmake_minimum_required(VERSION 3.20)

set(ENV{PROJECT_NAME} app-minimal)

# Выбор платы
set(ENV{BOARD} SOVA427)
# set(ENV{BOARD} SOIKA)

# zephyr/gnuarmemb/armclang или другое, см. https://docs.zephyrproject.org/latest/develop/toolchains/index.html
set(ZEPHYR_TOOLCHAIN_VARIANT zephyr)

# Поиск пакета zephyr, путь должен быть прописан в path
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project($ENV{PROJECT_NAME} LANGUAGES C VERSION 1.0.0)

# принудительная установкиа .conf файлов
# set(CONF_FILE debug.conf prj.conf conffile1.conf)

# Для подключения заголовочных файлов
include_directories(Inc)

# Подключение sources
file(GLOB_RECURSE SOURCES "src/*.*")

# должно быть app, а не PROJECT_NAME
target_sources(app PRIVATE ${SOURCES})
