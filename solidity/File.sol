pragma solidity >=0.4.14 <0.5.13;

contract File {
    byte[] _data;
    uint256 size;
    
    function read() view public returns(byte[] memory){
        return _data;
    }
    
    function bytesToBytes32(uint offset) public returns (bytes32) {
        bytes32 out;

        for (uint i = 0; i < 32; i++) {
            out |= bytes32(_data[offset + i] & 0xFF) >> (i * 8);
        }
        return out;
    }
    
    function write(byte[] memory data) public {
        _data = data;
        size = data.length;
    }
    
    function write(byte[] memory data, uint off_t) public {
        for(uint i = off_t; i < data.length; i++){
            _data[i] = data[i];
        }
    }
    
    function get_file_size() view public returns(uint256){
        return size;
    }
}