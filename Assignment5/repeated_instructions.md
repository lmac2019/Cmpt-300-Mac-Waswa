### A list of common instructions copy/pasted a lot in Assignment 5


## Build linux

# Setup the default config file for building the kernel:
make defconfig

# Build the linux kernel (the number after j represents the number of cores your device has, run nproc on the terminal to find this):
make -j4 


## Launch QEMU
- Make sure linux has been built completely before executing the following
- Both instructions to launch QEMU require you to be in the linux-stable/ folder as the current directory

# Launch QEMU in the current terminal window:
qemu-system-x86_64 -m 64M -hda ../debian_squeeze_amd64_standard.qcow2 -append "root=/dev/sda1 console=tty0 console=ttyS0,115200n8" -kernel arch/x86_64/boot/bzImage -nographic

# Launch QEMU in its own terminal window
qemu-system-x86_64 -m 64M -hda ../debian_squeeze_amd64_standard.qcow2 -append "root=/dev/sda1 console=tty0 console=ttyS0,115200n8" -kernel arch/x86_64/boot/bzImage


## Power Off QEMU

poweroff