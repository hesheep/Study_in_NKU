import idautils
for func in idautils.Functions():
    dism_addr = list(idautils.FuncItems(func))
    for line in dism_addr:
        m = idc.GetMnem(line)
        if m == 'call':
            print '0x%x %s' % (line,idc.GetDisasm(line))