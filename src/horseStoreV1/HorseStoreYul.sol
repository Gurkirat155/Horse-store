// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

contract HorseStoreYul {
    uint256 numberOfHorses;

    function updateNumberOfHorses(uint256 updateNumber) external {
        // numberOfHorses = updateNumber;
        assembly {
            sstore(numberOfHorses.slot, updateNumber)
        }
    }

    function viewNumberOfHorses() external view returns (uint256) {
        // return numberOfHorses;
        assembly {
            let num:= sload(numberOfHorses.slot)
            mstore(0,num)
            return(0, 0x20)
        }
    }
}
