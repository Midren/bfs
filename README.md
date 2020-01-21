# Blockchain based filesystem

## Table of contents
 - [Installing](#installing)
 - [Usage](#usage)
 - [Team](#team)
 - [Documentation](#documentation)
 
 
## Installing
### Dependencies
Depends on the next C++ libraries:
- Boost
- Crypto++
- Curl

For Ubuntu:
```sh
sudo apt install libboost-all-dev libcrypto++-dev libcurl4-gnutls-dev
```
### Build
Compile:
```sh
mkdir build
cd build
cmake .. && make
```

### Set up local blockchain
Check in [wiki](https://github.com/RomanMilishchuk/bfs/wiki/Setting-up-local-Ethereum-blockchain) pages, how to set up
local blockchain. Use `config.json` for configuring local blockchain.

## Usage

### Deploying Smart Contracts
Firstly, use [Remix](http://remix.ethereum.org/) (it is important to use http version, otherwise geth/aleth won't work) to
compile solidity code(importantly with optimization enabled) and publish for local blockchain. Working options in remix:
- Environment: Web3 Provider (http://localhost:8545 address by default)
- Gas limit: 12000000
- Value: 0 wei

Then, save somewhere the address of Memory Manager.

### Mount filesystem
```
./BFS <directory> <YOUR_ACCOUNT_ADDRESS> <MEMORY_MANAGER_ADDRESS>
```
Example:
```
./BFS mnt/ "0x00c469eee8b9bc1a331070be0e5814a0bc6f902e" "0xdd8ac7f9f50e465bac369dffabc978ec04183825"
```

## TODO:
- [ ] Finish FUSE driver
  - [ ] Fix creating files and directories
  - [ ] Fix sometimes problems with writing to a file
- [ ] Add permission support using Zero knowledge
- [ ] Add deprolying contract using C++

## Documentation
All documentation can be found in the [wiki](https://github.com/RomanMilishchuk/bfs/wiki) pages.

## Team
| **Roman Milishchuk** | **Hermann Yavorskyi** | **Yurii Yelisieiev** |
| :---: |:---:|:---:|
| ![image](https://user-images.githubusercontent.com/32875119/71295256-cc177a00-2383-11ea-92a5-944b3969e083.png) | <img src="https://hackernoon.com/hn-images/1*KWr54bVaO-XAQWwZPSHUXA.png"> | <img src="https://themerkle.com/wp-content/uploads/2015/03/maxresdefault.jpg"> |
| [RomanMilishchuk](https://github.com/RomanMilishchuk) | [wardady](https://github.com/wardady) | [YuraYelisieiev](https://github.com/YuraYelisieiev) |x
