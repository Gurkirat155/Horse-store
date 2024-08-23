// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";
import {TestBaseHorse, HorseStore} from "./BaseTestV1.t.sol";
// import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";

contract TestHorseStoreHuff is TestBaseHorse {
    string public constant HORSE_STORE_HUFF_LOCATION = "horseStoreV1/HorseStore";

    function setUp() public override {
        horseStore = HorseStore(HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION));
    }

    // function testReadHuffContractValue
}
