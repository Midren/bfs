pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;

import './File.sol';
import './Directory.sol';
import "github.com/Arachnid/solidity-stringutils/strings.sol";

contract MemoryManager{
    using strings for *;
    DirectoryFactory fact = new DirectoryFactory();
    Directory root_directory = new Directory("/", "/", fact);
    
    function split_into_array(string memory path, string memory _delim) private returns(string[]){
        var s = path.toSlice();
        var delim = _delim.toSlice();
        var parts = new string[](s.count(delim) + 1);
        for(uint i = 0; i < parts.length; i++) {
            parts[i] = s.split(delim).toString();
        }
        return parts;
    }
    
    function find_file(string path) private returns(Directory, string memory){
        string[] memory next_dirs = split_into_array(path, "/");
        Directory current_dir = root_directory;
        string memory file_name = next_dirs[next_dirs.length - 1];
        
        for(uint i = 1; i < next_dirs.length - 1; i++){
            current_dir = root_directory.get_dir_by_name(next_dirs[i]);
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
        var (current_dir, dir_name) = find_file(path);
        current_dir.delete_file(path);
    }
    
    function delete_directory(string memory path) public {
        var (current_dir, dir_name) = find_file(path);
        current_dir.delete_dir(path);
    }
    
    function list_dir(string memory path) view public returns(string[] memory){
        var (current_dir, dir_name) = find_file(path);
        return current_dir.list_dir();
    }
    
    function get_stat_dir(string memory path) public returns(Directory.stat) {
        var (current_dir, dir_name) = find_file(path);
        return current_dir.get_stat_dir();
    }
    
    
}
