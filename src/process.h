
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <stdio.h>
#include <inttypes.h>

#include <libvmi/libvmi.h>

#include<time.h>

//存放进程节点信息
struct info{
	vmi_pid_t pid; //节点
	char *name;
	addr_t addr;
	vmi_pid_t ppid; //父节点
	char *pname;
	addr_t paddr;
};
//获得结构体首地址函数
addr_t getStructAddr(addr_t address,unsigned long offset);
//获取节点信息函数
void getInfo(vmi_instance_t vmi,addr_t current_process,struct info *proc_info,int *sum);
//找到节点的所有孩子节点函数
void findAllChildren(vmi_instance_t vmi,addr_t curProc,struct info *proc_info,int *sum);
//打印输出函数
void printInfo(vmi_instance_t vmi,struct info *proc,int *count);

//获取树遍历时所需的偏移量
unsigned long get_offset(char *name);
//获取系统中的偏移量
void get_ostype(vmi_instance_t vmi);
//获取系统中模块链表头节点
addr_t get_modulelist(vmi_instance_t vmi,addr_t next_module);

//获取系统中进程链表头节点
addr_t get_listhead(vmi_instance_t vmi,addr_t list_head);
//获取树结构进程函数，存储到struct结构中，返回值为进程个数
int process_tree(vmi_instance_t vmi,struct info *proc_tree);
//获取链表结构进程函数，存储到struct结构中，返回获取进程的个数
int process_list(vmi_instance_t vmi,struct info *proc_list);
//获取模块结构名函数，存储到struct的name中，并返回模块个数
int get_module(vmi_instance_t vmi,struct info *module_info);
//模块结构输出函数
void module_list(vmi_instance_t vmi,struct info *module);
//截取字符串
char * left(char *dst,char *src, int n);
//通过配置文件libvmi.conf获取虚拟机名称，存储到数组name中并返回虚拟机个数
int get_VMname(char **name);

char* copy(char* from,char *to);
//通过指令获取正在运行的虚拟机状态以及信息并保持到文件xl_info,读取文件保存到数组并返回读取行数值
int get_xl(char **a);

