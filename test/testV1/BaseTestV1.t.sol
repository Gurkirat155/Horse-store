// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

import {Test} from "forge-std/Test.sol";
import {console} from "forge-std/console.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

abstract contract TestBaseHorse is Test {
    HorseStore horseStore;

    function setUp() public virtual {
        horseStore = new HorseStore();
    }

    function testReadHorse() public view {
        console.log("this is value of horse", horseStore.viewNumberOfHorses());
        uint256 valueOfHorses = horseStore.viewNumberOfHorses();
        assertEq(valueOfHorses, 0);
    }

    function testUpdateHorses(uint256 updateValue) public {
        horseStore.updateNumberOfHorses(updateValue);
        uint256 currentValueHorses = horseStore.viewNumberOfHorses();
        assertEq(currentValueHorses, updateValue);
    }
}
