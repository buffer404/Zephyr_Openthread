# Install script for directory: /home/mike/zephyr/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/mike/download/zephyr-sdk-0.16.3/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/acpica/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/altera/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_ambiq/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/atmel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_espressif/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_ethos_u/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_gigadevice/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_infineon/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_intel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/microchip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/nuvoton/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_nxp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/openisa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/quicklogic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_renesas/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_rpi_pico/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/silabs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/stm32/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_telink/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/ti/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/xtensa/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/tinycrypt/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/trusted-firmware-a/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/modules/lmtlib_light/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mike/zephyr/zephyr/zephyr_lmtltd_light/applications/cc-app-minimal/cmake-build-debug/zephyr/cmake/reports/cmake_install.cmake")
endif()

