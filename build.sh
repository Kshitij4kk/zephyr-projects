cd $ZEPHYR_BASE
# In order for this script to work properly, the user needs to source $app to shell environment
west build -p auto -b qemu_x86 --build-dir $appl/build $appl 
