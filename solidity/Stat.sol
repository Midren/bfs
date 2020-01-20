pragma solidity >=0.4.25 <=0.4.26;
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
    
