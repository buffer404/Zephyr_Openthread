
if(BOARD_SOVA427VI)
board_runner_args(jlink "--device=STM32F427VI" "--speed=200")
endif()

if(BOARD_SOVA407VG)
board_runner_args(jlink "--device=STM32F407VG" "--speed=200")
endif()

if(BOARD_SOVA407VE)
board_runner_args(jlink "--device=STM32F407VE" "--speed=200")
endif()

include(${ZEPHYR_BASE}/boards/common/openocd.board.cmake)
include(${ZEPHYR_BASE}/boards/common/jlink.board.cmake)
