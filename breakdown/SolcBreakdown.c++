// 0x6080604052 348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c80631afef78d14603457806367d41eca146048575b5f80fd5b5f5460405190815260200160405180910390f35b605760533660046059565b5f55565b005b5f602082840312156068575f80fd5b503591905056fea26469706673582212208482a9c1076c9296be7599809ce4e8a7391c19272b1dfb06cbe9bb9c2982867264736f6c634300081a0033
// (↑, ↓, ←, →).
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

// FUNCTION DISPATCHER FOR UPDATING THE NUMBER OF HORSES STARTS HERE
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

// FUNCTION DISPATCHER FOR READING NUMBER OF HORSES STARTS HERE
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

// This is the jump destination for reading number of horses 
JUMPDEST        //[func_selector]
PUSH0           //[0x00, func_selector]     It means sload will check the value at 0 index because number of horses are stored in their
SLOAD           //[num_Of_Horses, func_selector]     It will load value of horses stores at 0 index
PUSH1 0x40      //[0x40, num_Of_Horses, func_selector] 
MLOAD           //[0x80, num_Of_Horses, func_selector]   Memory at 0x40 is pointer to [0x80]   
SWAP1           //[num_Of_Horses, 0x80, func_selector]
DUP2            //[0x80, num_Of_Horses, 0x80, func_selector]
MSTORE          //[0x80, func_selector]      Memory at index 0x80:[num_Of_Horses] is stored 0x80:[num_Of_Horses]
// Now we need to update free memory pointer to next index because our space is full at 0x80 so now 0x40 should point at next free memory index
PUSH1 0x20      //Stack:[0x20, 0x80, func_selector]     Memory:0x80:[num_Of_Horses]
ADD             //Stack:[0xa, func_selector]     Memory:0x80:[num_Of_Horses]    0x20 + 0x80 = 0xa0  viz 32 + 128 = 160 bytes 160 bytes = 0xa0
PUSH1 0x40      //Stack:[0x40, 0xa, func_selector]     Memory:0x80:[num_Of_Horses] 
MLOAD           //Stack:[0x80, 0xa, func_selector]     Memory:0x80:[num_Of_Horses] 
DUP1            //Stack:[0x80, 0x80, 0xa, func_selector]     Memory:0x80:[num_Of_Horses] 
SWAP2           //Stack:[0xa0, 0x80, 0x80, func_selector]     Memory:0x80:[num_Of_Horses] 
SUB             //Stack:[0xa0 - 0x80, func_selector]     Memory:0x80:[num_Of_Horses]      0xa0 - 0x80 = 0x20 or 32 bytes
SWAP1           //Stack:[0x80, 0x20, func_selector]     Memory:0x80:[num_Of_Horses]
// Return a value of size 32 bytes, that's located at position 0x80 in memory
RETURN          //Stack:[0x80, 0x20, func_selector]     Memory:0x80:[num_Of_Horses] will return the value in memory and stop execeution of code 

// Setup jumping program counters in the stack 
JUMPDEST        //[func_selector]
PUSH1 0x57      //[0x57, func_selector]
PUSH1 0x53      //[0x53, 0x57, func_selector]
CALLDATASIZE    //[call_data_size, 0x53, 0x57, func_selector]
PUSH1 0x04      //[0x04, call_data_size, 0x53, 0x57, func_selector]
PUSH1 0x59      //[0x59, 0x04, call_data_size, 0x53, 0x57, func_selector]
JUMP            //[0x59, 0x04, call_data_size, 0x53, 0x57, func_selector]

// This is JUMPdest 4 
// This is where code will continue from line after the solidity has chedked below things 
// 1. Function Dispact
// 2. Checked if their is msg.value
// 3. Checked if calldata or data is being sent with msg.value or not
// 4. Recieved now in stack the data that has been sent in msg.value
JUMPDEST        //[data_Sent, 0x57, func_selector]
PUSH0           //[0x00, data_Sent, 0x57, func_selector] now sstore will store data at 0x00 or 0 index the value that is sent
SSTORE          //Stack:[0x57, func_selector] Storage: [data_Sent]
JUMP            //Stack:[func_selector] Storage: [data_Sent]  we will jump to 0x57 which is 87 opcode or below jumpdest
// ↓↓↓↓↓↓↓↓  this is where the code will execute next  from below jumpdest
// Jumpdest 5
JUMPDEST        //Stack:[func_selector]
STOP            //Stack:[func_selector]  execution ended

// What below code block is checking if thae calldata value that we are sending is it only the function slector or of 0x04 bytes 
// Or does tha calldata value contains more than function slector does it scarry data of yes than it would be 
// function selector 4 bytes + data/ number value of 32 bytes 
// If it does contain data than it will to next jumpdest otherwise it will revert at line 152

// Jump destination from line 118 to here this is update number of horses jumpdestination
JUMPDEST        //[0x04, call_data_size, 0x53, 0x57, func_selector] 
PUSH0           //[0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
PUSH1 0x20      //[0x20, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
DUP3            //[0x04, 0x20, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector] Duplicate 3 item on the stack from the top viz 0x04 in line 130
DUP5            //[call_data_size, 0x04, 0x20, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
SUB             //[call_data_size - 0x04, 0x20, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
// what wew are basically checking in calldata is, if their is  more calldata than just the function selector 
// like if calldata contains on function selector or (function selector + data(bytes32)/0x20) 
SLT             //[call_data_size - 0x04 < 0x20, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector] SLT is less than sign
// call_data_size - 0x04 < 0x20 is 1 means it call_data_size - 0x04 only contains function selctor and is less than 32 bytes or 0x20 hex
// call_data_size - 0x04 < 0x20 is 0 means that call_data_size - 0x04 contains more than function selector it carries data 
ISZERO          //[more_calldata_than_selector?, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
PUSH1 0x68      //[0x68, more_calldata_than_selector? true : false, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
JUMPI           //[0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
// We are going to jump if their is more calldata than 0x20 viz 32 bytes  if not the it will revert from below code of line 152

//Revert if their isn't enough calldata
PUSH0           //[0x00, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
DUP1            //[0x00, 0x00, 0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
REVERT
//SO COOL THING ABOUT SOLIDITY IT DIN'T ONLY CHECK FOR MSG.VALUE WHETHER OR NOT IT IS BEING SENT OR NOT AT LINE 53  BUT IT ALSO CHECKED IF THEIR IS ENOUGH DATA THAT IS BEING SENT IN THE CALLDATA TO UPDATE THE NUMBER OF HORSES FROM LINE 133


JUMPDEST        //[0x00, 0x04, call_data_size, 0x53, 0x57, func_selector]
POP             //[0x04, call_data_size, 0x53, 0x57, func_selector]
// call_data_value[0x04] means ignore the 4 bytes or function selctor and load the data in msg.value
// call_data_value[0x04] == 0000000000000000000000000000000000000000000000000000000000000007 is in stack
// 0x1afef78d ignored in calldata by putting in 0x04 in calldataload and 0000000000000000000000000000000000000000000000000000000000000007 is in stack
//  data_Sent == call_data_value[0x04] ==  0000000000000000000000000000000000000000000000000000000000000007
CALLDATALOAD    //[data_Sent, call_data_size, 0x53, 0x57, func_selector]
SWAP2           //[0x53, call_data_size, data_Sent, 0x57, func_selector]
SWAP1           //[call_data_size, 0x53, data_Sent, 0x57, func_selector]
POP             //[0x53, data_Sent, 0x57, func_selector]
JUMP            //[data_Sent, 0x57, func_selector] 0x53 is where the next jumpdest is present and the code will continue from which is jumpdest 4 or 0x53 == 83 opcode from the beggining 


// 3. Metadata of the code this can't be reached out by any of the above code
// It's the data that ethercan uses to verify etc
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