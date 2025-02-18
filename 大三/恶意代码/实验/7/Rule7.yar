private rule IsPE
 {
    condition:
        filesize < 10MB and    
        uint16(0) == 0x5A4D and 
        uint32(uint32(0x3C)) == 0x00004550 
}
 //Lab11-01
 rule lab11_1
 {
    strings:
         $s1 = "msgina32.dll" 
    condition:
         IsPE and $s1
 }
 //Lab11-02
 rule lab11_2
 {
     strings:
        $s1 = "AppInit_DLLs" 
        $s2 = "OUTLOOK.EXE" 
        $s3 = "MSIMN.EXE" 
    condition:
         IsPE and $s1 and $s2 and $s3
 }
//Lab11-03
 rule lab11_3_exe
 {
    strings:
        $s1 = "net start cisvc" 
        $s2 = "C:\\WINDOWS\\System32\\inet_epar32.dll" 
    condition:
        IsPE and $s1 and $s2
 }
//Lab11-03
 rule lab11_3_dll
 {
    strings:
        $s1 = "C:\\WINDOWS\\System32\\kernel64x.dll" 
        $s2 = "zzz69806582" 
    condition:
        IsPE and $s1 and $s2
 }