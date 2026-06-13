
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BLOCK_SIZE 512                          // 定义每个磁盘块的大小为 512 byte
#define TOTAL_BLOCKS 1280                       // 定义文件系统总共包含 1280 个磁盘块
#define FS_SIZE (BLOCK_SIZE * TOTAL_BLOCKS)     //定义文件系统的总大小
#define MAX_FILENAME 28                         // 定义文件/目录名最大长度为 28 字符
#define MAX_FILES 128                           // 定义最大文件/目录的总数为 128
#define DIR_ENTRY_SIZE sizeof(struct dir_entry) // 定义目录项结构体的大小

const char *ramdisk = "/dev/ram0"; // 定义虚拟磁盘设备文件路径

struct super_block {// 超级块
    int total_blocks;       // 总块数
    int free_blocks;        // 空闲块数
    int bitmap_offset;      // 位图在磁盘上的起始块号
    int root_dir_offset;    // 根目录在磁盘上的起始块号
};

struct dir_entry {// 目录项
    char name[MAX_FILENAME]; // 文件/目录名
    int is_directory;        // 标志位：0 为文件，1 为目录
    int start_block;         // 文件/目录数据在磁盘上的起始块号
    int size;                // 文件/目录占用的块数 [然而在当前实现中，所有文件大小都为1块!!!!!!]
};

struct super_block sb;// 初始化超级块实例，用于在内存中维护文件系统的超级块信息

unsigned char bitmap[TOTAL_BLOCKS];// 初始化位图阵列变量bitmap，用于跟踪每个磁盘块的使用情况，0 为空闲，1 为已使用

struct dir_entry root_dir[MAX_FILES];// 初始化根目录表变量root_dir，在内存中维护根目录下的所有文件和目录的目录项信息


void write_block(int fd, int block_num, void *buf) {
    /*
    * 写入数据到指定块
    * 参数：
    * fd: 文件描述符
    * block_num: 要写入的块的逻辑块号
    * buf: 待写入数据的缓冲区指针
    */

    lseek(fd, block_num * BLOCK_SIZE, SEEK_SET);
    // 使用 lseek 定位到文件描述符 fd 中 block_num 块的起始位置
    // BLOCK_SIZE * block_num 得到该块在磁盘上的字节偏移量
    write(fd, buf, BLOCK_SIZE);
    // 从 buf 缓冲区写入 BLOCK_SIZE 大小的数据到当前文件描述符位置
}


void read_block(int fd, int block_num, void *buf) {
    /*
    *从指定块读取数据
    *参数：
    *fd: 文件描述符
    *block_num: 要读取的块的逻辑块号
    *buf: 存放读取数据的缓冲区指针
    */


    lseek(fd, block_num * BLOCK_SIZE, SEEK_SET);
    // 使用 lseek 定位到文件描述符 fd 中 block_num 块的起始位置

    read(fd, buf, BLOCK_SIZE);
    // 从当前文件描述符位置读取 BLOCK_SIZE 大小的数据到 buf 缓冲区

}

int allocate_block() {
    /*
    *分配一个空闲块
    *返回值：
    *成功：块号
    *失败：-1
     */
    for (int i = 0; i < TOTAL_BLOCKS; i++) {//遍历位图查找块
        if (bitmap[i] == 0) {   // 找到一个空闲块
            bitmap[i] = 1;      // 将该块标记为已使用
            sb.free_blocks--;   // 更新超级块中空闲块的数量
            return i;           // 返回分配到的块号
        }
    }
    return -1;  // 没有空闲块，返回失败
}


void free_block(int block_num) {
    /*
     *释放一个块
     *参数：
     *block_num: 要释放的块的逻辑块号
     */


    if (bitmap[block_num]) {    // 检查该块是否已被占用，如是，释放
        bitmap[block_num] = 0;  // 标记该块为空闲
        sb.free_blocks++;       // 更新空闲块数量
    }
}
void save_metadata(int fd) {
    /*将内存中的元数据（超级块、位图、根目录）写入磁盘
     *参数：
    *fd: 文件描述符
    */
    lseek(fd, 0, SEEK_SET);//定位磁盘起始位置
    write(fd, &sb, sizeof(sb)); // 写入超级块数据到磁盘
    write(fd, bitmap, sizeof(bitmap));//写入位图数据到磁盘
    lseek(fd, sb.root_dir_offset * BLOCK_SIZE, SEEK_SET);// 保存根目录
    write(fd, root_dir, sizeof(root_dir));//写入根目录数据到磁盘
}

void load_metadata(int fd) {
    /*
     *从磁盘加载元数据到内存
     *参数:
     *fd:文件描述符
     */

    lseek(fd, 0, SEEK_SET);// 定位磁盘起始位置
    read(fd, &sb, sizeof(sb));// 从磁盘读取超级块数据到内存中sb 变量
    read(fd, bitmap, sizeof(bitmap));// 从磁盘读取位图数据到内存中的bitmap 阵列
    lseek(fd, sb.root_dir_offset * BLOCK_SIZE, SEEK_SET); //读取根目录
    read(fd, root_dir, sizeof(root_dir)); // 从磁盘读取根目录数据到内存中的root_dir 阵列

}

void format_fs(int fd) {
    /*
     *格式化文件系统
     *参数:
     *fd:文件描述符
     */
    sb.total_blocks = TOTAL_BLOCKS;// 设置总块数

    sb.root_dir_offset = 20;  //目录表偏移到第20块，避免覆盖数据块


    memset(bitmap, 0, sizeof(bitmap));// 初始化位图，标记所有块为空闲

    //start 标记0~(root_dir占用块)为已用
    int metadata_blocks = sb.root_dir_offset + (sizeof(root_dir) + BLOCK_SIZE - 1) / BLOCK_SIZE;
    for (int i = 0; i < metadata_blocks; i++) {
        bitmap[i] = 1;
    }
    //end 标记0~(root_dir占用块)为已用

    memset(root_dir, 0, sizeof(root_dir));  // 初始化根目录


    save_metadata(fd);//将初始化后的元数据写入到磁盘
}



int find_file(const char *name) {
    /*
     *在根目录中查找文件或目录
     *参数：
     *name: 要查找的文件或目录的名称
     *返回值：
     *成功：目录项的索引
     *失败：-1
     */
    for (int i = 0; i < MAX_FILES; i++) {
        if (strcmp(root_dir[i].name, name) == 0) {        // 使用 strcmp 比较名称，如果匹配则返回当前索引
            return i;
        }
    }
    return -1; // 返回失败
}

int find_empty_dir_entry() {

    /*
     *查找一个空闲的目录项位置
     *返回值：
     *成功：空目录项的索引
     *失败：-1
     */
    for (int i = 0; i < MAX_FILES; i++) {//遍历根目录表
        if (root_dir[i].name[0] == '\0') { // 检查名称的第一个字符是否为空
            return i;//返回空目录项的索引
        }
    }
    return -1; // 目录项已满，返回失败
}

void create_entry(int fd, const char *name, int is_dir, int size) {
    /*
     *
     *创建文件或目录
     *参数：
     *fd: 文件描述符
     *name: 文件/目录的名称
     *is_dir: 标志位，0为文件，1为目录
     *size: 文件/目录占用的块数 [当前实现仅能为1！！！！]
     */


    if (find_file(name) != -1) {    // 检查是否存在同名文件或目录
        printf("已存在该名称的文件或目录\n");
        return;
    }
    int idx = find_empty_dir_entry();    // 查找一个空闲的目录项，保存空目录项的索引

    if (idx == -1) {//判断是否找不到空目录
        printf("目录项已满\n");
        return;
    }

    int start_block = allocate_block();    // 分配一个空闲块给新的文件或目录，保存块号

    if (start_block == -1) {//判断是否没有空块
        printf("磁盘空间不足\n");
        return;
    }

    //start初始化新的目录项
    strncpy(root_dir[idx].name, name, MAX_FILENAME - 1); // 复制名称，确保以 '\0' 结尾
    root_dir[idx].name[MAX_FILENAME - 1] = '\0'; // 强制 null 终止
    root_dir[idx].is_directory = is_dir;        // 设置类型 (文件或目录)
    root_dir[idx].start_block = start_block;    // 设置起始块号
    root_dir[idx].size = size;                  // 设置占用块数
    //end初始化新的目录项


    save_metadata(fd);// 将更新后的元数据写入磁盘
    printf("创建%s '%s' 成功\n", is_dir ? "目录" : "文件", name);
}


void delete_entry(int fd, const char *name) {
    /*
     *删除文件或目录并释放其占用的块
     *参数：
     *fd: 文件描述符
     *name: 要删除的文件或目录的名称
     *
     */


    int idx = find_file(name);    // 查找要删除的文件/目录的索引

    if (idx == -1) {//判断文件/目录是否不存在
        printf("找不到文件或目录\n");
        return;
    }
    for (int i = 0; i < root_dir[idx].size; i++) {
        free_block(root_dir[idx].start_block + i);  // 释放该文件/目录占用的所有块
    }

    memset(&root_dir[idx], 0, sizeof(struct dir_entry));    // 清除内存中的目录项信息

    save_metadata(fd);    // 将更新后的元数据写入磁盘

    printf("已删除 '%s'\n", name);
}

//

void rename_entry(int fd, const char *old_name, const char *new_name) {
    /*
     *重命名文件或目录
     *参数：
     *fd: 文件描述符
     *old_name: 旧名称
     *new_name: 新名称
     */

    int idx = find_file(old_name);  // 查找旧名称文件/目录对应的目录项索引

    if (idx == -1) {//判断旧名称文件/目录是否存在
        printf("找不到文件或目录\n");
        return;
    }

    strncpy(root_dir[idx].name, new_name, MAX_FILENAME - 1);    //更新目录项的名称
    root_dir[idx].name[MAX_FILENAME - 1] = '\0'; //强制null终止
    save_metadata(fd);    // 将更新后的元数据写入磁盘
    printf("重命名 '%s' 为 '%s' 成功\n", old_name, new_name);
}

void list_dir() {
    /*
     *显示当前根目录中的所有文件和目录
     */
    printf("当前目录内容：\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (root_dir[i].name[0] != '\0') {        // 检查目录项是否被占用
            printf("%s\t%s\t块号: %d 大小: %d\n",
                   root_dir[i].is_directory ? "[目录]" : "[文件]", //判断是目录还是文件
                   root_dir[i].name,                               // 名称
                   root_dir[i].start_block,                        // 起始块号
                   root_dir[i].size);                              // 占用大小
        }
    }
}


void write_file(int fd, const char *name, const char *data) {
    /*
     *向指定文件写入数据
    *参数：
    *fd:文件描述符
     *name:文件名
     *data:数据
      */
    int idx = find_file(name);    // 查找文件索引
    if (idx == -1 ) { // 判断文件是否存在
        printf("找不到该文件或它是目录\n");
        return;
    }
    if ( root_dir[idx].is_directory) {//判断文件名是否为目录
        printf("名称为目录\n");
        return;
    }
    char buf[BLOCK_SIZE] = {0};  // 初始化缓冲区为0，防止残留脏数据
    strncpy(buf, data, BLOCK_SIZE - 1); // 拷贝数据到缓冲区，确保不溢出
    write_block(fd, root_dir[idx].start_block, buf); // 将数据写入文件的起始块

    printf("写入完成\n");
}


void read_file(int fd, const char *name) {
    /*
     *从指定文件读取数据
    *参数：
    *fd:文件描述符
     *name:文件名
     */

    int idx = find_file(name); // 查找文件索引

    if (idx == -1 ) { // 判断文件是否存在
        printf("找不到该文件或它是目录\n");
        return;
    }
    if ( root_dir[idx].is_directory) {//判断文件名是否为目录
        printf("名称为目录\n");
        return;
    }

    char buf[BLOCK_SIZE] = {0}; //创建一个缓冲区用于存放读取的数，并初始化为 0
    read_block(fd, root_dir[idx].start_block, buf);   //从文件起始块读取数据
    printf("文件内容：\n%s\n", buf);
}


void copy_entry(int fd, const char *src, const char *dst) {
   /*
     *复制文件或目录
     *参数：
    *fd: 文件描述符
    *src: 源文件/目录的名称
    *dst: 目标文件/目录的名称
     */
    int idx = find_file(src); // 查找源文件/目录在文件系统中的索引
    if (idx == -1) {{// 判断源文件/目录是否存在
        printf("源文件或目录不存在\n");
        return;
    }


    char buf[BLOCK_SIZE] = {0}; //初始化缓存区
    read_block(fd, root_dir[idx].start_block, buf);   //读取源文件的数据

    int new_start_block = allocate_block();// 分配一个空闲块给新文件/目录
    if (new_start_block == -1) {//判断是否分配失败，如是，说明磁盘空间不足
        printf("磁盘空间不足，复制失败\n");
        return;
    }

    int new_idx = find_empty_dir_entry();
    if (new_idx == -1) {// 如果没有空闲目录项，如是，说明目录项已满
        free_block(new_start_block);// 释放已分配的块
        printf("目录项已满，复制失败\n");
        return;
    }

    // start写入新的目录项
    strncpy(root_dir[new_idx].name, dst, MAX_FILENAME - 1);
    root_dir[new_idx].name[MAX_FILENAME - 1] = '\0';// 确保字符串以空字符结尾
    root_dir[new_idx].is_directory = root_dir[idx].is_directory;// 复制是否为目录的标志
    root_dir[new_idx].start_block = new_start_block;// 设置新文件/目录的起始块号
    root_dir[new_idx].size = 1;// 复制文件大小为 1 块 [对于当前实现，文件大小固定为1块！！！]
    //end写入新的目录项

    write_block(fd, new_start_block, buf);   //写入数据到新文件块

    save_metadata(fd); //保存新的目录结构和位图

    printf("已复制 '%s' 为 '%s'\n", src, dst);
}




int main() {
    int fd = open(ramdisk, O_RDWR);//以读写模式打开虚拟磁盘设备文件

    if (fd < 0) {
        perror("打开ramdisk失败"); //如果打开失败，打印错误信息
        return 1;//返回错误码，结束运行
    }

    char name[128], name2[128], data[BLOCK_SIZE]; //用于记录用户输入文件/目录名和数据

    load_metadata(fd);// 加载元数据

    int choice;//记录用户输入

    while (1) {
        printf("\n=== 功能选单 ===\n");
        printf("0. 格式化文件系统\n");
        printf("1. 创建文件\n");
        printf("2. 创建目录\n");
        printf("3. 删除文件/目录\n");
        printf("4. 重命名\n");
        printf("5. 复制文件/目录\n");
        printf("6. 写入文件\n");
        printf("7. 读取文件\n");
        printf("8. 显示目录内容\n");
        printf("9. 退出\n> ");
        scanf("%d", &choice); // 读取用户选择
        getchar(); // 吸收 scanf 留下的换行符

        switch (choice) {    //根据用户选择执行相应操作
            case 0:
                printf("确定执行格式化吗?:[y/N] ");
                scanf("%c", (char *)&choice);//用户输入是否确定格式化
                while ((name[0] = getchar()) != '\n' && name[0]  != EOF); //清空输入缓冲区，防止死循环
                if(choice=='y') {//判断用户是否确定执行格式化
                    format_fs(fd); //格式化文件系统
                    break;
                }

                printf("未执行格式化\n");
                break;
            case 1:
                printf("输入文件名: ");
                fgets(name, sizeof(name), stdin);//读取文件名
                name[strcspn(name, "\n")] = 0; // 去除文件名末尾的换行符
                create_entry(fd, name, 0, 1);   //创建文件(is_dir=0)
                break;
            case 2:
                printf("输入目录名: ");
                fgets(name, sizeof(name), stdin); // 读取目录名
                name[strcspn(name, "\n")] = 0;// 去除目录名末尾的换行符
                create_entry(fd, name, 1, 1);     // 创建目录 (is_dir =1)
                break;
            case 3:
                printf("输入名称: ");
                fgets(name, sizeof(name), stdin); // 读取要删除的名称
                name[strcspn(name, "\n")] = 0;
                delete_entry(fd, name);// 删除文件或目录
                break;
            case 4:
                printf("输入旧名称: ");
                fgets(name, sizeof(name), stdin); // 读取旧名称
                name[strcspn(name, "\n")] = 0;
                printf("输入新名称: ");
                fgets(name2, sizeof(name2), stdin); //读取新名称
                name2[strcspn(name2, "\n")] = 0;
                rename_entry(fd, name, name2);//执行重命名
                break;
            case 5:
                printf("输入源名称: ");
                fgets(name, sizeof(name), stdin); // 读取源名称
                name[strcspn(name, "\n")] = 0;
                printf("输入目标名称: ");
                fgets(name2, sizeof(name2), stdin); // 读取目标名称
                name2[strcspn(name2, "\n")] = 0;
                copy_entry(fd, name, name2);       // 复制
                break;
            case 6:
                printf("输入文件名: ");
                fgets(name, sizeof(name), stdin); // 读取文件名
                name[strcspn(name, "\n")] = 0;
                printf("输入写入数据: ");
                fgets(data, sizeof(data), stdin); //读取要写入的数据
                data[strcspn(data, "\n")] = 0;
                write_file(fd, name, data);// 写入文件
                break;
            case 7:
                printf("输入文件名: ");
                fgets(name, sizeof(name), stdin);// 读取文件名
                name[strcspn(name, "\n")] = 0;
                read_file(fd, name);//读取文件
                break;
            case 8:
                list_dir(); //显示目录内容
                break;
            case 9:
                close(fd);  //关闭磁盘文件描述符
                return 0;   // 退出程序
            default:
                printf("无效选项\n"); // 处理无效输入
        }
    }
}
