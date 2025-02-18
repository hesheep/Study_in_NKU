private rule isPEFile
{
condition:
    filesize < 10MB and //这几个PE均小于10MB
    uint16(0) == 0x5A4D and //“MZ”头
    uint32(uint32(0x3C)) == 0x00004550 // “PE”头
}

//Lab03-01.exe
rule Lab03_01
{
    strings:
        $s1= "kernel32.dll"
        $s2="ExitProcess"
        $s3="WinVMX32-"
        $s4="vmx32to64.exe"
    condition:
        isPEFile and $s1 and $s2 and $s3 and $s4

}

//Lab03-02.dll
rule Lab03_02
{
    strings:
        $s4="IPRIP"
        $s5="svchost.exe"
        
    condition:
        isPEFile and $s4 and $s5 
}

//Lab03-03.exe
rule Lab03_03
{
    strings:
        $s1="svchost.exe"
        $s2="Sleep"
        $s3="ntdll.dll"
    condition:
        isPEFile and $s1 and $s2 and $s3
}

//Lab03-04.exe
rule Lab03_04
{
    strings:
        $s1="CreateServiceA"
        $s2="RegSetValueExA"
        $s3="DOWNLOAD"
        $s4="UPLOAD"
        $s5="HTTP/1.0"
        $s6="cmd.exe"
        $s7=" >> NUL"
    condition:
        isPEFile and $s1 and $s2 and $s3 
        and $s4 and $s5 and $s6 and $s7
}
