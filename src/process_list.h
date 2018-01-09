#ifndef _PROCESS_LIST_H
#define _PROCESS_LIST_H

#include "definition.h"
#include <algorithm>
#include <iostream>
using namespace std;

/*初始化虚拟机vmi,
	(1):  argv->虚拟机名称
	(2):  数据结构VM_vmi
*/
int VM_vmi_init(char *argv,VM_vmi &vmi);
bool print_XL_list(); 
/*初始化vmi的成员变量process(进程)
	(1):  VM_process->vmi成员变量
*/
int VM_process_init(struct VM_process &process);
/*遍历vmi虚拟机的进程链表，产生vmi成员变量process链式结构
	(1):  要遍历的虚拟机
	(2):  该虚拟机的成员变量process
*/
int VM_find_process_list(VM_vmi &vmi_os,VM_process &process);
/*VM_find_process_tree（）->dfs遍历vmi虚拟机的进程链表，产生vmi成员变量process链式结构
	(1):  要遍历的虚拟机
	(2):  该虚拟机的成员变量process
*/
void VM_find_process_tree_dfs(VM_vmi &vmi_os,VM_process &process,addr_t current_process,int b); // dfs打印进程树
void VM_find_process_tree(VM_vmi &vmi_os,VM_process &process); // 遍历vmi的树

void printf_process_tree(const VM_process &process,int b);//终端打印进程树

void get_module_infornmation(VM_vmi &vmi_os,addr_t current_module);
int VM_module_init(VM_module &module);//初始化模块
void VM_find_modules_list( VM_vmi &vmi_os,VM_module &module);//遍历vmi虚拟机模块链表，产生vmi成员变量module链式结构
void VM_find_process_code(VM_vmi &vmi_os,VM_process &process);//查找进程代码段

int VM_find_process_hide(VM_vmi &vmi_os);

void VM_lsmod(VM_module& head);
bool walk_module(VM_vmi &vmi_os);//遍历模块
vector<VM_module*> cmp_lsmod(VM_vmi &vmi_os);
vector<VM_process*> cmp_process(VM_vmi &vmi_os);

/**/

/*解析地址，返回路径vector*/
vector<string> get_path_arry(string path);

/*拿到目标目录的目录项地址*/
addr_t get_search_dentry(VM_vmi& vmi_os,string path);

bool get_file_info(VM_file& newnode);

/*ls命令*/
bool do_ls(VM_vmi& vmi_os,addr_t ls_addr);

/*在本层查找指定目录*/
addr_t find_dentry_addr(const VM_vmi& vmi_os,addr_t parent_dentry_addr,string dentry_name);

void do_dfs(VM_vmi& vmi_os,addr_t subdirs_head,VM_file* parentNode,int deep,vector<string>& file_vector);

void init_file_tree(VM_vmi& vmi_os,string path);


void traverse_file_tree(VM_file* fileNode,int deep);

vector<VM_file*> cmp_file(VM_vmi& vmi_os,char* path);

vector<VM_file*> dfs_cmp_file(VM_file* fileNode,int deep,vector<string>& file_vector);

vector<VM_module*> cmp_lsmod(VM_vmi &vmi_os);

bool walk_module(VM_vmi &vmi_os);

int VM_module_init(VM_module &module);

void VM_find_modules_list(VM_vmi &vmi_os,VM_module &module);

void get_module_info(VM_vmi &vmi_os,VM_module &module,addr_t current_module);

bool get_vm_list(VM_list_vm *v);

#endif
