// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

interface IHorseStore {

    function updateNumberOfHorses(uint256 updateNumber) external;

    function viewNumberOfHorses() external view returns (uint256);
}
