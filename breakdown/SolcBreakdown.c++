// 0x6080604052 348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c80631afef78d14603457806367d41eca146048575b5f80fd5b5f5460405190815260200160405180910390f35b605760533660046059565b5f55565b005b5f602082840312156068575f80fd5b503591905056fea26469706673582212208482a9c1076c9296be7599809ce4e8a7391c19272b1dfb06cbe9bb9c2982867264736f6c634300081a0033

// This is where the free memeory pointter if we want to store anything in the memory the code will look where there is free memory with help of this code 
PUSH1 0x80
PUSH1 0x40
MSTORE

// This below chunk of code will tell if there is any msg.value sent while deployment which should revert an error
// Because no should be passed in the constructor
CALLVALUE       //[msg.value]
DUP1            //[msg.value, msg.value]
ISZERO          //[msg.value == 0, msg.value]
PUSH1 0x0e      //[0x0e, msg.value == 0, msg.value]
JUMPI           //[msg.value] Jump to jumpdest if there is no msg.value passed if yes then will follow below code and revert
PUSH0           //[0x00,msg.value]
DUP1            //[0x00, 0x00, msg.value]
REVERT          //[msg.value]
// Jumpdest if msg.value === 0
JUMPDEST        //[msg.value]
POP             //[]
PUSH1 0xa5      //[0xa5]
DUP1            //[0xa5, 0xa5]
PUSH1 0x1a      //[0x1a, 0xa5, 0xa5]
PUSH0           //[0x00, 0x1a, 0xa5, 0xa5] 0x1a-->the code above to ignore which coverted to decimal is 26 and  0xa5 is from number of opcode present in runtime which is 0xa5=126 in decimal viz from line 32 to the bottom
CODECOPY        //[0xa5]stack   Memory:[runtime code]
PUSH0           //[0x00, 0xa5]Stack     Memory:[runtime code]
RETURN          //[]  THIS retrun statement deploys the contract to onchain saying ok at 0x00 in memory there is runtime code present which is 126 dec or 0xa5 of opcodes
INVALID         //[]

//END OF CONTRACT CREATION CODE
// RUNTIME CODE
PUSH1 0x80      //[0x80]
PUSH1 0x40      //[0x40, 0x80]
MSTORE          //[]Stack Memory:[0x80]  this is where free memory pointer starts
// above code is free memory pointer


//What this is doing is checking if their is any function that is payable if not then it will revert with below
CALLVALUE       //[msg.value]
DUP1            //[msg.value, msg.value]
ISZERO          //[msg.value == 0, msg.value]
PUSH1 0x0e      //[0xe0, msg.value == 0, msg.value]
JUMPI           //[msg.value] if msg.value is zero jump to next jumpdest
PUSH0           //[0x00, msg.value] if msg.value != 0 than it this opcodes starts to execute
DUP1            //[0x00, 0x00, msg.value]
REVERT          //[msg.value]

//if msg.value === 0, Continue here
JUMPDEST        //[msg.value]
POP             //[]

// What below opcodes are doing is checking if the calldata size has minimum 4 bytes which is length of a function selector of it does even have that or not
PUSH1 0x04      //[0x04]
CALLDATASIZE    //[Calldata_Size, 0x04]  what ever data user has sent in calldata then it to size in bytes like 0x412434 is 3 bytes so 0x03 will be calldata size
LT              // if [Calldata_Size < 0x04]
PUSH1 0x30      //[0x30, Calldata_Size < 0x04]
JUMPI           //[]
// If calldata is less than Calldata_Size < 0x04 jump to jumpdest
// If calldata is greater than 4 bytes Calldata_Size > 0x04 then follow below code from 62 line

// Now here function dispatching starts from solidity
PUSH0           //[0x00]
CALLDATALOAD    //[32bytes of calldata is loaded which is sent by user]
PUSH1 0xe0      //[0xe0,32bytes of calldata]
SHR             //[calldata[0:4]]  this will only contain the function selector
DUP1            //[calldata[0:4],calldata[0:4]] OR we can write as [func_selector,func_selector]
PUSH4 0x1afef78d //[0x1afef78d,func_selector,func_selector]
EQ              //[0x1afef78d ==func_selector,func_selector]
PUSH1 0x34      //[0x34,0x1afef78d ==func_selector,func_selector]
JUMPI           //[func_selector]
// if func_selector = 0xcdfeade → updateNumberOfHorses function is called by jumpi 

//As solidity is doing again DUP1 so our function dispatcher in solidity is little bit more optimsed as we only do DUP1 once as we know that their are only two functions which i think solidity doesn't know
DUP1            //[func_selector,func_selector]
PUSH4 0x67d41eca //[0x67d41eca,func_selector,func_selector]
EQ              //[0x67d41eca == func_selector,func_selector]
PUSH1 0x48      //[0x48,0x67d41eca == func_selector,func_selector]
JUMPI           //[func_selector]
// if func_selector = 0x67d41eca → viewNumberOfHorses function is called by jumpi 
// And if function selector doesn't match the in both the cases of viewNumberOfHorses and updateNumberOfHorses viz      0x67d41eca , 0xcdfeade respectilvely than the code will continue below and give and error from line 86 to 89 

// But isn't the below revert reserved for if the it doesn't contain the function dispatcher 0x04 bytes at line 57  ????????????????

// If calldata is less than Calldata_Size < 0x04 then below code will revert
// revert Jumpdest
JUMPDEST        //[]
PUSH0           //[0x00]
DUP1            //[0x00, 0x00]
REVERT          //[]


JUMPDEST
PUSH0
SLOAD
PUSH1 0x40
MLOAD
SWAP1
DUP2
MSTORE
PUSH1 0x20
ADD
PUSH1 0x40
MLOAD
DUP1
SWAP2
SUB
SWAP1
RETURN

JUMPDEST
PUSH1 0x57
PUSH1 0x53
CALLDATASIZE
PUSH1 0x04
PUSH1 0x59
JUMP
JUMPDEST
PUSH0
SSTORE
JUMP
JUMPDEST
STOP
JUMPDEST
PUSH0
PUSH1 0x20
DUP3
DUP5
SUB
SLT
ISZERO
PUSH1 0x68
JUMPI
PUSH0
DUP1
REVERT
JUMPDEST
POP
CALLDATALOAD
SWAP2
SWAP1
POP
JUMP
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
DUP5
DUP3
INVALID
INVALID
SMOD
PUSH13 0x9296be7599809ce4e8a7391c19
INVALID
INVALID
SAR
INVALID
MOD
INVALID
INVALID
INVALID
SWAP13
INVALID
DUP3
DUP7
PUSH19 0x64736f6c634300081a0033