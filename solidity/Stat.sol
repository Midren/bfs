pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;
    
library FileStat {
    struct stat {
        uint dev;
        uint ino;
        uint mode;
        uint uid;
        uint gid;
        uint rdev;
        uint size;
        uint blk_size;
        uint blocks;
        uint atime;
        uint mtime;
        uint ctime;
    }
}
