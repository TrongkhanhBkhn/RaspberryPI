
enum device_types {
	DEVICE_NULL,
	DEVICE_LED,
	DEVICE_MONITOR,
	DEVICE_SDCARD,
	DEVICE_CLOCKS,
	/* add new ones here */
	DEVICE_MAX
};

enum syscalls_dev {
	DEVCALL_NULL,
	DEVCALL_READ,
	DEVCALL_WRITE,
	/* add new ones here */
	DEVCALL_MAX
};

enum syscalls_nondev {
	SYSCALL_NULL,
	SYSCALL_NEWPROC,
	SYSCALL_NEWTHREAD,
	/* add new ones here */
	SYSCALL_MAX
};

