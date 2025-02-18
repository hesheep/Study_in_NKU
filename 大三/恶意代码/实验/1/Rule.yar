private rule isPEFile
{
condition:
    filesize < 10MB and //这几个PE均小于10MB
    uint16(0) == 0x5A4D and //“MZ”头
    uint32(uint32(0x3C)) == 0x00004550 // “PE”头
}

//Lab01-01.exe
rule lab0101exe
{
    strings:
        $s1="kernel32.dll"
        $s2="FindFirstFile"
        $s3="FindNextFile"
        $s4="CopyFile"
        $s5="C:\\windows\\system32\\kerne132.dll"
        $s6="Lab01-01.dll"
    condition:
        isPEFile and $s1 and $s2 and $s3 and $s4 and $s5 and $s6
}


//Lab01-02.dll
rule lab0101dll
{
    strings:
        $s1="sleep"
        $s2="exec"
        $s3="CreateProcessA"
        $s4="127.26.152.13"
    condition:
        isPEFile and $s1 and $s2 and $s3 and $s4
}


//Lab01-02.exe
rule lab0102exe
{
    strings:
        $s1="MalService"
        $s2= {68 74 74 70 3A 2F 2F 77 FF B7 BF DD 00 2E 6D 1E 77 61 72 65 61 6E 07 79 73 69 73 62 6F 6F 6B 2E 63 6F FF DB DB 6F 6D}
        $s3="HGL345"
    condition:
        isPEFile and $s1 and $s2 and $s3
}

//Lab01-03.exe
rule lab0103exe
{
    strings:
        $s1 = "ole32.vd"
        $s2 = "OLEAUTLA"
        $s3 = "_getmas"
    condition:
        isPEFile and $s1 and $s2 and $s3
}

//Lab01-04.exe
rule lab0104exe
{
    strings:
        $s1="\\system32\\wupdmgrd.exe"
        $s2="http://www.practicalmalwareanalysis.com/updater.exe"
        $s3="LoadResource"
        $s4="FindResource"
        $s5="SizeofResource"
        $s6="CreateFile"
    condition:
        isPEFile and $s1 and $s2 and $s3 and $s4 and $s5 and $s6
}