import string, base64
result = ""
tab = "XYZlabcd3fghijko12e456789ABCDEFGHIJKL+/MNOPQRSTUVmn0pqrstuvwxyz"
standardBase64 ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
text = "e6LJC+xnBq90daDNB+1TDrhG6aUG6p9LC/iNBqsGi2sVgJdqhZXDZoMMomKGoqxUE7"
for i in text:
    if i in tab:
        s += standardBase64[string.find (tab, str (ch))]
    elif i == '=':
        s += '='
print(base64.decodestring(a))