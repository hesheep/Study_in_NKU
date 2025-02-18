private rule IsPE
{
    condition:
        filesize < 10MB and    
        uint16(0) == 0x5A4D and 
        uint32(uint32(0x3C)) == 0x00004550 
}
//Lab13-01
rule lab13_1
{
    strings:
        $s1 = "Mozilla/4.0" 
        $s2 = "http://%s/%s/" 
        $s3 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" 
        $s4 = "CloseHandle"
    condition:
        IsPE and $s1 and $s2 and $s3 and $s4
}
//Lab13-02
rule lab13_2
{
    strings:
        $s1 = "temp%08x" 
        $s2 = "GetACP" 
        $s3 = "GetDC" 
        $s4 = "MultiByteToWideChar"
    condition:
        IsPE and $s1 and $s2 and $s3 and $s4
}
//Lab13-03
rule lab13_3
{
    strings:
        $s1 = "CDEFGHIJKLMNOPQRSTUVWXYZABcdefghijklmnopqrstuvwxyzab0123456789+/" 
        $s2 = "cmd.exe" 
        $s3 = "WriteConsole"
    condition:
        IsPE and $s1 and $s2 and $s3
}