first 4 bytes in an input data/calldata is function name and the input that we are providinig that' how it remix knows to call which function it's called the  signature (cast sig "updateNumberOfHorses(uint256)" gives -- > 0x67d41eca)

callData(it is input data in remix) --> Function dispatch (this is 0x67d41eca function dispatch) --> function is called



EVM is stack stores data --> this is cheapest place to store data on Evm

three places to store data on EVM stack, memory, storage

when we call calldata opcode then it pops off the 0x00 opcodeand replaces that with itself starting from 0 index
calldata == function name and input it is taking so the evm knows which function to call (example -- updateNumberOfHorses(uint256) will give 0x67d41eca)