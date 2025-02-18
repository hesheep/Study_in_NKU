private rule IsPE
{
    condition:
        filesize < 10MB and //小于10MB
        uint16(0) == 0x5A4D and //“MZ”头
        uint32(uint32(0x3C)) == 0x00004550 // “PE”头
}

rule lab0701exe
{
    strings:
        $s1 = "http://www.malwareanalysisbook.com"
        $s2 = "Internet Explorer 8.0"
        $s3 = "MalService"
    condition:
        IsPE and $s1 and $s2 and $s3
}

rule lab0702exe
{
    strings:
        $s1 = "http://www.malwareanalysisbook.com/ad.htm" wide ascii
    condition:
        IsPE and $s1
}

rule lab0703exe
{
    strings:
        $s1 = "kerne132.dll"
        $s2 = "C:\\Windows\\System32\\Kernel32.dll"
        $s3 = "C:\\*"
    condition:
        IsPE and $s1 and $s2 and $s3
}

rule lab0703dll
{
    strings:
        $s1 = "127.26.152.13"
        $s2 = "Sleep"
        $s3 = "exec"
    condition:
        IsPE and $s1 and $s2 and $s3
}

