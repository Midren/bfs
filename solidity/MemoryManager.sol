pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;

import './File.sol';
import './Directory.sol';

contract MemoryManager{
    DirectoryFactory fact = new DirectoryFactory();
    Directory root_directory = new Directory("/", "/", fact);
    
    function split_into_array(string memory path) public returns(string[]){
        bytes memory path_bytes = bytes(path);
        
        uint cnt = 0;
        for(uint k = 0; k < path_bytes.length; k++)
            if(path_bytes[k] == '/')
                cnt++;
        
        var parts = new string[](cnt);
        
        uint prev = 1;
        uint str_num = 0;
        for(uint i = 1; i < path_bytes.length; i++) {
            if(path_bytes[i] == '/') {
                bytes memory res = new bytes(i - prev);
                for(uint j = prev; j < i; j++) {
                    res[j-prev] = path_bytes[j];
                }
                parts[str_num] = string(res);
                str_num++;
                prev = i+1;
            }
        }
        if(prev != path_bytes.length) {
            bytes memory res1 = new bytes(path_bytes.length - prev);
            for(j = prev; j < path_bytes.length; j++) {
                res1[j-prev] = path_bytes[j];
            }
            parts[str_num] = string(res);
        }
        return parts;
    }
    
    function find_file(string path) public returns(Directory, string memory){
        string[] memory next_dirs = split_into_array(path);
        Directory current_dir = root_directory;
        string memory file_name = next_dirs[next_dirs.length - 1];
        
        for(uint i = 1; i < next_dirs.length - 1; i++){
            current_dir = current_dir.get_dir_by_name(next_dirs[i]);
        }
        return (current_dir, file_name);
    }
    
    function create_file(string memory path) public returns(string[] memory){
        var (current_dir, file_name) = find_file(path);
        current_dir.create_file(file_name);
        return current_dir.list_dir();
    }
    
    function write(string memory path, byte[] memory data) public {
        var (current_dir, file_name) = find_file(path);
        current_dir.file_write(file_name, data);
    }
    
    function write(string memory path, byte[] memory data, uint off_t) public {
        var (current_dir, file_name) = find_file(path);
        current_dir.file_write(file_name, data, off_t);
    }
    
    function read(string memory path) view public returns(byte[] memory){
         var (current_dir, file_name) = find_file(path);
         return current_dir.file_read(file_name);
    }
    
    function read(string memory path, uint256 off_t) view public returns(bytes32){
         var (current_dir, file_name) = find_file(path);
         return current_dir.file_read(file_name, off_t);
    }
    
    function make_directory(string path) public returns(string[] memory){
        var (current_dir, dir_name) = find_file(path);
        current_dir.create_directory(dir_name);
        return current_dir.list_dir();
    }
    
    function get_file_size(string memory path) public returns(uint256) {
        var (current_dir, file_name) = find_file(path);
        return current_dir.get_file_size(file_name);
    }
    
    function delete_file(string memory path) public {
        var (current_dir, file_name) = find_file(path);
        current_dir.delete_file(file_name);
    }
    
    function delete_directory(string memory path) public {
        var (current_dir, dir_name) = find_file(path);
        current_dir.delete_dir(dir_name);
    }
    
    function list_dir(string memory path) view public returns(string[] memory){
        var (current_dir, dir_name) = find_file(path);
        return current_dir.list_dir();
    }
    
    function get_stat(string memory path) view public returns(FileStat.stat){
        var (current_dir, file_name) = find_file(path);
        if(current_dir.is_file(file_name))
            return current_dir.get_stat_file(file_name);
        else
            return current_dir.get_stat_dir();
    }
}
