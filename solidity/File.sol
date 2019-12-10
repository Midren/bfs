pragma solidity >=0.4.14 <0.5.13;

contract File {
    byte[] _data;
    uint32 _size;
    
    function read() view public returns(byte[] memory){
        return _data;
    }
    
    function write(byte[] memory data) public {
        _data = data;
    }
}