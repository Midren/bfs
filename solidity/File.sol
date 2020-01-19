pragma solidity >=0.4.14 <0.5.13;

import './Directory.sol';
pragma experimental ABIEncoderV2;

contract File {
    enum mode_t {S_IFMT, S_IFSOCK, S_IFLNK, S_IFREG, S_IFBLK, S_IFDIR, S_IFCHR, S_IFIFO} 
    
    struct stat {
        uint atime;
        uint mtime;
        uint ctime;
        mode_t st_mode;
        uint dev_t;
        uint ino;
        uint uid;
        uint gid;
        uint rdev;
        uint size;
        uint blk_size;
        uint blocks;
    }
    
    byte[] _data;
    uint256 size;
    stat public entry_stat; 
    
    function read() view public returns(byte[] memory){
        entry_stat.atime = now;
        return _data;
    }
    
    constructor() public {
        uint time = now;
        entry_stat.atime = time;
        entry_stat.mtime = time;
        entry_stat.ctime = time;
        entry_stat.st_mode = mode_t.S_IFREG;
    }
    
    function bytesToBytes32(uint offset) public returns (bytes32) {
        bytes32 out;

        for (uint i = 0; i < 32; i++) {
            out |= bytes32(_data[offset + i] & 0xFF) >> (i * 8);
        }
        return out;
    }
    
    function write(byte[] memory data) public {
        uint time = now;
        entry_stat.atime = time;
        entry_stat.mtime = time;
        _data = data;
        size = data.length;
    }
    
    function write(byte[] memory data, uint off_t) public {
        for(uint i = off_t; i < data.length; i++){
            _data[i] = data[i];
        }
        uint time = now;
        entry_stat.atime = time;
        entry_stat.mtime = time;
    }
    
    function get_file_size() view public returns(uint256){
        return size;
    }
    
    function get_stat() public returns(stat){
        return entry_stat;
    }
}