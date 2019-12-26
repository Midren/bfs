pragma solidity >=0.4.14 <0.5.13;

contract File {
    byte[] _data;
    uint256 size;
    
    function read() view public returns(byte[] memory){
        return _data;
    }
    
    function write(byte[] memory data) public {
        _data = data;
        size = data.length;
    }
    
    function get_file_size() view public returns(uint256){
        return size;
    }
}