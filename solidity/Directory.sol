pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;

import './File.sol';
import 'https://github.com/ethereum/dapp-bin/blob/master/library/stringUtils.sol';

contract DirectoryFactory{
    function dir_create(string _dir_name, string _curr_dir) public returns(Directory){
        Directory new_dir = new Directory(_dir_name, _curr_dir, this);
        return new_dir;
    }
    
}

contract Directory {
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
    
    stat entry_stat;
    DirectoryFactory public factory;
    string dir_name;
    string previous_dir;
    mapping(string => Directory) internal directories;
    string[] dir_list;
    mapping(string => File) internal files;

    constructor(string _name, string _current_dir, DirectoryFactory _factory) public {
        dir_name = _name;
        previous_dir = _current_dir;
        factory = _factory;
        uint time = now;
        entry_stat.atime = time;
        entry_stat.mtime = time;
        entry_stat.ctime = time;
        entry_stat.st_mode = mode_t.S_IFDIR;
    }
    
    function find(string value) returns(uint) {
        uint i = 0;
        while (StringUtils.equal(dir_list[i], value) == false) {
            i++;
        }
        return i;
    }

    function removeByValue(string value) {
        uint i = find(value);
        removeByIndex(i);
    }

    function removeByIndex(uint i) {
        while (i<dir_list.length-1) {
            dir_list[i] = dir_list[i+1];
            i++;
        }
        dir_list.length--;
    }
    
    function create_file(string _name) public {
        dir_list.push(_name);
        files[_name] = new File();
    }
    
    function file_write(string _file_name, byte[] _data) public {
        files[_file_name].write(_data);
    }
    
    function file_write(string _file_name, byte[] _data, uint off_t) public {
        files[_file_name].write(_data, off_t);
    }
    
    function file_read(string _file_name) view public returns(byte[] memory){
        return files[_file_name].read();
    }
    
    function file_read(string _file_name, uint off_t) view public returns(bytes32){
        return files[_file_name].bytesToBytes32(off_t);
    }
    
    
    function list_dir() view public returns(string[] memory){
        return dir_list;
    }
    
    function get_file_size(string _file_name) public returns(uint256){
        return files[_file_name].get_file_size();
    }

    function create_directory(string _name) public{
        dir_list.push(_name);
        directories[_name] = factory.dir_create(_name, dir_name);
    }
    
    function get_dir_by_name(string _name) view public returns(Directory) {
        return directories[_name];
    }

    function get_file_by_name(string _name) view public returns(File) {
        return files[_name];
    }
    
    function delete_file(string _name) public {
        delete files[_name];
        removeByValue(_name);
    }
    
    function delete_dir(string _name) public {
        delete directories[_name];
        removeByValue(_name);
    }
    
    function get_stat_dir() public returns(stat){
        return entry_stat;
    }
    
    function get_stat_file(string _name) public returns(File.stat){
        return files[_name].get_stat();
    }
}