private rule isPEFile
{
condition:
    filesize < 10MB and //这几个PE均小于10MB
    uint16(0) == 0x5A4D and //“MZ”头
    uint32(uint32(0x3C)) == 0x00004550 // “PE”头
}
rule Lab05
{
    strings:
        $s1= "socket() GetLastError reports %d"
        $s2 = "WSAStartup() error: %d"
        $s3 = "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0"
        $s4 = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion"
        $s5 = "xkey.dll"
    condition:
        isPEFile and $s1 and $s2 and $s3 and $s4 and $s5
}