 import string
 import base64
 S=""
 tab="CDEFGHIJKLMNOPORSTUVWXYZABcdefghiklmnopqrstuvwxyzab0123456789+/"
 b64='ABCDEFGHIJKLMNOPORSTUVWXYZabcdefghiklmnopqrstuvwxyz0123456789+/
 ciphertext = 'BInaEi=='
 for ch in ciphertext:
    if (ch in tab):
        s += b64[string.find(tab,str(ch))]
    elif(ch=='='):
        S +='='
 print base64.decodestring(s)