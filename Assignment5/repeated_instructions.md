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


# Launch QEMU and redirect port 8888 on the host OS to the QEMU VM's port 22
qemu-system-x86_64 -m 64M -hda ../debian_squeeze_amd64_standard.qcow2 -append "root=/dev/sda1 console=tty0 console=ttyS0,115200n8" -kernel arch/x86_64/boot/bzImage -nographic -net user,hostfwd=tcp::8888-:22 -net nic


## Copy your file (helloWorld, for example) to the QEMU virtual machine via SCP 
scp -P 8888 helloWorld root@localhost:~


## Copy multiple files (helloWorld, myApp, fooFile2, for example) to the QEMU virtual machine via SCP
scp -P 8888 helloWorld myApp fooFile2 root@localhost:~


## SSH from host into guest VM
# Make sure QEMU is running and you are logged in
ssh root@localhost -p8888


## Power Off QEMU
poweroff


## Adding a syscall
Create a folder in the linux-stable directory
Create a .c file in this folder
Add the system call content in the .c file
Create a Makefile
Add obj-y := name_of_file.o [dependency_file.o dependency_file_2.o] to the Makefile
Edit the Makefile in the linux-stable folder to include the new folder (about line 993):
    ifeq ($(KBUILD_EXTMOD),)
    core-y += kernel/ mm/ fs/ ipc/ security/ crypto/ block/ new_folder/
Add a syscall entry to the file in linux-stable at the path arch/x86/entry/syscalls/syscall_64.tbl as follows:
    340 common cs300_test sys_cs300_test