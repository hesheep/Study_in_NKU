
private rule IsPE
{
 condition:
    filesize < 10MB and   
    uint16(0) == 0x5A4D and 
    uint32(uint32(0x3C)) == 0x00004550 
}

 //Lab14-01
 rule lab14_1
 {
    strings:
        $s1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" 
        $s2 = "http://www.practicalmalwareanalysis.com/%s/%c.png" 
    condition:
        IsPE and $s1 and $s2
 }
 //Lab14-02
 rule lab14_2
 {
    strings:
        $s1 = "WXYZlabcd3fghijko12e456789ABCDEFGHIJKL+/MNOPQRSTUVmn0pqrstuvwxyz" 
        $s2 = "/c del" 
        $s3 = "cmd.exe" 
    condition:
        IsPE and $s1 and $s2 and $s3
 }
 //Lab14-03
 rule lab14_3
 {
    strings:
        $s1 = "User-Agent: Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729)" 
        $s2 = "C:\\autobat.exe" 
    condition:
        IsPE and $s1 and $s2
 }