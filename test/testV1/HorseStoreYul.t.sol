// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";
import {TestBaseHorse, IHorseStore} from "./BaseTestV1.t.sol";

contract TestingYul is TestBaseHorse {

    function setUp() public override{
        horseStore =  IHorseStore(address(new HorseStoreYul()));
    }
}