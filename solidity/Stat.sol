pragma solidity >=0.4.14 <0.5.13;
pragma experimental ABIEncoderV2;
    
library FileStat {
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
}
