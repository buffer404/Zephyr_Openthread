zephyr_library()

# if(CONFIG_NET_L2_ETHERNET)
    zephyr_library_sources(pins.c)
# endif()