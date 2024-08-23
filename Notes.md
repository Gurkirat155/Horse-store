first 4 bytes in an input data/calldata is function name and the input that we are providinig that' how it remix knows to call which function it's called the  signature (cast sig "updateNumberOfHorses(uint256)" gives -- > 0x67d41eca)

callData(it is input data in remix) --> Function dispatch (this is 0x67d41eca function dispatch) --> function is called



EVM is stack stores data --> this is cheapest place to store data on Evm

three places to store data on EVM stack, memory, storage

when we call calldata opcode then it pops off the 0x00 opcode and replaces that with itself starting from 0 index
calldata == function name and input it is taking so the evm knows which function to call (example -- updateNumberOfHorses(uint256) will give 0x67d41eca)


Anytime we need to do a operation we need to stick to the stack in evm

cast --to-base 0xF102 dec == 61698


CALLDATALOAD can only take place 32 bytes of calldata onto the stack

0x01(hex) = 1 byte =  1 bits
0x0102 = 2 bytes = 0b 1 00000010 ==> 1 -- 0x01(cast --to-base 0x01 bin) and 00000010 -- 0x02 

1 byte = 8 bits

Main data structure we are wokring in ethereum is stack, 


For running particular file in below case it's huff and debug a particular function 
forge test --match-path ./test/testV1/HorseStoreHuff.t.sol --debug  testUpdateHorses