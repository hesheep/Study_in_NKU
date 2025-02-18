from sys import exit
from bitcoin.core.script import *

from utils import *
from config import my_private_key, my_public_key, my_address, faucet_address
from ex1 import send_from_P2PKH_transaction
from bitcoin.wallet import CBitcoinSecret


cust1_private_key = CBitcoinSecret(
    'cQVsk59yrstUic9KuT9CbnyGDUeHJjuqwxt1BmqH19huBnRtRPKT')
cust1_public_key = cust1_private_key.pub
cust2_private_key = CBitcoinSecret(
    'cNZsz6BNQxTqRfvUFoxEnCsHvVCkYKsx59uFomHJbZrBvWCMKQLC')
cust2_public_key = cust2_private_key.pub
cust3_private_key = CBitcoinSecret(
    'cU1JNcRBZf5Aa9hQDnYcS84zMHCmKAGnTNp1k8yQVPetCYSqT6Ri')
cust3_public_key = cust3_private_key.pub


######################################################################
# TODO: Complete the scriptPubKey implementation for Exercise 2

# You can assume the role of the bank for the purposes of this problem
# and use my_public_key and my_private_key in lieu of bank_public_key and
# bank_private_key.


ex2a_txout_scriptPubKey = [
    my_public_key,      # 银行的公钥
    OP_CHECKSIGVERIFY,
    OP_2,                # 需要两个签名
    cust1_public_key,    # 第一个客户的公钥
    cust2_public_key,    # 第二个客户的公钥
    cust3_public_key,    # 第三个客户的公钥
    OP_3,                # 总共三个公钥
    OP_CHECKMULTISIG     # 多重签名检查
]
######################################################################

if __name__ == '__main__':
    ######################################################################
    # TODO: set these parameters correctly
    amount_to_send = 0.00001
    txid_to_spend = (
        'e876a96965a3b816fb56f71b4f61c9fa038e4af35bfda3d9530f80f995b975cc')
    utxo_index = 2
    ######################################################################

    response = send_from_P2PKH_transaction(
        amount_to_send, txid_to_spend, utxo_index,
        ex2a_txout_scriptPubKey)
    print(response.status_code, response.reason)
    print(response.text)
