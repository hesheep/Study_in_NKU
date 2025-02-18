// =============================================================================
//                                  Config
// =============================================================================

// 设置 Web3.js 实例
if (typeof web3 !== 'undefined') {
    web3 = new Web3(web3.currentProvider);
    //console.log('Web3 is initialized with Metamask provider');
} else {
    web3 = new Web3(new Web3.providers.HttpProvider("http://localhost:8545"));
    //console.log('Web3 is initialized with HTTP provider');
}
// console.log(window.web3);
// console.log(Web3.version); // 仅适用于旧版 Web3.js（例如 0.x）
// console.log(window.web3.version); // 仅适用于旧版 Web3.js（例如 0.x）
// console.log(window.web3.currentProvider); // 查看 provider，确认它被正确设置



// 默认账户是第一个账户
web3.eth.defaultAccount = web3.eth.accounts[0];

// 常量：Genesis 区块的哈希值，用于确定区块链的起始点
var GENESIS = '0x0000000000000000000000000000000000000000000000000000000000000000';

// 这里填写智能合约的 ABI（从 Remix 获取，'Compile' 选项卡）
var abi =
[
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "creditor",
				"type": "address"
			},
			{
				"internalType": "uint32",
				"name": "amount",
				"type": "uint32"
			},
			{
				"internalType": "address[]",
				"name": "path",
				"type": "address[]"
			},
			{
				"internalType": "uint32",
				"name": "minamount",
				"type": "uint32"
			}
		],
		"name": "add_IOU",
		"outputs": [],
		"stateMutability": "nonpayable",
		"type": "function"
	},
	{
		"inputs": [
			{
				"internalType": "address",
				"name": "debtor",
				"type": "address"
			},
			{
				"internalType": "address",
				"name": "creditor",
				"type": "address"
			}
		],
		"name": "lookup",
		"outputs": [
			{
				"internalType": "uint32",
				"name": "ret",
				"type": "uint32"
			}
		],
		"stateMutability": "view",
		"type": "function"
	}
];
// 使用 abiDecoder 添加 ABI 以解析合约调用数据
abiDecoder.addABI(abi);

// 创建合约实例
var BlockchainSplitwiseContractSpec = web3.eth.contract(abi);

// 合约地址（从 Remix 获取）
var contractAddress = '0x4c7cF29B7Cc23933C14422e9EC0C80943787a72F'; // FIXME: 用合约地址替换

// 初始化合约对象
var BlockchainSplitwise = BlockchainSplitwiseContractSpec.at(contractAddress);


// =============================================================================
//                            Functions To Implement
// =============================================================================

// 获取数据（例如从合约调用的所有数据）
function getAllData(dataExtractor, condition) {
    const Calls = getAllFunctionCalls(contractAddress, 'add_IOU', condition);
    const Result = Calls.map(Call => dataExtractor(Call)).flat();
    return Array.from(new Set(Result));
}

// 获取所有债权人
function getCreditors(user) {
    const Creditors = getAllData(Call => [Call.args?.[0].toLowerCase()], null);
    return Creditors.filter(creditor => BlockchainSplitwise.lookup(user, creditor).toNumber() > 0);
}

// 返回所有用户（曾发送或接收欠条的人）
function getUsers() {
    return getAllData(Call => [Call.from.toLowerCase(), Call.args?.[0].toLowerCase()], null);
}

// 获取用户所欠的总金额
function getTotalOwed(user) {
    const Creditors = getAllData(Call => [Call.args?.[0].toLowerCase()], null);
    let totalOwed = 0;
    
    Creditors.forEach(creditor => {
        totalOwed += BlockchainSplitwise.lookup(user, creditor).toNumber();
    });
    return totalOwed;
}
// function getTotalOwed(user) {
//     const Creditors = getAllData(Call => [Call.args?.[0].toLowerCase()], null);
//     let totalOwed = 0;
    
//     Creditors.forEach(creditor => {
//         const amount = BlockchainSplitwise.lookup(user, creditor);
        
//         // 判断是否是 BigNumber 类型
//         if (BigNumber.isBigNumber(amount)) {
//             totalOwed += amount.toNumber(); // 使用 .toNumber() 转换
//         } else {
//             totalOwed += amount; // 直接加数字
//         }
//     });

//     return totalOwed;
// }


// 获取用户的最后活动时间戳
function getLastActive(user) {
    const timeStamp = getAllData(Call => (Call.from.toLowerCase() === user.toLowerCase() || Call.args?.[0].toLowerCase() === user.toLowerCase()) ? [Call.timestamp] : [], 
                              Call => Call.from.toLowerCase() === user.toLowerCase() || Call.args?.[0].toLowerCase() === user.toLowerCase());
    
    return timeStamp.length ? Math.max(...timeStamp) : null;
}

// 向系统中添加一个 IOU（欠条）
function add_IOU(creditor, amount) {
    const debtor = web3.eth.defaultAccount; // 获取当前账户作为债务人

    // 确保债务人不能是债权人
    if (debtor === creditor) {
        alert("Debtor and Creditor cannot be the same person!");
        return;
    }

    // 确保金额合法
    const parsedAmount = parseInt(amount, 10);
    if (isNaN(parsedAmount) || parsedAmount <= 0) {
        alert("Amount must be a positive number!");
        return;
    }

    // 查找路径（如果存在循环）
    const path = doBFS(creditor, debtor, getCreditors);

    if (path) {
        let minDebt = Infinity;
        
        // 在客户端计算最小债务金额，而不依赖合约进行计算
        for (let i = 1; i < path.length; i++) {
            const debt = BlockchainSplitwise.lookup(path[i - 1], path[i]).toNumber();
            minDebt = Math.min(minDebt, debt);
        }

        // 最终的债务金额为路径中的最小债务金额与传入的金额的最小值
        const finalDebt = Math.min(minDebt, parsedAmount);
        // 只在需要的时候调用合约方法，避免不必要的合约调用
        return BlockchainSplitwise.add_IOU(creditor, parsedAmount, path, finalDebt);
    }

    // 如果没有路径，直接调用合约方法，传递空路径和最小金额为0
    return BlockchainSplitwise.add_IOU(creditor, parsedAmount, [], 0);
}


// =============================================================================
//                              Provided Functions
// =============================================================================

// 从区块链历史中查找所有调用特定合约方法的交易
function getAllFunctionCalls(addressOfContract, functionName, earlyStopFn) {
    let curBlock = web3.eth.blockNumber; // 当前区块高度
    let function_calls = []; // 存储调用记录

    while (curBlock !== GENESIS) {
        let b = web3.eth.getBlock(curBlock, true); // 获取区块数据
        let txns = b.transactions; // 获取区块中的所有交易

        for (let j = 0; j < txns.length; j++) {
            let txn = txns[j];
            if (txn.to === addressOfContract.toLowerCase()) {
                let func_call = abiDecoder.decodeMethod(txn.input); // 解码交易输入数据
                if (func_call && func_call.name === functionName) {
                    let args = func_call.params.map(function (x) { return x.value });
                    function_calls.push({ from: txn.from, args: args, timestamp: b.timestamp });

                    // 如果满足停止条件，提前返回
                    if (earlyStopFn && earlyStopFn(function_calls[function_calls.length - 1])) {
                        return function_calls;
                    }
                }
            }
        }
        curBlock = b.parentHash; // 继续往前查找区块
    }
    return function_calls;
}

// 广度优先搜索 (BFS)，用于查找从 start 到 end 的路径
function doBFS(start, end, getNeighbors) {
    let queue = [[start]];
    while (queue.length > 0) {
        let cur = queue.shift(); // 取出队列中的第一个路径
        let lastNode = cur[cur.length - 1];
        if (lastNode === end) {
            return cur;
        }
        else {
            let neighbors = getNeighbors(lastNode); // 获取邻居节点
            for (let i = 0; i < neighbors.length; i++) {
                queue.push(cur.concat([neighbors[i]])); // 扩展路径
            }
        }
    }
    return null; // 如果没有找到路径，返回 null
}


// =============================================================================
//                                      UI
// =============================================================================

// 更新 'My Account' 页面上的 UI
$("#total_owed").html("$" + getTotalOwed(web3.eth.defaultAccount));
$("#last_active").html(timeConverter(getLastActive(web3.eth.defaultAccount)));

// 账户切换时更新 UI
$("#myaccount").change(function () {
    web3.eth.defaultAccount = $(this).val();
    $("#total_owed").html("$" + getTotalOwed(web3.eth.defaultAccount));
    $("#last_active").html(timeConverter(getLastActive(web3.eth.defaultAccount)));
});

// 列出所有以太坊账户
let opts = web3.eth.accounts.map(function (a) { return '<option value="' + a + '">' + a + '</option>' });
$(".account").html(opts);
$(".wallet_addresses").html(web3.eth.accounts.map(function (a) { return '<li>' + a + '</li>' }));

// 更新 UI 中所有用户的列表
$("#all_users").html(getUsers().map(function (u, i) { return "<li>" + u + "</li>" }));

// 点击按钮时执行 add_IOU 函数
$("#addiou").click(function () {
    add_IOU($("#creditor").val(), $("#amount").val());
    window.location.reload(false); // 刷新页面
});

// 提供日志输出函数，可以将信息输出到页面而不是控制台
function log(description, obj) {
    $("#log").html($("#log").html() + description + ": " + JSON.stringify(obj, null, 2) + "\n\n");
}
