# import idautils
# ea=idc.ScreenEA()
# funcName=idc.GetFunctionName(ea)
# func=idaapi.get_func(ea)
# print("FuncName:%s"%funcName) # 获取函数名
# print "Start:0x%x,End:0x%x" % (func.startEA,func.endEA) # 获取函数开始地址和结束地址
# # 分析函数属性 
# flags = idc.GetFunctionFlags(ea)
# if flags&FUNC_NORET:
#      print "FUNC_NORET"
# if flags & FUNC_FAR:
#     print "FUNC_FAR"
# if flags & FUNC_STATIC:
#     print "FUNC_STATIC"
# if flags & FUNC_FRAME:
#     print "FUNC_FRAME"
# if flags & FUNC_USERFAR:
#     print "FUNC_USERFAR"
# if flags & FUNC_HIDDEN:
#     print "FUNC_HIDDEN"
# if flags & FUNC_THUNK:
#     print "FUNC_THUNK"
# if not(flags & FUNC_LIB or flags & FUNC_THUNK):# 获取当前函数中call或者jmp的指令
#     dism_addr = list(idautils.FuncItems(ea))
#     for line in dism_addr:
#         m = idc.GetMnem(line)
#         if m == "call" or m == "jmp":
#             print "0x%x %s" % (line,idc.GetDisasm(line))


import idautils
import idc
import idaapi
KNOWN_API_LIST = ["printf", "malloc", "free", "strcpy", "strlen", "exit"]  # 可根据需要扩展
call_graph = {}

def analyze_function(ea):
    """
    分析指定函数的函数调用关系
    """
    func_name = idc.get_func_name(ea)
    if not func_name:
        return

    if func_name in call_graph:
        # 避免重复分析
        return

    print(f"Analyzing function: {func_name}")
    call_graph[func_name] = []  # 初始化函数调用关系

    func = idaapi.get_func(ea)
    if not func:
        return

    # 遍历函数中的每一条指令
    for insn_ea in idautils.FuncItems(func.start_ea):
        mnem = idc.print_insn_mnem(insn_ea)
        if mnem == "call":
            # 获取调用的操作数
            opnd = idc.get_operand_type(insn_ea, 0)
            if opnd == idc.o_near:  # 直接调用
                callee_ea = idc.get_operand_value(insn_ea, 0)
                callee_name = idc.get_func_name(callee_ea)

                if not callee_name:
                    continue

                # 排除已知的标准库或系统调用
                if callee_name in KNOWN_API_LIST:
                    continue

                # 记录调用关系
                call_graph[func_name].append(callee_name)

                # 对被调用函数递归分析
                analyze_function(callee_ea)

def build_call_graph():
    """
    遍历所有函数，构建函数调用图
    """
    for ea in idautils.Functions():
        analyze_function(ea)

def print_call_graph():
    """
    打印函数调用图
    """
    print("\nFunction Call Graph:")
    for func, callees in call_graph.items():
        print(f"{func} -> {', '.join(callees) if callees else 'None'}")

if __name__ == "__main__":
    print("Building Function Call Graph...")
    build_call_graph()
    print_call_graph()
