private rule IsPE
{
    condition:
        filesize < 10MB and   
        uint16(0) == 0x5A4D and 
        uint32(uint32(0x3C)) == 0x00004550 
}
rule lab12_1_exe
{
    strings:
        $s1 = "Lab12-01.dll" 
        $s2 = "GetModuleBaseNameA" 
        $s3 = "psapi.dll" 
    condition:
        IsPE and $s1 and $s2 and $s3
}
rule lab12_1_dll
{
    strings:
        $s1 = "Practical Malware Analysis %d" 
        $s2 = "Press OK to reboot" 
    condition:
        IsPE and $s1 and $s2
}
rule lab12_2
{
    strings:
        $s1 = "\svchost.exe" 
        $s2 = "AAAqAAApAAAsAAArAAAuAAAtAAAwAAAvAAAyAAAxAA" 
        $s3 = "spoolvxx32.dll"
    condition:
        IsPE and $s1 and $s2 and $s3
}
rule lab12_3
{
    strings:
        $s1 = "praticalmalwarenanlysis.log" 
        $s2 = "[CAPS LOCK]" 
        $s3 = "[ENTER]" 
        $s4 = "VirtualAlloc"
    condition:
        IsPE and $s1 and $s2 and $s3 and $s4
}
rule lab12_4
    {
    strings:
        $s1 = "winlogon.exe" 
        $s2 = "\system32\wupdmgrd.exe" 
        $s3 = "\winup.exe" 
        $s4 = "<SHIFT>"
    condition:
        IsPE and $s1 and $s2 and $s3 and $s4
}

