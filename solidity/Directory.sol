pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;

import './File.sol';

contract DirectoryFactory {
    function dir_create(string _dir_name, string _curr_dir) public returns(Directory){
        return new Directory(_dir_name, _curr_dir);
    }
}

contract Directory {
    struct Directory_check { 
    Directory dir;
    bool exists;
    }
    DirectoryFactory factory;
    string dir_name;
    string previous_dir;
    mapping(string => Directory) internal directories;
    string[] internal dir_names;
    mapping(string => File) internal files;
    string[] file_names;

    constructor(string _name, string _current_dir) public {
        dir_name = _name;
        previous_dir = _current_dir;
    }
    
    function create_file(string _name) public {
        file_names.push(_name);
        files[_name] = new File();
    }
    
    function file_write(string _file_name, byte[] _data) public {
        files[_file_name].write(_data);
    }
    
    function file_read(string _file_name) view public returns(byte[] memory){
        return files[_file_name].read();
    }
    
    function get_file_names() view public returns(string[] memory){
        return file_names;
    }
    
    function get_dir_names() view public returns(string[] memory){
        return dir_names;
    }

    function create_directory(string _name) public{
        dir_names.push(_name);
        // directories[_name] = Directory_check(factory.dir_create(_name, dir_name), true);
        directories[_name] = factory.dir_create(_name, dir_name);
    }
    
    function get_dir_by_name(string _name) view public returns(Directory){
        // require(directories[_name].exists, "Directory doesn`t exist!");
        return directories[_name];
        
    }
    
    function get_file_by_name(string _name) view public returns(File){
        return files[_name];
    }
}