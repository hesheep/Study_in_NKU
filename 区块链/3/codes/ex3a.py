from sys import exit
from bitcoin.core.script import *

from utils import *
from config import my_private_key, my_public_key, my_address, faucet_address
from ex1 import send_from_P2PKH_transaction


######################################################################
# TODO: Complete the scriptPubKey implementation for Exercise 3
ex3a_txout_scriptPubKey = [
    OP_2DUP,
    OP_ADD,
    2213,
    OP_EQUALVERIFY,
    OP_SUB,
    599,
    OP_EQUAL
]
######################################################################

if __name__ == '__main__':
    ######################################################################
    # TODO: set these parameters correctly
    amount_to_send = 0.000001 
    txid_to_spend = (
        '7ed1931848a84f35ff2ecddae8785cf1f6fcb2441fe460b697bc62baf3a476b5')
    utxo_index = 0
    ######################################################################

    response = send_from_P2PKH_transaction(
        amount_to_send, txid_to_spend, utxo_index,
        ex3a_txout_scriptPubKey)
    print(response.status_code, response.reason)
    print(response.text)
