from idaapi import *
from idautils import *
from idc import *

def is_simple_jump(func_start, func_end):

    if func_end - func_start <= 5:  
        if GetMnem(func_start) == "jmp":
            return True
    return False

def is_library_function(func_ea):

    flags = GetFunctionFlags(func_ea)
    return flags & FUNC_LIB != 0

def is_register_operand(ea, op_num):

    return GetOpType(ea, op_num) == o_reg

def process_function(func_ea):

    func = get_func(func_ea)
    if not func:
        return
    
    func_start = func.start_ea
    func_end = func.end_ea
    

    if is_library_function(func_start) or is_simple_jump(func_start, func_end):
        return
    
    ea = func_start
    while ea < func_end:
        mnem = GetMnem(ea)
        if mnem in ("call", "jmp"):
            if is_register_operand(ea, 0):  
                print("%X: %s" % (ea, GetDisasm(ea)))
        ea = NextHead(ea, func_end)

for func_ea in Functions():
    process_function(func_ea)
