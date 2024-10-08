// SPDX-License-Identifier: MIT
pragma solidity 0.8.20;

import {Base_TestV2, HorseStore} from "./BaseTestV2.t.sol";
import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuffV2 is Base_TestV2 {
    string public constant horseStoreLocation = "horseStoreV2/HorseStoreV2";

    function setUp() public override {
        horseStore = HorseStore(
            HuffDeployer.config().with_args(bytes.concat(abi.encode(NFT_NAME), abi.encode(NFT_SYMBOL))).deploy(
                horseStoreLocation
            )
        );
    }
}