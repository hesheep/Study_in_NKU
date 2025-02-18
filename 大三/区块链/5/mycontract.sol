// Please paste your contract's solidity code here
// Note that writing a contract here WILL NOT deploy it and allow you to access it from your client
// You should write and develop your contract in Remix and then, before submitting, copy and paste it here
// Please paste your contract's solidity code here
// Note that writing a contract here WILL NOT deploy it and allow you to access it from your client
// You should write and develop your contract in Remix and then, before submitting, copy and paste it here

pragma solidity >=0.4.0;

contract BlockchainSplitwise {
    struct Debt {
        uint32 amount;
    }
    mapping(address => mapping(address => Debt)) internal Debts;

    // 查询债务金额
    function lookup(address debtor, address creditor) public view returns (uint32 ret) {
        ret = Debts[debtor][creditor].amount;
    }

    // 添加欠条
    function add_IOU(address creditor, uint32 amount, address[] memory path, uint32 minamount) public {
        address debtor = msg.sender;
        
        require(creditor != debtor, "Debtor and Creditor cannot be the same person!");

        require(amount > 0, "amount must be greater than 0 !");

        require(creditor == path[0] && debtor == path[path.length - 1], "The path is wrong!");

        Debt storage debt = Debts[debtor][creditor];

        // 如果没有路径调整，只需增加金额
        if (minamount == 0) {
            debt.amount += amount;
            return;
        }

        // 检查最低金额是否满足条件
        require((debt.amount + amount) >= minamount, "The amount cannot be smaller than minamount!");

        uint32 minAmount = minamount;  // 初始最小金额为 minamount

        // 计算路径上的债务金额，减少每个路径上金额
        for (uint256 i = 0; i < path.length - 1; i++) {
            address currentCreditor = path[i];
            address nextCreditor = path[i + 1];
            Debt storage intermediateDebt = Debts[currentCreditor][nextCreditor];
            require(intermediateDebt.amount >= minamount, "The debt does not enough to deduct the minamount!");
            intermediateDebt.amount -= minAmount;
        }
        debt.amount += amount - minAmount;
    }
}
