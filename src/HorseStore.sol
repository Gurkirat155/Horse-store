// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

contract horseStore {

    uint256 numberOfHorses;

    function updateNumberOfHorses(uint256 updateNumber) external {
        numberOfHorses = updateNumber ;
    }


    function viewNumberOfHorses() external view returns(uint256) {
        return numberOfHorses;
    }
}